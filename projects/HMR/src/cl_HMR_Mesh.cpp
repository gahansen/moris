#include "cl_HMR_Mesh.hpp" //HMR/src

#include <string>

#include "cl_HMR.hpp" //HMR/src
#include "cl_HMR_Database.hpp"
#include "cl_HMR_Field.hpp"
#include "cl_HMR_Lagrange_Mesh_Base.hpp" //HMR/src
#include "cl_HMR_Background_Element.hpp"
#include "cl_HMR_Element.hpp"
#include "MTK_Tools.hpp"
#include "fn_sort.hpp"
#include "fn_unique.hpp"

namespace moris
{
    namespace hmr
    {
//-----------------------------------------------------------------------------

        Mesh::Mesh(       std::shared_ptr< Database >   aDatabase,
                    const uint                        & aLagrangeOrder,
                    const uint                        & aLagrangePattern )
        {
            // copy database pointer
            mDatabase = aDatabase;

            // get number of meshes
            uint tNumberOfMeshes = mDatabase->get_number_of_lagrange_meshes();

            // find correct block
            for( uint k=0; k<tNumberOfMeshes; ++k )
            {
                auto tMesh = mDatabase->get_lagrange_mesh_by_index( k );

                // test if mesh uses active pattern
                if ( tMesh->get_activation_pattern() == aLagrangePattern &&           //FIXME
                     tMesh->get_order() == aLagrangeOrder )
                {
                    mMesh = tMesh;

                    break;
                }
            }

            MORIS_ERROR(mMesh != nullptr, "Mesh::Mesh(), Mesh not found");

            setup_glb_to_local_maps();


//             MORIS_ERROR( mMesh != NULL, "Could not find mesh, do you parameters for lagrange_orders contain the provided aLagrangeOrder?" );
        }

//-----------------------------------------------------------------------------

        Mesh::Mesh(       std::shared_ptr< Database >   aDatabase,
                    const uint                        & aLagrangeMeshIndex )
        {
            // copy database pointer
            mDatabase = aDatabase;

            MORIS_ASSERT( aLagrangeMeshIndex <= mDatabase->get_number_of_lagrange_meshes(), "Could not find mesh, Lagrange mesh index %-5i exceeds number of Lagrange meshes.", aLagrangeMeshIndex );

            mMesh = mDatabase->get_lagrange_mesh_by_index( aLagrangeMeshIndex );

            MORIS_ERROR( mMesh != nullptr, "Pointer to Lagrange mesh %-5i is nullptr", aLagrangeMeshIndex );

//            mDatabase->get_background_mesh()->set_activation_pattern( aLagrangeMeshIndex );

            setup_glb_to_local_maps();
        }

//-----------------------------------------------------------------------------

        Mesh::Mesh(       std::shared_ptr< Database >   aDatabase,
                    const uint                        & aOrder,
                    const uint                        & aLagrangePattern,
                    const uint                        & aBpslinePattern)
        {
            // copy database pointer
            mDatabase = aDatabase;

            mDummyBSplineMeshes.resize( 3, nullptr );
            moris::hmr::Factory tFactory;

            for( uint Ik = 0; Ik<3; Ik++ )
            {
                mDummyBSplineMeshes( Ik ) = tFactory.create_bspline_mesh( mDatabase->get_parameters(),                 //FIXME only one mesh
                                                                          mDatabase->get_background_mesh(),
                                                                          aBpslinePattern,
                                                                          aOrder );
            }

            mMesh = tFactory.create_lagrange_mesh( mDatabase->get_parameters(),
                                                   mDatabase->get_background_mesh(),
                                                   mDummyBSplineMeshes,
                                                   aLagrangePattern,
                                                   aOrder );

            mDatabase->add_lagrange_mesh( mMesh );                                       //FIXME dont add

            // remember active pattern
            auto tActivePattern = mDatabase->get_background_mesh()->get_activation_pattern();

            // activate output pattern
            mDatabase->get_background_mesh()->set_activation_pattern( mMesh->get_activation_pattern() );

            mMesh->update_mesh();

            mMesh->calculate_node_indices();
            mMesh->calculate_node_sharing();
            mMesh->calculate_t_matrices();

            for( auto tMesh : mDummyBSplineMeshes )      //FIXME only one mesh
            {
                tMesh->calculate_basis_indices( mDatabase->get_communication_table() );
            }

            // reset active pattern
            if ( mDatabase->get_background_mesh()->get_activation_pattern() != tActivePattern )
            {
                mDatabase->get_background_mesh()->set_activation_pattern( tActivePattern );
            }
        }

//-----------------------------------------------------------------------------

        Mesh::~Mesh()
        {
            //delete mBlock;
        }


//-----------------------------------------------------------------------------

        Matrix< IdMat > Mesh::get_communication_table() const
        {
            return mDatabase->get_communication_table();
        }

//-----------------------------------------------------------------------------

        std::shared_ptr< Field > Mesh::create_field( const std::string & aLabel, const uint & aBSplineIndex )
        {
            // fixme: this is not the best solution. See also
            // https://forum.libcinder.org/topic/solution-calling-shared-from-this-in-the-constructor

            // create temporary weak pointer so that shared from this works
            auto tWptr = std::shared_ptr<Mesh>( this, [](Mesh*){} );

            // create field
            return std::make_shared< Field >( aLabel,
                                              this->shared_from_this(),
                                              aBSplineIndex,
                                              mDatabase,
                                              mMesh );
        }

//-----------------------------------------------------------------------------
// MTK
//-----------------------------------------------------------------------------

        uint Mesh::get_spatial_dim() const
        {
            return mDatabase->get_parameters()->get_number_of_dimensions();
        }

//-----------------------------------------------------------------------------

        uint Mesh::get_num_entities( enum EntityRank aEntityRank ) const
        {
            switch ( aEntityRank )
            {
                case( EntityRank::NODE ) :
                {
                    return this->get_num_nodes();
                    break;
                }
                case( EntityRank::EDGE ) :
                {
                     return this->get_num_edges();
                     break;
                }
                case( EntityRank::FACE ) :
                {
                     return this->get_num_faces();
                     break;
                }
                case( EntityRank::ELEMENT ) :
                {
                    if( mDatabase->get_parameters()->use_number_aura() )
                    {
                        return this->get_num_elemens_including_aura();
                    }
                    else
                    {
                        return this->get_num_elems();
                    }

                    break;
                }
                // aEntityRank is not unique for Bsplines
//                case( EntityRank::BSPLINE_1 ) :
//                case( EntityRank::BSPLINE_2 ) :
//                case( EntityRank::BSPLINE_3 ) :
//                {
//                    return this->get_num_coeffs( mtk::entity_rank_to_order ( aEntityRank ) );
//                    break;
//                }
                default :
                {
                    MORIS_ERROR( false, "unknown entity rank");
                    return 0;
                    break;
                }
            }
        }
//-----------------------------------------------------------------------------

