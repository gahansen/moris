#include <catch.hpp>
#include "cl_HMR.hpp"
#include "cl_HMR_Background_Mesh.hpp" //HMR/src
#include "cl_HMR_BSpline_Mesh_Base.hpp" //HMR/src
#include "cl_HMR_Element.hpp" //HMR/src
#include "cl_HMR_Factory.hpp" //HMR/src
#include "cl_HMR_Field.hpp"
#include "cl_HMR_Lagrange_Mesh_Base.hpp" //HMR/src
#include "cl_HMR_Parameters.hpp" //HMR/src

#include "cl_Communication_Manager.hpp" //COM/src
#include "cl_Communication_Tools.hpp" //COM/src
#include "typedefs.hpp" //COR/src
#include "cl_Matrix.hpp" //LINALG/src

#include "HDF5_Tools.hpp"

using namespace moris;
using namespace hmr;

TEST_CASE("HMR_Lagrange_Mesh", "[moris],[mesh],[hmr],[hmr_lagrange_mesh]")
{
//-------------------------------------------------------------------------------

    if(  moris::par_size() == 1  ||  moris::par_size() == 2  || moris::par_size() == 4 )
    {
//-------------------------------------------------------------------------------


        // empty container for B-Spline meshes
        moris::Cell< moris::hmr::BSpline_Mesh_Base* > tBSplineMeshes;


        SECTION("Lagrange Mesh 2D: test node uniqueness")
        {
            // create settings object
            moris::hmr::Parameters * tParameters = new moris::hmr::Parameters;

            // pattern this mesh operates on
            uint tPattern = tParameters->get_lagrange_input_pattern();

            // set number of elements
            moris::Matrix< moris::DDLUMat > tNumberOfElements = { {6}, {6} };
            tParameters->set_number_of_elements_per_dimension( tNumberOfElements );

            // set buffer size to zero
            tParameters->set_refinement_buffer( 0 );
            tParameters->set_staircase_buffer( 0 );

            // deactivate truncation
            tParameters->set_bspline_truncation( false );

            // create factory
            moris::hmr::Factory tFactory;

            // create background mesh object
            moris::hmr::Background_Mesh_Base* tBackgroundMesh = tFactory.create_background_mesh( tParameters );

            // maximum level to refine to
            moris::uint tLevel = 3;

            // set active pattern of output mesh
            tBackgroundMesh->set_activation_pattern( tPattern );

            // refine a few elements in the mesh
            for( moris::uint l=0; l<tLevel; ++l  )
            {
                auto tNumberOfElements =  tBackgroundMesh->get_number_of_active_elements_on_proc();

                // refine every other element
                for( moris::luint k=0; k<tNumberOfElements; k += 3 )
                {
                    // get element
                    moris::hmr::Background_Element_Base* tElement = tBackgroundMesh->get_element( k );

                    // flag element for refinement
                    tElement->put_on_refinement_queue();
                }
                // refine mesh
                tBackgroundMesh->perform_refinement();

            }

            for ( uint p=1; p<=3; ++p )
            {
                // set max order to 3
                tParameters->set_mesh_orders_simple( p );

                // create first order Lagrange mesh
                moris::hmr::Lagrange_Mesh_Base* tLagrangeMesh =  tFactory.create_lagrange_mesh( tParameters,
                                                                                                tBackgroundMesh,
                                                                                                tBSplineMeshes,
                                                                                                tPattern,
                                                                                                p );

                // test node uniqueness
                REQUIRE ( tLagrangeMesh->test_for_double_nodes() );
                // delete mesh
                delete tLagrangeMesh;
            }

            // delete background mesh
            delete tBackgroundMesh;

            // delete settings object
            delete tParameters;

        } // end section
//-------------------------------------------------------------------------------

        SECTION("Lagrange Mesh 3D: test node uniqueness")
        {
            // create settings object
            moris::hmr::Parameters * tParameters = new moris::hmr::Parameters;

            uint tPattern = tParameters->get_lagrange_input_pattern();

            // set number of elements
            moris::Matrix< moris::DDLUMat > tNumberOfElements = { {6}, {6}, {6} };
            tParameters->set_number_of_elements_per_dimension( tNumberOfElements );

            // set buffer size to zero
            tParameters->set_refinement_buffer( 0 );
            tParameters->set_staircase_buffer( 0 );

            // deactivate truncation
            tParameters->set_bspline_truncation( false );

            // set max order to 3
            tParameters->set_mesh_orders_simple( 3 );

            // create factory
            moris::hmr::Factory tFactory;

            // create background mesh object
            moris::hmr::Background_Mesh_Base* tBackgroundMesh = tFactory.create_background_mesh( tParameters );

            // set active pattern of output mesh
            tBackgroundMesh->set_activation_pattern( tPattern );

            // maximum level to refine to
            moris::uint tLevel = 3;

            // this test operates on pattern zero
            tBackgroundMesh->set_activation_pattern( 0 );

            // refine a few elements in the mesh
            for( moris::uint l=0; l<tLevel; ++l  )
            {
                auto tNumberOfElements =  tBackgroundMesh->get_number_of_active_elements_on_proc();

                // refine every other element
                for( moris::luint k=0; k<tNumberOfElements; k += 7 )
                {
                    // get element
                    moris::hmr::Background_Element_Base * tElement = tBackgroundMesh->get_element( k );

                    // flag element for refinement
                    tElement->put_on_refinement_queue();
                }
                // refine mesh
                tBackgroundMesh->perform_refinement();
            }

            for ( uint p=1; p<=3; ++p )
            {
                // create first order Lagrange mesh
                moris::hmr::Lagrange_Mesh_Base * tLagrangeMesh =  tFactory.create_lagrange_mesh( tParameters,
                                                                                                 tBackgroundMesh,
                                                                                                 tBSplineMeshes,
                                                                                                 tPattern,
                                                                                                 p );

                // test node uniqueness
                REQUIRE ( tLagrangeMesh->test_for_double_nodes() );
                // delete mesh
                delete tLagrangeMesh;
            }

            // delete background mesh
            delete tBackgroundMesh;

            // delete settings object
            delete tParameters;
        } // end section
    } // end if
//-------------------------------------------------------------------------------
} // end test

