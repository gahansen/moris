/*
 * cl_XTK_Enrichment.hpp
 *
 *  Created on: Feb 23, 2018
 *      Author: ktdoble
 */

#ifndef XTK_SRC_XTK_CL_XTK_ENRICHMENT_HPP_
#define XTK_SRC_XTK_CL_XTK_ENRICHMENT_HPP_

// XTKL: Linalg Includes
#include "cl_Matrix.hpp"
#include "cl_XTK_Matrix_Base_Utilities.hpp"


// Std includes
#include <limits>

// XTKL: XTK Includes
#include "cl_Cell.hpp"
#include "cl_XTK_Model.hpp"
#include "cl_XTK_Child_Mesh.hpp"
#include "cl_XTK_Cut_Mesh.hpp"
#include "fn_mesh_flood_fill.hpp"
#include "fn_prune_element_to_element.hpp"
#include "fn_generate_element_to_element.hpp"
#include "fn_local_child_mesh_flood_fill.hpp"
#include "fn_generate_shared_face_element_graph.hpp"
#include "fn_mesh_flood_fill.hpp"
#include "fn_Pairing.hpp"
#include "fn_equal_to.hpp"


// Mesh includes
#include "cl_MTK_Mesh.hpp"
#include "cl_MTK_Cell.hpp"
#include "cl_Mesh_Enums.hpp"
#include "cl_XTK_Background_Mesh.hpp"
#include "cl_Mesh_Enums.hpp"

#include "fn_unique.hpp"

#include "cl_XTK_Vertex_Enrichment.hpp"

/*
 * This class provides all the functions to perform the enrichment strategy on a child mesh
 */
namespace xtk
{

enum class Enrichment_Method
{
    USE_INTEGRATION_CELL_BASIS, // this one computes directly the vertex interpolation (uses the basis of tetrahedral cell)
    USE_INTERPOLATION_CELL_BASIS, // This one constructs an interpolation cell which interpolates into each subphase. (Uses basis of interpolation cell)
    INVALID
};

class Enrichment_Parameters
{
public:
    Enrichment_Parameters(){};

    enum moris::EntityRank mBasisToEnrich = EntityRank::NODE ; /*For lagrange mesh this is node, for HMR this may be bsplines*/
};


class Model;

class Enrichment
{
public:
    Enrichment(){};

    Enrichment(enum Enrichment_Method aMethod,
               enum EntityRank        aBasisRank,
               moris::moris_index     aInterpIndex,
               moris::moris_index     aNumBulkPhases,
               xtk::Model*            aXTKModelPtr,
               xtk::Cut_Mesh*         aCutMeshPtr,
               xtk::Background_Mesh*  aBackgroundMeshPtr);

    bool mVerbose = false;
    bool mBasisEnrToBulkPhase = false;
    moris::moris_index INDEX_MAX = std::numeric_limits<moris::moris_index>::max();


    /*!
     * Performs basis function enrichment so that each element in connected regions of a given bulk phase are
     * assigned a unique enrichment level in the basis support.
     * @param[in] aCutMesh - Mesh containing elements around the interface
     * @param[in] aBackgroundMesh - Background mesh (Lagrangian Mesh)
     * @param[in] aMatrixFactory - Means of creating matrix objects
     *
     */
    void
    perform_enrichment();

    /*!
     * Returns the element inds in a basis support constructed in call to perform_enrichment. These are indexed by basis function index.
     */
    Cell<moris::Matrix< moris::IdMat >> const &
    get_element_inds_in_basis_support() const;

    /*!
    * Returns the element enrichment levels in a basis support constructed in call to perform_enrichment. These are indexed by basis function index.
    * Correspond to the element inds found at the same index in mElementIndsInBasis.
    */
    Cell<moris::Matrix< moris::IndexMat >> const &
    get_element_enrichment_levels_in_basis_support() const;


    // ----------------------------------------------------------------------------------
    // Accessing enrichment data
    // ----------------------------------------------------------------------------------

    /*!
     * Returns the vertex enrichment for the provided vertex index
     */
    Vertex_Enrichment const &
    get_vertex_enrichment(moris::moris_index aVertexIndex) const
    {
        MORIS_ASSERT(aVertexIndex<(moris::moris_index)mVertexEnrichments.size(), "Specifed vertex index is out of bounds");
        return mVertexEnrichments(aVertexIndex);
    }

