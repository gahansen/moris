
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
#include "fn_equal_to.hpp" // ALG/src

#include "cl_FEM_NodeProxy.hpp"                //FEM/INT/src
#include "cl_FEM_ElementProxy.hpp"             //FEM/INT/src
#include "cl_FEM_Node_Base.hpp"                //FEM/INT/src
#include "cl_FEM_Element_Factory.hpp"          //FEM/INT/src
#include "cl_FEM_IWG_Factory.hpp"              //FEM/INT/src

#include "cl_MDL_Model.hpp"

#include "cl_HMR.hpp"
#include "cl_HMR_Background_Mesh.hpp" //HMR/src
#include "cl_HMR_BSpline_Mesh_Base.hpp" //HMR/src
#include "cl_HMR_Element.hpp" //HMR/src
#include "cl_HMR_Factory.hpp" //HMR/src
#include "cl_HMR_Field.hpp"
#include "cl_HMR_Lagrange_Mesh_Base.hpp" //HMR/src
#include "cl_HMR_Parameters.hpp" //HMR/src

#include "fn_norm.hpp"

moris::real
LevelSetFunction( const moris::Matrix< moris::DDRMat > & aPoint )
{
    return norm( aPoint ) - 0.5;
}

namespace moris
{
    namespace mdl
    {
        TEST_CASE( "Diffusion_2x2x2", "[moris],[mdl],[Diffusion_2x2x2]" )
        {
        if(par_size() == 1 )
        {
            // Create a 3D mesh of HEX8 using MTK ------------------------------------------
            std::cout<<" Create a 3D mesh of HEX8 using MTK "<<std::endl;
            //------------------------------------------------------------------------------

            std::string tPrefix = std::getenv("MORISROOT");
            std::string tMeshFileName = tPrefix + "projects/FEM/INT/test/data/Cube_with_side_sets.g";
            std::cout<<"Mesh input name = "<<tMeshFileName<<std::endl;

            moris::mtk::Scalar_Field_Info<DDRMat> tNodeField1;
            std::string tFieldName1 = "Temp_Field";
            tNodeField1.set_field_name( tFieldName1 );
            tNodeField1.set_field_entity_rank( EntityRank::NODE );

            // Initialize field information container
            moris::mtk::MtkFieldsInfo tFieldsInfo;

            // Place the node field into the field info container
            add_field_for_mesh_input(&tNodeField1,tFieldsInfo);

            // Declare some supplementary fields
            mtk::MtkMeshData tMeshData;
            tMeshData.FieldsInfo = &tFieldsInfo;

            moris::mtk::Mesh* tMesh = moris::mtk::create_mesh( MeshType::STK, tMeshFileName, &tMeshData );

            // create a list of IWG type
            Cell< Cell< fem::IWG_Type > >tIWGTypeList( 3 );
            tIWGTypeList( 0 ).resize( 1, fem::IWG_Type::SPATIALDIFF_BULK );
            tIWGTypeList( 1 ).resize( 1, fem::IWG_Type::SPATIALDIFF_DIRICHLET );
            tIWGTypeList( 2 ).resize( 1, fem::IWG_Type::SPATIALDIFF_NEUMANN );

            // create a list of active sidesets
            moris::Cell< moris_index >  tSidesetList = { 3, 5 };

            // create a list of BC type for the sidesets
            moris::Cell< fem::BC_Type > tSidesetBCTypeList = { fem::BC_Type::DIRICHLET,
                                                               fem::BC_Type::NEUMANN };

            // create model
            mdl::Model * tModel = new mdl::Model( tMesh, 1, tIWGTypeList,
                                                  tSidesetList, tSidesetBCTypeList );

            //solve
            moris::Matrix< DDRMat > tSolution11;
            tModel->solve( tSolution11 );

            // checking the solution--------------------------------------------------------
            //------------------------------------------------------------------------------
            // Expected solution
            Matrix< DDRMat > tExpectedSolution = {{ 25.0, 25.0, 25.0,
                                                    25.0,  5.0, 25.0,
                                                    45.0, 25.0,  5.0,
                                                    25.0, 45.0, 25.0,
                                                     5.0, 25.0, 45.0,
                                                     5.0, 45.0,  5.0,
                                                    45.0,  5.0, 45.0,
                                                     5.0, 45.0,  5.0,
                                                    45.0,  5.0, 45.0 }};

            // define an epsilon environment
            double tEpsilon = 1E-12;

            // define a bool for solution check
            bool tCheckNodalSolution = true;

            // number of mesh nodes
            uint tNumOfNodes = tMesh->get_num_nodes();

            // loop over the node and chyeck solution
            for ( uint i = 0; i < tNumOfNodes; i++ )
            {
                // check solution
                tCheckNodalSolution = tCheckNodalSolution
                                   && ( std::abs( tSolution11( i ) - tExpectedSolution( i ) ) < tEpsilon );
            }
            // check bool is true
            REQUIRE( tCheckNodalSolution );

            tModel->output_solution( tFieldName1 );

        }/* if( par_size() */
    }

