/*
 * cl_NLA_Nonlinear_Solver.hpp
 *
 *  Created on: Okt 6, 2018
 *      Author: schmidt
 */
#ifndef MORIS_DISTLINALG_CL_NLA_NONLINEAR_SOLVER_HPP_
#define MORIS_DISTLINALG_CL_NLA_NONLINEAR_SOLVER_HPP_

// MORIS header files.
#include "typedefs.hpp" // CON/src
#include "cl_Cell.hpp"
#include <memory>
#include "cl_Param_List.hpp"
#include "cl_MSI_Dof_Type_Enums.hpp"

#include "cl_NLA_Nonlinear_Solver_Enums.hpp"
#include "cl_NLA_Nonlinear_Solver_Factory.hpp"

namespace moris
{
namespace NLA
{
    class Nonlinear_Problem;
    class Nonlinear_Algorithm;
    class Nonlinear_Database;
    class Nonlinear_Solver
    {
    private:
        //! List of list of dof types
        moris::Cell< moris::Cell< enum MSI::Dof_Type > >  mStaggeredDofTypeList;

        //! List with nonlinear solvers
        moris::Cell< std::shared_ptr< Nonlinear_Algorithm > > mNonLinearSolverList;

        //! Pointer to solver database
        Nonlinear_Database * mNonlinearDatabase;

        //! Pointer to nonlinear problem
        Nonlinear_Problem * mNonlinearProblem = nullptr;

        //! Pointer to solver interface
        Solver_Interface * mSolverInput = nullptr;

        // Nonlinear solver manager index
        moris::sint mNonlinearSolverManagerIndex = -1;

        //! Reference norm
        moris::real mRefNorm = -1.0;

        //! First residual norm of this solve
        moris::real mFirstResidualNorm = -1.0;

        //! Actual residual norm
        moris::real mResidualNorm = -1.0;

        Param_List< boost::variant< bool, sint, real > > mParameterListNonLinearSolver;

        enum NonlinearSolverType mNonLinSolverType = NonlinearSolverType::END_ENUM;

        moris::uint mCallCounter = 0;

        moris::sint mLevel = 0;

    protected:

    public:
        /**
         * @brief Constructor. Creates a default nonlinear solver
         *
         * @param[in] aNonLinSolverType Nonlinear solver type. Default is Newton
         */
        Nonlinear_Solver( const enum NonlinearSolverType aNonLinSolverType = NonlinearSolverType::NEWTON_SOLVER );

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Constructor. Sets given List of nonlinear solvers to this nonlinear solver manager
         *
         * @param[in] aNonlinerSolverList List of nonlinear solvers.
         * @param[in] aNonLinSolverType Nonlinear solver type. Default is Newton
         */
        Nonlinear_Solver(       moris::Cell< std::shared_ptr<Nonlinear_Algorithm > > & aNonlinerSolverList,
                                  const enum NonlinearSolverType                            aNonLinSolverType = NonlinearSolverType::NEWTON_SOLVER );

        //--------------------------------------------------------------------------------------------------

        ~Nonlinear_Solver();

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Sets one of the lists this nonlinear solver manager is operating on. Should be called multiple times for black solvers
         *
         * @param[in] aStaggeredDofTypeList List of dof types.
         * @param[in] aLevel                Solver level in the block structure. Default is 0
         */
        void set_dof_type_list( const moris::Cell< enum MSI::Dof_Type > aStaggeredDofTypeList,
                                const moris::sint                       aLevel =  0);

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Set nonlinear solver. Uses push back to add the given nonlinear solver to the list.
         *
         * @param[in] aNonLinSolver Pointer to nonlinear solver.
         */
        void set_nonlinear_solver( std::shared_ptr< Nonlinear_Algorithm > aNonLinSolver );

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Set nonlinear solver on position in list
         *
         * @param[in] aNonLinSolver Pointer to nonlinear solver.
         * @param[in] aListEntry Pointer to nonlinear solver.
         */
        void set_nonlinear_solver(       std::shared_ptr< Nonlinear_Algorithm > aLinSolver,
                                   const moris::uint                         aListEntry );

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Get function for list of list of dof types
         *
         * @param[out] rListOfListsOfDofTypes Returns the nonlinear solver managers list of list of dof types
         */
        moris::Cell< moris::Cell< enum MSI::Dof_Type > > & get_dof_type_list()    { return mStaggeredDofTypeList; };

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Get the union of this nonlinear solver managers dof types
         *
         * @param[out] rUnionListOfDofTypes Returns the union list of this nonliner solver managers dof types
         */
        moris::Cell< enum MSI::Dof_Type > get_dof_type_union();

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Sets the index of this nonlinear solver manager
         *
         * @param[in] aNonlinearSolverManagerIndex Nonlinear solver manager index
         */
        void set_sonlinear_solver_manager_index( const moris::sint aNonlinearSolverManagerIndex );

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Get the nonlinear solver manager index
         *
         * @param[out] rNonlinerSolverManagerIndex Returns the nonlinear solver manager index
         */
        moris::sint get_sonlinear_solver_manager_index();

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Retruns pointer to the solver database
         *
         * @param[out] rSolverDatabase Returns the pointer to the solver database
         */
        Nonlinear_Database * get_nonlinear_database(  )    { return mNonlinearDatabase;};

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Set pointer to the solver database
         *
         * @param[in] rSolverDatabase Poiner to the solver database
         */
        void set_nonlinear_manager( Nonlinear_Database * aNonlinearDatabase );

        //--------------------------------------------------------------------------------------------------

        void solve();

        void solve( Nonlinear_Problem * aNonlinearProblem );

        void get_full_solution( moris::Matrix< DDRMat > & LHSValues );

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Returns a reference to the reference norm
         *
         * @param[out] rRefNorm Returns the nonlinear solver manager reference norm
         */
        moris::real & get_ref_norm(){ return mRefNorm; }

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Returns a reference to the actual residual norm
         *
         * @param[out] rResidualNorm Returns the nonlinear solver manager residual norm
         */
        moris::real & get_residual_norm(){ return mResidualNorm; }

        //--------------------------------------------------------------------------------------------------

        /**
         * @brief Returns a reference to the actual first residual norm of this solve
         *
         * @param[out] rNonlinerSolverManagerIndex rResidualNorm Returns the first nonlinear solver manager residual norm
         */
        moris::real & get_first_residual_norm(){ return mFirstResidualNorm; }

        //--------------------------------------------------------------------------------------------------

        void set_nonlinear_solver_manager_parameters();

        //--------------------------------------------------------------------------------------------------

        boost::variant< bool, sint, real > & set_param( char const* aKey )
        {
            return mParameterListNonLinearSolver( aKey );
        }
    };
}
}
#endif /* MORIS_DISTLINALG_CL_NLA_NONLINEAR_SOLVER_HPP_ */