        uint Mesh::get_num_elemens_including_aura() const
        {
            return mMesh->get_number_of_elements_including_aura();
        }

//-----------------------------------------------------------------------------

        uint Mesh::get_num_nodes() const
        {
            return mMesh->get_number_of_nodes_on_proc();
        }

//-----------------------------------------------------------------------------

        uint Mesh::get_num_edges() const
        {
            return mMesh->get_number_of_edges();
        }

//-----------------------------------------------------------------------------

        uint Mesh::get_num_faces() const
        {
            return mMesh->get_number_of_facets();
        }

//-----------------------------------------------------------------------------

        uint Mesh::get_num_elems() const
        {
            return mMesh->get_number_of_elements();
        }

//-----------------------------------------------------------------------------

        uint Mesh::get_num_coeffs( const uint aBsplineMeshIndex ) const
        {
            return mMesh->get_number_of_bsplines_on_proc( aBsplineMeshIndex );
        }

//-----------------------------------------------------------------------------

        Matrix< IndexMat > Mesh::get_bspline_inds_of_node_loc_ind( const moris_index      aNodeIndex,
                                                                   const enum EntityRank  aBSplineRank )
        {
            return mMesh->get_node_by_index( aNodeIndex ) ->get_interpolation( 0)->get_indices();
        }

//-----------------------------------------------------------------------------
        Matrix<IndexMat> Mesh::get_entity_connected_to_entity_loc_inds( moris_index     aEntityIndex,
                                                                        enum EntityRank aInputEntityRank,
                                                                        enum EntityRank aOutputEntityRank) const
        {
            switch ( aOutputEntityRank )
            {
                case( EntityRank::NODE ) :
                {
                    switch ( aInputEntityRank )
                    {
                        case( EntityRank::NODE ) :
                        {
                            return this->get_nodes_connected_to_node_loc_inds( aEntityIndex );
                            break;
                        }
                        case( EntityRank::EDGE ) :
                        {
                            Matrix<IndexMat> tNodeToEdge = this->get_nodes_connected_to_edge_loc_inds( aEntityIndex );
                            return tNodeToEdge;

                            break;
                        }
                        case( EntityRank::FACE ) :
                        {
                            Matrix<IndexMat> tNodeToFace = this->get_nodes_connected_to_face_loc_inds( aEntityIndex );
                            return tNodeToFace;
                            break;
                        }
                        case( EntityRank::ELEMENT ) :
                        {
                            Matrix<IndexMat> tNodeToElement = this->get_nodes_connected_to_element_loc_inds( aEntityIndex );
                            return tNodeToElement;
                            break;
                        }
                        default :
                        {
                            MORIS_ERROR( false, "HMR does not provide the requested connectivity" );
                            return Matrix<IndexMat>( 0, 0 );
                            break;
                        }
                    }
                    break;
                } // end output rank node
                case( EntityRank::EDGE ) :
                {
                    switch( aInputEntityRank )
                    {
                        case( EntityRank::NODE ) :
                        {
                            return this->get_edges_connected_to_node_loc_inds( aEntityIndex );
                            break;
                        }
                        case( EntityRank::EDGE ) :
                        {
                            MORIS_ERROR( false, "HMR does not provide edge to edge connectivity" );
                            return Matrix<IndexMat>( 0, 0 );
                            break;
                        }
                        case( EntityRank::FACE ) :
                        {
                            MORIS_ERROR( false, "HMR does not provide edge to face connectivity" );
                            return Matrix<IndexMat>( 0, 0 );
                            break;
                        }
                        case( EntityRank::ELEMENT ) :
                        {
                            if(this->get_spatial_dim() == 3)
                            {
                            return this->get_edges_connected_to_element_loc_inds ( aEntityIndex );
                            }
                            else
                            {
                                return this->get_faces_connected_to_element_loc_inds( aEntityIndex );
                            }
                            break;
                        }
                        default :
                        {
                            MORIS_ERROR( false, "HMR does not provide the requested connectivity" );
                            return Matrix<IndexMat>( 0, 0 );
                            break;
                        }
                    }
                    break;
                } // end output rank edge
                case( EntityRank::FACE ) :
                {
                    switch( aInputEntityRank )
                    {
                        case( EntityRank::NODE ) :
                        {
                            return this->get_faces_connected_to_node_loc_inds( aEntityIndex );
                            break;
                        }
                        case( EntityRank::EDGE ) :
                        {
                            MORIS_ERROR( false, "HMR does not provide face to edge connectivity" );
                            return Matrix<IndexMat>( 0, 0 );
                            break;
                        }
                        case( EntityRank::FACE ) :
                        {
                            MORIS_ERROR( false, "HMR does not provide face to face connectivity" );
                            return Matrix<IndexMat>( 0, 0 );
                            break;
                        }
                        case( EntityRank::ELEMENT ) :
                        {
                            return this->get_faces_connected_to_element_loc_inds( aEntityIndex );
                            break;
                        }
                        default :
                        {
                            MORIS_ERROR( false, "HMR does not provide the requested connectivity" );
                            return Matrix<IndexMat>( 0, 0 );
                            break;
                        }
                    }
                    break;
                } // end output rank face
                case( EntityRank::ELEMENT ) :
                {
                    switch( aInputEntityRank )
                    {
                        case( EntityRank::NODE ) :
                        {
                            return this->get_elements_connected_to_node_loc_inds ( aEntityIndex );
                            break;
                        }
                        case( EntityRank::EDGE ) :
                        {
                            MORIS_ERROR( false, "HMR does not provide element to edge connectivity" );
                            return Matrix<IndexMat>( 0, 0 );
                            break;
                        }
                        case( EntityRank::FACE ) :
                        {
                            return this->get_elements_connected_to_face_loc_inds( aEntityIndex );
                            break;
                        }
                        case( EntityRank::ELEMENT ) :
                        {
                            return this->get_elements_connected_to_element_and_face_ind_loc_inds( aEntityIndex );
                            break;
                        }
                        default :
                        {
                            MORIS_ERROR( false, "HMR does not provide the requested connectivity" );
                            return Matrix<IndexMat>( 0, 0 );
                            break;
                        }
                    }
                    break;
                } // end output rank element
                case( EntityRank::BSPLINE_1 ) :
                {
                    switch( aInputEntityRank )
                    {
                        case( EntityRank::ELEMENT ) :
                        {
                            return this->get_inds_of_active_elements_connected_to_basis( mMesh->get_bspline_mesh( 1 )
                                                                                              ->get_active_basis( aEntityIndex ) );
                            break;
                        }
                        default :
                        {
                            MORIS_ERROR( false, "HMR does not provide the requested connectivity" );
                            return Matrix<IndexMat>( 0, 0 );
                            break;
                        }
                    }
                }  // end output rank linear bspline
                case( EntityRank::BSPLINE_2 ) :
                {
                    switch( aInputEntityRank )
                    {
                        case( EntityRank::ELEMENT ) :
                        {
                            return this->get_inds_of_active_elements_connected_to_basis( mMesh->get_bspline_mesh( 2 )
                                                                                              ->get_active_basis( aEntityIndex ) );
                            break;
                        }
                        default :
                        {
                            MORIS_ERROR( false, "HMR does not provide the requested connectivity" );
                            return Matrix<IndexMat>( 0, 0 );
                            break;
                        }
                    }
                }  // end output rank quadratic bspline
                case( EntityRank::BSPLINE_3 ) :
                {
                    switch( aInputEntityRank )
                    {
                        case( EntityRank::ELEMENT ) :
                        {
                                return this->get_inds_of_active_elements_connected_to_basis( mMesh->get_bspline_mesh( 3 )
                                                                                                  ->get_active_basis( aEntityIndex ) );
                                break;
                        }
                        default :
                        {
                            MORIS_ERROR( false, "HMR does not provide the requested connectivity" );
                            return Matrix<IndexMat>( 0, 0 );
                            break;
                        }
                    }
                }  // end output rank cubic bspline
                default :
                {
                    MORIS_ERROR( false, "HMR does not provide the requested connectivity" );
                    return Matrix<IndexMat>( 0, 0 );
                    break;
                }
            }
        }

//-----------------------------------------------------------------------------
        Matrix< IndexMat > Mesh::get_entity_connected_to_entity_glob_ids( moris_index     aEntityId,
                                                                          enum EntityRank aInputEntityRank,
                                                                          enum EntityRank aOutputEntityRank) const
        {