TEST_CASE("HMR_T_Matrix_Perturb_lin", "[moris],[mesh],[hmr],[hmr_t_matrix_perturb_lin]")
{
    if(  moris::par_size() == 1 )
    {
        moris::uint tBplineOrder = 1;
        moris::uint tLagrangeOrder = 1;
        moris::uint tMyCoeff = 1;

        ParameterList tParameters = create_hmr_parameter_list();

        tParameters.set( "number_of_elements_per_dimension", "2, 2" );
        tParameters.set( "domain_dimensions", "3, 3" );
        tParameters.set( "domain_offset", "-1.5, -1.5" );

        tParameters.set( "truncate_bsplines", 1 );
        tParameters.set( "bspline_orders", "1" );
        tParameters.set( "lagrange_orders", "1" );

        tParameters.set( "use_multigrid", 1 );

        tParameters.set( "refinement_buffer", 3 );
        tParameters.set( "staircase_buffer", 1 );

        tParameters.set("domain_sidesets", "1, 2, 3, 4" );

        HMR tHMR( tParameters );

        // std::shared_ptr< Database >
        auto tDatabase = tHMR.get_database();

        // manually select output pattern
        tDatabase->get_background_mesh()->set_activation_pattern( tHMR.get_parameters()->get_lagrange_output_pattern() );

        tHMR.perform_initial_refinement();

        // refine the first element three times
        for( uint tLevel = 0; tLevel < 4; ++tLevel )          // 4
        {
            tDatabase->flag_element( 0 );

            tDatabase->perform_refinement( moris::hmr::RefinementMode::SIMPLE, false );
        }

        // update database etc
        tDatabase->perform_refinement( moris::hmr::RefinementMode::SIMPLE, false );

        tHMR.finalize();

//        tHMR.renumber_and_save_to_exodus( "Mesh_lin_renumber.exo" );
//        tHMR.save_bsplines_to_vtk("Basis_renumber.vtk");

        auto tMesh = tHMR.create_mesh( tLagrangeOrder );
        uint tNumCoeffs = tMesh->get_num_coeffs( tBplineOrder );

        for( uint k=0; k<tNumCoeffs; ++k )
        {
            std::string tLabel = "BSPline_" + std::to_string( k );

            std::shared_ptr< moris::hmr::Field > tField = tMesh->create_field( tLabel, tBplineOrder );

            Matrix<DDRMat> & tCoeffs = tField->get_coefficients();

            tCoeffs.set_size( tMesh->get_num_coeffs( tBplineOrder ), 1, 0.0 );

            tCoeffs( k ) = 1.0;

            tField->evaluate_node_values();

            Matrix< DDRMat > tNodalFieldValues = tField->get_node_values();

            //tField->save_field_to_hdf5( "BSpline_Field_Values.hdf5", false );
            //tField->save_node_values_to_hdf5( "Node_Field_Values_lin.hdf5", false );
            Matrix< DDRMat > tNodalRefFieldValues;

            std::string tPrefix = std::getenv("MORISROOT");
            std::string tMeshFileName = tPrefix + "/projects/HMR/test/data/HMR_T_Matrix_Perturb-Reference_Values_Lin.hdf5";

            hid_t tFile    = open_hdf5_file( tMeshFileName );
            herr_t tStatus = 0;
            load_matrix_from_hdf5_file(
                    tFile,
                    tLabel,
                    tNodalRefFieldValues,
                    tStatus );

            tStatus = close_hdf5_file( tFile );

            MORIS_ERROR( tStatus == 0, "HMR_T_Matrix_Perturb: Status returned != 0, Error in reading reference values");

            CHECK( norm( tNodalFieldValues - tNodalRefFieldValues ) < 1e-12 );
        }
//
//        tHMR.renumber_and_save_to_exodus( "Mesh_lin_renumber.exo" );
//        tHMR.save_bsplines_to_vtk("Basis_renumber.vtk");
//        tHMR.save_faces_to_vtk( "Faces.vtk" );
    }
}

