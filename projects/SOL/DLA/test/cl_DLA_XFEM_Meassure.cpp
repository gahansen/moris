/*
 * cl_DLA_Multigrid_Test.cpp
 *
 *  Created on: Nov 18, 2018
 *      Author: schmidt
 */
#include "../../../FEM/INT/src/cl_FEM_Element_Bulk.hpp"
#include "catch.hpp"

#include "fn_equal_to.hpp" // ALG/src

#include "typedefs.hpp" // COR/src

#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"

#include "cl_Communication_Tools.hpp" // COM/src
#include "cl_Matrix_Vector_Factory.hpp" // DLA/src
#include "cl_SOL_Dist_Vector.hpp" // DLA/src

#include "cl_SDF_Generator.hpp"

#include "cl_MSI_Multigrid.hpp"
#include "cl_MSI_Model_Solver_Interface.hpp"
#include "cl_MSI_Solver_Interface.hpp"

#include "cl_PRM_MSI_Parameters.hpp"

#include "cl_HMR_Parameters.hpp"
#include "cl_HMR.hpp"
#include "cl_HMR_Field.hpp"
#include "cl_HMR_Mesh_Interpolation.hpp"
#include "cl_HMR_Mesh_Integration.hpp"

#include "cl_FEM_Node_Base.hpp"
#include "cl_FEM_IWG_L2.hpp"
#include "cl_FEM_Set.hpp"
#include "cl_FEM_IWG_Factory.hpp"

#include "cl_DLA_Solver_Factory.hpp"
#include "cl_DLA_Solver_Interface.hpp"

#include "cl_NLA_Nonlinear_Solver_Factory.hpp"
#include "cl_NLA_Nonlinear_Problem.hpp"
#include "cl_MSI_Solver_Interface.hpp"
#include "cl_MSI_Equation_Object.hpp"
#include "cl_MSI_Model_Solver_Interface.hpp"
#include "cl_DLA_Linear_Solver_Aztec.hpp"
#include "cl_DLA_Linear_Solver.hpp"
#include "cl_NLA_Nonlinear_Solver.hpp"
#include "cl_PRM_SOL_Parameters.hpp"
#include "cl_SOL_Warehouse.hpp"
#include "cl_TSA_Time_Solver.hpp"

#include "fn_norm.hpp"

moris::real
LevelSetFunction( const moris::Matrix< moris::DDRMat > & aPoint )
{
    return norm( aPoint ) - 0.9;
}

moris::real
LevelSetFunction_1( const moris::Matrix< moris::DDRMat > & aPoint )
{
    moris::real tPhi = std::atan2( aPoint( 0 ), aPoint( 1 ) );
    moris::real tLevelSetVaue = 0.5 + 0.1 * std::sin( 5 * tPhi ) - std::sqrt( std::pow( aPoint( 0 ), 2 ) + std::pow( aPoint( 1 ), 2 ) );

    return tLevelSetVaue;
}