    Vertex_Enrichment &
    get_vertex_enrichment(moris::moris_index aVertexIndex)
    {
        MORIS_ASSERT(aVertexIndex<(moris::moris_index)mVertexEnrichments.size(), "Specifed vertex index is out of bounds");
        return mVertexEnrichments(aVertexIndex);
    }

    /*!
     * Get element to basis connectivity
     */
    moris::Cell<moris::moris_index> const &
    get_element_to_basis_connectivity(moris::moris_index aElementIndex) const
    {
        MORIS_ASSERT(aElementIndex<(moris::moris_index)mElementToBasis.size(),"Element index out of bounds");
        return mElementToBasis(aElementIndex);
    }

    /*!
     * Get element to basis enrichment level connectivity
     */
    moris::Cell<moris::moris_index> const &
    get_element_to_basis_enrichment_level(moris::moris_index aElementIndex) const
    {
        MORIS_ASSERT(aElementIndex<(moris::moris_index)mElementToBasis.size(),"Element index out of bounds");
        return mElementToBasisEnrichmentLevel(aElementIndex);
    }


    moris::Cell<moris::Matrix<moris::IndexMat>> const &
    get_enriched_basis_indices() const
    {
        return mBasisEnrichmentIndices;
    }

    moris::Cell<moris::Matrix<moris::IndexMat>> const &
    get_enriched_basis_bulk_phase() const
    {
        MORIS_ASSERT(mBasisEnrToBulkPhase,"This data is only constructed when mBasisEnrToBulkPhase is true");

        return mBasisEnrichmentBulkPhase;
    }


//    void
//    create_multilevel_enrichments();

    /*
     * Returns a vector of cell fields names to declare in STK mesh if you want to visualize the cell level
     * enrichment fields. cells within each subphase of a given basis function. One field per basis function, one field per child mesh
     */
    Cell<std::string>
    get_cell_enrichment_field_names() const;

    /*
     * Provided an MTK mesh, writes the cell enrichment data onto the mesh. (fields declared from get_cell_enrichment_field_names )
     */
    void
    write_cell_enrichment_to_fields(Cell<std::string>  & aEnrichmentFieldStrs,
                                    mtk::Mesh*           aMeshWithEnrFields) const;


private:

    // enrichment method
    enum Enrichment_Method mEnrichmentMethod;

    // basis rank
    enum EntityRank mBasisRank;

    // index of interpolation
    uint mInterpIndex;

    moris::size_t mNumBulkPhases;

    // Pointers to Model, Cut and Background meshes (since they are used in most functions)
    Model*    mXTKModelPtr              = nullptr;
    Cut_Mesh* mCutMeshPtr               = nullptr;
    Background_Mesh* mBackgroundMeshPtr = nullptr;
    Enrichment_Parameters mParameters;

    // Enrichment Data ordered by basis function indices
    // For each basis function, the element indices and elemental subphases
    Cell<moris::Matrix< moris::IndexMat >> mElementEnrichmentLevel;
    Cell<moris::Matrix< moris::IndexMat >> mElementIndsInBasis;
    Cell<xtk::Vertex_Enrichment>           mVertexEnrichments;

    // element to basis and enrichment level connectivity
    // for a given element, the basis function and enrichment level of that basis function
    // (transpose of mElementIndsInBasis)
    //TODO: Only store parent element to basis and element index to enrichment level
    moris::Cell<moris::Cell<moris::moris_index>> mElementToBasis;
    moris::Cell<moris::Cell<moris::moris_index>> mElementToBasisEnrichmentLevel;

    // Basis enrichment level indics
    moris::Cell<moris::Matrix<moris::IndexMat>> mBasisEnrichmentIndices;

    // Unintersected Parent Cell, Basis interpolating in them and corresponding enrichment level
    // outer cell corresponds to interp cell index
    // inncer cell corrsponds to basis/enrlev in intepr cell
    Cell<Cell< moris_index >> mInterpCellBasis;
    Cell<Cell< moris_index >> mInterpCellBasisEnrLev;

