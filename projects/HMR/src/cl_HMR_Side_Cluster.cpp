/*
 * cl_HMR_Side_Cluster.cpp
 *
 *  Created on: May 30, 2019
 *      Author: doble
 */
#include "cl_HMR_Side_Cluster.hpp"


namespace moris
{
namespace hmr
{
//----------------------------------------------------------------
Side_Cluster_HMR::Side_Cluster_HMR():
    mTrivial(true),
    mInterpolationCell(nullptr),
    mIntegrationCells(0,nullptr),
    mIntegrationCellSideOrdinals(0,0),
    mVerticesInCluster(0,nullptr),
    mVertexParamCoords(0,0)
    {}
//----------------------------------------------------------------

Side_Cluster_HMR::Side_Cluster_HMR( moris::mtk::Cell const *                        aInterpCell,
                                    moris::mtk::Cell const *                        aIntegrationCell,
                                    moris::Cell<moris::mtk::Vertex const *> const & aVerticesInCluster,
                                    moris_index aSideOrdinal):
    mTrivial(true),
    mInterpolationCell(aInterpCell),
    mIntegrationCells(0,nullptr),
    mIntegrationCellSideOrdinals({{aSideOrdinal}}),
    mVerticesInCluster(aVerticesInCluster),
    mVertexParamCoords(0,0)
{
    mIntegrationCells.push_back(aIntegrationCell);

    // add to map
    for(moris::uint i = 0; i <aVerticesInCluster.size(); i++)
    {
        this->add_vertex_to_map(aVerticesInCluster(i)->get_id(),i);
    }

}

//----------------------------------------------------------------

Side_Cluster_HMR::Side_Cluster_HMR(
                 bool                                            aTrivial,
                 moris::mtk::Cell const *                        aInterpolationCell,
                 moris::Cell<moris::mtk::Cell const *>   const & aIntegrationCells,
                 moris::Matrix<moris::IndexMat>          const & aIntegrationCellSideOrdinals,
                 moris::Cell<moris::mtk::Vertex const *> const & aVerticesInCluster,
                 moris::Matrix<moris::DDRMat>            const & aVertexParamCoords):
    mTrivial(aTrivial),
    mInterpolationCell(aInterpolationCell),
    mIntegrationCells(aIntegrationCells),
    mIntegrationCellSideOrdinals(aIntegrationCellSideOrdinals),
    mVerticesInCluster(aVerticesInCluster),
    mVertexParamCoords(aVertexParamCoords)
{
    MORIS_ERROR(aVerticesInCluster.size() == aVertexParamCoords.n_rows(),"Dimension mismatch between parametric coordinates provided and vertices provided (one row in parametric coordinates for each vertex in cluster).");

    // add vertices to map
    for(moris::uint i = 0; i <aVerticesInCluster.size(); i++)
    {
        this->add_vertex_to_map(aVerticesInCluster(i)->get_id(),i);
    }
}

//----------------------------------------------------------------

bool
Side_Cluster_HMR::is_trivial( const moris::uint aSide ) const
{
    return mTrivial;
}

//----------------------------------------------------------------

moris::mtk::Cell const &
Side_Cluster_HMR::get_interpolation_cell( const moris::uint aSide) const
{
    return *mInterpolationCell;
}

//----------------------------------------------------------------

moris::Cell<moris::mtk::Cell const *> const &
Side_Cluster_HMR::get_cells_in_side_cluster() const
{
    return mIntegrationCells;
}

//----------------------------------------------------------------

moris::Matrix<moris::IndexMat>
Side_Cluster_HMR::get_cell_side_ordinals( const moris::uint aSide) const
{
    return mIntegrationCellSideOrdinals;
}

//----------------------------------------------------------------

moris_index
Side_Cluster_HMR::get_cell_side_ordinal(moris::moris_index aCellIndexInCluster,
        const moris::uint aSide ) const
{
    MORIS_ASSERT(aCellIndexInCluster<(moris_index)mIntegrationCellSideOrdinals.numel(),"Cell index in cluster out of bounds");

    return mIntegrationCellSideOrdinals(aCellIndexInCluster);
}

//----------------------------------------------------------------

moris::Cell<moris::mtk::Vertex const *> const &
Side_Cluster_HMR::get_vertices_in_cluster( const moris::uint aSide ) const
{
    return mVerticesInCluster;
}

//----------------------------------------------------------------

moris::Matrix<moris::DDRMat> const &
Side_Cluster_HMR::get_vertices_local_coordinates_wrt_interp_cell( const moris::uint aSide ) const
{
    MORIS_ERROR(!mTrivial,"Accessing local coordinates on a trivial side cluster is not allowed");

    return mVertexParamCoords;
}

//----------------------------------------------------------------

moris::moris_index
Side_Cluster_HMR::get_vertex_cluster_index( moris::mtk::Vertex const * aVertex ) const
{

     return this->get_vertex_cluster_local_index(aVertex->get_id());
}

//----------------------------------------------------------------

moris::Matrix<moris::DDRMat>
Side_Cluster_HMR::get_vertex_local_coordinate_wrt_interp_cell( moris::mtk::Vertex const * aVertex,
        const moris::uint aSide ) const
{
    MORIS_ERROR(!mTrivial,"Accessing local coordinates on a trivial side cluster is not allowed");

    moris_index tLocalVertIndex = this->get_vertex_cluster_local_index(aVertex->get_id());

    MORIS_ASSERT( tLocalVertIndex < (moris_index)mVertexParamCoords.n_rows(),"Vertex local side cluster index out of bounds. This could be cause by not adding parametric coordinates");

    return mVertexParamCoords.get_row(tLocalVertIndex);
}

//----------------------------------------------------------------

moris_index
Side_Cluster_HMR::get_dim_of_param_coord( const moris::uint aSide ) const
{
    MORIS_ERROR(!mTrivial,"Accessing size of local coordinates on a trivial side cluster is not allowed");
    return mVertexParamCoords.n_cols();
}

//----------------------------------------------------------------

moris_index
Side_Cluster_HMR::get_vertex_cluster_local_index(moris_id aVertexId) const
{
    auto tIter = mVertexIdToLocalIndex.find(aVertexId);

    MORIS_ERROR(tIter != mVertexIdToLocalIndex.end(),"Vertex not found in side cluster");

    return tIter->second;
}

//----------------------------------------------------------------

void
Side_Cluster_HMR::add_vertex_to_map(moris_id aVertexId,
                  moris_index aVertexLocalIndex)
{
    MORIS_ERROR(mVertexIdToLocalIndex.find(aVertexId) == mVertexIdToLocalIndex.end(),"Trying to add vertex already found in side cluster");
    mVertexIdToLocalIndex[aVertexId] = aVertexLocalIndex;
}

//----------------------------------------------------------------

}
}