            moris_index tEntityIndex = this->get_loc_entity_ind_from_entity_glb_id(aEntityId,aInputEntityRank);

            Matrix<IndexMat> tEntityToEntity = this->get_entity_connected_to_entity_loc_inds(tEntityIndex,aInputEntityRank,aOutputEntityRank);

            for(moris::uint i = 0; i <tEntityToEntity.numel(); i++)
            {
                tEntityToEntity(i) = this->get_glb_entity_id_from_entity_loc_index(tEntityToEntity(i),aOutputEntityRank);
            }

            return tEntityToEntity;
        }

//-----------------------------------------------------------------------------

        Matrix< IndexMat > Mesh::get_nodes_connected_to_node_loc_inds( moris_index aNodeIndex ) const
        {
            // get pointer to basis
            const Basis * tBasis = mMesh->get_node_by_index( aNodeIndex );

            // get number of connected elements
            uint tNumberOfElements = tBasis->get_element_counter();

            // get number of nodes connected to element
            uint tCount = 0;
            for( uint e=0; e<tNumberOfElements; ++e )
            {
                tCount += ( tBasis->get_element( e )->get_number_of_vertices() - 1 );
            }

            // allocate temporary Matrix
            Matrix< IndexMat > tNodeIndices( tCount, 1 );

            // reset counter
            tCount = 0;

            // get ID of this basis
            auto tMyID = tBasis->get_hmr_id();

            // loop over all elements
            for( uint e=0; e<tNumberOfElements; ++e )
            {
                // get pointer to element
                const Element * tElement = tBasis->get_element( e );

                // ask element about number of nodes
                uint tNumberOfVertices = tElement->get_number_of_vertices();

                // loop over all connected vertices
                for( uint k=0; k<tNumberOfVertices; ++k )
                {
                    // test if this vertex is not myself
                    if( tElement->get_basis( k )->get_hmr_id() != tMyID )
                    {
                        // add basis index to Indices
                        tNodeIndices( tCount++ ) = tElement->get_basis( k )->get_index();
                    }
                }
            }

            // make result unique
            Matrix< IndexMat > aNodeIndices;
            unique( tNodeIndices, aNodeIndices );
            return aNodeIndices;
        }
//-----------------------------------------------------------------------------

        Matrix< IndexMat > Mesh::get_nodes_connected_to_edge_loc_inds( moris_index aEdgeIndex ) const
        {
           return mMesh->get_edge( aEdgeIndex )->get_vertex_inds();
        }

//-----------------------------------------------------------------------------

        Matrix< IndexMat > Mesh::get_nodes_connected_to_face_loc_inds( moris_index aFaceIndex ) const
        {
            return mMesh->get_facet( aFaceIndex )->get_vertex_inds();
        }

//-----------------------------------------------------------------------------

        Matrix< IndexMat > Mesh::get_nodes_connected_to_element_loc_inds( moris_index aElementIndex ) const
        {
             Element * tElement;

            // get pointer to element
            if( mDatabase->get_parameters()->use_number_aura() )
            {
                tElement = mMesh->get_element_including_aura( aElementIndex );
            }
            else
            {
                tElement = mMesh->get_element( aElementIndex );
            }

            // get number of nodes
            uint tNumberOfNodes = tElement->get_number_of_vertices();

            // allocate output
            Matrix< IndexMat > aIndices( tNumberOfNodes, 1 );

            // populate output
            for( uint k=0; k<tNumberOfNodes; ++k )
            {
                aIndices( k ) = tElement->get_basis( k )->get_index();
            }

            return aIndices;
        }

//-----------------------------------------------------------------------------

        Matrix < IndexMat > Mesh::get_edges_connected_to_node_loc_inds( moris_index aNodeIndex ) const
        {
            // get pointer to basis
            Basis * tBasis = mMesh->get_node_by_index( aNodeIndex );

            uint tNumberOfEdges = tBasis->get_edge_counter();

            Matrix < IndexMat > tEdgeIndex( tNumberOfEdges , 1 );

            for( uint k=0; k<tNumberOfEdges; ++k )
            {
                tEdgeIndex( k ) = tBasis->get_edge( k )->get_index();
            }

            Matrix < IndexMat > aEdgeIndex;
            sort( tEdgeIndex, aEdgeIndex );
            return aEdgeIndex;
        }

//-----------------------------------------------------------------------------

