/*
 * main.cpp
 *
 *  Created on: Sep 30, 2018
 *      Author: messe
 */

// MORIS header files.


#include "cl_Stopwatch.hpp"
#include "cl_Communication_Manager.hpp" // COM/src
#include "cl_Communication_Tools.hpp" // COM/src
#include "typedefs.hpp" // COR/src

#include "cl_Cell.hpp"


#include "banner.hpp" // COR/src

#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "fn_save_matrix_to_binary_file.hpp"

#include "cl_Mesh_Factory.hpp"

#include "SDF_Tools.hpp"

#include "cl_SDF_State.hpp"
#include "cl_SDF_Arguments.hpp"
#include "cl_SDF_Parameters.hpp"
#include "cl_SDF_Mesh.hpp"
#include "cl_SDF_Object.hpp"
#include "cl_SDF_Data.hpp"
#include "cl_SDF_Core.hpp"
#include "cl_SDF_STK.hpp"
#include "cl_SDF_Field.hpp"
moris::Comm_Manager gMorisComm;

using namespace moris;
using namespace sdf;

//------------------------------------------------------------------------------

//void
//save_exodus_mesh( const std::string & aMeshPath,
//------------------------------------------------------------------------------

void
perform_calculation(
        const Arguments   & aArguments,
        const bool aCalculateSDF )
{

    // step 1: load parameters
    ParameterList tGlobalParameters;
    moris::Cell< ParameterList > tObjectParameters;

    // load XML file
    load_sdf_parameter_list_from_xml(
            aArguments.get_parameter_path(),
            tGlobalParameters,
            tObjectParameters );

    // get verbose flag
    bool tVerbose = tGlobalParameters.get< sint >("verbose") == 1;

    // step 2: create mesh objects
    mtk::Mesh * tMtkMesh = mtk::create_mesh(
            MeshType::STK,
            aArguments.get_input_mesh_path(),
            nullptr);

    sdf::Mesh tMesh( tMtkMesh, tVerbose );

    // step 3: create output data


    uint tNumberOfObjects = tObjectParameters.size();

    // get number of nodes on mesh
    uint tNumberOfNodes    = tMesh.get_num_nodes();
    //uint tNumberOfElements = tMesh.get_num_elems();

    // create empty matrix
    Matrix< DDRMat > tEmpty( tNumberOfNodes, 1 );

    // create array for output data
    uint tNumberOfFields = 0;

    if( ! aCalculateSDF )
    {
        tNumberOfFields = tNumberOfObjects;
    }
    else
    {
        tNumberOfFields = 2*tNumberOfObjects;
    }

    moris::Cell< Matrix< DDRMat > > tFieldValues( tNumberOfFields, tEmpty );
    moris::Cell< std::string > tFieldLabels( tNumberOfFields, "" );

    // step 4: perform raycast

    // loop over all objects
    for( uint k=0; k<tNumberOfObjects; ++k )
    {
        // create SDF object
        sdf::Object tObject( tObjectParameters( k ).get< std::string >("stl_file") );

        // create data object
        sdf::Data tData( tObject );

        // create core and set verbosity flag
        sdf::Core tCore( tMesh, tData, tVerbose );

        // set parameters of core
        tCore.set_candidate_search_depth( tObjectParameters( k ).get< sint >("candidate_search_depth") );
        tCore.set_candidate_search_epsilon( tObjectParameters( k ).get< real >("candidate_search_epsilon") );

        // set label of output field
        tFieldLabels( k ) =  tObjectParameters( k ).get< std::string >("label");

        if( ! aCalculateSDF )
        {
            // perform raycast
            tCore.calculate_raycast();

            // create output matrix
            Matrix< DDRMat > tNodeIsInside( tNumberOfNodes, 1 );

            // loop over all nodes and write -1 if node is inside
            for( uint i=0; i<tNumberOfNodes; ++i )
            {
                if( tMesh.get_vertex( i )->is_inside() )
                {
                    tFieldValues( k )( i ) = -1.0;
                }
                else
                {
                    tFieldValues( k )( i ) = 1.0;
                }
            }
        }
        else
        {
            // perform raycast and sdf
            tCore.calculate_raycast_and_sdf( tFieldValues( k ) );

            // create flag if SDF exists
            uint j = tNumberOfObjects + k;
            for( uint i=0; i<tNumberOfNodes; ++i )
            {
                if( tMesh.get_vertex( i )->has_sdf() )
                {
                    tFieldValues( j )( i ) = 1.0;
                }
                else
                {
                    tFieldValues( j )( i ) = 0.0;
                }
            }

            // set label of sdf field
            tFieldLabels( j ) =  tFieldLabels( k ) + "_has_sdf";
        }


        // get path for output data and make it parallel
        std::string tBinaryPath = tObjectParameters( k ).get< std::string >( "output_values" );

        if( tBinaryPath.size() > 0 )
        {
            // save matrix to binary file
            save_matrix_to_binary_file( tFieldValues( k ), parallelize_path ( tBinaryPath ) );
        }

        // get HDF path
        std::string tHdf5Path = tObjectParameters( k ).get< std::string >( "output_hdf5" );

        if( tHdf5Path.size() > 0 )
        {
            // create field object
            Field tField( tFieldLabels( k ), tMesh, tFieldValues( k ) );

            // save field
            tField.save_field_to_hdf5( tHdf5Path );
        }
    }

    // create output mesh
    std::string tOutputPath = aArguments.get_output_mesh_path();


    if( tOutputPath.size() > 0 )
    {
        sdf::STK tSTK( tMesh );
        tSTK.create_mesh_data( tFieldValues, tFieldLabels, aArguments.get_timestep() );

        tSTK.save_to_file( tOutputPath );
    }

    // tidy up memory
    delete tMtkMesh;
}

//------------------------------------------------------------------------------
int
main(
        int    argc,
        char * argv[] )
{
    // initialize MORIS global communication manager
    gMorisComm = moris::Comm_Manager( &argc, &argv );

//------------------------------------------------------------------------------

    // create arguments object
    Arguments tArguments( argc, argv );

//------------------------------------------------------------------------------

    switch ( tArguments.get_state() )
    {
        case( State::PRINT_USAGE ) :
        {
            // print system usage
            tArguments.print_usage();
            break;
        }
        case( State::PRINT_VERSION ) :
        {
            // print welcome banner and system information
            moris::print_banner( argc, argv );
            break;
        }
        case( State::PRINT_HELP ) :
        {
            // print help line and exit
            tArguments.print_help();
            break;
        }
        case( State::CALCULATE_RAYCAST ) :
        {
            // perform raycast
            perform_calculation( tArguments, false );
            break;
        }
        case( State::CALCULATE_RAYCAST_AND_SDF ) :
        {
            // perform raycast and calculate sdf
            perform_calculation( tArguments, true );
            break;
        }
        default:
        {
            // print system usage
            tArguments.print_usage();
            break;
        }
    }

    // finalize MORIS global communication manager
    gMorisComm.finalize();

    return 0;

}