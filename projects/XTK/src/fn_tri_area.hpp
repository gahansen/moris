/*
 * fn_tri_area.hpp
 *
 *  Created on: Mar 21, 2019
 *      Author: doble
 */

#ifndef PROJECTS_XTK_SRC_TOOLS_FN_TRI_AREA_HPP_
#define PROJECTS_XTK_SRC_TOOLS_FN_TRI_AREA_HPP_

#include "cl_Matrix.hpp"
#include "fn_cross.hpp"
#include "fn_norm.hpp"
#include "op_div.hpp"
using namespace moris;
namespace xtk
{

inline
moris::real
area_tri(moris::Matrix< moris::DDRMat >  & aCoords)
{
    MORIS_ASSERT(aCoords.n_rows() == 3," triangle needs three node coordinates");

    Matrix<DDRMat> tABVec = aCoords.get_row(0) - aCoords.get_row(1);
    Matrix<DDRMat> tACVec = aCoords.get_row(0) - aCoords.get_row(2);

    return norm(cross(tABVec,tACVec))/2;
}

inline
moris::real
area_tri_2D(moris::Matrix< moris::DDRMat >  & aCoords)
{
    MORIS_ASSERT(aCoords.n_rows() == 3," triangle needs three node coordinates");

    Matrix<DDRMat> tABVec = aCoords.get_row(0) - aCoords.get_row(1);
    Matrix<DDRMat> tACVec = aCoords.get_row(0) - aCoords.get_row(2);

    return std::abs(tABVec(0,0)*tACVec(0,1) - tABVec(0,1)*tACVec(0,0))/2;
}
}


#endif /* PROJECTS_XTK_SRC_TOOLS_FN_TRI_AREA_HPP_ */