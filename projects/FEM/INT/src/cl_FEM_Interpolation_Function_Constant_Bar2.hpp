/*
 * cl_FEM_Interpolation_Function_Constant_Bar2.hpp
 *
 *  Created on: Mar 01, 2019
 *      Author: noel
 */

#ifndef SRC_FEM_CL_FEM_INTERPOLATION_FUNCTION_CONSTANT_BAR2_HPP_
#define SRC_FEM_CL_FEM_INTERPOLATION_FUNCTION_CONSTANT_BAR2_HPP_

#include "assert.h"

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
    Interpolation_Function< Interpolation_Type::CONSTANT, 1, 1 >::get_interpolation_order() const
    {
        return mtk::Interpolation_Order::CONSTANT;
    }

//------------------------------------------------------------------------------

    template<>
    Matrix< DDRMat >
    Interpolation_Function< Interpolation_Type::CONSTANT, 1, 1 >::get_param_coords() const
    {
        Matrix< DDRMat > tXiHat(1,2);
        tXiHat( 0 ) = -1.000000;
        tXiHat( 1 ) =  1.000000;
        return tXiHat;
    }

//------------------------------------------------------------------------------

        template<>
        Matrix < DDRMat >
        Interpolation_Function< Interpolation_Type::CONSTANT, 1, 1  >::eval_N(
                const Matrix< DDRMat > & aXi ) const
        {
            // make sure that input is correct
            MORIS_ASSERT( aXi.length() >= 1, "eval_N: aXi not allocated or hat wrong size." );

            Matrix< DDRMat > tN(1,1);
            tN( 0 ) = 1.0;
            return tN;
        }

//------------------------------------------------------------------------------

        template<>
        Matrix < DDRMat >
        Interpolation_Function< Interpolation_Type::CONSTANT, 1, 1 >::eval_dNdXi( const Matrix< DDRMat > & aXi ) const
        {
            // make sure that input is correct
            MORIS_ASSERT( aXi.length() >= 1,
                          "eval_dNdXi: aXi not allocated or hat wrong size." );

            Matrix< DDRMat > tdNdXi(1,1);
            tdNdXi( 0 ) = 0.0;
            return tdNdXi;
        }

//------------------------------------------------------------------------------

        template<>
        Matrix< DDRMat >
        Interpolation_Function< Interpolation_Type::CONSTANT, 1, 1  >::eval_d2NdXi2( const Matrix< DDRMat > & aXi ) const
        {
            // make sure that input is correct
            MORIS_ASSERT( aXi.length() >= 1,
                          "ad2NdXi2: aXi not allocated or hat wrong size." );

            Matrix< DDRMat > td2NdXi2(1,1);
            td2NdXi2( 0 ) =  0.0;
            return td2NdXi2;
        }

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

//------------------------------------------------------------------------------
#endif /* SRC_FEM_CL_FEM_INTERPOLATION_FUNCTION_CONSTANT_BAR2_HPP_ */
