/*
 * cl_FEM_Interpolation_Function_Quad16.hpp
 *
 *  Created on: Jul 9, 2018
 *      Author: messe
 */

#ifndef SRC_FEM_CL_FEM_INTERPOLATION_FUNCTION_LAGRANGE_QUAD16_HPP_
#define SRC_FEM_CL_FEM_INTERPOLATION_FUNCTION_LAGRANGE_QUAD16_HPP_

#include "assert.h"

//#include "cl_FEM_Interpolation_Matrix.hpp"
#include "typedefs.hpp" //MRS/COR/src
#include "cl_FEM_Enums.hpp" //FEM/INT/src
#include "cl_FEM_Interpolation_Function.hpp" //FEM/INT/src

namespace moris
{
    namespace fem
    {

//------------------------------------------------------------------------------

        template<>
        mtk::Interpolation_Order
        Interpolation_Function< Interpolation_Type::LAGRANGE, 2, 16 >::get_interpolation_order() const
        {
            return mtk::Interpolation_Order::CUBIC;
        }

//------------------------------------------------------------------------------

        template<>
        Matrix< DDRMat >
        Interpolation_Function< Interpolation_Type::LAGRANGE, 2, 16 >::get_param_coords() const
        {
            Matrix< DDRMat > tXiHat( 2, 16 );
            real c = 1.0/3.0;
            tXiHat( 0,  0 ) = -1.000000;
            tXiHat( 1,  0 ) = -1.000000;
            tXiHat( 0,  1 ) =  1.000000;
            tXiHat( 1,  1 ) = -1.000000;
            tXiHat( 0,  2 ) =  1.000000;
            tXiHat( 1,  2 ) =  1.000000;
            tXiHat( 0,  3 ) = -1.000000;
            tXiHat( 1,  3 ) =  1.000000;
            tXiHat( 0,  4 ) = -c;
            tXiHat( 1,  4 ) = -1.000000;
            tXiHat( 0,  5 ) =  c;
            tXiHat( 1,  5 ) = -1.000000;
            tXiHat( 0,  6 ) =  1.000000;
            tXiHat( 1,  6 ) = -c;
            tXiHat( 0,  7 ) =  1.000000;
            tXiHat( 1,  7 ) =  c;
            tXiHat( 0,  8 ) =  c;
            tXiHat( 1,  8 ) =  1.000000;
            tXiHat( 0,  9 ) = -c;
            tXiHat( 1,  9 ) =  1.000000;
            tXiHat( 0, 10 ) = -1.000000;
            tXiHat( 1, 10 ) =  c;
            tXiHat( 0, 11 ) = -1.000000;
            tXiHat( 1, 11 ) = -c;
            tXiHat( 0, 12 ) = -c;
            tXiHat( 1, 12 ) = -c;
            tXiHat( 0, 13 ) =  c;
            tXiHat( 1, 13 ) = -c;
            tXiHat( 0, 14 ) =  c;
            tXiHat( 1, 14 ) =  c;
            tXiHat( 0, 15 ) = -c;
            tXiHat( 1, 15 ) =  c;
            return tXiHat;
        }

//------------------------------------------------------------------------------

