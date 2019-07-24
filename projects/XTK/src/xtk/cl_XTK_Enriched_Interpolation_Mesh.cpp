/*
 * cl_XTK_Enriched_Interpolation_Mesh.cpp
 *
 *  Created on: Jul 10, 2019
 *      Author: doble
 */



#include "cl_XTK_Enriched_Interpolation_Mesh.hpp"

namespace xtk
{
//------------------------------------------------------------------------------
Enriched_Interpolation_Mesh::Enriched_Interpolation_Mesh(Model* aXTKModel):
    mXTKModel(aXTKModel),
    mNumVerts(0),
    mNumVertsPerInterpCell(MORIS_UINT_MAX)
{

}
//------------------------------------------------------------------------------
MeshType
Enriched_Interpolation_Mesh::get_mesh_type() const
{
    return MeshType::XTK;
}
//------------------------------------------------------------------------------
moris::uint
Enriched_Interpolation_Mesh::get_spatial_dim() const
{
    return mXTKModel->get_spatial_dim();
}
//------------------------------------------------------------------------------
uint
Enriched_Interpolation_Mesh::get_num_entities( enum EntityRank aEntityRank ) const
{
    switch(aEntityRank)
    {
        case(EntityRank::NODE):
        {
            return mEnrichedInterpVerts.size();
            break;
        }
        case(EntityRank::ELEMENT):
        {
            return mEnrichedInterpCells.size();
            break;
        }
        default:
            MORIS_ERROR(0,"Only support get num entities for nodes and elements currently");
            return 0;
    }
}
//------------------------------------------------------------------------------
Matrix<IndexMat>
Enriched_Interpolation_Mesh::get_entity_connected_to_entity_loc_inds(moris_index  aEntityIndex,
                                                                     enum EntityRank aInputEntityRank,
                                                                     enum EntityRank aOutputEntityRank) const
{
    MORIS_ERROR(aInputEntityRank == EntityRank::ELEMENT && aOutputEntityRank == EntityRank::NODE,"Only support element to node connectivity");
    MORIS_ASSERT(aEntityIndex<(moris_index)mEnrichedInterpCells.size(),"Element index out of bounds");
    return mEnrichedInterpCells(aEntityIndex).get_vertex_inds();
}
//------------------------------------------------------------------------------
Matrix< IndexMat >
Enriched_Interpolation_Mesh::get_elements_connected_to_element_and_face_ind_loc_inds(moris_index aElementIndex) const
{
    MORIS_ERROR(0,"XTK ENRICHED MESH ERROR: get_elements_connected_to_element_and_face_ind_loc_inds no implemented");
    return Matrix<IndexMat>(0,0);
}
//------------------------------------------------------------------------------
Cell<mtk::Vertex const *>
Enriched_Interpolation_Mesh::get_all_vertices() const
{
    moris::uint tNumNodes = this->get_num_entities(EntityRank::NODE);
    Cell<mtk::Vertex const *> tVertices(tNumNodes);
    for(moris::uint i = 0; i < tNumNodes; i++)
    {
        tVertices(i) = & mEnrichedInterpVerts(i);
    }
    return tVertices;
}
//------------------------------------------------------------------------------
moris_id
Enriched_Interpolation_Mesh::get_glb_entity_id_from_entity_loc_index(moris_index     aEntityIndex,
                                                                     enum EntityRank aEntityRank) const
{
    moris::uint tMapIndex = (uint)aEntityRank;

    MORIS_ASSERT(aEntityRank == EntityRank::NODE || aEntityRank == EntityRank::ELEMENT,"XTK ENRICHED MESH ERROR: Only support glb to loc conversion for vertices and cells");
    MORIS_ASSERT(aEntityIndex<(moris_index)mLocalToGlobalMaps(tMapIndex).numel(),"Entityindex out of bounds");
    return mLocalToGlobalMaps(tMapIndex)(aEntityIndex);
}
//------------------------------------------------------------------------------
moris_index
Enriched_Interpolation_Mesh::get_loc_entity_ind_from_entity_glb_id(moris_id        aEntityId,
                                                                   enum EntityRank aEntityRank) const
{
    moris::uint tMapIndex = (uint)aEntityRank;

