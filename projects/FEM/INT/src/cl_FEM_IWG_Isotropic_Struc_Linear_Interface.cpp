
#include "cl_FEM_IWG_Isotropic_Struc_Linear_Interface.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_Set.hpp"

#include "fn_trans.hpp"
#include "fn_eye.hpp"
#include "fn_dot.hpp"

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        IWG_Isotropic_Struc_Linear_Interface::IWG_Isotropic_Struc_Linear_Interface()
        {
            // set size for the constitutive model pointer cell
            mMasterCM.resize( static_cast< uint >( IWG_Constitutive_Type::MAX_ENUM ), nullptr );
            mSlaveCM.resize( static_cast< uint >( IWG_Constitutive_Type::MAX_ENUM ), nullptr );

            // populate the constitutive map
            mConstitutiveMap[ "ElastLinIso" ] = IWG_Constitutive_Type::ELAST_LIN_ISO;

            // set size for the stabilization parameter pointer cell
            mStabilizationParam.resize( static_cast< uint >( IWG_Stabilization_Type::MAX_ENUM ), nullptr );

            // populate the stabilization map
            mStabilizationMap[ "NitscheInterface" ] = IWG_Stabilization_Type::NITSCHE_INTERFACE;
        }

        //------------------------------------------------------------------------------

        void IWG_Isotropic_Struc_Linear_Interface::set_constitutive_model(
                std::shared_ptr< Constitutive_Model > aConstitutiveModel,
                std::string                           aConstitutiveString,
                mtk::Master_Slave                     aIsMaster  )
        {
            // check that aConstitutiveString makes sense
            std::string tErrMsg =
                    std::string( "IWG_Isotropic_Struc_Linear_Interface::set_constitutive_model - Unknown aConstitutiveString: " ) +
                    aConstitutiveString;
            MORIS_ERROR( mConstitutiveMap.find( aConstitutiveString ) != mConstitutiveMap.end(), tErrMsg.c_str() );

            // set the constitutive model in the constitutive model cell
            this->get_constitutive_models( aIsMaster )( static_cast< uint >( mConstitutiveMap[ aConstitutiveString ] ) ) = aConstitutiveModel;
        }

        //------------------------------------------------------------------------------

        void IWG_Isotropic_Struc_Linear_Interface::set_stabilization_parameter(
                std::shared_ptr< Stabilization_Parameter > aStabilizationParameter,
                std::string                                aStabilizationString )
        {
            // check that aStabilizationString makes sense
            std::string tErrMsg =
                    std::string( "IWG_Isotropic_Struc_Linear_Interface::set_stabilization_parameter - Unknown aStabilizationString: " ) +
                    aStabilizationString;
            MORIS_ERROR( mStabilizationMap.find( aStabilizationString ) != mStabilizationMap.end(), tErrMsg.c_str() );

            // set the stabilization parameter in the stabilization parameter cell
            this->get_stabilization_parameters()( static_cast< uint >( mStabilizationMap[ aStabilizationString ] ) ) = aStabilizationParameter;
        }

        //------------------------------------------------------------------------------

        void IWG_Isotropic_Struc_Linear_Interface::compute_residual( real aWStar )
        {
#ifdef DEBUG
            // check master and slave field interpolators
            this->check_field_interpolators( mtk::Master_Slave::MASTER );
            this->check_field_interpolators( mtk::Master_Slave::SLAVE );
#endif

            // get master index for residual dof type, indices for assembly
            uint tMasterDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::MASTER );
            uint tMasterResStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
            uint tMasterResStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

            // get slave index for residual dof type, indices for assembly
            uint tSlaveDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::SLAVE );
            uint tSlaveResStartIndex = mSet->get_res_dof_assembly_map()( tSlaveDofIndex )( 0, 0 );
            uint tSlaveResStopIndex  = mSet->get_res_dof_assembly_map()( tSlaveDofIndex )( 0, 1 );

            // get master field interpolator for the residual dof type
            Field_Interpolator * tFIMaster =
                    mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get slave field interpolator for the residual dof type
            Field_Interpolator * tFISlave  =
                    mSlaveFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get the elasticity constitutive model
            std::shared_ptr< Constitutive_Model > tCMMasterElasticity =
                    mMasterCM( static_cast< uint >( IWG_Constitutive_Type::ELAST_LIN_ISO ) );
            std::shared_ptr< Constitutive_Model > tCMSlaveElasticity =
                    mSlaveCM( static_cast< uint >( IWG_Constitutive_Type::ELAST_LIN_ISO ) );

            // get the Nitsche stabilization parameter
            std::shared_ptr< Stabilization_Parameter > tSPNitsche =
                    mStabilizationParam( static_cast< uint >( IWG_Stabilization_Type::NITSCHE_INTERFACE ) );
            real tNitsche      = tSPNitsche->val()( 0 );
            real tMasterWeight = tSPNitsche->val()( 1 );
            real tSlaveWeight  = tSPNitsche->val()( 2 );

            // evaluate average traction
            Matrix< DDRMat > tTraction =
                    tMasterWeight * tCMMasterElasticity->traction( mNormal ) +
                    tSlaveWeight  * tCMSlaveElasticity->traction( mNormal );

            // evaluate temperature jump
            Matrix< DDRMat > tJump = tFIMaster->val() - tFISlave->val();

            // compute master residual
            mSet->get_residual()( 0 )( { tMasterResStartIndex, tMasterResStopIndex }, { 0, 0 } ) += aWStar * (
                    - trans( tFIMaster->N() ) * tTraction
                    + tMasterWeight * tCMMasterElasticity->testTraction( mNormal, mResidualDofType ) * tJump
                    + tNitsche * trans( tFIMaster->N() ) * tJump ) ;

            // compute slave residual
            mSet->get_residual()( 0 )( { tSlaveResStartIndex, tSlaveResStopIndex }, { 0, 0 } ) += aWStar * (
                    trans( tFISlave->N() ) * tTraction
                    + tSlaveWeight * tCMSlaveElasticity->testTraction( mNormal, mResidualDofType ) * tJump
                    - tNitsche * trans( tFISlave->N() ) * tJump );
        }

        //------------------------------------------------------------------------------
        void IWG_Isotropic_Struc_Linear_Interface::compute_jacobian( real aWStar )
        {
#ifdef DEBUG
            // check master and slave field interpolators
            this->check_field_interpolators( mtk::Master_Slave::MASTER );
            this->check_field_interpolators( mtk::Master_Slave::SLAVE );
#endif

            // get master index for residual dof type, indices for assembly
            uint tMasterDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::MASTER );
            uint tMasterResStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
            uint tMasterResStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

            // get slave index for residual dof type, indices for assembly
            uint tSlaveDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::SLAVE );
            uint tSlaveResStartIndex = mSet->get_res_dof_assembly_map()( tSlaveDofIndex )( 0, 0 );
            uint tSlaveResStopIndex  = mSet->get_res_dof_assembly_map()( tSlaveDofIndex )( 0, 1 );

            // get master field interpolator for the residual dof type
            Field_Interpolator * tFIMaster =
                    mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get slave field interpolator for the residual dof type
            Field_Interpolator * tFISlave  =
                    mSlaveFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get the elasticity constitutive model
            std::shared_ptr< Constitutive_Model > tCMMasterElasticity =
                    mMasterCM( static_cast< uint >( IWG_Constitutive_Type::ELAST_LIN_ISO ) );
            std::shared_ptr< Constitutive_Model > tCMSlaveElasticity =
                    mSlaveCM( static_cast< uint >( IWG_Constitutive_Type::ELAST_LIN_ISO ) );

            // get the Nitsche stabilization parameter
            std::shared_ptr< Stabilization_Parameter > tSPNitsche =
                    mStabilizationParam( static_cast< uint >( IWG_Stabilization_Type::NITSCHE_INTERFACE ) );
            real tNitsche      = tSPNitsche->val()( 0 );
            real tMasterWeight = tSPNitsche->val()( 1 );
            real tSlaveWeight  = tSPNitsche->val()( 2 );

            // get number of master dof dependencies
            uint tMasterNumDofDependencies = mRequestedMasterGlobalDofTypes.size();

            // evaluate displacement jump
            Matrix< DDRMat > tJump = tFIMaster->val() - tFISlave->val();

            // compute the jacobian for indirect dof dependencies through master constitutive models
            for( uint iDOF = 0; iDOF < tMasterNumDofDependencies; iDOF++ )
            {
                // get the dof type
                Cell< MSI::Dof_Type > tDofType = mRequestedMasterGlobalDofTypes( iDOF );

                // get the index for the dof type
                sint tDofDepIndex         = mSet->get_dof_index_for_type( tDofType( 0 ), mtk::Master_Slave::MASTER );
                uint tMasterDepStartIndex = mSet->get_jac_dof_assembly_map()( tMasterDofIndex )( tDofDepIndex, 0 );
                uint tMasterDepStopIndex  = mSet->get_jac_dof_assembly_map()( tMasterDofIndex )( tDofDepIndex, 1 );

                // compute jacobian direct dependencies
                if ( tDofType( 0 ) == mResidualDofType( 0 ) )
                {
                    mSet->get_jacobian()(
                            { tMasterResStartIndex, tMasterResStopIndex },
                            { tMasterDepStartIndex, tMasterDepStopIndex } ) += aWStar * (
                                    tMasterWeight * tCMMasterElasticity->testTraction( mNormal, mResidualDofType ) * tFIMaster->N()
                                    + tNitsche * trans( tFIMaster->N() ) * tFIMaster->N() );

                    mSet->get_jacobian()(
                            { tSlaveResStartIndex,  tSlaveResStopIndex },
                            { tMasterDepStartIndex, tMasterDepStopIndex } ) += aWStar * (
                                    tSlaveWeight * tCMSlaveElasticity->testTraction( mNormal, mResidualDofType ) * tFIMaster->N()
                                    - tNitsche * trans( tFISlave->N() ) * tFIMaster->N() );
                }

                // if dependency on the dof type
                if ( tCMMasterElasticity->check_dof_dependency( tDofType ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()(
                            { tMasterResStartIndex, tMasterResStopIndex },
                            { tMasterDepStartIndex, tMasterDepStopIndex } ) += aWStar * (
                                    - trans( tFIMaster->N() ) * tMasterWeight * tCMMasterElasticity->dTractiondDOF( tDofType, mNormal ) );
                    //+ tMasterWeight * tCMMasterElasticity->dTestTractiondDOF( tDofType, mNormal ) * tJump;

                    mSet->get_jacobian()(
                            { tSlaveResStartIndex,  tSlaveResStopIndex },
                            { tMasterDepStartIndex, tMasterDepStopIndex } ) += aWStar * (
                                    trans( tFISlave->N() ) * tMasterWeight * tCMMasterElasticity->dTractiondDOF( tDofType, mNormal ) );
                }

                // if dependency of stabilization parameters on the dof type
                if ( tSPNitsche->check_dof_dependency( tDofType, mtk::Master_Slave::MASTER ) )
                {
                    // get the derivatives of the SPs
                    Matrix< DDRMat > tNitscheDer      = tSPNitsche->dSPdMasterDOF( tDofType ).get_row( 0 );
                    Matrix< DDRMat > tMasterWeightDer = tSPNitsche->dSPdMasterDOF( tDofType ).get_row( 1 );
                    Matrix< DDRMat > tSlaveWeightDer  = tSPNitsche->dSPdMasterDOF( tDofType ).get_row( 2 );

                    // add contribution to jacobian
                    mSet->get_jacobian()(
                            { tMasterResStartIndex, tMasterResStopIndex },
                            { tMasterDepStartIndex, tMasterDepStopIndex } ) += aWStar * (
                                    trans( tFIMaster->N() ) * tJump * tNitscheDer
                                    - trans( tFIMaster->N() ) * tCMMasterElasticity->traction( mNormal ) * tMasterWeightDer
                                    + tCMMasterElasticity->testTraction( mNormal, mResidualDofType ) * tJump * tMasterWeightDer
                                    - trans( tFIMaster->N() ) * tCMSlaveElasticity->traction( mNormal ) * tSlaveWeightDer );

                    mSet->get_jacobian()(
                            { tSlaveResStartIndex,  tSlaveResStopIndex },
                            { tMasterDepStartIndex, tMasterDepStopIndex } ) += aWStar * (
                                    - trans( tFISlave->N() ) * tJump * tNitscheDer
                                    + trans( tFISlave->N() ) * tCMMasterElasticity->traction( mNormal ) * tMasterWeightDer
                                    + trans( tFISlave->N() ) * tCMSlaveElasticity->traction( mNormal ) * tSlaveWeightDer
                                    + tCMSlaveElasticity->testTraction( mNormal, mResidualDofType ) * tJump * tSlaveWeightDer );
                }
            }

            // compute the jacobian for indirect dof dependencies through slave constitutive models
            uint tSlaveNumDofDependencies = mRequestedSlaveGlobalDofTypes.size();
            for( uint iDOF = 0; iDOF < tSlaveNumDofDependencies; iDOF++ )
            {
                // get dof type
                Cell< MSI::Dof_Type > tDofType = mRequestedSlaveGlobalDofTypes( iDOF );

                // get the index for the dof type
                sint tDofDepIndex        = mSet->get_dof_index_for_type( tDofType( 0 ), mtk::Master_Slave::SLAVE );
                uint tSlaveDepStartIndex = mSet->get_jac_dof_assembly_map()( tSlaveDofIndex )( tDofDepIndex, 0 );
                uint tSlaveDepStopIndex  = mSet->get_jac_dof_assembly_map()( tSlaveDofIndex )( tDofDepIndex, 1 );

                // if dof type is residual dof type
                if( tDofType( 0 ) == mResidualDofType( 0 ) )
                {
                    mSet->get_jacobian()(
                            { tMasterResStartIndex, tMasterResStopIndex },
                            { tSlaveDepStartIndex,  tSlaveDepStopIndex  } ) += aWStar * (
                                    - tMasterWeight * tCMMasterElasticity->testTraction( mNormal, mResidualDofType ) * tFISlave->N()
                                    - tNitsche * trans( tFIMaster->N() ) * tFISlave->N() );

                    mSet->get_jacobian()(
                            { tSlaveResStartIndex, tSlaveResStopIndex },
                            { tSlaveDepStartIndex, tSlaveDepStopIndex } ) += aWStar * (
                                    - tSlaveWeight * tCMSlaveElasticity->testTraction( mNormal, mResidualDofType ) * tFISlave->N()
                                    + tNitsche * trans( tFISlave->N() ) * tFISlave->N() );
                }

                // if dependency on the dof type
                if ( tCMSlaveElasticity->check_dof_dependency( tDofType ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()(
                            { tMasterResStartIndex, tMasterResStopIndex },
                            { tSlaveDepStartIndex,  tSlaveDepStopIndex  } ) += aWStar * (
                                    - trans( tFIMaster->N() ) * tSlaveWeight * tCMSlaveElasticity->dTractiondDOF( tDofType, mNormal ) );

                    mSet->get_jacobian()(
                            { tSlaveResStartIndex, tSlaveResStopIndex },
                            { tSlaveDepStartIndex, tSlaveDepStopIndex } ) += aWStar * (
                                    + trans( tFISlave->N() ) * tSlaveWeight * tCMSlaveElasticity->dTractiondDOF( tDofType, mNormal ) );
                }

                // if dependency of stabilization parameters on the dof type
                if ( tSPNitsche->check_dof_dependency( tDofType, mtk::Master_Slave::SLAVE ) )
                {
                    // get the derivatives of the SPs
                    Matrix< DDRMat > tNitscheDer      = tSPNitsche->dSPdSlaveDOF( tDofType ).get_row( 0 );
                    Matrix< DDRMat > tMasterWeightDer = tSPNitsche->dSPdSlaveDOF( tDofType ).get_row( 1 );
                    Matrix< DDRMat > tSlaveWeightDer  = tSPNitsche->dSPdSlaveDOF( tDofType ).get_row( 2 );

                    // add contribution to jacobian
                    mSet->get_jacobian()(
                            { tMasterResStartIndex, tMasterResStopIndex },
                            { tSlaveDepStartIndex,  tSlaveDepStopIndex  } ) += aWStar * (
                                    + trans( tFIMaster->N() ) * tJump * tNitscheDer
                                    - trans( tFIMaster->N() ) * tCMMasterElasticity->traction( mNormal ) * tMasterWeightDer
                                    + tCMMasterElasticity->testTraction( mNormal, mResidualDofType ) * tJump * tMasterWeightDer
                                    - trans( tFIMaster->N() ) * tCMSlaveElasticity->traction( mNormal ) * tSlaveWeightDer );

                    mSet->get_jacobian()(
                            { tSlaveResStartIndex, tSlaveResStopIndex },
                            { tSlaveDepStartIndex, tSlaveDepStopIndex } ) += aWStar * (
                                    - trans( tFISlave->N() ) * tJump * tNitscheDer
                                    + trans( tFISlave->N() ) * tCMMasterElasticity->traction( mNormal ) * tMasterWeightDer
                                    + trans( tFISlave->N() ) * tCMSlaveElasticity->traction( mNormal ) * tSlaveWeightDer
                                    + tCMSlaveElasticity->testTraction( mNormal, mResidualDofType ) * tJump * tSlaveWeightDer );
                }
            }
        }

        //------------------------------------------------------------------------------

        void IWG_Isotropic_Struc_Linear_Interface::compute_jacobian_and_residual( real aWStar )
        {
            MORIS_ERROR( false, "IWG_Isotropic_Struc_Linear_Interface::compute_jacobian_and_residual - This function does nothing.");
        }

        //------------------------------------------------------------------------------

        void IWG_Isotropic_Struc_Linear_Interface::compute_dRdp( real aWStar )
        {
            MORIS_ERROR( false, "IWG_Isotropic_Struc_Linear_Interface::compute_dRdp - This function does nothing.");
        }

        //------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */
