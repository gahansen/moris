#include <string>
#include <iomanip>
#include "cl_MTK_Integration_Mesh.hpp"
#include "cl_MTK_Mesh_Core.hpp"
#include "cl_MTK_Cell_Cluster.hpp"
#include "cl_MTK_Side_Cluster.hpp"
#include "cl_MTK_Double_Side_Cluster.hpp"
#include "assert.hpp"
#include "cl_Matrix.hpp"
#include "cl_MTK_Block.hpp"
#include "cl_MTK_Space_Interpolator.hpp"
#include "cl_MTK_Integration_Rule.hpp"
#include "cl_MTK_Cell_Info.cpp"
#include "fn_norm.hpp"

#include "fn_stringify_matrix.hpp"
#include "fn_join_horiz.hpp"

#include "HDF5_Tools.hpp"

namespace moris
{
    namespace mtk
    {
        // ----------------------------------------------------------------------------

        void
        Integration_Mesh::save_IG_node_TMatrices_to_file()
        {
            // get total number of integration vertices on IG mesh
            uint tNumVertices = this->get_num_nodes();
            MORIS_LOG_SPEC( "Num of IG vertices to save T-matrices for", tNumVertices );

            // get Number of Block Sets
            uint tNumSets = this->get_num_blocks();

            // go through all bulk sets
            for( uint iSet = 0; iSet < tNumSets; iSet++ )
            {
                // -------------------------------------
                // get T-Matrices 

                // initialize cells containing info for T-matrices mapping (Background-BSp)-(Background-Lag) for each IP vertex
                moris::Cell< Matrix< IdMat > >  tIPtoBSIds;
                moris::Cell< Matrix< DDRMat > > tIPtoBSWeights;

                // get T-matrices mapping from IP nodes to B-splines
                this->get_IP_to_BS_nodal_T_matrices( tIPtoBSIds, tIPtoBSWeights, iSet );

                // initialize cells containing info for T-matrices mapping (Background-Lag)-(IG-Vertices) for each IG vertex
                moris::Cell< Matrix< IdMat > >  tIGtoIPIds;
                moris::Cell< Matrix< DDRMat > > tIGtoIPWeights;
            
                // get T-matrices mapping from IG nodes to IP nodes
                this->get_IG_to_IP_nodal_T_matrices( tIGtoIPIds, tIGtoIPWeights, iSet );

                // initialize cells containing info for T-matrices mapping (Background-BSp)-(IG-Vertices) for each IG vertex
                moris::Cell< Matrix< IdMat > >  tIGtoBSIds;
                moris::Cell< Matrix< DDRMat > > tIGtoBSWeights;

                // combine T-Matrices to get 
                this->get_IG_to_BS_nodal_T_matrices( tIGtoBSIds, tIGtoBSWeights, tIPtoBSIds, tIPtoBSWeights, tIGtoIPIds, tIGtoIPWeights );

                // -------------------------------------
                // combine everything into one matrix

                // initialize matrices for sparse mat
                Matrix< DDUMat > tSparseIndices;
                Matrix< DDRMat > tWeights;

                // combine everything
                this->build_sparse_extraction_operator( tIGtoBSIds, tIGtoBSWeights, tSparseIndices, tWeights );

                // -------------------------------------
                // write to file

                // construct string from output file name 
                std::string tStrOutputFile = "Extraction_Operator." + ios::stringify( iSet ) + ".hdf5";

                // log/print that the extraction operator is output to
                MORIS_LOG_INFO( "Saving Extraction Operator for Set-# %i to file: %s", iSet, tStrOutputFile.c_str() );

                // initialize hdf5 file
                hid_t tFileID = create_hdf5_file( tStrOutputFile );
                herr_t tStatus = 0;

                // write to file
                save_matrix_to_hdf5_file( tFileID, "IDs",  tSparseIndices,  tStatus );
                save_matrix_to_hdf5_file( tFileID, "Weights",  tWeights,  tStatus );

                // close file
                close_hdf5_file( tFileID );

            } // end: loop over all sets
        }

        // ----------------------------------------------------------------------------

