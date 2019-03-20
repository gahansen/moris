
#include "catch.hpp"

#include "cl_MTK_Vertex.hpp"    //MTK
#include "cl_MTK_Cell.hpp"
#include "cl_MTK_Enums.hpp"
#include "cl_MTK_Mesh.hpp"

#include "cl_Mesh_Factory.hpp"
#include "cl_MTK_Mesh_Tools.hpp"
#include "cl_MTK_Mesh_Data_Input.hpp"
#include "cl_MTK_Scalar_Field_Info.hpp"
#include "cl_MTK_Mesh.hpp"

#include "cl_Matrix.hpp"        //LINALG
#include "linalg_typedefs.hpp"

#include "cl_FEM_NodeProxy.hpp"                //FEM/INT/src
#include "cl_FEM_ElementProxy.hpp"             //FEM/INT/src
#include "cl_FEM_Node_Base.hpp"                //FEM/INT/src
#include "cl_FEM_Element_Factory.hpp"          //FEM/INT/src
#include "cl_FEM_IWG_Factory.hpp"              //FEM/INT/src

#include "cl_MDL_Model.hpp"

#include "cl_DLA_Solver_Factory.hpp"
#include "cl_DLA_Solver_Interface.hpp"

#include "cl_NLA_Nonlinear_Solver_Factory.hpp"
#include "cl_NLA_Nonlinear_Solver.hpp"
#include "cl_NLA_Nonlinear_Problem.hpp"
#include "cl_MSI_Solver_Interface.hpp"
#include "cl_MSI_Equation_Object.hpp"
#include "cl_MSI_Model_Solver_Interface.hpp"
#include "cl_DLA_Linear_Solver_Aztec.hpp"
#include "cl_DLA_Linear_Solver.hpp"

namespace moris
{

moris::real
LevelSetCircleFunction( const moris::Matrix< moris::DDRMat > & aPoint )
{
    return std::sqrt( std::pow(aPoint( 0 ), 2 ) + std::pow( aPoint( 1 ), 2 ) ) - 2.5;
}

moris::real
LevelSetSphereFunction( const moris::Matrix< moris::DDRMat > & aPoint )
{
    return  std::pow(aPoint( 0 ), 2 ) + std::pow( aPoint( 1 ), 2 ) - std::pow( 2.5, 2 );
}

moris::real
LevelSetFrontFunction( const moris::Matrix< moris::DDRMat > & aPoint )
{
    return aPoint( 0 ) - 2.5;
}

    namespace fem
    {

