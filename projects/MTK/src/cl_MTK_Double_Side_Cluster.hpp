/*
 * cl_MTK_Double_Side_Cluster.hpp
 *
 *  Created on: May 14, 2019
 *      Author: doble
 */

#ifndef PROJECTS_MTK_SRC_CL_MTK_DOUBLE_SIDE_CLUSTER_HPP_
#define PROJECTS_MTK_SRC_CL_MTK_DOUBLE_SIDE_CLUSTER_HPP_

#include "cl_MTK_Cell.hpp"
#include "cl_MTK_Side_Cluster.hpp"

#include "cl_MTK_Cluster.hpp"

namespace moris
{
namespace mtk
{
class Double_Side_Cluster : public Cluster
{
    /*
     * An assumption here is made that the first side appearing in the left side cluster is paired
     * with the first side appearing in the right side cluster.
     */
    moris::mtk::Side_Cluster * mLeftSideCluster;
    moris::mtk::Side_Cluster * mRightSideCluster;

    /*!
     * A one way pairing from left vertices to right vertices
     */
    moris::Cell<moris::mtk::Vertex const *> mLeftToRightVertexPairs;


public:
    Double_Side_Cluster():
    mLeftSideCluster(nullptr),
    mRightSideCluster(nullptr){};

    Double_Side_Cluster(moris::mtk::Side_Cluster *                      aLeftSideCluster,
                        moris::mtk::Side_Cluster *                     aRightSideCluster,
                        moris::Cell<moris::mtk::Vertex const *> const & aLeftToRightVertexPair):
        mLeftSideCluster(aLeftSideCluster),
        mRightSideCluster(aRightSideCluster)
    {
        MORIS_ASSERT(this->get_left_num_sides() == this->get_right_num_sides(),"Number of sides in left cluster do not match the number in right cluster");

        if(!this->is_left_trivial())
        {
            MORIS_ASSERT(this->get_left_num_vertices_in_cluster() == this->get_right_num_vertices_in_cluster(),"Number of vertices mismatch in double cluster");
        }

        mLeftToRightVertexPairs.append(aLeftToRightVertexPair);

    };

    //##############################################
    // Side Cluster traits access
    //##############################################

    /*!
     * Indicates there is a 1 to 1 relationship between
     * integration cell and interpolation cells in this cluster
     * on the left
     *
     */

    virtual bool is_trivial( const moris::uint aSide ) const
    {
        if ( aSide == 0 )
        {
            return this->get_left_side_cluster().is_trivial();
        }
        else if( aSide == 1 )
        {
            return this->get_right_side_cluster().is_trivial();
        }
        else
        {
            MORIS_ERROR(false, "is_trivial(): can only be 1 and 2");
            return false;
        }
    }

    bool
    is_left_trivial() const
    {
        return this->get_left_side_cluster().is_trivial();
    }

    /*!
     * Indicates there is a 1 to 1 relationship between
     * integration cell and interpolation cells in this cluster
     * on the right
     *
     */

    bool
    is_right_trivial() const
    {
        return this->get_right_side_cluster().is_trivial();
    }

    //##############################################
    // Single Side Cluster Access
    // (Pure )
    //##############################################

    /*!
     * Returns the left side cluster
     */

    moris::mtk::Side_Cluster const &
    get_left_side_cluster() const
    {
        return *mLeftSideCluster;
    }

    //----------------------------------------------------------------

    /*!
     * Returns the left side cluster in this double sided side cluster
     */

    moris::mtk::Side_Cluster const &
    get_right_side_cluster() const
    {
        return *mRightSideCluster;
    }

    //##############################################
    // Vertex Pair Access
    //##############################################
    /*!
     * Provided a vertex in the left cluster, returns the corresponding
     * vertex in the right cluster.
     */
    moris::mtk::Vertex const *
    get_left_vertex_pair(moris::mtk::Vertex const * aLeftVertex) const
    {
        moris_index tLeftClusterIndex = this->get_left_side_cluster().get_vertex_cluster_index(aLeftVertex);

        MORIS_ASSERT(tLeftClusterIndex < (moris_index)mLeftToRightVertexPairs.size(),"Vertex index out of bounds in pairing.");

        return mLeftToRightVertexPairs(tLeftClusterIndex);
    }

    //----------------------------------------------------------------

    //##############################################
    // Cell Side Ordinals/Vertex Access
    //##############################################

    /*!
     * Get left interpolation cell interpolating into the left side of the double
     * sided side set
     */

    moris::mtk::Cell const &
    get_left_interpolation_cell() const
    {
        return this->get_left_side_cluster().get_interpolation_cell();
    }

    //----------------------------------------------------------------


    /*!
     * Get right interpolation cell interpolating into the right side of the double
     * sided side set
     */

    moris::mtk::Cell const &
    get_right_interpolation_cell() const
    {
        return this->get_right_side_cluster().get_interpolation_cell();
    }

    //----------------------------------------------------------------

    /*!
     * Get all integration cells on the left side of the side set
     * in this double sided cluster
     */

    moris::Cell<mtk::Cell const *> const &
    get_left_integration_cells() const
    {
        return this->get_left_side_cluster().get_cells_in_side_cluster();
    }

    //----------------------------------------------------------------

    /*!
     * Get all integration cells on the right side of the side set
     * in this double sided cluster
     */

    moris::Cell<mtk::Cell const *> const &
    get_right_integration_cells() const
    {
        return this->get_right_side_cluster().get_cells_in_side_cluster();
    }

    //----------------------------------------------------------------

