/*
 * cl_FEM_Integration_Coeffs_Tet_15.hpp
 *
 *  Created on: Apr 05, 2019
 *      Author: noel
 */

#ifndef SRC_FEM_CL_FEM_INTEGRATION_COEFFS_TET_15_HPP_
#define SRC_FEM_CL_FEM_INTEGRATION_COEFFS_TET_15_HPP_

#include "cl_FEM_Integration_Coeffs.hpp"
#include "typedefs.hpp" //MRS/COR/src
#include "cl_Matrix.hpp" //LNA/src
#include "linalg_typedefs.hpp" //LNA/src
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
            Integration_Order::TET_15>::get_number_of_dimensions()
        {
            return 4;
        }
//------------------------------------------------------------------------------

        template<>
        uint
        Integration_Coeffs<
            Integration_Type::GAUSS,
            Integration_Order::TET_15>::get_number_of_points()
            {
                return 15;
            }

//------------------------------------------------------------------------------

        template<>
        Matrix< DDRMat >
        Integration_Coeffs<
                Integration_Type::GAUSS,
                Integration_Order::TET_15>::get_points()
        {
            Matrix< DDRMat > aIntegrationPoints =
            {
                { 0.2500000000000000, 0.0000000000000000, 0.3333333333333333, 0.3333333333333333, 0.3333333333333333,
                  0.7272727272727273, 0.0909090909090909, 0.0909090909090909, 0.0909090909090909, 0.4334498464263357,
                  0.0665501535736643, 0.0665501535736643, 0.0665501535736643, 0.4334498464263357, 0.4334498464263357 },
                { 0.2500000000000000, 0.3333333333333333, 0.3333333333333333, 0.3333333333333333, 0.0000000000000000,
                  0.0909090909090909, 0.0909090909090909, 0.0909090909090909, 0.7272727272727273, 0.0665501535736643,
                  0.4334498464263357, 0.0665501535736643, 0.4334498464263357, 0.0665501535736643, 0.4334498464263357 },
                { 0.2500000000000000, 0.3333333333333333, 0.3333333333333333, 0.0000000000000000, 0.3333333333333333,
                  0.0909090909090909, 0.0909090909090909, 0.7272727272727273, 0.0909090909090909, 0.0665501535736643,
                  0.0665501535736643, 0.4334498464263357, 0.4334498464263357, 0.4334498464263357, 0.0665501535736643 },
                { 0.2500000000000000, 0.3333333333333333, 0.0000000000000000, 0.3333333333333333, 0.3333333333333333,
                  0.0909090909090910, 0.7272727272727273, 0.0909090909090913, 0.0909090909090910, 0.4334498464263360,
                  0.4334498464263360, 0.4334498464263360, 0.0665501535736640, 0.0665501535736640, 0.0665501535736640 },
            };
            return aIntegrationPoints;
          }

//------------------------------------------------------------------------------

            template<>
            Matrix< DDRMat >
            Integration_Coeffs<
                Integration_Type::GAUSS,
                Integration_Order::TET_15>::get_weights()
            {
                Matrix< DDRMat > aWeights =
                {
                    { 0.1817020685825351/6, 0.0361607142857143/6, 0.0361607142857143/6, 0.0361607142857143/6, 0.0361607142857143/6,
                      0.0698714945161738/6, 0.0698714945161738/6, 0.0698714945161738/6, 0.0698714945161738/6, 0.0656948493683187/6,
                      0.0656948493683187/6, 0.0656948493683187/6, 0.0656948493683187/6, 0.0656948493683187/6, 0.0656948493683187/6 }
                };
                return aWeights;
            }

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */
#endif /* SRC_FEM_CL_FEM_INTEGRATION_COEFFS_TET_15_HPP_ */