        TEST_CASE( "Element_Diffusion_3", "[moris],[mdl],[Diffusion_block_7x8x9]" )
        {
        if(par_size() == 1 )
        {
            // Create a 3D mesh of HEX8 using MTK ------------------------------------------
            std::cout<<" Create a 3D mesh of HEX8 using MTK "<<std::endl;
            //------------------------------------------------------------------------------

            std::string tPrefix = std::getenv("MORISROOT");
            std::string tMeshFileName = tPrefix + "projects/FEM/MDL/test/data/Block_7x8x9.g";

            std::cout<<"Mesh input name = "<< tMeshFileName<<std::endl;

            moris::mtk::Scalar_Field_Info<DDRMat> tNodeField1;
            std::string tFieldName1 = "Temp_Field";
            tNodeField1.set_field_name(tFieldName1);
            tNodeField1.set_field_entity_rank(EntityRank::NODE);

            // Initialize field information container
            moris::mtk::MtkFieldsInfo tFieldsInfo;

            // Place the node field into the field info container
            add_field_for_mesh_input(&tNodeField1,tFieldsInfo);

            // Declare some supplementary fields
            mtk::MtkMeshData tMeshData;
            tMeshData.FieldsInfo = &tFieldsInfo;

            moris::mtk::Mesh* tMesh = moris::mtk::create_mesh( MeshType::STK, tMeshFileName, &tMeshData );

            //1) Create the fem nodes ------------------------------------------------------
            std::cout<<" Create the fem nodes "<<std::endl;
            //------------------------------------------------------------------------------
            Cell< Cell< fem::IWG_Type > >tIWGTypeList( 3 );
            tIWGTypeList( 0 ).resize( 1, fem::IWG_Type::SPATIALDIFF_BULK );
            tIWGTypeList( 1 ).resize( 1, fem::IWG_Type::SPATIALDIFF_DIRICHLET );
            tIWGTypeList( 2 ).resize( 1, fem::IWG_Type::SPATIALDIFF_NEUMANN );

            // create a list of active sidesets
            moris::Cell< moris_index >  tSidesetList = { 3, 5 };

            // create a list of BC type for the sidesets
            moris::Cell< fem::BC_Type > tSidesetBCTypeList = { fem::BC_Type::DIRICHLET,
                                                               fem::BC_Type::NEUMANN };

            // create model
            mdl::Model * tModel = new mdl::Model( tMesh, 1, tIWGTypeList,
                                                  tSidesetList, tSidesetBCTypeList );

            //solve
            moris::Matrix< DDRMat > tSolution11;
            tModel->solve( tSolution11 );


            tModel->output_solution( tFieldName1 );

            // print(tSolution11,"Solution");

            // Expected solution
            Matrix< DDRMat > tExpectedSolution =
                 {{+2.500000000875184e+01, +2.500000000987847e+01, +2.500000001157717e+01,
                   +2.500000001368304e+01, +2.500000001479958e+01, +2.500000001683809e+01,
                   +2.500000002126988e+01, +2.500000002173021e+01, +2.500000000560846e+01,
                   +2.500000000793639e+01, +2.500000001182473e+01, +2.500000001665577e+01,
                   +2.500000002234817e+01, +2.500000002784368e+01, +2.500000003077465e+01,
                   +2.500000002928050e+01, +2.499999999946052e+01, +2.500000000375664e+01,
                   +2.500000001180321e+01, +2.500000001954013e+01, +2.500000002360115e+01,
                   +2.500000003273075e+01, +2.500000003627261e+01, +2.500000002781392e+01,
                   +2.499999998871123e+01 }};

            // define an epsilon environment
            double tEpsilon = 1E-12;

            // define a bool for solution check
            bool tCheckNodalSolution = true;

            // loop over the node and chyeck solution
            for ( uint i = 0; i < 25; i++ )
            {
            	// check solution
            	tCheckNodalSolution = tCheckNodalSolution
            			&& ( std::abs( tSolution11( i ) - tExpectedSolution( i ) ) < tEpsilon );
            }
            // check bool is true
            REQUIRE( tCheckNodalSolution );

        }/* if( par_size() */
    }

//-------------------------------------------------------------------------------------------------------
	
