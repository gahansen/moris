/*
 * cl_XTK_Child_Mesh_Test_NH_Permutations.cpp
 *
 *  Created on: Jun 25, 2018
 *      Author: ktdoble
 */

#ifndef UNIT_TEST_SRC_XTK_CL_XTK_CHILD_MESH_TEST_NH_PERMUTATIONS_CPP_
#define UNIT_TEST_SRC_XTK_CL_XTK_CHILD_MESH_TEST_NH_PERMUTATIONS_CPP_

#include "catch.hpp"

#include "linalg/cl_XTK_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "op_plus.hpp"

#include "xtk/cl_XTK_Child_Mesh_Modification_Template.hpp"
#include "xtk/fn_local_child_mesh_flood_fill.hpp"
#include "mesh/fn_verify_tet_topology.hpp"
#include "geomeng/fn_Triangle_Geometry.hpp" // For surface normals



#include <chrono>
#include <thread>
#include <iostream>
#include "xtk/cl_XTK_Child_Mesh.hpp"


namespace xtk
{
class Permutations
{
public:
    Permutations(std::string tType = "")

{
        if(tType.compare("") == 0)
        {
            this->load_all_permutations();
        }

        else if(tType.compare("pa") == 0)
        {
            this->load_pos_a_permutations();
        }

        else if(tType.compare("na") == 0)
        {
            this->load_neg_a_permutations();
        }

        else if (tType.compare("pb") == 0)
        {
            this->load_pos_b_permutations();
        }
        else if (tType.compare("nb") == 0)
        {
            this->load_neg_b_permutations();
        }

        else if (tType.compare("pc") == 0)
        {
            this->load_pos_c_permutations();
        }

        else if (tType.compare("nc") == 0)
        {
            this->load_neg_c_permutations();
        }
        else if (tType.compare("3p") == 0)
        {
            this->load_pos_3_permutations();
        }
        else if (tType.compare("3n") == 0)
        {
            this->load_neg_3_permutations();
        }
        else
        {
            std::cout<<"String Not Recognized"<<std::endl;
        }
        mNumPermutations = mPermutations.size();
}

    size_t get_num_permutations()
    {
        return mNumPermutations;
    }

    Cell<size_t> get_permutation(size_t aIndex)
                                {
        return mPermutations(aIndex);
                                }
private:
    size_t mNumPermutations;
    Cell<Cell<size_t>> mPermutations;


private:
    void load_all_permutations()
    {
        mPermutations = {
                         {0,2,4,5},
                         {0,2,5,4},
                         {0,4,2,5},
                         {0,4,5,2},
                         {0,5,2,4},
                         {0,5,4,2},

                         {2,0,4,5},
                         {2,0,5,4},
                         {2,4,0,5},
                         {2,4,5,0},
                         {2,5,0,4},
                         {2,5,4,0},

                         {4,0,2,5},
                         {4,0,5,2},
                         {4,2,0,5},
                         {4,2,5,0},
                         {4,5,0,2},
                         {4,5,2,0},


                         {5,0,2,4},
                         {5,0,4,2},
                         {5,2,0,4},
                         {5,2,4,0},
                         {5,4,0,2},
                         {5,4,2,0},

                         {0,1,3,5},
                         {0,1,5,3},
                         {0,3,1,5},
                         {0,3,5,1},
                         {0,5,1,3},
                         {0,5,3,1},

                         {1,0,3,5},
                         {1,0,5,3},
                         {1,3,0,5},
                         {1,3,5,0},
                         {1,5,0,3},
                         {1,5,3,0},

                         {3,0,1,5},
                         {3,0,5,1},
                         {3,1,0,5},
                         {3,1,5,0},
                         {3,5,0,1},
                         {3,5,1,0},

                         {5,0,1,3},
                         {5,0,3,1},
                         {5,1,0,3},
                         {5,1,3,0},
                         {5,3,0,1},
                         {5,3,1,0},

                         {2,1,3,4},
                         {2,1,4,3},
                         {2,3,1,4},
                         {2,3,4,1},
                         {2,4,1,3},
                         {2,4,3,1},

                         {1,2,3,4},
                         {1,2,4,3},
                         {1,3,2,4},
                         {1,3,4,2},
                         {1,4,2,3},
                         {1,4,3,2},

                         {3,2,1,4},
                         {3,2,4,1},
                         {3,1,2,4},
                         {3,1,4,2},
                         {3,4,2,1},
                         {3,4,1,2},

                         {4,2,1,3},
                         {4,2,3,1},
                         {4,1,2,3},
                         {4,1,3,2},
                         {4,3,2,1},
                         {4,3,1,2}
        };
    }

    void load_pos_a_permutations()
    {


        mPermutations = {{0,2,4,5},  // 5420
                         {0,4,2,5},  // 5240
                         {5,4,2,0},  // 245
                         {5,2,4,0},  // 425
                         {1,0,5,3},  // 3501
                         {3,0,5,1},  // 1503
                         {1,5,0,3},  // 3051
                         {3,5,0,1},  // 1053
                         {2,1,3,4},  // 4312
                         {4,1,3,2},  // 2314
                         {2,3,1,4},  // 4132
                         {4,3,1,2}}; //2134

    }

