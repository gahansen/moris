/*
 * cl_FEM_Integration_Coeffs_Hex_5x5x5.hpp
 *
 *  Created on: Jul 19, 2018
 *      Author: messe
 */

#ifndef SRC_FEM_CL_FEM_INTEGRATION_COEFFS_HEX_5x5x5_HPP_
#define SRC_FEM_CL_FEM_INTEGRATION_COEFFS_HEX_5x5x5_HPP_

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
    } /* namespace fem */
} /* namespace moris */
#endif /* SRC_FEM_CL_FEM_INTEGRATION_COEFFS_HEX_5X5X5_HPP_ */