        void
        Integration_Mesh::get_IG_to_IP_nodal_T_matrices( 
                moris::Cell< Matrix< IdMat > >   & aIGtoIPIds,
                moris::Cell< Matrix< DDRMat > >  & aIGtoIPWeights,
                uint                             aSetIndex )
        {
            // get number of IG vertices on mesh
            uint tNumVertices = this->get_num_nodes();

            // initialize cells containing info for T-matrices mapping (Background-Lag)-(IG-Vertices) for each IG vertex
            aIGtoIPIds.resize( tNumVertices );
            aIGtoIPWeights.resize( tNumVertices );

            // get number of clusters on current set
            uint tNumClustersOnSet = this->get_set_by_index( aSetIndex )->get_num_clusters_on_set();

            // proceed with saving, if set is non-empty
            if( tNumClustersOnSet > 0 )
            {
                // go through clusters in current set
                for( uint iCluster = 0; iCluster < tNumClustersOnSet; iCluster++ )
                {
                    // get current cluster
                    const Cluster * tCluster = this->get_set_by_index( aSetIndex )->get_clusters_by_index( iCluster );

                    // get IP cell current cluster is on
                    const moris::mtk::Cell & tInterpolationCell = tCluster->get_interpolation_cell();

                    // get list of all vertices on IP cell associated with current cluster
                    moris::Cell< Vertex *> tIPVertices = tInterpolationCell.get_vertex_pointers();

                    // get info for IP cell associated with cluster currently handled
                    Cell_Info const * tCellInfo = tCluster->get_interpolation_cell().get_cell_info();

                    // creating interpolation rule
                    Interpolation_Rule tInterpolationRule(
                            tCellInfo->get_cell_geometry(),             // basic geometry of IP element (i.e. QUAD or HEX)
                            Interpolation_Type::LAGRANGE,               // space IP type
                            tCellInfo->get_cell_interpolation_order(),  // space IP order
                            Interpolation_Type::LAGRANGE,               // time IP type
                            Interpolation_Order::LINEAR);               // time IP order

                    // create a space interpolator
                    Space_Interpolator tSpaceInterpolator(tInterpolationRule);

                    // get list of list of coordinate of vertices on current cluster
                    moris::Matrix< moris::DDRMat > tLocalCoords = tCluster->get_vertices_local_coordinates_wrt_interp_cell();

                    // get list of (pointers to) vertices on current cluster
                    moris::Cell< moris::mtk::Vertex const * > tIGVertices = tCluster->get_vertices_in_cluster();

                    // get number of vertices on the treated mesh cluster
                    uint tNumVerticesOnCluster = tLocalCoords.n_rows();

                    // loop over the vertices on the treated mesh cluster
                    for( uint iIgVert = 0; iIgVert < tNumVerticesOnCluster; iIgVert++ )
                    {
                        // set interpolation point in space to current vertex
                        tSpaceInterpolator.set_space_time( trans( tLocalCoords.get_row( iIgVert ) ) );

                        // evaluate vector of shape functions at current vertex and retrieve it
                        const Matrix< DDRMat > & tN = tSpaceInterpolator.NXi();

                        // get current vertex ID and index
                        moris_id tIGVertexId = tIGVertices( iIgVert )->get_id();

                        // get number of shape functions interpolating into current vertex
                        uint tNumSFs = tN.n_cols();

                        // initialize size of T-Matrix for current vertex
                        aIGtoIPIds( tIGVertexId - 1 ).set_size( 1, tNumSFs, gNoID );
                        aIGtoIPWeights( tIGVertexId - 1 ).set_size( 1, tNumSFs, -1.0 );

                        // initialize counter
                        uint tCount = 0;

                        // loop over all T-Matrix entries
                        for( uint iSF = 0; iSF < tNumSFs; iSF++ )
                        {
                            // ignore T-matrix entries which are zero close to machine precision
                            if ( std::abs( tN( iSF ) ) > 10.0 * MORIS_REAL_EPS )
                            {
                                // copy pointer of dof and convert to mtk::Vertex
                                aIGtoIPIds( tIGVertexId - 1 )( tCount ) = tIPVertices( iSF )->get_id();

                                // copy entry of T-Matrix
                                aIGtoIPWeights( tIGVertexId - 1 )( tCount ) = tN( iSF );

                                // increment counter
                                tCount++;
                            }
                        }
                    } // end: loop over vertices on cluster
                } // end: loop over clusters
            } // end: if cluster is empty
        }

        // ----------------------------------------------------------------------------

