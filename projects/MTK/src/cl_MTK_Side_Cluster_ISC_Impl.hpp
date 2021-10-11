/*
 * cl_MTK_Side_Cluster_ISC_Impl.hpp
 *
 *  Created on: Jun 22, 2021
 *      Author: momo
 */

#ifndef PROJECTS_MTK_SRC_CL_MTK_SIDE_CLUSTER_ISC_IMPL_HPP_
#define PROJECTS_MTK_SRC_CL_MTK_SIDE_CLUSTER_ISC_IMPL_HPP_


#include <unordered_map>

#include "cl_MTK_Side_Cluster.hpp"

namespace moris
{
    namespace mtk
    {

        class Side_Cluster_ISC: public mtk::Side_Cluster
        {
            private:

                bool                                    mTrivial;
                moris::mtk::Cell const *                mInterpolationCell;
                moris::Cell<moris::mtk::Cell const *>   mIntegrationCells;
                moris::Matrix<moris::IndexMat>          mIntegrationCellSideOrdinals;
                moris::Cell<moris::mtk::Vertex const *> mVerticesInCluster;
                moris::Matrix<moris::DDRMat>            mVertexParamCoords;

                // map from vertex id to local index
                std::unordered_map<moris_index,moris_index> mVertexIdToLocalIndex;


            public:
                //----------------------------------------------------------------
                /*
                 * Default constructor
                 */
                Side_Cluster_ISC();

                //----------------------------------------------------------------
                /**
                 * Trivial constructor
                 * When Integration cell and interpolation cell are the same
                 */
                Side_Cluster_ISC( moris::mtk::Cell const * aInterpCell,
                        moris::mtk::Cell const * aIntegrationCell,
                        moris::Cell<moris::mtk::Vertex const *> const & aVerticesInCluster,
                        moris_index aSideOrdinal);

                //----------------------------------------------------------------
                /**
                 * Trivial constructor
                 * When Integration cell and interpolation cell are the same
                 */
                Side_Cluster_ISC(bool aTrivial,
                        moris::mtk::Cell const *                        aInterpolationCell,
                        moris::Cell<moris::mtk::Cell const *>   const & aIntegrationCells,
                        moris::Matrix<moris::IndexMat>          const & aIntegrationCellSideOrdinals,
                        moris::Cell<moris::mtk::Vertex const *> const & aVerticesInCluster,
                        moris::Matrix<moris::DDRMat> const & aVertexParamCoords);

                //----------------------------------------------------------------
                /**
                 * Determines if a side cluster is trivial
                 * @param[ in ] aIsMaster If the cluster is master or slave
                 */
                bool
                is_trivial( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;

                //----------------------------------------------------------------
                /**
                 * Returns Interpolation Cell
                 * @param[ in ] aIsMaster If the cluster is master or slave
                 */
                moris::mtk::Cell const &
                get_interpolation_cell( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER) const;

                //----------------------------------------------------------------
                /**
                 * Returns Integration cells in the side cluster
                 */
                moris::Cell<moris::mtk::Cell const *> const &
                get_cells_in_side_cluster() const;

                //----------------------------------------------------------------
                /**
                 * Returns side ordinals of the integration cells
                 * @param[ in ] aIsMaster If the cluster is master or slave
                 */
                moris::Matrix<moris::IndexMat>
                get_cell_side_ordinals( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;

                //----------------------------------------------------------------
                /**
                 * Returns side ordinal of a specific integration cell within cluster
                 * @param[ in ] aIsMaster If the cluster is master or slave
                 * @param[ in ] aCellIndexInCluster Local index of the integration cell in the cluster
                 */
                moris_index
                get_cell_side_ordinal(moris::moris_index aCellIndexInCluster,
                        const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;

                //----------------------------------------------------------------
                /**
                 * Returns cell of vertices in the clsuter
                 * @param[ in ] aIsMaster If the cluster is master or slave
                 */
                moris::Cell<moris::mtk::Vertex const *>
                get_vertices_in_cluster( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;

                //----------------------------------------------------------------
                /**
                 * Returns vertices local coordinates wrt to the interpolation cell
                 * @param[ in ] aIsMaster If the cluster is master or slave
                 */
                moris::Matrix<moris::DDRMat>
                get_vertices_local_coordinates_wrt_interp_cell(const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER) const;

                //----------------------------------------------------------------
                /**
                 * Returns local index of the vertex within cluster
                 * @param[ in ] aVertex an mtk vertex
                 * @param[ in ] aIsMaster If the cluster is master or slave
                 */
                moris_index
                get_vertex_cluster_index( moris::mtk::Vertex const * aVertex,
                        const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER  ) const;

                //----------------------------------------------------------------
                /**
                 * Returns ordinal of a vertex within a integration cell
                 * @param[ in ] aCellIndexInCluster Local index of the integration cell in the cluster
                 * @param[ in ] aVertex an mtk vertex
                 */
                moris_index
                get_vertex_ordinal_on_facet( moris_index aCellIndexInCluster, moris::mtk::Vertex const * aVertex ) const;

                //----------------------------------------------------------------
                /**
                 * Returns local coordinates of a vertex
                 * @param[ in ] aVertex an mtk vertex
                 * @param[ in ] aIsMaster If the cluster is master or slave
                 */
                moris::Matrix<moris::DDRMat>
                get_vertex_local_coordinate_wrt_interp_cell( moris::mtk::Vertex const * aVertex,
                        const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER) const;

                //----------------------------------------------------------------
                /**
                 * Returns dimension of the parametric coordinates
                 * @param[ in ] aVertex an mtk vertex
                 */
                moris_index
                get_dim_of_param_coord( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;

                //----------------------------------------------------------------
                /**
                 * Returns the local index of the vertex based on the global id
                 * @param[ in ] aVertexId Id of the vertex
                 */
                moris_index
                get_vertex_cluster_local_index(moris_id aVertexId) const;

                //----------------------------------------------------------------
                /**
                 * Add vertex to the map of local index to global id
                 * @param[ in ] aVertexId Id of the vertex
                 * @param[ in ] aVertexLocalIndex Local index of the vertex
                 */
                void
                add_vertex_to_map(moris_id aVertexId,
                        moris_index aVertexLocalIndex);

                friend class Intersection_Detect;
                friend class Intersection_Detect_2D;

        };
    }
}




#endif /* PROJECTS_MTK_SRC_CL_MTK_SIDE_CLUSTER_ISC_IMPL_HPP_ */