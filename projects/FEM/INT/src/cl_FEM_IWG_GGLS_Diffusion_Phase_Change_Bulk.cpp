//FEM/INT/src
#include "cl_FEM_IWG_GGLS_Diffusion_Phase_Change_Bulk.hpp"
#include "cl_FEM_Set.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"
//LINALG/src
#include "fn_trans.hpp"

namespace moris
{
    namespace fem
    {

//------------------------------------------------------------------------------
        IWG_GGLS_Diffusion_Phase_Change_Bulk::IWG_Diffusion_Bulk()
        {
            // set size for the property pointer cell
            mMasterProp.resize( static_cast< uint >( IWG_Property_Type::MAX_ENUM ), nullptr );

            // populate the property map
            mPropertyMap[ "Load" ] = IWG_Property_Type::BODY_LOAD;

            // set size for the constitutive model pointer cell
            mMasterCM.resize( static_cast< uint >( IWG_Constitutive_Type::MAX_ENUM ), nullptr );

            // populate the constitutive map
            mConstitutiveMap[ "Diffusion_Phase_Change" ] = IWG_Constitutive_Type::DIFFUSION_PHASE_CHANGE;

            // set size for the stabilization parameter pointer cell
            mStabilizationParam.resize( static_cast< uint >( IWG_Stabilization_Type::MAX_ENUM ), nullptr );

            // populate the stabilization map
            mStabilizationMap[ "DirichletNitsche" ] = IWG_Stabilization_Type::DIRICHLET_NITSCHE;
        }

//------------------------------------------------------------------------------
        void IWG_GGLS_Diffusion_Phase_Change_Bulk::compute_residual( real aWStar )
        {
            // check master field interpolators
#ifdef DEBUG
            this->check_field_interpolators();
#endif

            // get master index for residual dof type, indices for assembly
            uint tMasterDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::MASTER );
            uint tMasterResStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
            uint tMasterResStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

            // get residual dof type field interpolator (here temperature)
            Field_Interpolator * tFITemp = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );



            // get body load property
            std::shared_ptr< Property > tPropLoad
            = mMasterProp( static_cast< uint >( IWG_Property_Type::BODY_LOAD ) );

            // get the Phase Change CM
            std::shared_ptr< Constitutive_Model > tCMDiffusionPhaseChange
            = mMasterCM( static_cast< uint >( IWG_Constitutive_Type::DIFFUSION_PHASE_CHANGE ) );

            // get the Stabilization Parameter
            std::shared_ptr< Stabilization_Parameter > tGGLSParam
            = mStabilizationParam( static_cast< uint >( IWG_Stabilization_Type::GGLS_DIFFUSION ) );



            // compute the residual from bulk diffusion term
            mSet->get_residual()( 0 )( { tMasterResStartIndex, tMasterResStopIndex }, { 0, 0 } )
            += aWStar * ( trans( tCMDiffusionPhaseChange->testStrain() ) * tGGLSParam *
                          ( tCMDiffusionPhaseChange->gradHdot() - tCMDiffusionPhaseChange->graddivflux() ) );

            // if body load
            if ( tPropLoad != nullptr )
            {
                // compute contribution of body load to residual
                mSet->get_residual()( 0 )( { tMasterResStartIndex, tMasterResStopIndex }, { 0, 0 } )
                -= aWStar * ( trans( tCMDiffusionPhaseChange->testStrain() ) * tGGLSParam * tPropLoad->val()( 0 ) );
            }

        }

//------------------------------------------------------------------------------
        void IWG_GGLS_Diffusion_Phase_Change_Bulk::compute_jacobian( real aWStar )
        {
#ifdef DEBUG
            // check master field interpolators
            this->check_field_interpolators();
#endif

            // get master index for residual dof type, indices for assembly
            uint tMasterDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::MASTER );
            uint tMasterResStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
            uint tMasterResStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

            // get field interpolator for a given dof type
            Field_Interpolator * tFITemp = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );


            // get body load property
            std::shared_ptr< Property > tPropLoad
            = mMasterProp( static_cast< uint >( IWG_Property_Type::BODY_LOAD ) );

            // get the Phase Change CM
            std::shared_ptr< Constitutive_Model > tCMDiffusionPhaseChange
            = mMasterCM( static_cast< uint >( IWG_Constitutive_Type::DIFFUSION_PHASE_CHANGE ) );

            // get the Stabilization Parameter
            std::shared_ptr< Stabilization_Parameter > tGGLSParam
            = mStabilizationParam( static_cast< uint >( IWG_Stabilization_Type::GGLS_DIFFUSION ) );



            // get the number of master dof type dependencies
            uint tNumDofDependencies = mRequestedMasterGlobalDofTypes.size();

            // loop over master dof type dependencies
            for( uint iDOF = 0; iDOF < tNumDofDependencies; iDOF++ )
            {
                // get the treated dof type
                Cell< MSI::Dof_Type > tDofType = mRequestedMasterGlobalDofTypes( iDOF );

                // get the index for dof type, indices for assembly
                sint tDofDepIndex         = mSet->get_dof_index_for_type( tDofType( 0 ), mtk::Master_Slave::MASTER );
                uint tMasterDepStartIndex = mSet->get_jac_dof_assembly_map()( tMasterDofIndex )( tDofDepIndex, 0 );
                uint tMasterDepStopIndex  = mSet->get_jac_dof_assembly_map()( tMasterDofIndex )( tDofDepIndex, 1 );

                // if constitutive model has dependency on the dof type
                if ( tCMDiffusionPhaseChange->check_dof_dependency( tDofType ) )
                {
                    // if body load
                    if ( tPropLoad != nullptr )
                    {
                        // if body load property has dependency on the dof type
                        if ( tPropLoad->check_dof_dependency( tDofType ) )
                        {
                            // compute contribution of body load to jacobian
                            mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex },
                                                  { tMasterDepStartIndex, tMasterDepStopIndex } )
                            -= aWStar * ( trans( tCMDiffusionPhaseChange->testStrain() ) * tGGLSParam * tPropLoad->dPropdDOF( tDofType ) );
                        }
                    }

                    // compute the jacobian
                    mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex }, { tMasterDepStartIndex, tMasterDepStopIndex } )
                    +=   aWStar * ( trans( tCMDiffusionPhaseChange->testStrain() ) * tGGLSParam *
                                   ( tCMDiffusionPhaseChange->dGradHdotdDOF + tCMDiffusionPhaseChange->dGradDivFluxdDOF ) );
                }
            }

        }

//------------------------------------------------------------------------------
        void IWG_GGLS_Diffusion_Phase_Change_Bulk::compute_jacobian_and_residual( real aWStar )
        {
            MORIS_ERROR( false, "IWG_GGLS_Diffusion_Phase_Change_Bulk::compute_jacobian_and_residual - Not implemented." );
        }

//------------------------------------------------------------------------------
        void IWG_GGLS_Diffusion_Phase_Change_Bulk::compute_dRdp( real aWStar )
        {
#ifdef DEBUG
            // check master field interpolators, properties and constitutive models
            this->check_field_interpolators();
#endif

            MORIS_ERROR( false, "IWG_GGLS_Diffusion_Phase_Change_Bulk::compute_dRdp - Not implemented." );

        }

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */
