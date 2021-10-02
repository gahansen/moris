/*
 * cl_XTK_Cell_Cluster.hpp
 *
 *  Created on: Jul 22, 2019
 *      Author: doble
 */

#ifndef PROJECTS_XTK_SRC_XTK_CL_XTK_CELL_CLUSTER_HPP_
#define PROJECTS_XTK_SRC_XTK_CL_XTK_CELL_CLUSTER_HPP_


#include "cl_MTK_Cell_Cluster.hpp"
#include "cl_XTK_Enriched_Integration_Mesh.hpp"

using namespace moris;

namespace xtk
{
class Interpolation_Cell_Unzipped;
class Child_Mesh;
class IG_Vertex_Group;
class IG_Cell_Group;
class Side_Cluster;

class Cell_Cluster : public mtk::Cell_Cluster
{
public:
    Cell_Cluster();
    ~Cell_Cluster();
    bool                                          is_trivial( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;
    moris::Cell<moris::mtk::Cell const *> const & get_primary_cells_in_cluster( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;
    moris::Cell<moris::mtk::Cell const *> const & get_void_cells_in_cluster() const;
    moris::mtk::Cell const &                      get_interpolation_cell( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;
    moris::Cell<moris::mtk::Vertex const *>       get_vertices_in_cluster( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER) const;
    moris::Matrix<moris::DDRMat>                  get_vertices_local_coordinates_wrt_interp_cell( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const;
    moris::Matrix<moris::DDRMat>                  get_vertex_local_coordinate_wrt_interp_cell( moris::mtk::Vertex const * aVertex, const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER) const ;
    moris_index                                   get_dim_of_param_coord( const mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER ) const ;
    moris::Matrix<moris::DDRMat>                  get_primary_cell_local_coords_on_side_wrt_interp_cell(moris::moris_index aPrimaryCellClusterIndex) const;

    friend class Enriched_Integration_Mesh;
    friend class Side_Cluster;

    // functions for internal XTK use
    Interpolation_Cell_Unzipped const * get_xtk_interpolation_cell() const;

    Matrix< IndexMat > get_hanging_nodes(  ) const;

    // memory
    size_t
    capacity();

    void
    set_primary_integration_cell_group(std::shared_ptr<IG_Cell_Group> aPrimaryIgCells);

    void
    set_void_integration_cell_groups(moris::Cell<std::shared_ptr<IG_Cell_Group>> & aVoidIgCells);

    void
    set_ig_vertex_group(std::shared_ptr<IG_Vertex_Group> aVertexGroup);
    
    std::shared_ptr<IG_Vertex_Group>
    get_ig_vertex_group();

protected:
    bool                                        mTrivial;
    Interpolation_Cell_Unzipped const *         mInterpolationCell;
    Child_Mesh const *                          mChildMesh;
    moris::Cell<moris::mtk::Cell const *>       mPrimaryIntegrationCells;
    moris::Cell<moris::mtk::Cell const *>       mVoidIntegrationCells;
    moris::Cell<moris::mtk::Vertex const *>     mVerticesInCluster;
    Matrix<DDRMat>                              mLocalCoords;
    std::shared_ptr<IG_Vertex_Group>            mVertexGroup;
    std::shared_ptr<IG_Cell_Group>              mPrimaryIgCellGroup;
    moris::Cell<std::shared_ptr<IG_Cell_Group>> mVoidIgCellGroup;
};
}


#endif /* PROJECTS_XTK_SRC_XTK_CL_XTK_CELL_CLUSTER_HPP_ */
