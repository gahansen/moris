/*
 * op_greater_equal.hpp
 *
 *  Created on: Aug 31, 2018
 *      Author: doble
 */

#ifndef PROJECTS_LINALG_SRC_OP_GREATER_EQUAL_HPP_
#define PROJECTS_LINALG_SRC_OP_GREATER_EQUAL_HPP_


#ifdef MORIS_USE_EIGEN
#include "Eigen_Impl/op_greater_equal_Eigen.hpp"
#endif

#ifdef MORIS_USE_ARMA
#include "Arma_Impl/op_greater_equal_Arma.hpp"
#endif

namespace moris
{
/**
 * @brief Determine greater than or equal to
 *
 * @param[in] aA Input matrix
 * @param[in] aB Input matrix
 *
 * This function checks if @f$ \mathbf{A}_{ij} \geq \mathbf{B}_{ij} @f$. It returns a
 * logical matrix with elements set to logical 1 (true) where A is greater than or
 * equal to B; otherwise, it returns logical 0 (false).
 *
 * Example:
 * @include LNA/src/op_greater_equal.inc
 *
 */
    template< typename Matrix_Type >
    auto
    operator>=(
            Matrix< Matrix_Type > const & aA,
            Matrix< Matrix_Type > const & aB )
    ->decltype( operator>=( aA.matrix_data(), aB.matrix_data() ) )
    {
        return operator>=( aA.matrix_data(), aB.matrix_data() );
    }

    template< typename Matrix_Type >
    auto
    operator>=(
            Matrix< Matrix_Type > & aA,
            Matrix< Matrix_Type > & aB )
    ->decltype( operator>=( aA.matrix_data(), aB.matrix_data() ) )
    {
        return operator>=( aA.matrix_data(), aB.matrix_data() );
    }

    template< typename Matrix_Type >
    auto
    operator>=( typename Matrix< Matrix_Type >::Data_Type aA,
                         Matrix< Matrix_Type > &          aB )
    ->decltype( operator>=( aA, aB.matrix_data() ) )
    {
        return operator>=( aA, aB.matrix_data() );
    }

    template< typename Matrix_Type >
    auto
    operator>=(          Matrix< Matrix_Type > & aA,
                typename Matrix< Matrix_Type >::Data_Type aB)
    ->decltype( operator>=( aA.matrix_data(), aB ) )
    {

        return operator>=( aA.matrix_data(), aB );
    }

}


#endif /* PROJECTS_LINALG_SRC_OP_GREATER_EQUAL_HPP_ */
