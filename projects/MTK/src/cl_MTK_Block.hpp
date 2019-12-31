/*
 * cl_MTK_Element_Block.hpp
 *
 *  Created on: Jul 24, 2019
 *      Author: Schmidt
 */

#ifndef SRC_MESH_CL_MTK_BLOCK_HPP_
#define SRC_MESH_CL_MTK_BLOCK_HPP_

#include <string>

#include "typedefs.hpp" //MRS/COR/src
#include "fn_unique.hpp" //MRS/COR/src
#include "cl_Map.hpp"
#include "cl_MTK_Vertex.hpp" //MTK/src
#include "cl_MTK_Cell.hpp" //MTK/src

#include "cl_MTK_Cell_Cluster.hpp" //MTK/src
#include "cl_MTK_Set.hpp" //MTK/src


namespace moris
{
    namespace mtk
    {

//------------------------------------------------------------------------------
        class Block : public Set
        {
        private :
            uint                              mNumVerticesOnBlock;
            moris::Matrix< DDSMat >           mVerticesOnBlock;

            uint                              mNumCellsOnBlock;
            moris::Matrix< DDSMat >           mCellsOnBlock;

            bool mOnlyPrimaryVertCheck = false;
            bool mOnlyPrimaryCellCheck = false;

//------------------------------------------------------------------------------

            void calculate_vertices_on_blocks( const bool aOnlyPrimary )
            {
                uint tMaxNumVert = 0;

                for( uint Ik = 0; Ik < mSetClusters.size(); Ik++)
                {
                    for( uint Ij = 0; Ij < mSetClusters( Ik )->get_primary_cells_in_cluster().size(); Ij++)
                    {
                        tMaxNumVert +=  mSetClusters( Ik )->get_primary_cells_in_cluster()( Ij )
                                                          ->get_vertex_inds().numel();
                    }

                    if( !aOnlyPrimary )
                    {
                        for( uint Ij = 0; Ij < mSetClusters( Ik )->get_void_cells_in_cluster().size(); Ij++)
                        {
                            tMaxNumVert +=  mSetClusters( Ik )->get_void_cells_in_cluster()( Ij )
                                                              ->get_vertex_inds().numel();
                        }
                    }
                }

                moris::Matrix< DDSMat > tVerticesOnBlock(1, tMaxNumVert, -1 );

                uint tCounter = 0;

                for( uint Ik = 0; Ik < mSetClusters.size(); Ik++)
                {
                    for( uint Ij = 0; Ij < mSetClusters( Ik )->get_primary_cells_in_cluster().size(); Ij++)
                    {
                        //FIXME rewrite for more readability
                        tVerticesOnBlock( { 0, 0 },{ tCounter, tCounter + mSetClusters( Ik )->get_primary_cells_in_cluster()( Ij )
                                                           ->get_vertex_inds().numel() - 1 }) =
                                                             mSetClusters( Ik )->get_primary_cells_in_cluster()( Ij )
                                                                               ->get_vertex_inds().matrix_data();

                        tCounter += mSetClusters( Ik )->get_primary_cells_in_cluster()( Ij )
                                                      ->get_vertex_inds().numel();
                    }

                    if( !aOnlyPrimary )
                    {
                        for( uint Ij = 0; Ij < mSetClusters( Ik )->get_void_cells_in_cluster().size(); Ij++)
                        {
                            //FIXME rewrite for more readability
                            tVerticesOnBlock( { 0, 0 },{ tCounter, tCounter + mSetClusters( Ik )->get_void_cells_in_cluster()( Ij )
                                                               ->get_vertex_inds().numel() - 1 }) =
                                                                 mSetClusters( Ik )->get_void_cells_in_cluster()( Ij )
                                                                                   ->get_vertex_inds().matrix_data();

                            tCounter += mSetClusters( Ik )->get_void_cells_in_cluster()( Ij )
                                                          ->get_vertex_inds().numel();
                        }
                    }
                }

                //FIXME: Maybe add this to linalg. Armadillo throws if min is called on an empty matrix
#ifdef DEBUG
                if(tVerticesOnBlock.numel()!=0)
                {
                    MORIS_ASSERT( tVerticesOnBlock.min() != -1, "calculate_vertices_on_blocks(): negative vertex index");
                }
#endif

                unique( tVerticesOnBlock, mVerticesOnBlock);

                //FIXME delete this if statement the unique bud in aramdillo is fixed.
                if ( tVerticesOnBlock.n_rows() != mVerticesOnBlock.n_rows() )
                {
                    tVerticesOnBlock = mVerticesOnBlock;
                    mVerticesOnBlock.set_size( 1, mVerticesOnBlock.numel() );

                    for( uint Ik = 0; Ik < tVerticesOnBlock.numel(); Ik++ )
                    {
                        mVerticesOnBlock( Ik ) = tVerticesOnBlock( Ik );
                    }
                }

                mNumVerticesOnBlock = mVerticesOnBlock.numel();
            };

//------------------------------------------------------------------------------

