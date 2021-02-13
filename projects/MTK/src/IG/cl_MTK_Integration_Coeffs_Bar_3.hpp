/*
 * cl_FEM_Integration_Coeffs_Bar_2.hpp
 *
 *  Created on: Jul 19, 2018
 *      Author: messe
 */

#ifndef SRC_FEM_CL_FEM_INTEGRATION_COEFFS_BAR_3_HPP_
#define SRC_FEM_CL_FEM_INTEGRATION_COEFFS_BAR_3_HPP_

#include "cl_FEM_Integration_Coeffs.hpp"
#include "typedefs.hpp" //MRS/COR/src
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_FEM_Enums.hpp" //FEM/INT/src

namespace moris
{
    namespace fem
    {

//------------------------------------------------------------------------------

        template<>
        uint
        Integration_Coeffs<
        Integration_Type::GAUSS,
        Integration_Order::BAR_3>::get_number_of_dimensions()
        {
            return 1;
        }

//------------------------------------------------------------------------------

        template<>
        uint
        Integration_Coeffs<
            Integration_Type::GAUSS,
            Integration_Order::BAR_3>::get_number_of_points()
            {
                return 3;
            }

//------------------------------------------------------------------------------

        template<>
        void
        Integration_Coeffs<
                Integration_Type::GAUSS,
                Integration_Order::BAR_3>::get_points( Matrix< DDRMat > & aIntegrationPoints )
        {
            aIntegrationPoints =
            {
                {
                    -0.7745966692414834,
                     0.000000000000000,
                     0.7745966692414834
                }
            };
          }

//------------------------------------------------------------------------------

            template<>
            void
            Integration_Coeffs<
                Integration_Type::GAUSS,
                Integration_Order::BAR_3 >::get_weights( Matrix< DDRMat > & aIntegrationWeights )
            {
                aIntegrationWeights =
                {
                      {
                          5.555555555555556e-01,
                          8.888888888888888e-01,
                          5.555555555555556e-01
                      }
                };
            }

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

#endif /* SRC_FEM_CL_FEM_INTEGRATION_COEFFS_BAR_3_HPP_ */