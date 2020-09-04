/*
 * cl_FEM_IQI_Strain_energy.cpp
 *
 *  Created on: Dec 5, 2019
 *      Author: noel
 */
#include "cl_FEM_Set.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_IQI_Analytic.hpp"

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------
        IQI_Analytic::IQI_Analytic()
        {
            mMasterProp.resize( static_cast< uint >( IQI_Property_Type::MAX_ENUM ), nullptr );

            // populate the constitutive map
            mPropertyMap[ "Function" ] = IQI_Property_Type::FUNCTION;
        }
        //------------------------------------------------------------------------------
        void IQI_Analytic::compute_QI( Matrix< DDRMat > & aQI )
        {
            // get indices for properties, CM and SP
            uint tFunctionIndex = static_cast< uint >( IQI_Property_Type::FUNCTION );


            // evaluate the QI
            aQI = mMasterProp(tFunctionIndex)->val();
        }

        //------------------------------------------------------------------------------
        void IQI_Analytic::compute_dQIdu( MSI::Dof_Type aDofType, Matrix< DDRMat > & adQIdu )
        {
            MORIS_ERROR(false, "compute_dQIdu() not implemented for an analytic IQI.");
        }

        //------------------------------------------------------------------------------
    }/* end_namespace_fem */
}/* end_namespace_moris */