     TEST_CASE( "Diffusion_hmr_10x4x4", "[moris],[mdl],[Diffusion_hmr_10x4x4]" )
     {
        if( par_size() == 2 )
        {
            // Create a 3D mesh of HEX8 using MTK ------------------------------------------
            std::cout<<" Create a 3D mesh of HEX8 using MTK "<<std::endl;
            //------------------------------------------------------------------------------

            moris::uint tBplineOrder = 1;
            moris::uint tLagrangeOrder = 1;
            moris::uint tMyCoeff = 1;

            hmr::ParameterList tParameters = hmr::create_hmr_parameter_list();

            tParameters.set( "number_of_elements_per_dimension", "10, 4, 4" );
            tParameters.set( "domain_dimensions", "10, 4, 4" );
            tParameters.set( "domain_offset", "-10.0, -2.0, -2.0" );
            tParameters.set( "domain_sidesets", "1, 6, 3, 4, 5, 2");
            tParameters.set( "verbose", 0 );
            tParameters.set( "truncate_bsplines", 1 );
            tParameters.set( "bspline_orders", "1" );
            tParameters.set( "lagrange_orders", "1" );

            tParameters.set( "use_multigrid", 0 );

            tParameters.set( "refinement_buffer", 1 );
            tParameters.set( "staircase_buffer", 1 );

             hmr::HMR tHMR( tParameters );

             std::shared_ptr< moris::hmr::Mesh > tMesh = tHMR.create_mesh( tLagrangeOrder );

             // create field
             std::shared_ptr< moris::hmr::Field > tField = tMesh->create_field( "Circle", tLagrangeOrder );

             for( uint k=0; k<3; ++k )
             {
                 tField->evaluate_scalar_function( LevelSetFunction );
                 tHMR.flag_surface_elements( tField );
                 tHMR.perform_refinement( moris::hmr::RefinementMode::SIMPLE );
                 tHMR.update_refinement_pattern();
             }

             tHMR.finalize();

             // evaluate node values
//             tField->evaluate_scalar_function( LevelSetFunction );
//             tHMR.save_to_exodus( "Circle_diff.exo" );
//             tHMR.save_faces_to_vtk( "Faces.vtk" );

            //1) Create the fem nodes ------------------------------------------------------
            std::cout<<" Create the fem nodes "<<std::endl;
            //------------------------------------------------------------------------------
            Cell< Cell< fem::IWG_Type > >tIWGTypeList( 3 );
            tIWGTypeList( 0 ).resize( 1, fem::IWG_Type::SPATIALDIFF_BULK );
            tIWGTypeList( 1 ).resize( 1, fem::IWG_Type::SPATIALDIFF_DIRICHLET );
            tIWGTypeList( 2 ).resize( 1, fem::IWG_Type::SPATIALDIFF_NEUMANN );

            // create a list of active sidesets
            Cell< moris_index >  tSidesetList = { 3, 5 };

            // create a list of BC type for the sidesets
            Cell< fem::BC_Type > tSidesetBCTypeList = { fem::BC_Type::DIRICHLET,
                                                        fem::BC_Type::NEUMANN };

            // create model
            mdl::Model * tModel = new mdl::Model( tMesh.get(), tBplineOrder, tIWGTypeList,
                                                  tSidesetList, tSidesetBCTypeList );

            //solve
            moris::Matrix< DDRMat > tSolution11;
            tModel->solve( tSolution11 );

            tModel->output_solution( "Circle" );

            tField->put_scalar_values_on_field( tModel->get_mSolHMR() );

//            tHMR.save_to_exodus( "Circle_diff_temp.exo" );

            // Expected solution
            Matrix< DDRMat > tExpectedSolution;

            if ( par_rank() == 0 )
            {
                // Expected solution for first processor
                 tExpectedSolution = {{ +4.999999999823309e+00,    +2.499999999379938e+01,    +4.499999998728015e+01,
                                        +6.499999997824342e+01,    +8.499999996238753e+01,    +1.049999999295709e+02,
                                        +4.999999999800635e+00,    +2.499999999394931e+01,    +4.499999998731124e+01,
                                        +6.499999997819508e+01,    +8.499999996482042e+01,    +1.049999999328457e+02,
                                        +4.999999999792283e+00,    +2.499999999418053e+01,    +4.499999998799023e+01,
                                        +6.499999998037731e+01,    +8.499999996742547e+01,    +1.049999999424134e+02,
                                        +4.999999999779568e+00,    +2.499999999442362e+01,    +4.499999998863433e+01,
                                        +6.499999998244976e+01,    +8.499999997341547e+01,    +1.049999999520176e+02,
                                        +4.999999999779885e+00, }};
               // print(tSolution11,"Processor_ONE");
            }
            else if ( par_rank() == 1 )
            {
                // Expected solution for second processor
                 tExpectedSolution = {{ +1.049999999295709e+02,    +1.249999999264930e+02,    +1.449999999406017e+02,
                                        +1.649999999466469e+02,    +1.749999999495133e+02,    +1.749999999500786e+02,
                                        +1.749999999489033e+02,    +1.749999999492710e+02,    +1.849999999512872e+02,
                                        +1.949999999603241e+02,    +1.849999999536432e+02,    +1.949999999629034e+02,
                                        +1.849999999509966e+02,    +1.949999999600533e+02,    +1.849999999538221e+02,
                                        +1.949999999627871e+02,    +2.049999999627414e+02,    +2.049999999653978e+02,
                                        +2.049999999635851e+02,    +2.049999999665377e+02,    +1.049999999328457e+02,
                                        +1.249999999292042e+02,    +1.449999999398408e+02,    +1.649999999465366e+02,
                                        +1.749999999506973e+02, }};

                //print(tSolution11,"Processor_TWO");
            }

            // define an epsilon environment
            double tEpsilon = 1E-8;

            // define a bool for solution check
            bool tCheckNodalSolution = true;

            // loop over the node and chyeck solution
            for ( uint i = 0; i < 25; i++ )
            {
                // check solution
                tCheckNodalSolution = tCheckNodalSolution
                                   && ( std::abs( tSolution11( i ) - tExpectedSolution( i ) ) < tEpsilon );
            }

            // check bool is true
            REQUIRE( tCheckNodalSolution );
        }/* if( par_size() */
    }

//-------------------------------------------------------------------------------------------------------

//    TEST_CASE( "Diffusion_hmr2_10x4x4", "[moris],[mdl],[Diffusion_hmr2_10x4x4]" )
//    {
//       if(par_size() == 1 )
//       {
//           // Create a 3D mesh of HEX8 using MTK ------------------------------------------
//           std::cout<<" Create a 3D mesh of HEX8 using MTK "<<std::endl;
//           //------------------------------------------------------------------------------
//
//           moris::uint tBplineOrder = 2;
//           moris::uint tLagrangeOrder = 1;
//           moris::uint tMyCoeff = 1;
//
//           hmr::ParameterList tParameters = hmr::create_hmr_parameter_list();
//
//           tParameters.set( "number_of_elements_per_dimension", "2, 2, 2" );
//           tParameters.set( "domain_dimensions", "2, 2, 2" );
//           tParameters.set( "domain_offset", "0, 0.0, 0.0" );
//           tParameters.set( "domain_sidesets", "1, 6, 3, 4, 5, 2");
//           tParameters.set( "verbose", 0 );
//           tParameters.set( "truncate_bsplines", 1 );
//           tParameters.set( "bspline_orders", "2" );
//           tParameters.set( "lagrange_orders", "1" );
//
//           tParameters.set( "use_multigrid", 0 );
//
//           tParameters.set( "refinement_buffer", 2 );
//           tParameters.set( "staircase_buffer", 1 );
//
//            hmr::HMR tHMR( tParameters );
//
//            std::shared_ptr< moris::hmr::Mesh > tMesh = tHMR.create_mesh( tLagrangeOrder );
//
//            // create field
//            std::shared_ptr< moris::hmr::Field > tField = tMesh->create_field( "Circle", tLagrangeOrder );
//
//            for( uint k=0; k<0; ++k )
//            {
//                tField->evaluate_scalar_function( LevelSetFunction );
//                tHMR.flag_surface_elements( tField );
//                tHMR.perform_refinement( moris::hmr::RefinementMode::SIMPLE );
//                tHMR.update_refinement_pattern();
//            }
//
//            tHMR.finalize();
//
//           // evaluate node values
//           tField->evaluate_scalar_function( LevelSetFunction );
//
//           tHMR.save_to_exodus( 2,"Circle_diff.exo" );
//
//           tHMR.save_bsplines_to_vtk("DLA_BSplines.vtk");
//
//           //1) Create the fem nodes ------------------------------------------------------
//           std::cout<<" Create the fem nodes "<<std::endl;
//           //------------------------------------------------------------------------------
//           Cell< Cell< fem::IWG_Type > >tIWGTypeList( 3 );
//           tIWGTypeList( 0 ).resize( 1, fem::IWG_Type::SPATIALDIFF_BULK );
//           tIWGTypeList( 1 ).resize( 1, fem::IWG_Type::SPATIALDIFF_DIRICHLET );
//           tIWGTypeList( 2 ).resize( 1, fem::IWG_Type::SPATIALDIFF_NEUMANN );
//
//           // create a list of active sidesets
//           Cell< moris_index >  tSidesetList = { 3, 5 };
//
//           // create a list of BC type for the sidesets
//           Cell< fem::BC_Type > tSidesetBCTypeList = { fem::BC_Type::DIRICHLET,
//                                                       fem::BC_Type::NEUMANN };
//
//           // create model
//           mdl::Model * tModel = new mdl::Model( tMesh.get(), tBplineOrder, tIWGTypeList,
//                                                 tSidesetList, tSidesetBCTypeList );
//
//           //solve
//           moris::Matrix< DDRMat > tSolution11;
//           tModel->solve( tSolution11 );
//
//           print(tSolution11,"tSolution11");
//
//           tModel->output_solution( "Circle" );
//
//           tField->put_scalar_values_on_field( tModel->get_mSolHMR() );
//
//           tHMR.save_to_exodus( 2,"Circle_diff_temp.exo" );
//
//           // Expected solution
//           Matrix< DDRMat > tExpectedSolution = {{ 5.000000000439168e+00,    2.499999999484336e+01,    4.499999998931914e+01,
//                                                   6.499999998398192e+01,    8.499999997909634e+01,    1.049999999750879e+02,
//                                                   1.249999999726532e+02,    1.349999999677999e+02,    1.349999999669917e+02,
//                                                   1.349999999688249e+02,    1.349999999678056e+02,    1.449999999632745e+02,
//                                                   1.549999999576012e+02,    1.449999999607157e+02,    1.549999999559840e+02,
//                                                   1.449999999644306e+02,    1.549999999607020e+02,    1.449999999638932e+02,
//                                                   1.549999999578126e+02,    1.649999999541855e+02,    1.749999999460777e+02,
//                                                   1.649999999497775e+02,    1.749999999406942e+02,    1.649999999575286e+02,
//                                                   1.749999999499552e+02,    1.649999999538873e+02,    1.749999999470990e+02,
//                                                   1.849999999366943e+02,    1.949999999299542e+02,    1.849999999312525e+02,
//                                                   1.949999999239139e+02,    1.849999999408975e+02,    1.949999999326252e+02,
//                                                   1.849999999358517e+02,    1.949999999274455e+02,    2.049999999278416e+02,
//                                                   2.049999999213750e+02,    2.049999999302681e+02,    2.049999999247313e+02,
//                                                   5.000000000440735e+00,    2.499999999481117e+01,    4.499999998922714e+01,
//                                                   6.499999998376413e+01,    8.499999997856834e+01,    1.049999999739319e+02 }};
//
//           // define an epsilon environment
//           double tEpsilon = 1E-12;
//
//           // define a bool for solution check
//           bool tCheckNodalSolution = true;
//
//           // loop over the node and chyeck solution
//           for ( uint i = 0; i < 45; i++ )
//           {
//               // check solution
//               tCheckNodalSolution = tCheckNodalSolution
//                                  && ( std::abs( tSolution11( i ) - tExpectedSolution( i ) ) < tEpsilon );
//           }
//           // check bool is true
//           REQUIRE( tCheckNodalSolution );
//       }/* if( par_size() */
//   }

//-------------------------------------------------------------------------------------------------------

