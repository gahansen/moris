/*
 * fn_isempty_Eigen.hpp
 *
 *  Created on: Aug 29, 2018
 *      Author: schmidt
 */

#ifndef PROJECTS_LINALG_SRC_EIGEN_IMPL_FN_ISEMPTY_EIGEN_HPP_
#define PROJECTS_LINALG_SRC_EIGEN_IMPL_FN_ISEMPTY_EIGEN_HPP_
#include <Eigen/Dense>

namespace moris
{
    template< typename ET >
    bool
    isempty( const Eigen::MatrixBase<ET> & aA )
    {
        // If either of the dimensions is zero, then the matrix is empty
        // Note: eigen returns a matrix [0x1] or [1x0] if is empty.
        if ( aA.rows() == 0 || aA.cols() == 0 )
        {
            return true;
        }
        return false;
    }
}



#endif /* PROJECTS_LINALG_SRC_EIGEN_IMPL_FN_ISEMPTY_EIGEN_HPP_ */