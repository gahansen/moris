/*
 * cl_MTK_Exodus_IO_Helper.hpp
 *
 *  Created on: Nov 26, 2018
 *      Author: doble
 */

#ifndef PROJECTS_MTK_SRC_CL_MTK_EXODUS_IO_HELPER_HPP_
#define PROJECTS_MTK_SRC_CL_MTK_EXODUS_IO_HELPER_HPP_

#include <exodusII.h>
#include <ne_nemesisI.h>

#include "cl_Matrix.hpp"

namespace moris
{
    namespace mtk
    {
        class Exodus_IO_Helper
        {
            private:

                int  mErrFlag = true;
                bool mVerbose = false;

                // general mesh info
                int mNumDim       = -1;
                int mNumNodes     = -1;
                int mNumElem      = -1;
                int mNumElemBlk   = -1;
                int mNumNodeSets  = -1;
                int mNumSideSets  = -1;
                char * mTitle     = nullptr;

                // Coordinates
                Matrix<DDRMat> mX;
                Matrix<DDRMat> mY;
                Matrix<DDRMat> mZ;

                // GLobal information
                int mNumNodesGlobal    = -1;
                int mNumElemsGlobal    = -1;
                int mNumElemBlksGlobal = -1;
                int mNumNodeSetsGlobal = -1;
                int mNumSideSetsGlobal = -1;

                std::vector<int> mGlobalElemBlkIds;
                std::vector<int> mGlobalElemBlkCnts;

                // Communication Map information
                int mExoFileId         = -1;
                int mNumInternalNodes  = -1;
                int mNumBorderNodes    = -1;
                int mNumExternalNodes  = -1;
                int mNumInternalElems  = -1;
                int mNumBorderElems    = -1;
                int mNumNodeCmaps      = -1;
                int mNumElemCmaps      = -1;

                Matrix<IdMat> mNodeCmapIds;
                Matrix<IdMat> mNodeCmapNodeCnts;
                Matrix<IdMat> mElemCmapIds;
                Matrix<IdMat> mElemCmapElemCnts;

                moris::Cell<Matrix<IdMat>> mNodeCmapNodeIds;
                moris::Cell<Matrix<IdMat>> mNodeCmapProcIds;

                std::vector<int> mGlobalNodesetIds;
                std::vector<int> mNumGlobalNodeCounts;
                std::vector<int> mNumGlobalNodeDfCounts;

                Matrix<IdMat> mElemMapi;
                Matrix<IdMat> mElemMapb;
                Matrix<IdMat> mNodeMapi;
                Matrix<IdMat> mNodeMapb;
                Matrix<IdMat> mNodeMape;
                Matrix<IdMat> mNodeNumMap;
                Matrix<IdMat> mElemNumMap;

                // Node Sets
                std::vector<int>              mNodeSetIds;
                std::vector<int>              mNodeSetNEntries;
                std::vector<int>              mNodeSetDistFactors;
                std::vector<char>             mNodeSetNamesMemory;
                std::vector<char*>            mNodeSetNamePtrs;
                std::vector<Matrix<IndexMat>> mNodeSetNodeIds;

                // Side Sets
                std::vector<int>              mSideSetIds;
                std::vector<int>              mSideSetNEntries;
                std::vector<int>              mSideSetDistFactors;
                std::vector<char>             SideSetNamesMemory;
                std::vector<char*>            mSideSetNamePtrs;
                std::vector<Matrix<IndexMat>> mSideSetElemIds;
                std::vector<Matrix<IndexMat>> mSideSetSideOrd;

                // Block sets
                std::vector<int>   mBlockIds;
                std::vector<int>   mBlockSetNEntries;
                std::vector<int>   mBlockSetNNodesPerEntry;
                std::vector<int>   mBlockSetNedgesPerEntry;
                std::vector<int>   mBlockSetNfacesPerEntry;
                std::vector<int>   mBlockSetNattrPerEntry;
                std::vector<char>  mBlockNamesMemory;
                std::vector<char*> mBlockNamesPtrs;
                std::vector<char>  mBlockElemTypeNamesMemory;
                std::vector<char*> mBlockElemTypeNamesPtrs;
                std::vector<Matrix<IndexMat>> mBlockSetNodeConn;
                std::vector<Matrix<IndexMat>> mBlockSetEdgeConn;
                std::vector<Matrix<IndexMat>> mBlockSetFaceConn;

                // Nodal Fields
                int                         mNumNodalVars  = -1;
                int                         mNumTimeSteps  = -1;
                int                         mTimeStepIndex = 0;
                real                        mTimeValue     = -1.0;