    void load_neg_a_permutations()
    {
        mPermutations = {{2,0,5,4},
                         {2,5,0,4},
                         {4,0,5,2},
                         {4,5,0,2},
                         {0,1,3,5},
                         {0,3,1,5},
                         {5,3,1,0},
                         {5,1,3,0},
                         {1,2,4,3},
                         {1,4,2,3},
                         {3,2,4,1},
                         {3,4,2,1}};

    }

    void load_pos_b_permutations()
    {
        mPermutations = {{0,5,2,4},
                         {0,5,4,2},
                         {5,0,2,4},
                         {5,0,4,2},
                         {1,3,0,5},
                         {3,1,0,5},
                         {1,3,5,0},
                         {3,1,5,0},
                         {4,2,1,3},
                         {2,4,3,1},
                         {4,2,3,1},
                         {2,4,1,3}};
    }

    void load_neg_b_permutations()
    {
        mPermutations = {{4,2,0,5},
                         {4,2,5,0},
                         {2,4,0,5},
                         {2,4,5,0},
                         {0,5,1,3},
                         {0,5,3,1},
                         {5,0,1,3},
                         {5,0,3,1},
                         {1,3,2,4},
                         {1,3,4,2},
                         {3,1,2,4},
                         {3,1,4,2}};
    }

    void load_pos_c_permutations()
    {

        mPermutations = {{0,2,5,4},
                         {0,4,5,2},
                         {5,2,0,4},
                         {5,4,0,2},
                         {1,0,3,5},
                         {3,0,1,5},
                         {1,5,3,0},
                         {3,5,1,0},
                         {2,1,4,3},
                         {4,1,2,3},
                         {2,3,4,1},
                         {4,3,2,1}};
    }

    void load_neg_c_permutations()
    {
        mPermutations = {{2,0,4,5},
                         {2,5,4,0},
                         {4,0,2,5},
                         {4,5,2,0},
                         {0,1,5,3},
                         {0,3,5,1},
                         {5,1,0,3},
                         {5,3,0,1},
                         {1,2,3,4},
                         {1,4,3,2},
                         {3,2,1,4},
                         {3,4,1,2}};
    }

    void load_pos_3_permutations()
    {
        mPermutations = {{0,2,3,0},
                         {2,3,0,0},
                         {3,0,2,0},
                         {1,5,2,0},
                         {2,1,5,0},
                         {5,2,1,0},
                         {0,4,1,0},
                         {1,0,4,0},
                         {4,1,0,0},
                         {3,5,4,0},
                         {4,3,5,0},
                         {5,4,3,0}};
    }

