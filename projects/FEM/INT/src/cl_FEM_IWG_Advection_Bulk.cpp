
#include "cl_FEM_IWG_Advection_Bulk.hpp"
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
        IWG_Advection_Bulk::IWG_Advection_Bulk()
        {
            // set size for the property pointer cell
            mMasterProp.resize( static_cast< uint >( IWG_Property_Type::MAX_ENUM ), nullptr );

            // populate the property map
            mPropertyMap[ "Density" ] = IWG_Property_Type::DENSITY;
            mPropertyMap[ "HeatCapacity" ] = IWG_Property_Type::HEAT_CAPACITY;

            // set size for the constitutive model pointer cell
            mMasterCM.resize( static_cast< uint >( IWG_Constitutive_Type::MAX_ENUM ), nullptr );

            // populate the constitutive map
            mConstitutiveMap[ "Diffusion" ] = IWG_Constitutive_Type::DIFFUSION;

            // set size for the stabilization parameter pointer cell
            mStabilizationParam.resize( static_cast< uint >( IWG_Stabilization_Type::MAX_ENUM ), nullptr );

            // populate the stabilization map
            mStabilizationMap[ "SUPG" ] = IWG_Stabilization_Type::SUPG;
        }

//------------------------------------------------------------------------------
        void IWG_Advection_Bulk::compute_residual( real aWStar )
        {
            // check master field interpolators
#ifdef DEBUG
            this->check_field_interpolators();
#endif

            // get master index for residual dof type, indices for assembly
            uint tMasterDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::MASTER );
            uint tMasterResStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
            uint tMasterResStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

            // get the residual dof (here temperature) field interpolator
            Field_Interpolator* tFITemp = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get the velocity dof field interpolator
            // FIXME protect dof type
            Field_Interpolator* tFIVelocity = mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::VX );

            // get density property
            std::shared_ptr< Property > tPropDensity
            = mMasterProp( static_cast< uint >( IWG_Property_Type::DENSITY ) );
            real tDensity = tPropDensity->val()( 0 );

            // get the heat capacity property
            std::shared_ptr< Property > tPropHeatCapacity
            = mMasterProp( static_cast< uint >( IWG_Property_Type::HEAT_CAPACITY ) );
            real tHeatCapacity = tPropHeatCapacity->val()( 0 );

            // get the SUPG stabilization parameter
            std::shared_ptr< Stabilization_Parameter > tSPSUPG
            = mStabilizationParam( static_cast< uint >( IWG_Stabilization_Type::SUPG ) );

            // compute the residual strong form
            Matrix< DDRMat > tRT;
            this->compute_residual_strong_form( tRT );

            // compute the residual
            mSet->get_residual()( 0 )( { tMasterResStartIndex, tMasterResStopIndex }, { 0, 0 } )
            += aWStar
             * (   tDensity * tHeatCapacity * trans( tFITemp->N() ) * trans( tFIVelocity->val() ) * tFITemp->gradx( 1 )
                 + tSPSUPG->val()( 0 ) * trans( tFITemp->dnNdxn( 1 ) ) * tFIVelocity->val() * tRT( 0, 0 ) / ( tDensity * tHeatCapacity ) );
        }

