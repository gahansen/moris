//
// example specific interface to moris
//

#include <catch.hpp>

#include "cl_Logger.hpp"                // MRS/IOS/src
#include "cl_MTK_Exodus_IO_Helper.hpp"  // MTK/src
#include "cl_Communication_Tools.hpp"   // MRS/COM/src

#include "cl_Matrix.hpp"
#include "fn_norm.hpp"

#include "HDF5_Tools.hpp"

using namespace moris;

//---------------------------------------------------------------

// global variable for interpolation order
uint gInterpolationOrder;

// flag to print reference values
bool gPrintReferenceValues = false;

//---------------------------------------------------------------

int fn_WRK_Workflow_Main_Interface( int argc, char * argv[] );

//---------------------------------------------------------------

TEST_CASE("Two_Bar_Truss",
        "[moris],[example],[structure],[linear],[optimization],[sweep]")
{
    // define command line call
    int argc = 2;

    char tString1[] = "";
    char tString2[] = "./Two_Bar_Truss.so";

    char * argv[2] = {tString1,tString2};

    // set interpolation order
    gInterpolationOrder = 1;

    MORIS_LOG_INFO("");
    MORIS_LOG_INFO("Two_Bar_Truss: Interpolation order %i - %i Processors.",gInterpolationOrder,par_size());
    MORIS_LOG_INFO("");

    // call to performance manager main interface
    fn_WRK_Workflow_Main_Interface( argc, argv );

    // Sweep HDF5 file
    hid_t tFileID = open_hdf5_file( "TwoBarTruss.hdf5" );
    herr_t tStatus = 0;

    // Declare sensitivity matrices for comparison
    Matrix<DDRMat> tObjectiveAnalytical;
    Matrix<DDRMat> tConstraintsAnalytical;
    Matrix<DDRMat> tObjectiveFD;
    Matrix<DDRMat> tConstraintsFD;

    // Read analytical sensitivities
    load_matrix_from_hdf5_file( tFileID, "objective_gradients eval_1-1 analytical", tObjectiveAnalytical, tStatus);
    load_matrix_from_hdf5_file( tFileID, "constraint_gradients eval_1-1 analytical", tConstraintsAnalytical, tStatus);
    REQUIRE(tObjectiveAnalytical.length() == tConstraintsAnalytical.length()); // one objective and one constraint for this problem only

    // Read FD sensitivities and compare
    Cell<std::string> tFDTypes = {"fd_forward", "fd_backward", "fd_central"};

    MORIS_LOG_INFO("------------------------------------------------------");

    for (uint tADVIndex = 0; tADVIndex < tObjectiveAnalytical.length(); tADVIndex++)
    {
        for (uint tFDIndex = 0; tFDIndex < tFDTypes.size(); tFDIndex++)
        {
            load_matrix_from_hdf5_file( tFileID, "objective_gradients eval_1-1 epsilon_1-1 " + tFDTypes(tFDIndex), tObjectiveFD, tStatus);
            load_matrix_from_hdf5_file( tFileID, "constraint_gradients eval_1-1 epsilon_1-1 " + tFDTypes(tFDIndex), tConstraintsFD, tStatus);

            REQUIRE(tObjectiveAnalytical.length()   == tObjectiveFD.length());
            REQUIRE(tConstraintsAnalytical.length() == tConstraintsFD.length());

            MORIS_LOG_INFO("Check derivative of objective  wrt. ADV(%i):  analytical  %12.5e, finite difference (%s) %12.5e, percent error %12.5e.",
                    tADVIndex,
                    tObjectiveAnalytical(tADVIndex),
                    tFDTypes(tFDIndex).c_str(),
                    tObjectiveFD(tADVIndex),
                    100*std::abs((tObjectiveAnalytical(tADVIndex)-tObjectiveFD(tADVIndex))/tObjectiveFD(tADVIndex)));

            MORIS_LOG_INFO("Check derivative of constraint wrt. ADV(%i):  analytical  %12.5e, finite difference (%s) %12.5e, percent error %12.5e.",
                    tADVIndex,
                    tConstraintsAnalytical(tADVIndex),
                    tFDTypes(tFDIndex).c_str(),
                    tConstraintsAnalytical(tADVIndex),
                    100*std::abs((tConstraintsAnalytical(tADVIndex)-tConstraintsAnalytical(tADVIndex))/tConstraintsAnalytical(tADVIndex)));

            //CHECK(tObjectiveAnalytical(tADVIndex) == Approx(tObjectiveFD(tADVIndex)));
            //CHECK(tConstraintsAnalytical(tADVIndex) == Approx(tConstraintsFD(tADVIndex)));
        }
        MORIS_LOG_INFO("------------------------------------------------------");
    }

    // close file
    close_hdf5_file( tFileID );
}