        Matrix< IndexMat > Mesh::get_edges_connected_to_element_loc_inds( moris_index aElementIndex ) const
        {
            // get pointer to element
            Element * tElement;

           // get pointer to element
           if( mDatabase->get_parameters()->use_number_aura() )
           {
               tElement = mMesh->get_element_including_aura( aElementIndex );
           }
           else
           {
               tElement = mMesh->get_element( aElementIndex );
           }

            // will be 0 for 2D, 12 for 3D
            uint tNumberOfEdges = tElement->get_background_element()->get_number_of_edges();

            // allocate output
            Matrix< IndexMat > aIndices( tNumberOfEdges, 1 );

            // populate output
            for( uint e=0; e<tNumberOfEdges; ++e )
            {
                aIndices( e ) = tElement->get_hmr_edge( e )->get_index();
            }

            return aIndices;
        }

//-----------------------------------------------------------------------------

        Matrix < IndexMat > Mesh::get_faces_connected_to_node_loc_inds( moris_index aNodeIndex ) const
        {
            // get pointer to basis
            Basis * tBasis = mMesh->get_node_by_index( aNodeIndex );

            uint tNumberOfFacets = tBasis->get_facet_counter();

            Matrix < IndexMat > tFaceIndex( tNumberOfFacets , 1 );

            for( uint k=0; k<tNumberOfFacets; ++k )
            {
                tFaceIndex( k ) = tBasis->get_facet( k )->get_index();
            }

            Matrix < IndexMat > aFaceIndex;
            sort( tFaceIndex, aFaceIndex );
            return aFaceIndex;
        }

//-----------------------------------------------------------------------------

        Matrix< IndexMat > Mesh::get_faces_connected_to_element_loc_inds( moris_index aElementIndex ) const
        {
            // get pointer to element
            Element * tElement;

           // get pointer to element
           if( mDatabase->get_parameters()->use_number_aura() )
           {
               tElement = mMesh->get_element_including_aura( aElementIndex );
           }
           else
           {
               tElement = mMesh->get_element( aElementIndex );
           }

            uint tNumberOfFaces = tElement->get_background_element()->get_number_of_facets();

            Matrix< IndexMat > aIndices( tNumberOfFaces, 1 );

            for( uint f=0; f<tNumberOfFaces; ++f )
            {
                aIndices( f ) = tElement->get_hmr_facet( f )->get_index();
            }

            return aIndices;
        }

//-----------------------------------------------------------------------------

        Matrix < IndexMat > Mesh::get_elements_connected_to_node_loc_inds( moris_index aNodeIndex ) const
        {
            // collect memory indices of active elements
            Matrix< DDLUMat> tMemoryIndices;
            this->collect_memory_indices_of_active_elements_connected_to_node( aNodeIndex,
                                                                               tMemoryIndices );

            Matrix< IndexMat > aIndices;
            this->get_element_indices_from_memory_indices( tMemoryIndices,
                                                           aIndices );

            return aIndices;
        }

//-----------------------------------------------------------------------------

        Matrix< IndexMat > Mesh::get_elements_connected_to_face_loc_inds( moris_index aFaceIndex ) const
        {
            // get pointer to facet
            Facet * tFacet = mMesh->get_facet( aFaceIndex );

            Matrix< IndexMat > aIndices;

            if( tFacet->get_slave() == NULL )
            {
                if( tFacet->get_hmr_master()->is_active() )
                {
                    aIndices.set_size( 1, 1 );
                    aIndices( 0 ) = tFacet->get_hmr_master()->get_index();
                }
            }
            else
            {
                Element * tMaster = tFacet->get_hmr_master();
                Element * tSlave  = tFacet->get_hmr_slave();

                if(  tMaster->is_active() && tSlave->is_active() )
                {
                    aIndices.set_size( 2, 1 );
                    aIndices( 0 ) = tMaster->get_index();
                    aIndices( 1 ) = tSlave->get_index();
                }
                else if ( tMaster->is_active() )
                {
                    aIndices.set_size( 1, 1 );
                    aIndices( 0 ) = tMaster->get_index();
                }
                else if ( tSlave->is_active() )
                {
                    aIndices.set_size( 1, 1 );
                    aIndices( 0 ) = tSlave->get_index();
                }
            }

            return aIndices;
        }

//-----------------------------------------------------------------------------

        void
        Mesh::get_elements_in_support_of_basis(const uint           aMeshIndex,
                                               const uint           aBasisIndex,
                                               Matrix< IndexMat > & aElementIndices)
        {

            mMesh->get_my_elements_in_basis_support( aMeshIndex, aBasisIndex, aElementIndices );
        }

//-------------------------------------------------------------------------------

        uint
        Mesh::get_num_basis_functions(const uint aMeshIndex)
        {
            return mMesh->get_bspline_mesh(aMeshIndex)->get_number_of_indexed_basis();
        }

//-------------------------------------------------------------------------------

        void Mesh::get_nodes_indices_in_bounding_box( const moris::Matrix< DDRMat >   & aPoint,
                                                      const moris::Matrix< DDRMat >   & aBoundingBoxSize,
                                                            moris::Matrix< IndexMat > & aNodeIndices )
        {
            mMesh->calculate_nodes_indices_in_bounding_box( aPoint, aBoundingBoxSize, aNodeIndices );
        }

//-----------------------------------------------------------------------------

        Matrix< IndexMat > Mesh::get_elements_connected_to_element_and_face_ind_loc_inds( moris_index aElementIndex ) const
        {
            // collect memory indices of active neighbors
            Matrix< DDLUMat> tMemoryIndices;
            Matrix< DDLUMat> tThisCellFacetsOrds;
            luint tNumberOfNeighbors;

            this->collect_memory_indices_of_active_element_neighbors( aElementIndex,
                                                                      tMemoryIndices,
                                                                      tThisCellFacetsOrds,
                                                                      tNumberOfNeighbors );
            // reserve memory for output matrix
            Matrix< IndexMat > tIndices( 2, tNumberOfNeighbors);

            // my cell
            Element * tMyCell = mMesh->get_element( aElementIndex );


            // copy indices from pointers
            for( luint k=0; k<tNumberOfNeighbors; ++k )
            {

                Element * tOtherCell = mMesh->get_element_by_memory_index( tMemoryIndices( k ) );
                tIndices( 0, k ) = tOtherCell->get_index();

                // verify the facet neighborhood makes sense
                Facet * tFacet = tMyCell->get_hmr_facet(tThisCellFacetsOrds(k));


                tIndices( 1, k ) = tFacet->get_index();

            }
            return tIndices;
        }

//-----------------------------------------------------------------------------
// private
//-----------------------------------------------------------------------------