    moris::Cell<moris::Matrix<moris::IndexMat>> mBasisEnrichmentBulkPhase;

    // total number of basis enrichment levels (all basis functions)
    moris::uint mNumEnrichmentLevels;

    moris::Matrix< DDSMat >  mEnrichedMultilevelBasis;
    moris::Matrix< DDSMat >  mLevelOfEnrichedMultilevelBasis;
    moris::Matrix< DDSMat >  mEnrichmentToBasisIndex;
    moris::Matrix< DDSMat >  mEnrichmentToBulk;

    // Multigrid member data
    moris::Cell<moris::Matrix< DDSMat >> mChildrenToParents;
    moris::Cell<moris::Matrix< DDSMat >> mParentsToChildren;

    /*
     * Performs enrichment on elements in support of full basis cluster. This enrichment includes all children elements of parents in
     * the basis cluster and parent elements with no children
     * @param[in] aCutMesh - Mesh containing elements around the interface
     * @param[in] aBackgroundMesh - Background mesh (Lagrangian Mesh)
     * @param[in] aMatrixFactory - Means of creating matrix objects
     */
    void
    perform_basis_cluster_enrichment();

    void
    construct_neighborhoods();


    /*
     * Starting from the full element to element graph of elements in the support of basis aBasisIndex,  removes elements from
     *  this graph that are not in the support, creating a pruned element to element graph
     * @param[in] aNumFacePerElement - Number of faces per given element
     * @param[in] aElementsInSupport - Elements in support of basis
     * @param[in] aCutMesh - Mesh containing elements around the interface
     * @param[in] aBackgroundMesh - Background mesh (Lagrangian Mesh)
     * @param[in] aMatrixFactory - Means of creating matrix objects
     * @param[out] Cell(0) Pruned element to element graph only including the elements found in the aElementsInPrunedGraph vector
     *             Cell(1) Pruned shared faces
     */
    Cell<moris::Matrix< moris::IndexMat >>
    generate_pruned_element_graph_in_basis_support(moris::size_t const &                     aNumFacePerElement,
                                                    moris::Matrix< moris::IndexMat > const & aElementsInSupport);


    /*
     * Constructs the subphase bin neighboorhood graph within the support of a basis function (think of element to element graph but for sub-phase bins).
     * This is accomplished by tieing subphase bins across parent element borders.
     * @param[in] aParentElementsInSupport      - Parent elements in support of basis
     * @param[in] aNumSubPhaseBins              - Number of subphase bins in support of basis
     * @param[in] aSubphaseBinIndexToCMBinIndex - Map from child mesh index and child mesh bin index to basis bin index
     * @param[in] aPrunedElementGraph           - Pruned parent element graph only including parent elements in basis support
     * @param[in] aPrunedSharedFaces            - Shared faces corresponding to aPrunedElementGraph
     * @param[in] aCutMesh                      - Mesh containing elements around the interface
     * @param[in] aBackgroundMesh               - Background mesh (Lagrangian Mesh)
     * @param[in] aMatrixFactory                - Means of creating matrix objects
     */
    moris::Matrix< moris::IndexMat >
    construct_subphase_bin_neighborhood(moris::Matrix< moris::IndexMat > const &                    aParentElementsInSupport,
                                        moris::size_t                    const &                    aNumSubPhaseBins,
                                        std::unordered_map<moris::moris_index,moris::moris_index> & aSubphaseBinIndexToCMBinIndex,
                                        moris::Matrix< moris::IndexMat > const &                    aPrunedElementGraph,
                                        moris::Matrix< moris::IndexMat > const &                    aPrunedSharedFaces);


    void
    construct_subphase_bin_to_subphase_bin_2_child_interface(
            moris::moris_index const &                                  aParentElementIndex0,
            moris::moris_index const &                                  aParentElementIndex1,
            moris::moris_index const &                                  aSharedFaceIndex,
            std::unordered_map<moris::moris_index,moris::moris_index> & aSubphaseBinIndexToCMBinIndex,
            moris::Matrix< moris::IndexMat > &                          aSubphaseBinToSubphaseBin,
            moris::Matrix< moris::DDSTMat >  &                          aSubphaseBinCounter);


