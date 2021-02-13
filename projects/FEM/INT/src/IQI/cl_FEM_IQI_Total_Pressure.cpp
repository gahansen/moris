/*
 * cl_FEM_IQI_Total_Pressure.cpp
 *
 *  Created on: Sep 27, 2020
 *      Author: noel
 */
#include "cl_FEM_Set.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_IQI_Total_Pressure.hpp"

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        IQI_Total_Pressure::IQI_Total_Pressure()
        {
            // set fem IQI type
            mFEMIQIType = fem::IQI_Type::TOTAL_PRESSURE;

            // set size for the constitutive model pointer cell
            mMasterCM.resize( static_cast< uint >( IQI_Constitutive_Type::MAX_ENUM ), nullptr );

            // populate the constitutive map
            mConstitutiveMap[ "Fluid" ] = static_cast< uint >( IQI_Constitutive_Type::FLUID );
        }
        
        //------------------------------------------------------------------------------

        void IQI_Total_Pressure::compute_QI( Matrix< DDRMat > & aQI )
        {
            // get the fluid CM
            std::shared_ptr< Constitutive_Model > & tCMFluid =
                    mMasterCM( static_cast< uint >( IQI_Constitutive_Type::FLUID ) );

            // get density from CM
            std::shared_ptr< Property > & tPropDensity = tCMFluid->get_property( "Density" );

            // FIXME protect dof type
            // get velocity field interpolator
            Field_Interpolator * tFIVelocity =
                    mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::VX );

            // FIXME protect dof type
            // get pressure field interpolator
            Field_Interpolator * tFIPressure =
                    mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::P );

            // evaluate the QI
            aQI = tFIPressure->val() +
                    0.5 * tPropDensity->val() * trans( tFIVelocity->val() ) * tFIVelocity->val();
        }

        //------------------------------------------------------------------------------

        void IQI_Total_Pressure::compute_QI( real aWStar )
        {
            // get index for QI
            sint tQIIndex = mSet->get_QI_assembly_index( mName );

            // get the fluid CM
            std::shared_ptr< Constitutive_Model > & tCMFluid =
                    mMasterCM( static_cast< uint >( IQI_Constitutive_Type::FLUID ) );

            // get density from CM
            std::shared_ptr< Property > & tPropDensity = tCMFluid->get_property( "Density" );

            // FIXME protect dof type
            // get velocity field interpolator
            Field_Interpolator * tFIVelocity =
                    mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::VX );

            // FIXME protect dof type
            // get pressure field interpolator
            Field_Interpolator * tFIPressure =
                    mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::P );

            // evaluate the QI
            mSet->get_QI()( tQIIndex ) += aWStar * ( tFIPressure->val() +
                    0.5 * tPropDensity->val() * trans( tFIVelocity->val() ) * tFIVelocity->val() );
        }

        //------------------------------------------------------------------------------

        void IQI_Total_Pressure::compute_dQIdu( real aWStar )
        {
            // get the column index to assemble in residual
            sint tQIIndex = mSet->get_QI_assembly_index( mName );

            // get the fluid CM
            std::shared_ptr< Constitutive_Model > & tCMFluid =
                    mMasterCM( static_cast< uint >( IQI_Constitutive_Type::FLUID ) );

            // get density from CM
            std::shared_ptr< Property > & tPropDensity =
                    tCMFluid->get_property( "Density" );

            // FIXME protect dof type
            // get velocity field interpolator
            Field_Interpolator * tFIVelocity =
                    mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::VX );

            // FIXME protect dof type
            // get pressure field interpolator
            Field_Interpolator * tFIPressure =
                    mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::P );

            // get the number of master dof type dependencies
            uint tNumDofDependencies = mRequestedMasterGlobalDofTypes.size();

            // compute dQIdu for indirect dof dependencies
            for( uint iDof = 0; iDof < tNumDofDependencies; iDof++ )
            {
                // get the treated dof type
                Cell< MSI::Dof_Type > & tDofType = mRequestedMasterGlobalDofTypes( iDof );

                // get master index for residual dof type, indices for assembly
                uint tMasterDofIndex      = mSet->get_dof_index_for_type( tDofType( 0 ), mtk::Master_Slave::MASTER );
                uint tMasterDepStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
                uint tMasterDepStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

                // if dof type is velocity
                // FIXME protect dof type
                if ( tDofType( 0 ) == MSI::Dof_Type::VX )
                {
                    mSet->get_residual()( tQIIndex )(
                            { tMasterDepStartIndex, tMasterDepStopIndex },
                            { 0, 0 } ) += aWStar * (
                                    tPropDensity->val()( 0 ) * tFIVelocity->N_trans() * tFIVelocity->val() );
                }

                // if dof type is pressure
                // FIXME protect dof type
                if ( tDofType( 0 ) == MSI::Dof_Type::P )
                {
                    mSet->get_residual()( tQIIndex )(
                            { tMasterDepStartIndex, tMasterDepStopIndex },
                            { 0, 0 } ) += aWStar * ( tFIPressure->N_trans() );
                }

                // if density depends on dof type
                if ( tPropDensity->check_dof_dependency( tDofType ) )
                {
                    // compute dQIdu
                    mSet->get_residual()( tQIIndex )(
                            { tMasterDepStartIndex, tMasterDepStopIndex },
                            { 0, 0 } ) += aWStar * ( 0.5 * trans( tFIVelocity->val() ) * tFIVelocity->val() *
                                    tPropDensity->dPropdDOF( tDofType ) );
                }
            }
        }

        //------------------------------------------------------------------------------

        void IQI_Total_Pressure::compute_dQIdu(
                moris::Cell< MSI::Dof_Type > & aDofType,
                Matrix< DDRMat >             & adQIdu )
        {
            // get the fluid CM
            std::shared_ptr< Constitutive_Model > & tCMFluid =
                    mMasterCM( static_cast< uint >( IQI_Constitutive_Type::FLUID ) );

            // get density from CM
            std::shared_ptr< Property > & tPropDensity =
                    tCMFluid->get_property( "Density" );

            // FIXME protect dof type
            // get velocity field interpolator
            Field_Interpolator * tFIVelocity =
                    mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::VX );

            // FIXME protect dof type
            // get pressure field interpolator
            Field_Interpolator * tFIPressure =
                    mMasterFIManager->get_field_interpolators_for_type( MSI::Dof_Type::P );

            // if dof type is velocity
            // FIXME protect dof type
            if ( aDofType( 0 ) == MSI::Dof_Type::VX )
            {
                adQIdu += tPropDensity->val()( 0 ) * trans( tFIVelocity->N() ) * tFIVelocity->val();
            }

            // if dof type is pressure
            // FIXME protect dof type
            if ( aDofType( 0 ) == MSI::Dof_Type::P )
            {
                adQIdu += trans( tFIPressure->N() );
            }

            // if density depends on dof type
            if ( tPropDensity->check_dof_dependency( aDofType ) )
            {
                // compute dQIdu
                adQIdu += 0.5 * trans( tFIVelocity->val() ) * tFIVelocity->val() *
                        tPropDensity->dPropdDOF( aDofType );
            }
        }

        //------------------------------------------------------------------------------
    }/* end_namespace_fem */
}/* end_namespace_moris */


