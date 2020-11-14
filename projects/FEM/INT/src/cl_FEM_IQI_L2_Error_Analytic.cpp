/*
 * cl_FEM_IQI_L2_Error_Analytic.cpp
 *
 *  Created on: Feb 2, 2020
 *      Author: noel
 */
#include "cl_FEM_Set.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_IQI_L2_Error_Analytic.hpp"

#include "fn_norm.hpp"

namespace moris
{
    namespace fem
    {

        //------------------------------------------------------------------------------

        IQI_L2_Error_Analytic::IQI_L2_Error_Analytic()
        {
            // set FEM IQI type
            mFEMIQIType = fem::IQI_Type::L2_ERROR_ANALYTIC;

            // set size for the property pointer cell
            mMasterProp.resize( static_cast< uint >( IQI_Property_Type::MAX_ENUM ), nullptr );

            // populate the property map
            mPropertyMap[ "L2Check" ] = static_cast< uint >( IQI_Property_Type::L2_CHECK );
        }

        //------------------------------------------------------------------------------

        void IQI_L2_Error_Analytic::compute_QI( Matrix< DDRMat > & aQI )
        {
            // get field interpolator
            Field_Interpolator * tFI =
                    mMasterFIManager->get_field_interpolators_for_type( mMasterDofTypes( 0 )( 0 ) );

            // get analytical solution property
            std::shared_ptr< Property > & tPropL2Check =
                    mMasterProp( static_cast< uint >( IQI_Property_Type::L2_CHECK ) );

            // compute jump
            real tJumpNorm = norm( tFI->val() - tPropL2Check->val());

            // evaluate the QI
            aQI = tJumpNorm * tJumpNorm;
        }

        //------------------------------------------------------------------------------

        void IQI_L2_Error_Analytic::compute_dQIdu(
                moris::Cell< MSI::Dof_Type > & aDofType,
                Matrix< DDRMat >             & adQIdu )
        {
            MORIS_ERROR( false, "IQI_L2_Error_Analytic::compute_dQIdu - Not implemented." );
        }

        //------------------------------------------------------------------------------
    }/* end_namespace_fem */
}/* end_namespace_moris */