        void
        Integration_Mesh::get_IP_to_BS_nodal_T_matrices( 
                moris::Cell< Matrix< IdMat > >   & aIPtoBSIds,
                moris::Cell< Matrix< DDRMat > >  & aIPtoBSWeights,
                uint                             aSetIndex )
        {
            // get number of IP nodes on mesh
            uint tNumIpNodes = this->get_max_IP_ID_on_set( aSetIndex );

            // initialize map size
            aIPtoBSIds.resize( tNumIpNodes );
            aIPtoBSWeights.resize( tNumIpNodes );

            // matrices that mark which ID pairs have been found
            Matrix< DDSMat > tIdentifierMatIP( tNumIpNodes, 1, 0 );

            // get number of clusters on current set
            uint tNumClustersOnSet = this->get_set_by_index( aSetIndex )->get_num_clusters_on_set();

            // check if cluster is empty, if so skip procedure
            if( tNumClustersOnSet > 0 )
            {
                // loop over all clusters in current bulk set
                for( uint iCluster = 0; iCluster < tNumClustersOnSet; iCluster++ )
                {
                    // get current cluster
                    const Cluster * tCluster = this->get_set_by_index( aSetIndex )->get_clusters_by_index( iCluster );

                    // get IP cell current cluster is on
                    const moris::mtk::Cell & tInterpolationCell = tCluster->get_interpolation_cell();

                    // get list of all vertices on IP cell associated with current cluster
                    moris::Cell< Vertex *> tIPVertices = tInterpolationCell.get_vertex_pointers();

                    // go through all IP vertices, build BSp - Lag map
                    for( uint iIpVert = 0; iIpVert < tIPVertices.size(); iIpVert++)
                    {
                        // check if current IP vertex is empty
                        MORIS_ASSERT( tIPVertices( iIpVert )->has_interpolation( 0 ), "IP Vertex does not have a B-spline interpolation 0.");

                        // get IP vertex ID
                        uint tIP_ID = tIPVertices( iIpVert )->get_id();

                        MORIS_ERROR( tIP_ID > 0, "Integration_Mesh::get_IP_to_BS_nodal_T_matrices() - ID expected to be greater equal 1." );

                        // check if IP vertex has already been treated
                        if( tIdentifierMatIP( tIP_ID - 1 ) == 0 )
                        {
                            // get list of B-spline IDs associated with current IP vertex
                            Matrix< IdMat > tBSpIDs = tIPVertices( iIpVert )->get_interpolation( 0 )->get_ids();
                            Matrix< DDRMat > tBSWeights = *tIPVertices( iIpVert )->get_interpolation( 0 )->get_weights();

                            // get number of B-splines assiciated with current IP vertex
                            uint tNumBspOnIpNode = tBSpIDs.numel();

                            // resize nodal T-matrix to accommodate all B-spline IDs and weights 
                            aIPtoBSIds( tIP_ID - 1 ).set_size( 1, tNumBspOnIpNode, gNoID );
                            aIPtoBSWeights( tIP_ID - 1 ).set_size( 1, tNumBspOnIpNode, -1 );

                            // create T-matrices - copy list of associated B-spline IDs and their weights
                            for ( uint iBsp = 0; iBsp < tNumBspOnIpNode; iBsp++ )
                            {
                                aIPtoBSIds( tIP_ID - 1 )( iBsp ) = tBSpIDs( iBsp );
                                aIPtoBSWeights( tIP_ID - 1 )( iBsp ) = tBSWeights( iBsp );
                            }

                            // tick off IP vertex as treated
                            tIdentifierMatIP( tIP_ID - 1 ) = 1;
                        }
                    } // end: loop over IP vertices
                } // end: loop over clusters
            } // skip: check if cluster is empty
        }

        // ----------------------------------------------------------------------------

