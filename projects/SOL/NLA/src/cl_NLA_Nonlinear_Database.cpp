#include "cl_NLA_Nonlinear_Solver_Manager.hpp"
#include "cl_DLA_Solver_Interface.hpp"

#include "cl_Communication_Tools.hpp"
#include "cl_NLA_Nonlinear_Database.hpp"

#include "cl_Vector.hpp"
#include "cl_Map_Class.hpp"

using namespace moris;
using namespace NLA;

void Nonlinear_Database::create_solver_manager_dependencies()
{
    // Set size of nonlinear solver manager list to number of nonlinear solver managers
    mListSolverManagerDepenencies.resize( mListNonlinerSolverManagers.size() );

    // Loop over all nonlinear solver manager
    for ( uint Ik = 0 ; Ik < mListNonlinerSolverManagers.size(); Ik++ )
    {
        // Get the list of list of dof types in which this particular nonlinear solver manager is operating on
        moris::Cell< moris::Cell< enum MSI::Dof_Type > > tNonlinerSolverManagerDofTypeList = mListNonlinerSolverManagers( Ik )->get_dof_type_list();

        // Set the size of the dependency list for this nonlinear solver manager == number sub-solvers
        mListSolverManagerDepenencies( Ik ).set_size( tNonlinerSolverManagerDofTypeList.size(), 1, -1 );

        // Loop over all sub system dof type lists
        for ( uint Ii = 0 ; Ii < tNonlinerSolverManagerDofTypeList.size(); Ii++ )
        {
            // Loop over all nonlinear solver managers
            for ( uint Ij = 0 ; Ij < mListNonlinerSolverManagers.size(); Ij++ )
            {
                // Check that the to be compared nonlinear solver manager indices are not equal
                if( Ij != Ik )
                {
                    // Get dof type union of the downward nonlinear solver manager
                    moris::Cell< enum MSI::Dof_Type > tUnionDofTypeList = mListNonlinerSolverManagers( Ij )->get_dof_type_union();

                    // Check if the subsystem doftype list and the downward solver union list are the same
                    if( tNonlinerSolverManagerDofTypeList( Ii ).data() == tUnionDofTypeList.data() )
                    {
                        // Check that a possible downward solver is only found once
                        MORIS_ERROR( mListSolverManagerDepenencies( Ik )( Ii, 0 ) == -1,
                                "Nonlinear_Database::create_solver_manager_dependencies(): Two solvers are operating on the same dof types" );

                        // Add downward solver nonlinear solver manager index to list
                        mListSolverManagerDepenencies( Ik )( Ii, 0 ) = Ij;
                    }
                }
            }
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------

moris::sint Nonlinear_Database::get_nonlinear_solver_manager_index( const moris::sint aSolverManagerIndex,
                                                                    const moris::sint aDofTypeListIndex )
{
    // check if index was set.
    MORIS_ERROR( mListSolverManagerDepenencies( aSolverManagerIndex )( aDofTypeListIndex, 0 ) != -1,
            "Nonlinear_Database::get_nonliner_solver_manager_index(): Return nonlinear solver manager -1. Check create_solver_manager_dependencies()" );

    return mListSolverManagerDepenencies( aSolverManagerIndex )( aDofTypeListIndex , 0 );
}

//---------------------------------------------------------------------------------------------------------------------

void Nonlinear_Database::create_maps()
{
    // Create matrix vector factory
    Matrix_Vector_Factory tMatFactory( MapType::Epetra );

    // Get number nonliner solver managers
    moris::uint tNumberNonlinSolverManager = mListNonlinerSolverManagers.size();

    // Set size of list of maps
    mListOfFreeMaps.resize( tNumberNonlinSolverManager + 1, nullptr );

    // create full map pointer on last entry on map list
    mListOfFreeMaps( tNumberNonlinSolverManager ) = tMatFactory.create_map( mSolverInterface->get_my_local_global_overlapping_map() );

    // Loop over all nonlinear solver managers
    for ( uint Ik = 0 ; Ik < tNumberNonlinSolverManager; Ik++ )
    {
        // Get dof type union of the downward nonlinear solver manager
        moris::Cell< enum MSI::Dof_Type > tUnionDofTypeList = mListNonlinerSolverManagers( Ik )->get_dof_type_union();

        // FIXME Set dof type on solver inerface
        mSolverInterface->set_requested_dof_types( tUnionDofTypeList );

        // Create free map for this dof type list
        mListOfFreeMaps( Ik ) = tMatFactory.create_map( mSolverInterface->get_my_local_global_map() );
    }
}

//---------------------------------------------------------------------------------------------------------------------

Map_Class * Nonlinear_Database::get_list_of_maps( const moris::sint aSolverManagerIndex )
{
    // return map for this nonlinear solver manager index
    return mListOfFreeMaps( aSolverManagerIndex );
}

//---------------------------------------------------------------------------------------------------------------------

void Nonlinear_Database::finalize()
{
    // Call to calculate nonliner solver manager dependencies
    this->create_solver_manager_dependencies();

    // Call to build all maps
    this->create_maps();

    // Build matrix vector factory
    Matrix_Vector_Factory    tMatFactory( MapType::Epetra );

    // Create Full Vector
    mFullVector = tMatFactory.create_vector( mSolverInterface, mListOfFreeMaps( mListNonlinerSolverManagers.size()), VectorType::FREE );

    // Initilaze full vector with zeros
    mFullVector->vec_put_scalar( 0.0 );

    mListNonlinerSolverManagers( 0 )->finalize();

    // Loop over all nonliner solver managers and set pointer to the database
    for ( uint Ik = 0; Ik < mListNonlinerSolverManagers.size(); Ik++ )
    {
        mListNonlinerSolverManagers( Ik )->set_nonlinear_manager( this );
    }
}

//---------------------------------------------------------------------------------------------------------------------

void Nonlinear_Database::set_nonliner_solver_managers( Nonlinear_Solver_Manager * aNonlinerSolverManager )
{
    if( mCallCounter == 0 )
    {
        mListNonlinerSolverManagers.clear();

        mListNonlinerSolverManagers.push_back( aNonlinerSolverManager );

        mListNonlinerSolverManagers( mCallCounter )->set_sonlinear_solver_manager_index( mCallCounter );
    }
    else
    {
        mListNonlinerSolverManagers.push_back( aNonlinerSolverManager );

        mListNonlinerSolverManagers( mCallCounter )->set_sonlinear_solver_manager_index( mCallCounter );
    }

    mCallCounter = mCallCounter + 1;
}

//---------------------------------------------------------------------------------------------------------------------

void Nonlinear_Database::solve()
{
    this->finalize();

    mListNonlinerSolverManagers( 0 )->solve( );
}

//---------------------------------------------------------------------------------------------------------------------

