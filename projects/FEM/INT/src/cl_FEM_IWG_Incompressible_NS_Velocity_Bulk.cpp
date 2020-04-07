
#include "cl_FEM_IWG_Incompressible_NS_Velocity_Bulk.hpp"
#include "cl_FEM_Set.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"

#include "fn_trans.hpp"
#include "fn_norm.hpp"
#include "fn_eye.hpp"

namespace moris
{
    namespace fem
    {

//------------------------------------------------------------------------------
        IWG_Incompressible_NS_Velocity_Bulk::IWG_Incompressible_NS_Velocity_Bulk()
        {
            // set size for the property pointer cell
            mMasterProp.resize( static_cast< uint >( IWG_Property_Type::MAX_ENUM ), nullptr );

            // populate the property map
            mPropertyMap[ "Density" ] = IWG_Property_Type::DENSITY;
            mPropertyMap[ "Gravity" ] = IWG_Property_Type::GRAVITY;

            // set size for the constitutive model pointer cell
            mMasterCM.resize( static_cast< uint >( IWG_Constitutive_Type::MAX_ENUM ), nullptr );

            // populate the constitutive map
            mConstitutiveMap[ "IncompressibleFluid" ] = IWG_Constitutive_Type::INCOMPRESSIBLE_FLUID;

            // set size for the stabilization parameter pointer cell
            mStabilizationParam.resize( static_cast< uint >( IWG_Stabilization_Type::MAX_ENUM ), nullptr );

            // populate the stabilization map
            mStabilizationMap[ "IncompressibleFlow" ] = IWG_Stabilization_Type::INCOMPRESSIBLE_FLOW;
        }

//------------------------------------------------------------------------------
        void IWG_Incompressible_NS_Velocity_Bulk::compute_residual( real aWStar )
        {
            // check master field interpolators
#ifdef DEBUG
            this->check_field_interpolators();
#endif

            // get master index for residual dof type (here velocity), indices for assembly
            uint tMasterDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::MASTER );
            uint tMasterResStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
            uint tMasterResStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

            // get the velocity FI
            Field_Interpolator * tVelocityFI = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get the density and gravity properties
            std::shared_ptr< Property > tDensityProp = mMasterProp( static_cast< uint >( IWG_Property_Type::DENSITY ) );
            std::shared_ptr< Property > tGravityProp = mMasterProp( static_cast< uint >( IWG_Property_Type::GRAVITY ) );

            // get the incompressible fluid constitutive model
            std::shared_ptr< Constitutive_Model > tIncFluidCM
            = mMasterCM( static_cast< uint >( IWG_Constitutive_Type::INCOMPRESSIBLE_FLUID ) );

            // get the incompressible flow stabilization parameter
            std::shared_ptr< Stabilization_Parameter > tIncFlowSP
            = mStabilizationParam( static_cast< uint >( IWG_Stabilization_Type::INCOMPRESSIBLE_FLOW ) );

            // compute the residual strong form
            Matrix< DDRMat > tRM;
            real tRC;
            this->compute_residual_strong_form( tRM, tRC );

            // get the density value
            real tDensity = tDensityProp->val()( 0 );

            // compute uj vij
            Matrix< DDRMat > tujvij;
            this->compute_ujvij( tujvij );

            // build multiplication matrix for sigma_ij epsilon_ij
            Matrix< DDRMat > tPre;
            if( tVelocityFI->get_number_of_fields() == 2 )
            {
                tPre.set_size( 3, 3, 0.0 );
                tPre( 0, 0 ) = 1.0;
                tPre( 1, 1 ) = 1.0;
                tPre( 2, 2 ) = 2.0;
            }
            else
            {
                tPre.set_size( 6, 6, 0.0 );
                tPre( 0, 0 ) = 1.0;
                tPre( 1, 1 ) = 1.0;
                tPre( 2, 2 ) = 1.0;
                tPre( 3, 3 ) = 2.0;
                tPre( 4, 4 ) = 2.0;
                tPre( 5, 5 ) = 2.0;
            }