        void Mesh::get_element_indices_from_memory_indices( const Matrix< DDLUMat>   & aMemoryIndices,
                                                                  Matrix< IndexMat > & aIndices ) const
        {
            // get length of vector
            uint tNumberOfElements = aMemoryIndices.length();

            // allocate memory
            aIndices.set_size( tNumberOfElements, 1);

            // copy indices from pointers
            for( uint k=0; k<tNumberOfElements; ++k )
            {
                aIndices( k ) = mMesh->get_element_by_memory_index( aMemoryIndices( k ) )->get_index();
            }
        }

//-----------------------------------------------------------------------------

        void Mesh::collect_memory_indices_of_active_element_neighbors( const moris_index        aElementIndex,
                                                                             Matrix< DDLUMat> & aMemoryIndices,
                                                                             Matrix< DDLUMat> & aThisCellFacetOrds,
                                                                             luint            & aCounter) const
        {
            // get active index of this mesh
            uint tPattern = mMesh->get_activation_pattern();

            // get pointer to element
            Element * tElement = mMesh->get_element( aElementIndex );

            // get pointer to background element
            Background_Element_Base * tBackElement = tElement->get_background_element();

            // count elements that are not padding
            aCounter = 0;

            uint tNumberOfFacets = tBackElement->get_number_of_facets();

            for( uint k=0; k<tNumberOfFacets; ++k )
            {
                // get pointer to neighbor
                Background_Element_Base * tNeighbor = tBackElement->get_neighbor( k );

                if( ! tNeighbor->is_padding() )
                {
                    if( tNeighbor->is_refined( tPattern ) )
                    {
                        tNeighbor->get_number_of_active_descendants( tPattern, aCounter );
                    }
                    else
                    {
                        // increment counter
                        ++aCounter;
                    }
                }
            }

            // allocate matrix with memory indices
            aMemoryIndices.set_size( aCounter, 1 );
            aMemoryIndices.fill(MORIS_INDEX_MAX);

            aThisCellFacetOrds.set_size( aCounter, 1 );
            aThisCellFacetOrds.fill(MORIS_INDEX_MAX);

            // reset counter
            aCounter = 0;

            // number of desecendents
            moris::uint tStart = 0;
            moris::uint tEnd = 0;

            // loop over all neighbors
            for( uint k=0; k<tNumberOfFacets; ++k )
            {
                // get pointer to neighbor
                Background_Element_Base * tNeighbor = tBackElement->get_neighbor( k );

                if( ! tNeighbor->is_padding() )
                {
                    if( tNeighbor->is_refined( tPattern ) )
                    {

                        tStart = aCounter;

                        tNeighbor->collect_active_descendants_by_memory_index( tPattern,
                                                                               aMemoryIndices,
                                                                               aCounter,
                                                                               k );

                        // mark facets that we share with other element
                        tEnd = aCounter;

                        for(moris::uint i = tStart; i < tEnd; i++)
                        {
                            aThisCellFacetOrds(i) = k;
                        }


                    }
                    else
                    {
                        while ( ! tNeighbor->is_active( tPattern ) )
                        {
                            tNeighbor = tNeighbor->get_parent();
                        }

                        aThisCellFacetOrds(aCounter) = k;
                        aMemoryIndices( aCounter++ ) = tNeighbor->get_memory_index();
                    }
                }
            }

            aMemoryIndices.resize(aCounter,1);
            aThisCellFacetOrds.resize(aCounter,1);
        }

//-----------------------------------------------------------------------------

        void Mesh::collect_memory_indices_of_active_elements_connected_to_node( const moris_index        aNodeIndex,
                                                                                      Matrix< DDLUMat> & aMemoryIndices ) const
        {
            // get active index of this mesh
            uint tPattern = mMesh->get_activation_pattern();

            // get pointer to node
            Basis * tNode = mMesh->get_node_by_index( aNodeIndex );

            // get number of elements
            luint tElementCounter = tNode->get_element_counter();

            // element counter with active elements
            luint tCount = 0;

            for( uint k=0; k<tElementCounter; ++k )
            {
                if( tNode->get_element( k )->get_background_element()->is_active( tPattern ) )
                {
                    // increment counter
                    ++tCount;
                }
            }

            // allocate matrix with memory indices
            aMemoryIndices.set_size( tCount, 1 );

            // reset counter
            tCount = 0;

            for( uint k=0; k<tElementCounter; ++k )
            {
                // get pointer to element
                Background_Element_Base * tBackElement = tNode->get_element( k )
                                                              ->get_background_element();

                if( tBackElement->is_active( tPattern ) )
                {
                    // increment counter
                    aMemoryIndices( tCount++ ) = tBackElement->get_memory_index( );
                }
            }
        }

//-----------------------------------------------------------------------------

        Matrix< DDRMat > Mesh::get_node_coordinate( moris_index aNodeIndex ) const
        {
            return mMesh->get_node_by_index( aNodeIndex )->get_coords();
        }

//-----------------------------------------------------------------------------

        moris_id Mesh::get_glb_entity_id_from_entity_loc_index( moris_index     aEntityIndex,
                                                                enum EntityRank aEntityRank) const
        {
            switch ( aEntityRank )
            {
                case( EntityRank::NODE ) :
                {
                    return mMesh->get_node_by_index( aEntityIndex )->get_id();
                    break;
                }
                case( EntityRank::EDGE ) :
                {
                    return mMesh->get_edge( aEntityIndex )->get_id();
                    break;
                }
                case( EntityRank::FACE ) :
                {
                    return mMesh->get_facet( aEntityIndex )->get_id();
                    break;
                }
                case( EntityRank::ELEMENT ) :
                {
                    if( mDatabase->get_parameters()->use_number_aura() )
                    {
                        return mMesh->get_element_including_aura( aEntityIndex )->get_id();
                    }
                    else
                    {
                        return mMesh->get_element( aEntityIndex )->get_id();
                    }

                    break;
                }
                default :
                {
                    MORIS_ERROR( false, "unknown entity rank");
                    return 0;
                    break;
                }
            }
        }

        moris_id Mesh::get_glb_element_id_from_element_loc_index( moris_index aEntityIndex ) const
        {
            return mMesh->get_element_including_aura( aEntityIndex )->get_id();
        }

//-----------------------------------------------------------------------------

        moris_index Mesh::get_loc_entity_ind_from_entity_glb_id( moris_id        aEntityId,
                                                                 enum EntityRank aEntityRank) const
        {
            auto tIter = mEntityGlobaltoLocalMap( ( uint )aEntityRank ).find( aEntityId );