    /*!
     * Return all integration cell side ordinals on left side of the
     * double sided side cluster
     */

    moris::Matrix<moris::IndexMat>
    get_left_integration_cell_side_ordinals() const
    {
        return this->get_left_side_cluster().get_cell_side_ordinals();
    }

    //----------------------------------------------------------------

    /*!
     * Single side ordinal version of above
     */

    moris_index
    get_left_cell_side_ordinal(moris::moris_index aLeftCellIndexInCluster) const
    {
        return this->get_left_side_cluster().get_cell_side_ordinal(aLeftCellIndexInCluster);
    }

    //----------------------------------------------------------------

    /*!
     * Return all integration cell side ordinals on right side of the
     * double sided side cluster
     */

    moris::Matrix<moris::IndexMat>
    get_right_integration_cell_side_ordinals() const
    {
        return this->get_right_side_cluster().get_cell_side_ordinals();
    }

    //----------------------------------------------------------------

    /*!
     * Single side ordinal version of above
     */

    moris_index
    get_right_cell_side_ordinal(moris::moris_index aRightCellIndexInCluster) const
    {
        return this->get_right_side_cluster().get_cell_side_ordinal(aRightCellIndexInCluster);
    }
    //----------------------------------------------------------------

    /*!
     * Returns all the left vertices in this cluster
     */

    moris::Cell<moris::mtk::Vertex const *> const &
    get_left_vertices_in_cluster() const
    {
        return this->get_left_side_cluster().get_vertices_in_cluster();
    }

    //----------------------------------------------------------------

    /*!
     * Returns all the right vertices in this cluster
     */

    moris::Cell<moris::mtk::Vertex const *> const &
    get_right_vertices_in_cluster() const
    {
         return this->get_right_side_cluster().get_vertices_in_cluster();
    }

    //##############################################
    // Local Coordinate Access
    //##############################################

    /*
     * Access the full array of local coordinates on the left
     */

    moris::Matrix<moris::DDRMat> const &
    get_left_vertices_local_coordinates_wrt_interp_cell() const
    {
        return this->get_left_side_cluster().get_vertices_local_coordinates_wrt_interp_cell();
    }

    //----------------------------------------------------------------

    /*
     * Access the full array of local coordinates on the right
     */

    moris::Matrix<moris::DDRMat> const &
    get_right_vertices_local_coordinates_wrt_interp_cell() const
    {
        return this->get_right_side_cluster().get_vertices_local_coordinates_wrt_interp_cell();
    }

    //----------------------------------------------------------------

    /*
     * Access a single local coordinate of a vertex on the left
     */

    moris::Matrix<moris::DDRMat>
    get_left_vertex_local_coordinate_wrt_interp_cell( moris::mtk::Vertex const * aVertex ) const
    {
        return this->get_left_side_cluster().get_vertex_local_coordinate_wrt_interp_cell(aVertex);
    }

    //----------------------------------------------------------------

    /*
     * Access a single local coordinate of a vertex on the right
     */

    moris::Matrix<moris::DDRMat>
    get_right_vertex_local_coordinate_wrt_interp_cell( moris::mtk::Vertex const * aVertex ) const
    {
        return this->get_right_side_cluster().get_vertex_local_coordinate_wrt_interp_cell(aVertex);
    }

    /*!
     * Access an integration cells parametric coordinates on a side left side
     * @param[in] - Local integration cell index with respect to the cluster (not proc local index)
     */
    moris::Matrix<moris::DDRMat>
    get_left_cell_local_coords_on_side_wrt_interp_cell(moris::moris_index aLeftClusterLocalIndex) const
    {
        return this->get_left_side_cluster().get_cell_local_coords_on_side_wrt_interp_cell(aLeftClusterLocalIndex);
    }

    /*!
     * Access an integration cells parametric coordinates on a side right side
     * @param[in] - Local integration cell index with respect to the cluster (not proc local index)
     */
    moris::Matrix<moris::DDRMat>
    get_right_cell_local_coords_on_side_wrt_interp_cell(moris::moris_index aRightClusterLocalIndex) const
    {
        return this->get_right_side_cluster().get_cell_local_coords_on_side_wrt_interp_cell(aRightClusterLocalIndex);
    }


    //----------------------------------------------------------------

    //##############################################
    // Size Access
    //##############################################
    /*!
     * Size of the xsi vector of left
     */
    moris_index
    get_left_dim_of_param_coord() const
    {
        return this->get_left_side_cluster().get_dim_of_param_coord();
    }

    //----------------------------------------------------------------

    /*!
     * Size of the xsi vector of right
     */
    moris_index
    get_right_dim_of_param_coord() const
    {
        return this->get_right_side_cluster().get_dim_of_param_coord();
    }

    //----------------------------------------------------------------


    moris::uint
    get_left_num_sides() const
    {
        return this->get_left_side_cluster().get_num_sides_in_cluster();
    }

    //----------------------------------------------------------------


    moris::uint
    get_right_num_sides() const
    {
        return this->get_right_side_cluster().get_num_sides_in_cluster();
    }

    //----------------------------------------------------------------


    moris::uint
    get_left_num_vertices_in_cluster() const
    {
        return this->get_left_side_cluster().get_num_vertices_in_cluster();
    }

    //----------------------------------------------------------------

    moris::uint
    get_right_num_vertices_in_cluster() const
    {
        return this->get_right_side_cluster().get_num_vertices_in_cluster();
    }



};
}
}

#endif /* PROJECTS_MTK_SRC_CL_MTK_DOUBLE_SIDE_CLUSTER_HPP_ */