    void
    construct_subphase_bin_to_subphase_bin_mixed_interface(
            moris::moris_index const &                                   aParentElementWithChildren,
            moris::moris_index const &                                   aParentElementWithoutChildren,
            moris::moris_index const &                                   aSharedFaceIndex,
            std::unordered_map<moris::moris_index,moris::moris_index> &  aSubphaseBinIndexToCMBinIndex,
            moris::Matrix< moris::IndexMat > &                           aSubphaseBinToSubphaseBin,
            moris::Matrix< moris::DDSTMat > &                            aSubphaseBinCounter);


    void
    construct_subphase_bin_to_subphase_bin_2_parent_interface(
            moris::moris_index const &                                 aParentElementIndex0,
            moris::moris_index const &                                 aParentElementIndex1,
            std::unordered_map<moris::moris_index,moris::moris_index>  aSubphaseBinIndexToCMBinIndex,
            moris::Matrix< moris::IndexMat > &                         aSubphaseBinToSubphaseBin,
            moris::Matrix< moris::DDSTMat >  &                         aSubphaseBinCounter);

    /*
     *  Assigns enrichment levels to each of the sub-phase bins in support of a basis function by considering local sub-phase bins and
     *  cross parent element boundary bins tieing.
     * @param[in] aParentElementsInSupport      - Parent elements in support of basis
     * @param[in] aNumSubPhaseBins              - Number of subphase bins in support of basis
     * @param[in] aSubPhaseBinBulkPhase         - Bulk phase index of each of the subphase bins
     * @param[in] aSubphaseBinIndexToCMBinIndex - Map from child mesh index and child mesh bin index to basis bin index
     * @param[in] aPrunedElementGraph           - Pruned parent element graph only including parent elements in basis support
     * @param[in] aPrunedSharedFaces            - Shared faces corresponding to aPrunedElementGraph
     * @param[in] aCutMesh                      - Mesh containing elements around the interface
     * @param[in] aBackgroundMesh               - Background mesh (Lagrangian Mesh)
     * @param[in] aMatrixFactory                - Means of creating matrix objects
     */
    moris::Matrix< moris::IndexMat >
    assign_subphase_bin_enrichment_levels_in_basis_support(moris::Matrix< moris::IndexMat > const &                     aParentElementsInSupport,
                                                           moris::size_t const &                                              aNumSubPhaseBins,
                                                           moris::Matrix< moris::IndexMat > const &                     aSubPhaseBinBulkPhase,
                                                           std::unordered_map<moris::moris_index, moris::moris_index> & aSubphaseBinIndexToCMBinIndex,
                                                           moris::Matrix< moris::IndexMat > const &                     aPrunedElementGraph,
                                                           moris::Matrix< moris::IndexMat > const &                     aPrunedSharedFaces);

    moris::size_t
    setup_all_subphase_bins_in_basis_support(moris::Matrix< moris::IndexMat > const &               aParentElementsInSupport,
                                             std::unordered_map<moris::moris_index,moris::moris_index> & aSubphaseBinIndexToCMBinIndex,
                                             moris::Matrix< moris::IndexMat > &                  aSubPhaseBinBulkPhase);


    void
    unzip_subphase_bin_enrichment_into_element_enrichment(moris_index                                                  aBasisIndex,
                                                          moris::Matrix< moris::IndexMat > const &                     aParentElementsInSupport,
                                                          std::unordered_map<moris::moris_index, moris::moris_index> & aSubphaseBinIndexToCMBinIndex,
                                                          moris::Matrix< moris::IndexMat > const &                     aSubPhaseBinEnrichmentLevel,
                                                          moris::Matrix< moris::IndexMat > &                           aElementIndInBasisSupport,
                                                          moris::Matrix< moris::IndexMat > &                           aElementEnrichmentLevel);


    void
    setup_vertex_enrichment_data();

    void
    construct_enriched_interpolation_mesh();

    void
    construct_enriched_integration_mesh();

    void
    allocate_interpolation_cells();

    //FIXME: this needs to be done in parallel
    void
    construct_enriched_interpolation_vertices_and_cells();

