/*
 * cl_MTK_CELL_INFO.hpp
 *
 *  Created on: Jul 25, 2019
 *      Author: ryan
 */

#ifndef PROJECTS_MTK_SRC_CL_MTK_CELL_INFO_HPP_
#define PROJECTS_MTK_SRC_CL_MTK_CELL_INFO_HPP_

#include "cl_Cell.hpp"
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "assert.hpp"
#include "cl_MTK_Enums.hpp"

namespace moris
{
namespace mtk
{

class Cell_Info
{
	public:
	Cell_Info(){}

	virtual
	~Cell_Info(){}
	// ---------------------------------------------------------------------------------
	virtual
	enum Geometry_Type
	get_cell_geometry() const = 0;
	// ---------------------------------------------------------------------------------
        virtual
        enum Interpolation_Order
        get_cell_interpolation_order() const = 0;
        // ---------------------------------------------------------------------------------
        virtual
        uint
        get_num_verts() const  = 0;
        // ---------------------------------------------------------------------------------
        virtual
        uint
        get_num_verts_per_facet() const = 0;
        // ---------------------------------------------------------------------------------
        virtual
        uint
        get_num_facets() const = 0;
        // ---------------------------------------------------------------------------------
	virtual
	moris::Matrix<moris::IndexMat>
	get_node_to_face_map() const = 0;
	// ---------------------------------------------------------------------------------
	virtual
	moris::Matrix<moris::IndexMat>
	get_node_to_face_map(moris::uint aSideOrdinal) const  = 0;
	// ---------------------------------------------------------------------------------
	virtual
	moris::Matrix<moris::IndexMat>
	get_node_to_facet_map() const = 0;
	// ---------------------------------------------------------------------------------
	virtual
	moris::Matrix<moris::IndexMat>
	get_node_to_facet_map(moris::uint aSideOrdinal) const = 0;
	// ---------------------------------------------------------------------------------
	virtual
	moris::Matrix<moris::IndexMat>
	get_node_to_edge_map() const  = 0;
	// ---------------------------------------------------------------------------------
	virtual
	moris::Matrix<moris::IndexMat>
	get_node_to_edge_map(moris::uint aEdgeOrdinal) const  = 0;
	// ---------------------------------------------------------------------------------
	virtual
	moris::Matrix<moris::IndexMat>
	get_node_map_outward_normal(moris::uint aSideOrdinal) const  = 0;

        // ---------------------------------------------------------------------------------
	virtual
	moris::Matrix<moris::IndexMat>
	get_edge_to_face_map() const
	{
	    MORIS_ERROR(0,"get edge to face map not implemented for this CELL_INFO, this CELL_INFO currently used in XTK only for tets/tris");
	    return moris::Matrix<moris::IndexMat>(0,0);
	}

};

}

}



#endif /* PROJECTS_MTK_SRC_CL_MTK_CELL_INFO_HPP_ */