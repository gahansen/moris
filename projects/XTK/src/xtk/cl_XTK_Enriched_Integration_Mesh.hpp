/*
 * cl_XTK_Enriched_Integration_Mesh.hpp
 *
 *  Created on: Jul 22, 2019
 *      Author: doble
 */
#ifndef PROJECTS_XTK_SRC_XTK_CL_XTK_ENRICHED_INTEGRATION_MESH_HPP_
#define PROJECTS_XTK_SRC_XTK_CL_XTK_ENRICHED_INTEGRATION_MESH_HPP_

#include "cl_MTK_Integration_Mesh.hpp"
#include "typedefs.hpp"
#include <unordered_map>

using namespace moris;

namespace xtk
{
class Model;
class Cell_Cluster;
class Side_Cluster;
class Interpolation_Cell_Unzipped;

class Enriched_Integration_Mesh : public mtk::Integration_Mesh
{
public:
    Enriched_Integration_Mesh(Model*             aXTKModel,
                              moris::moris_index aInterpIndex);

    ~Enriched_Integration_Mesh();

    //------------------------------------------------------------------------------
    // MTK Mesh Core Functionality (see base class mtk::Mesh for documentation)
    //------------------------------------------------------------------------------

    MeshType                  get_mesh_type() const;
    moris::uint               get_spatial_dim() const;
    uint                      get_num_entities( enum EntityRank aEntityRank ) const;
    Matrix< IndexMat >        get_entity_connected_to_entity_loc_inds(moris_index aEntityIndex, enum EntityRank aInputEntityRank, enum EntityRank aOutputEntityRank) const;
    Matrix< IndexMat >        get_elements_connected_to_element_and_face_ind_loc_inds(moris_index aElementIndex) const;
    moris_id                  get_glb_entity_id_from_entity_loc_index(moris_index aEntityIndex,enum EntityRank aEntityRank) const;
    moris_index               get_loc_entity_ind_from_entity_glb_id( moris_id aEntityId, enum EntityRank aEntityRank) const;
    Cell<mtk::Vertex const *> get_all_vertices() const;
    Matrix< IdMat >           get_entity_connected_to_entity_glob_ids( moris_id aEntityId, enum EntityRank aInputEntityRank, enum EntityRank aOutputEntityRank) const;
    Matrix< DDRMat >          get_node_coordinate( moris_index aNodeIndex ) const;
    mtk::Vertex &             get_mtk_vertex( moris_index aVertexIndex );
    mtk::Vertex const &       get_mtk_vertex( moris_index aVertexIndex ) const;
    mtk::Cell &               get_writable_mtk_cell( moris_index aElementIndex );
    mtk::Cell &               get_mtk_cell( moris_index aElementIndex );
    mtk::Cell const &         get_mtk_cell( moris_index aElementIndex ) const;
    Matrix< IdMat >           get_communication_table() const;
    moris::Cell<std::string>  get_set_names(enum EntityRank aSetEntityRank) const;

    //------------------------------------------------------------------------------
    // end mesh core functions
    //------------------------------------------------------------------------------

    //------------------------------------------------------------------------------
    // MTK Integration Mesh Functions
    // see base class mtk::Integration_Mesh for documentation
    //------------------------------------------------------------------------------