            // compute the residual weak form
            mSet->get_residual()( 0 )( { tMasterResStartIndex, tMasterResStopIndex }, { 0, 0 } )
            += aWStar * (   trans( tVelocityFI->N() ) * tDensity * trans( tVelocityFI->gradt( 1 ) )
                          + trans( tVelocityFI->N() ) * tDensity * trans( tVelocityFI->gradx( 1 ) ) * tVelocityFI->val()
                          + trans( tIncFluidCM->testStrain() ) * tPre * tIncFluidCM->flux()
                          + trans( tujvij ) * tDensity * tIncFlowSP->val()( 0 ) * tRM
                          + trans( tVelocityFI->div_operator() ) * tIncFlowSP->val()( 1 ) * tRC );

            // if gravity
            if ( tGravityProp != nullptr )
            {
                // add gravity to residual weak form
                mSet->get_residual()( 0 )( { tMasterResStartIndex, tMasterResStopIndex }, { 0, 0 } )
                -= aWStar * ( trans( tVelocityFI->N() ) * tDensity * tGravityProp->val() );
            }
        }

//------------------------------------------------------------------------------
        void IWG_Incompressible_NS_Velocity_Bulk::compute_jacobian( real aWStar )
        {
#ifdef DEBUG
            // check master field interpolators
            this->check_field_interpolators();
#endif

            // get master index for residual dof type (here velocity), indices for assembly
            uint tMasterDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::MASTER );
            uint tMasterResStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
            uint tMasterResStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

            // get velocity FI
            Field_Interpolator * tVelocityFI = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get the density and gravity properties
            std::shared_ptr< Property > tDensityProp = mMasterProp( static_cast< uint >( IWG_Property_Type::DENSITY ) );
            std::shared_ptr< Property > tGravityProp = mMasterProp( static_cast< uint >( IWG_Property_Type::GRAVITY ) );

            // evaluate the density
            real tDensity = tDensityProp->val()( 0 );

            // get the incompressible fluid constitutive model
            std::shared_ptr< Constitutive_Model > tIncFluidCM
            = mMasterCM( static_cast< uint >( IWG_Constitutive_Type::INCOMPRESSIBLE_FLUID ) );

            // get the incompressible flow stabilization parameter
            std::shared_ptr< Stabilization_Parameter > tIncFlowSP
            = mStabilizationParam( static_cast< uint >( IWG_Stabilization_Type::INCOMPRESSIBLE_FLOW ) );

            // build multiplication matrix for sigma_ij epsilon_ij
            Matrix< DDRMat > tPre;
            if( tVelocityFI->get_number_of_fields() == 2 )
            {
                tPre.set_size( 3, 3, 0.0 );
                tPre( 0, 0 ) = 1.0;
                tPre( 1, 1 ) = 1.0;
                tPre( 2, 2 ) = 2.0;
            }
            else
            {
                tPre.set_size( 6, 6, 0.0 );
                tPre( 0, 0 ) = 1.0;
                tPre( 1, 1 ) = 1.0;
                tPre( 2, 2 ) = 1.0;
                tPre( 3, 3 ) = 2.0;
                tPre( 4, 4 ) = 2.0;
                tPre( 5, 5 ) = 2.0;
            }

            // compute the residual strong form
            Matrix< DDRMat > tRM;
            real tRC;
            this->compute_residual_strong_form( tRM, tRC );

