/*
 * cl_GEN_Geometry_Engine.cpp
 *
 *  Created on: Dec 11, 2019
 *      Author: sonne
 */

#include "cl_GEN_Geometry_Engine.hpp"

// HMR
#include "cl_HMR_Mesh.hpp"
#include "cl_HMR.hpp"

namespace moris
{
namespace ge
{
//------------------------------------------------------------------------------
GEN_Geometry_Engine::GEN_Geometry_Engine
( moris::ge::GEN_Geometry          & aGeometry,
  moris::ge::GEN_Phase_Table const & aPhaseTable,
  moris::uint                        aSpatialDim )
: mThresholdValue( 0 ),
  mComputeDxDp( false ),
  mSpatialDim( aSpatialDim ),
  mActiveGeometryIndex( 0 ),
  mGeometryObjectManager(),
  mPhaseTable( aPhaseTable )
{
    mPerturbationValue = 0.0000005;
    mGeometry.push_back( &aGeometry );
}

//------------------------------------------------------------------------------
GEN_Geometry_Engine::GEN_Geometry_Engine( Cell< GEN_Geometry* >      const & aGeometry,
                                          moris::ge::GEN_Phase_Table const & aPhaseTable,
                                          moris::uint                        aSpatialDim )
: mThresholdValue( 0 ),
  mComputeDxDp( false ),
  mSpatialDim( aSpatialDim ),
  mActiveGeometryIndex( 0 ),
  mGeometry( aGeometry ),
  mPhaseTable( aPhaseTable )
{
    mPerturbationValue = 0.0000005;
}

// TODO: create the destructor to delete the analytic geometry pointer created via "new" in the initialization function

//------------------------------------------------------------------------------
void GEN_Geometry_Engine::initialize_geometry_objects_for_background_mesh_nodes(moris::size_t const & aNumNodes)
{
    // Allocate space
    mNodePhaseVals = moris::Matrix< moris::DDRMat >(aNumNodes,mGeometry.size(),0);

    // Allocate geometry object
    Cell< GEN_Geometry_Object > tGeometryObjects( aNumNodes );

    // Associate each geometry object with a row in phase val matrix (note phase val computed later)
    moris::Matrix< moris::IndexMat > tNodeIndex( 1, aNumNodes );
    for(moris::size_t i = 0; i<aNumNodes; i++)
    {
        tGeometryObjects(i).set_phase_val_row(i);
        tNodeIndex(0,i) = i;
    }

    // Place these in the geometry object manager
    mGeometryObjectManager.store_geometry_objects(tNodeIndex,tGeometryObjects);
}

//------------------------------------------------------------------------------
void GEN_Geometry_Engine::initialize( std::shared_ptr< Library_IO > aLibrary )
{
	mLibrary = aLibrary;

	this->initialize_geometries_and_phase_table();
}

void GEN_Geometry_Engine::initialize()
{
	this->initialize_geometries_and_phase_table();
}

void GEN_Geometry_Engine::initialize_geometries_and_phase_table()
{
    // initialize threshold for level sets
    mThresholdValue = 0.0;

    // flag to compute DxDp ( TODO: needs to be updated/adjusted )
    mComputeDxDp = false;

    // initialize for XTK's decomposition
    mActiveGeometryIndex = 0;

    // create geometry vector
    moris::Cell< std::string > tGeomFuncNames;
    string_to_cell( mParameterList.get< std::string >( "geometries" ), tGeomFuncNames );

    // get number of geometry function names
    uint tNumGeometry = tGeomFuncNames.size();

    // set size for the list of geometry pointers
    mGeometry.resize( tNumGeometry, nullptr );

    // loop over the geometry function names
    for( uint iFunc = 0; iFunc < tNumGeometry; iFunc++ )
    {
    	MORIS_ERROR( mLibrary != nullptr, "GEN_Geometry_Engine::initialize_geometries_and_phase_table(), mLibrary not set");

        // read a geometry function from input
        MORIS_GEN_FUNCTION tGeometry = mLibrary->load_gen_free_functions( tGeomFuncNames( iFunc ) );

        // create a geometry pointer
        mGeometry( iFunc ) = new Analytic_Geometry( tGeometry );
    }

    // create phase table for geometry engine
    mPhaseTable =  moris::ge::GEN_Phase_Table( tNumGeometry, Phase_Table_Structure::EXP_BASE_2);
}
//------------------------------------------------------------------------------

void GEN_Geometry_Engine::initialize_geometry_object_phase_values( moris::Matrix< moris::DDRMat > const & aNodeCoords )
{
    // Allocate space
    moris::size_t tNumNodes = aNodeCoords.n_rows();

    // Loop through each geometry and then each node and compute the level set field value
    // add value to phase value matrix

    for(moris::size_t j = 0; j<get_num_geometries(); j++)
    {
        bool tAnalyticFlag = mGeometry(j)->is_analytic();

        // Analytic
        if(tAnalyticFlag)
        {
        	bool tAnalyticFuncPointer = mGeometry(j)->is_func_pointer();

        	if(tAnalyticFuncPointer)
        	{
        		for(moris::size_t i = 0; i<tNumNodes; i++ )
        		{
        			Cell< real > tDummy(0);	// TODO: need to get these constants from the input file?
        			real tTempLSVal;
        			mGeometry(j)->eval( tTempLSVal, aNodeCoords.get_row( i ), tDummy );
        			mNodePhaseVals(i,j) = tTempLSVal;
        		}
        	}
        	else
        	{
        		for(moris::size_t i = 0; i<tNumNodes; i++ )
        		{
        			mNodePhaseVals(i,j) = mGeometry(j)->evaluate_field_value_with_coordinate(i,aNodeCoords);
        		}
        	}
        }

        // Discrete
        else
        {
            for(moris::size_t i = 0; i<tNumNodes; i++ )
            {
                mNodePhaseVals(i,j) = mGeometry(j)->access_field_value_with_entity_index(i, moris::EntityRank::NODE);
            }
        }
    }
}

//------------------------------------------------------------------------------

void GEN_Geometry_Engine::associate_new_nodes_with_geometry_object( Cell<Pending_Node> & aNewNodes,
                                                                    bool                 aInterfaceNodes )
{
    // Allocate space
    moris::size_t tNumNewNodes = aNewNodes.size();
    moris::size_t tNumCurrNodes = mNodePhaseVals.n_rows();

    // add space to the node phase value table
    mNodePhaseVals.resize(tNumNewNodes+tNumCurrNodes,mGeometry.size());

    Cell<GEN_Geometry_Object> tGeometryObjects(tNumNewNodes);

    moris::Matrix< moris::IndexMat > tNodeIndex(1,tNumNewNodes);
    for(moris::size_t i = 0; i<tNumNewNodes; i++)
    {
        tGeometryObjects(i).set_phase_val_row(i+tNumCurrNodes);
        tNodeIndex(0,i) = aNewNodes(i).get_node_index();
        if(aInterfaceNodes)
        {
            tGeometryObjects(i).set_parent_entity_topology(aNewNodes(i).get_parent_topology_ptr());
        }
    }

    if(tNumNewNodes !=0)
    {
        mGeometryObjectManager.store_geometry_objects(tNodeIndex,tGeometryObjects);
    }

    // Compute and store level set value of this node for each new node
    for(moris::size_t j = 0; j<get_num_geometries(); j++)
    {

        for(moris::size_t i = 0; i<tNumNewNodes; i++ )
        {
            // Ask the pending node about its parent
            // This information is needed to know what to interpolate based on
            moris::Matrix< moris::DDRMat > const & tLocalCoordinate = aNewNodes(i).get_local_coordinate_relative_to_parent();
            moris::Matrix< moris::DDRMat >  tLevelSetValues(1,1);
            xtk::Topology const & tParentTopology = aNewNodes(i).get_parent_topology();

            // Interpolate all level set values to node
            this->interpolate_level_set_value_to_child_node_location(tParentTopology, j,tLocalCoordinate,tLevelSetValues);
            mNodePhaseVals(i+tNumCurrNodes,j) = tLevelSetValues(0,0);
        }

    }
}
//------------------------------------------------------------------------------

void GEN_Geometry_Engine::create_new_node_geometry_objects( Cell< moris_index >  const & aNewNodeIndices,
                                                            bool                         aStoreParentTopo,
                                                            Cell<xtk::Topology*> const & aParentTopo,
                                                            Cell<Matrix<DDRMat>> const & aParamCoordRelativeToParent,
                                                            Cell<Matrix<DDRMat>> const & aGlobalNodeCoord )
{
    // Allocate space
    moris::size_t tNumNewNodes = aNewNodeIndices.size();
    moris::size_t tNumCurrNodes = mNodePhaseVals.n_rows();

    // add space to the node phase value table
    mNodePhaseVals.resize(tNumNewNodes+tNumCurrNodes,mGeometry.size());

    Cell<GEN_Geometry_Object> tGeometryObjects(tNumNewNodes);

    moris::Matrix< moris::IndexMat > tNodeIndex(1,tNumNewNodes);
    for(moris::size_t i = 0; i<tNumNewNodes; i++)
    {
        tGeometryObjects(i).set_phase_val_row(i+tNumCurrNodes);
        tNodeIndex(0,i) = aNewNodeIndices(i);
        if(aStoreParentTopo)
        {
            tGeometryObjects(i).set_parent_entity_topology(aParentTopo(i)->copy());
            mIntegNodeIndices.push_back( aNewNodeIndices(i) );
        }
    }

    if(tNumNewNodes !=0)
    {
        mGeometryObjectManager.store_geometry_objects(tNodeIndex,tGeometryObjects);
    }

    for(moris::size_t j = 0; j<get_num_geometries(); j++)
    {

        for(moris::size_t i = 0; i<tNumNewNodes; i++ )
        {
            // Ask the pending node about its parent
            // This information is needed to know what to interpolate based on
            moris::Matrix< moris::DDRMat >  tLevelSetValues(1,1);
            this->interpolate_level_set_value_to_child_node_location(*aParentTopo(i), j, aParamCoordRelativeToParent(i),tLevelSetValues);

            mNodePhaseVals(i+tNumCurrNodes,j) = tLevelSetValues(0,0);
        }

    }
}

//------------------------------------------------------------------------------

void GEN_Geometry_Engine::link_new_nodes_to_existing_geometry_objects( Matrix< IndexMat > const & aNodesIndicesWithGeomObj,
                                                                       Matrix< IndexMat > const & aNodesIndicesToLink )
{
    // Assert lengths match
    MORIS_ASSERT(aNodesIndicesWithGeomObj.numel() == aNodesIndicesToLink.numel(),
    "Length of nodes with geometry objects does not match length of list with node indices to link  ");

    // Number of nodes to link
    uint tNumNodes = aNodesIndicesWithGeomObj.numel();

    // Iterate through nodes and create the link
    for(uint i = 0; i <tNumNodes; i++)
    {
        mGeometryObjectManager.link_to_node_to_another_nodes_geometry_object(aNodesIndicesWithGeomObj(i),aNodesIndicesToLink(i));
    }

}
//------------------------------------------------------------------------------

void GEN_Geometry_Engine::is_intersected( moris::Matrix< moris::DDRMat > const &   aNodeCoords,
                                          moris::Matrix< moris::IndexMat > const & aNodetoEntityConn,
                                          moris::size_t                            aCheckType,
                                          Cell< GEN_Geometry_Object > &            aGeometryObjects )
{
    //Get information for loops
    moris::size_t tNumEntities = aNodetoEntityConn.n_rows(); // Number of entities provided to the geometry engine

    //Initialize
    moris::size_t tIntersectedCount = 0;    // Intersected element counter
    aGeometryObjects.clear();
    aGeometryObjects.resize(tNumEntities,GEN_Geometry_Object());

    //Loop over elements and determine if the element has an intersection
    for(moris::moris_index i = 0; i < (moris::moris_index)tNumEntities; i++)
    {

        //Populate the intersection flag of this element with a bool
        moris::Matrix< moris::IndexMat > tRow = aNodetoEntityConn.get_row(i);
        moris::Matrix< moris::IndexMat > tNodeADVIndices;
        bool tIsIntersected = compute_intersection_info( i,tRow, aNodeCoords, aCheckType, tNodeADVIndices, aGeometryObjects(tIntersectedCount) );

        if(tIsIntersected)
        {
            tIntersectedCount++;
        }
    }

    // resize
    aGeometryObjects.resize( tIntersectedCount, GEN_Geometry_Object() );
}

//------------------------------------------------------------------------------

void GEN_Geometry_Engine::compute_interface_sensitivity( Matrix< IndexMat > const & aInterfaceNodeIndices,
                                                         Matrix< DDRMat >   const & aNodeCoords,
                                                         moris_index                aGeomIndex,
                                                         bool               const   aGlbCoord )
{
    // Figure out how many entities to compute sensitivity for
    uint tNumEntities = aInterfaceNodeIndices.numel();

    // iterate through node indices and compute sensitivity for each
    for( uint iEnt = 0; iEnt<tNumEntities; iEnt++ )
    {
        // get the node index
        moris::moris_index tNodeIndex = aInterfaceNodeIndices( iEnt );

        // Get the node geometry object
        GEN_Geometry_Object & tGeoObj = this->get_geometry_object( tNodeIndex );

        // Get the parent topology that this node was created on
        xtk::Topology const & tParentEdge = tGeoObj.get_parent_entity_topology( );

        MORIS_ASSERT(tParentEdge.get_topology_type() == xtk::Topology_Type::EDGE,"Only supporting interface sensitivity computation on an edge");

        // Get the node indices from the topology
        Matrix< IndexMat > const & tParentEntityNodes = tParentEdge.get_node_indices( );

        // Initialize sensitivity
        Matrix< DDRMat > tDxDp(1,1,0.0);

        // Get the node vars of the parent edge nodes
        Matrix< DDRMat > tEntityNodeVars( tParentEntityNodes.numel(), 1 );
        for(uint i = 0; i < tParentEntityNodes.numel(); i++)
        {
            tEntityNodeVars(i) = this->get_entity_phase_val( tParentEntityNodes(i), aGeomIndex );
        }

        // Recompute local intersection (This could be stored instead)
        Matrix< DDRMat > tIntersectLocalCoordinate( 1, 1, 0.0 );
        Matrix< DDRMat > tIntersectGlobalCoordinate( 1, 1, 0.0 );
        get_intersection_location(mThresholdValue,
                                  mPerturbationValue,
                                  aNodeCoords,
                                  tEntityNodeVars,
                                  tParentEntityNodes,
                                  tIntersectLocalCoordinate,
                                  tIntersectGlobalCoordinate,
                                  true,
                                  aGlbCoord);

        // FIXME: Parent edge nodes need to not be the ADVs
        Matrix< IndexMat > tADVIndices;

        compute_dx_dp_for_an_intersection( tParentEntityNodes, aNodeCoords, tIntersectLocalCoordinate, tEntityNodeVars, tDxDp, tADVIndices );

        tGeoObj.set_sensitivity_dx_dp( tDxDp );
        tGeoObj.set_node_adv_indices( tParentEntityNodes );
      }
}

//------------------------------------------------------------------------------

void GEN_Geometry_Engine::get_intersection_location( moris::real const &                      aIsocontourThreshold,
                                                     moris::real const &                      aPerturbationThreshold,
                                                     moris::Matrix< moris::DDRMat > const &   aGlobalNodeCoordinates,
                                                     moris::Matrix< moris::DDRMat > const &   aEntityNodeVars,
                                                     moris::Matrix< moris::IndexMat > const & aEntityNodeIndices,
                                                     moris::Matrix< moris::DDRMat > &         aIntersectionLocalCoordinates,
                                                     moris::Matrix< moris::DDRMat > &         aIntersectionGlobalCoordinates,
                                                     bool                                     aCheckLocalCoordinate,
                                                     bool                                     aComputeGlobalCoordinate )
{

    // compute the local coordinate where the intersection occurs
    Interpolation::linear_interpolation_value(aEntityNodeVars, aIsocontourThreshold, aIntersectionLocalCoordinates);

    // Perturb away from node if necessary
    if(aCheckLocalCoordinate)
    {
        if(aIntersectionLocalCoordinates(0, 0) >= 1-aPerturbationThreshold)
        {
            aIntersectionLocalCoordinates(0, 0) = aIntersectionLocalCoordinates(0, 0) - aPerturbationThreshold;
        }

        if(aIntersectionLocalCoordinates(0, 0) <= -1+aPerturbationThreshold)
        {
            aIntersectionLocalCoordinates(0, 0) = aIntersectionLocalCoordinates(0, 0) + aPerturbationThreshold;
        }
    }

    // Compute the global coordinate only if you plan to use it
    if(aComputeGlobalCoordinate)
    {
        // Place only the entity coordinates in a matrix
        moris::Matrix< moris::DDRMat > tEntityCoordinates(2,mSpatialDim);
        replace_row(aEntityNodeIndices(0,0), aGlobalNodeCoordinates,0,tEntityCoordinates);
        replace_row(aEntityNodeIndices(0,1), aGlobalNodeCoordinates,1,tEntityCoordinates);

        // compute the global coordinate
        Interpolation::linear_interpolation_location(tEntityCoordinates,aIntersectionLocalCoordinates,aIntersectionGlobalCoordinates);
    }
}

//------------------------------------------------------------------------------

void GEN_Geometry_Engine::compute_dx_dp_finite_difference( moris::real                      const & aPerturbationVal,
                                                           moris::Matrix< moris::DDRMat >   const & aGlobalNodeCoordinates,
                                                           moris::Matrix< moris::DDRMat >   const & aEntityNodeCoordinates,
                                                           moris::Matrix< moris::DDRMat >   const & aIntersectionLclCoordinate,
                                                           moris::Matrix< moris::IndexMat > const & aEntityNodeIndices,
                                                           moris::Matrix< moris::DDRMat >         & aEntityNodeVars,
                                                           moris::Matrix< moris::DDRMat >         & aDxDp )
{

    moris::size_t tNumNodeVars = aEntityNodeVars.n_rows();
    MORIS_ASSERT(tNumNodeVars == 2,"Currently compute_dx_dp_finite_difference has only been tested on edges");
    aDxDp.resize(2,3);

    moris::real tPerturbationLen = 2*aPerturbationVal;
    moris::real tScale   = 1/tPerturbationLen;
    Cell<moris::real>  tPerturbationSign = {1,-1};

    moris::Matrix< moris::DDRMat >       tDxDp(1,3);
    moris::Matrix< moris::DDRMat >       tPerturbedLocalCoordinate(1,1);
    Cell<moris::Matrix< moris::DDRMat >> tPerturbedGlobCoordinates = {moris::Matrix< moris::DDRMat >(1,3),
                                                             moris::Matrix< moris::DDRMat >(1,3)};
    // Loop over all the nodes and perturb up and down
    for(moris::size_t i = 0; i<tNumNodeVars; i++)
    {
        // Perturb up and down
        for(moris::size_t j = 0; j<2; j++)
        {

            moris::real tPerturb = tPerturbationSign(j)*aPerturbationVal;
            // Perturb
            aEntityNodeVars(i,0) = aEntityNodeVars(i,0) + tPerturb;

            // Locate perturbed interface
            get_intersection_location(mThresholdValue, aPerturbationVal, aGlobalNodeCoordinates, aEntityNodeVars, aEntityNodeIndices, tPerturbedLocalCoordinate, tPerturbedGlobCoordinates(j),false, true);

            // Reverse perturb
            aEntityNodeVars(i,0) = aEntityNodeVars(i,0) - tPerturb;

        }

        tDxDp.matrix_data() = tScale*(tPerturbedGlobCoordinates(1).matrix_data() - tPerturbedGlobCoordinates(0).matrix_data());

        replace_row(0,tDxDp,i,aDxDp);


    }
}

//------------------------------------------------------------------------------

void GEN_Geometry_Engine::compute_dx_dp_for_an_intersection( moris::Matrix< moris::IndexMat > const & aEntityNodeIndices,
                                                             moris::Matrix< moris::DDRMat >   const & aGlobalNodeCoordinates,
                                                             moris::Matrix< moris::DDRMat >   const & aIntersectionLclCoordinate,
                                                             moris::Matrix< moris::DDRMat >         & aEntityNodeVars,
                                                             moris::Matrix< moris::DDRMat >         & aDxDp,
                                                             moris::Matrix< moris::IndexMat >       & aADVIndices )
{
    moris::real tPerturbationLength = 0.005;
    moris::size_t tNumNodes = aEntityNodeIndices.n_cols();

    MORIS_ASSERT(tNumNodes == 2,"Currently, this function is only supported on edges");

    // Initialize
    moris::Cell< moris::Matrix< moris::DDRMat > > tDPhiiDp(2);// = { moris::Matrix< moris::DDRMat >(0,0), moris::Matrix< moris::DDRMat >(0,0) };


    uint tDim = aGlobalNodeCoordinates.n_cols();

    moris::Matrix< moris::DDRMat > tEntityNodeCoordinates( tNumNodes,tDim );

    // Assemble the entity local coordinates
    replace_row(aEntityNodeIndices(0,0), aGlobalNodeCoordinates,0,tEntityNodeCoordinates);
    replace_row(aEntityNodeIndices(0,1), aGlobalNodeCoordinates,1,tEntityNodeCoordinates);

    // Get information from a analytic geometry
    if(ActiveGeometry().is_analytic())
    {
        aADVIndices = get_node_adv_indices_analytic();
        for(moris::size_t i = 0; i < tNumNodes; i++)
        {
            tDPhiiDp(i) = ActiveGeometry().evaluate_sensitivity_dphi_dp_with_coordinate(aEntityNodeIndices(0, i),aGlobalNodeCoordinates);
        }

        compute_dx_dp_with_linear_basis( tDPhiiDp(0), tDPhiiDp(1), tEntityNodeCoordinates, aEntityNodeVars, aDxDp );
    }

    // Get information from a discrete geometry
    else
    {
        aADVIndices = get_node_adv_indices_discrete( aEntityNodeIndices );
        compute_dx_dp_finite_difference( tPerturbationLength, aGlobalNodeCoordinates, tEntityNodeCoordinates, aIntersectionLclCoordinate,aEntityNodeIndices,aEntityNodeVars, aDxDp );
    }
}

//------------------------------------------------------------------------------

GEN_Geometry_Object &
GEN_Geometry_Engine::get_geometry_object(moris::size_t const & aNodeIndex)
{
   return mGeometryObjectManager.get_geometry_object_from_manager(aNodeIndex);
}

//------------------------------------------------------------------------------

GEN_Geometry_Object const &
GEN_Geometry_Engine::get_geometry_object(moris::size_t const & aNodeIndex) const
{
   return mGeometryObjectManager.get_geometry_object_from_manager(aNodeIndex);
}

//------------------------------------------------------------------------------

moris::size_t GEN_Geometry_Engine::get_num_phases()
{
    return mPhaseTable.get_num_phases();
}

//------------------------------------------------------------------------------

moris::moris_index
GEN_Geometry_Engine::get_phase_sign_of_given_phase_and_geometry( moris::moris_index aPhaseIndex,
                                                                 moris::moris_index aGeometryIndex )
{
    return mPhaseTable.get_phase_sign_of_given_phase_and_geometry( aPhaseIndex,aGeometryIndex );
}

//------------------------------------------------------------------------------

moris::real
GEN_Geometry_Engine::get_entity_phase_val( moris::size_t const & aNodeIndex,
                                           moris::size_t const & aGeomIndex )
{
    GEN_Geometry_Object & tNodesGeoObj = get_geometry_object(aNodeIndex);
    moris::size_t tNodeRowIndex = tNodesGeoObj.get_phase_val_row();

    MORIS_ASSERT(tNodeRowIndex<mNodePhaseVals.n_rows(),"Entity row index out of bounds in the nodal phase val matrix");

    return mNodePhaseVals(tNodeRowIndex,aGeomIndex);
}

//------------------------------------------------------------------------------

moris::Matrix< moris::DDRMat > const &
GEN_Geometry_Engine::get_node_dx_dp( moris::size_t const & aNodeIndex ) const
{
    GEN_Geometry_Object const & tNodesGeoObj = get_geometry_object( aNodeIndex );
    return tNodesGeoObj.get_sensitivity_dx_dp();
}

//------------------------------------------------------------------------------

moris::Matrix< moris::IndexMat > const &
GEN_Geometry_Engine::get_node_adv_indices( moris::size_t const & aNodeIndex ) const
{
    GEN_Geometry_Object const & tNodesGeoObj = get_geometry_object( aNodeIndex );
    return tNodesGeoObj.get_node_adv_indices();
}

//------------------------------------------------------------------------------

void GEN_Geometry_Engine::get_phase_index( moris::Matrix< moris::DDSTMat > const & aNodeIndex,
                                           moris::Matrix< moris::DDSTMat > & aNodePhaseIndex )
{
    // 0 for neg 1 for pos
    moris::real tNodePhaseValue = 0;
    moris::Matrix< moris::IndexMat > tPhaseOnOff(1,mGeometry.size());

    for(moris::size_t i = 0; i<aNodeIndex.n_cols(); i++)
    {
        GEN_Geometry_Object & tNodesGeoObj = get_geometry_object(aNodeIndex(0,i));
        moris::size_t tNodeRowIndex = tNodesGeoObj.get_phase_val_row();

        for(moris::size_t iG = 0; iG<mGeometry.size(); iG++)
        {
            tNodePhaseValue =  mNodePhaseVals(tNodeRowIndex,iG);

            // Negative
            if(tNodePhaseValue<mThresholdValue)
            {
                tPhaseOnOff(0,iG) = 0;
            }

            else
            {
                tPhaseOnOff(0,iG) = 1;
            }
        }
        aNodePhaseIndex(i,0) = mPhaseTable.get_phase_index(tPhaseOnOff);
    }
}

//------------------------------------------------------------------------------

void GEN_Geometry_Engine::get_phase_index( moris::moris_index const & aNodeIndex,
                                           moris::size_t & aNodePhaseIndex )
{
    // 0 for neg 1 for pos
    moris::real tNodePhaseValue = 0;
    moris::Matrix< moris::IndexMat > tPhaseOnOff(1,mGeometry.size());

    GEN_Geometry_Object & tNodesGeoObj = get_geometry_object(aNodeIndex);
    moris::size_t tNodeRowIndex = tNodesGeoObj.get_phase_val_row();

    for(moris::size_t iG = 0; iG<mGeometry.size(); iG++)
    {
        tNodePhaseValue =  mNodePhaseVals(tNodeRowIndex,iG);

        // Negative
        if(tNodePhaseValue<mThresholdValue)
        {
            tPhaseOnOff(0,iG) = 0;
        }

        else
        {
            tPhaseOnOff(0,iG) = 1;
        }
    }
    aNodePhaseIndex = mPhaseTable.get_phase_index(tPhaseOnOff);
}

//------------------------------------------------------------------------------

moris::size_t
GEN_Geometry_Engine::get_node_phase_index_wrt_a_geometry( moris::size_t aNodeIndex,
                                                          moris::size_t aGeometryIndex )
{
    GEN_Geometry_Object & tNodesGeoObj = get_geometry_object(aNodeIndex);
    moris::size_t tNodeRowIndex = tNodesGeoObj.get_phase_val_row();

    moris::real tNodePhaseVal = mNodePhaseVals(tNodeRowIndex,aGeometryIndex);

    moris::size_t tPhaseOnOff = 10000;

    if(tNodePhaseVal<mThresholdValue)
    {
        tPhaseOnOff = 0;
    }
    else
    {
        tPhaseOnOff = 1;
    }

    return tPhaseOnOff;
}

//------------------------------------------------------------------------------

bool GEN_Geometry_Engine::is_geometry_analytic()
{
    return ActiveGeometry().is_analytic();
}

//------------------------------------------------------------------------------

moris::size_t GEN_Geometry_Engine::get_num_geometries()
{
    return mGeometry.size();
}

//------------------------------------------------------------------------------

moris::size_t GEN_Geometry_Engine::get_num_bulk_phase()
{
    return mPhaseTable.get_num_phases();
}

//------------------------------------------------------------------------------

moris::size_t GEN_Geometry_Engine::get_active_geometry_index()
{
    return mActiveGeometryIndex;
}

//------------------------------------------------------------------------------

void GEN_Geometry_Engine::advance_geometry_index()
{
    MORIS_ASSERT(mActiveGeometryIndex<get_num_geometries(),"Trying to advance past the number of geometries in the geometry engine");
    mActiveGeometryIndex += 1;
}

//------------------------------------------------------------------------------

moris::Matrix< moris::IndexMat >
GEN_Geometry_Engine::get_node_adv_indices_analytic()
{
    moris::size_t tNumDVS = get_num_design_vars_analytic();
    moris::Matrix< moris::IndexMat > tMatrix(1,tNumDVS);
    for(moris::size_t i = 0; i<tNumDVS; i++)
    {
        tMatrix(0,i) = (moris::moris_index)i;
    }
    return tMatrix;
}

//------------------------------------------------------------------------------
// FIXME: this is out-dated and not used in the current implementation of the PDV interface
moris::uint
GEN_Geometry_Engine::get_num_design_variables() const
{
    MORIS_ASSERT(mGeometry.size() == 1,"get num design variables only implemented on 1 geometry meshes");
    MORIS_ASSERT(mGeometry(0)->is_analytic(),"get num design variables only implemented on analytic geometries");
    return mGeometry(0)->get_num_des_vars();
}

//------------------------------------------------------------------------------
// FIXME: this is out-dated and not used in the current implementation of the PDV interface
moris::Matrix< moris::IndexMat >
GEN_Geometry_Engine::get_node_adv_indices_discrete(moris::Matrix< moris::IndexMat > const & aEntityNodes)
{
    //FIXME: use this line
//        moris::Matrix< moris::IndexMat > tNodeADVIndices = ActiveGeometry().get_node_adv_indices(aEntityNodes);

    return aEntityNodes.copy();
}

//------------------------------------------------------------------------------
// FIXME: this is out-dated and not used in the current implementation of the PDV interface
moris::size_t
GEN_Geometry_Engine::get_num_design_vars_analytic()
{
    moris::size_t tNumRows = 0;
    moris::size_t tNumCols = 0;
    moris::size_t tNumDVs = 0;
    for(moris::size_t i = 0; i<mGeometry.size(); i++)
    {
        mGeometry(i)->get_dphi_dp_size(tNumRows,tNumCols);
        tNumDVs += tNumCols;
    }

    return tNumDVs;
}
//------------------------------------------------------------------------------

Pdv_Host_Manager* GEN_Geometry_Engine::get_pdv_host_manager(  )
{
    return &mPdvHostManager;
}

Geometry_Object_Manager* GEN_Geometry_Engine::get_all_geom_obj()
{
    return &mGeometryObjectManager;
}

//------------------------------------------------------------------------------

void GEN_Geometry_Engine::register_mesh( mtk::Mesh_Manager* aMesh )
{
    mMesh = aMesh;

    mSpatialDim = mMesh->get_interpolation_mesh( 0 )->get_spatial_dim();	// assuming there is only one pair in the manager
}

moris_index GEN_Geometry_Engine::register_mesh( std::shared_ptr< moris::hmr::Mesh > aMesh )   //FIXME: this needs to be deleted and the GE should only be able to register a mesh pair
{
    mMesh_HMR.push_back( aMesh );

    mSpatialDim = mMesh_HMR( mMesh_HMR.size()-1 )->get_spatial_dim();

    return mMesh_HMR.size()-1;
}

void GEN_Geometry_Engine::set_performer( std::shared_ptr< hmr::HMR > aMesh )
{
    mHMRPerformer.push_back( aMesh );
}

void GEN_Geometry_Engine::set_library( std::shared_ptr< Library_IO > aLibrary )
{
	mLibrary = aLibrary;
}

void GEN_Geometry_Engine::perform( )
{
    this->perform_refinement();
}

void GEN_Geometry_Engine::perform_refinement()
{
	uint tLagrangeMeshIndex = 0;

    std::shared_ptr< moris::hmr::Mesh > tMesh = mHMRPerformer( 0 )->create_mesh( tLagrangeMeshIndex );

    mMesh_HMR.push_back( tMesh );

    mSpatialDim = tMesh->get_spatial_dim();

    this->initialize();

    for( sint Ik=0; Ik< mParameterList.get< moris::sint >( "number_HMR_refinments"); ++Ik )
    {
        moris::Cell< moris::Matrix< DDRMat > > tValues;

        this->get_field_values_for_all_geometries( tValues );

        for( uint Ik=0; Ik < tValues.size(); ++Ik )
        {
        	mHMRPerformer( 0 )->based_on_field_put_elements_on_queue( tValues( Ik ), tLagrangeMeshIndex );
        }

        mHMRPerformer( 0 )->perform_refinement_based_on_working_pattern( 0, false );
    }
}

//------------------------------------------------------------------------------

Matrix< DDRMat > GEN_Geometry_Engine::get_cylinder_vals( moris_index aWhichMesh,
                                                         GEN_CylinderWithEndCaps* aFiber,
                                                         uint aNumberOfFibers )  //FIXME this is currently only setup to work with an HMR member mesh
{
    uint tNumOfIPNodes = mMesh_HMR( aWhichMesh )->get_num_nodes();

    Matrix< DDRMat > tLSVals(tNumOfIPNodes, 1, 1.0); // FIXME: 10.0 needs to be replaced with problem dependent value

    for( uint k=0; k<aNumberOfFibers; ++k )
    {
        uint tNumCylinders = aFiber->get_number_of_cylinders(k);

        for( uint l=0; l<tNumCylinders; ++l )
        {
            Matrix<DDRMat> tMidPoint;
            Matrix<DDRMat> tLength;
            aFiber->midPoint_and_BB_dims( k, l, tMidPoint, tLength, 1.0 ); // FIXME: 1.0 needs to be the size of the coarsest element ( this is the bounding box buffer value )

            Matrix<IndexMat> tNodeIndices;
            mMesh_HMR( aWhichMesh )->get_nodes_indices_in_bounding_box( tMidPoint,
                                                                        { { tLength(0) },{ tLength(1) } ,{ tLength(2) }},
                                                                        tNodeIndices );
            for( uint i=0; i<tNodeIndices.numel(); ++i )
            {
                Matrix<DDRMat> tVertexCoords = mMesh_HMR( aWhichMesh )->get_mtk_vertex( tNodeIndices( i ) ).get_coords();
                tLSVals( tNodeIndices( i ) ) = std::min( tLSVals( tNodeIndices( i ) ),
                                                         aFiber->create_cylinder( tVertexCoords, k, l ) );
            }

        }
    }

      return tLSVals;
}

//------------------------------------------------------------------------------




//------------------------------------------------------------------------------
// private functions
//------------------------------------------------------------------------------
GEN_Geometry &
GEN_Geometry_Engine::ActiveGeometry() const
{
    return (*mGeometry(mActiveGeometryIndex));
}
//------------------------------------------------------------------------------
bool
GEN_Geometry_Engine::compute_intersection_info( moris::moris_index               const & aEntityIndex,
                                                moris::Matrix< moris::IndexMat > const & aEntityNodeInds,
                                                moris::Matrix< moris::DDRMat >   const & aNodeCoords,
                                                moris::size_t const &                    aCheckType,
                                                moris::Matrix< moris::IndexMat > &       aNodeADVIndices,
                                                GEN_Geometry_Object & aGeometryObject )
{
    //Initialize
    bool tIsIntersected = false;

    moris::real tMax = 0;
    moris::real tMin = 0;
    moris::uint tMaxLocRow = 0;
    moris::uint tMaxLocCol = 0;
    moris::uint tMinLocRow = 0;
    moris::uint tMinLocCol = 0;

    moris::size_t tNodeInd  = 0;
    moris::size_t tNumNodes = aEntityNodeInds.numel();
    moris::Matrix< moris::DDRMat > tEntityNodeVars(tNumNodes, 1);
    moris::Matrix< moris::DDRMat > tInterpLocationCoords(1,1);


    // Loop through nodes and get levelset values from precomputed values in aNodeVars or in the levelset mesh
    for(moris::size_t n = 0; n < tNumNodes; n++)
    {   //Get node id n
        tNodeInd = aEntityNodeInds(n);

        GEN_Geometry_Object & tGeoObj = get_geometry_object(tNodeInd);
        moris::size_t tPhaseValRowIndex = tGeoObj.get_phase_val_row();
        tEntityNodeVars(n) = mNodePhaseVals(tPhaseValRowIndex, mActiveGeometryIndex);
    }

    //get the max and minimum levelset value for the entity
    tMax = tEntityNodeVars.max(tMaxLocRow,tMaxLocCol);
    tMin = tEntityNodeVars.min(tMinLocRow,tMinLocCol);

    //    If there is a sign change in element node variables return true, else return false

    //TODO: intersection flag should not be a moris::real (needs to be a bool) split this function
    moris::Matrix< moris::DDRMat > tIntersection(1, 2, 0.0);// Initialize as false

    moris::real tErrorFactor = 1;
    // If the max is also the threshold value, figure out which node is on the interface

    if( moris::ge::approximate(tMin, mThresholdValue,tErrorFactor) && moris::ge::approximate(tMax, mThresholdValue,tErrorFactor))
    {
        aGeometryObject.set_parent_entity_index(aEntityIndex);
        aGeometryObject.mark_all_nodes_as_on_interface();
        tIsIntersected = true;
    }

    else if(moris::ge::approximate(tMax,mThresholdValue,tErrorFactor))
    {
        aGeometryObject.set_parent_entity_index(aEntityIndex);
        aGeometryObject.mark_node_as_on_interface(tMaxLocRow);
        tIsIntersected = true;
    }

    // If the min is also the threshold value, figure out which node is on the interface
    else if(moris::ge::approximate(tMin,mThresholdValue,tErrorFactor))
    {
        aGeometryObject.set_parent_entity_index(aEntityIndex);
        aGeometryObject.mark_node_as_on_interface(tMinLocRow);
        tIsIntersected = true;
    }

//        MORIS_ASSERT(tMax != mThresholdValue && tMin != mThresholdValue, "Threshold levelset value at all nodes! There is no handling of this inside XTK currently.");

    else if((tMax > mThresholdValue) &&
       (tMin < mThresholdValue))
    {
        aGeometryObject.set_parent_entity_index(aEntityIndex);
        aGeometryObject.mark_nodes_as_not_on_interface();
        tIsIntersected = true;
        if(aCheckType == 1)
        {
            moris::Matrix< moris::DDRMat > tIntersectLocalCoordinate(1,1);
            moris::Matrix< moris::DDRMat > tIntersectGlobalCoordinate(1,mSpatialDim);

            get_intersection_location(mThresholdValue,
                                      mPerturbationValue,
                                      aNodeCoords,
                                      tEntityNodeVars,
                                      aEntityNodeInds,
                                      tIntersectLocalCoordinate,
                                      tIntersectGlobalCoordinate,
                                      true,
                                      true);

            aGeometryObject.set_interface_loc_coord(tIntersectLocalCoordinate(0));
            aGeometryObject.set_interface_glb_coord(tIntersectGlobalCoordinate);
            if(mComputeDxDp)
            {
                moris::Matrix< moris::DDRMat > tDxDp(1,1,100.0);
                compute_dx_dp_for_an_intersection(aEntityNodeInds,aNodeCoords,tIntersectLocalCoordinate,tEntityNodeVars, tDxDp, aNodeADVIndices);
                aGeometryObject.set_sensitivity_dx_dp(tDxDp);
                aGeometryObject.set_node_adv_indices(aNodeADVIndices);
            }
       }
    }

    return tIsIntersected;

}
//------------------------------------------------------------------------------
void
GEN_Geometry_Engine::interpolate_level_set_value_to_child_node_location( xtk::Topology const & aParentTopology,
                                                                         moris::size_t const &                  aGeometryIndex,
                                                                         moris::Matrix< moris::DDRMat > const & aNodeLocalCoordinate,
                                                                         moris::Matrix< moris::DDRMat >       & aLevelSetValues  )
 {

     // Get node indices attached to parent (These are indices relative to another mesh and may need to be mapped)
     moris::Matrix< moris::IndexMat > const & tNodesAttachedToParent = aParentTopology.get_node_indices();

     // Get number of nodes attached to parent
     moris::size_t tNumNodesAttachedToParent = tNodesAttachedToParent.numel();
     moris::Matrix< moris::DDRMat > tNodesLevelSetValues(1, tNumNodesAttachedToParent);

     for(moris::size_t i = 0; i < tNumNodesAttachedToParent; i++)
     {
         GEN_Geometry_Object & tGeoObj = get_geometry_object(tNodesAttachedToParent(i));
         moris::size_t tPhaseRow = tGeoObj.get_phase_val_row();

         tNodesLevelSetValues(0,i) = mNodePhaseVals(tPhaseRow,aGeometryIndex);
     }

     // Ask the topology how to interpolate
     moris::Matrix< moris::DDRMat > tBasisValues(1,1);
     xtk::Basis_Function const & tParentBasisFunctions = aParentTopology.get_basis_function();

     // Evaluate basis function
     tParentBasisFunctions.evaluate_basis_function(aNodeLocalCoordinate,tBasisValues);

     // Compute \phi = Ni.\phi_i
     aLevelSetValues = tBasisValues*moris::trans(tNodesLevelSetValues);

 }

void GEN_Geometry_Engine::get_field_values_for_all_geometries( moris::Cell< Matrix< DDRMat > > & aAllFieldVals,
                                          const moris_index                 aWhichMesh )
{
    //TODO: implement for the case of discrete geometries and a mesh manager (rather than just an HMR mesh)
    uint tNumVertices = mMesh_HMR( aWhichMesh )->get_num_nodes();

    aAllFieldVals.resize( mGeometry.size() );

    for ( uint Ik = 0; Ik< mGeometry.size(); Ik++ )
    {
        aAllFieldVals( Ik ).set_size( tNumVertices, 1, - MORIS_REAL_MAX );

        for( uint iVert = 0; iVert <tNumVertices; iVert++)
        {
            Matrix< DDRMat > tCoord = mMesh_HMR( aWhichMesh )->get_mtk_vertex( iVert ).get_coords();

            moris::real tVal = - MORIS_REAL_MAX;

            Cell< moris::real > tTempConstCell = {{0}};

            mGeometry( Ik )->eval( tVal, tCoord, tTempConstCell );

            // FIXME will not work in parallel. Ind are not consistent because of aura
            aAllFieldVals( Ik )( iVert ) = tVal;
        }
    }
}
//------------------------------------------------------------------------------
}   // end ge namespace
}   // end moris namespace

