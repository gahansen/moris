/*
 * op_greater.hpp
 *
 *  Created on: Aug 31, 2018
 *      Author: doble
 */

#ifndef PROJECTS_LINALG_SRC_ARMA_IMPL_OP_GREATER_ARMA_HPP_
#define PROJECTS_LINALG_SRC_ARMA_IMPL_OP_GREATER_ARMA_HPP_


namespace moris
{
template< typename Matrix_Type, typename T1, typename ET >
auto
operator>( const arma::eOp<T1, ET> &  aA,
           Matrix< Matrix_Type > & aB )
->decltype( aA > aB.matrix_data() )
{
    return  aA > aB.matrix_data();
}

template< typename Matrix_Type, typename T1, typename ET >
auto
operator>( Matrix< Matrix_Type > & aA,
           const arma::eOp<T1, ET> &  aB)
->decltype( aA.matrix_data()  > aB )
{
    return  aA.matrix_data() > aB;
}
}


#endif /* PROJECTS_LINALG_SRC_ARMA_IMPL_OP_GREATER_ARMA_HPP_ */
