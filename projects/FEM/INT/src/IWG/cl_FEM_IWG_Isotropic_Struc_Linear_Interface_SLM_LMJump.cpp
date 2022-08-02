
#include "cl_FEM_IWG_Isotropic_Struc_Linear_Interface_SLM_LMJump.hpp"

#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_Set.hpp"
#include "cl_FEM_Cluster.hpp"

#include "fn_eye.hpp"
#include "fn_dot.hpp"

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        IWG_Isotropic_Struc_Linear_Interface_SLM_LMJump::IWG_Isotropic_Struc_Linear_Interface_SLM_LMJump()
        {
            // set size for the property pointer cell
            mMasterProp.resize( static_cast< uint >( IWG_Property_Type::MAX_ENUM ), nullptr );

            // set size for the constitutive model pointer cell
            mMasterCM.resize( static_cast< uint >( IWG_Constitutive_Type::MAX_ENUM ), nullptr );
            mSlaveCM.resize( static_cast< uint >( IWG_Constitutive_Type::MAX_ENUM ), nullptr );

            // set size for the stabilization parameter pointer cell
            mStabilizationParam.resize( static_cast< uint >( IWG_Stabilization_Type::MAX_ENUM ), nullptr );


        }

        //------------------------------------------------------------------------------

        void
		IWG_Isotropic_Struc_Linear_Interface_SLM_LMJump::compute_residual( real aWStar )
        {
#ifdef DEBUG
            // check master and slave field interpolators
            this->check_field_interpolators( mtk::Master_Slave::MASTER );
            this->check_field_interpolators( mtk::Master_Slave::SLAVE );
#endif



            // get master index for residual dof type, indices for assembly
            const uint tMasterDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 )( 0 ), mtk::Master_Slave::MASTER );
            const uint tMasterResStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
            const uint tMasterResStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

            // get slave index for residual dof type, indices for assembly
            const uint tSlaveDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 )( 0 ), mtk::Master_Slave::SLAVE );
            const uint tSlaveResStartIndex = mSet->get_res_dof_assembly_map()( tSlaveDofIndex )( 0, 0 );
            const uint tSlaveResStopIndex  = mSet->get_res_dof_assembly_map()( tSlaveDofIndex )( 0, 1 );

            Field_Interpolator* tFILambdaMaster =
                    mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::VX );

            // get slave field interpolator for the residual dof type
            Field_Interpolator* tFILambdaSlave =
                    mSlaveFIManager->get_field_interpolators_for_type( MSI::Dof_Type::VX );

            real h = mCluster->compute_cluster_cell_side_measure( mtk::Primary_Void::PRIMARY, mtk::Master_Slave::MASTER );

            // compute master residual
            mSet->get_residual()( 0 )( { tMasterResStartIndex, tMasterResStopIndex } ) -=
                    aWStar
                    * ( h * tFILambdaMaster->N_trans() * ( tFILambdaMaster->val() - tFILambdaSlave->val() ) );


            // compute slave residual
            mSet->get_residual()( 0 )( { tSlaveResStartIndex, tSlaveResStopIndex } ) +=
                    aWStar
                    * ( h * tFILambdaSlave->N_trans() * ( tFILambdaMaster->val() - tFILambdaSlave->val() ) );


            // check for nan, infinity
            MORIS_ASSERT( isfinite( mSet->get_residual()( 0 ) ),
                    "IWG_Isotropic_Struc_Linear_Interface_SLM_Mixed::compute_residual - Residual contains NAN or INF, exiting!" );
        }

        //------------------------------------------------------------------------------

        void
		IWG_Isotropic_Struc_Linear_Interface_SLM_LMJump::compute_jacobian( real aWStar )
        {
#ifdef DEBUG
            // check master and slave field interpolators
            this->check_field_interpolators( mtk::Master_Slave::MASTER );
            this->check_field_interpolators( mtk::Master_Slave::SLAVE );
#endif

             // get master index for residual dof type, indices for assembly
            const uint tMasterDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 )( 0 ), mtk::Master_Slave::MASTER );
            const uint tMasterResStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
            const uint tMasterResStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

            // get slave index for residual dof type, indices for assembly
            const uint tSlaveDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 )( 0 ), mtk::Master_Slave::SLAVE );
            const uint tSlaveResStartIndex = mSet->get_res_dof_assembly_map()( tSlaveDofIndex )( 0, 0 );
            const uint tSlaveResStopIndex  = mSet->get_res_dof_assembly_map()( tSlaveDofIndex )( 0, 1 );

            Field_Interpolator* tFILambdaMaster =
                    mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::VX );

            // get slave field interpolator for the residual dof type
            Field_Interpolator* tFILambdaSlave =
                    mSlaveFIManager->get_field_interpolators_for_type( MSI::Dof_Type::VX );

            real h = mCluster->compute_cluster_cell_side_measure( mtk::Primary_Void::PRIMARY, mtk::Master_Slave::MASTER );


            // compute the jacobian for indirect dof dependencies through master constitutive models
            uint tMasterNumDofDependencies = mRequestedMasterGlobalDofTypes.size();
            for ( uint iDOF = 0; iDOF < tMasterNumDofDependencies; iDOF++ )
            {
                // get the dof type
                const Cell< MSI::Dof_Type >& tDofType = mRequestedMasterGlobalDofTypes( iDOF );

                // get the index for the dof type
                const sint tDofDepIndex         = mSet->get_dof_index_for_type( tDofType( 0 ), mtk::Master_Slave::MASTER );
                const uint tMasterDepStartIndex = mSet->get_jac_dof_assembly_map()( tMasterDofIndex )( tDofDepIndex, 0 );
                const uint tMasterDepStopIndex  = mSet->get_jac_dof_assembly_map()( tMasterDofIndex )( tDofDepIndex, 1 );

                // extract sub-matrices
                auto tJacMM = mSet->get_jacobian()(
                        { tMasterResStartIndex, tMasterResStopIndex }, { tMasterDepStartIndex, tMasterDepStopIndex } );

                auto tJacSM = mSet->get_jacobian()(
                        { tSlaveResStartIndex, tSlaveResStopIndex }, { tMasterDepStartIndex, tMasterDepStopIndex } );

                // compute jacobian direct dependencies
                if ( tDofType( 0 ) == MSI::Dof_Type::VX )
                {
                    tJacMM -= aWStar
                            * ( h * tFILambdaMaster->N_trans() * tFILambdaMaster->N() );

                    tJacSM += aWStar
                            * ( h * tFILambdaSlave->N_trans() * tFILambdaMaster->N() );
                }
            }

            // compute the jacobian for indirect dof dependencies through slave constitutive models
            uint tSlaveNumDofDependencies = mRequestedSlaveGlobalDofTypes.size();
            for ( uint iDOF = 0; iDOF < tSlaveNumDofDependencies; iDOF++ )
            {
                // get dof type
                const Cell< MSI::Dof_Type >& tDofType = mRequestedSlaveGlobalDofTypes( iDOF );

                // get the index for the dof type
                const sint tDofDepIndex        = mSet->get_dof_index_for_type( tDofType( 0 ), mtk::Master_Slave::SLAVE );
                const uint tSlaveDepStartIndex = mSet->get_jac_dof_assembly_map()( tSlaveDofIndex )( tDofDepIndex, 0 );
                const uint tSlaveDepStopIndex  = mSet->get_jac_dof_assembly_map()( tSlaveDofIndex )( tDofDepIndex, 1 );

                // extract sub-matrices
                auto tJacMS = mSet->get_jacobian()(
                        { tMasterResStartIndex, tMasterResStopIndex }, { tSlaveDepStartIndex, tSlaveDepStopIndex } );

                auto tJacSS = mSet->get_jacobian()(
                        { tSlaveResStartIndex, tSlaveResStopIndex }, { tSlaveDepStartIndex, tSlaveDepStopIndex } );

                // if dof type is residual dof type
                if ( tDofType( 0 ) == MSI::Dof_Type::VX )
                {
                    tJacMS += aWStar
                            * ( h * tFILambdaMaster->N_trans() * tFILambdaSlave->N() );

                    tJacSS -= aWStar
                            * ( h * tFILambdaSlave->N_trans() * tFILambdaSlave->N() );
                }
            }

            // check for nan, infinity
            MORIS_ASSERT( isfinite( mSet->get_jacobian() ),
                    "IWG_Isotropic_Struc_Linear_Interface_SLM_LMJump::compute_jacobian - Jacobian contains NAN or INF, exiting!" );
        }

        //------------------------------------------------------------------------------

        void
		IWG_Isotropic_Struc_Linear_Interface_SLM_LMJump::compute_jacobian_and_residual( real aWStar )
        {
            MORIS_ERROR( false,
                    "IWG_Isotropic_Struc_Linear_Interface_SLM_LMJump::compute_jacobian_and_residual - This function does nothing." );
        }

        //------------------------------------------------------------------------------

        void
		IWG_Isotropic_Struc_Linear_Interface_SLM_LMJump::compute_dRdp( real aWStar )
        {
            MORIS_ERROR( false, "IWG_Isotropic_Struc_Linear_Interface_SLM_Mixed::compute_dRdp - This function does nothing." );
        }

        //------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */
