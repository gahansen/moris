/*
 * LINALG_typedefs.hpp
 *
 *  Created on: Aug 24, 2018
 *      Author: doble
 */

#ifndef PROJECTS_LINALG_SRC_LINALG_TYPEDEFS_HPP_
#define PROJECTS_LINALG_SRC_LINALG_TYPEDEFS_HPP_


#include "typedefs.hpp"
namespace moris
{
/*
 * Each typedef for matrix type has a string of letters which indicate the type of matrix it is.
 * Letters are used here to cut down on the length of the typedef which will be used throughout MORIS
 *
 *
 * DD - Dense Dynamic
 * ST - size_t
 * L  - lint
 * S  - sint
 * U  - uint
 */
#ifdef MORIS_USE_EIGEN
#include "Eigen/Dense"
typedef Eigen::Matrix<real,   Eigen::Dynamic, Eigen::Dynamic>   DDRMat; // Dense dynamic Real Mat
typedef Eigen::Matrix<size_t, Eigen::Dynamic, Eigen::Dynamic>   DDSTMat; // Dense dynamic size_t Mat
typedef Eigen::Matrix<lint,   Eigen::Dynamic, Eigen::Dynamic>   DDLMat;     // Dense dynamic lint Mat
typedef Eigen::Matrix<sint,   Eigen::Dynamic, Eigen::Dynamic>   DDSMat; // Dense dynamic sint  Mat
typedef Eigen::Matrix<uint,   Eigen::Dynamic, Eigen::Dynamic>   DDUMat; // Dense dynamic uint  Mat
typedef Eigen::Matrix<cplx,   Eigen::Dynamic, Eigen::Dynamic>   DDCMat; // Dense dynamic cmplx Mat
typedef Eigen::Matrix<real,                3,              3>   F33RMat; // Fixed 3x3 Real Mat


#else
#include <armadillo>
typedef arma::Mat< real > DDRMat; // Dense dynamic Real Mat
typedef arma::Mat<size_t> DDSTMat; // Dense dynamic size_t Mat
typedef arma::Mat< lint > DDLMat;     // Dense dynamic lint Mat
typedef arma::Mat< sint > DDSMat; // Dense sint size_t Mat
typedef arma::Mat< uint > DDUMat; // Dense uint size_t Mat
typedef arma::Mat< cplx > DDCMat; // Dense dynamic cmplx Mat
typedef arma::Mat< real > F33RMat; // Fixed 3x3 Real Mat (for arma this is the same as DDRMat)
#endif

}
#ifdef MORIS_USE_EIGEN
namespace xtk
{
    typedef Eigen::Matrix<double,   Eigen::Dynamic, Eigen::Dynamic> Default_Matrix_Real;
    typedef Eigen::Matrix<size_t, Eigen::Dynamic, Eigen::Dynamic> Default_Matrix_Integer;
}
#else
namespace xtk
{
    typedef arma::Mat< moris::real > Default_Matrix_Real;
    typedef arma::Mat<moris::size_t> Default_Matrix_Integer;
}
#endif


#endif /* PROJECTS_LINALG_SRC_LINALG_TYPEDEFS_HPP_ */
