/*
 * cl_Linear_Solver_Trilinos.cpp
 *
 *  Created on: Mar 20, 2018
 *      Author: schmidt
 */

#ifdef MORIS_HAVE_PARALLEL
     #include "Epetra_MpiComm.h"
     #include <mpi.h>
#else
    #include "Epetra_SerialComm.h"
#endif

#include "catch.hpp"

#include "fn_equal_to.hpp" // ALG/src

#include "typedefs.hpp" // COR/src

#include "cl_Mat.hpp" // LNA/src

#include "Epetra_FECrsMatrix.h"
#include "Epetra_RowMatrix.h"
#include "Epetra_FECrsGraph.h"
#include "Epetra_BlockMap.h"
#include "Epetra_Map.h"
#include "Epetra_FEVector.h"
#include "Epetra_IntVector.h"

#include "cl_Communication_Manager.hpp" // COM/src/
#include "cl_Communication_Tools.hpp" // COM/src/
#include "cl_Linear_Solver_Trilinos.hpp" // DLA/src/
#include "cl_Linear_Solver_Aztec.hpp" // DLA/src/

#include "cl_Matrix_Vector_Factory.hpp" // DLA/src/
#include "cl_Solver_Input_Test.hpp" // DLA/src/
#include "cl_Solver_Factory.hpp" // DLA/src/


extern moris::Comm_Manager gMorisComm;
namespace moris
{
TEST_CASE("Linear Solver Trilinos","[Linear Solver],[DistLinAlg]")
{
    // Determine process rank and size
    size_t rank = par_rank();
    size_t size = par_size();

    if (size == 4)
    {
//    // Row, col and values for sparse matrix
//    uint    row[109]={8,   8,  8,  8,  8,  8,  9,   9,  9,  9, 9,  9,  9, 16,  16, 16,  16, 16, 16, 16, 16, 17,  17, 17, 17, 17,  17, 17, 17, 14, 14,  14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15,
//                     2,   2,  2,  2,  2,  2, 10,  10, 10, 10,10, 10, 10, 11,  11, 11,  11, 11, 11, 11, 11,  4,   4,  4,  4,  4,   4,  4,  5,  5,  5,   5,  5,  5,  5, 12, 12, 12, 12, 12, 12, 12, 12, 12,
//                    13, 13, 13, 13, 13, 13, 13,  13,  6,  6, 6,  6,  6,  6,   6,  7,   7,  7,  7,  7,  7,  7};
//    uint    col[109]={8,  14, 15,  2, 10, 11,  9,  17, 14, 15, 2, 10, 11, 16,  14,  2,  10,  4,  5,  6,  7,  9,  17,  2,  4,  5,  13,  6,  7,  8,  9,  16, 14, 12, 13,  7,  8,  9, 15, 12, 13,  6,  7,
//                     2,  11,  8,  9, 16, 17, 10,   8,  9, 16, 5, 12, 13,  2,  11,  8,   9,  4,  5, 12, 13,   4,  5, 16, 17, 11,  12, 13,  4,  5, 16,  17, 10, 11, 12, 12,  6,  7, 14, 15, 10, 11,  4, 5,
//                    13,  6, 14, 15, 17, 10, 11,   4, 12, 13, 6,  7, 15, 16,  17, 12,   6,  7, 14, 15, 16,  17};
//    real val[109]={24, -6,  3, -6, -6, -3, 24, -12,  3, -6, 3, -3, -6, 48, -12, -6, -12, -6, -3, -6,  3, -12, 48,  3, -3, -6, -12,  3, -6, -6,  3, -12, 24, -6, -3,  3,  3, -6, 24, -3, -6, -3, -6,
//                     12, -3, -6,  3, -6,  3, 24,  -6, -3,-12,-3, -6,  3, -3,  24, -3,  -6,  3, -6,  3, -6,  12,  3, -6, -3,  3,  -6, -3,  3, 12, -3,  -6, -3, -6,  3,24,  -6, -3, -6, -3, -6,  3, -6, 3,
//                     24,  3, -3, -6,-12,  3, -6,  -3, -6,  3,12, -3, -3, -6,   3, -3,  -3, 12,  3, -6,  3,  -6};

    // Build Input Class
    Solver_Input* tSolverInput = new Solver_Input_Test( );

    // create solver factory
    Solver_Factory  tSolFactory;

    // create solver object
    std::shared_ptr< Linear_Solver > tLin = tSolFactory.create_solver( tSolverInput, SolverType::TRILINOSTEST );

    // call solve
    tLin->solve_linear_system();

    // Set solution vector
    moris::Mat< moris::real > tSol;
    tLin->get_solution( tSol );

    // Check if solution corresponds to given solution
    if (rank == 0)
    {
        CHECK(equal_to(tSol(0,0),-0.0138889,1.0e+08));
        CHECK(equal_to(tSol(5,0),-0.00694444,1.0e+08));
    }
    if (rank == 3)
    {
        CHECK(equal_to(tSol(3,0),-0.0138889,1.0e+08));
    }

    //delete tEpetraComm;
    delete ( tSolverInput );
    }
}

//TEST_CASE("Reader Trilinos","[Reader Solver],[DistLinAlg]")
//{
//    // Determine process rank and size
//    size_t rank = par_rank();
//    size_t size = par_size();
//
//    if (size == 4)
//    {
//    // Build Input Class
//    Solver_Input* tSolverInput = new Solver_Input_Test( );
//
//    // Set flag to use matrix market
//    tSolverInput->use_matrix_market_files();
//
//    // create solver factory
//    Solver_Factory  tSolFactory;
//
//    // create solver object
//    std::shared_ptr< Linear_Solver > tLinSys = tSolFactory.create_solver( tSolverInput );
//
//    //tLinSys->set_param("max_its")   = 200;
//    //tLinSys->set_param("solver_type")   = AZ_cg;
//
//    // call solve
//    tLinSys->solve_linear_system();
//
//    // Set solution vector
//    moris::Mat< moris::real > tSol ( 15, 1, 0.0 );
//    tLinSys->get_solution( tSol );
//
//    // Check if solution corresponds to given solution
//    if ( rank == 0 )
//    {
//        CHECK( equal_to( tSol(0,0),-0.0138889,1.0e+08 ) );
//        CHECK( equal_to( tSol(5,0),-0.00694444,1.0e+08 ) );
//    }
//    if (rank == 3)
//    {
//        CHECK( equal_to( tSol(3,0),-0.0138889,1.0e+08 ) );
//    }
//
//    //delete tEpetraComm;
//    delete ( tSolverInput );
//    }
//}
/*
TEST_CASE("Linear Solver Aztec","[Linear_Solver_Aztec],[DistLG]")//
{
    // Determine process rank and size
    size_t rank = par_rank();
    //size_t size = par_size();

    // Solve liner System with cl_Linear_Solver_Trilinos
    Linear_Solver_Trilinos     tLin;

    std::cout<<"--------"<<std::endl;
    tLin.solve_linear_system();
    std::cout<<"--------"<<std::endl;

    // Set solution vector
    moris::Mat< moris::real > tSol (15, 1, 0.0);
    tLin.get_solution(tSol);

    // Check if solution corresponds to given solution
    if (rank == 0)
    {
        CHECK(equal_to(tSol(0,0),-0.0138889,1.0e+08));
        CHECK(equal_to(tSol(5,0),-0.00694444,1.0e+08));
    }
//    if (rank == 3)
//    {
//        CHECK(equal_to(tSol(3,0),-0.0138889,1.0e+08));
//    }

}*/
}