    void
    construct_enriched_vertex_interpolation(mtk::Vertex_Interpolation* aBaseVertexInterp,
                                            Cell<moris_index> const &  aSubPhaseBasisEnrLev,
                                            std::unordered_map<moris_id,moris_id> & aMapBasisIndexToLocInSubPhase,
                                            Vertex_Enrichment &        aVertexEnrichment);


    std::unordered_map<moris_id,moris_id>
    construct_subphase_basis_to_basis_map(Cell<moris_id> const & aSubPhaseBasisIndex);

    moris::size_t
    count_subphase_bins_in_support(moris::Matrix< moris::IndexMat > const & aParentElementsInSupport);

    /*
     * Given parent elements from the background mesh, counts all children of these parent elements.
     * Used for sizing of matrices for next step
     * @param[in] aParentElementsInSupport - Parent element index in support of the basis function
     * @param[in] aCutMesh                 - Mesh containing elements around the interface
     * @param[in] aBackgroundMesh          - Background mesh (Lagrangian Mesh)
     */
    moris::size_t
    count_elements_in_support(moris::Matrix< moris::IndexMat > const &            aParentElementsInSupport);


    /*!
     * Construct element to basis connectivity and corresponding enrichment level
     */
    void
    construct_element_to_basis_connectivity(moris::Cell<moris::Cell<moris::moris_index>> & aElementToBasis,
                                            moris::Cell<moris::Cell<moris::moris_index>> & aElementToBasisEnrichmentLevel);

    void
    construct_xtk_created_vertices_to_background_mesh_vertices(moris::Cell<moris::Cell<moris::moris_index>> & aXTKVertsToBGVerts,
                                                               moris::Cell<moris::Cell<moris::real>> & aXTKVertsToBGVertsWeights);


    /*!
     * Using element to basis connectivity construct node to basis connectivity
     */
    void
    construct_vertex_to_basis_connectivity(moris::Cell<moris::Cell<moris::moris_index>>  const & aXTKVertsToBGVerts,
                                           moris::Cell<moris::Cell<moris::real>> const &         aXTKVertsToBGVertsWeights,
                                           moris::Cell< moris::Matrix<moris::IndexMat> > &       aVertexToBasisIndex,
                                           moris::Cell< moris::Matrix<moris::DDRMat> > &         aVertexToBasisWeights);


    void
    construct_vertex_to_basis_map(moris::Cell< moris::Matrix<moris::IndexMat> > & aVertexToBasisIndex);

    void
    clear_vertex_to_basis_maps();

    void
    add_vertex_to_basis_weights(moris::Cell< moris::Matrix<moris::IndexMat> > const & aVertexToEnrichedBasisIndex,
                                moris::Cell< moris::Matrix<moris::DDRMat> >   const & aVertexToBasisWeights);

    void
    construct_vertex_to_enriched_basis_with_element_to_basis(moris::Cell<moris::Cell<moris::moris_index>> const & aElementToBasis,
                                                      moris::Cell<moris::Cell<moris::moris_index>> const & aElementToBasisEnrichmentLevel,
                                                      moris::Cell< moris::Matrix<moris::IndexMat> > const & aVertexToBasisIndex,
                                                      moris::Cell< moris::Matrix<moris::DDRMat> >  const & aVertexToBasisWeights);



    void
    determine_background_vertex_enriched_basis(moris::Cell<moris::Cell<moris::moris_index>>  const & aElementToBasis,
                                               moris::Cell<moris::Cell<moris::moris_index>>  const & aElementToBasisEnrichmentLevel,
                                               moris::Cell< moris::Matrix<moris::IndexMat> > const & aVertexToBasisIndex,
                                               moris::Cell< moris::Matrix<moris::IndexMat> > & aVertexToEnrichedBasis);

    /*
     * Assigns each enrichment level at the basis function a local proc index and globally unique id
     */
    void
    assign_enrichment_level_identifiers();

    /*!
     * Stores the bulk phase associated with each basis enrichment level
     */
    void
    set_up_basis_enrichment_to_bulk_phase();

//    void
//    create_multilevel_children_to_parent_relations();
//
//    void
//    create_multilevel_parent_to_children_relations();




};
}
#endif /* XTK_SRC_XTK_CL_XTK_ENRICHMENT_HPP_ */