        TEST_CASE( "Element_Diffusion", "[moris],[fem],[ElemDiff]" )
        {
            if(par_size() == 1 )
            {

                // Create a 3D mesh of HEX8 using MTK ------------------------------------------
                std::cout<<" Create a 3D mesh of HEX8 using MTK "<<std::endl;
                //------------------------------------------------------------------------------
                uint aNumElemTypes = 1; // only 1 element type ( quad )
                uint aNumDim = 3;       // number of spatial dimensions

                // element connectivity
                Matrix< IdMat > aElementConnQuad = {{ 1, 2, 3, 4, 5, 6, 7, 8 }};

                // local to global element map
                Matrix< IdMat > aElemLocalToGlobalQuad = {{ 1 }};

                // node coordinates
                Matrix< DDRMat > aCoords = {{ 0.0, 0.0, 0.0 },
                                            { 1.0, 0.0, 0.0 },
                                            { 1.0, 1.0, 0.0 },
                                            { 0.0, 2.0, 0.0 },
                                            { 0.0, 0.0, 1.0 },
                                            { 1.0, 0.0, 1.0 },
                                            { 1.0, 1.0, 1.0 },
                                            { 0.0, 2.0, 1.0 }};

                // specify the local to global map
                Matrix< IdMat > aNodeLocalToGlobal = {{ 1,  2,  3,  4,  5,  6,  7,  8 }};

                // create mesh MTK database
                mtk::MtkMeshData tMeshData( aNumElemTypes );
                tMeshData.CreateAllEdgesAndFaces  = true;
                tMeshData.SpatialDim              = & aNumDim;
                tMeshData.ElemConn( 0 )           = & aElementConnQuad;
                tMeshData.NodeCoords              = & aCoords;
                tMeshData.LocaltoGlobalElemMap(0) = & aElemLocalToGlobalQuad;
                tMeshData.LocaltoGlobalNodeMap    = & aNodeLocalToGlobal;

                mtk::Mesh* tMesh = create_mesh( MeshType::STK, tMeshData );

                // create sideset
                Matrix<IndexMat> tSideset =
                    tMesh->get_entity_connected_to_entity_loc_inds( 0,
                                                                    EntityRank::ELEMENT,
                                                                    EntityRank::FACE );

                print( tSideset, " tSideset " );

//                //1) Create the fem nodes ------------------------------------------------------
//                std::cout<<" Create the fem nodes "<<std::endl;
//                //------------------------------------------------------------------------------
//
//                // number of mesh nodes
//                uint tNumOfNodes = tMesh->get_num_nodes();
//
//                //create a cell of fem nodes
//                moris::Cell< Node_Base* > tNodes( tNumOfNodes, nullptr );
//
//                // loop over the mesh nodes
//                for( uint k = 0; k < tNumOfNodes; k++ )
//                {
//                    // create a fem node for each mesh node
//                    tNodes( k ) = new fem::Node( & tMesh->get_mtk_vertex( k ) );
//                }
//
//                //2) Create the IWGs -----------------------------------------------------------
//                std::cout<<" Create the IWGs "<<std::endl;
//                //------------------------------------------------------------------------------
//
//                // input a cell of IWG types to be created
//                Cell< fem::IWG_Type > tIWGTypeList = { fem::IWG_Type::SPATIALDIFF_BULK };
//
//                // number of IWGs to be created
//                uint tNumOfIWGs = tIWGTypeList.size();
//
//                // a factory to create the IWGs
//                fem::IWG_Factory tIWGFactory;
//
//                // create a cell of IWGs for the problem considered
//                moris::Cell< fem::IWG* > tIWGs( tNumOfIWGs , nullptr );
//
//                // loop over the IWG types
//                for( uint i = 0; i < tNumOfIWGs; i++)
//                {
//                    // create an IWG with the factory for the ith IWG type
//                    tIWGs( i ) = tIWGFactory.create_IWGs( tIWGTypeList( i ) );
//                }
//
//                //3) Create the elements -------------------------------------------------------
//                std::cout<<" Create the elements "<<std::endl;
//                //------------------------------------------------------------------------------
////                // nodal weak bc
////                Matrix< DDRMat > tNodalValues = {{ 2.0, 2.0, 2.0, 2.0, 4.0, 2.0, 2.0, 2.0, 2.0,
////                                                   2.0, 2.0, 2.0, 2.0, 4.0, 2.0, 2.0, 2.0, 2.0,
////                                                   2.0, 2.0, 2.0, 2.0, 4.0, 2.0, 2.0, 2.0, 2.0 }};
//
//                // a factory to create the elements
//                Element_Factory tElementFactory;
//
//                // ask mesh about number of elements
//                uint tNumOfElements = tMesh->get_num_elems();
//
//                // create equation objects
//                Cell< MSI::Equation_Object* > tElements( tNumOfElements, nullptr );
//
//                // loop over the mesh elements
//                for( uint k = 0; k < tNumOfElements; k++ )
//                {
//                    // create the element
//                    tElements( k ) = tElementFactory.create_element( Element_Type::BULK,
//                                                                     & tMesh->get_mtk_cell( k ),
//                                                                     tIWGs,
//                                                                     tNodes );
//
////                    // get the nodal weak bcs of the element
////                    Matrix< DDRMat > & tNodalWeakBCs = tElements( k )->get_weak_bcs();
////
////                    // get the element number of nodes
////                    uint tNumberOfNodes = tElements( k )->get_num_nodes();
////
////                    // set size of the element nodal weak bc
////                    tNodalWeakBCs.set_size( tNumberOfNodes, 1 );
////
////                    // loop over the element nodes
////                    Matrix< IndexMat > tNodeIndices = tMesh->get_mtk_cell( k ).get_vertex_inds();
////                    for( uint l = 0; l < tNumberOfNodes; l++ )
////                    {
////                        // copy weak bc into element
////                        tNodalWeakBCs( l ) = tNodalValues( tNodeIndices( l ) );
////                    }
//                }
//
//                //4) Create the model solver interface -----------------------------------------
//                std::cout<<" Create the model solver interface "<<std::endl;
//                //------------------------------------------------------------------------------
//
//                //FIXME force the communication table
//                Matrix< IdMat > tCommunicationTable( 1, 1, 0 );
//
//                // FIXME: get map from mesh
//                uint tDofOrder = 1;
//                map< moris_id, moris_index > tCoefficientsMap;
//                //tMesh->get_adof_map( tDofOrder, tCoefficientsMap );
//
//                uint tNumCoeff = 1000000;
//                //= tMesh->get_num_coeffs( 1 )
//
//                moris::MSI::Model_Solver_Interface* tModelSolverInterface
//                    = new moris::MSI::Model_Solver_Interface( tElements,
//                                                              tCommunicationTable,
//                                                              tCoefficientsMap,
//                                                              tNumCoeff,
//                                                              tMesh );
//
//                tModelSolverInterface->set_param( "TEMP" )  = (sint)tDofOrder;
//
//                tModelSolverInterface->finalize();
//
//                // calculate AdofMap
//                Matrix< DDUMat > tAdofMap = tModelSolverInterface->get_dof_manager()->get_adof_ind_map();
//
//                //4) Create solver interface ---------------------------------------------------
//                std::cout<<" Create solver interface "<<std::endl;
//                //------------------------------------------------------------------------------
//
//                MSI::MSI_Solver_Interface * tSolverInterface
//                    = new moris::MSI::MSI_Solver_Interface( tModelSolverInterface );
//
//                // 5) Create Nonlinear Problem -------------------------------------------------
//                std::cout<<" Create Nonlinear Problem "<<std::endl;
//                //------------------------------------------------------------------------------
//
//                NLA::Nonlinear_Problem* tNonlinearProblem
//                    = new NLA::Nonlinear_Problem( tSolverInterface );
//
//                // 6) Create Solvers and solver manager ----------------------------------------
//                std::cout<<" Create Solvers and solver manager "<<std::endl;
//                //------------------------------------------------------------------------------
//
//                // create factory for nonlinear solver
//                NLA::Nonlinear_Solver_Factory tNonlinFactory;
//
//                // create nonlinear solver
//                std::shared_ptr< NLA::Nonlinear_Algorithm > tNonlinearSolverAlgorithm
//                    = tNonlinFactory.create_nonlinear_solver( NLA::NonlinearSolverType::NEWTON_SOLVER );
//
//                // create factory for linear solver
//                dla::Solver_Factory  tSolFactory;
//
//                // create linear solver
//                std::shared_ptr< dla::Linear_Solver_Algorithm > tLinearSolverAlgorithm
//                    = tSolFactory.create_solver( SolverType::AZTEC_IMPL );
//
//                // set default parameters for linear solver
//                tLinearSolverAlgorithm->set_param("AZ_diagnostics") = AZ_none;
//                tLinearSolverAlgorithm->set_param("AZ_output") = AZ_none;
//
//                // create solver manager
//                dla::Linear_Solver*    tLinSolver       = new dla::Linear_Solver();
//                NLA::Nonlinear_Solver* tNonlinearSolver = new NLA::Nonlinear_Solver();
//
//                // set manager and settings
//                tNonlinearSolverAlgorithm->set_linear_solver( tLinSolver );
//
//                // set first solver
//                tLinSolver->set_linear_algorithm( 0, tLinearSolverAlgorithm );
//
//                tNonlinearSolver->set_nonlinear_algorithm( tNonlinearSolverAlgorithm, 0 );
//
//                // 7) Solve --------------------------------------------------------------------
//                std::cout<<" Solve "<<std::endl;
//                //------------------------------------------------------------------------------
//                Matrix<DDRMat> tSolution1;
//
//                // call solver
//                tNonlinearSolver->solve( tNonlinearProblem );
//
//                // temporary array for solver
//                Matrix< DDRMat > tSolution;
//                tNonlinearSolverAlgorithm->get_full_solution( tSolution );
//
//                // get length of array
//                uint tLength = tSolution.length();
//
//                // rearrange data into output
//                tSolution1.set_size( tLength, 1 );
//
//                for( uint k = 0; k < tLength; k++ )
//                {
//                    tSolution1( k ) = tSolution( tAdofMap( k ) );
//                }
//                print( tSolution1, "tSolution1" );
//
//                // 8) Postprocessing
//                // dof type list for the solution to write on the mesh
//                moris::Cell< MSI::Dof_Type > tDofTypeList = { MSI::Dof_Type::TEMP };
//
//                // create a matrix to be filled  with the solution
//                Matrix< DDRMat > tTempSolutionField( tNumOfNodes, 1 );
//
//                // loop over the nodes
//                for( uint i = 0; i < tNumOfNodes; i++ )
//                {
//                    // get a list of elements connected to the ith node
//                    Matrix<IndexMat> tConnectedElements =
//                        tMesh->get_entity_connected_to_entity_loc_inds( static_cast< moris_index >( i ),
//                                                                        EntityRank::NODE,
//                                                                        EntityRank::ELEMENT );
//
//                    // number of connected element
//                    uint tNumConnectElem = tConnectedElements.numel();
//
//                    // reset the nodal value
//                    real tNodeVal = 0.0;
//
//                    // loop over the connected elements
//                    for( uint j = 0; j < tNumConnectElem; j++ )
//                    {
//                        // extract the field value at the ith node for the jth connected element
//                        real tElemVal
//                            = tElements( tConnectedElements( j ) )->get_element_nodal_pdof_value( i,
//                                                                                                  tDofTypeList);
//                        // add up the contribution of each element to the node value
//                        tNodeVal = tNodeVal + tElemVal;
//                    }
//                    // fill the solution matrix with the node value
//                    tTempSolutionField( i ) = tNodeVal/tNumConnectElem;
//                }
//                print( tTempSolutionField, "tTempSolutionField" );
//
//                // initialize Scalar_Field_Info structure with a DDRMat as the template type
//                moris::mtk::Scalar_Field_Info<DDRMat> tTempField;
//
//                // set the fields names
//                std::string tTempFieldName = "Temp_Field";
//                tTempField.set_field_name( tTempFieldName );
//
//                // set the entity rank associated with the fields
//                tTempField.set_field_entity_rank( EntityRank::NODE );
//
//                // initialize field information container
//                moris::mtk::MtkFieldsInfo tFieldsInfo;
//
//                // place the node field into the field info container
//                add_field_for_mesh_input( &tTempField, tFieldsInfo );
//
//                // declare some supplementary fields
//                tMeshData.FieldsInfo = &tFieldsInfo;
//
//                // create the mesh
//                mtk::Mesh* tMeshForOutput = create_mesh( MeshType::STK, tMeshData );
//
//                // add field to the mesh
//                tMeshForOutput->add_mesh_field_real_scalar_data_loc_inds( tTempFieldName,
//                                                                          EntityRank::NODE,
//                                                                          tTempSolutionField );
//
//                // create output mesh
//                std::string tOutputFile = "./int_ElemDiff_test.exo";
//                tMeshForOutput->create_output_mesh( tOutputFile );
//
//                // 8) Clean up -----------------------------------------------------------------
//                std::cout<<" Clean up "<<std::endl;
//                //------------------------------------------------------------------------------
//                delete tMesh;
//                delete tMeshForOutput;
//
//                for( uint i = 0; i < tNumOfNodes; i++ )
//                {
//                    delete tNodes( i );
//                }
//
//                for( uint i = 0; i < tNumOfIWGs; i++)
//                {
//                    delete tIWGs( i );
//                }
//
//                for( uint i = 0; i < tNumOfElements; i++ )
//                {
//                    delete tElements( i );
//                }
//
//                delete tModelSolverInterface;
//                delete tSolverInterface;
//                delete tNonlinearProblem;
//                delete tLinSolver;
//                delete tNonlinearSolver;

            }/* if( par_size() */
        }/* TEST_CASE */
    }/* namespace fem */
}/* namespace moris */
