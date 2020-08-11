/*
 * ut_MTK_Cell_Info_Hex27.cpp
 *
 *  Created on: Aug 7, 2020
 *      Author: kedo3694
 */
#include "catch.hpp"
#include "cl_MTK_Cell_Info.hpp"
#include "cl_MTK_Cell_Info_Hex27.hpp"
#include "cl_Matrix.hpp"
#include "fn_norm.hpp"
namespace moris
{

TEST_CASE("MTK Hex27 Cell Info","[HEX_27]")
{
    moris::real tEps = 1e-8;

    // construct a Hex27 info
    mtk::Cell_Info_Hex27 tHex27ConnInfo;

    CHECK(tHex27ConnInfo.get_num_verts() == 27);

    // matrix for shape functions
    Matrix<DDRMat> tN;

    for(moris::uint i = 0; i < tHex27ConnInfo.get_num_verts(); i++)
    {

        Matrix<DDRMat> tCoords = tHex27ConnInfo.get_vertex_loc_coord((moris_index)i);

        tHex27ConnInfo.eval_N(tCoords,tN);


        CHECK(std::abs(tN(i)) - 1.0 < tEps);
        CHECK(moris::norm(tN) - 1.0 < tEps);

    }

}


}