TEST_CASE("HMR_T_Matrix_Perturb_quad", "[moris],[mesh],[hmr],[hmr_t_matrix_perturb_quad]")
{
    if(  moris::par_size() == 1 )
    {
        moris::uint tBplineOrder = 2;
        moris::uint tLagrangeOrder = 2;
        moris::uint tMyCoeff = 1;

        ParameterList tParameters = create_hmr_parameter_list();

        tParameters.set( "number_of_elements_per_dimension", "2, 2" );
        tParameters.set( "domain_dimensions", "3, 3" );
        tParameters.set( "domain_offset", "-1.5, -1.5" );

        tParameters.set( "truncate_bsplines", 1 );
        tParameters.set( "bspline_orders", "2" );
        tParameters.set( "lagrange_orders", "2" );

        tParameters.set( "use_multigrid", 1 );

        tParameters.set( "refinement_buffer", 3 );
        tParameters.set( "staircase_buffer", 1 );

        //tParameters.set( "additional_lagrange_refinement", 2 );

        HMR tHMR( tParameters );

        // std::shared_ptr< Database >
        auto tDatabase = tHMR.get_database();

        // manually select output pattern
        tDatabase->get_background_mesh()->set_activation_pattern( tHMR.get_parameters()->get_lagrange_output_pattern() );

        tHMR.perform_initial_refinement();

        //tDatabase->get_background_mesh()->get_element(0)->set_min_refimenent_level(4);
        //tDatabase->get_background_mesh()->get_element(0)->put_on_refinement_queue();
        //tDatabase->flag_element( 0 );

        // refine the first element three times
        for( uint tLevel = 0; tLevel < 4; ++tLevel )
        {
            tDatabase->flag_element( 0 );

            // manually refine, do not reset pattern
            // tDatabase->get_background_mesh()->perform_refinement();
            tDatabase->perform_refinement( moris::hmr::RefinementMode::SIMPLE, false );
        }

        // update database etc
        tDatabase->perform_refinement( moris::hmr::RefinementMode::SIMPLE, false );

        //tDatabase->perform_refinement( moris::hmr::RefinementMode::LAGRANGE_REFINE, false );
        //tDatabase->perform_refinement( moris::hmr::RefinementMode::BSPLINE_REFINE, false );

//        tHMR.flag_element( 0 );
//        tHMR.get_database()->get_background_mesh()->get_element( 0 )->set_min_refimenent_level( 4 );
//
//        tHMR.perform_refinement(  moris::hmr::RefinementMode::LAGRANGE_REFINE );
//        tHMR.perform_refinement(  moris::hmr::RefinementMode::BSPLINE_REFINE );

        tHMR.finalize();

        auto tMesh = tHMR.create_mesh( tLagrangeOrder );

        std::cout<<tMesh->get_num_elems()<<std::endl;

        uint tNumCoeffs = tMesh->get_num_coeffs( tBplineOrder );

        for( uint k=0; k<tNumCoeffs; ++k )
        {
            std::string tLabel = "BSPline_" + std::to_string( k );

            std::shared_ptr< moris::hmr::Field > tField = tMesh->create_field( tLabel, tBplineOrder );

            Matrix<DDRMat> & tCoeffs = tField->get_coefficients();

            tCoeffs.set_size( tMesh->get_num_coeffs( tBplineOrder ), 1, 0.0 );

            tCoeffs( k ) = 1.0;

            tField->evaluate_node_values();

            Matrix< DDRMat > tNodalFieldValues = tField->get_node_values();

            //tField->save_field_to_hdf5( "BSpline_Field_Values.hdf5", false );
            //tField->save_node_values_to_hdf5( "Node_Field_Values.hdf5", false );
            Matrix< DDRMat > tNodalRefFieldValues;

            std::string tPrefix = std::getenv("MORISROOT");
            std::string tMeshFileName = tPrefix + "/projects/HMR/test/data/HMR_T_Matrix_Perturb-Reference_Values_Quad.hdf5";

            hid_t tFile    = open_hdf5_file( tMeshFileName );
            herr_t tStatus = 0;
            load_matrix_from_hdf5_file(
                    tFile,
                    tLabel,
                    tNodalRefFieldValues,
                    tStatus );

            tStatus = close_hdf5_file( tFile );

            MORIS_ERROR( tStatus == 0, "HMR_T_Matrix_Perturb: Status returned != 0, Error in reading reference values");

//            CHECK( norm( tNodalFieldValues - tNodalRefFieldValues ) < 1e-12 );
        }
        //tHMR.flag_volume_and_surface_elements( tField );

        //tHMR.perform_refinement_and_map_fields();

        tHMR.save_to_exodus( "Mesh1.exo" );
        //tHMR.save_bsplines_to_vtk("Basis.vtk");
        //tHMR.save_last_step_to_exodus( "LastStep.exo" );
        //tHMR.save_to_hdf5( "Database.hdf5" );
        //tHMR.save_coeffs_to_hdf5_file( "TMatrix.hdf5" );
    }
}

TEST_CASE("HMR_T_Matrix_Perturb_qub", "[moris],[mesh],[hmr],[hmr_t_matrix_perturb_qub]")
{
    if(  moris::par_size() == 1 )
    {
        moris::uint tBplineOrder = 3;
        moris::uint tLagrangeOrder = 3;
        moris::uint tMyCoeff = 1;

        ParameterList tParameters = create_hmr_parameter_list();

        tParameters.set( "number_of_elements_per_dimension", "2, 2" );
        tParameters.set( "domain_dimensions", "3, 3" );
        tParameters.set( "domain_offset", "-1.5, -1.5" );

        tParameters.set( "truncate_bsplines", 1 );
        tParameters.set( "bspline_orders", "3" );
        tParameters.set( "lagrange_orders", "3" );

        tParameters.set( "use_multigrid", 1 );

        tParameters.set( "refinement_buffer", 3 );
        tParameters.set( "staircase_buffer", 1 );

        HMR tHMR( tParameters );

        // std::shared_ptr< Database >
        auto tDatabase = tHMR.get_database();

        // manually select output pattern
        tDatabase->get_background_mesh()->set_activation_pattern( tHMR.get_parameters()->get_lagrange_output_pattern() );

        tHMR.perform_initial_refinement();

        // refine the first element three times
        for( uint tLevel = 0; tLevel < 4; ++tLevel )
        {
            tDatabase->flag_element( 0 );

            tDatabase->perform_refinement( moris::hmr::RefinementMode::SIMPLE, false );
        }

        // update database etc
        tDatabase->perform_refinement( moris::hmr::RefinementMode::SIMPLE, false );

        tHMR.finalize();

        std::cout<<"create mesh"<<std::endl;
//        auto tMesh = tHMR.create_mesh( tLagrangeOrder );

        std::shared_ptr< Interpolation_Mesh_HMR > tMesh =  tHMR.create_interpolation_mesh(
                tLagrangeOrder, tHMR.get_parameters()->get_lagrange_output_pattern() );

        uint tNumCoeffs = tMesh->get_num_coeffs( tBplineOrder );

        for( uint k=0; k<tNumCoeffs; ++k )
        {
            std::string tLabel = "BSPline_" + std::to_string( k );

            std::shared_ptr< moris::hmr::Field > tField = tMesh->create_field( tLabel, tBplineOrder );

            Matrix<DDRMat> & tCoeffs = tField->get_coefficients();

            tCoeffs.set_size( tMesh->get_num_coeffs( tBplineOrder ), 1, 0.0 );

            tCoeffs( k ) = 1.0;

            tField->evaluate_node_values();

            Matrix< DDRMat > tNodalFieldValues = tField->get_node_values();

            //tField->save_field_to_hdf5( "BSpline_Field_Values.hdf5", false );
//            tField->save_node_values_to_hdf5( "Node_Field_Values_Qub.hdf5", false );
            Matrix< DDRMat > tNodalRefFieldValues;

            std::string tPrefix = std::getenv("MORISROOT");
            std::string tMeshFileName = tPrefix + "/projects/HMR/test/data/HMR_T_Matrix_Perturb-Reference_Values_Qub.hdf5";

            hid_t tFile    = open_hdf5_file( tMeshFileName );
            herr_t tStatus = 0;
            load_matrix_from_hdf5_file(
                    tFile,
                    tLabel,
                    tNodalRefFieldValues,
                    tStatus );

            tStatus = close_hdf5_file( tFile );

            MORIS_ERROR( tStatus == 0, "HMR_T_Matrix_Perturb: Status returned != 0, Error in reading reference values");

            CHECK( norm( tNodalFieldValues - tNodalRefFieldValues ) < 1e-12 );
        }

        //tHMR.save_to_exodus( "Mesh_qub.exo" );
    }
}