            MORIS_ERROR(tIter!=mEntityGlobaltoLocalMap((uint)aEntityRank).end(),
                        "Provided Entity Id is not in the map, Has the map been initialized?: aEntityId =%u EntityRank = %u on process %u",aEntityId, (uint)aEntityRank, par_rank());

            return tIter->second;
        }

//-----------------------------------------------------------------------------
        moris_id Mesh::get_max_entity_id( enum EntityRank aEntityRank ) const
        {
            switch ( aEntityRank )
            {
                case( EntityRank::NODE ) :
                {
                    return mMesh->get_max_node_id();
                    break;
                }
                case( EntityRank::EDGE ) :
                {
                    return mMesh->get_max_edge_id();
                    break;
                }
                case( EntityRank::FACE ) :
                {
                    return mMesh->get_max_facet_id();
                    break;
                }
                case( EntityRank::ELEMENT ) :
                {
                    return mMesh->get_max_element_id();
                    break;
                }
                default :
                {
                    MORIS_ERROR( false, "unknown entity rank");
                    return 0;
                    break;
                }
            }
        }

//-----------------------------------------------------------------------------

        moris_id Mesh::get_entity_owner( moris_index     aEntityIndex,
                                         enum EntityRank aEntityRank ) const
        {
            switch ( aEntityRank )
            {
                case( EntityRank::NODE ) :
                {
                    return mMesh->get_node_by_index( aEntityIndex )->get_owner();
                    break;
                }
                case( EntityRank::EDGE ) :
                {
                    if(this->get_spatial_dim() == 3)
                    {
                        return mMesh->get_edge( aEntityIndex )->get_owner();
                    }
                    else
                    {
                        return mMesh->get_facet( aEntityIndex )->get_owner();
                    }
                    break;
                }
                case( EntityRank::FACE ) :
                {
                    return mMesh->get_facet( aEntityIndex )->get_owner();
                    break;
                }
                case( EntityRank::ELEMENT ) :
                {
                    if( mDatabase->get_parameters()->use_number_aura() )
                    {
                        return mMesh->get_element_including_aura( aEntityIndex )->get_owner();
                    }
                    else
                    {
                        return mMesh->get_element( aEntityIndex )->get_owner();
                    }
                    break;
                }
                default :
                {
                    MORIS_ERROR( false, "unknown entity rank");
                    return 0;
                    break;
                }
            }
        }

//-----------------------------------------------------------------------------
        void Mesh::get_processors_whom_share_entity( moris_index       aEntityIndex,
                                                     enum EntityRank   aEntityRank,
                                                     Matrix< IdMat > & aProcsWhomShareEntity) const
        {
            MORIS_ASSERT(par_size() == 1,"Not implemented in HMR (pending completion of entity sharing info in HMR");

            aProcsWhomShareEntity.resize(0,0);
        }

        //-----------------------------------------------------------------------------

        enum EntityRank
        Mesh::get_facet_rank() const
        {
            return EntityRank::FACE;
        }

//-----------------------------------------------------------------------------

        moris::Cell<moris::mtk::Vertex const *>
        Mesh::get_all_vertices() const
        {
            uint tNumVertices = this->get_num_entities(EntityRank::NODE);

            moris::Cell<moris::mtk::Vertex const *> tVertices (tNumVertices);

            for(moris::uint  i = 0; i < tNumVertices; i++)
            {
                tVertices(i) = &get_mtk_vertex((moris_index)i);
            }

            return tVertices;
        }

////-----------------------------------------------------------------------------
//
//        moris::Cell<moris::mtk::Vertex const *>
//        Mesh::get_all_vertices_including_aura() const
//        {
//            uint tNumVertices = this->get_num_nodes_including_aura();
//
//            moris::Cell<moris::mtk::Vertex const *> tVertices (tNumVertices);
//
//            for(moris::uint  i = 0; i < tNumVertices; i++)
//            {
//                tVertices(i) = &get_mtk_vertex_including_aura( ( moris_index ) i );
//            }
//
//            return tVertices;
//        }

//-----------------------------------------------------------------------------

        void Mesh::get_adof_map( const uint                           aBSplineIndex,
                                       map< moris_id, moris_index > & aAdofMap ) const
        {
            aAdofMap.clear();

            moris_index tNumberOfBSplines = mMesh->get_number_of_bsplines_on_proc( aBSplineIndex );

            for( moris_index k=0; k<tNumberOfBSplines; ++k )
            {
                Basis * tBasis = mMesh->get_bspline( aBSplineIndex, k );
                aAdofMap[ tBasis->get_id() ] = tBasis->get_index();
            }
        }

//-----------------------------------------------------------------------------

        uint Mesh::get_num_fields( const enum EntityRank aEntityRank ) const
        {
            switch ( aEntityRank )
            {
                case( EntityRank::NODE ) :
                {
                    return mMesh->get_number_of_real_scalar_fields();
                    break;
                }
                case( EntityRank::BSPLINE_1 ) :
                case( EntityRank::BSPLINE_2 ) :
                case( EntityRank::BSPLINE_3 ) :
                {
                    return mMesh->get_number_of_real_scalar_fields();
                    break;
                }
                default :
                {
                    MORIS_ERROR( false, "Entity not supported in hmr::Mesh::get_num_fields()" );
                    return 0;
                }
            }
        }

//-------------------------------------------------------------------------------

        real & Mesh::get_value_of_scalar_field( const      moris_index aFieldIndex,
                                                const enum EntityRank  aEntityRank,
                                                const uint             aEntityIndex )
        {
            switch ( aEntityRank )
            {
                case( EntityRank::NODE ) :
                {
                    return mMesh->get_real_scalar_field_data( aFieldIndex )( aEntityIndex );
                    break;
                }
                case( EntityRank::BSPLINE_1 ) :
                case( EntityRank::BSPLINE_2 ) :
                case( EntityRank::BSPLINE_3 ) :
                {
                    return mMesh->get_real_scalar_field_coeffs( aFieldIndex )( aEntityIndex );
                    break;
                }
                default :
                {
                    MORIS_ERROR( false, "Entity not supported in hmr::Mesh::get_value_of_scalar_field()" );
                    return mDummyReal;
                    break;
                }
            }
        }

//-------------------------------------------------------------------------------

