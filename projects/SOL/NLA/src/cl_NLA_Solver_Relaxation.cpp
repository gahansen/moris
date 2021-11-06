/*
 * cl_NLA_Solver_Relaxation.cpp
 */

#include "cl_NLA_Solver_Relaxation.hpp"

#include "typedefs.hpp"

#include "cl_Logger.hpp"
#include "cl_Tracer.hpp"

namespace moris
{
    namespace NLA
    {
        //--------------------------------------------------------------------------------------------------------------------------

        Solver_Relaxation::Solver_Relaxation( ParameterList & aParameterListNonlinearSolver)
        {
            // get relaxation strategy
            mRelaxationStratey = static_cast < sol::SolverRelaxationType > (
                    aParameterListNonlinearSolver.get< uint >( "NLA_relaxation_strategy" ) );

            // get initial relaxation parameter
            mRelaxation = aParameterListNonlinearSolver.get< real >( "NLA_relaxation_parameter" );

            // get damping factor
            mBetaDamping = aParameterListNonlinearSolver.get< real >( "NLA_relaxation_damping" );
        }

        //--------------------------------------------------------------------------------------------------------------------------

        bool Solver_Relaxation::eval(
                const real & aRefNorm,
                const real & aResNorm,
                real       & aRelaxValue)
        {
            // set flag for computation of search direction
            bool tComputeSearchDirection = true;

            // compute relaxation value depending on strategy
            switch ( mRelaxationStratey )
            {
                // constant relaxation parameter
                case sol::SolverRelaxationType::Constant:
                {
                    aRelaxValue = mRelaxation;

                    // log relaxation value
                    MORIS_LOG_INFO("Relaxation (Constant): %7.5e", aRelaxValue );

                    break;
                }
                // residual dependent relaxation parameter
                // see Boris Polyak & Andrey Tremba (2019) DOI: 10.1080/10556788.2019.1669154, Algorithm 1, Page 10
                case sol::SolverRelaxationType::InvResNorm:
                {
                    // update beta(k); different from paper
                    if ( mResk > 0.0 )
                    {
                        mBetak = mRelaxation * mResk;
                    }
                    else
                    {
                        mBetak = mRelaxation * aRefNorm;
                    }

                    // store current residual
                    mResk = aResNorm + MORIS_REAL_EPS;

                    // compute relaxation parameter
                    aRelaxValue = std::min( 1.0, mBetak / mResk );

                    // log relaxation value
                    MORIS_LOG_INFO("Relaxation (InvResNorm): %7.5e", aRelaxValue );

                    break;
                }
                // residual dependent relaxation parameter with adaptation
                //  see Boris Polyak & Andrey Tremba (2019) DOI: 10.1080/10556788.2019.1669154, Algorithm 2, Page 15
                case sol::SolverRelaxationType::InvResNormAdaptive:
                {
                    // initialize beta(k)
                    if ( mBetak < 0.0 )
                    {
                        mBetak = mRelaxation * aRefNorm;
                    }

                    // perform check and apply damping to relaxation parameter if necessary
                    if ( mAlphak > 0 )
                    {
                        // check that internal parameters are initialized
                        MORIS_ASSERT( mResk > 0.0 && mBetak > 0.0,
                                "Solver_Relaxation::eval - internal parameters have not been initialized.\n");

                        // check whether step is acceptable
                        bool tCheck1 = mAlphak <  1 && aResNorm < mResk - mBetak/2.0;
                        bool tCheck2 = mAlphak >= 1 && aResNorm < mResk*mResk/2.0/mBetak;

                        // if both checks fail step is not acceptable and beta(k) is reduced
                        if ( !tCheck1 && !tCheck2 )
                        {
                            // count number of trials along current step size
                            mNumTrials++;

                            // apply damping to beta until effective
                            while ( mBetak > mResk / mBetaDamping )
                            {
                                mBetak *= mBetaDamping;
                            }

                            // apply damping
                            mBetak *= mBetaDamping;

                            // suppress computing new search direction
                            tComputeSearchDirection = false;
                        }
                    }

                    // if step is acceptable compute relaxation parameter based on current residual norm
                    // and store internal parameters
                    if ( tComputeSearchDirection  )
                    {
//                        // set beta(k) to previous residual once it has been set
//                        if ( mResk > 0 )
//                        {
//                            mBetak= mRelaxation * mResk;
//                        }

                       // increase beta(k) if last step was accept on first attempt
                       if ( mNumTrials == 0 )
                       {
                           mBetak*=2.0;
                       }

                       // store current residual
                        mResk = aResNorm + MORIS_REAL_EPS;

                        // re-initialize relaxation history
                        mRelaxHist = 0.0;

                        // log that step has been accepted
                        MORIS_LOG_INFO("Relaxation (InvResNormAdaptive): step has been accepted after %d trials", mNumTrials );

                        // reset number of trials
                        mNumTrials=0;
                    }

                    // compute and store effective relaxation parameter
                    mAlphak = std::min( 1.0, mBetak / mResk );

                     // adjust relaxation value considering previous incremental updates
                    aRelaxValue= mAlphak - mRelaxHist;

                    // update incremental update history
                    mRelaxHist += aRelaxValue;

                    // log relaxation value
                    MORIS_LOG_INFO("Relaxation (InvResNormAdaptive): %7.5e (incremental relaxation: %7.5e) - mResk = %7.5e   mBetak = %7.5e",
                            mAlphak, aRelaxValue,mResk,mBetak );

                    break;
                }
                default:
                {
                    MORIS_ERROR(false,"Solver_Relaxation::eval - relaxation strategy not implemented.\n");
                }
            }

            return tComputeSearchDirection;
        }
    }
}