    void load_neg_3_permutations()
    {

        mPermutations = {{0,3,2,0},
                         {2,0,3,0},
                         {3,2,0,0},
                         {1,2,5,0},
                         {2,5,1,0},
                         {5,1,2,0},
                         {0,1,4,0},
                         {1,4,0,0},
                         {4,0,1,0},
                         {3,4,5,0},
                         {4,5,3,0},
                         {5,3,4,0}};

    }

};

template<typename Real_Matrix>
void
get_midside_coordinate(size_t const & aEdgeIndex,
                       moris::Matrix< Real_Matrix > & aMidEdgeCoordinate)
{
    if( aEdgeIndex == 0)
    {
        aMidEdgeCoordinate(0,0) = 0.5;  aMidEdgeCoordinate(0,1) = 0.0;  aMidEdgeCoordinate(0,2) = 0.0;
    }

    else if( aEdgeIndex == 1)
    {
        aMidEdgeCoordinate(0,0) = 0.5;  aMidEdgeCoordinate(0,1) = 0.5;  aMidEdgeCoordinate(0,2) = 0.0;
    }

    else if( aEdgeIndex == 2)
    {
        aMidEdgeCoordinate(0,0) = 0.0;  aMidEdgeCoordinate(0,1) = 0.5;  aMidEdgeCoordinate(0,2) = 0.0;
    }

    else if( aEdgeIndex == 3)
    {
        aMidEdgeCoordinate(0,0) = 0.0;  aMidEdgeCoordinate(0,1) = 0.0;  aMidEdgeCoordinate(0,2) = 0.5;
    }

    else if( aEdgeIndex == 4)
    {
        aMidEdgeCoordinate(0,0) = 0.5;  aMidEdgeCoordinate(0,1) = 0.0;  aMidEdgeCoordinate(0,2) = 0.5;
    }

    else if( aEdgeIndex == 5)
    {
        aMidEdgeCoordinate(0,0) = 0.0;  aMidEdgeCoordinate(0,1) = 0.5;  aMidEdgeCoordinate(0,2) = 0.5;
    }
    else
    {
        XTK_ERROR<<"INVALID EDGE"<<std::endl;
    }
}

template< typename Real_Matrix>
void
setup_node_coordinates_3_node(size_t const & tEdgeL,
                              size_t const & tEdgeM,
                              size_t const & tEdgeH,
                              moris::Matrix< Real_Matrix > & aNodeCoordinates)
{
    moris::Matrix< Real_Matrix > tEdgeNodeCoordinates(1,3,75);

    aNodeCoordinates = moris::Matrix< Real_Matrix >(7,3);
    aNodeCoordinates(0,0) =  0.0;     aNodeCoordinates(0,1) =  0.0;     aNodeCoordinates(0,2) =  0.0;
    aNodeCoordinates(1,0) =  1.0;     aNodeCoordinates(1,1) =  0.0;     aNodeCoordinates(1,2) =  0.0;
    aNodeCoordinates(2,0) =  0.0;     aNodeCoordinates(2,1) =  1.0;     aNodeCoordinates(2,2) =  0.0;
    aNodeCoordinates(3,0) =  0.0;     aNodeCoordinates(3,1) =  0.0;     aNodeCoordinates(3,2) =  1.0;

    get_midside_coordinate(tEdgeL, tEdgeNodeCoordinates);
    aNodeCoordinates(4,0) = tEdgeNodeCoordinates(0,0);     aNodeCoordinates(4,1) =  tEdgeNodeCoordinates(0,1);     aNodeCoordinates(4,2) =  tEdgeNodeCoordinates(0,2);

    get_midside_coordinate(tEdgeM, tEdgeNodeCoordinates);
    aNodeCoordinates(5,0) = tEdgeNodeCoordinates(0,0);     aNodeCoordinates(5,1) =  tEdgeNodeCoordinates(0,1);     aNodeCoordinates(5,2) =  tEdgeNodeCoordinates(0,2);

    get_midside_coordinate(tEdgeH, tEdgeNodeCoordinates);
    aNodeCoordinates(6,0) = tEdgeNodeCoordinates(0,0);     aNodeCoordinates(6,1) =  tEdgeNodeCoordinates(0,1);     aNodeCoordinates(6,2) =  tEdgeNodeCoordinates(0,2);

}

template<typename Real_Matrix>
void
setup_node_coordinates_4_node(size_t const & tEdgeL,
                              size_t const & tEdgeML,
                              size_t const & tEdgeMH,
                              size_t const & tEdgeH,
                              moris::Matrix< Real_Matrix > & aNodeCoordinates)
{
    moris::Matrix< Real_Matrix > tEdgeNodeCoordinates(1,3,75);

    aNodeCoordinates = moris::Matrix< Real_Matrix >(8,3);
    aNodeCoordinates(0,0) =  0.0;     aNodeCoordinates(0,1) =  0.0;     aNodeCoordinates(0,2) =  0.0;
    aNodeCoordinates(1,0) =  1.0;     aNodeCoordinates(1,1) =  0.0;     aNodeCoordinates(1,2) =  0.0;
    aNodeCoordinates(2,0) =  0.0;     aNodeCoordinates(2,1) =  1.0;     aNodeCoordinates(2,2) =  0.0;
    aNodeCoordinates(3,0) =  0.0;     aNodeCoordinates(3,1) =  0.0;     aNodeCoordinates(3,2) =  1.0;

    get_midside_coordinate(tEdgeL, tEdgeNodeCoordinates);
    aNodeCoordinates(4,0) = (tEdgeNodeCoordinates)(0,0);     aNodeCoordinates(4,1) =  (tEdgeNodeCoordinates)(0,1);     aNodeCoordinates(4,2) =  (tEdgeNodeCoordinates)(0,2);

    get_midside_coordinate(tEdgeML, tEdgeNodeCoordinates);
    aNodeCoordinates(5,0) = (tEdgeNodeCoordinates)(0,0);     aNodeCoordinates(5,1) =  (tEdgeNodeCoordinates)(0,1);     aNodeCoordinates(5,2) =  (tEdgeNodeCoordinates)(0,2);

    get_midside_coordinate(tEdgeMH, tEdgeNodeCoordinates);
    aNodeCoordinates(6,0) = (tEdgeNodeCoordinates)(0,0);     aNodeCoordinates(6,1) =  (tEdgeNodeCoordinates)(0,1);     aNodeCoordinates(6,2) =  (tEdgeNodeCoordinates)(0,2);

    get_midside_coordinate(tEdgeH, tEdgeNodeCoordinates);
    aNodeCoordinates(7,0) = (tEdgeNodeCoordinates)(0,0);     aNodeCoordinates(7,1) =  (tEdgeNodeCoordinates)(0,1);     aNodeCoordinates(7,2) =  (tEdgeNodeCoordinates)(0,2);
}


TEST_CASE("NEW Node Hierarchy Template 3 Node Case Permutations","[3_NODE_NEW]")
{
    // Tests:
    // Floodfill which checks whether the element to element connectivity is traversable
    // Topology which checks whether the new tets have the correct topology
    // Face ancestry check using surface normals of tri
    // Number of child faces created on parent face

    moris::Matrix< Default_Matrix_Integer > tNodeIndex({{0,1,2,3}});

    moris::Matrix< Default_Matrix_Integer > tNodeIds({{1,2,3,4,5,6,7}});


    moris::Matrix< Default_Matrix_Integer > tElementsAncestry({{0}}); // Not used
    moris::Matrix< Default_Matrix_Integer > tParentEdgeInds({{0,1,2,3,4,5}});
    moris::Matrix< Default_Matrix_Integer > tParentEdgeRanks(1,6,1);
    moris::Matrix< Default_Matrix_Integer > tParentFaceInds({{0,1,2,3}});
    moris::Matrix< Default_Matrix_Integer > tParentFaceRanks(1,4,2);

    Cell<std::string> tCaseStrings = {"3p","3n"};
    for(size_t iCase = 0; iCase<tCaseStrings.size(); iCase++)
    {
        /*
         * Initialize Permutations
         */
        std::string & tCases = tCaseStrings(iCase);
        Permutations tPermutations(tCases);
        size_t tNumPermutations = tPermutations.get_num_permutations();

        for(size_t iPerm = 0; iPerm<tNumPermutations; iPerm++)
        {
            // Initialize Template
            Mesh_Modification_Template<real,size_t,Default_Matrix_Real,Default_Matrix_Integer> tMeshTemplate(tElementsAncestry(0,0),
                                                                                                             0,
                                                                                                             tNodeIndex,
                                                                                                             tParentEdgeInds,
                                                                                                             tParentEdgeRanks,
                                                                                                             tParentFaceInds,
                                                                                                             tParentFaceRanks,
                                                                                                             TemplateType::TET_4);

            // Initialize child mesh with template (in this case a tet4)
            Child_Mesh_Test<real,size_t,Default_Matrix_Real,Default_Matrix_Integer> tChildMesh(tMeshTemplate);


            // add new node indices
            tChildMesh.add_node_indices({{4,5,6}});
            tChildMesh.add_node_ids(tNodeIds);

            // select template
            Cell<size_t> tCurrentPermutation = tPermutations.get_permutation(iPerm);
            size_t tEdgeL  = tCurrentPermutation(0);
            size_t tEdgeM = tCurrentPermutation(1);
            size_t tEdgeH = tCurrentPermutation(2);

            size_t tPermutationId = 100*tEdgeH + 10*tEdgeM + tEdgeL;

            // Set up node coordinates
            moris::Matrix< Default_Matrix_Real > tNodeCoords;
            setup_node_coordinates_3_node(tEdgeL,tEdgeM,tEdgeH,tNodeCoords);

            // Compute base tet volume
            real tTetVol = compute_volume_for_multiple_tets(tNodeCoords,tChildMesh.get_element_to_node());


            // Compute base element surface normals (parent faces)
            moris::Matrix< Default_Matrix_Integer > const & tParentFaceToNode = tChildMesh.get_face_to_node();
            size_t tNumParentFaces = tParentFaceToNode.n_rows();
            moris::Matrix< Default_Matrix_Real > tParentFaceNormals(3,tNumParentFaces);

            // Iterate through and compute all face normals
            for( size_t iF = 0; iF<tNumParentFaces; iF++)
            {
                // Get face iF nodes
                moris::Matrix< Default_Matrix_Integer > tFaceNodes = tParentFaceToNode.get_row(iF);

                moris::Matrix< Default_Matrix_Real > tFaceNormal(3,1,9.0);
                compute_tri_surface_normal( tFaceNodes,tNodeCoords, tFaceNormal, true);

                tParentFaceNormals.set_column(iF,tFaceNormal);
            }

            // Initialize/set  intersection connectivity in child mehs
            moris::Matrix< Default_Matrix_Integer > tIntersectConn({{3,4,5,6,UINT_MAX,UINT_MAX,UINT_MAX,tEdgeL,tEdgeM,tEdgeH,UINT_MAX,UINT_MAX,UINT_MAX}});
            tChildMesh.set_intersect_connectivity(tIntersectConn);

            tChildMesh.modify_child_mesh(TemplateType::HIERARCHY_TET4);

            // Verify that if we set each element to the same bulk phase we can traverse the element to element connectivity
            size_t tMax = std::numeric_limits<size_t>::max();
            size_t tNumPhases = 2;
            moris::Matrix< Default_Matrix_Integer > tActiveElements({{0,1,2,3}});
            moris::Matrix< Default_Matrix_Integer > tIncludedElementMarker(1,4,1);
            moris::Matrix< Default_Matrix_Integer > tElementPhase(1,4,0);
            moris::Matrix< Default_Matrix_Integer > tElementSubphase =
            flood_fill( tChildMesh.get_element_to_element(),
                        tElementPhase,
                        tActiveElements,
                        tIncludedElementMarker,
                        tNumPhases,
                        tMax,
                        true);

            moris::Matrix< Default_Matrix_Integer > tExpElementSubphase(1,4,0);
            CHECK(equal_to(tExpElementSubphase,tElementSubphase));

            // Verify that the tets created have correct topology
            bool tValidTopo = verify_tet4_topology(tChildMesh.get_element_to_node(),
                                                   tChildMesh.get_element_to_edge(),
                                                   tChildMesh.get_element_to_face(),
                                                   tChildMesh.get_edge_to_node(),
                                                   tChildMesh.get_face_to_node());

            CHECK(tValidTopo);

            // verify volume is conserved
            real tTotalChildVol = compute_volume_for_multiple_tets(tNodeCoords,tChildMesh.get_element_to_node());;

            CHECK(approximate(tTetVol,tTotalChildVol));


            // Check ancestry of faces
            moris::Matrix< Default_Matrix_Integer > const & tFaceToNode      = tChildMesh.get_face_to_node();
            moris::Matrix< Default_Matrix_Integer > const & tFaceParentInds  = tChildMesh.get_face_parent_inds();
            moris::Matrix< Default_Matrix_Integer > const & tFaceParentRanks = tChildMesh.get_face_parent_ranks();
            size_t tNumFaces = tFaceToNode.n_rows();
            moris::Matrix< Default_Matrix_Real > tFaceNormals(3,tNumFaces);

            // Iterate through and compute all face normals
            for( size_t iF = 0; iF<tNumFaces; iF++)
            {
                // Get face iF nodes
                moris::Matrix< Default_Matrix_Integer > tFaceNodes = tFaceToNode.get_row(iF);

                moris::Matrix< Default_Matrix_Real > tFaceNormal(3,1,9.0);
                compute_tri_surface_normal( tFaceNodes,tNodeCoords, tFaceNormal, true);

                tFaceNormals.set_column(iF,tFaceNormal);
            }

            // Check to see if the surface normal matches parent face normals
            // Count for number of children faces born on a parent face
            size_t tChildFacewithParentFaceRank = 0;
            for( size_t iF = 0; iF<tNumFaces; iF++)
            {
                if( tFaceParentRanks(0,iF) == 2)
                {
                    moris::Matrix< Default_Matrix_Real > tChildFaceNormal  = tFaceNormals.get_column(iF);
                    moris::Matrix< Default_Matrix_Real > tParentFaceNormal = tParentFaceNormals.get_column(tFaceParentInds(0,iF));
                    tChildFacewithParentFaceRank++;
                    CHECK(equal_to(tChildFaceNormal, tParentFaceNormal));
                }
            }
            CHECK(tChildFacewithParentFaceRank == 10);

        }
    }
}

TEST_CASE("NEW Node Hierarchy Template 4 Node Case Permutations","[4_NODE_NEW]")
{
    // Tests:
    // Floodfill which checks whether the element to element connectivity is traversable
    // Topology which checks whether the new tets have the correct topology

    moris::Matrix< Default_Matrix_Integer > tNodeIndex({{0,1,2,3}});

    moris::Matrix< Default_Matrix_Integer > tNodeIds({{1,2,3,4,5,6,7,8}});


    moris::Matrix< Default_Matrix_Integer > tElementsAncestry({{0}}); // Not used
    moris::Matrix< Default_Matrix_Integer > tParentEdgeInds({{0,1,2,3,4,5}});
    moris::Matrix< Default_Matrix_Integer > tParentEdgeRanks(1,6,1);
    moris::Matrix< Default_Matrix_Integer > tParentFaceInds({{0,1,2,3}});
    moris::Matrix< Default_Matrix_Integer > tParentFaceRanks(1,4,2);

    Cell<std::string> tCaseNames = {"pa","na","pb","nb","pc","nc"};
    for(size_t iCase = 0; iCase<tCaseNames.size(); iCase++)
    {
        /*
         * Initialize Permutations
         */
        std::string & tCases = tCaseNames(iCase);
        Permutations tPermutations(tCases);
        size_t tNumPermutations = tPermutations.get_num_permutations();

        for(size_t iPerm = 0; iPerm<tNumPermutations; iPerm++)
        {

            // Initialize Template
            Mesh_Modification_Template<real,size_t,Default_Matrix_Real,Default_Matrix_Integer> tMeshTemplate(tElementsAncestry(0,0),
                                                                                                             0,
                                                                                                             tNodeIndex,
                                                                                                             tParentEdgeInds,
                                                                                                             tParentEdgeRanks,
                                                                                                             tParentFaceInds,
                                                                                                             tParentFaceRanks,
                                                                                                             TemplateType::TET_4);

            // Initialize child mesh with template (in this case a tet4)
            Child_Mesh_Test<real,size_t,Default_Matrix_Real,Default_Matrix_Integer> tChildMesh(tMeshTemplate);


            // add new node indices
            tChildMesh.add_node_indices({{4,5,6,7}});
            tChildMesh.add_node_ids(tNodeIds);

            // select template
            Cell<size_t> tCurrentPermutation = tPermutations.get_permutation(iPerm);
            size_t tEdgeL  = tCurrentPermutation(0);
            size_t tEdgeML = tCurrentPermutation(1);
            size_t tEdgeMH = tCurrentPermutation(2);
            size_t tEdgeH  = tCurrentPermutation(3);

            size_t tPermutationId = 1000*tEdgeH + 100*tEdgeMH + 10 * tEdgeML + tEdgeL;

            // Set up node coordinates
            moris::Matrix< Default_Matrix_Real > tNodeCoords;
            setup_node_coordinates_4_node(tEdgeL,tEdgeML,tEdgeMH,tEdgeH,tNodeCoords);
            // Compute base tet volume
            real tTetVol = compute_volume_for_multiple_tets(tNodeCoords,tChildMesh.get_element_to_node());


            // Compute base element surface normals (parent faces)
            moris::Matrix< Default_Matrix_Integer > const & tParentFaceToNode = tChildMesh.get_face_to_node();
            size_t tNumParentFaces = tParentFaceToNode.n_rows();
            moris::Matrix< Default_Matrix_Real > tParentFaceNormals(3,tNumParentFaces);

            // Iterate through and compute all face normals
            for( size_t iF = 0; iF<tNumParentFaces; iF++)
            {
                // Get face iF nodes
                moris::Matrix< Default_Matrix_Integer > tFaceNodes = tParentFaceToNode.get_row(iF);

                moris::Matrix< Default_Matrix_Real > tFaceNormal(3,1,9.0);
                compute_tri_surface_normal( tFaceNodes,tNodeCoords, tFaceNormal, true);

                tParentFaceNormals.set_column(iF,tFaceNormal);
            }

            // Initialize/set  intersection connectivity in child mehs
            moris::Matrix< Default_Matrix_Integer > tIntersectConn({{4,4,5,6,7,UINT_MAX,UINT_MAX,tEdgeL,tEdgeML,tEdgeMH,tEdgeH,UINT_MAX,UINT_MAX}});
            tChildMesh.set_intersect_connectivity(tIntersectConn);

            tChildMesh.modify_child_mesh(TemplateType::HIERARCHY_TET4);

            // Verify that if we set each element to the same bulk phase we can traverse the element to element connectivity
            size_t tMax = std::numeric_limits<size_t>::max();
            size_t tNumPhases = 2;
            moris::Matrix< Default_Matrix_Integer > tActiveElements({{0,1,2,3,4,5}});
            moris::Matrix< Default_Matrix_Integer > tIncludedElementMarker(1,6,1);
            moris::Matrix< Default_Matrix_Integer > tElementPhase(1,6,0);
            moris::Matrix< Default_Matrix_Integer > tElementSubphase =
            flood_fill( tChildMesh.get_element_to_element(),
                        tElementPhase,
                        tActiveElements,
                        tIncludedElementMarker,
                        tNumPhases,
                        tMax,
                        true);

            moris::Matrix< Default_Matrix_Integer > tExpElementSubphase(1,6,0);
            CHECK(equal_to(tExpElementSubphase,tElementSubphase));

            // Verify that the tets created have correct topology
            bool tValidTopo = verify_tet4_topology(tChildMesh.get_element_to_node(),
                                                   tChildMesh.get_element_to_edge(),
                                                   tChildMesh.get_element_to_face(),
                                                   tChildMesh.get_edge_to_node(),
                                                   tChildMesh.get_face_to_node());

            CHECK(tValidTopo);

            // verify volume is conserved
            real tTotalChildVol = compute_volume_for_multiple_tets(tNodeCoords,tChildMesh.get_element_to_node());;

            CHECK(approximate(tTetVol,tTotalChildVol));


            // Check ancestry of faces
            moris::Matrix< Default_Matrix_Integer > const & tFaceToNode      = tChildMesh.get_face_to_node();
            moris::Matrix< Default_Matrix_Integer > const & tFaceParentInds  = tChildMesh.get_face_parent_inds();
            moris::Matrix< Default_Matrix_Integer > const & tFaceParentRanks = tChildMesh.get_face_parent_ranks();
            size_t tNumFaces = tFaceToNode.n_rows();
            moris::Matrix< Default_Matrix_Real > tFaceNormals(3,tNumFaces);

            // Iterate through and compute all face normals
            for( size_t iF = 0; iF<tNumFaces; iF++)
            {
                // Get face iF nodes
                moris::Matrix< Default_Matrix_Integer > tFaceNodes = tFaceToNode.get_row(iF);

                moris::Matrix< Default_Matrix_Real > tFaceNormal(3,1,9.0);
                compute_tri_surface_normal( tFaceNodes,tNodeCoords, tFaceNormal, true);

                tFaceNormals.set_column(iF,tFaceNormal);
            }

            // Check to see if the surface normal matches parent face normals
            // Count for number of children faces born on a parent face
            size_t tChildFacewithParentFaceRank = 0;
            for( size_t iF = 0; iF<tNumFaces; iF++)
            {
                if( tFaceParentRanks(0,iF) == 2)
                {
                    moris::Matrix< Default_Matrix_Real > tChildFaceNormal  = tFaceNormals.get_column(iF);
                    moris::Matrix< Default_Matrix_Real > tParentFaceNormal = tParentFaceNormals.get_column(tFaceParentInds(0,iF));
                    tChildFacewithParentFaceRank++;
                    CHECK(equal_to(tChildFaceNormal, tParentFaceNormal));
                }
            }
            CHECK(tChildFacewithParentFaceRank == 12);

        }
    }
}

TEST_CASE("Recursive modification of child mesh","[NH_RECURSION_4_NODE]")
{
    // Tests:
    // Floodfill which checks whether the element to element connectivity is traversable
    // Topology which checks whether the new tets have the correct topology

    moris::Matrix< Default_Matrix_Integer > tNodeIndex({{0,1,2,3}});

    moris::Matrix< Default_Matrix_Integer > tNodeIds({{1,2,3,4,5,6,7,8}});


    moris::Matrix< Default_Matrix_Integer > tElementsAncestry({{0}}); // Not used
    moris::Matrix< Default_Matrix_Integer > tParentEdgeInds({{0,1,2,3,4,5}});
    moris::Matrix< Default_Matrix_Integer > tParentEdgeRanks(1,6,1);
    moris::Matrix< Default_Matrix_Integer > tParentFaceInds({{0,1,2,3}});
    moris::Matrix< Default_Matrix_Integer > tParentFaceRanks(1,4,2);

    Cell<std::string> tCaseNames = {"pa","na","pb","nb","pc","nc"};
//    Cell<std::string> tCaseNames = {"pa"};

    for(size_t iCase = 0; iCase<tCaseNames.size(); iCase++)
    {

        std::string & tCases = tCaseNames(iCase);
        Permutations tPermutations(tCases);
        size_t tNumPermutations = tPermutations.get_num_permutations();
//        size_t tNumPermutations = 1;

        // Second template insertion permutation
        for(size_t iPerm2 = 0; iPerm2<tNumPermutations; iPerm2++)
        {
            // select template
            Cell<size_t> tCurrentPermutation = tPermutations.get_permutation(iPerm2);

            // Edge ordinals
            size_t tEdgeOrdL2  = tCurrentPermutation(0);
            size_t tEdgeOrdML2 = tCurrentPermutation(1);
            size_t tEdgeOrdMH2 = tCurrentPermutation(2);
            size_t tEdgeOrdH2  = tCurrentPermutation(3);

            size_t tPermutationId2 = 1000*tEdgeOrdH2 + 100*tEdgeOrdMH2 + 10 * tEdgeOrdML2 + tEdgeOrdL2;

            // First template insertion permutation
            for(size_t iPerm1 = 0; iPerm1<tNumPermutations; iPerm1++)
            {

               // Initialize Template
                Mesh_Modification_Template<real,size_t,Default_Matrix_Real,Default_Matrix_Integer> tMeshTemplate(tElementsAncestry(0,0),
                                                                                                                 0,
                                                                                                                 tNodeIndex,
                                                                                                                 tParentEdgeInds,
                                                                                                                 tParentEdgeRanks,
                                                                                                                 tParentFaceInds,
                                                                                                                 tParentFaceRanks,
                                                                                                                 TemplateType::TET_4);

                // Initialize child mesh with template (in this case a tet4)
                Child_Mesh_Test<real,size_t,Default_Matrix_Real,Default_Matrix_Integer> tChildMesh(tMeshTemplate);


                // add new node indices
                tChildMesh.add_node_indices({{4,5,6,7}});
                tChildMesh.add_node_ids(tNodeIds);

                // select template
                Cell<size_t> tCurrentPermutation = tPermutations.get_permutation(iPerm1);
                size_t tEdgeL1  = tCurrentPermutation(0);
                size_t tEdgeML1 = tCurrentPermutation(1);
                size_t tEdgeMH1 = tCurrentPermutation(2);
                size_t tEdgeH1  = tCurrentPermutation(3);

                size_t tPermutationId1 = 1000*tEdgeH1 + 100*tEdgeMH1 + 10 * tEdgeML1 + tEdgeL1;

                // Set up node coordinates
                moris::Matrix< Default_Matrix_Real > tNodeCoords;
                setup_node_coordinates_4_node(tEdgeL1,tEdgeML1,tEdgeMH1,tEdgeH1,tNodeCoords);

                // ------------------------------------------------
                // Compute Base Tet Information
                // ------------------------------------------------

                // Compute base tet volume
                real tTetVol = compute_volume_for_multiple_tets(tNodeCoords,tChildMesh.get_element_to_node());

                // Compute base element surface normals (parent faces)
                moris::Matrix< Default_Matrix_Integer > const & tParentFaceToNode = tChildMesh.get_face_to_node();
                size_t tNumParentFaces = tParentFaceToNode.n_rows();
                moris::Matrix< Default_Matrix_Real > tParentFaceNormals(3,tNumParentFaces);

                // Iterate through and compute all face normals
                for( size_t iF = 0; iF<tNumParentFaces; iF++)
                {
                    // Get face iF nodes
                    moris::Matrix< Default_Matrix_Integer > tFaceNodes = tParentFaceToNode.get_row(iF);

                    moris::Matrix< Default_Matrix_Real > tFaceNormal(3,1,9.0);
                    compute_tri_surface_normal( tFaceNodes,tNodeCoords, tFaceNormal, true);

                    tParentFaceNormals.set_column(iF,tFaceNormal);
                }

                // ------------------------------------------------
                // Insert First Template
                // ------------------------------------------------

                // Initialize/set  intersection connectivity in child mesh for first level modification
                moris::Matrix< Default_Matrix_Integer > tIntersectConn({{4,4,5,6,7,UINT_MAX,UINT_MAX,tEdgeL1,tEdgeML1,tEdgeMH1,tEdgeH1,UINT_MAX,UINT_MAX}});
                tChildMesh.set_intersect_connectivity(tIntersectConn);
                tChildMesh.modify_child_mesh(TemplateType::HIERARCHY_TET4);

                // ------------------------------------------------
                // Second Template Insertion
                // ------------------------------------------------
                // Replacing element 0
                // Node Ids for this template
                moris::Matrix< Default_Matrix_Integer > tNodeInds2({{11,10,9,8}});
                moris::Matrix< Default_Matrix_Integer > tNodeIds2({{12,11,10,9}});
                tChildMesh.add_node_indices(tNodeInds2);
                tChildMesh.add_node_ids(tNodeIds);

                // Initialize intersection connectivity
                tChildMesh.init_intersect_connectivity();


                moris::Matrix< Default_Matrix_Integer > const & tElemToEdge = tChildMesh.get_element_to_edge();
                moris::Matrix< Default_Matrix_Integer > const & tEdgeToNode = tChildMesh.get_edge_to_node();
                size_t  tEdgeL2 = tElemToEdge(0,tEdgeOrdL2);
                size_t  tEdgeML2 = tElemToEdge(0,tEdgeOrdML2);
                size_t  tEdgeMH2 = tElemToEdge(0,tEdgeOrdMH2);
                size_t  tEdgeH2 = tElemToEdge(0,tEdgeOrdH2);

                tChildMesh.add_entity_to_intersect_connectivity(8, tEdgeL2 , 1);
                tChildMesh.add_entity_to_intersect_connectivity(9, tEdgeML2, 1);
                tChildMesh.add_entity_to_intersect_connectivity(10, tEdgeMH2, 1);
                tChildMesh.add_entity_to_intersect_connectivity(11, tEdgeH2 , 1);

                // Set up node coordinates for second template insertion
                tNodeCoords.resize(tNodeCoords.n_rows() + 4,tNodeCoords.n_cols());

                moris::Matrix< Default_Matrix_Real > tMidSideCoord(1,3);

                moris::Matrix< Default_Matrix_Real > tN1Coord = tNodeCoords.get_row(tEdgeToNode(tEdgeL2,0));
                moris::Matrix< Default_Matrix_Real > tN2Coord = tNodeCoords.get_row(tEdgeToNode(tEdgeL2,1));

                tMidSideCoord =  0.5 * ( tN1Coord + tN2Coord ) ;
                tNodeCoords.set_row(11,tMidSideCoord);

                tN1Coord = tNodeCoords.get_row(tEdgeToNode(tEdgeML2,0));
                tN2Coord = tNodeCoords.get_row(tEdgeToNode(tEdgeML2,1));
                tMidSideCoord =  0.5 * ( tN1Coord + tN2Coord ) ;
                tNodeCoords.set_row(10,tMidSideCoord);

                tN1Coord = tNodeCoords.get_row(tEdgeToNode(tEdgeMH2,0));
                tN2Coord = tNodeCoords.get_row(tEdgeToNode(tEdgeMH2,1));
                tMidSideCoord =  0.5 * ( tN1Coord + tN2Coord ) ;
                tNodeCoords.set_row(9,tMidSideCoord);


                tN1Coord = tNodeCoords.get_row(tEdgeToNode(tEdgeH2,0));
                tN2Coord = tNodeCoords.get_row(tEdgeToNode(tEdgeH2,1));
                tMidSideCoord =  0.5 * ( tN1Coord + tN2Coord ) ;
                tNodeCoords.set_row(8,tMidSideCoord);

//                print_to_matlab(tNodeCoords.matrix_base(),"tNodeCoords");

                tChildMesh.modify_child_mesh(TemplateType::HIERARCHY_TET4);
//                print_to_matlab(tChildMesh.get_element_to_node().matrix_base(),"tElemNode");

                // ------------------------------------------------
                // Test the Generated Mesh
                // ------------------------------------------------
                size_t tNumElems = tChildMesh.get_num_entities(EntityRank::ELEMENT);

                CHECK(tNumElems == 11);

                // Verify that the tets created have correct topology
                bool tValidTopo = verify_tet4_topology(tChildMesh.get_element_to_node(),
                                                       tChildMesh.get_element_to_edge(),
                                                       tChildMesh.get_element_to_face(),
                                                       tChildMesh.get_edge_to_node(),
                                                       tChildMesh.get_face_to_node());

                CHECK(tValidTopo);

                // verify volume is conserved
                real tTotalChildVol = compute_volume_for_multiple_tets(tNodeCoords,tChildMesh.get_element_to_node());
                CHECK(approximate(tTetVol,tTotalChildVol));


                // Check ancestry of faces
                moris::Matrix< Default_Matrix_Integer > const & tFaceToNode      = tChildMesh.get_face_to_node();
                moris::Matrix< Default_Matrix_Integer > const & tFaceParentInds  = tChildMesh.get_face_parent_inds();
                moris::Matrix< Default_Matrix_Integer > const & tFaceParentRanks = tChildMesh.get_face_parent_ranks();
                size_t tNumFaces = tFaceToNode.n_rows();
                moris::Matrix< Default_Matrix_Real > tFaceNormals(3,tNumFaces);

                // Iterate through and compute all face normals
                for( size_t iF = 0; iF<tNumFaces; iF++)
                {
                    // Get face iF nodes
                    moris::Matrix< Default_Matrix_Integer > tFaceNodes = tFaceToNode.get_row(iF);

                    moris::Matrix< Default_Matrix_Real > tFaceNormal(3,1,9.0);
                    compute_tri_surface_normal( tFaceNodes,tNodeCoords, tFaceNormal, true);

                    tFaceNormals.set_column(iF,tFaceNormal);
                }

                // Check to see if the surface normal matches parent face normals
                // Count for number of children faces born on a parent face
                size_t tChildFacewithParentFaceRank = 0;
                for( size_t iF = 0; iF<tNumFaces; iF++)
                {
                    if( tFaceParentRanks(0,iF) == 2)
                    {
                        moris::Matrix< Default_Matrix_Real > tChildFaceNormal  = tFaceNormals.get_column(iF);
                        moris::Matrix< Default_Matrix_Real > tParentFaceNormal = tParentFaceNormals.get_column(tFaceParentInds(0,iF));
                        tChildFacewithParentFaceRank++;

                        CHECK(equal_to(tChildFaceNormal, tParentFaceNormal));
                    }
                }

            }
        }
    }
}


}


#endif /* UNIT_TEST_SRC_XTK_CL_XTK_CHILD_MESH_TEST_NH_PERMUTATIONS_CPP_ */