#ifndef MORIS_DISTLINALG_CL_NLA_NONLinearSolver_HPP_
#define MORIS_DISTLINALG_CL_NLA_NONLinearSolver_HPP_

// MORIS header files.
#ifdef MORIS_HAVE_PARALLEL
 #include <mpi.h>
#endif

#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"

#include "cl_NLA_Nonlinear_Solver_Enums.hpp"
#include "cl_NLA_Nonlinear_Problem.hpp"
#include "cl_DLA_Linear_Solver_Manager.hpp"

#include "cl_Param_List.hpp"

namespace moris
{
class Map_Class;
class Dist_Vector;
class Solver_Interface;
namespace dla
{
    class Linear_Solver;
}
namespace NLA
{
    class Nonlinear_Solver_Manager;
    class Nonlinear_Solver
    {
    private:

    protected:

        dla::Linear_Solver_Manager * mLinSolverManager = nullptr;

        Nonlinear_Problem * mNonlinearProblem = nullptr;

        Param_List< boost::variant< bool, sint, real, const char* > > mParameterListNonlinearSolver;

        friend class Convergence;

        Nonlinear_Solver_Manager * mMyNonLinSolverManager = nullptr;

        /**
         * @brief Set the parameters in the nonlinear solver parameter list
         *
         */
        void set_nonlinear_solver_parameters();

        /**
         * @brief Member function which keeps track of used time for a particular purpose.
         *
         */
        moris::real calculate_time_needed( const clock_t aTime );

    public:
        Nonlinear_Solver(){};

        //Nonlinear_Solver( Solver_Interface * aSolverInterface );

        virtual ~Nonlinear_Solver(){};

        void set_nonlinear_problem( Nonlinear_Problem * aNonlinearProblem );

        void set_linear_solvers( dla::Linear_Solver_Manager * aLinSolverManager );

        void set_linear_solver( const moris::uint aListEntry,
                                      std::shared_ptr< dla::Linear_Solver > aLinearSolver );

        virtual void solver_nonlinear_system() = 0;

        virtual void solver_nonlinear_system( Nonlinear_Problem * aNonlinearProblem ) = 0;
//
//        virtual Dist_Vector * get_full_sol_vec() = 0;
//
        virtual void get_full_solution( moris::Matrix< DDRMat > & LHSValues ) = 0;
//
//        virtual void get_solution( moris::Matrix< DDRMat > & LHSValues ) =0;
//
        virtual void extract_my_values( const moris::uint             & aNumIndices,
                                        const moris::Matrix< DDSMat > & aGlobalBlockRows,
                                        const moris::uint             & aBlockRowOffsets,
                                              moris::Matrix< DDRMat > & LHSValues ) = 0;

        void set_nonlinear_solver_manager( Nonlinear_Solver_Manager* aNonlinSolverManager )
        {
            mMyNonLinSolverManager = aNonlinSolverManager;
        };

        virtual boost::variant< bool, sint, real, const char* > & set_param( char const* aKey ) = 0;


    };
}
}
#endif /* MORIS_DISTLINALG_CL_NLA_NONLinearSolver_HPP_ */