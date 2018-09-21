/*
 * cl_Pdof_Host_Test.cpp
 *
 *  Created on: Jul 14, 2018
 *      Author: schmidt
 */
#ifdef MORIS_HAVE_PARALLEL
 #include "Epetra_MpiComm.h"
 #include <mpi.h>
#endif

#include "catch.hpp"
#include "fn_equal_to.hpp"
#include "typedefs.hpp"
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_Communication_Tools.hpp"

#define protected public
#define private   public
#include "cl_MSI_Equation_Object.hpp"
#include "cl_MSI_Node_Obj.hpp"
#include "cl_MSI_Model_Solver_Interface.hpp"
#include "cl_MSI_Dof_Manager.hpp"
#include "cl_MSI_Pdof_Host.hpp"
#include "cl_MSI_Adof.hpp"
#undef protected
#undef private

namespace moris
{
    namespace MSI
    {
    TEST_CASE("Pdof_host_set_dof_type","[MSI],[Pdof_host_set_dof_type]")
    {
        // Create node obj
        moris::uint tNodeId = 4;

        // Create generic adofs to this nodes pdof
        Matrix< IdMat > tAdofsListId( 2, 1 );

        tAdofsListId( 0, 0 ) = 0;
        tAdofsListId( 1, 0 ) = 1;

        // Create generic adofs to this nodes pdof
        Matrix< IdMat > tAdofsListInd( 2, 1 );

        tAdofsListInd( 0, 0 ) = 0;
        tAdofsListInd( 1, 0 ) = 1;

        // Create generic T-matrices
        Matrix< DDRMat > tMatrix( 2, 1 );

        // Create generic T-matrices
        tMatrix( 0, 0 ) = 1.0;
        tMatrix( 1, 0 ) = -2.0;

        // Create generic adof owning processor
        Matrix< IdMat > tAdofOwningProcessor( 2, 1 );

        tAdofOwningProcessor( 0, 0 ) = 0;
        tAdofOwningProcessor( 1, 0 ) = 0;

        // Create generic Node Object
        fem::Node_Base * tNode;
        tNode = new Node_Obj( tNodeId, tAdofsListId, tAdofsListInd, tMatrix, tAdofOwningProcessor );

        // Create Pdof Host
        Pdof_Host tPdofHost( 1, tNode );

        //Check noodeId of the created pdof host
        CHECK( equal_to( tPdofHost.mNodeID, 4 ) );

        // Create pdof type enum and time step moris Mat
        enum Dof_Type tDofType = Dof_Type::TEMP;
        Matrix< DDUMat >  tTimeSteps(1, 1, 0);
        moris::uint tNumMaxPdofTypes = 1;

        Matrix< DDSMat >tDofTypeIndexMap( 4, 1, -1);
        tDofTypeIndexMap(3, 0) = 0;

        //  Set pdof type and timestep
        tPdofHost.set_pdof_type( tDofType, tTimeSteps, tNumMaxPdofTypes, tDofTypeIndexMap );

        // Check size of type and time list
        CHECK( equal_to( tPdofHost.mListOfPdofTimePerType.size(), 1 ) );
        CHECK( equal_to( tPdofHost.mListOfPdofTimePerType( 0 ).size(), 1 ) );

        // check time step indx of this pdof
        CHECK( equal_to( (tPdofHost.mListOfPdofTimePerType( 0 )( 0 ))->mTimeStepIndex, 0 ) );

        delete tNode;
    }

    TEST_CASE("Pdof_Host_Get_Adofs","[MSI],[Pdof_host_get_adofs]")
    {
        // Create node obj
        moris::uint tNodeId = 4;

        // Create generic adofs to this nodes pdof
        Matrix< IdMat > tAdofsListId( 2, 1 );

        tAdofsListId( 0, 0 ) = 0;
        tAdofsListId( 1, 0 ) = 2;

        // Create generic adofs to this nodes pdof
        Matrix< IdMat > tAdofsListInd( 2, 1 );

        tAdofsListInd( 0, 0 ) = 0;
        tAdofsListInd( 1, 0 ) = 2;

        // Create generic T-matrices
        Matrix< DDRMat > tMatrix( 2, 1 );

        // Create generic T-matrices
        tMatrix( 0, 0 ) = 1.0;
        tMatrix( 1, 0 ) = -2.0;

        // Create generic adof owning processor
        Matrix< IdMat > tAdofOwningProcessor( 2, 1 );

        tAdofOwningProcessor( 0, 0 ) = 0;
        tAdofOwningProcessor( 1, 0 ) = 0;

        // Create generic Node Object
        fem::Node_Base * tNode;
        tNode = new Node_Obj( tNodeId, tAdofsListId, tAdofsListInd, tMatrix, tAdofOwningProcessor );

        // Create Pdof Host
        Pdof_Host tPdofHost( 1, tNode );

        //Check noodeId of the created pdof host
        CHECK( equal_to( tPdofHost.mNodeID, 4 ) );

        // Create pdof type enum and time step moris Mat
        enum Dof_Type tDofType = Dof_Type::TEMP;
        Matrix< DDUMat >  tTimeSteps(1, 1, 0);
        moris::uint tNumMaxPdofTypes = 1;

        Matrix< DDSMat >tDofTypeIndexMap(4, 1, -1);
        tDofTypeIndexMap(3, 0) = 0;

        // Set pdof type and timestep
        tPdofHost.set_pdof_type( tDofType, tTimeSteps, tNumMaxPdofTypes, tDofTypeIndexMap );

        // Create external adof list
        moris::Cell< moris::Cell < Adof * > > tAdofList;
        tAdofList.resize( 1 );
        tAdofList( 0 ).resize( 5 );

        Matrix< DDUMat > tTimeLevelOffsets( 1, 1, 0);

        tPdofHost.get_adofs( tTimeLevelOffsets, tAdofList, true );

        // Check if adofs are set to right spot
        REQUIRE( tAdofList( 0 )( 0 ) != NULL );
        REQUIRE( tAdofList( 0 )( 2 ) != NULL );
        REQUIRE( tAdofList( 0 )( 1 ) == NULL );

        delete tNode;
    }

    TEST_CASE("Pdof_Host_Build_Map","[MSI],[Pdof_host_build_map]")
    {
        // Create Pdof Host
        Pdof_Host tPdofHost;

        // Hadcode values into the mUniqueAdofList for test purposes
        tPdofHost.mUniqueAdofList.set_size( 6, 1 );
        tPdofHost.mUniqueAdofList( 0, 0 ) = 1;
        tPdofHost.mUniqueAdofList( 1, 0 ) = 5;
        tPdofHost.mUniqueAdofList( 2, 0 ) = 10;
        tPdofHost.mUniqueAdofList( 3, 0 ) = 15;
        tPdofHost.mUniqueAdofList( 4, 0 ) = 16;
        tPdofHost.mUniqueAdofList( 5, 0 ) = 19;

        // Create map for adofs
        tPdofHost.set_unique_adof_map();

        // Check if map works
        CHECK( equal_to( tPdofHost.mUniqueAdofMap[ 1 ],  0 ) );
        CHECK( equal_to( tPdofHost.mUniqueAdofMap[ 5 ],  1 ) );
        CHECK( equal_to( tPdofHost.mUniqueAdofMap[ 10 ], 2 ) );
        CHECK( equal_to( tPdofHost.mUniqueAdofMap[ 15 ], 3 ) );
        CHECK( equal_to( tPdofHost.mUniqueAdofMap[ 16 ], 4 ) );
        CHECK( equal_to( tPdofHost.mUniqueAdofMap[ 19 ], 5 ) );
    }
    }
}

