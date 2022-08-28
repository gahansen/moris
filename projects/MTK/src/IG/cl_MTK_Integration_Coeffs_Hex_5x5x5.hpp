/*
 * Copyright (c) 2022 University of Colorado
 * Licensed under the MIT license. See LICENSE.txt file in the MORIS root for details.
 *
 *------------------------------------------------------------------------------------
 *
 * cl_MTK_Integration_Coeffs_Hex_5x5x5.hpp
 *
 */

#ifndef SRC_MTK_CL_MTK_INTEGRATION_COEFFS_HEX_5x5x5_HPP_
#define SRC_MTK_CL_MTK_INTEGRATION_COEFFS_HEX_5x5x5_HPP_

#include "cl_MTK_Integration_Coeffs.hpp"
#include "typedefs.hpp" //MRS/COR/src
#include "cl_Matrix.hpp" //LNA/src
#include "linalg_typedefs.hpp" //LNA/src
#include "cl_MTK_Enums.hpp" //MTK/src

namespace moris
{
    namespace mtk
    {
//------------------------------------------------------------------------------

        template<>
        uint
        Integration_Coeffs<
        Integration_Type::GAUSS,
        Integration_Order::HEX_5x5x5>::get_number_of_dimensions()
        {
            return 3;
        }

//------------------------------------------------------------------------------

        template<>
        uint
        Integration_Coeffs<
            Integration_Type::GAUSS,
            Integration_Order::HEX_5x5x5>::get_number_of_points()
            {
                return 125;
            }

//------------------------------------------------------------------------------

        template<>
        void
        Integration_Coeffs<
                Integration_Type::GAUSS,
                Integration_Order::HEX_5x5x5>::get_points( Matrix< DDRMat > & aIntegrationPoints )
        {
            aIntegrationPoints =
            {
                {
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                     0.0,
                     5.384693101056830e-01,
                     9.061798459386640e-01
                     },
                     {-9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                 },
                 {
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -9.061798459386640e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                    -5.384693101056830e-01,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     0.0,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     5.384693101056830e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                     9.061798459386640e-01,
                 }
            };
          }

//------------------------------------------------------------------------------

            template<>
            void
            Integration_Coeffs<
                Integration_Type::GAUSS,
                Integration_Order::HEX_5x5x5 >::get_weights( Matrix< DDRMat > & aIntegrationWeights )
            {
                aIntegrationWeights =
                {
                    {
                        1.329973642063265e-02,
                        2.686750876537184e-02,
                        3.193420735284829e-02,
                        2.686750876537184e-02,
                        1.329973642063265e-02,
                        2.686750876537184e-02,
                        5.427649123462816e-02,
                        6.451200000000000e-02,
                        5.427649123462816e-02,
                        2.686750876537184e-02,
                        3.193420735284829e-02,
                        6.451200000000000e-02,
                        7.667773006934522e-02,
                        6.451200000000000e-02,
                        3.193420735284829e-02,
                        2.686750876537184e-02,
                        5.427649123462816e-02,
                        6.451200000000000e-02,
                        5.427649123462816e-02,
                        2.686750876537184e-02,
                        1.329973642063265e-02,
                        2.686750876537184e-02,
                        3.193420735284829e-02,
                        2.686750876537184e-02,
                        1.329973642063265e-02,
                        2.686750876537184e-02,
                        5.427649123462816e-02,
                        6.451200000000000e-02,
                        5.427649123462816e-02,
                        2.686750876537184e-02,
                        5.427649123462816e-02,
                        1.096468424545388e-01,
                        1.303241410696483e-01,
                        1.096468424545388e-01,
                        5.427649123462816e-02,
                        6.451200000000000e-02,
                        1.303241410696483e-01,
                        1.549007829622049e-01,
                        1.303241410696483e-01,
                        6.451200000000000e-02,
                        5.427649123462816e-02,
                        1.096468424545388e-01,
                        1.303241410696483e-01,
                        1.096468424545388e-01,
                        5.427649123462816e-02,
                        2.686750876537184e-02,
                        5.427649123462816e-02,
                        6.451200000000000e-02,
                        5.427649123462816e-02,
                        2.686750876537184e-02,
                        3.193420735284829e-02,
                        6.451200000000000e-02,
                        7.667773006934522e-02,
                        6.451200000000000e-02,
                        3.193420735284829e-02,
                        6.451200000000000e-02,
                        1.303241410696483e-01,
                        1.549007829622048e-01,
                        1.303241410696483e-01,
                        6.451200000000000e-02,
                        7.667773006934522e-02,
                        1.549007829622048e-01,
                        1.841121097393690e-01,
                        1.549007829622048e-01,
                        7.667773006934522e-02,
                        6.451200000000000e-02,
                        1.303241410696483e-01,
                        1.549007829622048e-01,
                        1.303241410696483e-01,
                        6.451200000000000e-02,
                        3.193420735284829e-02,
                        6.451200000000000e-02,
                        7.667773006934522e-02,
                        6.451200000000000e-02,
                        3.193420735284829e-02,
                        2.686750876537184e-02,
                        5.427649123462816e-02,
                        6.451200000000000e-02,
                        5.427649123462816e-02,
                        2.686750876537184e-02,
                        5.427649123462816e-02,
                        1.096468424545388e-01,
                        1.303241410696483e-01,
                        1.096468424545388e-01,
                        5.427649123462816e-02,
                        6.451200000000000e-02,
                        1.303241410696483e-01,
                        1.549007829622049e-01,
                        1.303241410696483e-01,
                        6.451200000000000e-02,
                        5.427649123462816e-02,
                        1.096468424545388e-01,
                        1.303241410696483e-01,
                        1.096468424545388e-01,
                        5.427649123462816e-02,
                        2.686750876537184e-02,
                        5.427649123462816e-02,
                        6.451200000000000e-02,
                        5.427649123462816e-02,
                        2.686750876537184e-02,
                        1.329973642063265e-02,
                        2.686750876537184e-02,
                        3.193420735284829e-02,
                        2.686750876537184e-02,
                        1.329973642063265e-02,
                        2.686750876537184e-02,
                        5.427649123462816e-02,
                        6.451200000000000e-02,
                        5.427649123462816e-02,
                        2.686750876537184e-02,
                        3.193420735284829e-02,
                        6.451200000000000e-02,
                        7.667773006934522e-02,
                        6.451200000000000e-02,
                        3.193420735284829e-02,
                        2.686750876537184e-02,
                        5.427649123462816e-02,
                        6.451200000000000e-02,
                        5.427649123462816e-02,
                        2.686750876537184e-02,
                        1.329973642063265e-02,
                        2.686750876537184e-02,
                        3.193420735284829e-02,
                        2.686750876537184e-02,
                        1.329973642063265e-02
                    }
                };
            }

//------------------------------------------------------------------------------
    } /* namespace mtk */
} /* namespace moris */
#endif /* SRC_MTK_CL_MTK_INTEGRATION_COEFFS_HEX_5X5X5_HPP_ */