        template<>
        Matrix < DDRMat >
        Interpolation_Function< Interpolation_Type::LAGRANGE, 2, 16 >::eval_N(const Matrix< DDRMat > & aXi ) const
        {
            // make sure that input is correct
            MORIS_ASSERT( aXi.length() >= 2,
                    "eval_shape: aXi not allocated or hat wrong size." );

            // unpack xi and eta from input vector
            auto  xi = aXi( 0 );
            auto eta = aXi( 1 );

            real a0 =  ( xi*( 1.0 + 9.0 * xi * ( 1.0 - xi ) ) - 1.0 )*0.0625;
            real a1 =  ( 9.0 - xi * ( 27.0 + xi*( 9.0 - 27.0*xi ) ) )*0.0625;
            real a2 =  ( 9.0 + xi * ( 27.0 - xi*( 9.0 + 27.0*xi ) ) )*0.0625;
            real a3 = ( -xi*( 1.0 - 9.0 * xi * ( 1.0 + xi ) ) - 1.0 )*0.0625;

            real b0 =  ( eta*( 1.0 + 9.0 * eta * ( 1.0 - eta ) ) - 1.0 )*0.0625;
            real b1 =  ( 9.0 - eta * ( 27.0 + eta*( 9.0 - 27.0*eta ) ) )*0.0625;
            real b2 =  ( 9.0 + eta * ( 27.0 - eta*( 9.0 + 27.0*eta ) ) )*0.0625;
            real b3 = ( -eta*( 1.0 - 9.0 * eta * ( 1.0 + eta ) ) - 1.0 )*0.0625;

            // populate matrix with values
            Matrix< DDRMat > tN(1,16);
            tN(  0 ) = a0*b0;
            tN(  1 ) = a3*b0;
            tN(  2 ) = a3*b3;
            tN(  3 ) = a0*b3;
            tN(  4 ) = a1*b0;
            tN(  5 ) = a2*b0;
            tN(  6 ) = a3*b1;
            tN(  7 ) = a3*b2;
            tN(  8 ) = a2*b3;
            tN(  9 ) = a1*b3;
            tN( 10 ) = a0*b2;
            tN( 11 ) = a0*b1;
            tN( 12 ) = a1*b1;
            tN( 13 ) = a2*b1;
            tN( 14 ) = a2*b2;
            tN( 15 ) = a1*b2;
            return tN;

        }

//------------------------------------------------------------------------------

        template<>
        Matrix< DDRMat >
        Interpolation_Function< Interpolation_Type::LAGRANGE, 2, 16 >::eval_dNdXi( const Matrix< DDRMat > & aXi ) const
        {
            // make sure that input is correct
            MORIS_ASSERT( aXi.length() >= 2,
                    "eval_shape: aXi not allocated or hat wrong size." );

            // unpack xi and eta from input vector
            auto  xi = aXi( 0 );
            auto eta = aXi( 1 );

            // often used parameters
            real a0 =  ( xi*( 1.0 + 9.0 * xi * ( 1.0 - xi ) ) - 1.0 ) * 0.0625;
            real a1 =  ( 9.0 - xi * ( 27.0 + xi*( 9.0 - 27.0*xi ) ) ) * 0.0625;
            real a2 =  ( 9.0 + xi * ( 27.0 - xi*( 9.0 + 27.0*xi ) ) ) * 0.0625;
            real a3 = ( -xi*( 1.0 - 9.0 * xi * ( 1.0 + xi ) ) - 1.0 ) * 0.0625;

            real b0 =  ( eta*( 1.0 + 9.0 * eta * ( 1.0 - eta ) ) - 1.0 ) * 0.0625;
            real b1 =  ( 9.0 - eta * ( 27.0 + eta*( 9.0 - 27.0*eta ) ) ) * 0.0625;
            real b2 =  ( 9.0 + eta * ( 27.0 - eta*( 9.0 + 27.0*eta ) ) ) * 0.0625;
            real b3 = ( -eta*( 1.0 - 9.0 * eta * ( 1.0 + eta ) ) - 1.0 ) * 0.0625;

            real da0 = (   1.0 + xi*( 18.0 - 27.0*xi )) * 0.0625;
            real da1 = ( -27.0 - xi*( 18.0 - 81.0*xi )) * 0.0625;
            real da2 = (  27.0 - xi*( 18.0 + 81.0*xi )) * 0.0625;
            real da3 = (  -1.0 + xi*( 18.0 + 27.0*xi )) * 0.0625;

            real db0 = (   1.0 + eta*( 18.0 - 27.0*eta )) * 0.0625;
            real db1 = ( -27.0 - eta*( 18.0 - 81.0*eta )) * 0.0625;
            real db2 = (  27.0 - eta*( 18.0 + 81.0*eta )) * 0.0625;
            real db3 = (  -1.0 + eta*( 18.0 + 27.0*eta )) * 0.0625;

            // populate output matrix
            Matrix< DDRMat > tdNdXi(2,16);
            tdNdXi( 0,  0 ) = da0*b0;
            tdNdXi( 1,  0 ) = a0*db0;

            tdNdXi( 0,  1 ) = da3*b0;
            tdNdXi( 1,  1 ) = a3*db0;

            tdNdXi( 0,  2 ) = da3*b3;
            tdNdXi( 1,  2 ) = a3*db3;

            tdNdXi( 0,  3 ) = da0*b3;
            tdNdXi( 1,  3 ) = a0*db3;

            tdNdXi( 0,  4 ) = da1*b0;
            tdNdXi( 1,  4 ) = a1*db0;

            tdNdXi( 0,  5 ) = da2*b0;
            tdNdXi( 1,  5 ) = a2*db0;

            tdNdXi( 0,  6 ) = da3*b1;
            tdNdXi( 1,  6 ) = a3*db1;

            tdNdXi( 0,  7 ) = da3*b2;
            tdNdXi( 1,  7 ) = a3*db2;

            tdNdXi( 0,  8 ) = da2*b3;
            tdNdXi( 1,  8 ) = a2*db3;

            tdNdXi( 0,  9 ) = da1*b3;
            tdNdXi( 1,  9 ) = a1*db3;

            tdNdXi( 0, 10 ) = da0*b2;
            tdNdXi( 1, 10 ) = a0*db2;

            tdNdXi( 0, 11 ) = da0*b1;
            tdNdXi( 1, 11 ) = a0*db1;

            tdNdXi( 0, 12 ) = da1*b1;
            tdNdXi( 1, 12 ) = a1*db1;

            tdNdXi( 0, 13 ) = da2*b1;
            tdNdXi( 1, 13 ) = a2*db1;

            tdNdXi( 0, 14 ) = da2*b2;
            tdNdXi( 1, 14 ) = a2*db2;

            tdNdXi( 0, 15 ) = da1*b2;
            tdNdXi( 1, 15 ) = a1*db2;
            return tdNdXi;
        }

//------------------------------------------------------------------------------

