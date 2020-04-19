/*
 * cl_DLA_Linear_Problem.cpp
 *
 *  Created on: Dec 6, 2017
 *      Author: schmidt
 */
#include "cl_DLA_Linear_Problem.hpp"
#include "cl_SOL_Dist_Vector.hpp"
#include "cl_SOL_Dist_Matrix.hpp"

#include "cl_Stopwatch.hpp" //CHR/src

// detailed logging package
#include "cl_Tracer.hpp"
#include "cl_Tracer_Enums.hpp"

namespace moris
{
namespace dla
{
    Dist_Vector * Linear_Problem::get_full_solver_LHS()
    {
        // zero out full LHS vec
        mFullVectorLHS->vec_put_scalar( 0.0 );

        // Import free LHS to full LHS
        mFullVectorLHS->import_local_to_global( *mFreeVectorLHS );

        return mFullVectorLHS;
    }

//----------------------------------------------------------------------------------------
    void Linear_Problem::set_free_solver_LHS( Dist_Vector * aFullSolVector)
    {
        mFreeVectorLHS->import_local_to_global( *aFullSolVector );
    }

//----------------------------------------------------------------------------------------
    void Linear_Problem::assemble_residual_and_jacobian( Dist_Vector * aFullSolutionVector )
    {
        // zero out RHS
        mVectorRHS->vec_put_scalar( 0.0 );

        // zero out matrix
        mMat->mat_put_scalar( 0.0 );

        //
        mSolverInterface->fill_matrix_and_RHS( mMat, mVectorRHS, aFullSolutionVector );
    }

//----------------------------------------------------------------------------------------
    void Linear_Problem::assemble_residual( Dist_Vector * aFullSolutionVector )
    {
        Tracer tTracer(EntityBase::LinearProblem, EntityType::NoType, EntityAction::AssembleResidual);

        // Zero out RHS
        mVectorRHS->vec_put_scalar( 0.0 );

        // start timer
        tic tTimer;

        // assemble RHS
        mSolverInterface->assemble_RHS( mVectorRHS, aFullSolutionVector );

        real tElapsedTime = tTimer.toc<moris::chronos::milliseconds>().wall;
        MORIS_LOG_INFO( " Assembly of residual on processor %u took %5.3f seconds.", ( uint ) par_rank(), ( double ) tElapsedTime / 1000);

        //mVectorRHS->print();
    }

//----------------------------------------------------------------------------------------
    void Linear_Problem::assemble_jacobian( Dist_Vector * aFullSolutionVector )
    {
        Tracer tTracer(EntityBase::LinearProblem, EntityType::NoType, EntityAction::AssembleJacobian);

        mMat->mat_put_scalar( 0.0 );

        // start timer
        tic tTimer;

        // assemble jacobian
        mSolverInterface->assemble_jacobian( mMat, aFullSolutionVector);

        // stop timer
        real tElapsedTime = tTimer.toc<moris::chronos::milliseconds>().wall;

        MORIS_LOG_INFO( " Assembly of jacobianon processor %u took %5.3f seconds.", ( uint ) par_rank(), ( double ) tElapsedTime / 1000);
    }

//----------------------------------------------------------------------------------------
    void Linear_Problem::assemble_residual_and_jacobian( )
    {
        mVectorRHS->vec_put_scalar( 0.0 );
        mMat->mat_put_scalar( 0.0 );

        mSolverInterface->fill_matrix_and_RHS( mMat, mVectorRHS);
    }

}
}