            void calculate_cells_on_blocks( const bool aOnlyPrimary )
            {
                uint tMaxNumCells = 0;

                for( uint Ik = 0; Ik < mSetClusters.size(); Ik++)
                {
                    tMaxNumCells += mSetClusters( Ik )->get_primary_cells_in_cluster().size();
                    if( !aOnlyPrimary )
                    {
                        tMaxNumCells += mSetClusters( Ik )->get_void_cells_in_cluster().size();
                    }
                }

                moris::Matrix< DDSMat > tCellsOnBlock( tMaxNumCells, 1, -1 );

                uint tCounter = 0;

                for( uint Ik = 0; Ik < mSetClusters.size(); Ik++)
                {
                    for( uint Ij = 0; Ij < mSetClusters( Ik )->get_primary_cells_in_cluster().size(); Ij++ )
                    {
                        tCellsOnBlock( tCounter++ ) = mSetClusters( Ik )->get_primary_cells_in_cluster()( Ij )->get_index();
                    }

                    if( !aOnlyPrimary )
                    {
                        for( uint Ij = 0; Ij < mSetClusters( Ik )->get_void_cells_in_cluster().size(); Ij++ )
                        {
                            tCellsOnBlock( tCounter++ ) = mSetClusters( Ik )->get_void_cells_in_cluster()( Ij )->get_index();
                        }
                    }
                }

                //FIXME: Maybe add this to linalg. Armadillo throws if min is called on an empty matrix
#ifdef DEBUG
                if(tCellsOnBlock.numel()!=0)
                {
                    MORIS_ASSERT( tCellsOnBlock.min() != -1, "calculate_cells_on_blocks(): negative Cell index");
                }
#endif

                unique( tCellsOnBlock, mCellsOnBlock);

//                print(mVerticesOnBlock,"mNumVerticesOnBlock");

                mNumCellsOnBlock = mCellsOnBlock.numel();
            };

//------------------------------------------------------------------------------

            void communicate_ig_geometry_type()
            {
                mtk::Geometry_Type tIGGeometryType = mtk::Geometry_Type::UNDEFINED;

                if( mSetClusters.size() > 0 )
                {
                    // set the integration geometry type
                    tIGGeometryType = mSetClusters( 0 )->get_primary_cells_in_cluster( )( 0 )->get_geometry_type();
                }

                uint tRecIGGeometryType = (uint) mtk::Geometry_Type::UNDEFINED;

                min_all( (uint)tIGGeometryType, tRecIGGeometryType );

                mIGGeometryType = static_cast<enum mtk::Geometry_Type> (tRecIGGeometryType);

//                MORIS_ASSERT( mIGGeometryType != mtk::Geometry_Type::UNDEFINED, " communicate_type(); undefined geometry type on all processors");
            };

//------------------------------------------------------------------------------
        public:
//------------------------------------------------------------------------------

            /**
             * trivial constructor
             */
            Block( std::string                   aName,
                   moris::Cell<Cluster const *>  aBlockSetClusters,
                   const uint                    aSpatialDim ) : Set( aName, aBlockSetClusters, aSpatialDim )
            {
                this->calculate_vertices_on_blocks( mOnlyPrimaryVertCheck );

                this->calculate_cells_on_blocks( false );

                this->communicate_ig_geometry_type();
            };

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

            /**
             * trivial constructor
             */
            Block(){};

//------------------------------------------------------------------------------

            /**
             * virtual destructor
             */
            ~Block(){};

//------------------------------------------------------------------------------

