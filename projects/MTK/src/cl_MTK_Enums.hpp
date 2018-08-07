/*
 * cl_MTK_Enums.hpp
 *
 *  Created on: Jul 25, 2018
 *      Author: messe
 */

#ifndef SRC_MESH_CL_MTK_ENUMS_HPP_
#define SRC_MESH_CL_MTK_ENUMS_HPP_

//------------------------------------------------------------------------------
namespace moris
{
    namespace mtk
    {
//------------------------------------------------------------------------------

        enum class Geometry_Type
        {
            UNDEFINED,
            BAR,  // 1D line or curve
            QUAD,  // rectangle
            TRI,   // triangle
            HEX,   // quadrangle
            TET,   // tetrahedron
            PENTA  // pentahedron
        };

//------------------------------------------------------------------------------

        enum class Interpolation_Order
        {
            UNDEFINED,
            CONSTANT,
            LINEAR,
            QUADRATIC,
            SERENDIPITY,
            CUBIC
        };

//------------------------------------------------------------------------------
    } /* namespace mtk */
} /* namespace moris */


#endif /* SRC_MESH_CL_MTK_ENUMS_HPP_ */