    auto tIter = mGlobaltoLobalMaps(tMapIndex).find(aEntityId);

    MORIS_ASSERT(aEntityRank == EntityRank::NODE || aEntityRank == EntityRank::ELEMENT,"XTK ENRICHED MESH ERROR: Only support glb to loc conversion for vertices and cells");
    MORIS_ASSERT(tIter!=  mGlobaltoLobalMaps(tMapIndex).end(),"Id does not appear in map");
    return tIter->second;
}

//------------------------------------------------------------------------------

Matrix<IdMat>
Enriched_Interpolation_Mesh::get_entity_connected_to_entity_glob_ids( moris_id     aEntityId,
                                                                      enum EntityRank aInputEntityRank,
                                                                      enum EntityRank aOutputEntityRank) const
{
    moris_index tEntityIndex = get_loc_entity_ind_from_entity_glb_id(aEntityId,aInputEntityRank);

    Matrix<IndexMat> tEntityToEntityLoc = this->get_entity_connected_to_entity_loc_inds(tEntityIndex,aInputEntityRank,aOutputEntityRank);

    return convert_indices_to_ids(tEntityToEntityLoc,aOutputEntityRank);
}
//------------------------------------------------------------------------------
Matrix< DDRMat >
Enriched_Interpolation_Mesh::get_node_coordinate( moris_index aNodeIndex ) const
{
    mtk::Vertex const & tVertex = get_mtk_vertex(aNodeIndex);
    return tVertex.get_coords();
}
//------------------------------------------------------------------------------
mtk::Vertex &
Enriched_Interpolation_Mesh::get_mtk_vertex( moris_index aVertexIndex )
{
    MORIS_ASSERT(aVertexIndex < (moris_index)mEnrichedInterpVerts.size(),"Vertex index out of bounds");
    return mEnrichedInterpVerts(aVertexIndex);
}
mtk::Vertex const &
Enriched_Interpolation_Mesh::get_mtk_vertex( moris_index aVertexIndex ) const
{
    MORIS_ASSERT(aVertexIndex < (moris_index)mEnrichedInterpVerts.size(),"Vertex index out of bounds");
    return mEnrichedInterpVerts(aVertexIndex);
}
//------------------------------------------------------------------------------
mtk::Cell &
Enriched_Interpolation_Mesh::get_writable_mtk_cell( moris_index aElementIndex )
{
    MORIS_ASSERT(aElementIndex < (moris_index)mEnrichedInterpCells.size(),"Cell index out of bounds");
    return mEnrichedInterpCells(aElementIndex);
}
//------------------------------------------------------------------------------
Matrix< IdMat >
Enriched_Interpolation_Mesh::get_communication_table() const
{
    return mXTKModel->get_background_mesh().get_mesh_data().get_communication_table();
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
Matrix<IdMat>
Enriched_Interpolation_Mesh::convert_indices_to_ids(Matrix<IndexMat> const & aIndices,
                                                    enum EntityRank          aEntityRank) const
{
    moris::uint tNRow = aIndices.n_rows();
    moris::uint tNCol = aIndices.n_cols();
    Matrix<IdMat> tIds(tNRow,tNCol);
    for(moris::uint i = 0; i < tNRow; i++)
    {
        for(moris::uint j = 0; j<tNCol; j++)
        {
            tIds(i,j) = this->get_glb_entity_id_from_entity_loc_index(aIndices(i,j),aEntityRank);
        }
    }
    return tIds;
}
//------------------------------------------------------------------------------
Matrix<IndexMat>
Enriched_Interpolation_Mesh::convert_ids_to_indices(Matrix<IdMat> const & aIds,
                                                    enum EntityRank       aEntityRank) const
{
    moris::uint tNRow = aIds.n_rows();
    moris::uint tNCol = aIds.n_cols();
    Matrix<IdMat> tIndices(tNRow,tNCol);
    for(moris::uint i = 0; i < tNRow; i++)
    {
        for(moris::uint j = 0; j<tNCol; j++)
        {
            tIndices(i,j) = this->get_loc_entity_ind_from_entity_glb_id(aIds(i,j),aEntityRank);
        }
    }

    return tIndices;
}
//------------------------------------------------------------------------------
uint
Enriched_Interpolation_Mesh::get_num_elements()
{
    return mEnrichedInterpCells.size();
}
//------------------------------------------------------------------------------
uint
Enriched_Interpolation_Mesh::get_num_verts_per_interp_cell()
{
    MORIS_ASSERT(mNumVertsPerInterpCell != MORIS_UINT_MAX,"Number of verts per interpolation cell not set");
    return mNumVertsPerInterpCell;
}
//------------------------------------------------------------------------------
Interpolation_Vertex_Unzipped*
Enriched_Interpolation_Mesh::get_unzipped_vertex_pointer(moris_index aVertexIndex)
{
    MORIS_ASSERT(aVertexIndex < (moris_index)mEnrichedInterpVerts.size(),"Provided vertex index is out of bounds");
    return &mEnrichedInterpVerts(aVertexIndex);
}

//------------------------------------------------------------------------------
moris_index
Enriched_Interpolation_Mesh::add_vertex_enrichment( mtk::Vertex *       aBaseInterpVertex,
                                                    Vertex_Enrichment & aVertexEnrichment,
                                                    bool              & aNewVertex)
{
    // vertex index of the base interpolation vertex
    moris_index tBaseVertIndex = aBaseInterpVertex->get_index();

    // Number of enriched vertices related to the base vertex
    moris::uint tNumVertsEnrOnBaseVert = mBaseInterpVertToVertEnrichmentIndex(tBaseVertIndex).size();

    // not new until we make it to the end
    aNewVertex = false;

    // iterate through the enriched vertices related to the base vertex and see if any are equal
    for(moris::uint i = 0; i < tNumVertsEnrOnBaseVert; i++)
    {
        moris_index tVertEnrIndex = mBaseInterpVertToVertEnrichmentIndex(tBaseVertIndex)(i);

        if(aVertexEnrichment == mInterpVertEnrichment(tVertEnrIndex))
        {
            return tVertEnrIndex;
        }
    }

    // if we make it through the loop without finding an enrichment vertex
    // make a new one
    aNewVertex = true;

    // index of the vertex enrichment
    moris_index tVertexEnrichmentIndex = mInterpVertEnrichment.size();

    // add to member data
    mInterpVertEnrichment.push_back(aVertexEnrichment);

    // add a dummy value to the parent vertex index of a vertex interpolation
    mVertexEnrichmentParentVertexIndex.push_back(tVertexEnrichmentIndex);

    mBaseInterpVertToVertEnrichmentIndex(tBaseVertIndex).push_back(tVertexEnrichmentIndex);


    return tVertexEnrichmentIndex;
}
//------------------------------------------------------------------------------
Vertex_Enrichment *
Enriched_Interpolation_Mesh::get_vertex_enrichment(moris_index aVertexEnrichmentIndex)
{
    MORIS_ASSERT(aVertexEnrichmentIndex< (moris_index)mInterpVertEnrichment.size(),"Provided vertex enrichment index out of bounds");
    return &mInterpVertEnrichment(aVertexEnrichmentIndex);
}
//------------------------------------------------------------------------------
moris_index
Enriched_Interpolation_Mesh::get_vertex_related_to_vertex_enrichment(moris_index aVertexEnrichmentIndex) const
{
    MORIS_ASSERT(aVertexEnrichmentIndex< (moris_index)mVertexEnrichmentParentVertexIndex.size(),"Provided vertex enrichment index out of bounds");
    return mVertexEnrichmentParentVertexIndex(aVertexEnrichmentIndex);
}
//------------------------------------------------------------------------------
Cell<Interpolation_Cell_Unzipped> const &
Enriched_Interpolation_Mesh::get_enriched_interpolation_cells() const
{
    return mEnrichedInterpCells;
}
//------------------------------------------------------------------------------
void
Enriched_Interpolation_Mesh::print() const
{
    this->print_vertex_maps();
    this->print_enriched_cell_maps();
    this->print_enriched_cells();
}

void Enriched_Interpolation_Mesh::print_enriched_cells() const
{
    moris::uint tNumCells = this->get_num_entities(EntityRank::ELEMENT);
    std::cout<<"\nEnriched Interpolation Cells:"<<std::endl;
    for(moris::uint i =0; i <tNumCells; i++)
    {
        std::cout<<"   "<<mEnrichedInterpCells(i)<<std::endl;
    }
}
void Enriched_Interpolation_Mesh::print_vertex_maps() const
{
    moris::uint tNumNodes = this->get_num_entities(EntityRank::NODE);
    std::cout<<"\nVertex Map:"<<std::endl;
    for(moris::uint i =0; i <tNumNodes; i++)
    {
        std::cout<<"    Vertex Index: "<<i<< " | Vertex Id: "<<std::setw(9) <<mLocalToGlobalMaps(0)(i)<<std::endl;
    }
}

void Enriched_Interpolation_Mesh::print_enriched_cell_maps() const
{
    moris::uint tNumCells = this->get_num_entities(EntityRank::ELEMENT);
    moris::uint tSpatialDim = mXTKModel->get_spatial_dim();

    std::cout<<"\nCell Map:"<<std::endl;
    for(moris::uint i =0; i <tNumCells; i++)
    {
        std::cout<<"    Cell Index: "<<i<< " | Cell Id: "<<std::setw(9) <<mLocalToGlobalMaps(tSpatialDim)(i)<<std::endl;
    }
}

//------------------------------------------------------------------------------
void
Enriched_Interpolation_Mesh::finalize_setup()
{
    this->setup_local_to_global_maps();
}
//------------------------------------------------------------------------------
void
Enriched_Interpolation_Mesh::setup_local_to_global_maps()
{
    // initalize local to global maps
    mLocalToGlobalMaps = Cell<Matrix< IdMat >>( mXTKModel->get_spatial_dim() + 1 );
    mGlobaltoLobalMaps = Cell<std::unordered_map<moris_id,moris_index>>(mXTKModel->get_spatial_dim() + 1);

    setup_vertex_maps();
    setup_cell_maps();
}
//------------------------------------------------------------------------------
void
Enriched_Interpolation_Mesh::setup_vertex_maps()
{
    moris::uint tNumNodes = this->get_num_entities(EntityRank::NODE);

    mLocalToGlobalMaps(0) = Matrix<IdMat>(tNumNodes,1);

    for(moris::uint i =0; i <tNumNodes; i++)
    {
        mLocalToGlobalMaps(0)(mEnrichedInterpVerts(i).get_index()) = mEnrichedInterpVerts(i).get_id();

        MORIS_ASSERT(mGlobaltoLobalMaps(0).find(mEnrichedInterpVerts(i).get_id()) == mGlobaltoLobalMaps(0).end(),"Duplicate id in the vertex map detected");

        mGlobaltoLobalMaps(0)[mEnrichedInterpVerts(i).get_id()] = mEnrichedInterpVerts(i).get_index();
    }
}
//------------------------------------------------------------------------------
void
Enriched_Interpolation_Mesh::setup_cell_maps()
{
    moris::uint tNumCells = this->get_num_entities(EntityRank::ELEMENT);
    moris::uint tSpatialDim = mXTKModel->get_spatial_dim();

    mLocalToGlobalMaps(tSpatialDim) = Matrix<IdMat>(tNumCells,1);

    for(moris::uint i =0; i <tNumCells; i++)
    {
        mLocalToGlobalMaps(tSpatialDim)(mEnrichedInterpVerts(i).get_index()) = mEnrichedInterpVerts(i).get_id();

        MORIS_ASSERT(mGlobaltoLobalMaps(tSpatialDim).find(mEnrichedInterpVerts(i).get_id()) == mGlobaltoLobalMaps(tSpatialDim).end(),"Duplicate id in the vertex map detected");

        mGlobaltoLobalMaps(tSpatialDim)[mEnrichedInterpVerts(i).get_id()] = mEnrichedInterpVerts(i).get_index();
    }
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


}