/*
 * cl_FEM_IQI_L2_Error_Analytic.hpp
 *
 *  Created on: Feb 3, 2020
 *      Author: noel
 */

#ifndef PROJECTS_FEM_INT_SRC_CL_FEM_IQI_L2_ERROR_ANALYTIC_HPP_
#define PROJECTS_FEM_INT_SRC_CL_FEM_IQI_L2_ERROR_ANALYTIC_HPP_

#include <map>

#include "typedefs.hpp"                     //MRS/COR/src
#include "cl_Cell.hpp"                      //MRS/CON/src

#include "cl_Matrix.hpp"                    //LINALG/src
#include "linalg_typedefs.hpp"              //LINALG/src

#include "cl_FEM_IQI.hpp"                   //FEM/INT/src

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        class IQI_L2_Error_Analytic : public IQI
        {
                //------------------------------------------------------------------------------

                enum class IQI_Property_Type
                {
                        L2_CHECK,
                        MAX_ENUM
                };

            public:
                //------------------------------------------------------------------------------
                /*
                 * constructor
                 */
                IQI_L2_Error_Analytic();

                //------------------------------------------------------------------------------
                /**
                 * trivial destructor
                 */
                ~IQI_L2_Error_Analytic(){};

                //------------------------------------------------------------------------------

            private:

                //------------------------------------------------------------------------------
                /**
                 * compute the quantity of interest
                 * @param[ in ] aWStar weight associated to the evaluation point
                 */
                void compute_QI( real aWStar );

                //------------------------------------------------------------------------------
                /**
                 * Evaluate the quantity of interest and fill aQI with value
                 * @param[ in ] aQI IQI value at evaluation point
                 */
                void compute_QI( Matrix< DDRMat > & aQI );

                //------------------------------------------------------------------------------
                /**
                 * compute the derivative of the quantity of interest wrt dof types
                 * @param[ in ] aWStar weight associated to the evaluation point
                 */
                void compute_dQIdu( real aWStar )
                {
                    MORIS_ERROR( false, "IQI_L2_Error_Analytic::compute_dQIdu - not implemented." );
                }

                //------------------------------------------------------------------------------
                /**
                 * compute the derivative of the quantity of interest wrt dof types
                 * @param[ in ] aDofType group of dof types wrt which derivatives are evaluated
                 * @param[ in ] adQIdu   derivative of quantity of interest matrix to fill
                 */
                void compute_dQIdu(
                        moris::Cell< MSI::Dof_Type > & aDofType,
                        Matrix< DDRMat >             & adQIdu )
                {
                    MORIS_ERROR( false, "IQI_L2_Error_Analytic::compute_dQIdu() - not implemented for a drag/lift coefficient IQI.");
                }

                //------------------------------------------------------------------------------

        };
    }/* end namespace fem */
} /* end namespace moris */

#endif /* PROJECTS_FEM_INT_SRC_CL_FEM_IQI_L2_ERROR_ANALYTIC_HPP_ */