//------------------------------------------------------------------------------
        void IWG_Advection_Bulk::compute_jacobian( real aWStar )
        {
#ifdef DEBUG
            // check master field interpolators
            this->check_field_interpolators();
#endif

            // get master index for residual dof type, indices for assembly
            uint tMasterDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::MASTER );
            uint tMasterResStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
            uint tMasterResStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

            // get the residual dof (here temperature) field interpolator
            Field_Interpolator* tFITemp = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get the velocity dof field interpolator
            // FIXME protect dof type
            Field_Interpolator* tFIVelocity = mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::VX );

            // get density property
            std::shared_ptr< Property > tPropDensity
            = mMasterProp( static_cast< uint >( IWG_Property_Type::DENSITY ) );
            real tDensity = tPropDensity->val()( 0 );

            // get the heat capacity property
            std::shared_ptr< Property > tPropHeatCapacity
            = mMasterProp( static_cast< uint >( IWG_Property_Type::HEAT_CAPACITY ) );
            real tHeatCapacity = tPropHeatCapacity->val()( 0 );

            // get the SUPG stabilization parameter
            std::shared_ptr< Stabilization_Parameter > tSPSUPG
            = mStabilizationParam( static_cast< uint >( IWG_Stabilization_Type::SUPG ) );

            // compute the residual strong form
            Matrix< DDRMat > tRT;
            this->compute_residual_strong_form( tRT );

            // get number of master dof dependencies
            uint tNumDofDependencies = mRequestedMasterGlobalDofTypes.size();

            // loop over master dof dependencies
            for( uint iDOF = 0; iDOF < tNumDofDependencies; iDOF++ )
            {
                // get the treated dof type
                Cell< MSI::Dof_Type > tDofType = mRequestedMasterGlobalDofTypes( iDOF );

                // get the index for dof type, indices for assembly
                sint tDofDepIndex         = mSet->get_dof_index_for_type( tDofType( 0 ), mtk::Master_Slave::MASTER );
                uint tMasterDepStartIndex = mSet->get_jac_dof_assembly_map()( tMasterDofIndex )( tDofDepIndex, 0 );
                uint tMasterDepStopIndex  = mSet->get_jac_dof_assembly_map()( tMasterDofIndex )( tDofDepIndex, 1 );

                // if residual dof type (here temperature)
                if( tDofType( 0 ) == mResidualDofType( 0 ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex },
                                          { tMasterDepStartIndex, tMasterDepStopIndex } )
                    += aWStar
                     * ( tDensity * tHeatCapacity * trans( tFITemp->N() ) * trans( tFIVelocity->val() ) * tFITemp->dnNdxn( 1 ) );
                }

                // if velocity dof type
                // FIXME protect dof type
                if( tDofType( 0 ) == MSI::Dof_Type::VX )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex },
                                          { tMasterDepStartIndex, tMasterDepStopIndex } )
                    += aWStar
                     * (   tDensity * tHeatCapacity * trans( tFITemp->N() ) * trans( tFITemp->gradx( 1 ) ) * tFIVelocity->N()
                         + tSPSUPG->val()( 0 ) * trans( tFITemp->dnNdxn( 1 ) ) * tFIVelocity->N() * tRT( 0, 0 ) / ( tDensity * tHeatCapacity ) );
                }

                // compute the jacobian strong form
                Matrix< DDRMat > tJT;
                this->compute_jacobian_strong_form( tDofType, tJT );

                // compute the jacobian contribution from strong form
                mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex },
                                      { tMasterDepStartIndex, tMasterDepStopIndex } )
                += aWStar * ( tSPSUPG->val()( 0 ) * trans( tFITemp->dnNdxn( 1 ) ) * tFIVelocity->val() * tJT / ( tDensity * tHeatCapacity ) );

                // if density depends on dof type
                if ( tPropDensity->check_dof_dependency( tDofType ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex },
                                          { tMasterDepStartIndex, tMasterDepStopIndex } )
                    += aWStar
                     * (   tHeatCapacity * trans( tFITemp->N() ) * trans( tFIVelocity->val() ) * tFITemp->gradx( 1 ) * tPropDensity->dPropdDOF( tDofType )
                         - tSPSUPG->val()( 0 ) * trans( tFITemp->dnNdxn( 1 ) ) * tFIVelocity->val() * tRT( 0, 0 ) * tPropDensity->dPropdDOF( tDofType ) / ( std::pow( tDensity, 2.0 ) * tHeatCapacity ) );
                }

                // if heat capacity depends on dof type
                if ( tPropHeatCapacity->check_dof_dependency( tDofType ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex },
                                          { tMasterDepStartIndex, tMasterDepStopIndex } )
                    += aWStar
                     * (   tDensity * trans( tFITemp->N() ) * trans( tFIVelocity->val() ) * tFITemp->gradx( 1 ) * tPropHeatCapacity->dPropdDOF( tDofType )
                         - tSPSUPG->val()( 0 ) * trans( tFITemp->dnNdxn( 1 ) ) * tFIVelocity->val() * tRT( 0, 0 ) * tPropHeatCapacity->dPropdDOF( tDofType ) / ( tDensity * std::pow( tHeatCapacity, 2.0 ) ) );
                }

                // if SUPG stabilization parameter depends on dof type
                if( tSPSUPG->check_dof_dependency( tDofType ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex },
                                          { tMasterDepStartIndex, tMasterDepStopIndex } )
                    += aWStar
                     * ( trans( tFITemp->dnNdxn( 1 ) ) * tFIVelocity->val() * tRT( 0, 0 ) * tSPSUPG->dSPdMasterDOF( tDofType ) / ( tDensity * tHeatCapacity ) );
                }
            }
        }

//------------------------------------------------------------------------------
        void IWG_Advection_Bulk::compute_jacobian_and_residual( real aWStar )
        {
            MORIS_ERROR( false, "IWG_Advection_Bulk::compute_jacobian_and_residual - Not implemented." );
        }

//------------------------------------------------------------------------------
        void IWG_Advection_Bulk::compute_dRdp( real aWStar )
        {
            MORIS_ERROR( false, "IWG_Advection_Bulk::compute_dRdp - Not implemented." );
        }

