
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
            mStabilizationMap[ "NitscheInterface" ]      = IWG_Stabilization_Type::NITSCHE_INTERFACE;
            mStabilizationMap[ "MasterWeightInterface" ] = IWG_Stabilization_Type::MASTER_WEIGHT_INTERFACE;
            mStabilizationMap[ "SlaveWeightInterface" ]  = IWG_Stabilization_Type::SLAVE_WEIGHT_INTERFACE;
        }

//------------------------------------------------------------------------------
        void IWG_Isotropic_Struc_Linear_Interface::compute_residual( real tWStar )
        {
#ifdef DEBUG
            // check master and slave field interpolators
            this->check_field_interpolators( mtk::Master_Slave::MASTER );
            this->check_field_interpolators( mtk::Master_Slave::SLAVE );
#endif

            // get master index for residual dof type
            uint tDofIndexMaster = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::MASTER );

            // get slave index for residual dof type
            uint tDofIndexSlave  = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::SLAVE );

            // get master field interpolator for the residual dof type
            Field_Interpolator * tFIMaster = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get slave field interpolator for the residual dof type
            Field_Interpolator * tFISlave  = mSlaveFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get indices for SP, CM and properties
            uint tElastLinIsoIndex  = static_cast< uint >( IWG_Constitutive_Type::ELAST_LIN_ISO );
            uint tNitscheIndex      = static_cast< uint >( IWG_Stabilization_Type::NITSCHE_INTERFACE );
            uint tMasterWeightIndex = static_cast< uint >( IWG_Stabilization_Type::MASTER_WEIGHT_INTERFACE );
            uint tSlaveWeightIndex  = static_cast< uint >( IWG_Stabilization_Type::SLAVE_WEIGHT_INTERFACE );

            // evaluate average traction
            Matrix< DDRMat > tTraction = mStabilizationParam( tMasterWeightIndex )->val()( 0 ) * mMasterCM( tElastLinIsoIndex )->traction( mNormal )
                                       + mStabilizationParam( tSlaveWeightIndex )->val()( 0 ) * mSlaveCM( tElastLinIsoIndex )->traction( mNormal );

            // evaluate temperature jump
            Matrix< DDRMat > tJump = tFIMaster->val() - tFISlave->val();

            // compute master residual
            mSet->get_residual()( { mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 1 ) }, { 0, 0 } )
            += ( - trans( tFIMaster->N() ) * tTraction
                 + mStabilizationParam( tMasterWeightIndex )->val()( 0 ) * mMasterCM( tElastLinIsoIndex )->testTraction( mNormal ) * tJump
                 + mStabilizationParam( tNitscheIndex )->val()( 0 ) * trans( tFIMaster->N() ) * tJump ) * tWStar;

            // compute slave residual
            mSet->get_residual()( { mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 1 ) }, { 0, 0 } )
            +=  (   trans( tFISlave->N() ) * tTraction
                  + mStabilizationParam( tSlaveWeightIndex )->val()( 0 ) * mSlaveCM( tElastLinIsoIndex )->testTraction( mNormal ) * tJump
                  - mStabilizationParam( tNitscheIndex )->val()( 0 ) * trans( tFISlave->N() ) * tJump ) * tWStar;
        }

