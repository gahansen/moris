#include "cl_Communication_Manager.hpp" // COM/src
#include "cl_Communication_Tools.hpp" // COM/src
#include "typedefs.hpp" // COR/src
#include "banner.hpp" // COR/src
#include "cl_Mat.hpp" // LNA/src


#include "cl_HMR.hpp"
#include "cl_FEM_IWG_L2_Test.hpp"
#include "cl_MDL_Model.hpp"


moris::Comm_Manager gMorisComm;

using namespace moris;

real
distance( const Mat< real > & aPoint )
{
    real tValue = 0;
    uint tNumberOfDimensions = aPoint.length();

    for( uint k=0; k< tNumberOfDimensions; ++k )
    {
        tValue += std::pow( aPoint( k ), 2 );
    }
    return std::sqrt( tValue );
}

int
main(
        int    argc,
        char * argv[] )
{
    // initialize MORIS global communication manager
    gMorisComm = moris::Comm_Manager( &argc, &argv );

    // print welcome banner and system information
    moris::print_banner( argc, argv );

//------------------------------------------------------------------------------
        // In this part, an HMR object is created

        // create settings object
        /* ( this is actually my internal settings object. As far as I understood,
                     the user is supposed to control HMR using a parameter list.
                     This is not implemented yet ) */

        hmr::Parameters tParameters;

        // create a Mat for a 2D object

        Mat< luint > tNumberOfElements = { { 2 }, { 2 }, { 2 } };

        // mesh orders
        Mat< uint >  tLagrangeOrders = { { 2 }, { 2 }, { 2 } };

        // set interpolation degrees
        tParameters.set_lagrange_orders( tLagrangeOrders );

        Mat< uint >  tBSplineOrders = { { 3 }, { 3 } };
        tParameters.set_bspline_orders( tBSplineOrders );

        // set patterns
        //Parameters.set_default_patterns();

        Mat< uint >  tLagrangePatterns = { { 0 }, { 1 }, { 2 } };
        tParameters.set_lagrange_patterns( tLagrangePatterns );

        // @fixme make sure that B-Spline pattern is always coarser
        Mat< uint >  tBSplinePatterns = { { 0 }, { 1 } };
        tParameters.set_bspline_patterns( tBSplinePatterns );

        Mat< uint >  tLinks = { { 0 },  { 1 },  { 1 } }; // link last to 1
        tParameters.set_lagrange_to_bspline( tLinks );


        // pass number of elements to settings
        tParameters.set_number_of_elements_per_dimension( tNumberOfElements );

        // make mesh output silent

        tParameters.set_verbose( true );

        // buffer size must be set at least to max polynomial if truncation is used
        //tParameters.set_buffer_size( tParameters.get_max_polynomial() );

        tParameters.set_buffer_size( 0 );
        tParameters.set_bspline_truncation( true );

        hmr::HMR tHMR( &tParameters );

        tHMR.set_active_pattern( 0 );
        tHMR.flag_element( 0 );
        tHMR.perform_refinement();

        tHMR.set_active_pattern( 1 );

        if ( tNumberOfElements.length() == 2 )
        {
            tHMR.flag_element( 3 );
        }
        else
        {
            tHMR.flag_element( 7 );
        }
        tHMR.perform_refinement();


        tHMR.unite_patterns( 0, 1, 2 );

//------------------------------------------------------------------------------

        tHMR.set_active_pattern( 2 ); // 2
        tHMR.update_meshes();

        auto tField0 = tHMR.create_field( "Field", 0 );

        tField0->evaluate_function( distance );

        // the union
        auto tUnion = tHMR.create_field( "Field",  2 );
        tHMR.activate_all_t_matrices(); // < -- this is a problem and needs fixing

        // interpolate field 1 onto field 2
        tHMR.interpolate_field( tField0, tUnion );

        tHMR.set_active_pattern( 2 ); // 2
        auto tMesh = tHMR.create_interface();


        // create IWG object
        moris::fem::IWG_L2_Test tIWG;


        auto tField1 = tHMR.create_field( "Field", 1 );
        mdl::Model tModel( tMesh, tIWG, tUnion->get_data(), tField1->get_coefficients() );

        tField1->evaluate_node_values();
        tHMR.save_to_exodus( 1, "Mesh.exo" );

//------------------------------------------------------------------------------

    // finalize MORIS global communication manager
    gMorisComm.finalize();

    return 0;

}