            // compute the jacobian for dof dependencies
            uint tNumDofDependencies = mRequestedMasterGlobalDofTypes.size();
            for( uint iDOF = 0; iDOF < tNumDofDependencies; iDOF++ )
            {
                // get the treated dof type
                Cell< MSI::Dof_Type > tDofType = mRequestedMasterGlobalDofTypes( iDOF );

                // get the index for dof type, indices for assembly
                sint tDofDepIndex         = mSet->get_dof_index_for_type( tDofType( 0 ), mtk::Master_Slave::MASTER );
                uint tMasterDepStartIndex = mSet->get_jac_dof_assembly_map()( tMasterDofIndex )( tDofDepIndex, 0 );
                uint tMasterDepStopIndex  = mSet->get_jac_dof_assembly_map()( tMasterDofIndex )( tDofDepIndex, 1 );

                // compute uj vij
                Matrix< DDRMat > tujvij;
                this->compute_ujvij( tujvij );

                // if residual dof type (velocity)
                if( tDofType( 0 ) == mResidualDofType( 0 ) )
                {
                    // compute dnNdtn
                    Matrix< DDRMat > tdnNdtn;
                    this->compute_dnNdtn( tdnNdtn );

                    // compute uj vij rM
                    Matrix< DDRMat > tujvijrM;
                    this->compute_ujvijrm( tujvijrM, tRM );

                    // compute the jacobian
                    mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex }, { tMasterDepStartIndex, tMasterDepStopIndex } )
                    += aWStar *
                       (   trans( tVelocityFI->N() ) * tDensity * tdnNdtn
                         + trans( tVelocityFI->N() ) * tDensity * trans( tVelocityFI->gradx( 1 ) ) * tVelocityFI->N()
                         + trans( tVelocityFI->N() ) * tDensity * tujvij  //tVelocityFI->dnNdxn( 1 ) * tVelocityFI->val()
                         + tujvijrM * tDensity * tIncFlowSP->val()( 0 ) );
                }

                // compute the jacobian strong form
                Matrix< DDRMat > tJM;
                Matrix< DDRMat > tJC;
                compute_jacobian_strong_form( tDofType, tJM, tJC );

                // compute the jacobian contribution from strong form
                mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex },
                                      { tMasterDepStartIndex, tMasterDepStopIndex } )
                += aWStar *(   trans( tujvij ) * tDensity * tIncFlowSP->val()( 0 ) * tJM
                             + trans( tVelocityFI->div_operator() ) * tIncFlowSP->val()( 1 ) * tJC );

                // if property has dependency on the dof type
                if ( tDensityProp->check_dof_dependency( tDofType ) )
                {
                    // compute the jacobian
                    mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex }, { tMasterDepStartIndex, tMasterDepStopIndex } )
                    += aWStar *
                      (   trans( tVelocityFI->N() ) * tVelocityFI->gradt( 1 ) * tDensityProp->dPropdDOF( tDofType )
                        + trans( tVelocityFI->N() ) * tVelocityFI->val() * tVelocityFI->gradx( 1 ) * tDensityProp->dPropdDOF( tDofType )
                        + trans( tujvij )  * tIncFlowSP->val()( 0 ) * tRM * tDensityProp->dPropdDOF( tDofType ) );

                    if( tGravityProp != nullptr )
                    {
                        // compute the jacobian
                        mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex }, { tMasterDepStartIndex, tMasterDepStopIndex } )
                        -= aWStar * ( trans( tVelocityFI->N() ) * tGravityProp->val() * tDensityProp->dPropdDOF( tDofType ) );
                    }
                }

                // if constitutive model has dependency on the dof type
                if ( tIncFluidCM->check_dof_dependency( tDofType ) )
                {
                    // compute the jacobian
                    mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex }, { tMasterDepStartIndex, tMasterDepStopIndex } )
                    += aWStar * ( trans( tIncFluidCM->testStrain() ) * tPre * tIncFluidCM->dFluxdDOF( tDofType ) );
                }

                // if stabilization parameter has dependency on the dof type
                if ( tIncFlowSP->check_dof_dependency( tDofType ) )
                {
                    // compute the jacobian
                    mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex }, { tMasterDepStartIndex, tMasterDepStopIndex } )
                    += aWStar *
                       (   trans( tujvij ) * tDensity * tRM * tIncFlowSP->dSPdMasterDOF( tDofType ).get_row( 0 )
                         + trans( tVelocityFI->div_operator() ) * tRC * tIncFlowSP->dSPdMasterDOF( tDofType ).get_row( 1 ) );
                }

                // if gravity
                if ( tGravityProp != nullptr )
                {
                    // if property has dependency on the dof type
                    if ( tGravityProp->check_dof_dependency( tDofType ) )
                    {
                        // compute the jacobian
                        mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex }, { tMasterDepStartIndex, tMasterDepStopIndex } )
                        -= aWStar * ( trans( tVelocityFI->N() ) * tDensity * tGravityProp->dPropdDOF( tDofType ) );
                    }
                }
            }
        }

//------------------------------------------------------------------------------
        void IWG_Incompressible_NS_Velocity_Bulk::compute_jacobian_and_residual( real aWStar )
        {
#ifdef DEBUG
            // check master field interpolators
            this->check_field_interpolators();
#endif

            MORIS_ERROR( false, "IWG_Incompressible_NS_Velocity_Bulk::compute_jacobian_and_residual - Not implemented." );
        }

