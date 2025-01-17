/*
 * Copyright (c) 2022 University of Colorado
 * Licensed under the MIT license. See LICENSE.txt file in the MORIS root for details.
 *
 *------------------------------------------------------------------------------------
 *
 * cl_XTK_Decomposition_Data.hpp
 *
 */

#ifndef PROJECTS_XTK_SRC_XTK_CL_XTK_DECOMPOSITION_DATA_HPP_
#define PROJECTS_XTK_SRC_XTK_CL_XTK_DECOMPOSITION_DATA_HPP_

#include "cl_Matrix.hpp"
#include "cl_Cell.hpp"
#include "cl_XTK_Topology.hpp"
#include "cl_Mesh_Enums.hpp"
#include "cl_MTK_Mesh_Core.hpp"
#include "cl_MTK_Vertex.hpp"
using namespace moris;

namespace xtk
{
    struct Decomposition_Data
    {
            Decomposition_Data() :
                tCMNewNodeLoc( 0, 0 ),
                tNewNodeIndex( 0, 0 ),
                tNewNodeId( 0, 0 ),
                tNewNodeOwner( 0, 0 ),
                tNewNodeParentIndex( 0, 0 ),
                tNewNodeParentRank( 0, EntityRank::INVALID ),
                tNewNodeCoordinate( 0, Matrix< DDRMat >( 0, 0 ) ),
                mNumNewNodesWithIds( 0 )
            {
            }

            ~Decomposition_Data()
            {
                for ( uint i = 0; i < tNewNodeParentTopology.size(); i++ )
                {
                    delete tNewNodeParentTopology( i );
                }
            }

            /*!
             * Returns whether the request has been made and the request location
             * relative to tCMNewNodeLoc cell if it is not a new one aRequestLoc = MORIS_INDEX_MAX
             */
            bool
            request_exists( moris_index aParentEntityIndex,
                    enum EntityRank         aParentEntityRank,
                    moris_index&            aRequestLoc )
            {
                MORIS_ASSERT( !mHasSecondaryIdentifier, "request_exists without a secondary identifier argument should only be called when the decomposition does not need secondary identifiers" );
                bool tRequestExists = false;
                aRequestLoc         = MORIS_INDEX_MAX;
                switch ( aParentEntityRank )
                {
                    case EntityRank::ELEMENT:
                    {
                        auto tIter = tElementIndexToNodeLoc.find( aParentEntityIndex );
                        if ( tIter != tElementIndexToNodeLoc.end() )
                        {
                            tRequestExists = true;
                            aRequestLoc    = tIter->second;
                        }
                        break;
                    }
                    case EntityRank::FACE:
                    {
                        auto tIter = tFaceIndexToNodeLoc.find( aParentEntityIndex );
                        if ( tIter != tFaceIndexToNodeLoc.end() )
                        {
                            tRequestExists = true;
                            aRequestLoc    = tIter->second;
                        }
                        break;
                    }
                    case EntityRank::EDGE:
                    {

                        break;
                    }
                    default:
                    {
                        MORIS_ERROR( 0, "Invalid parent entity rank. Nodes are not supported in this request method at this time" );
                        return false;
                        break;
                    }
                }

                return tRequestExists;
            }