                std::vector<char>           mNodeFieldNamesMemory;
                std::vector<char*>          mNodeFieldNamePtrs;
                std::vector<Matrix<DDRMat>> mFieldsNodalVars;

                void
                get_init_mesh_data();

                void
                get_load_bal_parameters();

                void
                get_cmap_params();

                void
                get_node_cmap();

                void get_init_global();

                void
                get_eb_info_global();

                void
                get_node_coords();

                void
                get_ns_param_global();

                void
                get_node_map();

                void
                get_node_id_map();

                void
                get_elem_id_map();

                void
                get_set_information();

                void
                get_nodal_fields();

                void
                reload_nodal_fields();

                void
                copy_coordinates(int tNewExoFileId);

                void
                copy_node_sets(int aNewExoFileId);

                void
                copy_side_sets(int aNewExoFileId);


                void
                copy_block_sets(int aNewExoFileId);

                void
                copy_nodal_fields(
                        int              aNewExoFileId,
                        ex_init_params & init_params);

                /*
                 * from seacas test rd_wt_mesh.c
                 *
                 */
                void get_file_name(
                        const char *base,
                        const char *other,
                        char       *output);

                static void setup_names(
                        int nnames, std::vector<char>& storage,
                        std::vector<char*>           & ptrs);

            public:

                Exodus_IO_Helper(
                        const char * aExodusFile,
                        const int    aTimeStepIndex = 0,
                        const bool   aVerbose = false);

                ~Exodus_IO_Helper();

                //------------------------------------------------------------------------------
                /*
                 * @brief returns number of dimension
                 *
                 */

                int get_number_of_dimensions()
                {
                    return mNumDim;
                }

                //------------------------------------------------------------------------------
                /*
                 * @brief returns number of dimension
                 *
                 */

                int get_number_of_nodes()
                {
                    return mNumNodes;
                }

                //------------------------------------------------------------------------------
                /*
                 * @brief returns number of elements
                 *
                 */

                int get_number_of_elements()
                {
                    return mNumElem;
                }

                //------------------------------------------------------------------------------
                /*
                 * @brief returns number of elements
                 *
                 */

                int get_number_of_blocks()
                {
                    return mNumElemBlk;
                }

                //------------------------------------------------------------------------------
                /*
                 * @brief returns number of node sets
                 *
                 */

                int get_number_of_node_sets()
                {
                    return mNumNodeSets;
                }

                //------------------------------------------------------------------------------
                /*
                 * @brief returns number of node sets
                 *
                 */

                int get_number_of_side_sets()
                {
                    return mNumSideSets;
                }

                //------------------------------------------------------------------------------
                /*
                 * @brief returns absolute time for currently loaded time step
                 *
                 */

                real get_time_value()
                {
                    return mTimeValue;
                }

                //------------------------------------------------------------------------------
                /*
                 * @brief returns vector with coordinates of node, size: number of dimensions x 1
                 *
                 * @param[ in ] aNodeId   id of node
                 */

                moris::Matrix<DDRMat> get_nodal_coordinate( uint aNodeId );

                //------------------------------------------------------------------------------
                /*
                 * @brief returns node index given a node Id
                 *
                 * @param[ in ] aNodeId   id of node
                 */

                uint
                get_node_index_by_Id( uint aNodeId)
                {
                    // find index of node given its nodeId
                    auto tItr = std::find(mNodeNumMap.data(),mNodeNumMap.data()+mNumNodes,aNodeId);

                    // compute index
                    uint tIndex = std::distance(mNodeNumMap.data(),tItr);

                    // check that exactly one node index was found
                    MORIS_ASSERT( tIndex < (uint) mNumNodes, "Node not found");

                    return tIndex;
                }

                //------------------------------------------------------------------------------
                /*
                 * @brief returns nodal field value of node defined by its Id
                 *
                 * @param[ in ] aNodeId     id of node
                 * @param[ in ] aFieldInd   index of field
                 */

                real
                get_nodal_field_value( uint aNodeId, uint aFieldIndex, uint aTimeStepIndex);

                //------------------------------------------------------------------------------
                /*
                 * Create a new exodus file and the information for an element communication map
                 * Copy the exodus file in this Exodus_IO_Helper to a new one with the
                 * communication map. This is because once the exodus file has been setup,
                 * the element communication map cannot be appended
                 *
                 */
                void
                create_new_exo_with_elem_cmaps_from_existing_exo(
                        std::string    & aFileName,
                        Matrix<IdMat>  & aElementIds,
                        Matrix<IdMat>  & aElementSideOrds,
                        Matrix<IdMat>  & aSharedProcIds);
        };
    }
}

#endif /* PROJECTS_MTK_SRC_CL_MTK_EXODUS_IO_HELPER_HPP_ */