        template<>
        Matrix< DDRMat >
        Interpolation_Function< Interpolation_Type::LAGRANGE, 2, 16 >::eval_d2NdXi2( const Matrix< DDRMat > & aXi ) const
        {

            // make sure that input is correct
            MORIS_ASSERT( aXi.length() >= 2,
                    "eval_shape: aXi not allocated or hat wrong size." );

            // unpack xi and eta from input vector
            auto  xi = aXi( 0 );
            auto eta = aXi( 1 );

            // often used parameters
            real a0 =  ( xi*( 1.0 + 9.0 * xi * ( 1.0 - xi ) ) - 1.0 ) * 0.0625;
            real a1 =  ( 9.0 - xi * ( 27.0 + xi*( 9.0 - 27.0*xi ) ) ) * 0.0625;
            real a2 =  ( 9.0 + xi * ( 27.0 - xi*( 9.0 + 27.0*xi ) ) ) * 0.0625;
            real a3 = ( -xi*( 1.0 - 9.0 * xi * ( 1.0 + xi ) ) - 1.0 ) * 0.0625;

            real b0 =  ( eta*( 1.0 + 9.0 * eta * ( 1.0 - eta ) ) - 1.0 ) * 0.0625;
            real b1 =  ( 9.0 - eta * ( 27.0 + eta*( 9.0 - 27.0*eta ) ) ) * 0.0625;
            real b2 =  ( 9.0 + eta * ( 27.0 - eta*( 9.0 + 27.0*eta ) ) ) * 0.0625;
            real b3 = ( -eta*( 1.0 - 9.0 * eta * ( 1.0 + eta ) ) - 1.0 ) * 0.0625;

            real da0 = (   1.0 + xi*( 18.0 - 27.0*xi )) * 0.0625;
            real da1 = ( -27.0 - xi*( 18.0 - 81.0*xi )) * 0.0625;
            real da2 = (  27.0 - xi*( 18.0 + 81.0*xi )) * 0.0625;
            real da3 = (  -1.0 + xi*( 18.0 + 27.0*xi )) * 0.0625;

            real dda0 = ( 18.0 - 54.0*xi ) * 0.0625;
            real dda1 = ( 162.0*xi - 18.0 ) * 0.0625;
            real dda2 = ( - 162.0*xi - 18.0 ) * 0.0625;
            real dda3 = ( 54.0*xi + 18.0 ) * 0.0625;

            real db0 = (   1.0 + eta*( 18.0 - 27.0*eta )) * 0.0625;
            real db1 = ( -27.0 - eta*( 18.0 - 81.0*eta )) * 0.0625;
            real db2 = (  27.0 - eta*( 18.0 + 81.0*eta )) * 0.0625;
            real db3 = (  -1.0 + eta*( 18.0 + 27.0*eta )) * 0.0625;

            real ddb0 = ( 18.0 - 54.0*eta ) * 0.0625;
            real ddb1 = ( 162.0*eta - 18.0 ) * 0.0625;
            real ddb2 = ( - 162.0*eta - 18.0 ) * 0.0625;
            real ddb3 = ( 54.0*eta + 18.0 ) * 0.0625;

            Matrix< DDRMat > td2NdXi2(3,16);
            td2NdXi2( 0,   0 ) = dda0*b0;
            td2NdXi2( 1,   0 ) = a0*ddb0;
            td2NdXi2( 2,   0 ) = da0*db0;

            td2NdXi2( 0,   1 ) = dda3*b0;
            td2NdXi2( 1,   1 ) = a3*ddb0;
            td2NdXi2( 2,   1 ) = da3*db0;

            td2NdXi2( 0,   2 ) = dda3*b3;
            td2NdXi2( 1,   2 ) = a3*ddb3;
            td2NdXi2( 2,   2 ) = da3*db3;

            td2NdXi2( 0,   3 ) = dda0*b3;
            td2NdXi2( 1,   3 ) = a0*ddb3;
            td2NdXi2( 2,   3 ) = da0*db3;

            td2NdXi2( 0,   4 ) = dda1*b0;
            td2NdXi2( 1,   4 ) = a1*ddb0;
            td2NdXi2( 2,   4 ) = da1*db0;

            td2NdXi2( 0,   5 ) = dda2*b0;
            td2NdXi2( 1,   5 ) = a2*ddb0;
            td2NdXi2( 2,   5 ) = da2*db0;

            td2NdXi2( 0,   6 ) = dda3*b1;
            td2NdXi2( 1,   6 ) = a3*ddb1;
            td2NdXi2( 2,   6 ) = da3*db1;

            td2NdXi2( 0,   7 ) = dda3*b2;
            td2NdXi2( 1,   7 ) = a3*ddb2;
            td2NdXi2( 2,   7 ) = da3*db2;

            td2NdXi2( 0,   8 ) = dda2*b3;
            td2NdXi2( 1,   8 ) = a2*ddb3;
            td2NdXi2( 2,   8 ) = da2*db3;

            td2NdXi2( 0,   9 ) = dda1*b3;
            td2NdXi2( 1,   9 ) = a1*ddb3;
            td2NdXi2( 2,   9 ) = da1*db3;

            td2NdXi2( 0,  10 ) = dda0*b2;
            td2NdXi2( 1,  10 ) = a0*ddb2;
            td2NdXi2( 2,  10 ) = da0*db2;

            td2NdXi2( 0,  11 ) = dda0*b1;
            td2NdXi2( 1,  11 ) = a0*ddb1;
            td2NdXi2( 2,  11 ) = da0*db1;

            td2NdXi2( 0,  12 ) = dda1*b1;
            td2NdXi2( 1,  12 ) = a1*ddb1;
            td2NdXi2( 2,  12 ) = da1*db1;

            td2NdXi2( 0,  13 ) = dda2*b1;
            td2NdXi2( 1,  13 ) = a2*ddb1;
            td2NdXi2( 2,  13 ) = da2*db1;

            td2NdXi2( 0,  14 ) = dda2*b2;
            td2NdXi2( 1,  14 ) = a2*ddb2;
            td2NdXi2( 2,  14 ) = da2*db2;

            td2NdXi2( 0,  15 ) = dda1*b2;
            td2NdXi2( 1,  15 ) = a1*ddb2;
            td2NdXi2( 2,  15 ) = da1*db2;
            return td2NdXi2;

        }

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */
#endif /* SRC_FEM_CL_FEM_INTERPOLATION_FUNCTION_LAGRANGE_QUAD16_HPP_ */