//------------------------------------------------------------------------------
        void IWG_Advection_Bulk::compute_residual_strong_form( Matrix< DDRMat > & aRT )
        {
            // get the residual dof (here temperature) field interpolator
            Field_Interpolator* tFITemp = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get the velocity dof field interpolator
            // FIXME protect dof type
            Field_Interpolator* tFIVelocity = mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::VX );

            // get density property
            std::shared_ptr< Property > tPropDensity
            = mMasterProp( static_cast< uint >( IWG_Property_Type::DENSITY ) );
            real tDensity = tPropDensity->val()( 0 );

            // get the heat capacity property
            std::shared_ptr< Property > tPropHeatCapacity
            = mMasterProp( static_cast< uint >( IWG_Property_Type::HEAT_CAPACITY ) );
            real tHeatCapacity = tPropHeatCapacity->val()( 0 );

            // get the heat capacity property
            std::shared_ptr< Constitutive_Model > tCMDiffusion
            = mMasterCM( static_cast< uint >( IWG_Constitutive_Type::DIFFUSION ) );

            aRT = tDensity * tHeatCapacity * tFITemp->gradt( 1 )
                + tDensity * tHeatCapacity * trans( tFIVelocity->val() ) * tFITemp->gradx( 1 )
                - tCMDiffusion->divflux();
        }

//------------------------------------------------------------------------------
        void IWG_Advection_Bulk::compute_jacobian_strong_form
        ( moris::Cell< MSI::Dof_Type >   aDofTypes,
          Matrix< DDRMat >             & aJT )
        {
            // get the res dof and the derivative dof FIs
            Field_Interpolator * tFITemp = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );
            Field_Interpolator * tFIDer  = mMasterFIManager->get_field_interpolators_for_type( aDofTypes( 0 ) );

            // get the velocity dof field interpolator
            // FIXME protect dof type
            Field_Interpolator* tFIVelocity = mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::VX );

            // init aJT
            aJT.set_size( 1, tFIDer->get_number_of_space_time_coefficients(), 0.0 );

            // get density property
            std::shared_ptr< Property > tPropDensity
            = mMasterProp( static_cast< uint >( IWG_Property_Type::DENSITY ) );
            real tDensity = tPropDensity->val()( 0 );

            // get the heat capacity property
            std::shared_ptr< Property > tPropHeatCapacity
            = mMasterProp( static_cast< uint >( IWG_Property_Type::HEAT_CAPACITY ) );
            real tHeatCapacity = tPropHeatCapacity->val()( 0 );

            // get the heat capacity property
            std::shared_ptr< Constitutive_Model > tCMDiffusion
            = mMasterCM( static_cast< uint >( IWG_Constitutive_Type::DIFFUSION ) );

            // if derivative wrt to residual dof type (here temperature)
            if( aDofTypes( 0 ) == mResidualDofType( 0 ) )
            {
                aJT.matrix_data()
                +=   tDensity * tHeatCapacity * tFITemp->dnNdtn( 1 )
                   + tDensity * tHeatCapacity * trans( tFIVelocity->val() ) * tFITemp->dnNdxn( 1 );
            }

            // if derivative wrt to velocity dof type
            if( aDofTypes( 0 ) == MSI::Dof_Type::VX )
            {
                aJT.matrix_data()
                += tDensity * tHeatCapacity * trans( tFITemp->gradx( 1 ) ) * tFIVelocity->N();
            }

            // if density depends on dof type
            if( tPropDensity->check_dof_dependency( aDofTypes ) )
            {
                // compute contribution to jacobian strong form
                aJT.matrix_data()
                += tHeatCapacity * tFITemp->gradt( 1 ) * tPropDensity->dPropdDOF( aDofTypes )
                 + tHeatCapacity * trans( tFIVelocity->val() ) * tFITemp->gradx( 1 ) * tPropDensity->dPropdDOF( aDofTypes );
            }

            // if density depends on dof type
            if( tPropHeatCapacity->check_dof_dependency( aDofTypes ) )
            {
                // compute contribution to jacobian strong form
                aJT.matrix_data()
                += tDensity * tFITemp->gradt( 1 ) * tPropHeatCapacity->dPropdDOF( aDofTypes )
                 + tDensity * trans( tFIVelocity->val() ) * tFITemp->gradx( 1 ) * tPropHeatCapacity->dPropdDOF( aDofTypes );
            }

            // if CM diffusion depends on dof type
            if( tCMDiffusion->check_dof_dependency( aDofTypes ) )
            {
                // compute contribution to jacobian strong form
                aJT.matrix_data() -= tCMDiffusion->ddivfluxdu( aDofTypes ).matrix_data();
            }

        }

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */