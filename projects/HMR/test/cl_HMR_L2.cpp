
#include <catch.hpp>
#include "cl_HMR.hpp"
#include "cl_HMR_Database.hpp"
#include "cl_HMR_Field.hpp"
#include "HMR_Globals.hpp"

#include "cl_Communication_Manager.hpp" // COM/src
#include "cl_Communication_Tools.hpp" // COM/src
#include "typedefs.hpp" // COR/src
#include "banner.hpp" // COR/src
#include "cl_Matrix.hpp" // LINALG/src
#include "linalg_typedefs.hpp" // LINALG/src
#include "fn_r2.hpp"
#include "fn_norm.hpp"

using namespace moris;

moris::real
LevelSetFunction( const moris::Matrix< moris::DDRMat > & aPoint )
{
    return norm( aPoint ) - 1.2;
}

TEST_CASE("HMR_L2_Test", "[moris],[mesh],[hmr],[hmr_L2]")
{

    // can only perform test for 1, 2 or 4 procs
    if( moris::par_size() == 1 || moris::par_size() == 2 || moris::par_size() == 4 )
    {
        // do this test for 2 and 3 dimensions
        for( moris::uint tDimension=2; tDimension<=3; ++tDimension )
        {

            // do this for first, second and third order
            for( moris::uint tOrder=1; tOrder<=3; tOrder++ )
            {

//------------------------------------------------------------------------------
//  HMR Parameters setup
//------------------------------------------------------------------------------

                // The parameter object controls the behavior of HMR.
                moris::hmr::Parameters tParameters;

                moris::Matrix< moris::DDLUMat > tNumberOfElements;

                // set element size
                if( moris::par_size() == 1 )
                {
                    tNumberOfElements.set_size( tDimension, 1, 2 );
                }
                else if ( moris::par_size() == 2 )
                {
                    tNumberOfElements.set_size( tDimension, 1, 6 );
                }
                else if ( moris::par_size() == 4 )
                {
                    tNumberOfElements.set_size( tDimension, 1, 6 );
                }

                // set values to parameters
                tParameters.set_number_of_elements_per_dimension( tNumberOfElements );

                // make mesh output silent
                tParameters.set_verbose( false );

                // B-Spline truncation is turned on by default.
                // It is recommended to leave this setting as is.
                tParameters.set_bspline_truncation( true );

                // set mesh order
                tParameters.set_mesh_orders_simple( tOrder );

//------------------------------------------------------------------------------
//  HMR Initialization
//------------------------------------------------------------------------------

                // create the HMR object by passing the settings to the constructor
                moris::hmr::HMR tHMR( tParameters );

                // std::shared_ptr< Database >
                auto tDatabase = tHMR.get_database();

                // manually select output pattern
                tDatabase->get_background_mesh()->set_activation_pattern( tParameters.get_bspline_input_pattern() );

                // refine the first element three times
                // fixme: change this to 3
                for( uint tLevel = 0; tLevel < 1; ++tLevel )
                {
                    tDatabase->flag_element( 0 );

                    // manually refine, do not reset pattern
                    tDatabase->get_background_mesh()->perform_refinement();
                }

                // update database etc
                tDatabase->perform_refinement( moris::hmr::RefinementMode::SIMPLE, false );

                // manually select output pattern
                tDatabase->get_background_mesh()->set_activation_pattern( tParameters.get_bspline_output_pattern() );

                // refine the last element three times
                // fixme: change this to 3
                for( uint tLevel = 0; tLevel < 1; ++tLevel )
                {
                    tDatabase->flag_element( tDatabase->get_number_of_elements_on_proc()-1 );

                    // manually refine, do not reset pattern
                    tDatabase->get_background_mesh()->perform_refinement();
                }
                // update database etc
                tDatabase->perform_refinement( moris::hmr::RefinementMode::SIMPLE , false );

                // manually create union
                tDatabase->unite_patterns( tParameters.get_bspline_input_pattern(),
                                           tParameters.get_bspline_output_pattern(),
                                           tParameters.get_union_pattern() );

                // update background mesh
                // test if max polynomial is 3
                if ( tParameters.get_max_polynomial() > 2 )
                {
                    // activate extra pattern for exodus
                    tDatabase->add_extra_refinement_step_for_exodus();
                }

                //tHMR.mBackgroundMesh->save_to_vtk("Background.vtk");
                //tHMR.mBSplineMeshes( 1 )->save_to_vtk("BSpline.vtk");

                tDatabase->update_bspline_meshes();
                tDatabase->update_lagrange_meshes();
                // calculate T-Matrices etc
                tDatabase->finalize();

//------------------------------------------------------------------------------
//  Fields
//------------------------------------------------------------------------------

                // create pointer to input field
                auto tField = tHMR.create_field( "LevelSet", tOrder, tOrder );

                // evaluate function
                tField->evaluate_scalar_function( LevelSetFunction );

                // create pointer to output mesh
                auto tOutputMesh = tHMR.create_mesh( tOrder );

                // calculate exact value
                auto tExact = tOutputMesh->create_field( "Exact", tOrder );

                tExact->evaluate_scalar_function( LevelSetFunction );


                // map input to output
                tHMR.map_field_to_output( tField  );

//------------------------------------------------------------------------------
//   Test error
//------------------------------------------------------------------------------

                // determine coefficient of determination
                moris::real tR2 = moris::r2( tExact->get_node_values(),
                                             tField->get_node_values() );

                std::cout << "R2 " << tR2 << std::endl;

                // perform test
                if( tOrder == 1 )
                {
                     REQUIRE( tR2 > 0.97 );
                }
                else
                {
                    REQUIRE( tR2 > 0.99 );
                }

            } // end order loop
        } // end dimension loop
    } // end parallel
}