        const real & Mesh::get_value_of_scalar_field( const      moris_index  aFieldIndex,
                                                      const enum EntityRank   aEntityRank,
                                                      const uint              aEntityIndex ) const
        {
            switch ( aEntityRank )
            {
                case( EntityRank::NODE ) :
                {
                    return mMesh->get_real_scalar_field_data( aFieldIndex )( aEntityIndex );
                    break;
                }
                case( EntityRank::BSPLINE_1 ) :
                case( EntityRank::BSPLINE_2 ) :
                case( EntityRank::BSPLINE_3 ) :
                {
                    return mMesh->get_real_scalar_field_coeffs( aFieldIndex )( aEntityIndex );
                    break;
                }
                default :
                {
                    MORIS_ERROR( false, "Entity not supported in hmr::Mesh::get_value_of_scalar_field()" );
                    return mDummyReal;
                }
            }
        }

//-------------------------------------------------------------------------------

        Matrix<DDRMat> & Mesh::get_field( const moris_index     aFieldIndex,
                                          const enum EntityRank aEntityRank )
        {
            switch ( aEntityRank )
            {
                case( EntityRank::NODE ) :
                {
                    return mMesh->get_real_scalar_field_data( aFieldIndex );
                    break;
                }
                case( EntityRank::BSPLINE_1 ) :
                case( EntityRank::BSPLINE_2 ) :
                case( EntityRank::BSPLINE_3 ) :
                {
                    return mMesh->get_real_scalar_field_coeffs( aFieldIndex );
                    break;
                }
                default :
                {
                    MORIS_ERROR( false, "Entity not supported in hmr::Mesh::get_field()" );
                    return mDummyMatrix;
                }
            }
        }

//-------------------------------------------------------------------------------

        moris_index Mesh::get_field_ind( const std::string     & aFieldLabel,
                                         const enum EntityRank   aEntityRank  ) const
        {
            if( aEntityRank == EntityRank::NODE      || aEntityRank == EntityRank::BSPLINE_1 ||
                aEntityRank == EntityRank::BSPLINE_2 || aEntityRank == EntityRank::BSPLINE_3 )
            {
                // fixme: this is not a good method. A map would be better
                moris_index aIndex = gNoIndex;
                moris_index tNumberOfFields = mMesh->get_number_of_real_scalar_fields();
                for( moris_index k=0; k<tNumberOfFields; ++k )
                {
                    if( mMesh->get_real_scalar_field_label( k ) == aFieldLabel )
                    {
                        aIndex = k;
                        break;
                    }
                }
                return aIndex;
            }
            else
            {
                MORIS_ERROR( false, "Entity not supported in hmr::Mesh::get_field_ind()" );
                return gNoIndex;
            }
        }

//-------------------------------------------------------------------------------

        void Mesh::get_sideset_elems_loc_inds_and_ords( const std::string        & aSetName,
                                                              Matrix< IndexMat > & aElemIndices,
                                                              Matrix< IndexMat > & aSideOrdinals ) const
        {
            Matrix< DDUMat > tPatternList = mDatabase->create_output_pattern_list();

            if( mMesh->get_activation_pattern() == tPatternList( 0 ) )                      //FIXME loop for more pattern
            {
                // get ref to set
                const Side_Set & tSet = mDatabase->get_output_side_set( aSetName );

                if ( tSet.mElemIdsAndSideOrds.n_rows() > 0 )
                {
                    // copy indices into output
                    aElemIndices = tSet.mElemIndices;

                    // get side id of this set
                    uint tSide = tSet.mElemIdsAndSideOrds( 0, 1 );

                    // initialize ordinals
                    aSideOrdinals.set_size( aElemIndices.length(), 1, tSide );
                }
                else
                {
                    // sideset does not exist on this proc
                    aElemIndices  = Matrix< IndexMat >( 0, 1 );
                    aSideOrdinals = Matrix< IndexMat >( 0, 1 );
                }
            }
            else
            {
                MORIS_ERROR( false, "HMR only generates sidesets for meshes that are linked to the output pattern" );
            }
        }

//-------------------------------------------------------------------------------

        moris::Cell<std::string> Mesh::get_set_names(enum EntityRank aSetEntityRank ) const
        {
            if ( aSetEntityRank == EntityRank::ELEMENT )
            {
                std::string tDummy = "HMR_dummy";

                moris::Cell<std::string> tSetNames(1, tDummy );

                return tSetNames;
            }
            else if ( aSetEntityRank == EntityRank::FACE )
            {
                Matrix< DDUMat > tPatternList = mDatabase->create_output_pattern_list();

                if( mMesh->get_activation_pattern() == tPatternList( 0 ) )
                {
                    moris::uint tNumSideSets = mDatabase->get_side_sets().size();

                    moris::Cell<std::string> tSetNames( tNumSideSets );

                    for ( uint iEntity = 0; iEntity < tNumSideSets; ++iEntity )
                    {
                        tSetNames( iEntity ) = mDatabase->get_side_sets()( iEntity ).mInfo.mSideSetName;
                    }

                    return tSetNames;
                }
                else
                {
                    return Cell<std::string>(0);
                }
            }
            else if ( aSetEntityRank == EntityRank::NODE )
            {
                return Cell<std::string>(0);
            }
            else
            {
                MORIS_ERROR(false, "Mesh::get_set_names(), only EntityRank::ELEMENT/FACE is implemented for HMR. Rest can be implemented by you.");
            }

            return moris::Cell<std::string>(0);
        }

//-------------------------------------------------------------------------------

        Matrix< IndexMat > Mesh::get_set_entity_loc_inds( enum EntityRank aSetEntityRank,
                                                          std::string     aSetName) const
        {
            if (aSetEntityRank == EntityRank::ELEMENT)
            {
                moris::uint tNumEntities = this->get_num_elems();

                Matrix< IndexMat >  tOutputEntityInds ( tNumEntities, 1 );

                for ( uint iEntity = 0; iEntity < tNumEntities; ++iEntity )
                {
                    tOutputEntityInds( iEntity ) = mMesh->get_element( iEntity )->get_index();
                }

                return tOutputEntityInds;
            }
            if (aSetEntityRank == EntityRank::FACE)
            {
                // todo: fix this
                Matrix< IndexMat > tSideSetElementInd = mDatabase->get_output_side_set( aSetName ).mElemIndices;

                return tSideSetElementInd;
            }
            else
            {
                MORIS_ERROR(false, "Mesh::get_set_entity_loc_inds(), only EntityRank::ELEMENT/FACE is implemented for HMR. Rest can be implemented by you.");
            }

            return Matrix< IndexMat >(0,0);
        }

//-------------------------------------------------------------------------------

