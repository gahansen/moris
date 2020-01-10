/*
 * cl_MTK_Cell_Info_Quad4.hpp
 *
 *  Created on: Aug 5, 2019
 *      Author: ryan
 */

#ifndef PROJECTS_MTK_SRC_CL_MTK_QUAD4_CELL_INFO_HPP_
#define PROJECTS_MTK_SRC_CL_MTK_QUAD4_CELL_INFO_HPP_

#include "cl_Cell.hpp"
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_MTK_Cell_Info.hpp"



namespace moris
{
namespace mtk
{
class Cell_Info_Quad4 : public mtk::Cell_Info
{
public:

    enum Geometry_Type
    get_cell_geometry() const;
    // ----------------------------------------------------------------------------------
    enum Interpolation_Order
    get_cell_interpolation_order() const;
    // ----------------------------------------------------------------------------------
    uint
    get_num_verts() const;
    // ----------------------------------------------------------------------------------
    uint
    get_num_facets() const;
    // ----------------------------------------------------------------------------------
    uint
    get_num_verts_per_facet() const;
    // ----------------------------------------------------------------------------------
    moris::Matrix<moris::IndexMat>
    get_node_to_face_map() const;
    // ----------------------------------------------------------------------------------
    moris::Matrix<moris::IndexMat>
    get_node_to_edge_map() const;
    // ----------------------------------------------------------------------------------
    moris::Matrix<moris::IndexMat>
    get_node_to_facet_map() const;
    // ----------------------------------------------------------------------------------
    moris::Matrix<moris::IndexMat>
    get_node_to_face_map(moris::uint aSideOrdinal) const;
    // ----------------------------------------------------------------------------------
    moris::Matrix<moris::IndexMat>
    get_node_to_edge_map(moris::uint aEdgeOrdinal) const;
    // ----------------------------------------------------------------------------------
    moris::Matrix<moris::IndexMat>
    get_node_to_facet_map(moris::uint aSideOrdinal) const;
    // ----------------------------------------------------------------------------------
    moris::Matrix<moris::IndexMat>
    get_node_map_outward_normal(moris::uint aSideOrdinal) const;
    // ----------------------------------------------------------------------------------
    moris::real
    compute_cell_size( moris::mtk::Cell const * aCell ) const;
};
}
}

#endif /* PROJECTS_MTK_SRC_CL_MTK_QUAD4_CELL_INFO_HPP_ */

