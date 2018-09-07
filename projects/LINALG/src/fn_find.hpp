/*
 * fn_find.hpp
 *
 *  Created on: Aug 29, 2018
 *      Author: schmidt
 */

#ifndef PROJECTS_LINALG_SRC_FN_FIND_HPP_
#define PROJECTS_LINALG_SRC_FN_FIND_HPP_

#include "cl_Matrix.hpp"

#ifdef MORIS_USE_EIGEN
#include "Eigen_Impl/fn_trans_Eigen.hpp"
#endif

#ifdef MORIS_USE_ARMA
#include "Arma_Impl/fn_trans_Arma.hpp"
#endif


namespace moris
{
//    /**
//     * @brief Computes transpose of Matrix A.
//     *
//     * @param[in] A Matrix.
//     *
//     * @return The transpose of the Matrix A.
//     *
//     * @note In case of complex numbers, no conjugate is taken.
//     *
//     * Example:
//     * @include LNA/src/fn_trans/trans_real.inc
//     * @include LNA/src/fn_trans/trans_complex.inc
//     */
//    template< typename Type, typename Matrix_Type >
//    auto
//    trans( const Matrix< Type, Matrix_Type > & A )
//    -> decltype( trans(A.matrix_data()) )
//    {
//        return trans(A.matrix_data());
//    }
//
//    template< typename Type, typename Matrix_Type >
//    auto
//    trans( Matrix< Type, Matrix_Type > & A )
//    -> decltype( trans(A.matrix_data()) )
//    {
//        return trans(A.matrix_data());
//    }
}

#endif /* PROJECTS_LINALG_SRC_FN_FIND_HPP_ */
