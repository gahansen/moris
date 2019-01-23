/*
 * cl_NLA_Nonlinear_System_Manager.hpp
 *
 *  Created on: Okt 6, 2018
 *      Author: schmidt
 */
#ifndef MORIS_DISTLINALG_CL_NLA_NONLINEAR_SOLVER_MANAGER_HPP_
#define MORIS_DISTLINALG_CL_NLA_NONLINEAR_SOLVER_MANAGER_HPP_

// MORIS header files.
#ifdef MORIS_HAVE_PARALLEL
 #include <mpi.h>
#endif

#include "typedefs.hpp" // CON/src
#include "cl_Cell.hpp"
#include <memory>
#include "cl_Param_List.hpp"
#include "cl_MSI_Dof_Type_Enums.hpp"

#include "cl_NLA_DofTypeStruc.hpp"

namespace moris
{
namespace NLA
{
    class Nonlinear_Problem;
    class Nonlinear_Solver;
    class Nonlinear_Solver_Manager
    {
    private:
        moris::Cell< moris::Cell< enum MSI::Dof_Type > > mStaggeredDofTypeList;

        moris::Cell< std::shared_ptr< Nonlinear_Solver > > mNonLinearSolverList;

        moris::uint mCallCounter = 0;

        bool mSolveMonolithically = true;

        //! List of structs which contain the level of a staggered solver and the dof types
        moris::Cell< DofTypeStruc* > mListOfDofTypeStrucs;

        //! Lit with matrices containing the tree structure of the staggered solvers.
        moris::Cell< moris::Matrix< DDSMat> > mTreeStrucOfListOfDofTypeStrucs;

        Param_List< boost::variant< bool, sint, real > > mParameterListNonLinearSolver;

    protected:

    public:
        Nonlinear_Solver_Manager();

        ~Nonlinear_Solver_Manager();

        void set_staggered_dof_list( const moris::Cell< moris::Cell< enum MSI::Dof_Type > > aStaggeredDofTypeList,
                                     const moris::sint                                      aLevel =  0)
        {
            DofTypeStruc * tDofTypeStruc = new DofTypeStruc( aStaggeredDofTypeList, aLevel );

            MORIS_ERROR( !( aLevel == 0 && mListOfDofTypeStrucs( 0 ) == nullptr),
                    "Nonlinear_Solver_Manager::set_staggered_dof_list: Second list of dof types provided for level 0. This is not allowed" );

            if( aLevel == 0 )
            {
                mListOfDofTypeStrucs( 0 ) = tDofTypeStruc;
            }
            else
            {
                mListOfDofTypeStrucs.push_back( tDofTypeStruc );

            }
        };

        void set_nonlinear_solver( std::shared_ptr< Nonlinear_Solver > aNonLinSolver );

        void set_nonlinear_solver( const moris::uint                         aListEntry,
                                         std::shared_ptr< Nonlinear_Solver > aLinSolver );

        void set_nonlinear_solver_manager_parameters();

        boost::variant< bool, sint, real > & set_param( char const* aKey )
        {
            return mParameterListNonLinearSolver( aKey );
        }

    };
}
}
#endif /* MORIS_DISTLINALG_CL_NLA_NONLINEAR_SOLVER_MANAGER_HPP_ */