    mtk::Cell_Cluster const &         get_cell_cluster(mtk::Cell const & aInterpCell) const;
    Cell_Cluster const &              get_cell_cluster(moris_index aInterpCellIndex) const;
    moris::Cell<std::string>          get_block_set_names() const;
    std::string                       get_block_set_label(moris_index aBlockSetOrdinal) const;
    moris_index                       get_block_set_index(std::string aBlockSetLabel) const;
    moris::Cell<mtk::Cluster const *> get_cell_clusters_in_set(moris_index aBlockSetOrdinal) const;
    moris::Cell<mtk::Cluster const *> get_side_set_cluster(moris_index aSideSetOrdinal) const;
    uint                              get_num_side_sets() const;
    std::string                       get_side_set_label(moris_index aSideSetOrdinal) const;
    moris_index                       get_side_set_index(std::string aSideSetLabel) const;
    uint                              get_num_double_sided_sets() const;
    std::string                       get_double_sided_set_label(moris_index aSideSetOrdinal) const;
    moris_index                       get_double_sided_set_index(std::string aDoubleSideSetLabel) const;
    moris::Cell<mtk::Cluster const*>  get_double_side_set_cluster(moris_index aSideSetOrdinal) const;
    uint                              get_sidesets_num_faces( moris::Cell< moris_index > aSideSetIndex ) const;

    //------------------------------------------------------------------------------
    // end integration mesh functions
    //------------------------------------------------------------------------------

    /*
     * Get the side set name of the interface.
     */
    std::string
    get_interface_side_set_name(moris_index aGeomIndex,
                                moris_index aBulkPhaseIndex0,
                                moris_index aBulkPhaseIndex1);


    /*
     * Convenient helper functions
     */
    Matrix<IdMat> convert_indices_to_ids(Matrix<IndexMat> const & aIndices,
                                         enum EntityRank          aEntityRank) const;

    Matrix<IndexMat> convert_ids_to_indices(Matrix<IdMat> const & aIds,
                                            enum EntityRank       aEntityRank) const;

    moris::Cell<moris::mtk::Cell const *>
    get_mtk_cells_loc_inds(Matrix<IndexMat> const & aCellIndices);

    moris::Cell<moris::mtk::Vertex const *>
    get_mtk_vertices_loc_inds(Matrix<IndexMat> const & aVertexIndices);

    // Printing functions
    void print();
    void print_cell_clusters();
    void print_block_sets();
    void print_side_sets();


    friend class Enrichment;
protected:
    Model* mModel;

    //mesh index
    moris::moris_index mMeshIndexInModel;

    // Cell Clusters
    moris::Cell<xtk::Cell_Cluster * > mCellClusters;

    // Block sets containing Cell Clusters
    std::unordered_map<std::string, moris_index>        mBlockSetLabelToOrd;
    moris::Cell<std::string>                            mBlockSetNames;
    moris::Cell<moris::Cell<xtk::Cell_Cluster const *>> mPrimaryBlockSetClusters;

    // side sets
    std::unordered_map<std::string, moris_index> mSideSideSetLabelToOrd;
    moris::Cell<std::string>                     mSideSetLabels;
    moris::Cell<moris::Cell<xtk::Side_Cluster*>> mSideSets;

    // double side sets
    std::unordered_map<std::string, moris_index>   mDoubleSideSetLabelToOrd;
    moris::Cell<std::string>                       mDoubleSideSetLabels;
    moris::Cell<moris::Cell<mtk::Cluster const*> > mDoubleSideSets;
    moris::Cell<Side_Cluster*>                     mDoubleSideSetSideClusters;

private:
    void
    setup_cell_clusters();

    void
    setup_blockset_with_cell_clusters();

    void
    setup_side_set_clusters();

    void
    setup_double_side_set_clusters();

    moris::Cell<std::string>
    split_set_name_by_bulk_phase(std::string aBaseName);

    moris::Cell<std::string>
    split_set_name_by_child_no_child(std::string aBaseName);

    Cell<moris_index>
    register_block_set_names(moris::Cell<std::string> const & aBlockSetNames);

    Cell<moris_index>
    register_side_set_names(moris::Cell<std::string> const & aSideSetNames);

    /*!
     * Setup the interface side sets
     */
    void
    setup_interface_side_sets();

    void
    declare_interface_side_sets();

    void
    create_interface_side_sets_and_clusters();
};
}




#endif /* PROJECTS_XTK_SRC_XTK_CL_XTK_ENRICHED_INTEGRATION_MESH_HPP_ */