//------------------------------------------------------------------------------
        void IWG_Isotropic_Struc_Linear_Interface::compute_jacobian( real tWStar )
        {
#ifdef DEBUG
            // check master and slave field interpolators
            this->check_field_interpolators( mtk::Master_Slave::MASTER );
            this->check_field_interpolators( mtk::Master_Slave::SLAVE );
#endif

            // get master index for the residual dof type
            uint tDofIndexMaster = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::MASTER );

            // get slave index for the residual dof type
            uint tDofIndexSlave  = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::SLAVE );

            // get master field interpolator for the residual dof type
            Field_Interpolator * tFIMaster = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get slave field interpolator for the residual dof type
            Field_Interpolator * tFISlave  = mSlaveFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get indices for SP, CM and properties
            uint tElastLinIsoIndex  = static_cast< uint >( IWG_Constitutive_Type::ELAST_LIN_ISO );
            uint tNitscheIndex      = static_cast< uint >( IWG_Stabilization_Type::NITSCHE_INTERFACE );
            uint tMasterWeightIndex = static_cast< uint >( IWG_Stabilization_Type::MASTER_WEIGHT_INTERFACE );
            uint tSlaveWeightIndex  = static_cast< uint >( IWG_Stabilization_Type::SLAVE_WEIGHT_INTERFACE );

            // get number of master dof dependencies
            uint tMasterNumDofDependencies = mRequestedMasterGlobalDofTypes.size();

            // evaluate displacement jump
            Matrix< DDRMat > tJump = tFIMaster->val() - tFISlave->val();

            // compute the jacobian for direct dof dependencies
            if ( mResidualDofTypeRequested )
            {
                mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 1 ) },
                                      { mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tDofIndexMaster, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tDofIndexMaster, 1 ) } )
                        += (  mStabilizationParam( tMasterWeightIndex )->val()( 0 ) * mMasterCM( tElastLinIsoIndex )->testTraction( mNormal ) * tFIMaster->N()
                            + mStabilizationParam( tNitscheIndex )->val()( 0 ) * trans( tFIMaster->N() ) * tFIMaster->N() ) * tWStar;

                mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 1 ) },
                                      { mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tDofIndexSlave, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tDofIndexSlave, 1 ) } )
                        += ( - mStabilizationParam( tMasterWeightIndex )->val()( 0 ) * mMasterCM( tElastLinIsoIndex )->testTraction( mNormal ) * tFISlave->N()
                             - mStabilizationParam( tNitscheIndex )->val()( 0 ) * trans( tFIMaster->N() ) * tFISlave->N() ) * tWStar;

                mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 1 ) },
                                      { mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tDofIndexMaster, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tDofIndexMaster, 1 ) } )
                        += (  mStabilizationParam( tSlaveWeightIndex )->val()( 0 ) * mSlaveCM( tElastLinIsoIndex )->testTraction( mNormal ) * tFIMaster->N()
                            - mStabilizationParam( tNitscheIndex )->val()( 0 ) * trans( tFISlave->N() ) * tFIMaster->N() ) * tWStar;

                mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 1 ) },
                                      { mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tDofIndexSlave, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tDofIndexSlave, 1 ) } )
                        += ( - mStabilizationParam( tSlaveWeightIndex )->val()( 0 ) * mSlaveCM( tElastLinIsoIndex )->testTraction( mNormal ) * tFISlave->N()
                             + mStabilizationParam( tNitscheIndex )->val()( 0 ) * trans( tFISlave->N() ) * tFISlave->N() ) * tWStar;
            }

            // compute the jacobian for indirect dof dependencies through master constitutive models
            for( uint iDOF = 0; iDOF < tMasterNumDofDependencies; iDOF++ )
            {
                // get the dof type
                Cell< MSI::Dof_Type > tDofType = mRequestedMasterGlobalDofTypes( iDOF );

                // get index for the dof type
                sint tIndexDep = mSet->get_dof_index_for_type( tDofType( 0 ), mtk::Master_Slave::MASTER );

                // if dependency on the dof type
                if ( mMasterCM( tElastLinIsoIndex )->check_dof_dependency( tDofType ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 1 ) } )
                    += ( - trans( tFIMaster->N() ) * mStabilizationParam( tMasterWeightIndex )->val()( 0 ) * mMasterCM( tElastLinIsoIndex )->dTractiondDOF( tDofType, mNormal ) ) * tWStar;
                       //+ mStabilizationParam( tMasterWeightIndex )->val()( 0 ) * mMasterCM( tElastLinIsoIndex )->dTestTractiondDOF( tDofType, mNormal ) * tJump;

                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 1 ) } )
                    += trans( tFISlave->N() ) * mStabilizationParam( tMasterWeightIndex )->val()( 0 ) * mMasterCM( tElastLinIsoIndex )->dTractiondDOF( tDofType, mNormal ) * tWStar;
                }

                // if dependency of stabilization parameters on the dof type
                if ( mStabilizationParam( tNitscheIndex )->check_dof_dependency( tDofType, mtk::Master_Slave::MASTER ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 1 ) } )
                    += trans( tFIMaster->N() ) * tJump * mStabilizationParam( tNitscheIndex )->dSPdMasterDOF( tDofType ) * tWStar;

                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 1 ) } )
                    += - trans( tFISlave->N() ) * tJump * mStabilizationParam( tNitscheIndex )->dSPdMasterDOF( tDofType ) * tWStar;
                }

                if ( mStabilizationParam( tMasterWeightIndex )->check_dof_dependency( tDofType, mtk::Master_Slave::MASTER ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 1 ) } )
                    += ( - trans( tFIMaster->N() ) * mMasterCM( tElastLinIsoIndex )->traction( mNormal ) * mStabilizationParam( tMasterWeightIndex )->dSPdMasterDOF( tDofType )
                         + mMasterCM( tElastLinIsoIndex )->testTraction( mNormal ) * tJump * mStabilizationParam( tMasterWeightIndex )->dSPdMasterDOF( tDofType ) ) * tWStar;

                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 1 ) } )
                    += trans( tFISlave->N() ) * mMasterCM( tElastLinIsoIndex )->traction( mNormal ) * mStabilizationParam( tMasterWeightIndex )->dSPdMasterDOF( tDofType ) * tWStar;
                }

                if ( mStabilizationParam( tSlaveWeightIndex )->check_dof_dependency( tDofType, mtk::Master_Slave::MASTER ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 1 ) } )
                    += - trans( tFIMaster->N() ) * mSlaveCM( tElastLinIsoIndex )->traction( mNormal ) * mStabilizationParam( tSlaveWeightIndex )->dSPdMasterDOF( tDofType ) * tWStar;

                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 1 ) } )
                    += (   trans( tFISlave->N() ) * mSlaveCM( tElastLinIsoIndex )->traction( mNormal ) * mStabilizationParam( tSlaveWeightIndex )->dSPdMasterDOF( tDofType )
                         + mSlaveCM( tElastLinIsoIndex )->testTraction( mNormal ) * tJump * mStabilizationParam( tSlaveWeightIndex )->dSPdMasterDOF( tDofType ) ) * tWStar;
                }
            }

            // compute the jacobian for indirect dof dependencies through slave constitutive models
            uint tSlaveNumDofDependencies = mRequestedSlaveGlobalDofTypes.size();
            for( uint iDOF = 0; iDOF < tSlaveNumDofDependencies; iDOF++ )
            {
                // get dof type
                Cell< MSI::Dof_Type > tDofType = mRequestedSlaveGlobalDofTypes( iDOF );

                // get index for dof type
                sint tIndexDep = mSet->get_dof_index_for_type( tDofType( 0 ), mtk::Master_Slave::SLAVE );

                // if dependency on the dof type
                if ( mSlaveCM( tElastLinIsoIndex )->check_dof_dependency( tDofType ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 1 ) } )
                    += - trans( tFIMaster->N() ) * mStabilizationParam( tSlaveWeightIndex )->val()( 0 ) * mSlaveCM( tElastLinIsoIndex )->dTractiondDOF( tDofType, mNormal ) * tWStar;

                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 1 ) } )
                    +=   trans( tFISlave->N() ) * mStabilizationParam( tSlaveWeightIndex )->val()( 0 ) * mSlaveCM( tElastLinIsoIndex )->dTractiondDOF( tDofType, mNormal ) * tWStar;
                       //+ mStabilizationParam( tSlaveWeightIndex )->val()( 0 ) * mSlaveCM( tElastLinIsoIndex )->dTestTractiondDOF( tDofType, mNormal ) * tJump;
                }

                // if dependency of stabilization parameters on the dof type
                if ( mStabilizationParam( tNitscheIndex )->check_dof_dependency( tDofType, mtk::Master_Slave::SLAVE ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 1 ) } )
                    += trans( tFIMaster->N() ) * tJump * mStabilizationParam( tNitscheIndex )->dSPdSlaveDOF( tDofType ) * tWStar;

                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 1 ) } )
                    += - trans( tFISlave->N() ) * tJump * mStabilizationParam( tNitscheIndex )->dSPdSlaveDOF( tDofType ) * tWStar;
                }

                if ( mStabilizationParam( tMasterWeightIndex )->check_dof_dependency( tDofType, mtk::Master_Slave::SLAVE ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 1 ) } )
                    += ( - trans( tFIMaster->N() ) * mMasterCM( tElastLinIsoIndex )->traction( mNormal ) * mStabilizationParam( tMasterWeightIndex )->dSPdSlaveDOF( tDofType )
                         + mMasterCM( tElastLinIsoIndex )->testTraction( mNormal ) * tJump * mStabilizationParam( tMasterWeightIndex )->dSPdSlaveDOF( tDofType ) ) * tWStar;

                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 1 ) } )
                    += trans( tFISlave->N() ) * mMasterCM( tElastLinIsoIndex )->traction( mNormal ) * mStabilizationParam( tMasterWeightIndex )->dSPdSlaveDOF( tDofType ) * tWStar;
                }

                if ( mStabilizationParam( tSlaveWeightIndex )->check_dof_dependency( tDofType, mtk::Master_Slave::SLAVE ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexMaster )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexMaster )( tIndexDep, 1 ) } )
                    += - trans( tFIMaster->N() ) * mSlaveCM( tElastLinIsoIndex )->traction( mNormal ) * mStabilizationParam( tSlaveWeightIndex )->dSPdSlaveDOF( tDofType ) * tWStar;

                    mSet->get_jacobian()( { mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 0 ), mSet->get_res_dof_assembly_map()( tDofIndexSlave )( 0, 1 ) },
                                          { mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 0 ), mSet->get_jac_dof_assembly_map()( tDofIndexSlave )( tIndexDep, 1 ) } )
                    += (   trans( tFISlave->N() ) * mSlaveCM( tElastLinIsoIndex )->traction( mNormal ) * mStabilizationParam( tSlaveWeightIndex )->dSPdSlaveDOF( tDofType )
                         + mSlaveCM( tElastLinIsoIndex )->testTraction( mNormal ) * tJump * mStabilizationParam( tSlaveWeightIndex )->dSPdSlaveDOF( tDofType ) ) * tWStar;
                }
            }
        }

//------------------------------------------------------------------------------
        void IWG_Isotropic_Struc_Linear_Interface::compute_jacobian_and_residual( moris::Cell< moris::Cell< Matrix< DDRMat > > > & aJacobians,
                                                                                  moris::Cell< Matrix< DDRMat > >                & aResidual )
        {
            MORIS_ERROR( false, "IWG_Isotropic_Struc_Linear_Interface::compute_jacobian_and_residual - This function does nothing.");
        }

//------------------------------------------------------------------------------
        void IWG_Isotropic_Struc_Linear_Interface::compute_drdpdv( real aWStar )
        {
            MORIS_ERROR( false, "IWG_Isotropic_Struc_Linear_Interface::compute_drdpdv - This function does nothing.");
        }

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */