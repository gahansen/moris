#include <catch.hpp>

#include "cl_Communication_Manager.hpp" //COM/src
#include "cl_Communication_Tools.hpp" //COM/src
#include "typedefs.hpp" //COR/src

#include "cl_Matrix.hpp" //LINALG/src
#include "op_times.hpp" //LINALG/src
#include "fn_norm.hpp"


#include "cl_HMR_Parameters.hpp" //HMR/src
#include "cl_HMR_Element.hpp" //HMR/src
#include "cl_HMR_Background_Mesh_Base.hpp" //HMR/src
#include "cl_HMR_Lagrange_Mesh_Base.hpp" //HMR/src
#include "cl_HMR_BSpline_Mesh_Base.hpp" //HMR/src
#include "cl_HMR_Factory.hpp" //HMR/src
#define protected public
#define private   public
#include "cl_HMR_T_Matrix.hpp" //HMR/src
#undef protected
#undef private

TEST_CASE("HMR_T_Matrix_Private", "[moris],[mesh],[hmr]")
{

    // these tests are only performed in serial. They have nothing to do with parallel.
    if( moris::par_size() == 1 )
    {
         // This test checks that the 1D B-Spline functions
         // are correctly implemented.
        SECTION ( "T-Matrix: test B-Spline functions" )
        {
           // creaete minimal setup

            // create settings object
            moris::hmr::Parameters * tParameters = new moris::hmr::Parameters;

            // set number of elements
            moris::Matrix< moris::DDLUMat > tNumberOfElements = { {1}, {1} };
            tParameters->set_number_of_elements_per_dimension( tNumberOfElements );

            // do not print debug information during test
            tParameters->set_verbose( false );

            // set buffer to three
            tParameters->set_buffer_size ( 3 );

            // create background mesh
            moris::hmr::Factory tFactory;

            // create background mesh object
            moris::hmr::Background_Mesh_Base* tBackgroundMesh
                   = tFactory.create_background_mesh( tParameters );

            for( uint tOrder = 1; tOrder<=3; ++tOrder )
            {

                // create B-Spline mesh
                moris::hmr::BSpline_Mesh_Base* tBSplineMesh
                    =  tFactory.create_bspline_mesh(
                            tParameters,
                            tBackgroundMesh,
                            0,
                            tOrder );

                moris::hmr::Lagrange_Mesh_Base* tLagrangeMesh
                        =  tFactory.create_lagrange_mesh(
                                tParameters,
                                tBackgroundMesh,
                                tBSplineMesh,
                                0,
                                tOrder );

                // initialixe T-Matrix object
                moris::hmr::T_Matrix tTMatrix( tParameters, tBSplineMesh, tLagrangeMesh );

                // points where the function is tested
                moris::Matrix< moris::DDRMat > tXi = { { -1, -0.5, 0, 0.5, 1 } };

                // container for solution
                moris::Matrix< moris::DDRMat > tSolution;

                // fill solution vector with precomputed values
                switch ( tOrder )
                {
                case ( 1 ) :
                    {
                     moris::Matrix< moris::DDRMat > tSolution1 = {
                                    {  1, 0 },
                                    { 0.75, 0.25},
                                    { 0.5, 0.5 },
                                    { 0.25, 0.75 },
                                    { 0, 1} };
                     tSolution = tSolution1;
                     break;
                             }
                case ( 2 ) :
                    {
                        moris::Matrix< moris::DDRMat > tSolution3= {
                                {  0.5, 0.5, 0 },
                                { 0.28125, 0.6875, 0.03125},
                                { 0.125, 0.75, 0.125},
                                { 0.03125, 0.6875, 0.28125 },
                                {0, 0.5, 0.5} };

                        tSolution = tSolution3;
                        break;
                    }
                case( 3 ):
                    {
                        moris::Matrix< moris::DDRMat > tSolution3 = {
                              { 0.5, 2, 0.5, 0 },
                              { 0.2109375, 1.8359375, 0.9453125, 0.0078125 },
                              { 0.0625, 1.4375, 1.4375, 0.0625 },
                              { 0.0078125, 0.9453125, 1.8359375,  0.2109375 },
                              { 0, 0.5, 2, 0.5 } };
                        tSolution = tSolution3 * ( 1./3. );
                      break;
                    }
                case( 4 ):
                       {
                            moris::Matrix< moris::DDRMat > tSolution4 = {
                                    {  0.125, 1.375, 1.375, 0.125, 0  },
                                    { 0.03955078125, 0.974609375, 1.6826171875, 0.302734375, 0.00048828125  },
                                    { 0.0078125, 0.59375, 1.796875, 0.59375, 0.0078125  },
                                    { 0.00048828125, 0.302734375, 1.6826171875, 0.974609375, 0.03955078125  },
                                    { 0, 0.125, 1.375, 1.375, 0.125  } };

                           tSolution = tSolution4 * ( 1./3. );
                           break;
                       }
                case ( 5 ) :
                    {
                        moris::Matrix< moris::DDRMat > tSolution5 = {
                                { 0.025, 0.65,1.65,
                                        0.65, 0.025, 0 },
                                { 0.0059326171875,  0.3747314453125, 1.558935546875,
                                        0.984228515625, 0.0761474609375,  2.44140625000000e-05 },
                                { 0.00078125, 0.18515625, 1.3140625,
                                        1.3140625, 0.18515625, 0.00078125 },
                                { 2.44140625e-05, 0.0761474609375, 0.984228515625,
                                        1.558935546875, 0.3747314453125, 0.0059326171875 },
                                { 0, 0.025, 0.65, 1.65, 0.65, 0.025 } };

                         tSolution = tSolution5 * ( 1./3. );
                         break;
                    }
                }

                // loop over all contributing functions
                for( uint k=0; k<=tOrder; ++k )
                {
                    // reset error
                    moris::Matrix< moris::DDRMat > tError ( 5, 1, 0 );

                    for( uint i=0; i<5; ++i )
                    {
                        // save error into matrix
                        tError( i ) = tTMatrix.b_spline_shape_1d( tOrder, k, tXi( i ) )
                                           - tSolution( i, k );
                    }

                    // test solution
                    REQUIRE ( norm(tError) < 1e-12 );
                }

                delete tBSplineMesh;
                delete tLagrangeMesh;

            }
            // delete settings object
            delete tParameters;

            delete tBackgroundMesh;
        }

//-------------------------------------------------------------------------------

        // This test checks that the Lagrange shape functions work as expected
        SECTION ( "T-Matrix: Lagrange shape 2D" )
        {
            // create settings object
            moris::hmr::Parameters * tParameters = new moris::hmr::Parameters;

            // this geometry creates one element, geometry coordinates
            // are identical to parameter coordinates
            moris::Matrix< moris::DDLUMat > tNumberOfElements = { {1}, {1} };
            tParameters->set_number_of_elements_per_dimension( tNumberOfElements );

            // parameter space goes from -1 to +1
            moris::Matrix< moris::DDRMat > tDomain = { {2}, {2} };
            tParameters->set_domain_dimensions( tDomain );
            moris::Matrix< moris::DDRMat > tOffset = { {-1}, {-1} };
            tParameters->set_domain_offset( tOffset );

            // do not print debug information during test
            tParameters->set_verbose( false );

            for( uint tOrder=1; tOrder<=3; ++tOrder )
            {
                // set buffer size
                tParameters->set_buffer_size( tOrder );

                // activate truncation
                tParameters->set_bspline_truncation( true );


                // create factory
                moris::hmr::Factory tFactory;

                // create background mesh object
                moris::hmr::Background_Mesh_Base* tBackgroundMesh
                    = tFactory.create_background_mesh( tParameters );


                // create B-Spline Mesh
                moris::hmr::BSpline_Mesh_Base* tBSplineMesh
                    =  tFactory.create_bspline_mesh(
                            tParameters,
                            tBackgroundMesh,
                            0,
                            tOrder );

                // create B-Spline Mesh
                moris::hmr::Lagrange_Mesh_Base* tLagrangeMesh
                    =  tFactory.create_lagrange_mesh(
                            tParameters,
                            tBackgroundMesh,
                            tBSplineMesh,
                            0,
                            tOrder );

                // create T-Matrix object
                moris::hmr::T_Matrix * tTMatrix
                    = new moris::hmr::T_Matrix( tParameters, tBSplineMesh, tLagrangeMesh );

                // ask Lagrange mesh for number of nodes per element
                moris::luint tNumberOfNodes
                    = tLagrangeMesh->get_number_of_nodes_on_proc();

                // this flag must stay true all the time
                bool tCheck = true;

                // loop over all nodes
                for( uint k=0; k<tNumberOfNodes; ++k )
                {
                    // get pointer to node
                    moris::hmr::Basis * tNode
                        = tLagrangeMesh->get_basis_by_memory_index( k );

                    // get node coordinate
                    auto tXY = tNode->get_coords();

                    // shape function vector
                    moris::Matrix< moris::DDRMat > tN( tNumberOfNodes, 1 );

                    tTMatrix->lagrange_shape_2d( tXY, tN );

                    // epsilon environment
                    moris::real tEpsilon = 1e-12;

                    for( uint i=0; i<tNumberOfNodes; ++i )
                    {
                        if( i == k )
                        {
                            tCheck = tCheck && std::abs( tN( i ) - 1 ) < tEpsilon;
                        }
                        else
                        {
                            tCheck = tCheck && std::abs( tN( i ) )  < tEpsilon;
                        }
                    }
                }

                // tCheck must be true in order to pass test
                REQUIRE( tCheck );

                // tidy up memory
                delete tTMatrix;
                delete tBSplineMesh;
                delete tLagrangeMesh;
                delete tBackgroundMesh;
            }

            // delete settings object
            delete tParameters;

        } //end section

//-------------------------------------------------------------------------------

        // This test checks that the Lagrange shape functions work as expected
        SECTION ( "T-Matrix: Lagrange shape 3D" )
        {
            // create settings object
            moris::hmr::Parameters * tParameters = new moris::hmr::Parameters;

            // this geometry creates one element, geometry coordinates
            // are identical to parameter coordinates
            moris::Matrix< moris::DDLUMat > tNumberOfElements = { {1}, {1}, {1} };
            tParameters->set_number_of_elements_per_dimension( tNumberOfElements );

            // parameter space goes from -1 to +1
            moris::Matrix< moris::DDRMat > tDomain = { {2}, {2}, {2} };
            tParameters->set_domain_dimensions( tDomain );
            moris::Matrix< moris::DDRMat > tOffset = { {-1}, {-1}, {-1} };
            tParameters->set_domain_offset( tOffset );

            // do not print debug information during test
            tParameters->set_verbose( false );

            for( uint tOrder=1; tOrder<=3; ++tOrder )
            {
                // set buffer size
                tParameters->set_buffer_size( tOrder );

                // activate truncation
                tParameters->set_bspline_truncation( true );

                // create factory
                moris::hmr::Factory tFactory;

                // create background mesh object
                moris::hmr::Background_Mesh_Base* tBackgroundMesh
                = tFactory.create_background_mesh( tParameters );


                // create B-Spline Mesh
                moris::hmr::BSpline_Mesh_Base* tBSplineMesh
                =  tFactory.create_bspline_mesh(
                        tParameters,
                        tBackgroundMesh,
                        0,
                        tOrder );

                // create B-Spline Mesh
                moris::hmr::Lagrange_Mesh_Base* tLagrangeMesh
                =  tFactory.create_lagrange_mesh(
                        tParameters,
                        tBackgroundMesh,
                        tBSplineMesh,
                        0,
                        tOrder );

                // create T-Matrix object
                moris::hmr::T_Matrix * tTMatrix
                = new moris::hmr::T_Matrix( tParameters, tBSplineMesh, tLagrangeMesh );

                // ask Lagrange mesh for number of nodes per element
                moris::luint tNumberOfNodes
                = tLagrangeMesh->get_number_of_nodes_on_proc();

                // this flag must stay true all the time
                bool tCheck = true;

                // loop over all nodes
                for( uint k=0; k<tNumberOfNodes; ++k )
                {
                    // get pointer to node
                    moris::hmr::Basis * tNode
                    = tLagrangeMesh->get_basis_by_memory_index( k );

                    // get node coordinate
                    auto tXYZ = tNode->get_coords();

                    // shape function vector
                    moris::Matrix< moris::DDRMat > tN( tNumberOfNodes, 1 );

                    tTMatrix->lagrange_shape_3d( tXYZ, tN );

                    // epsilon environment
                    moris::real tEpsilon = 1e-12;

                    for( uint i=0; i<tNumberOfNodes; ++i )
                    {
                        if( i == k )
                        {
                            tCheck = tCheck && std::abs( tN( i ) - 1 ) < tEpsilon;
                        }
                        else
                        {
                            tCheck = tCheck && std::abs( tN( i ) )  < tEpsilon;
                        }
                    }
                }

                // tCheck must be true in order to pass test
                REQUIRE( tCheck );

                // tidy up memory
                delete tTMatrix;
                delete tBSplineMesh;
                delete tLagrangeMesh;
                delete tBackgroundMesh;
            }

            // delete settings object
            delete tParameters;

        } // end section

    } // end par rank
} // end test case

TEST_CASE("HMR_T_Matrix_Perturb", "[moris],[mesh],[hmr],[hmr_t_matrix_perturb]")
{
    moris::uint tBplineOrder = 2;
    moris::uint tLagrangeOrder = 2;
    moris::uint tMyCoeff = 1;

    std::cout<<"---"<<std::endl;



    ParameterList tParameters = create_hmr_parameter_list();

    tParameters.set( "number_of_elements_per_dimension", "9, 9" );
    tParameters.set( "domain_dimensions", "3, 3" );
    tParameters.set( "domain_offset", "-1.5, -1.5" );
    tParameters.set( "verbose", 1 );
    tParameters.set( "truncate_bsplines", 1 );
    tParameters.set( "bspline_orders", "2" );
    tParameters.set( "lagrange_orders", "2" );

    HMR tHMR( tParameters );

    auto tMesh = tHMR->create_mesh( tLagrangeOrder );

    auto tField = tMesh.create_field( "MyField", tBplineOrder );

    Matrix<DDRMat> & tCoeffs = tField->get_coefficients();

    tCoeffs.set_size( tMesh->get_num_coeffs( aBSplineOrder ), 1, 0.0 );

    tCoeffs( tMyCoeff ) = 1.0;

    tField->evaluate_node_values();

    //tHMR.flag_volume_and_surface_elements( tField );


    //tHMR.perform_refinement_and_map_fields();

    tHMR.save_to_exodus( "Mesh1.exo" );

    tHMR.save_last_step_to_exodus( "LastStep.exo" );

    tHMR.save_to_hdf5( "Database.hdf5" );

    tHMR.save_coeffs_to_hdf5_file( "TMatrix.hdf5" );

    tField->save_field_to_hdf5( "Circle.hdf5" );
}
