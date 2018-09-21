/*
 * fn_eig_gen_Eigen.hpp
 *
 *  Created on: Aug 29, 2018
 *      Author: schmidt
 */

#ifndef PROJECTS_LINALG_SRC_EIGEN_IMPL_FN_EIG_GEN_EIGEN_HPP_
#define PROJECTS_LINALG_SRC_EIGEN_IMPL_FN_EIG_GEN_EIGEN_HPP_
#include <Eigen/Dense>

namespace moris
{
    template< typename ET1, typename ET2, typename ET3 >
    void
    eig_gen(       Eigen::MatrixBase< ET1 > & aEigenValues,
                   Eigen::MatrixBase< ET2 > & aEigenVectors,
             const Eigen::MatrixBase< ET3 > & aA )
    {
        Eigen::SelfAdjointEigenSolver< Eigen::Matrix < moris::cplx, Eigen::Dynamic, Eigen::Dynamic > > eigensolver( aA );

        aEigenValues = eigensolver.eigenvalues();
        aEigenVectors = eigensolver.eigenvectors();
    }
}

#endif /* PROJECTS_LINALG_SRC_EIGEN_IMPL_FN_EIG_GEN_EIGEN_HPP_ */