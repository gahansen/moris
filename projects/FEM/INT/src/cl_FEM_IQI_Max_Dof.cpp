/*
 * cl_FEM_IQI_Max_Dof.cpp
 *
 *  Created on: Jul 10, 2020
 *      Author: wunsch
 */
#include "cl_FEM_Set.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_IQI_Max_Dof.hpp"

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        IQI_Max_Dof::IQI_Max_Dof()
        {
            // set IQI type
            mIQIType = vis::Output_Type::MAX_DOF;

            // set FEM IQI type
            mFEMIQIType = fem::IQI_Type::MAX_DOF;

            // set the property pointer cell size
            mMasterProp.resize( static_cast< uint >( IQI_Property_Type::MAX_ENUM ), nullptr );

            // populate the property map
            mPropertyMap[ "ReferenceValue" ]    = IQI_Property_Type::REFERENCE_VALUE;
            mPropertyMap[ "Exponent" ]          = IQI_Property_Type::EXPONENT;
        }

        //------------------------------------------------------------------------------

        void IQI_Max_Dof::set_property(
                std::shared_ptr< Property > aProperty,
                std::string                 aPropertyString,
                mtk::Master_Slave           aIsMaster)
        {
            // check that aPropertyString makes sense
            if ( mPropertyMap.find( aPropertyString ) == mPropertyMap.end() )
            {
                std::string tErrMsg =
                        std::string( "CM_Diffusion_Linear_Isotropic_Phase_Change::set_property - Unknown aPropertyString : ") +
                        aPropertyString;

                MORIS_ERROR( false , tErrMsg.c_str() );
            }

            // set the property in the property cell
            mMasterProp( static_cast< uint >( mPropertyMap[ aPropertyString ] ) ) = aProperty;
        }

        //------------------------------------------------------------------------------

        void IQI_Max_Dof::compute_QI( Matrix< DDRMat > & aQI )
        {
            // get field interpolator for a given dof type
            Field_Interpolator * tFI =
                    mMasterFIManager->get_field_interpolators_for_type( mMasterDofTypes( 0 )( 0 ) );

            MORIS_ERROR(mMasterProp( static_cast< uint >( IQI_Property_Type::REFERENCE_VALUE ) ) != nullptr,
                    "IQI_Max_Dof - no reference value set");

            MORIS_ERROR(mMasterProp( static_cast< uint >( IQI_Property_Type::EXPONENT ) ) != nullptr,
                    "IQI_Max_Dof - no exponent set");

            // get property values
            real tRefValue = mMasterProp( static_cast< uint >( IQI_Property_Type::REFERENCE_VALUE ) )->val()( 0 );
            real tExponent = mMasterProp( static_cast< uint >( IQI_Property_Type::EXPONENT ) )->val()( 0 );

            // check if dof index was set (for the case of vector field)
            if( mMasterDofTypes( 0 ).size() > 1 )
            {
                MORIS_ERROR( mIQITypeIndex != -1, "IQI_Max_Dof::compute_QI - mIQITypeIndex not set." );
            }
            else
            {
                mIQITypeIndex = 0;
            }

            // evaluate the QI
            aQI = {{ std::pow( 1/tRefValue * tFI->val()( mIQITypeIndex ) - 1.0, tExponent ) }};
        }

        //------------------------------------------------------------------------------

        void IQI_Max_Dof::compute_QI( moris::real aWStar )
        {
            // get index for QI
            sint tQIIndex = mSet->get_QI_assembly_index( mName );

            // get field interpolator for a given dof type
            Field_Interpolator * tFI =
                    mMasterFIManager->get_field_interpolators_for_type( mMasterDofTypes( 0 )( 0 ) );

            // get property values
            real tRefValue = mMasterProp( static_cast< uint >( IQI_Property_Type::REFERENCE_VALUE ) )->val()( 0 );
            real tExponent = mMasterProp( static_cast< uint >( IQI_Property_Type::EXPONENT ) )->val()( 0 );

            // check if dof index was set (for the case of vector field)
            if( mMasterDofTypes( 0 ).size() > 1 )
            {
                MORIS_ERROR( mIQITypeIndex != -1, "IQI_Max_Dof::compute_QI - mIQITypeIndex not set." );
            }
            else
            {
                mIQITypeIndex = 0;
            }

            // evaluate the QI
            mSet->get_QI()( tQIIndex ).matrix_data() += { aWStar *  std::pow( 1/tRefValue * tFI->val()( mIQITypeIndex ) - 1.0, tExponent ) };
        }

        //------------------------------------------------------------------------------

        void IQI_Max_Dof::compute_dQIdu( Matrix< DDRMat > & adQIdDof )
        {
            MORIS_ERROR( false, "IQI_Max_Dof::compute_dQIdu( Matrix< DDRMat > & adQIdDof ) --- Not implemented, yet. \n" );
        }

        //------------------------------------------------------------------------------
    }/* end_namespace_fem */
}/* end_namespace_moris */