        uint Mesh::get_level_of_entity_loc_ind( const enum EntityRank aEntityRank,
                                                const uint            aEntityIndex )
        {
            switch ( aEntityRank )
            {
                case( EntityRank::ELEMENT ) :
                {
                    return mMesh->get_element( aEntityIndex )->get_level();
                    break;
                }
                case( EntityRank::NODE ) :
                {
                    return mMesh->get_node_by_index( aEntityIndex )->get_level();
                    break;
                }
//                case( EntityRank::BSPLINE_1 ) :
//                {
//                    return mMesh->get_bspline( 1, aEntityIndex )->get_level();
//                    break;
//                }
//                case( EntityRank::BSPLINE_2 ) :
//                {
//                    return mMesh->get_bspline( 2, aEntityIndex )->get_level();
//                    break;
//                }
//                case( EntityRank::BSPLINE_3 ) :
//                {
//                    return mMesh->get_bspline( 3, aEntityIndex )->get_level();
//                    break;
//                }
                default :
                {
                    MORIS_ERROR( false, "get_level_of_entity_loc_ind: invalid entity rank" );
                    return 0;
                    break;
                }
            }
        }

//-------------------------------------------------------------------------------

        uint Mesh::get_max_level_of_entity( const enum EntityRank aEntityRank )
        {
            switch ( aEntityRank )
            {
                case( EntityRank::NODE ) :
                {
                    return mMesh->get_max_level();
                    break;
                }
                case( EntityRank::BSPLINE_1 ) :
                {
                    return mMesh->get_bspline_mesh( 1 )->get_max_level();
                    break;
                }
                case( EntityRank::BSPLINE_2 ) :
                {
                    return mMesh->get_bspline_mesh( 2 )->get_max_level();
                    break;
                }
                case( EntityRank::BSPLINE_3 ) :
                {
                    return mMesh->get_bspline_mesh( 3 )->get_max_level();
                    break;
                }
                default :
                {
                    MORIS_ERROR( false, "get_level_of_entity_loc_ind: invalid entity rank" );
                    return 0;
                    break;
                }
            }
        }

//-------------------------------------------------------------------------------

            mtk::Cell & Mesh::get_mtk_cell( moris_index aElementIndex )
            {
                if( mDatabase->get_parameters()->use_number_aura() )
                {
                    return *mMesh->get_element_including_aura( aElementIndex );
                }
                else
                {
                    return *mMesh->get_element( aElementIndex );
                }
            }

//-------------------------------------------------------------------------------

            mtk::Cell const & Mesh::get_mtk_cell( moris_index aElementIndex ) const
            {
                if( mDatabase->get_parameters()->use_number_aura() )
                {
                    return *mMesh->get_element_including_aura( aElementIndex );
                }
                else
                {
                    return *mMesh->get_element( aElementIndex );
                }
            }

//-------------------------------------------------------------------------------

        Matrix< IndexMat > Mesh::get_inds_of_active_elements_connected_to_basis( const Basis * aBasis ) const
        {
            // ask basis for number of elements
            luint tNumberOfElements = aBasis->get_element_counter();

            // get activation pattern from this mesh
            uint tPattern = mMesh->get_activation_pattern();

            // counter for active elements
            luint tCount = 0;

            // count active elements
            for( uint e=0; e<tNumberOfElements; ++e )
            {
                aBasis->get_element( e )->get_background_element()
                                        ->get_number_of_active_descendants( tPattern, tCount );
            }

            // allocate cell with connected elements
            Cell< const Background_Element_Base * > tBackElements( tCount, nullptr );

            // reset counter
            tCount = 0;

            // collect background elements
            for( luint e=0; e<tNumberOfElements; ++e )
            {
                aBasis->get_element( e )->get_background_element() ->collect_active_descendants( tPattern,
                                                                                                 tBackElements,
                                                                                                 tCount );
            }

            // allocate output matrix
            Matrix< IndexMat > aElementIndices( tCount, 1 );

            // loop over all background elements
            for( luint e=0; e<tCount; ++e )
            {
                // grab element by memory index and copy moris index into matrix
                aElementIndices( e ) = mMesh->get_element_by_memory_index( tBackElements( e )->get_memory_index() )->get_index();
            }

            return aElementIndices;
        }

        void Mesh::setup_glb_to_local_maps()
        {
            // Initialize global to local map
            mEntityGlobaltoLocalMap = moris::Cell<std::unordered_map<moris_id,moris_index>>(4);

            setup_entity_global_to_local_map(EntityRank::NODE);
            setup_entity_global_to_local_map(EntityRank::EDGE);
            setup_entity_global_to_local_map(EntityRank::FACE);
            setup_entity_global_to_local_map(EntityRank::ELEMENT);
//            setup_element_global_to_local_map();
        }

//-------------------------------------------------------------------------------

        void Mesh::setup_entity_global_to_local_map(enum EntityRank aEntityRank)
        {
//            this->get_lagrange_mesh()->select_activation_pattern(  );
//            MORIS_ERROR( aEntityRank != EntityRank::ELEMENT," function does not work for element use setup_element_global_to_local_map instead()");

            uint tNumEntities = this->get_num_entities(aEntityRank);
            moris_id tCount = 0;
            for( uint i = 0; i < tNumEntities; i++ )
            {
                moris_id tEntityId = this->get_glb_entity_id_from_entity_loc_index( i, aEntityRank );
//                MORIS_ASSERT(mEntityGlobaltoLocalMap((uint)aEntityRank).find(tEntityId) == mEntityGlobaltoLocalMap((uint)aEntityRank).end(),"Id already in the map.");   FIXME KEENAN
                mEntityGlobaltoLocalMap((uint)aEntityRank)[tEntityId] = tCount;
                tCount++;
            }
        }

//-------------------------------------------------------------------------------

        void Mesh::setup_element_global_to_local_map()
        {
////            this->get_lagrange_mesh()->select_activation_pattern(  );
//
//            uint tNumEntities = this->get_num_entities(aEntityRank);
//
//            moris_id tCount = 0;
//
//            for( uint i = 0; i < tNumElements; i++ )
//            {
//                moris_id tEntityId = this->get_glb_element_id_from_element_loc_index( i );
////                MORIS_ASSERT(mEntityGlobaltoLocalMap((uint)aEntityRank).find(tEntityId) == mEntityGlobaltoLocalMap((uint)aEntityRank).end(),"Id already in the map.");   FIXME KEENAN
//                mEntityGlobaltoLocalMap((uint)EntityRank::ELEMENT)[ tEntityId ] = tCount;
//                tCount++;
//            }

//    moris_id tEntityId = this->get_glb_entity_id_from_entity_loc_index(i,aEntityRank);

//    mEntityGlobaltoLocalMap((uint)aEntityRank)[tEntityId] = tCount;

        }

    } /* namespace hmr */
} /* namespace moris */