        void 
        Integration_Mesh::get_IG_to_BS_nodal_T_matrices( 
                        moris::Cell< Matrix< IdMat  > >  & aIGtoBSIds,
                        moris::Cell< Matrix< DDRMat > >  & aIGtoBSWeights,
                        moris::Cell< Matrix< IdMat  > >  & aIPtoBSIds,
                        moris::Cell< Matrix< DDRMat > >  & aIPtoBSWeights,
                        moris::Cell< Matrix< IdMat  > >  & aIGtoIPIds,
                        moris::Cell< Matrix< DDRMat > >  & aIGtoIPWeights )
        {
            // get number of IG vertices
            uint tNumIgNodes = aIGtoIPIds.size();
            MORIS_ERROR( tNumIgNodes == aIGtoIPWeights.size(), 
                    "Integration_Mesh::get_IG_to_BS_nodal_T_matrices() - Size of ID/weight maps for IG-IP T-Matrices don't match." );

            // initialize size of T-Matrix cells
            aIGtoBSIds.resize( tNumIgNodes );
            aIGtoBSWeights.resize( tNumIgNodes );

            // loop over all IG vertices
            for( uint iIgNode = 0; iIgNode < tNumIgNodes; iIgNode++ )
            {
                // initialize temporary vectors containing all
                Matrix< IdMat > tNodalIGtoBSIds( 0, 0 );
                Matrix< DDRMat > tNodalIGtoBSWeights( 0, 0 ); 

                // number of IP nodes associated with current IG node
                uint tNumIpBfs = aIGtoIPIds( iIgNode ).numel();

                // loop over all IP nodes current IG node is related to
                for( uint jIpNode = 0; jIpNode < tNumIpBfs; jIpNode++ )
                {
                    // get current IP ID
                    moris_id tIpId = aIGtoIPIds( iIgNode )( jIpNode );

                    // skip if IP-ID doesn't exist 
                    if( tIpId > gNoID )
                    {
                        // get what B-spline IDs and Weights are associated with current Node
                        Matrix< IdMat > tAddIdList = aIPtoBSIds( tIpId - 1 );
                        Matrix< DDRMat > tAddWeightList = aIGtoIPWeights( iIgNode )( jIpNode ) * aIPtoBSWeights( tIpId - 1 );

                        // append vectors of IDs and weights
                        tNodalIGtoBSIds = join_horiz( tNodalIGtoBSIds, tAddIdList );
                        tNodalIGtoBSWeights = join_horiz( tNodalIGtoBSWeights, tAddWeightList );
                    }
                } // end: loop over all IP Nodes

                // fixme: just copy onto lists for now, works only for linear everything
                aIGtoBSIds( iIgNode ) = tNodalIGtoBSIds;
                aIGtoBSWeights( iIgNode ) = tNodalIGtoBSWeights;

                // todo: make list unique for the case of higher order....
                 
            } // end: loop over all IG Nodes
        }

        // ----------------------------------------------------------------------------

        uint 
        Integration_Mesh::get_max_IP_ID_on_set( uint aSetIndex )
        {
            // initialize counter
            uint tMaxID = 0;

            // get number of clusters on current set
            uint tNumClustersOnSet = this->get_set_by_index( aSetIndex )->get_num_clusters_on_set();

            // check if cluster is empty, if so skip procedure
            if( tNumClustersOnSet > 0 )
            {
                // loop over all clusters in current bulk set
                for( uint iCluster = 0; iCluster < tNumClustersOnSet; iCluster++ )
                {
                    // get current cluster
                    const Cluster * tCluster = this->get_set_by_index( aSetIndex )->get_clusters_by_index( iCluster );

                    // get IP cell current cluster is on
                    const moris::mtk::Cell & tInterpolationCell = tCluster->get_interpolation_cell();

                    // get list of all vertices on IP cell associated with current cluster
                    moris::Cell< Vertex *> tIPVertices = tInterpolationCell.get_vertex_pointers();

                    // go through all IP vertices, build BSp - Lag map
                    for( uint iIpVert = 0; iIpVert < tIPVertices.size(); iIpVert++)
                    {
                        // get IP vertex ID
                        uint tIP_ID = tIPVertices( iIpVert )->get_id();

                        tMaxID = std::max( tMaxID, tIP_ID );
                    }
                }
            }

            // return max ID
            return tMaxID;
        }

        // ----------------------------------------------------------------------------

        void 
        Integration_Mesh::build_sparse_extraction_operator( 
                moris::Cell< Matrix< IdMat > > & aIGtoBSIds,
                moris::Cell< Matrix< DDRMat > > & aIGtoBSWeights,
                Matrix< DDUMat > & aSparseIndices,
                Matrix< DDRMat > & aWeights )
        {
            // initialize sparse matrix
            aSparseIndices.set_size( 0, 0 );
            aWeights.set_size( 0, 0 );

            // get number of IG nodes
            uint tNumIgNodes = aIGtoBSIds.size();

            // loop over all IG Nodes
            for ( uint iG = 0; iG < tNumIgNodes; iG++ )
            {
                // check if IG node has interpolation
                if( aIGtoBSIds( iG ).numel() > 0 )
                {
                    // loop over B-splines interpolating into current IG node
                    for ( uint iBsp = 0; iBsp < aIGtoBSIds( iG ).numel(); iBsp++ ) 
                    {
                        // get 
                        uint tBspId = aIGtoBSIds( iG )( iBsp );

                        // append indices and weights to list
                        aSparseIndices = join_horiz( aSparseIndices, { { iG + 1 }, { tBspId } } );
                        aWeights = join_horiz( aWeights, { { aIGtoBSWeights( iG )( iBsp ) } } );
                    }
                }
            } // end: loop over all IG nodes
            
            // flip orientation
            aSparseIndices = trans( aSparseIndices );
            aWeights = trans( aWeights );
        }

        // ----------------------------------------------------------------------------
    }
}