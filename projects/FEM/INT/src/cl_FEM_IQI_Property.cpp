/*
 * cl_FEM_IQI_Property.cpp
 *
 *  Created on: Feb 2, 2020
 *      Author: noel
 */
#include "cl_FEM_Set.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_IQI_Property.hpp"

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        IQI_Property::IQI_Property()
        {
            // set size for the property pointer cell
            mMasterProp.resize( static_cast< uint >( IQI_Property_Type::MAX_ENUM ), nullptr );

            // populate the property map
            mPropertyMap[ "Property" ] = static_cast< uint >( IQI_Property_Type::PROPERTY );
        }

        //------------------------------------------------------------------------------

        void IQI_Property::compute_QI( Matrix< DDRMat > & aQI )
        {
            // get property index
            uint tPropertyIndex = static_cast< uint >( IQI_Property_Type::PROPERTY );

            // evaluate the QI
            aQI = mMasterProp( tPropertyIndex )->val();
        }

        //------------------------------------------------------------------------------

        void IQI_Property::compute_dQIdu(
                moris::Cell< MSI::Dof_Type > & aDofType,
                Matrix< DDRMat >             & adQIdu )
        {
            // get the property
            std::shared_ptr< Property > & tProperty =
                    mMasterProp( static_cast< uint >( IQI_Property_Type::PROPERTY ) );

            // if property depends on dof type
            if ( tProperty->check_dof_dependency( aDofType ) )
            {
                // compute dQIdu
                adQIdu = tProperty->dPropdDOF( aDofType );
            }
        }

        //------------------------------------------------------------------------------
    }/* end_namespace_fem */
}/* end_namespace_moris */



