#ifndef MORIS_DISTLINALG_CL_NLA_NONLINEAR_PROBLEM_HPP_
#define MORIS_DISTLINALG_CL_NLA_NONLINEAR_PROBLEM_HPP_

// MORIS header files.
#ifdef MORIS_HAVE_PARALLEL
 #include <mpi.h>
#endif

#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"

#include "cl_NLA_Nonlinear_Solver_Enums.hpp"
#include "cl_DLA_Linear_Problem.hpp"

#include "cl_Param_List.hpp"

namespace moris
{
class Map_Class;
class Dist_Vector;
class Solver_Interface;
namespace dla
{
    class Linear_Problem;
}
namespace NLA
{
    class Nonlinear_Problem
    {
    private:

    protected:
        Dist_Vector * mVectorFullSol = nullptr;
        Dist_Vector * mPrevVectorFullSol = nullptr;
        Dist_Vector * mFullVector = nullptr;

        Map_Class   * mMap = nullptr;

        dla::Linear_Problem * mLinearProblem = nullptr;

        bool mHasSolverInterface = false;

        bool mBuildLinerSystemFlag = true;
        enum MapType mMapType = MapType::Epetra;

        moris::sint mNonlinearSolverManagerIndex = -1;

    public:
        Nonlinear_Problem( const enum MapType aMapType = MapType::Epetra )
        {
            mMapType = aMapType;
        };

        Nonlinear_Problem(       Solver_Interface * aSolverInterface,
                           const moris::sint        aNonlinearSolverManagerIndex = 0,
                           const bool               aBuildLinerSystemFlag = true,
                           const enum MapType       aMapType = MapType::Epetra);

        Nonlinear_Problem(       Solver_Interface * aSolverInterface,
                                 Dist_Vector      * aFullVector,
                           const moris::sint        aNonlinearSolverManagerIndex = 0,
                           const bool               aBuildLinerSystemFlag = true,
                           const enum MapType       aMapType = MapType::Epetra);

        ~Nonlinear_Problem();

        void set_interface( Solver_Interface * aSolverInterface );

        void build_linearized_problem( const bool & aRebuildJacobian, sint aNonLinearIt );

        void build_linearized_problem( const bool & aRebuildJacobian, const sint aNonLinearIt, const sint aRestart );

        void print_sol_vec( const sint aNonLinearIt );

        void restart_from_sol_vec( const sint aNonLinearIt );

        dla::Linear_Problem * get_linearized_problem(){ return mLinearProblem; };

        Dist_Vector * get_full_sol_vector();

        Dist_Vector * get_full_vector();

        void extract_my_values( const moris::uint             & aNumIndices,
                                const moris::Matrix< DDSMat > & aGlobalBlockRows,
                                const moris::uint             & aBlockRowOffsets,
                                      moris::Matrix< DDRMat > & LHSValues );
    private:

        void
        delete_pointers();

    };
}
}
#endif /* MORIS_DISTLINALG_CL_NLA_NONLINEAR_PROBLEM_HPP_ */