/*
 * cl_MTK_Cell_XTK_Impl.hpp
 *
 *  Created on: Feb 11, 2019
 *      Author: doble
 */

#ifndef PROJECTS_XTK_SRC_XTK_CL_MTK_CELL_XTK_IMPL_HPP_
#define PROJECTS_XTK_SRC_XTK_CL_MTK_CELL_XTK_IMPL_HPP_

#include "cl_MTK_Cell.hpp"
#include "typedefs.hpp" //MRS/COR/src
#include "cl_Cell.hpp"  //MRS/CON/src
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_MTK_Vertex.hpp" //MTK/src
#include "cl_MTK_Enums.hpp"  //MTK/src
#include "cl_XTK_Child_Mesh.hpp"
#include "cl_MTK_Cell_Info_Tet4.hpp"
#include "fn_cross.hpp"
#include "fn_norm.hpp"
#include "fn_trans.hpp"
#include "op_div.hpp"

namespace xtk
{
    class Background_Mesh;
}

//------------------------------------------------------------------------------
namespace xtk
{
    //------------------------------------------------------------------------------
    /**
    * \brief This is the XTK cell implementation when there is a child mesh to use.
    */

    class Cell_XTK_CM : public mtk::Cell
    {
    private:
        //------------------------------------------------------------------------------
    public:
        //------------------------------------------------------------------------------

        /**
         * trivial constructor
         */
        Cell_XTK_CM();

        Cell_XTK_CM(moris::moris_id aElementId,
                    moris::moris_index aElementIndex,
                    moris::moris_index aElementOwner,
                    moris::moris_index aCMElementIndex,
                    xtk::Child_Mesh *aChildMeshPtr,
                    xtk::Background_Mesh *aBackgroundMeshPtr);
        //------------------------------------------------------------------------------

        /**
        * Destructor
        */
        ~Cell_XTK_CM();

        //------------------------------------------------------------------------------

        /**
        * returns the domain wide id of the cell
        *
        * @return moris_id ID
        */
        moris_id
        get_id() const;

        //------------------------------------------------------------------------------

        /**
         * returns the local index of the cell
         *
         * @return moris_index ID
         */
        moris_index
        get_index() const;

        //------------------------------------------------------------------------------

        /**
         * tells how many vertices are connected to this cell
         */
        uint
        get_number_of_vertices() const;

        //------------------------------------------------------------------------------

        /**
         * returns the proc id of the owner of this cell
         * ( this information is needed for STK )
         */
        moris_id
        get_owner() const;

        //------------------------------------------------------------------------------

        /**
         * fills a moris::cell with pointers to connected vertices
         */
        //FIXME: SDF's Triangle_Vertex causes this to not be able to return a reference.
        moris::Cell<mtk::Vertex *>
        get_vertex_pointers() const;

        //------------------------------------------------------------------------------

        /**
         * returns a Mat with IDs of connected vertices
         */
        Matrix<IdMat>
        get_vertex_ids() const;

        //------------------------------------------------------------------------------

        /**
         * returns a Mat with indices of connected vertices
         */
        Matrix<IndexMat>
        get_vertex_inds() const;

        //------------------------------------------------------------------------------

        /**
         * returns a Mat of dimension
         * < number of vertices * number of dimensions >
         */
        Matrix<DDRMat>
        get_vertex_coords() const;

        //------------------------------------------------------------------------------

        /**
         * returns an enum that defines the geometry type of the element
         */
        mtk::Geometry_Type
        get_geometry_type() const;

        //------------------------------------------------------------------------------

        /**
         * returns the order of the element
         */
        mtk::Interpolation_Order
        get_interpolation_order() const;

        //------------------------------------------------------------------------------

        /**
         * returns error
         */
        mtk::Integration_Order
        get_integration_order() const
        {
            MORIS_ERROR(false, "Cell_XTK_CM::get_integration_order() not implemented.");
            return mtk::Integration_Order::UNDEFINED;
        }

        //------------------------------------------------------------------------------

        moris::Cell<moris::mtk::Vertex const *>
        get_vertices_on_side_ordinal(moris::moris_index aSideOrdinal) const;
        //------------------------------------------------------------------------------

        moris::Matrix<moris::DDRMat>
        compute_outward_side_normal(moris::moris_index aSideOrdinal) const;

        //------------------------------------------------------------------------------

        moris::real
        compute_cell_measure() const;

        //------------------------------------------------------------------------------

        moris::real
        compute_cell_measure_deriv(uint aLocalVertexID, uint aDirection) const;

        //------------------------------------------------------------------------------

        moris::real
        compute_cell_side_measure(moris_index const &aSideOrdinal) const;

        //------------------------------------------------------------------------------

        moris::real
        compute_cell_side_measure_deriv(moris_index const &aSideOrdinal, uint aLocalVertexID, uint aDirection) const;

        //------------------------------------------------------------------------------
        /*!
         * @brief capacity of the cell
         */
        size_t
        capacity();
        //------------------------------------------------------------------------------

    private:
        moris::moris_id mElementId;
        moris::moris_index mElementIndex;
        moris::moris_index mElementOwner;
        moris::moris_index mCMElementIndex; /* Needed to access connectivity (verts) */

        xtk::Child_Mesh *mChildMeshPtr;           /* Needed to access connectivity (verts) */
        xtk::Background_Mesh *mBackgroundMeshPtr; /* Needed to access coordinates */

        //------------------------------------------------------------------------------
    };

} // namespace xtk

#endif /* PROJECTS_XTK_SRC_XTK_CL_MTK_CELL_XTK_IMPL_HPP_ */