    TEST_CASE( "Diffusion_hmr3_10x4x4", "[moris],[mdl],[Diffusion_hmr3_10x4x4]" )
    {
       if( (par_size() == 1) || (par_size() == 2) )
       {
           // Create a 3D mesh of HEX8 using MTK ------------------------------------------
           std::cout<<" Create a 3D mesh of HEX8 using MTK "<<std::endl;
           //------------------------------------------------------------------------------

           moris::uint tBplineOrder = 2;
           moris::uint tLagrangeOrder = 2;
           moris::uint tMyCoeff = 1;

           hmr::ParameterList tParameters = hmr::create_hmr_parameter_list();

           tParameters.set( "number_of_elements_per_dimension", "4, 2, 2" );
           tParameters.set( "domain_dimensions", "4, 2, 2" );
           tParameters.set( "domain_offset", "-2.0, 0.0, 0.0" );
           tParameters.set( "domain_sidesets", "1, 6, 3, 4, 5, 2");
           tParameters.set( "verbose", 0 );
           tParameters.set( "truncate_bsplines", 1 );
           tParameters.set( "bspline_orders", "2" );
           tParameters.set( "lagrange_orders", "2" );

           tParameters.set( "use_multigrid", 0 );

           tParameters.set( "refinement_buffer", 2 );
           tParameters.set( "staircase_buffer", 1 );

           hmr::HMR tHMR( tParameters );

           std::shared_ptr< moris::hmr::Mesh > tMesh = tHMR.create_mesh( tLagrangeOrder );

           // create field
           std::shared_ptr< moris::hmr::Field > tField = tMesh->create_field( "Circle", tLagrangeOrder );

           //auto tDatabase = tHMR.get_database();

           for( uint k=0; k<3; ++k )
           {
               tField->evaluate_scalar_function( LevelSetFunction );
               tHMR.flag_surface_elements( tField );

               //tDatabase->flag_element( 0 );
               tHMR.perform_refinement( moris::hmr::RefinementMode::SIMPLE );
               tHMR.update_refinement_pattern();
           }

           tHMR.finalize();

           // evaluate node values
//           tField->evaluate_scalar_function( LevelSetFunction );
//           tHMR.save_to_exodus( 1,"Circle_diff.exo" );

           //1) Create the fem nodes ------------------------------------------------------
           std::cout<<" Create the fem nodes "<<std::endl;
           //------------------------------------------------------------------------------
           Cell< Cell< fem::IWG_Type > >tIWGTypeList( 3 );
           tIWGTypeList( 0 ).resize( 1, fem::IWG_Type::SPATIALDIFF_BULK );
           tIWGTypeList( 1 ).resize( 1, fem::IWG_Type::SPATIALDIFF_DIRICHLET );
           tIWGTypeList( 2 ).resize( 1, fem::IWG_Type::SPATIALDIFF_NEUMANN );

           // create a list of active sidesets
           Cell< moris_index >  tSidesetList = { 3, 5 };

           // create a list of BC type for the sidesets
           Cell< fem::BC_Type > tSidesetBCTypeList = { fem::BC_Type::DIRICHLET,
                                                       fem::BC_Type::NEUMANN };

           // create model
           mdl::Model * tModel = new mdl::Model( tMesh.get(), tBplineOrder, tIWGTypeList,
                                                 tSidesetList, tSidesetBCTypeList );

           //solve
           moris::Matrix< DDRMat > tSolution11;
           tModel->solve( tSolution11 );

           //print(tSolution11,"tSolution11");

           tModel->output_solution( "Circle" );

           tField->put_scalar_values_on_field( tModel->get_mSolHMR() );

//           tHMR.save_to_exodus( 1,"Circle_diff_temp.exo" );
//           tHMR.save_bsplines_to_vtk("Bsplines_temp.vtk");

//           //-------------------------------------//
//           // print solution of each processor
//           if (par_rank() == 0){
//             print(tSolution11,"Processor_ONE");
//           }
//           else if (par_rank() == 1){
//             print(tSolution11,"Processor_TWO");
//           }
//           else {} // do nothing
//           //-------------------------------------//

            // Expected solution when running in serial
            Matrix< DDRMat > tExpectedSolution = {{ +1.976384396893782e-09, +9.999999997638666e+00, +2.299478928887239e-09,
                                                    +9.999999997438143e+00, +4.152303135013222e-09, +9.999999996543764e+00,
                                                    +2.631924777316510e-09, +9.999999997284709e+00, +1.999999999016610e+01,
                                                    +2.249999998863940e+01, +2.749999998937424e+01, +2.249999999091407e+01,
                                                    +2.749999998558418e+01, +2.249999998975273e+01, +2.749999998741196e+01,
                                                    +2.249999999001834e+01, +2.749999998686932e+01, +3.249999997374252e+01,
                                                    +3.374999998746107e+01, +3.624999997886972e+01, +3.374999998168578e+01,
                                                    +3.624999998243668e+01, +3.374999998299653e+01, +3.624999998061379e+01,
                                                    +3.374999998348704e+01 }};

            // expected solutions when running in parallel
            if (par_size() == 2)
            {
                if ( par_rank() == 0 )
                {
                    // Expected solution for first processor
                    tExpectedSolution = {{ -3.302872243818668e-08, +1.000000001738268e+01, +1.085000671093155e-08,
                                           +9.999999995258710e+00, +1.725491188274901e-08, +9.999999992226838e+00,
                                           -8.821987998234748e-09, +1.000000000506248e+01, +1.999999997518040e+01,
                                           +2.250000000695395e+01, +2.750000001516867e+01, +2.250000000553710e+01,
                                           +2.750000000184574e+01, +2.250000000522549e+01, +2.750000000242706e+01,
                                           +2.250000000469339e+01, +2.750000000978408e+01, +3.249999997587295e+01,
                                           +3.375000001858257e+01, +3.624999998752415e+01, +3.375000000630910e+01,
                                           +3.625000002645388e+01, +3.375000000782835e+01, +3.625000002339387e+01,
                                           +3.375000001143644e+01 }};
                   // print(tSolution11,"Processor_ONE");
                }
                else if ( par_rank() == 1 )
                {
                    // Expected solution for second processor
                     tExpectedSolution = {{ +4.249999984172224e+01, +4.750000055380576e+01, +4.250000015181325e+01,
                                            +4.749999966007174e+01, +4.250000011538052e+01, +4.749999976236016e+01,
                                            +4.249999995438112e+01, +4.750000020612755e+01, +5.249999984162645e+01,
                                            +5.375000021335701e+01, +5.624999996839500e+01, +5.374999994715878e+01,
                                            +5.625000007162272e+01, +5.374999996649412e+01, +5.625000006434173e+01,
                                            +5.375000007562546e+01, +5.625000003060088e+01, +5.750000035171650e+01,
                                            +5.250000045361771e+01, +5.749999987371483e+01, +5.250000035870602e+01,
                                            +5.749999990229202e+01, +5.249999989014849e+01, +5.750000009994142e+01,
                                            +4.249999992652671e+01 }};

                // print(tSolution11,"Processor_TWO");
                }
                else {} //do nothing
            }
            else {} // end expected solutions for parallel

            // define an epsilon environment
            double tEpsilon = 1E-9;

            // define a bool for solution check
            bool tCheckNodalSolution = true;

            // loop over the node and check solution
            for ( uint i = 0; i < 25; i++ )
            {
                // check solution
                tCheckNodalSolution = tCheckNodalSolution
                                   && ( std::abs( tSolution11( i ) - tExpectedSolution( i ) ) < tEpsilon );
            }
            // check bool is true
            REQUIRE( tCheckNodalSolution );
           }/* if( par_size() */
       }

//-------------------------------------------------------------------------------------------------------