namespace moris
{
using namespace dla;
using namespace NLA;

TEST_CASE("MDL FEM Benchmark Diff Interface","[MDL_FEM_Benchmark_Diff_Interface]")
{

    if(par_size() == 1)
    {
//	std::cout<<"I am proc: "<<par_rank()<<std::endl;

        uint tLagrangeMeshIndex = 0;

        // empty container for B-Spline meshes
        moris::Cell< moris::hmr::BSpline_Mesh_Base* > tBSplineMeshes;

        // create settings object
        moris::hmr::Parameters tParameters;

        tParameters.set_number_of_elements_per_dimension( { {4}, {2}, {2} } );
        tParameters.set_domain_dimensions( 10, 5, 5 );
        tParameters.set_domain_offset( 0.0, 0.0, 0.0 );
        tParameters.set_side_sets({ {1}, {2}, {3}, {4}, {5}, {6} });

        tParameters.set_bspline_truncation( true );

        tParameters.set_lagrange_orders  ( { {1} });
        tParameters.set_lagrange_patterns( { {0} });

        tParameters.set_bspline_orders   ( { {1} } );
        tParameters.set_bspline_patterns ( { {0} } );

        tParameters.set_output_meshes( { {0} } );
//        tParameters.set_lagrange_input_mesh( { { 0 } } );

        tParameters.set_staircase_buffer( 1 );

        tParameters.set_initial_refinement( 0 );

        tParameters.set_number_aura( true );

        Cell< Matrix< DDSMat > > tLagrangeToBSplineMesh( 1 );
        tLagrangeToBSplineMesh( 0 ) = { {0} };

        tParameters.set_lagrange_to_bspline_mesh( tLagrangeToBSplineMesh );

        // create the HMR object by passing the settings to the constructor
        moris::hmr::HMR tHMR( tParameters );

        tHMR.perform_initial_refinement( 0 );

        std::shared_ptr< moris::hmr::Mesh > tMesh01 = tHMR.create_mesh( tLagrangeMeshIndex );   // HMR Lagrange mesh
        //==============================
        std::shared_ptr< hmr::Field > tField = tMesh01->create_field( "gyroid", tLagrangeMeshIndex);

        tField->evaluate_scalar_function( tPlane_MDLFEMBench );

        moris::Cell< std::shared_ptr< moris::hmr::Field > > tFields( 1, tField );

        for( uint k=0; k<0; ++k )
        {
            tHMR.flag_surface_elements_on_working_pattern( tField );
//            tHMR.user_defined_flagging( user_defined_refinement_MDLFEMBench, tFields, tParam, 0 );
            tHMR.perform_refinement_based_on_working_pattern( 0, true );
            tField->evaluate_scalar_function( tPlane_MDLFEMBench );
        }
        tHMR.finalize();

//==============================
        tHMR.save_to_exodus( 0, "gyroid_general_geomEng.g" );

        hmr::Interpolation_Mesh_HMR * tInterpMesh = tHMR.create_interpolation_mesh( tLagrangeMeshIndex  );

        moris::ge::GEN_Geom_Field_HMR tFieldAsGeom(tField);

        moris::Cell<moris::ge::GEN_Geometry*> tGeometryVector = {&tFieldAsGeom};

        size_t tModelDimension = 3;
        moris::ge::GEN_Phase_Table  tPhaseTable( tGeometryVector.size(),  Phase_Table_Structure::EXP_BASE_2 );
        moris::ge::GEN_Geometry_Engine  tGeometryEngine( tGeometryVector,tPhaseTable,tModelDimension );

        xtk::Model tXTKModel( tModelDimension,tInterpMesh,&tGeometryEngine );
        tXTKModel.mVerbose = false;

        //Specify decomposition Method and Cut Mesh ---------------------------------------
        Cell<enum Subdivision_Method> tDecompositionMethods = {Subdivision_Method::NC_REGULAR_SUBDIVISION_HEX8, Subdivision_Method::C_HIERARCHY_TET4};
        tXTKModel.decompose(tDecompositionMethods);

       tXTKModel.perform_basis_enrichment( EntityRank::BSPLINE, 0 );

       xtk::Enriched_Interpolation_Mesh & tEnrInterpMesh = tXTKModel.get_enriched_interp_mesh();
       xtk::Enriched_Integration_Mesh   & tEnrIntegMesh = tXTKModel.get_enriched_integ_mesh();

       //==============================

       // place the pair in mesh manager
       mtk::Mesh_Manager tMeshManager;
       tMeshManager.register_mesh_pair( &tEnrInterpMesh, &tEnrIntegMesh);

       //------------------------------------------------------------------------------
       // create the properties
       std::shared_ptr< fem::Property > tPropConductivity1 = std::make_shared< fem::Property >();
       tPropConductivity1->set_parameters( { {{ 1.0 }} } );
       tPropConductivity1->set_val_function( tPropValConstFunc_MDLFEMBench );

       std::shared_ptr< fem::Property > tPropConductivity2 = std::make_shared< fem::Property >();
       tPropConductivity2->set_parameters( { {{ 1.0 }} } );
       tPropConductivity2->set_val_function( tPropValConstFunc_MDLFEMBench );

       std::shared_ptr< fem::Property > tPropDirichlet = std::make_shared< fem::Property >();
       tPropDirichlet->set_parameters( { {{ 0.0 }} } );
       tPropDirichlet->set_val_function( tPropValConstFunc_MDLFEMBench );

       std::shared_ptr< fem::Property > tPropNeumann = std::make_shared< fem::Property >();
       tPropNeumann->set_parameters( { {{ 20.0 }} } );
       tPropNeumann->set_val_function( tPropValConstFunc_MDLFEMBench );

       std::shared_ptr< fem::Property > tPropTempLoad1 = std::make_shared< fem::Property >();
       tPropTempLoad1->set_parameters( { {{ 0.0 }} } );
       tPropTempLoad1->set_val_function( tPropValConstFunc_MDLFEMBench );

       std::shared_ptr< fem::Property > tPropTempLoad2 = std::make_shared< fem::Property >();
       tPropTempLoad2->set_parameters( { {{ 0.0 }} } );
       tPropTempLoad2->set_val_function( tPropValConstFunc_MDLFEMBench );

       // define constitutive models
       fem::CM_Factory tCMFactory;

       std::shared_ptr< fem::Constitutive_Model > tCMDiffLinIso1 = tCMFactory.create_CM( fem::Constitutive_Type::DIFF_LIN_ISO );
       tCMDiffLinIso1->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
       tCMDiffLinIso1->set_property( tPropConductivity1, "Conductivity" );
       tCMDiffLinIso1->set_space_dim( 3 );

       std::shared_ptr< fem::Constitutive_Model > tCMDiffLinIso2 = tCMFactory.create_CM( fem::Constitutive_Type::DIFF_LIN_ISO );
       tCMDiffLinIso2->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
       tCMDiffLinIso2->set_property( tPropConductivity2, "Conductivity" );
       tCMDiffLinIso2->set_space_dim( 3 );

       // define stabilization parameters
       fem::SP_Factory tSPFactory;
       std::shared_ptr< fem::Stabilization_Parameter > tSPDirichletNitsche = tSPFactory.create_SP( fem::Stabilization_Type::DIRICHLET_NITSCHE );
       tSPDirichletNitsche->set_parameters( { {{ 100.0 }} } );
       tSPDirichletNitsche->set_property( tPropConductivity2, "Material", mtk::Master_Slave::MASTER );

       std::shared_ptr< fem::Stabilization_Parameter > tSPNitscheInterface = tSPFactory.create_SP( fem::Stabilization_Type::NITSCHE_INTERFACE );
       tSPNitscheInterface->set_parameters( { {{ 1.0 }} } );
       tSPNitscheInterface->set_property( tPropConductivity1, "Material", mtk::Master_Slave::MASTER );
       tSPNitscheInterface->set_property( tPropConductivity2, "Material", mtk::Master_Slave::SLAVE );

       std::shared_ptr< fem::Stabilization_Parameter > tSPMasterWeightInterface = tSPFactory.create_SP( fem::Stabilization_Type::MASTER_WEIGHT_INTERFACE );
       tSPMasterWeightInterface->set_property( tPropConductivity1, "Material", mtk::Master_Slave::MASTER );
       tSPMasterWeightInterface->set_property( tPropConductivity2, "Material", mtk::Master_Slave::SLAVE );

       std::shared_ptr< fem::Stabilization_Parameter > tSPSlaveWeightInterface = tSPFactory.create_SP( fem::Stabilization_Type::SLAVE_WEIGHT_INTERFACE );
       tSPSlaveWeightInterface->set_property( tPropConductivity1, "Material", mtk::Master_Slave::MASTER );
       tSPSlaveWeightInterface->set_property( tPropConductivity2, "Material", mtk::Master_Slave::SLAVE );

       // define the IWGs
       fem::IWG_Factory tIWGFactory;

       std::shared_ptr< fem::IWG > tIWGBulk1 = tIWGFactory.create_IWG( fem::IWG_Type::SPATIALDIFF_BULK );
       tIWGBulk1->set_residual_dof_type( { MSI::Dof_Type::TEMP } );
       tIWGBulk1->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
       tIWGBulk1->set_constitutive_model( tCMDiffLinIso1, "DiffLinIso", mtk::Master_Slave::MASTER );
       tIWGBulk1->set_property( tPropTempLoad1, "Load", mtk::Master_Slave::MASTER );

       std::shared_ptr< fem::IWG > tIWGBulk2 = tIWGFactory.create_IWG( fem::IWG_Type::SPATIALDIFF_BULK );
       tIWGBulk2->set_residual_dof_type( { MSI::Dof_Type::TEMP } );
       tIWGBulk2->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
       tIWGBulk2->set_constitutive_model( tCMDiffLinIso2, "DiffLinIso", mtk::Master_Slave::MASTER );
       tIWGBulk2->set_property( tPropTempLoad2, "Load", mtk::Master_Slave::MASTER );

       std::shared_ptr< fem::IWG > tIWGDirichlet = tIWGFactory.create_IWG( fem::IWG_Type::SPATIALDIFF_DIRICHLET_UNSYMMETRIC_NITSCHE );
       tIWGDirichlet->set_residual_dof_type( { MSI::Dof_Type::TEMP } );
       tIWGDirichlet->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
       tIWGDirichlet->set_stabilization_parameter( tSPDirichletNitsche, "DirichletNitsche" );
       tIWGDirichlet->set_constitutive_model( tCMDiffLinIso2, "DiffLinIso", mtk::Master_Slave::MASTER );
       tIWGDirichlet->set_property( tPropDirichlet, "Dirichlet", mtk::Master_Slave::MASTER );

       std::shared_ptr< fem::IWG > tIWGNeumann = tIWGFactory.create_IWG( fem::IWG_Type::SPATIALDIFF_NEUMANN );
       tIWGNeumann->set_residual_dof_type( { MSI::Dof_Type::TEMP } );
       tIWGNeumann->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
       tIWGNeumann->set_property( tPropNeumann, "Neumann", mtk::Master_Slave::MASTER );

       std::shared_ptr< fem::IWG > tIWGInterface = tIWGFactory.create_IWG( fem::IWG_Type::SPATIALDIFF_INTERFACE );
       tIWGInterface->set_residual_dof_type( { MSI::Dof_Type::TEMP } );
       tIWGInterface->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
       tIWGInterface->set_dof_type_list( {{ MSI::Dof_Type::TEMP }},mtk::Master_Slave::SLAVE );
       tIWGInterface->set_stabilization_parameter( tSPNitscheInterface, "NitscheInterface");
       tIWGInterface->set_stabilization_parameter( tSPMasterWeightInterface, "MasterWeightInterface" );
       tIWGInterface->set_stabilization_parameter( tSPSlaveWeightInterface, "SlaveWeightInterface" );
       tIWGInterface->set_constitutive_model( tCMDiffLinIso1, "DiffLinIso", mtk::Master_Slave::MASTER );
       tIWGInterface->set_constitutive_model( tCMDiffLinIso2, "DiffLinIso", mtk::Master_Slave::SLAVE );

       // create the IQIs
       fem::IQI_Factory tIQIFactory;

       std::shared_ptr< fem::IQI > tIQITEMP = tIQIFactory.create_IQI( fem::IQI_Type::DOF );
       tIQITEMP->set_output_type( vis::Output_Type::TEMP );
       tIQITEMP->set_dof_type_list( { { MSI::Dof_Type::TEMP} }, mtk::Master_Slave::MASTER );
       tIQITEMP->set_output_type_index( 0 );

       // define set info
       fem::Set_User_Info tSetBulk1;
       tSetBulk1.set_mesh_set_name( "HMR_dummy_c_p0" );
       tSetBulk1.set_IWGs( { tIWGBulk2 } );
       tSetBulk1.set_IQIs( { tIQITEMP } );

       fem::Set_User_Info tSetBulk2;
       tSetBulk2.set_mesh_set_name( "HMR_dummy_n_p0" );
       tSetBulk2.set_IWGs( { tIWGBulk2 } );
       tSetBulk2.set_IQIs( { tIQITEMP } );

       fem::Set_User_Info tSetBulk3;
       tSetBulk3.set_mesh_set_name( "HMR_dummy_c_p1" );
       tSetBulk3.set_IWGs( { tIWGBulk1 } );
       tSetBulk3.set_IQIs( { tIQITEMP } );

       fem::Set_User_Info tSetBulk4;
       tSetBulk4.set_mesh_set_name( "HMR_dummy_n_p1" );
       tSetBulk4.set_IWGs( { tIWGBulk1 } );
       tSetBulk4.set_IQIs( { tIQITEMP } );

       fem::Set_User_Info tSetDirichlet;
       tSetDirichlet.set_mesh_set_name( "SideSet_4_n_p0" );
       tSetDirichlet.set_IWGs( { tIWGDirichlet } );

       fem::Set_User_Info tSetNeumann;
       tSetNeumann.set_mesh_set_name( "SideSet_2_n_p1" );
       tSetNeumann.set_IWGs( { tIWGNeumann } );

       std::string tDblInterfaceSideSetName = tEnrIntegMesh.get_dbl_interface_side_set_name(0,1);

       fem::Set_User_Info tSetInterface1;
       tSetInterface1.set_mesh_set_name( tDblInterfaceSideSetName );
       tSetInterface1.set_IWGs( { tIWGInterface } );

       // create a cell of set info
       moris::Cell< fem::Set_User_Info > tSetInfo( 7 );
       tSetInfo( 0 ) = tSetBulk1;
       tSetInfo( 1 ) = tSetBulk2;
       tSetInfo( 2 ) = tSetBulk3;
       tSetInfo( 3 ) = tSetBulk4;
       tSetInfo( 4 ) = tSetDirichlet;
       tSetInfo( 5 ) = tSetNeumann;
       tSetInfo( 6 ) = tSetInterface1;

       // create model
       mdl::Model * tModel = new mdl::Model( &tMeshManager,
                                              0,
                                              tSetInfo );

       // --------------------------------------------------------------------------------------
       // Define outputs
       vis::Output_Manager tOutputData;
       tOutputData.set_outputs( 0,
                                vis::VIS_Mesh_Type::STANDARD,
                                "UT_MDL_FEM_Benchmark_Output.exo",
                                { "HMR_dummy_c_p0", "HMR_dummy_c_p1", "HMR_dummy_n_p0", "HMR_dummy_n_p1"},
                                { "Temperature" },
                                { vis::Field_Type::NODAL },
                                { vis::Output_Type::TEMP } );

       tModel->set_output_manager( &tOutputData );

       dla::Solver_Factory  tSolFactory;
       std::shared_ptr< dla::Linear_Solver_Algorithm > tLinearSolverAlgorithm = tSolFactory.create_solver( sol::SolverType::AZTEC_IMPL );

       tLinearSolverAlgorithm->set_param("AZ_diagnostics") = AZ_none;
       tLinearSolverAlgorithm->set_param("AZ_output") = AZ_all;
       tLinearSolverAlgorithm->set_param("AZ_solver") = AZ_gmres_condnum;
       tLinearSolverAlgorithm->set_param("AZ_precond") = AZ_none;
       //tLinearSolverAlgorithm->set_param("AZ_kspace") = 500;

       dla::Linear_Solver tLinSolver;

       tLinSolver.set_linear_algorithm( 0, tLinearSolverAlgorithm );

       // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       // STEP 2: create nonlinear solver and algorithm
       // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

       NLA::Nonlinear_Solver_Factory tNonlinFactory;
       std::shared_ptr< NLA::Nonlinear_Algorithm > tNonlinearSolverAlgorithm
       = tNonlinFactory.create_nonlinear_solver( NLA::NonlinearSolverType::NEWTON_SOLVER );

       tNonlinearSolverAlgorithm->set_linear_solver( &tLinSolver );

       NLA::Nonlinear_Solver tNonlinearSolver;
       tNonlinearSolver.set_nonlinear_algorithm( tNonlinearSolverAlgorithm, 0 );

       // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       // STEP 3: create time Solver and algorithm
       // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       tsa::Time_Solver_Factory tTimeSolverFactory;
       std::shared_ptr< tsa::Time_Solver_Algorithm > tTimeSolverAlgorithm
       = tTimeSolverFactory.create_time_solver( tsa::TimeSolverType::MONOLITHIC );

       tTimeSolverAlgorithm->set_nonlinear_solver( &tNonlinearSolver );

       tsa::Time_Solver tTimeSolver;

       tTimeSolver.set_time_solver_algorithm( tTimeSolverAlgorithm );

       sol::SOL_Warehouse tSolverWarehouse;

       tSolverWarehouse.set_solver_interface(tModel->get_solver_interface());

       tNonlinearSolver.set_solver_warehouse( &tSolverWarehouse );
       tTimeSolver.set_solver_warehouse( &tSolverWarehouse );

       tNonlinearSolver.set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
       tTimeSolver.set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );

       tTimeSolver.set_output( 0, tSolverOutputCriteria_MDLFEMBench );

       // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       // STEP 4: Solve and check
       // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
       tTimeSolver.solve();
       Matrix<DDRMat> tFullSol;
       tTimeSolver.get_full_solution(tFullSol);

       delete tInterpMesh;
    }

}/* END_TEST_CASE */


}


