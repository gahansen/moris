/*
 * cl_Map_Epetra.cpp
 *
 *  Created on: Mar 19, 2018
 *      Author: schmidt
 */
#include "catch.hpp"
#include "fn_equal_to.hpp" // ALG/src
#include "typedefs.hpp" // COR/src
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_Communication_Tools.hpp" // COM/src/

#include "cl_Map_Epetra.hpp" // DLA/src/
#include "cl_Matrix_Vector_Factory.hpp" // DLA/src/

#include "cl_Map_PETSc.hpp" // DLA/src/

namespace moris
{
TEST_CASE("Epetra Map","[Solver Map],[DistLinAlg]")
{
    // Determine process rank
    size_t rank = par_rank();
    size_t size = par_size();

    if (size == 4)
    {
    // Set input integer and pointer
    uint tNumMyDofs = 0;
    Matrix< DDSMat > tMyGlobalElements;
    Matrix< DDUMat > tMyConstraintDofs;

    // Define input test values
    switch( rank )
        {
        case 0:
          tNumMyDofs = 8;
          tMyGlobalElements.resize( tNumMyDofs, 1 );
          tMyConstraintDofs.resize( 2, 1 );
          tMyGlobalElements(0,0) = 0;    tMyGlobalElements(1,0) = 1;  tMyGlobalElements(2,0) = 8;    tMyGlobalElements(3,0) = 9;    tMyGlobalElements(4,0) = 16;    tMyGlobalElements(5,0) = 17;    tMyGlobalElements(6,0) = 14;    tMyGlobalElements(7,0) = 15;
          tMyConstraintDofs(0,0) = 0;    tMyConstraintDofs(1,0) = 1;
          break;
        case 1:
          tNumMyDofs = 4;
          tMyGlobalElements.resize( tNumMyDofs, 1 );
          tMyConstraintDofs.resize( 1, 1 );
          tMyGlobalElements(0,0) = 2;   tMyGlobalElements(1,0) = 3;    tMyGlobalElements(2,0) = 10;    tMyGlobalElements(3,0) = 11;
          tMyConstraintDofs(0,0) = 3;
          break;
        case 2:
          tNumMyDofs = 2;
          tMyGlobalElements.resize( tNumMyDofs, 1 );
          tMyGlobalElements(0,0) = 4;    tMyGlobalElements(1,0) = 5;
          break;
        case 3:
          tNumMyDofs = 4;
          tMyGlobalElements.resize( tNumMyDofs, 1 );
          tMyGlobalElements(0,0) = 12;    tMyGlobalElements(1,0) = 13;    tMyGlobalElements(2,0) = 6;    tMyGlobalElements(3,0) = 7;
          break;
        }

    // Build factory for map
    Matrix_Vector_Factory      tMatFactory;

    // Build map
    Dist_Map * tMap = tMatFactory.create_map( tMyGlobalElements,
                                               tMyConstraintDofs );

    //std::cout<<*tEpetraMap.get_epetra_free_map()<<std::endl;

    // Set number of global map indices
    sint tNumInd =4;

    // Set the tNumInd global map indices
    Matrix< DDSMat > tGIndList (tNumInd, 1);
    tGIndList(0,0) = 0;    tGIndList(1,0) = 5;    tGIndList(2,0) = 12;    tGIndList(3,0) = 16;

    // Create output arrays for process and local indices
    Matrix< DDSMat > tPIndList (tNumInd, 1);
    Matrix< DDSMat > tLIndList (tNumInd, 1);
    // Get tNumInd process and local indices
    sint err = tMap->get_epetra_map()->RemoteIDList( tNumInd, tGIndList.data(), tPIndList.data(), tLIndList.data() );
    // Compare to true values.
    if (rank == 0)
    {
        CHECK(equal_to(tPIndList(0,0),-1));
        CHECK(equal_to(tLIndList(0,0),-1));
        CHECK(equal_to(tPIndList(2,0), 3));
        CHECK(equal_to(tLIndList(2,0), 0));
        CHECK(equal_to(tPIndList(3,0), 0));
        CHECK(equal_to(tLIndList(3,0), 2));
    }
    delete( tMap );
    }
}

//------------------------------------------------------------------------------------------------------
/*
TEST_CASE("PETSc Map","[Petsc Map],[DistLinAlg]")
{
    // Determine process rank
    size_t rank = par_rank();
    size_t size = par_size();

    if (size == 4)
    {
    // Set input integer and pointer
    uint tNumMyDofs = 0;                                // local dimension of the problem
    Matrix< DDSMat > tMyGlobalElements;
    Matrix< DDUMat > tMyConstraintDofs;

    // Define input test values
    switch( rank )
        {
        case 0:
          tNumMyDofs = 8;
          tMyGlobalElements.resize( tNumMyDofs, 1 );
          tMyConstraintDofs.resize( 2, 1 );
          tMyGlobalElements(0,0) = 0;    tMyGlobalElements(1,0) = 1;  tMyGlobalElements(2,0) = 8;    tMyGlobalElements(3,0) = 9;    tMyGlobalElements(4,0) = 16;    tMyGlobalElements(5,0) = 17;    tMyGlobalElements(6,0) = 14;    tMyGlobalElements(7,0) = 15;
          tMyConstraintDofs(0,0) = 0;    tMyConstraintDofs(1,0) = 1;
          break;
        case 1:
          tNumMyDofs = 4;
          tMyGlobalElements.resize( tNumMyDofs, 1 );
          tMyConstraintDofs.resize( 1, 1 );
          tMyGlobalElements(0,0) = 2;   tMyGlobalElements(1,0) = 3;    tMyGlobalElements(2,0) = 10;    tMyGlobalElements(3,0) = 11;
          tMyConstraintDofs(0,0) = 3;
          break;
        case 2:
          tNumMyDofs = 2;
          tMyGlobalElements.resize( tNumMyDofs, 1 );
          tMyGlobalElements(0,0) = 4;    tMyGlobalElements(1,0) = 5;
          break;
        case 3:
          tNumMyDofs = 4;
          tMyGlobalElements.resize( tNumMyDofs, 1 );
          tMyGlobalElements(0,0) = 12;    tMyGlobalElements(1,0) = 13;    tMyGlobalElements(2,0) = 6;    tMyGlobalElements(3,0) = 7;
          break;
        }

    moris::Mat<int> tTest (3, 1);
    tTest (0, 0) = 1;    tTest (1, 0) = 2;    tTest (2, 0) = 15;

    PetscInitializeNoArguments();

    // Build factory for map
    Matrix_Vector_Factory      tMatFactory;

    // Build map
    Dist_Map * tMap = tMatFactory.create_map( tNumMyDofs,
                                               tMyGlobalElements,
                                               tMyConstraintDofs );

    //Map_PETSc        tPetscMap(tNumMyDofs, tMyGlobalElements, tMyConstraintDofs);

    AOApplicationToPetsc(tMap->get_petsc_map(), 3, mem_pointer( tTest ));
    //AOView(tPetscMap.get_petsc_map(), PETSC_VIEWER_STDOUT_(PETSC_COMM_WORLD));

    // FIXME fix MPI problem with PetscFinalize
    PetscFinalize();

    if (rank == 0)
    {
        CHECK(equal_to(tTest(0,0), 1));
        CHECK(equal_to(tTest(1,0), 8));
        CHECK(equal_to(tTest(2,0), 7));
    }
    //CHECK_THROWS(tMat(3,3));
    }
}*/

}