    TEST_CASE( "Diffusion_hmr_cubic_10x4x4", "[moris],[mdl],[Diffusion_hmr_cubic_10x4x4]" )
    {
       if( par_size() == 1 )
       {
           // Create a 3D mesh of HEX8 using MTK ------------------------------------------
           std::cout<<" Create a 3D mesh of HEX8 using MTK "<<std::endl;
           //------------------------------------------------------------------------------

           moris::uint tBplineOrder = 3;
           moris::uint tLagrangeOrder = 3;
           moris::uint tMyCoeff = 1;

           hmr::ParameterList tParameters = hmr::create_hmr_parameter_list();

           tParameters.set( "number_of_elements_per_dimension", "4, 2, 2" );
           tParameters.set( "domain_dimensions", "4, 2, 2" );
           tParameters.set( "domain_offset", "-2.0, 0.0, 0.0" );
           tParameters.set( "domain_sidesets", "1, 6, 3, 4, 5, 2");
           tParameters.set( "verbose", 0 );
           tParameters.set( "truncate_bsplines", 1 );
           tParameters.set( "bspline_orders", "3" );
           tParameters.set( "lagrange_orders", "3" );

           tParameters.set( "use_multigrid", 0 );

           tParameters.set( "refinement_buffer", 1 );
           tParameters.set( "staircase_buffer", 1 );

           hmr::HMR tHMR( tParameters );

           std::shared_ptr< moris::hmr::Mesh > tMesh = tHMR.create_mesh( tLagrangeOrder );

           // create field
           std::shared_ptr< moris::hmr::Field > tField = tMesh->create_field( "Circle", tLagrangeOrder );

           for( uint k=0; k<2; ++k )
           {
               tField->evaluate_scalar_function( LevelSetFunction );
               tHMR.flag_surface_elements( tField );
               tHMR.perform_refinement( moris::hmr::RefinementMode::SIMPLE );
               tHMR.update_refinement_pattern();
           }

           tHMR.finalize();

           // evaluate node values
//           tField->evaluate_scalar_function( LevelSetFunction );
//           tHMR.save_to_exodus( 1,"Circle_diff.exo" );

           //1) Create the fem nodes ------------------------------------------------------
           std::cout<<" Create the fem nodes "<<std::endl;
           //------------------------------------------------------------------------------
           Cell< Cell< fem::IWG_Type > >tIWGTypeList( 3 );
           tIWGTypeList( 0 ).resize( 1, fem::IWG_Type::SPATIALDIFF_BULK );
           tIWGTypeList( 1 ).resize( 1, fem::IWG_Type::SPATIALDIFF_DIRICHLET );
           tIWGTypeList( 2 ).resize( 1, fem::IWG_Type::SPATIALDIFF_NEUMANN );

           // create a list of active sidesets
           Cell< moris_index >  tSidesetList = { 3, 5 };

           // create a list of BC type for the sidesets
           Cell< fem::BC_Type > tSidesetBCTypeList = { fem::BC_Type::DIRICHLET,
                                                       fem::BC_Type::NEUMANN };

           // create model
           mdl::Model * tModel = new mdl::Model( tMesh.get(), tBplineOrder, tIWGTypeList,
                                                 tSidesetList, tSidesetBCTypeList );

           //solve
           moris::Matrix< DDRMat > tSolution11;
           tModel->solve( tSolution11 );

           //print(tSolution11,"tSolution11");

           tModel->output_solution( "Circle" );

           tField->put_scalar_values_on_field( tModel->get_mSolHMR() );

//           tHMR.save_to_exodus( 1,"Circle_diff_temp.exo" );
//           tHMR.save_bsplines_to_vtk("Bsplines_temp_cubic.vtk");

            // Expected solution when running in serial
            Matrix< DDRMat > tExpectedSolution = {{ -5.000000000111186e+00,    +5.000000000069545e+00,    -4.999999999946497e+00,
                                                    +4.999999999979716e+00,    -4.999999999978130e+00,    +4.999999999989132e+00,
                                                    -5.000000000006851e+00,    +5.000000000003149e+00,    +1.499999999991764e+01,
                                                    +2.500000000013666e+01,    +3.500000000005484e+01,    +3.499999999998777e+01,
                                                    +3.499999999998835e+01,    +3.499999999999548e+01,    +1.500000000002021e+01,
                                                    +2.499999999996396e+01,    +1.500000000001141e+01,    +2.499999999997455e+01,
                                                    +1.499999999999502e+01,    +2.500000000000142e+01,    +3.499999999964501e+01,
                                                    +3.999999999991044e+01,    +4.500000000008001e+01,    +4.000000000000617e+01,
                                                    +4.499999999998079e+01 }};

            // define an epsilon environment
            double tEpsilon = 1E-9;

            // define a bool for solution check
            bool tCheckNodalSolution = true;

            // loop over the node and check solution
            for ( uint i = 0; i < 25; i++ )
            {
                // check solution
                tCheckNodalSolution = tCheckNodalSolution
                                   && ( std::abs( tSolution11( i ) - tExpectedSolution( i ) ) < tEpsilon );
            }
            // check bool is true
            REQUIRE( tCheckNodalSolution );
           }/* if( par_size() */
       }

//-------------------------------------------------------------------------------------------------------

//    // Test to verify that results that a Bar of 30x1x1 elements match with the results found in Matlab
//    TEST_CASE( "Diffusion_hmr3_bar", "[moris],[mdl],[Diffusion_hmr3_bar]" )
//     {
//        if( (par_size() == 1) || (par_size() == 2) )
//        {
//            // Create a 3D mesh of HEX8 using MTK ------------------------------------------
//            std::cout<<" Create a 3D mesh of HEX8 using MTK "<<std::endl;
//            //------------------------------------------------------------------------------
//
//            moris::uint tBplineOrder = 2;
//            moris::uint tLagrangeOrder = 2;
//            moris::uint tMyCoeff = 1;
//
//            hmr::ParameterList tParameters = hmr::create_hmr_parameter_list();
//
//            tParameters.set( "number_of_elements_per_dimension", "30, 1, 1" );
//            tParameters.set( "domain_dimensions", "30, 1, 1" );
//            tParameters.set( "domain_offset", "0, 0.0, 0.0" );
//            tParameters.set( "domain_sidesets", "1, 6, 3, 4, 5, 2");
//            tParameters.set( "verbose", 0 );
//            tParameters.set( "truncate_bsplines", 1 );
//            tParameters.set( "bspline_orders", "2" );
//            tParameters.set( "lagrange_orders", "2" );
//
//            tParameters.set( "use_multigrid", 0 );
//
//            tParameters.set( "refinement_buffer", 2 );
//            tParameters.set( "staircase_buffer", 1 );
//
//             hmr::HMR tHMR( tParameters );
//
//             std::shared_ptr< moris::hmr::Mesh > tMesh = tHMR.create_mesh( tLagrangeOrder );
//
//             // create field
//             std::shared_ptr< moris::hmr::Field > tField = tMesh->create_field( "Circle", tLagrangeOrder );
//
////             for( uint k=0; k<3; ++k )
////             {
////                 tField->evaluate_scalar_function( LevelSetFunction );
////                 tHMR.flag_surface_elements( tField );
////                 tHMR.perform_refinement( moris::hmr::RefinementMode::SIMPLE );
////                 tHMR.update_refinement_pattern();
////             }
//
//             tHMR.finalize();
//
//            // evaluate node values
//            tField->evaluate_scalar_function( LevelSetFunction );
//
//            tHMR.save_to_exodus( 1,"Bar_diff.exo" );
//
//
//            //1) Create the fem nodes ------------------------------------------------------
//                std::cout<<" Create the fem nodes "<<std::endl;
//                //------------------------------------------------------------------------------
//                Cell< Cell< fem::IWG_Type > >tIWGTypeList( 3 );
//                tIWGTypeList( 0 ).resize( 1, fem::IWG_Type::SPATIALDIFF_BULK );
//                tIWGTypeList( 1 ).resize( 1, fem::IWG_Type::SPATIALDIFF_DIRICHLET );
//                tIWGTypeList( 2 ).resize( 1, fem::IWG_Type::SPATIALDIFF_NEUMANN );
//
//                // create a list of active sidesets
//                Cell< moris_index >  tSidesetList = { 3, 5 };
//
//                // create a list of BC type for the sidesets
//                Cell< fem::BC_Type > tSidesetBCTypeList = { fem::BC_Type::DIRICHLET,
//                                                            fem::BC_Type::NEUMANN };
//
//                // create model
//                mdl::Model * tModel = new mdl::Model( tMesh.get(), tBplineOrder, tIWGTypeList,
//                                                      tSidesetList, tSidesetBCTypeList );
//
//                //solve
//                moris::Matrix< DDRMat > tSolution11;
//                tModel->solve( tSolution11 );
//
//
//
//                tModel->output_solution( "Circle" );
//
//                tField->put_scalar_values_on_field( tModel->get_mSolHMR() );
//
//                tHMR.save_to_exodus( 1,"Bar_diff_temp.exo" );
//
// //               //-------------------------------------//
// //               // print solution of each processor
// //               if (par_rank() == 0){
// //            	   print(tSolution11,"Processor_ONE");
// //               }
// //               else if (par_rank() == 1){
// //            	   print(tSolution11,"Processor_TWO");
// //               }
// //               else {} // do nothing
// //               //-------------------------------------//
//
//                // Expected solution when running in serial
//                Matrix< DDRMat > tExpectedSolution = {{ +1.976384396893782e-09, +9.999999997638666e+00, +2.299478928887239e-09,
//             		   	   	   	   	   	   	   	   	    +9.999999997438143e+00, +4.152303135013222e-09, +9.999999996543764e+00,
//                	   	   	   	   	   	   	   	   	    +2.631924777316510e-09, +9.999999997284709e+00, +1.999999999016610e+01,
//                	   	   	   	   	   	   	   	   	    +2.249999998863940e+01, +2.749999998937424e+01, +2.249999999091407e+01,
// 			   	   	   	   	   	   	   	   	   	        +2.749999998558418e+01, +2.249999998975273e+01, +2.749999998741196e+01,
//                	   	   	   	   	   	   	   	   	    +2.249999999001834e+01, +2.749999998686932e+01, +3.249999997374252e+01,
//                	   	   	   	   	   	   	   	   	    +3.374999998746107e+01, +3.624999997886972e+01, +3.374999998168578e+01,
//                	   	   	   	   	   	   	   	   	    +3.624999998243668e+01, +3.374999998299653e+01, +3.624999998061379e+01,
//                	   	   	   	   	   	   	   	   	    +3.374999998348704e+01 }};
//
//
//
//
//                // expected solutions when running in parallel
//                if (par_size() == 2)
//                {
//                if (par_rank() == 0){
//             	   // Expected solution for first processor
//             	   tExpectedSolution = {{ -3.302872243818668e-08, +1.000000001738268e+01, +1.085000671093155e-08,
//             	   	   	   	   	   	  	  +9.999999995258710e+00, +1.725491188274901e-08, +9.999999992226838e+00,
//										  -8.821987998234748e-09, +1.000000000506248e+01, +1.999999997518040e+01,
//										  +2.250000000695395e+01, +2.750000001516867e+01, +2.250000000553710e+01,
//										  +2.750000000184574e+01, +2.250000000522549e+01, +2.750000000242706e+01,
//										  +2.250000000469339e+01, +2.750000000978408e+01, +3.249999997587295e+01,
//										  +3.375000001858257e+01, +3.624999998752415e+01, +3.375000000630910e+01,
//										  +3.625000002645388e+01, +3.375000000782835e+01, +3.625000002339387e+01,
//										  +3.375000001143644e+01 }};
//             	   // print(tSolution11,"Processor_ONE");
//                }
//                if (par_rank() == 1){
//             	   // Expected solution for second processor
//             	   tExpectedSolution = {{ +4.249999984172224e+01, +4.750000055380576e+01, +4.250000015181325e+01,
//             	   	   	   	   	   	  	  +4.749999966007174e+01, +4.250000011538052e+01, +4.749999976236016e+01,
//										  +4.249999995438112e+01, +4.750000020612755e+01, +5.249999984162645e+01,
//										  +5.375000021335701e+01, +5.624999996839500e+01, +5.374999994715878e+01,
//										  +5.625000007162272e+01, +5.374999996649412e+01, +5.625000006434173e+01,
//										  +5.375000007562546e+01, +5.625000003060088e+01, +5.750000035171650e+01,
//										  +5.250000045361771e+01, +5.749999987371483e+01, +5.250000035870602e+01,
//										  +5.749999990229202e+01, +5.249999989014849e+01, +5.750000009994142e+01,
//										  +4.249999992652671e+01 }};
//
//
//             	   // print(tSolution11,"Processor_TWO");
//                }
//                else {} //do nothing
//                } else {} // end expected solutions for parallel
//
//
//                // define an epsilon environment
//                double tEpsilon = 1E-10;
//
//                // define a bool for solution check
//                bool tCheckNodalSolution = true;
//
//                // loop over the node and check solution
//                for ( uint i = 0; i < 25; i++ )
//                {
//             	   // check solution
//                    tCheckNodalSolution = tCheckNodalSolution
//                                       && ( std::abs( tSolution11( i ) - tExpectedSolution( i ) ) < tEpsilon );
//                }
//                // check bool is true
//                REQUIRE( tCheckNodalSolution );
//            }/* if( par_size() */
//        }



    }/* namespace fem */
}/* namespace moris */
