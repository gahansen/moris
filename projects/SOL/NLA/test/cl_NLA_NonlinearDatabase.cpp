/*
 * cl_NLA_NonlinearDatabase.cpp
 *
 *  Created on: Jan 21, 2018
 *      Author: schmidt
 */
#ifdef MORIS_HAVE_PARALLEL
 #include <mpi.h>
#endif

#include "catch.hpp"
#include "fn_equal_to.hpp"
#include "typedefs.hpp"
#include "cl_Matrix.hpp"
#include "fn_reshape.hpp"

#include "linalg_typedefs.hpp"
#include "cl_Communication_Tools.hpp"
#include "cl_Communication_Tools.hpp"

#include "cl_MSI_Dof_Type_Enums.hpp"

#define protected public
#define private   public
#include "cl_NLA_Nonlinear_Solver_Manager.hpp"
#include "cl_NLA_Nonlinear_Database.hpp"
#include "cl_NLA_Solver_Interface_Proxy2.hpp"
#undef protected
#undef private

namespace moris
{
namespace NLA
{
    TEST_CASE("NonlinearDatabase2","[NLA],[NLA_Database2]")
    {
        if ( par_size() == 1 )
        {
        moris::Cell< enum MSI::Dof_Type > tDofTypes1( 2 );
        moris::Cell< enum MSI::Dof_Type > tDofTypes2( 1 );

        tDofTypes1( 0 ) = MSI::Dof_Type::UX;
        tDofTypes1( 1 ) = MSI::Dof_Type::UY;

        tDofTypes2( 0 ) = MSI::Dof_Type::TEMP;

        Nonlinear_Solver_Manager tNonlinearSolverManager;

        tNonlinearSolverManager.set_dof_type_list( tDofTypes1 );
        tNonlinearSolverManager.set_dof_type_list( tDofTypes2 );

        CHECK( equal_to( static_cast< int >( tNonlinearSolverManager.get_dof_type_list()( 0 )( 0 ) ), static_cast< int >( MSI::Dof_Type::UX ) ) );
        CHECK( equal_to( static_cast< int >( tNonlinearSolverManager.get_dof_type_list()( 0 )( 1 ) ), static_cast< int >( MSI::Dof_Type::UY ) ) );
        CHECK( equal_to( static_cast< int >( tNonlinearSolverManager.get_dof_type_list()( 1 )( 0 ) ), static_cast< int >( MSI::Dof_Type::TEMP ) ) );
        }
    }

    TEST_CASE("NonlinearDatabase3","[NLA],[NLA_Database3]")
    {
        if ( par_size() == 1 )
        {
        moris::Cell< enum MSI::Dof_Type > tDofTypes1( 2 );
        moris::Cell< enum MSI::Dof_Type > tDofTypes2( 1 );

        tDofTypes1( 0 ) = MSI::Dof_Type::UX;
        tDofTypes1( 1 ) = MSI::Dof_Type::UY;

        tDofTypes2( 0 ) = MSI::Dof_Type::TEMP;

        Nonlinear_Solver_Manager tNonlinearSolverManager1( NLA::NonlinearSolverType::NLBGS_SOLVER );
        Nonlinear_Solver_Manager tNonlinearSolverManager2( NLA::NonlinearSolverType::NEWTON_SOLVER );
        Nonlinear_Solver_Manager tNonlinearSolverManager3( NLA::NonlinearSolverType::NEWTON_SOLVER );
        tNonlinearSolverManager1.set_dof_type_list( tDofTypes2 );
        tNonlinearSolverManager1.set_dof_type_list( tDofTypes1 );
        tNonlinearSolverManager2.set_dof_type_list( tDofTypes1 );
        tNonlinearSolverManager3.set_dof_type_list( tDofTypes2 );

        CHECK( equal_to( static_cast< int >( tNonlinearSolverManager1.get_dof_type_list()( 1 )( 0 ) ), static_cast< int >( MSI::Dof_Type::UX ) ) );
        CHECK( equal_to( static_cast< int >( tNonlinearSolverManager1.get_dof_type_list()( 1 )( 1 ) ), static_cast< int >( MSI::Dof_Type::UY ) ) );
        CHECK( equal_to( static_cast< int >( tNonlinearSolverManager1.get_dof_type_list()( 0 )( 0 ) ), static_cast< int >( MSI::Dof_Type::TEMP ) ) );

        Solver_Interface * tSolverInput = new NLA_Solver_Interface_Proxy_II();

        Nonlinear_Database tNonlinearDatabase( tSolverInput );

        tNonlinearDatabase.set_nonliner_solver_managers( & tNonlinearSolverManager1 );
        tNonlinearDatabase.set_nonliner_solver_managers( & tNonlinearSolverManager2 );
        tNonlinearDatabase.set_nonliner_solver_managers( & tNonlinearSolverManager3 );

        tNonlinearDatabase.solve();
        }
    }

    TEST_CASE("NonlinearDatabase4","[NLA],[NLA_Database4]")
    {
        if ( par_size() == 1 )
        {
        moris::Cell< enum MSI::Dof_Type > tDofTypes1( 1 );
        moris::Cell< enum MSI::Dof_Type > tDofTypes2( 3 );
        moris::Cell< enum MSI::Dof_Type > tDofTypes3( 2 );
        moris::Cell< enum MSI::Dof_Type > tDofTypes4( 1 );


        tDofTypes1( 0 ) = MSI::Dof_Type::TEMP;

        tDofTypes2( 0 ) = MSI::Dof_Type::UX;
        tDofTypes2( 1 ) = MSI::Dof_Type::UY;
        tDofTypes2( 2 ) = MSI::Dof_Type::UZ;

        tDofTypes3( 0 ) = MSI::Dof_Type::UX;
        tDofTypes3( 1 ) = MSI::Dof_Type::UY;

        tDofTypes4( 0 ) = MSI::Dof_Type::UZ;

        Nonlinear_Solver_Manager tNonlinearSolverManager1( NLA::NonlinearSolverType::NLBGS_SOLVER );
        Nonlinear_Solver_Manager tNonlinearSolverManager2( NLA::NonlinearSolverType::NEWTON_SOLVER );
        Nonlinear_Solver_Manager tNonlinearSolverManager3( NLA::NonlinearSolverType::NLBGS_SOLVER );
        Nonlinear_Solver_Manager tNonlinearSolverManager4( NLA::NonlinearSolverType::NEWTON_SOLVER );
        Nonlinear_Solver_Manager tNonlinearSolverManager5( NLA::NonlinearSolverType::NEWTON_SOLVER );

        tNonlinearSolverManager1.set_dof_type_list( tDofTypes1 );
        tNonlinearSolverManager1.set_dof_type_list( tDofTypes2 );

        tNonlinearSolverManager2.set_dof_type_list( tDofTypes1 );

        tNonlinearSolverManager3.set_dof_type_list( tDofTypes3 );
        tNonlinearSolverManager3.set_dof_type_list( tDofTypes4 );

        tNonlinearSolverManager4.set_dof_type_list( tDofTypes3 );

        tNonlinearSolverManager5.set_dof_type_list( tDofTypes4 );

        Solver_Interface * tSolverInput = new NLA_Solver_Interface_Proxy_II();

        Nonlinear_Database tNonlinearDatabase( tSolverInput );

        tNonlinearDatabase.set_nonliner_solver_managers( & tNonlinearSolverManager1 );
        tNonlinearDatabase.set_nonliner_solver_managers( & tNonlinearSolverManager2 );
        tNonlinearDatabase.set_nonliner_solver_managers( & tNonlinearSolverManager3 );
        tNonlinearDatabase.set_nonliner_solver_managers( & tNonlinearSolverManager4 );
        tNonlinearDatabase.set_nonliner_solver_managers( & tNonlinearSolverManager5 );

        tNonlinearDatabase.create_solver_manager_dependencies();

        CHECK( equal_to( tNonlinearDatabase.get_nonlinear_solver_manager_index( 0, 0 ),  1 ) );
        CHECK( equal_to( tNonlinearDatabase.get_nonlinear_solver_manager_index( 0, 1 ),  2 ) );
        CHECK( equal_to( tNonlinearDatabase.get_nonlinear_solver_manager_index( 2, 0 ),  3 ) );
        CHECK( equal_to( tNonlinearDatabase.get_nonlinear_solver_manager_index( 2, 1 ),  4 ) );
        }
    }

    TEST_CASE("NonlinearDatabase5","[NLA],[NLA_Database5]")
    {
        if ( par_size() == 1 )
        {
        moris::Cell< enum MSI::Dof_Type > tDofTypes1( 2 );
        moris::Cell< enum MSI::Dof_Type > tDofTypes2( 1 );

        tDofTypes1( 0 ) = MSI::Dof_Type::UX;
        tDofTypes1( 1 ) = MSI::Dof_Type::UY;

        tDofTypes2( 0 ) = MSI::Dof_Type::TEMP;

        Nonlinear_Solver_Manager tNonlinearSolverManager1( NLA::NonlinearSolverType::NLBGS_SOLVER );
        Nonlinear_Solver_Manager tNonlinearSolverManager2( NLA::NonlinearSolverType::NEWTON_SOLVER );
        Nonlinear_Solver_Manager tNonlinearSolverManager3( NLA::NonlinearSolverType::NEWTON_SOLVER );
        tNonlinearSolverManager1.set_dof_type_list( tDofTypes2 );
        tNonlinearSolverManager1.set_dof_type_list( tDofTypes1 );
        tNonlinearSolverManager2.set_dof_type_list( tDofTypes1 );
        tNonlinearSolverManager3.set_dof_type_list( tDofTypes2 );

        Solver_Interface * tSolverInput = new NLA_Solver_Interface_Proxy_II();

        Nonlinear_Database tNonlinearDatabase( tSolverInput );

        tNonlinearDatabase.set_nonliner_solver_managers( & tNonlinearSolverManager1 );
        tNonlinearDatabase.set_nonliner_solver_managers( & tNonlinearSolverManager2 );
        tNonlinearDatabase.set_nonliner_solver_managers( & tNonlinearSolverManager3 );

        tNonlinearDatabase.create_maps();

        // Set number of global map indices
        sint tNumInd =4;

        // Set the tNumInd global map indices
        Matrix< DDSMat > tGIndList (tNumInd, 1);
        tGIndList(0,0) = 0;    tGIndList(1,0) = 1;    tGIndList(2,0) = 2;    tGIndList(3,0) = 3;

        // Create output arrays for process and local indices
        Matrix< DDSMat > tPIndList (tNumInd, 1);        Matrix< DDSMat > tLIndList (tNumInd, 1);

        // Get tNumInd process and local indices
        tNonlinearDatabase.get_list_of_maps( 0 )->get_epetra_free_map()->RemoteIDList( tNumInd, tGIndList.data(), tPIndList.data(), tLIndList.data() );

        // Compare to true values.
        CHECK( equal_to( tLIndList( 0, 0 ), 0 ) );
        CHECK( equal_to( tLIndList( 2, 0 ), 2 ) );
        CHECK( equal_to( tLIndList( 3, 0 ), 3 ) );

        // Set number of global map indices
        tNumInd = 2;

        // Set the tNumInd global map indices
        tGIndList.resize (tNumInd, 1);
        tGIndList(0,0) = 2;    tGIndList(1,0) = 3;

        // Create output arrays for process and local indices
        tPIndList.resize (tNumInd, 1);        tLIndList.resize (tNumInd, 1);

        // Get tNumInd process and local indices
        tNonlinearDatabase.get_list_of_maps( 1 )->get_epetra_free_map()->RemoteIDList( tNumInd, tGIndList.data(), tPIndList.data(), tLIndList.data() );

        // Compare to true values.
        CHECK( equal_to( tLIndList( 0, 0 ), 0 ) );
        CHECK( equal_to( tLIndList( 1, 0 ), 1 ) );

        // Set number of global map indices
        tNumInd =4;

        // Set the tNumInd global map indices
        tGIndList.resize (tNumInd, 1);
        tGIndList(0,0) = 0;    tGIndList(1,0) = 1;    tGIndList(2,0) = 2;    tGIndList(3,0) = 3;

          // Create output arrays for process and local indices
        tPIndList.resize (tNumInd, 1);        tLIndList.resize (tNumInd, 1);

        // Get tNumInd process and local indices
        tNonlinearDatabase.get_list_of_maps( 3 )->get_epetra_free_map()->RemoteIDList( tNumInd, tGIndList.data(), tPIndList.data(), tLIndList.data() );

        // Compare to true values.
        CHECK( equal_to( tLIndList( 0, 0 ), 0 ) );
        CHECK( equal_to( tLIndList( 2, 0 ), 2 ) );
        CHECK( equal_to( tLIndList( 3, 0 ), 3 ) );
        }
    }
}
}