//------------------------------------------------------------------------------
        void IWG_Incompressible_NS_Velocity_Bulk::compute_dRdp( real aWStar )
        {
#ifdef DEBUG
            // check master field interpolators, properties and constitutive models
            this->check_field_interpolators();
#endif

            MORIS_ERROR( false, "IWG_Incompressible_NS_Velocity_Bulk::compute_dRdp - Not implemented." );
        }

//------------------------------------------------------------------------------
        void IWG_Incompressible_NS_Velocity_Bulk::compute_residual_strong_form( Matrix< DDRMat > & aRM,
                                                                                real             & aRC )
        {
            // get the velocity and pressure FIs
            Field_Interpolator * tVelocityFI = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get the density and gravity properties
            std::shared_ptr< Property > tDensityProp = mMasterProp( static_cast< uint >( IWG_Property_Type::DENSITY ) );
            std::shared_ptr< Property > tGravityProp = mMasterProp( static_cast< uint >( IWG_Property_Type::GRAVITY ) );

            // get the incompressible fluid constitutive model
            std::shared_ptr< Constitutive_Model > tIncFluidCM
            = mMasterCM( static_cast< uint >( IWG_Constitutive_Type::INCOMPRESSIBLE_FLUID ) );

            // get the incompressible flow stabilization parameter
            std::shared_ptr< Stabilization_Parameter > tIncFlowSP
            = mStabilizationParam( static_cast< uint >( IWG_Stabilization_Type::INCOMPRESSIBLE_FLOW ) );

            // get the density value
            real tDensity = tDensityProp->val()( 0 );

            // compute the residual strong form
            aRM = tDensity * trans( tVelocityFI->gradt( 1 ) )
                + tDensity * trans( tVelocityFI->gradx( 1 ) ) * tVelocityFI->val()
                - tIncFluidCM->divflux();

            aRC = tVelocityFI->div();

            // if gravity
            if ( tGravityProp != nullptr )
            {
                // add gravity to residual strong form
                aRM.matrix_data() -= tDensity * tGravityProp->val();
            }
        }

//------------------------------------------------------------------------------
        void IWG_Incompressible_NS_Velocity_Bulk::compute_jacobian_strong_form
        ( moris::Cell< MSI::Dof_Type >   aDofTypes,
          Matrix< DDRMat >             & aJM,
          Matrix< DDRMat >             & aJC )
        {
            // get the res dof and the derivative dof FIs
            Field_Interpolator * tVelocityFI = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );
            Field_Interpolator * tDerFI      = mMasterFIManager->get_field_interpolators_for_type( aDofTypes( 0 ) );

            // init aJM and aJC
            aJM.set_size( tVelocityFI->get_number_of_fields(),
                          tDerFI->get_number_of_space_time_coefficients(), 0.0 );
            aJC.set_size( 1,
                          tDerFI->get_number_of_space_time_coefficients(), 0.0 );

            // get the density and gravity properties
            std::shared_ptr< Property > tDensityProp = mMasterProp( static_cast< uint >( IWG_Property_Type::DENSITY ) );
            std::shared_ptr< Property > tGravityProp = mMasterProp( static_cast< uint >( IWG_Property_Type::GRAVITY ) );

            // get the incompressible fluid constitutive model
            std::shared_ptr< Constitutive_Model > tIncFluidCM
            = mMasterCM( static_cast< uint >( IWG_Constitutive_Type::INCOMPRESSIBLE_FLUID ) );

            // get the incompressible flow stabilization parameter
            std::shared_ptr< Stabilization_Parameter > tIncFlowSP
            = mStabilizationParam( static_cast< uint >( IWG_Stabilization_Type::INCOMPRESSIBLE_FLOW ) );

            // get the density value
            real tDensity = tDensityProp->val()( 0 );

            // if derivative wrt to residual dof type (here velocity)
            if( aDofTypes( 0 ) == mResidualDofType( 0 ) )
            {
                // compute the term uj vij
                Matrix< DDRMat > tujvij;
                this->compute_ujvij( tujvij );

                // compute the term dnNdtn
                Matrix< DDRMat > tdnNdtn;
                this->compute_dnNdtn( tdnNdtn );

                // compute the jacobian strong form
                aJM.matrix_data() += tDensity * tdnNdtn
                                   + tDensity * trans( tVelocityFI->gradx( 1 ) ) * tVelocityFI->N()
                                   + tDensity * tujvij ;

                aJC.matrix_data() += tVelocityFI->div_operator().matrix_data();
            }

            // if density depends on dof type
            if( tDensityProp->check_dof_dependency( aDofTypes ) )
            {
                // compute contribution to jacobian strong form
                aJM.matrix_data() += tVelocityFI->gradt( 1 ) * tDensityProp->dPropdDOF( aDofTypes )
                                   + trans( tVelocityFI->val() ) * tVelocityFI->gradx( 1 ) * tDensityProp->dPropdDOF( aDofTypes );
            }

            // if CM depends on dof type
            if( tIncFluidCM->check_dof_dependency( aDofTypes ) )
            {
                // compute contribution to jacobian strong form
                aJM.matrix_data() -= tIncFluidCM->ddivfluxdu( aDofTypes ).matrix_data();
            }

            // if gravity
            if ( tGravityProp != nullptr )
            {
                // if gravity depends on dof type
                if( tGravityProp->check_dof_dependency( aDofTypes ) )
                {
                    // add gravity to residual strong form
                    aJM.matrix_data() -= tDensity * tGravityProp->dPropdDOF( aDofTypes ).matrix_data();
                }
            }
        }