TEST_CASE("Lagrange_Mesh_Pattern","[moris],[hmr],[Lagrange_Mesh_Pattern]")
{
    if(par_size() == 1)
    {
        // empty container for B-Spline meshes
        moris::Cell< moris::hmr::BSpline_Mesh_Base* > tBSplineMeshes;

        // create settings object
        moris::hmr::Parameters * tParameters = new moris::hmr::Parameters;

        // set number of elements
        tParameters->set_number_of_elements_per_dimension( { {4}, {4} } );

        // set buffer size to zero
        tParameters->set_refinement_buffer( 1 );
        tParameters->set_staircase_buffer( 1 );

        // deactivate truncation
        tParameters->set_bspline_truncation( false );

        // use simple patterns
        tParameters->set_mesh_orders_simple( 2 );       //FIXME might have to replace this

        // create factory
        moris::hmr::Factory tFactory;

        // create background mesh object
        moris::hmr::Background_Mesh_Base * tBackgroundMesh = tFactory.create_background_mesh( tParameters );

        //----------------------------------------------------------------------------------------------------------
        // Work on activation pattern 0 mesh
        tBackgroundMesh->set_activation_pattern( 0 );

        // element 0 is the element with ID 18
        tBackgroundMesh->get_element( 0 )->put_on_refinement_queue();
        tBackgroundMesh->perform_refinement( );

        tBackgroundMesh->get_element( 0 )->put_on_refinement_queue();
        tBackgroundMesh->perform_refinement( );

        //----------------------------------------------------------------------------------------------------------
        // Work on activation pattern 1 mesh
        tBackgroundMesh->set_activation_pattern( 1 );

        // element 0 is the element with ID 18
        tBackgroundMesh->get_element( 15 )->put_on_refinement_queue();
        tBackgroundMesh->perform_refinement( );

        tBackgroundMesh->get_element( 18 )->put_on_refinement_queue();
        tBackgroundMesh->perform_refinement( );

        //----------------------------------------------------------------------------------------------------------
        // unite pattern 0 and 1 on pattern 3
        moris::Cell< uint > tSourcePattern( 2, 0 );
        tSourcePattern( 1 ) = 1;
        tBackgroundMesh->unite_patterns( tSourcePattern, 3 );

        //----------------------------------------------------------------------------------------------------------
        // check pattern 2
        tBackgroundMesh->set_activation_pattern( 3 );

        // create first order Lagrange mesh
        moris::hmr::Lagrange_Mesh_Base* tLagrangeMesh_1 =  tFactory.create_lagrange_mesh( tParameters,
                                                                                          tBackgroundMesh,
                                                                                          tBSplineMeshes,
                                                                                          0,
                                                                                          1 );
        // create first order Lagrange mesh
        moris::hmr::Lagrange_Mesh_Base* tLagrangeMesh_2 =  tFactory.create_lagrange_mesh( tParameters,
                                                                                          tBackgroundMesh,
                                                                                          tBSplineMeshes,
                                                                                          1,
                                                                                          1 );
        // create first order Lagrange mesh
        moris::hmr::Lagrange_Mesh_Base* tLagrangeMesh_3 =  tFactory.create_lagrange_mesh( tParameters,
                                                                                          tBackgroundMesh,
                                                                                          tBSplineMeshes,
                                                                                          3,
                                                                                          1 );

        REQUIRE( tLagrangeMesh_1->get_number_of_nodes_on_proc()  == 43 );
        REQUIRE( tLagrangeMesh_2->get_number_of_nodes_on_proc()  == 43 );
        REQUIRE( tLagrangeMesh_3->get_number_of_nodes_on_proc()  == 61 );

        // output to exodus
//        STK * tSTK = tLagrangeMesh_3->create_stk_object(0);
//        tSTK->save_to_file( "cccccc.g");
//        delete tSTK;

        // Check some basis coordinates of Lagrange mesh 1
        const moris::real* tXYZ_1 = tLagrangeMesh_1->get_node_by_index( 2 )->get_xyz( );
        REQUIRE( tXYZ_1[0]  == 0.0625 );    REQUIRE( tXYZ_1[1]  == 0.0625 );
        const moris::real* tXYZ_2 = tLagrangeMesh_1->get_node_by_index( 13 )->get_xyz( );
        REQUIRE( tXYZ_2[0]  == 0.25 );    REQUIRE( tXYZ_2[1]  == 0.25 );
        const moris::real* tXYZ_3 = tLagrangeMesh_1->get_node_by_index( 15 )->get_xyz( );
        REQUIRE( tXYZ_3[0]  == 0.375 );    REQUIRE( tXYZ_3[1]  == 0.125 );
        const moris::real* tXYZ_4 = tLagrangeMesh_1->get_node_by_index( 36 )->get_xyz( );
        REQUIRE( tXYZ_4[0]  == 0.75 );    REQUIRE( tXYZ_4[1]  == 0.75 );
        const moris::real* tXYZ_14 = tLagrangeMesh_1->get_node_by_index( 41 )->get_xyz( );
        REQUIRE( tXYZ_14[0]  == 0.75 );    REQUIRE( tXYZ_14[1]  == 1.0 );

        // Check some basis coordinates of Lagrange mesh 2
        const moris::real* tXYZ_5 = tLagrangeMesh_2->get_node_by_index( 2 )->get_xyz( );
        REQUIRE( tXYZ_5[0]  == 0.25 );    REQUIRE( tXYZ_5[1]  == 0.25 );
        const moris::real* tXYZ_6 = tLagrangeMesh_2->get_node_by_index( 13 )->get_xyz( );
        REQUIRE( tXYZ_6[0]  == 0.75 );    REQUIRE( tXYZ_6[1]  == 0.5 );
        const moris::real* tXYZ_7 = tLagrangeMesh_2->get_node_by_index( 15 )->get_xyz( );
        REQUIRE( tXYZ_7[0]  == 0.25 );    REQUIRE( tXYZ_7[1]  == 0.75 );
        const moris::real* tXYZ_8 = tLagrangeMesh_2->get_node_by_index( 36 )->get_xyz( );
        REQUIRE( tXYZ_8[0]  == 0.875 );    REQUIRE( tXYZ_8[1]  == 1.0 );

        // Check some basis coordinates of Lagrange mesh 3
        const moris::real* tXYZ_9 = tLagrangeMesh_3->get_node_by_index( 2 )->get_xyz( );
        REQUIRE( tXYZ_9[0]  == 0.0625 );    REQUIRE( tXYZ_9[1]  == 0.0625 );
        const moris::real* tXYZ_10 = tLagrangeMesh_3->get_node_by_index( 13 )->get_xyz( );
        REQUIRE( tXYZ_10[0]  == 0.25 );    REQUIRE( tXYZ_10[1]  == 0.25 );
        const moris::real* tXYZ_11 = tLagrangeMesh_3->get_node_by_index( 15 )->get_xyz( );
        REQUIRE( tXYZ_11[0]  == 0.375 );    REQUIRE( tXYZ_11[1]  == 0.125 );
        const moris::real* tXYZ_12 = tLagrangeMesh_3->get_node_by_index( 36 )->get_xyz( );
        REQUIRE( tXYZ_12[0]  == 0.75 );    REQUIRE( tXYZ_12[1]  == 0.75 );
        const moris::real* tXYZ_13 = tLagrangeMesh_3->get_node_by_index( 57 )->get_xyz( );
        REQUIRE( tXYZ_13[0]  == 0.875 );    REQUIRE( tXYZ_13[1]  == 0.9375 );
        const moris::real* tXYZ_15 = tLagrangeMesh_3->get_node_by_index( 41 )->get_xyz( );
        REQUIRE( tXYZ_15[0]  == 0.875 );    REQUIRE( tXYZ_15[1]  == 0.75 );

        // delete mesh
        delete tLagrangeMesh_1;
        delete tLagrangeMesh_2;
        delete tLagrangeMesh_3;

        // delete background mesh
        delete tBackgroundMesh;

        // delete settings object
        delete tParameters;
    }
}


