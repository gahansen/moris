/*
 * cl_DLA_Linear_Solver_Aztec.hpp
 *
 *  Created on: May 14, 2018
 *      Author: schmidt
 */
#ifndef SRC_DISTLINALG_CL_LINEAR_SOLVER_AZTEC_HPP_
#define SRC_DISTLINALG_CL_LINEAR_SOLVER_AZTEC_HPP_

#include "AztecOO.h"

// ML
#include "ml_include.h"
#include "ml_epetra_utils.h"
#include "ml_epetra_preconditioner.h"

#include "cl_DLA_Linear_Solver.hpp"
#include "cl_DLA_Linear_Problem.hpp"

namespace moris
{
namespace dla
{
    class Linear_Solver_Aztec : public Linear_Solver
    {
    private:
        AztecOO                               mAztecSolver;

        Teuchos::ParameterList                mlParams;
        ML_Epetra::MultiLevelPreconditioner * mMlPrec;

    protected:
    public:
        Linear_Solver_Aztec();

        Linear_Solver_Aztec( Linear_Problem * aLinearSystem );

        ~Linear_Solver_Aztec();

        void set_linear_problem( Linear_Problem * aLinearSystem );

        void set_solver_parameters();

        moris::sint solve_linear_system( );

        moris::sint solve_linear_system( Linear_Problem * aLinearSystem, const moris::sint aIter );

        void set_solver_internal_parameters();
    };
}
}

#endif /* SRC_DISTLINALG_CL_LINEAR_SOLVER_AZTEC_HPP_ */