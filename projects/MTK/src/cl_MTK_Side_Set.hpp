/*
 * cl_MTK_Side_Set.hpp
 *
 *  Created on: Jul 24, 2018
 *      Author: messe
 */

#ifndef SRC_MESH_CL_MTK_SIDE_SET_HPP_
#define SRC_MESH_CL_MTK_SIDE_SET_HPP_

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
        class Side_Set : public Set
        {
        private :
            uint                              mNumVerticesOnSet;
            moris::Matrix< DDSMat >           mVerticesOnSet;

//------------------------------------------------------------------------------

            void calculate_vertices_on_set()
            {
                uint tMaxNumVert = 0;

                for( uint Ik = 0; Ik < mSetClusters.size(); Ik++)
                {
                    Matrix< IndexMat > tSideOrdinal= mSetClusters( Ik )
                                                              ->get_cell_side_ordinals();

                    for( uint Ij = 0; Ij < mSetClusters( Ik )->get_primary_cells_in_cluster().size(); Ij++)
                    {
                        tMaxNumVert = tMaxNumVert + mSetClusters( Ik )->get_primary_cells_in_cluster()( Ij )
                                                                          ->get_vertices_ind_on_side_ordinal( tSideOrdinal(Ij) ).numel();
                    }
                }

                moris::Matrix< DDSMat > tVerticesOnSet(1, tMaxNumVert, -1 );

                uint tCounter = 0;

                for( uint Ik = 0; Ik < mSetClusters.size(); Ik++)
                {
                    Matrix< IndexMat > tSideOrdinal= mSetClusters( Ik )
                                                              ->get_cell_side_ordinals();

                    for( uint Ij = 0; Ij < mSetClusters( Ik )->get_primary_cells_in_cluster().size(); Ij++)
                    {
                        //FIXME rewrite for more readability
                        tVerticesOnSet( { 0, 0 },{ tCounter, tCounter + mSetClusters( Ik )->get_primary_cells_in_cluster()( Ij )
                                                          ->get_vertices_ind_on_side_ordinal(tSideOrdinal(Ij)).numel() - 1 }) =
                                                                  mSetClusters( Ik )->get_primary_cells_in_cluster()( Ij )
                                                   ->get_vertices_ind_on_side_ordinal(tSideOrdinal(Ij)).matrix_data();

                        tCounter =tCounter + mSetClusters( Ik )->get_primary_cells_in_cluster()( Ij )
                                          ->get_vertices_ind_on_side_ordinal(tSideOrdinal(Ij)).numel();
                    }
                }

//                MORIS_ASSERT( tVerticesOnSet.min() != -1, "calculate_vertices_on_blocks(): negative vertex index");

                unique( tVerticesOnSet, mVerticesOnSet);

//                print(mVerticesOnSet,"mVerticesOnSet");

                mNumVerticesOnSet = mVerticesOnSet.numel();
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

                mIGGeometryType = get_auto_side_geometry_type( mIGGeometryType );

//                MORIS_ASSERT( mIGGeometryType != mtk::Geometry_Type::UNDEFINED, " communicate_type(); undefined geometry type on all processors");
            };

//------------------------------------------------------------------------------
        public:
//------------------------------------------------------------------------------

            /**
             * trivial constructor
             */
            Side_Set( moris::Cell<Cluster const *>  aSideSetClusters ) : Set( aSideSetClusters )
            {
                 this->calculate_vertices_on_set();

                 this->communicate_ig_geometry_type();
            };

//------------------------------------------------------------------------------

            /**
             * virtual destructor
             */
            ~Side_Set(){};

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
              get_clusters_by_index( moris_index aClusterIndex ) const
              {
                  return mSetClusters( aClusterIndex );
              }

//------------------------------------------------------------------------------

              uint
              get_num_vertieces_on_set() const
              {
                  return mNumVerticesOnSet;
              }

//------------------------------------------------------------------------------

              moris::Matrix< DDSMat >
              get_vertieces_inds_on_block() const
              {
                  return mVerticesOnSet;
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
#endif /* SRC_MESH_CL_MTK_SIDE_SET_HPP_ */