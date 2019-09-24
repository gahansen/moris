/*
 * cl_MTK_Tri3_CELL_INFO.hpp
 *
 *  Created on: Aug 5, 2019
 *      Author: ryan
 */

#ifndef PROJECTS_MTK_SRC_CL_MTK_TRI3_CELL_INFO_HPP_
#define PROJECTS_MTK_SRC_CL_MTK_TRI3_CELL_INFO_HPP_

#include "cl_Cell.hpp"
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_MTK_Cell_Info.hpp"



namespace moris
{
namespace mtk
{
class Cell_Info_Tri3 : public mtk::Cell_Info
{
public:
    enum Geometry_Type
    get_cell_geometry() const
    {
        return Geometry_Type::TRI;
    }

    enum Interpolation_Order
    get_cell_interpolation_order() const
    {
        return Interpolation_Order::LINEAR;
    }
    uint
    get_num_verts() const
    {
        return 3;
    }
    uint
    get_num_facets() const
    {
        return 3;
    }

    uint
    get_num_verts_per_facet() const
    {
        return 2;
    }

    /*!
     * Node ordinal to face map
     */
    moris::Matrix<moris::IndexMat>
    get_node_to_face_map() const
    {
        MORIS_ERROR(0,"Elements have no faces in 2D. Check the MTK mesh class to get nodes connected to an element.");
        return moris::Matrix<moris::IndexMat>(0,0);
    }

    moris::Matrix<moris::IndexMat>
    get_node_to_edge_map() const
    {
        return {{0,1}, {1,2}, {2,0}};
    }

    moris::Matrix<moris::IndexMat>
    get_node_to_facet_map() const
    {
        return this->get_node_to_edge_map();
    }

    moris::Matrix<moris::IndexMat>
    get_node_to_face_map(moris::uint aSideOrdinal) const
    {
        MORIS_ERROR(0,"Elements have no faces in 2D. Check the MTK mesh class to get nodes connected to an element.");
        return moris::Matrix<moris::IndexMat>(0,0);
    }

    moris::Matrix<moris::IndexMat>
    get_node_to_edge_map(moris::uint aEdgeOrdinal) const
    {
        switch (aEdgeOrdinal)
        {
            case(0):{ return {{0, 1}}; break; }
            case(1):{ return {{1, 2}}; break; }
            case(2):{ return {{2, 0}}; break; }
            default:
            {
                MORIS_ASSERT(0,"Invalid edge ordinal specified");
                return moris::Matrix<moris::IndexMat>(0,0);
                break;
            }
        }
    }

    moris::Matrix<moris::IndexMat>
    get_node_to_facet_map(moris::uint aSideOrdinal) const
    {
        return this->get_node_to_edge_map(aSideOrdinal);
    }

    /*!
     * Nodes on edge to get the relative vector between and convert from
     * {x, y} to {-y, x}. This is one way to get the right-handed orthogonal.
     *   Col 0 - From this node
     *   Col 1 - To this node
     * @param aSideOrdinal Side ordinal of element
     * @return Edge nodes to use for outward normal
     */


    moris::Matrix<moris::IndexMat>
    get_node_map_outward_normal(moris::uint aSideOrdinal) const
    {
        switch (aSideOrdinal)
        {
            case(0):{ return {{1,0}}; break; }
            case(1):{ return {{2,1}}; break; }
            case(2):{ return {{0,2}}; break; }
            default:
            {
                MORIS_ERROR(0,"Invalid side ordinal specified");
                return moris::Matrix<moris::IndexMat>(0,0);
                break;
            }
        }
    }
};

}
}
#endif /* PROJECTS_MTK_SRC_CL_MTK_TRI3_CELL_INFO_HPP_ */



