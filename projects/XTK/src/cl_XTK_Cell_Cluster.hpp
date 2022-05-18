/*
 * Copyright (c) 2022 University of Colorado 
 * Licensed under the MIT license. See LICENSE.txt file in the MORIS root for details. 
 * 
 * ------------------------------------------------------------------------------------ 
 * 
 * cl_XTK_Cell_Cluster.hpp  
 * 
 */
#ifndef PROJECTS_XTK_SRC_XTK_CL_XTK_CELL_CLUSTER_HPP_
#define PROJECTS_XTK_SRC_XTK_CL_XTK_CELL_CLUSTER_HPP_

#include "cl_MTK_Cell_Cluster.hpp"
#include "cl_MTK_Cluster_Group.hpp"
#include "cl_XTK_Enriched_Integration_Mesh.hpp"

using namespace moris;

namespace xtk
{
    class Interpolation_Cell_Unzipped;
    class Child_Mesh;
    class IG_Vertex_Group;
    class IG_Cell_Group;

    class Cell_Cluster : public mtk::Cell_Cluster
    {
        friend class Enriched_Integration_Mesh;
        friend class Side_Cluster;

        //------------------------------------------------------------------------------

      protected:

        bool                                            mTrivial;
        bool                                            mVoid = false;
        bool                                            mInvalid;
        Interpolation_Cell_Unzipped const*              mInterpolationCell;
        Child_Mesh const*                               mChildMesh;  // FIXME: this doesn't seem to be used, should be removed
        moris::Cell< moris::mtk::Cell const* >          mPrimaryIntegrationCells;
        moris::Cell< moris::mtk::Cell const* >          mVoidIntegrationCells;
        moris::Cell< moris::mtk::Vertex const* >        mVerticesInCluster;
        Matrix< DDRMat >                                mLocalCoords;
        std::shared_ptr< IG_Vertex_Group >              mVertexGroup;
        moris::Cell< std::shared_ptr< IG_Cell_Group > > mPrimaryIgCellGroup;
        moris::Cell< std::shared_ptr< IG_Cell_Group > > mVoidIgCellGroup;
        std::shared_ptr< mtk::Cluster_Group >           mClusterGroup;

        //------------------------------------------------------------------------------

      public:
      
        Cell_Cluster();
        ~Cell_Cluster();
        bool                                          is_trivial( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;
        bool                                          is_full() const;
        bool                                          is_void() const;
        bool                                          is_invalid() const;
        moris::Cell< moris::mtk::Cell const* > const& get_primary_cells_in_cluster( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;
        moris::Cell< moris::mtk::Cell const* > const& get_void_cells_in_cluster() const;
        moris::mtk::Cell const&                       get_interpolation_cell( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;
        moris::Cell< moris::mtk::Vertex const* >      get_vertices_in_cluster( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;
        moris::Matrix< moris::DDRMat >                get_vertices_local_coordinates_wrt_interp_cell( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;
        moris::Matrix< moris::DDRMat >                get_vertex_local_coordinate_wrt_interp_cell( moris::mtk::Vertex const *aVertex, const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;
        moris_index                                   get_dim_of_param_coord( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;
        moris::Matrix< moris::DDRMat >                get_primary_cell_local_coords_on_side_wrt_interp_cell( moris::moris_index aPrimaryCellClusterIndex ) const;

        //------------------------------------------------------------------------------

        // functions for internal XTK use
        Interpolation_Cell_Unzipped const* 
        get_xtk_interpolation_cell() const;

        //------------------------------------------------------------------------------

        Matrix< IndexMat > 
        get_hanging_nodes() const;

        //------------------------------------------------------------------------------

        // memory
        size_t
        capacity();

        //------------------------------------------------------------------------------

        void
        set_primary_integration_cell_group( std::shared_ptr< IG_Cell_Group > aPrimaryIgCells );

        //------------------------------------------------------------------------------

        void
        set_primary_integration_cell_groups( moris::Cell< std::shared_ptr< IG_Cell_Group > > aPrimaryIgCells );

        //------------------------------------------------------------------------------

        void
        set_void_integration_cell_groups( moris::Cell< std::shared_ptr< IG_Cell_Group > > &aVoidIgCells );

        //------------------------------------------------------------------------------

        void
        set_ig_vertex_group( std::shared_ptr< IG_Vertex_Group > aVertexGroup );

        //------------------------------------------------------------------------------

        std::shared_ptr< IG_Vertex_Group >
        get_ig_vertex_group();

        //------------------------------------------------------------------------------

        moris::real
        compute_cluster_group_cell_measure(
                const mtk::Primary_Void aPrimaryOrVoid = mtk::Primary_Void::PRIMARY,
                const mtk::Master_Slave aIsMaster      = mtk::Master_Slave::MASTER) const;

        //------------------------------------------------------------------------------

        moris::real
        compute_cluster_group_cell_measure_derivative(
                const Matrix< DDRMat > & aPerturbedVertexCoords,
                uint aDirection,
                const mtk::Primary_Void aPrimaryOrVoid = mtk::Primary_Void::PRIMARY,
                const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;

        //------------------------------------------------------------------------------

    };  // class Cell_Cluster 
}    // namespace xtk

#endif /* PROJECTS_XTK_SRC_XTK_CL_XTK_CELL_CLUSTER_HPP_ */