            /*!
             *
             */
            bool
            request_exists( moris_index aParentEntityIndex,
                    moris_index             aParentSecondaryIdentifier,
                    enum EntityRank         aParentEntityRank,
                    moris_index&            aRequestLoc )
            {
                MORIS_ASSERT( mHasSecondaryIdentifier,
                        "request_exists with a secondary identifier argument should only be called when the decomposition does not need secondary identifiers" );
                bool tRequestExists = false;
                aRequestLoc         = MORIS_INDEX_MAX;

                switch ( aParentEntityRank )
                {
                    case EntityRank::ELEMENT:
                    {
                        auto tIter = tElementIndexToNodeLoc.find( aParentEntityIndex );

                        // if the iterator is not in the map then this is a request made on a parent element which has not had any requests in it yet.
                        if ( tIter == tElementIndexToNodeLoc.end() )
                        {
                            break;
                        }

                        // If the parent entity has requests on it, look if the secondary identifier shows up in the second map
                        else
                        {
                            // location of parent entity cell with secondary map
                            moris_index tParentEntityLoc = tIter->second;

                            auto tSecondIter = mElementIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc ).find( aParentSecondaryIdentifier );
                            if ( tSecondIter != mElementIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc ).end() )
                            {
                                aRequestLoc    = tSecondIter->second;
                                tRequestExists = true;
                            }
                        }
                        break;
                    }
                    case EntityRank::FACE:
                    {
                        auto tIter = tFaceIndexToNodeLoc.find( aParentEntityIndex );

                        // if the iterator is not in the map then this is a request made on a parent face which has not had any requests in it yet.
                        if ( tIter == tFaceIndexToNodeLoc.end() )
                        {
                            break;
                        }

                        // If the parent entity has requests on it, look if the secondary identifier shows up in the second map
                        else
                        {
                            // location of parent entity in cell of secondary maps
                            moris_index tParentEntityLoc = tIter->second;

                            // iterator of the secondary identifier
                            auto tSecondIter = mFaceIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc ).find( aParentSecondaryIdentifier );

                            // if this secondary identifier does not show up then, it is a new request
                            if ( tSecondIter != mFaceIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc ).end() )
                            {
                                tRequestExists = true;
                                aRequestLoc    = tSecondIter->second;
                            }
                        }
                        break;
                    }
                    case EntityRank::EDGE:
                    {
                        auto tIter = mEdgeIndexToNodeLoc.find( aParentEntityIndex );

                        // if the iterator is not in the map then this is a request made on a parent face which has not had any requests in it yet.
                        if ( tIter == mEdgeIndexToNodeLoc.end() )
                        {
                            break;
                        }

                        // If the parent entity has requests on it, look if the secondary identifier shows up in the second map
                        else
                        {
                            // location of parent entity in cell of secondary maps
                            moris_index tParentEntityLoc = tIter->second;

                            // iterator of the secondary identifier
                            auto tSecondIter = mEdgeIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc ).find( aParentSecondaryIdentifier );

                            // if this secondary identifier does not show up then, it is a new request
                            if ( tSecondIter != mEdgeIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc ).end() )
                            {
                                tRequestExists = true;
                                aRequestLoc    = tSecondIter->second;
                            }
                        }
                        break;
                    }
                    default:
                    {
                        MORIS_ERROR( 0, "Invalid parent entity rank. Nodes are not supported in this request method at this time" );
                        return false;
                        break;
                    }
                } // end: switch ( aParentEntityRank )

                return tRequestExists;
            }

            moris_index
            register_new_request(
                    moris_index                         aParentEntityIndex,
                    moris_index                         aParentEntityOwner,
                    enum EntityRank                     aParentEntityRank,
                    Matrix< DDRMat > const&             aNewNodeCoord,
                    moris::mtk::Cell*                   aNewVertexParentCell,
                    std::shared_ptr< Matrix< DDRMat > > aNewVertexLocalCooridnates )
            {
                MORIS_ASSERT( !mHasSecondaryIdentifier, "register_new_request w/o a secondary identifier should only be used when secondary identifiers are not necessary, this is because the maps in this data structure are slightly different between the two cases" );

                moris_index tRequestIndex = tNewNodeIndex.size();

                // push back the location for the node id and index
                // maximum value here because it is not known
                tNewNodeIndex.push_back( MORIS_INDEX_MAX );
                tNewNodeId.push_back( MORIS_INDEX_MAX );
                tNewNodeOwner.push_back( aParentEntityOwner );

                // add node parent information
                tNewNodeParentIndex.push_back( aParentEntityIndex );
                tNewNodeParentRank.push_back( aParentEntityRank );
                tNewNodeCoordinate.push_back( aNewNodeCoord );
                mNewNodeParentCells.push_back( aNewVertexParentCell );
                mNewVertexLocalCoordWRTParentCell.push_back( aNewVertexLocalCooridnates );

                switch ( aParentEntityRank )
                {
                    case EntityRank::ELEMENT:
                    {
                        // Check if this entity already exists in debug only
                        MORIS_ASSERT( tElementIndexToNodeLoc.find( aParentEntityIndex ) == tElementIndexToNodeLoc.end(), "New request being made which already exists" );

                        // add to map
                        tElementIndexToNodeLoc[aParentEntityIndex] = tRequestIndex;
                        break;
                    }
                    case EntityRank::FACE:
                    {
                        // Check if this entity already exists in debug only
                        MORIS_ASSERT( tFaceIndexToNodeLoc.find( aParentEntityIndex ) == tFaceIndexToNodeLoc.end(), "New request being made which already exists" );

                        // add to map
                        tFaceIndexToNodeLoc[aParentEntityIndex] = tRequestIndex;
                        break;
                    }
                    case EntityRank::EDGE:
                    {
                        // Check if this entity already exists in debug only
                        MORIS_ASSERT( tEdgeIndexToNodeLoc.find( aParentEntityIndex ) == tEdgeIndexToNodeLoc.end(), "New request being made which already exists" );

                        // add to map
                        tEdgeIndexToNodeLoc[aParentEntityIndex] = tRequestIndex;
                        break;
                    }
                    default:
                    {
                        MORIS_ERROR( 0, "Invalid parent entity rank. Nodes are not supported in this request method at this time" );
                        return false;
                        break;
                    }
                }

                return tRequestIndex;
            }

            moris_index
            register_new_request(
                    moris_index                         aParentEntityIndex,
                    moris_index                         aSecondaryIdentifier,
                    moris_index                         aParentEntityOwner,
                    enum EntityRank                     aParentEntityRank,
                    Matrix< DDRMat > const&             aNewNodeCoord,
                    moris::mtk::Cell*                   aNewVertexParentCell       = nullptr,
                    std::shared_ptr< Matrix< DDRMat > > aNewVertexLocalCooridnates = nullptr )
            {
                MORIS_ASSERT( mHasSecondaryIdentifier, "register_new_request with a secondary identifier should only be used when secondary identifiers are not necessary, this is because the maps in this data structure are slightly different between the two cases" );

                moris_index tRequestIndex = tNewNodeIndex.size();

                // push back the location for the node id and index
                // maximum value here because it is not known
                tNewNodeIndex.push_back( MORIS_INDEX_MAX );
                tNewNodeId.push_back( MORIS_INDEX_MAX );

                tNewNodeOwner.push_back( aParentEntityOwner );

                // add node parent information
                tNewNodeParentIndex.push_back( aParentEntityIndex );
                tNewNodeParentRank.push_back( aParentEntityRank );
                tSecondaryIdentifiers.push_back( aSecondaryIdentifier );
                tNewNodeCoordinate.push_back( aNewNodeCoord );

                // for octree refinement
                mNewNodeParentCells.push_back( aNewVertexParentCell );
                mNewVertexLocalCoordWRTParentCell.push_back( aNewVertexLocalCooridnates );

                // add information to the maps
                switch ( aParentEntityRank )
                {
                    case EntityRank::ELEMENT:
                    {
                        auto tIter = tElementIndexToNodeLoc.find( aParentEntityIndex );

                        // if this parent entity has no requests made we need to setup some things
                        if ( tIter == tElementIndexToNodeLoc.end() )
                        {
                            // cell where this parent entity is going to
                            moris::moris_index tParentEntityLoc        = mElementIndexToSecondaryIdAndNewNodeLoc.size();
                            tElementIndexToNodeLoc[aParentEntityIndex] = tParentEntityLoc;
                            mElementIndexToSecondaryIdAndNewNodeLoc.push_back( std::unordered_map< moris_index, moris_index >() );
                        }

                        moris_index tParentEntityLoc = tElementIndexToNodeLoc[aParentEntityIndex];

                        // check that the secondary id does not exist already
                        MORIS_ASSERT( mElementIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc ).find( aSecondaryIdentifier ) == mElementIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc ).end(), "New request being made which already exists" );

                        // add to map
                        mElementIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc )[aSecondaryIdentifier] = tRequestIndex;
                        break;
                    }
                    case EntityRank::FACE:
                    {
                        auto tIter = tFaceIndexToNodeLoc.find( aParentEntityIndex );

                        // if this parent entity has no requests made we need to setup some things
                        if ( tIter == tFaceIndexToNodeLoc.end() )
                        {
                            // cell where this parent entity is going to
                            moris::moris_index tParentEntityLoc = mFaceIndexToSecondaryIdAndNewNodeLoc.size();

                            tFaceIndexToNodeLoc[aParentEntityIndex] = tParentEntityLoc;

                            mFaceIndexToSecondaryIdAndNewNodeLoc.push_back( std::unordered_map< moris_index, moris_index >() );
                        }

                        moris_index tParentEntityLoc = tFaceIndexToNodeLoc[aParentEntityIndex];

                        // check that the secondary id exists
                        MORIS_ASSERT( mFaceIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc ).find( aSecondaryIdentifier ) == mFaceIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc ).end(), "New request being made which already exists" );

                        // add to map
                        mFaceIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc )[aSecondaryIdentifier] = tRequestIndex;
                        break;
                    }
                    case EntityRank::EDGE:
                    {

                        auto tIter = mEdgeIndexToNodeLoc.find( aParentEntityIndex );

                        // if this parent entity has no requests made we need to setup some things
                        if ( tIter == mEdgeIndexToNodeLoc.end() )
                        {
                            // cell where this parent entity is going to
                            moris::moris_index tParentEntityLoc = mEdgeIndexToSecondaryIdAndNewNodeLoc.size();

                            mEdgeIndexToNodeLoc[aParentEntityIndex] = tParentEntityLoc;

                            mEdgeIndexToSecondaryIdAndNewNodeLoc.push_back( std::unordered_map< moris_index, moris_index >() );
                        }

                        moris_index tParentEntityLoc = mEdgeIndexToNodeLoc[aParentEntityIndex];

                        // check that the secondary id exists
                        MORIS_ASSERT( mEdgeIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc ).find( aSecondaryIdentifier ) == mEdgeIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc ).end(), "New request being made which already exists" );

                        // add to map
                        mEdgeIndexToSecondaryIdAndNewNodeLoc( tParentEntityLoc )[aSecondaryIdentifier] = tRequestIndex;
                        break;
                    }
                    default:
                    {
                        MORIS_ERROR( 0, "Invalid parent entity rank. Nodes are not supported in this request method at this time" );
                        return false;
                        break;
                    }
                }
                return tRequestIndex;
            }

            void
            print_requests(
                    moris::mtk::Mesh const& aBackgroundMesh,
                    std::string             aFile = "" )
            {
                std::stringstream oSS;
                oSS << "Request_Index,";
                oSS << "PRank,";
                oSS << "Parent_Id,";
                oSS << "Secondary_Id,";
                oSS << "Parent_Rank,";
                for ( size_t iSPH = 0; iSPH < aBackgroundMesh.get_spatial_dim(); iSPH++ )
                {
                    oSS << "Coords_" << std::to_string( iSPH );
                    if ( iSPH != aBackgroundMesh.get_spatial_dim() - 1 )
                    {
                        oSS << ",";
                    }
                }

                oSS << "\n";

                for ( moris::uint i = 0; i < tNewNodeId.size(); i++ )
                {
                    oSS << i << ",";
                    oSS << par_rank() << ",";
                    oSS << aBackgroundMesh.get_glb_entity_id_from_entity_loc_index( tNewNodeParentIndex( i ), tNewNodeParentRank( i ) );
                    oSS << tSecondaryIdentifiers( i );
                    oSS << get_enum_str( tNewNodeParentRank( i ) );
                    for ( moris::uint j = 0; j < aBackgroundMesh.get_spatial_dim(); j++ )
                    {
                        oSS << std::scientific << tNewNodeCoordinate( i )( j );
                        if ( j != aBackgroundMesh.get_spatial_dim() - 1 )
                        {
                            oSS << ",";
                        }
                    }
                    oSS << "\n";
                }
                if ( aFile.empty() == false )
                {
                    std::ofstream tOutputFile( aFile );
                    tOutputFile << oSS.str() << std::endl;
                    tOutputFile.close();
                }
            }

            void
            print(
                    moris::mtk::Mesh const& aBackgroundMesh,
                    std::string             aFile = "" )
            {
                // std::stringstream oSS;
                // oSS << "Request_Index,";
                // oSS << "PRank,";
                // oSS << "Parent_Id,";
                // oSS << "Secondary_Id,";
                // oSS << "Parent_Rank,";
                // oSS << "New_Vert_Id,";
                // oSS << "New_Vert_Index,";
                // for ( size_t iSPH = 0; iSPH < aBackgroundMesh.get_spatial_dim(); iSPH++ )
                // {
                //     oSS << "Coords_" << std::to_string( iSPH );
                //     if ( iSPH != aBackgroundMesh.get_spatial_dim() - 1 )
                //     {
                //         oSS << ",";
                //     }
                // }

                // oSS << "\n";

                // for ( moris::uint i = 0; i < tNewNodeId.size(); i++ )
                // {
                //     oSS << i << ",";
                //     oSS << par_rank() << ",";
                //     oSS << aBackgroundMesh.get_glb_entity_id_from_entity_loc_index( tNewNodeParentIndex( i ), tNewNodeParentRank( i ) ) << ",";
                //     oSS << tSecondaryIdentifiers( i ) << ",";
                //     oSS << get_enum_str( tNewNodeParentRank( i ) ) << ",";
                //     oSS << tNewNodeId( i ) << ",";
                //     oSS << tNewNodeIndex( i ) << ",";

                //     for ( moris::uint j = 0; j < aBackgroundMesh.get_spatial_dim(); j++ )
                //     {
                //         oSS << std::scientific << tNewNodeCoordinate( i )( j );
                //         if ( j != aBackgroundMesh.get_spatial_dim() - 1 )
                //         {
                //             oSS << ",";
                //         }
                //     }
                //     oSS << "\n";
                // }
                // if ( aFile.empty() == false )
                // {
                //     std::ofstream tOutputFile( aFile );
                //     tOutputFile << oSS.str() << std::endl;
                //     tOutputFile.close();
                // }
            }

            moris_index tDecompId = 0;

            // Store the decomposition method here (used for assertion purposes)
            enum Subdivision_Method mSubdivisionMethod = Subdivision_Method::NO_METHOD;

            // Specify whether the decomposition is conformal or note
            // needed to tell geometry engine to store the edge a node was created once
            bool mConformalDecomp        = false;
            bool mHasSecondaryIdentifier = false;
            bool mFirstSubdivision       = false;

            // Active child mesh to its nodes location in tNewNodeIndex
            Cell< Cell< moris_index > >      tCMNewNodeLoc;         // input: Cell group index || output: list of edge indices
            Cell< Cell< Matrix< DDRMat > > > tCMNewNodeParamCoord;  // input: Cell group index || output: list of coordinates
            /* Note: this stores some duplicate parametric coordinates but is necessary for flexible use*/

            // New node indices
            Cell< moris_index > tNewNodeIndex;

            // new node ids
            Cell< moris_index > tNewNodeId;

            // new node owner
            Cell< moris_index > tNewNodeOwner;

            // hanging nodes between procs
            Cell< moris_index > tNewNodeHangingFlag;
            Cell< moris_index > tNewNodeHangingWRTProcRank;

            // New node parent topology
            Cell< Topology* > tNewNodeParentTopology;

            Cell< moris::mtk::Cell* >                   mNewNodeParentCells;
            Cell< std::shared_ptr< Matrix< DDRMat > > > mNewVertexLocalCoordWRTParentCell;

            // new node vertex dependencies
            Cell< std::shared_ptr< Cell< moris::mtk::Vertex* > > > mNewVertexParentVertices;

            Cell< std::shared_ptr< Matrix< DDRMat > > > mNewVertexBasisWeights;

            // Parent index of a new node
            Cell< moris_index > tNewNodeParentIndex;

            // Parent entity secondary identifier
            Cell< moris_index > tSecondaryIdentifiers;

            // Parent entity rank
            Cell< enum EntityRank > tNewNodeParentRank;

            // new node coordinate
            Cell< Matrix< DDRMat > > tNewNodeCoordinate;

            // new node parametric coordinate relative to parent entity
            Cell< Matrix< DDRMat > > tParamCoordRelativeToParent;

            // map from elements to location in tNewNodeParentIndex
            std::unordered_map< moris_index, moris_index > tElementIndexToNodeLoc;

            Cell< std::unordered_map< moris_index, moris_index > > mElementIndexToSecondaryIdAndNewNodeLoc;

            // map from face to location in tNewNodeParentIndex
            std::unordered_map< moris_index, moris_index > tFaceIndexToNodeLoc;

            // Face index to secondary identifiers
            // outer cell - Face index
            // inner map - iter->first  = secondary id
            //             iter->second = new node location
            Cell< std::unordered_map< moris_index, moris_index > > mFaceIndexToSecondaryIdAndNewNodeLoc;

            std::unordered_map< moris_index, moris_index >         mEdgeIndexToNodeLoc;
            Cell< std::unordered_map< moris_index, moris_index > > mEdgeIndexToSecondaryIdAndNewNodeLoc;

            // map from edge to location in tNewNodeParentIndex
            std::unordered_map< moris_index, moris_index > tEdgeIndexToNodeLoc;

            // number of new nodes which have been assigned identifiers
            uint mNumNewNodesWithIds;
    };
}// namespace xtk

#endif /* PROJECTS_XTK_SRC_XTK_CL_XTK_DECOMPOSITION_DATA_HPP_ */