//------------------------------------------------------------------------------
        void IWG_Incompressible_NS_Velocity_Bulk::compute_ujvij( Matrix< DDRMat > & aujvij )
        {
            // get the residual dof type FI (here velocity)
            Field_Interpolator * tVelocityFI = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // init size for uj vij
            uint tNumRow = tVelocityFI->dnNdxn( 1 ).n_rows();
            uint tNumCol = tVelocityFI->dnNdxn( 1 ).n_cols();
            aujvij.set_size( tNumRow, tNumRow * tNumCol, 0.0 );

            // loop over the number of rows
            for( uint i = 0; i < tNumRow; i++ )
            {
                // compute uj vij
                aujvij( { i, i }, { i * tNumCol, ( i + 1 ) * tNumCol -1 })
                = trans( tVelocityFI->val() ) * tVelocityFI->dnNdxn( 1 );
            }
        }

//------------------------------------------------------------------------------
        void IWG_Incompressible_NS_Velocity_Bulk::compute_ujvijrm( Matrix< DDRMat > & aujvijrm,
                                                                   Matrix< DDRMat > & arm )
        {
            // get the residual dof type FI (here velocity)
            Field_Interpolator * tVelocityFI = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // set size for uj vij rM
            uint tNumField = tVelocityFI->get_number_of_fields();
            uint tNumBases = tVelocityFI->get_number_of_space_time_bases();
            aujvijrm.set_size( tNumField * tNumBases, tNumField * tNumBases , 0.0 );

            // loop over the number of fields
            for( uint iField = 0; iField < tNumField; iField++ )
            {
                // loop over the number of fields
                for( uint iField2 = 0; iField2 < tNumField; iField2++ )
                {
                    // compute uj vij rm
                    aujvijrm( { iField  * tNumBases, ( iField + 1 )  * tNumBases - 1 },
                              { iField2 * tNumBases, ( iField2 + 1 ) * tNumBases - 1 } )
                    = trans( tVelocityFI->dnNdxn( 1 ).get_row( iField2 ) ) * tVelocityFI->NBuild() * arm( iField );
                }
            }
        }

//------------------------------------------------------------------------------
        // FIXME provided directly by the field interpolator?
        void IWG_Incompressible_NS_Velocity_Bulk::compute_dnNdtn( Matrix< DDRMat > & adnNdtn )
        {
            // get the residual dof type FI (here velocity)
            Field_Interpolator * tVelocityFI = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // init size for dnNdtn
            uint tNumRowt = tVelocityFI->get_number_of_fields();
            uint tNumColt = tVelocityFI->dnNdtn( 1 ).n_cols();
            adnNdtn.set_size( tNumRowt, tNumRowt * tNumColt , 0.0 );

            // loop over the fields
            for( uint iField = 0; iField < tNumRowt; iField++ )
            {
                // fill the matrix for each dimension
                adnNdtn( { iField, iField }, { iField * tNumColt, ( iField + 1 ) * tNumColt - 1 } )
                = tVelocityFI->dnNdtn( 1 ).matrix_data();
            }
        }

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */
