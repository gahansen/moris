/*
 * cl_NLA_Nonlinear_System_Manager.hpp
 *
 *  Created on: Okt 6, 2018
 *      Author: schmidt
 */
#ifndef MORIS_DISTLINALG_CL_NLA_NONLINEAR_MANAGER_HPP_
#define MORIS_DISTLINALG_CL_NLA_NONLINEAR_MANAGER_HPP_

// MORIS header files.
#ifdef MORIS_HAVE_PARALLEL
#include <mpi.h>
#endif

#include "typedefs.hpp" // CON/src
#include "cl_Cell.hpp"
#include <memory>
#include "cl_Param_List.hpp"
#include "cl_MSI_Dof_Type_Enums.hpp"

#include "cl_NLA_NonlinearDatabase.hpp"
#include "cl_NLA_Nonlinear_Solver_Manager.hpp"

namespace moris
{
namespace NLA
{
    class Nonlinear_Problem;
    class Nonlinear_Solver;
    class Nonlinear_Manager
    {
    private:
        moris::uint mCallCounter = 0;

        bool mSolveMonolithically = true;

        NonLinDatabase * mNonlinearDatabase;

        moris::Cell< Nonlinear_Solver_Manager * > mListNonlinerSolverManagers;

        Solver_Interface * mSolverInput;

    protected:

    public:
        Nonlinear_Manager( Solver_Interface * aSolverInput ) : mSolverInput( aSolverInput )
        {};

        ~Nonlinear_Manager()
        {};

        void set_nonliner_solver_managers( Nonlinear_Solver_Manager * aNonlinerSolverManager )
        {
            mListNonlinerSolverManagers.push_back( aNonlinerSolverManager );
        };

        void solve()
        {
            this->finalize();

            mListNonlinerSolverManagers( 0 )->solve( );
        };

        void finalize()
        {
            mListNonlinerSolverManagers( 0 )->finalize();

            for ( uint Ik = 0; Ik < mListNonlinerSolverManagers.size(); Ik++ )
            {
                mListNonlinerSolverManagers( Ik )->set_nonlinear_manager( this );
            }
        };

        Solver_Interface * get_solver_interface()
        {
            return mSolverInput;
        };

        moris::Cell< Nonlinear_Solver_Manager * > & get_nonliner_solver_manager_list()
        {
            return mListNonlinerSolverManagers;
        };

    };
}
}
#endif /* MORIS_DISTLINALG_CL_NLA_NONLINEAR_MANAGER_HPP_ */