            /**
             * return a label that describes the block
             */
//              const moris::Matrix< DDUMat > &
//              get_list_of_block_cell_clusters() const
//              {
//                  return mMyBlockSetClusterInds;
//              }


//------------------------------------------------------------------------------

              const Cluster  *
              get_clusters_by_index( moris_index aCellClusterIndex ) const
              {
                  return mSetClusters( aCellClusterIndex );
              }

//------------------------------------------------------------------------------

              uint get_num_vertieces_on_set( const bool aOnlyPrimary )
              {
                  if ( mOnlyPrimaryVertCheck != aOnlyPrimary )
                  {
                      this->calculate_vertices_on_blocks( aOnlyPrimary );
                  }

                  return mNumVerticesOnBlock;
              }

//------------------------------------------------------------------------------

              moris::Matrix< DDSMat > get_vertieces_inds_on_block( const bool aOnlyPrimary )
              {
                  if ( mOnlyPrimaryVertCheck != aOnlyPrimary )
                  {
                      this->calculate_vertices_on_blocks( aOnlyPrimary );
                  }

                  return mVerticesOnBlock;
              }

//------------------------------------------------------------------------------

              uint get_num_cells_on_set( const bool aOnlyPrimary )
              {
                  if ( mOnlyPrimaryCellCheck != aOnlyPrimary )
                  {
                      this->calculate_cells_on_blocks( aOnlyPrimary );
                  }
                  return mNumCellsOnBlock;
              }

//------------------------------------------------------------------------------

              moris::Matrix< DDSMat > get_cell_inds_on_block( const bool aOnlyPrimary )
              {
                  if ( mOnlyPrimaryCellCheck != aOnlyPrimary )
                  {
                      this->calculate_cells_on_blocks( aOnlyPrimary );
                  }
                  return mCellsOnBlock;
              }

//------------------------------------------------------------------------------

              moris::uint
              get_num_clusters_on_set() const
              {
                  return mSetClusters.size();
              }

//------------------------------------------------------------------------------

              moris::Cell<Cluster const *>
              get_clusters_on_set() const
              {
                  return mSetClusters;
              }

//------------------------------------------------------------------------------
            /**
             * return a label that describes the block
             */
//            virtual std::string
//            get_label() const;

//------------------------------------------------------------------------------

//            /**
//             * sets the name of a block
//             */
//            virtual void
//            set_label( const std::string & aLabel );
//
////------------------------------------------------------------------------------
//
//            /**
//             * returns the Id of this block
//             */
//            virtual moris_id
//            get_id() const;
//
////------------------------------------------------------------------------------
//
//            /**
//             * returns the number of vertices owned and shared on this proc
//             */
//            virtual uint
//            get_number_of_vertices() const;
//
////------------------------------------------------------------------------------
//
//            /**
//             * returns the number of element owned by this proc
//             */
//            virtual uint
//            get_number_of_cells() const;
//
////------------------------------------------------------------------------------
//
//            /**
//             * returns a pointer to a vertex
//             */
//            virtual Vertex *
//            get_vertex_by_index( const moris_index & aIndex );
//
////------------------------------------------------------------------------------
//
//            /**
//             * returns a pointer to a vertex ( const version )
//             */
//            virtual const Vertex *
//            get_vertex_by_index( const moris_index & aIndex ) const;
//
////------------------------------------------------------------------------------
//
//            /**
//             * returns a pointer to a cell
//             */
//            virtual Cell *
//            get_cell_by_index( const moris_index & aIndex );
//
////------------------------------------------------------------------------------
//
//            /**
//             * returns a pointer to a cell ( const version )
//             */
//            virtual const Cell *
//            get_cell_by_index( const moris_index & aIndex ) const;
//
////------------------------------------------------------------------------------
//
//            virtual sint
//            get_number_of_adofs_used_by_proc() const;
//
////------------------------------------------------------------------------------
//
//            virtual void
//            get_adof_map( const uint aOrder, map< moris_id, moris_index > & aAdofMap  ) const;
//
////------------------------------------------------------------------------------
//
//            /**
//             * return the interpolation order of the cells on the block
//             */
//            virtual uint
//            get_interpolation_order() const;

//------------------------------------------------------------------------------
    };

//------------------------------------------------------------------------------
    } /* namespace mtk */
} /* namespace moris */
//------------------------------------------------------------------------------
#endif /* SRC_MESH_CL_MTK_BLOCK_HPP_ */
