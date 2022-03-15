/*
 * cl_NLA_Solver_Load_Control.cpp
 */

#include "cl_NLA_Solver_Load_Control.hpp"

#include "typedefs.hpp"

#include "cl_Logger.hpp"
#include "cl_Tracer.hpp"

namespace moris
{
    namespace NLA
    {
        //--------------------------------------------------------------------------------------------------------------------------

        Solver_Load_Control::Solver_Load_Control( ParameterList& aParameterListNonlinearSolver )
        {
            // get relaxation strategy
            mLoadControlStrategy = static_cast< sol::SolverLoadControlType >(
                    aParameterListNonlinearSolver.get< uint >( "NLA_laod_control_strategy" ) );

            // get initial relaxation parameter
            mInitialLoadFactor = aParameterListNonlinearSolver.get< real >( "NLA_load_control_factor" );

            // get number of growth steps
            mNumLoadSteps = aParameterListNonlinearSolver.get< sint >( "NLA_load_control_steps" );

            // get required relative residual drop for triggering growth
            mRelativeResidualDropThreshold = aParameterListNonlinearSolver.get< real >( "NLA_load_control_relres" );

            // strategy depending parameters
            switch ( mLoadControlStrategy )
            {
                case sol::SolverLoadControlType::Exponential:
                {
                    mExponent = aParameterListNonlinearSolver.get< real >( "NLA_load_control_exponent" );
                    break;
                }
                case sol::SolverLoadControlType::UserDefined:
                {
                    MORIS_ERROR( false, "Solver_Load_Control::Solver_Load_Control - User Defined Strategy not implemented yet." );
                    break;
                }
                default:
                {
                }
            }

            // initialize load step counter
            mLoadStepCounter = 0;
        }

        //--------------------------------------------------------------------------------------------------------------------------

        real
        Solver_Load_Control::get_initial_load_factor()
        {
            return mInitialLoadFactor;
        }

        //--------------------------------------------------------------------------------------------------------------------------

        void
        Solver_Load_Control::eval(
                const real& aRefNorm,
                const real& aResNorm,
                real&       aLoadFactor )
        {
            // compute relaxation value depending on strategy
            switch ( mLoadControlStrategy )
            {
                // constant relaxation parameter
                case sol::SolverLoadControlType::Constant:
                {
                    aLoadFactor = mInitialLoadFactor;

                    break;
                }
                case sol::SolverLoadControlType::Exponential:
                {
                    // compute relative residual
                    real tRelResNorm = aResNorm / aRefNorm;

                    // update laod factor if requirement on relative residual is satisfied
                    if ( tRelResNorm < mRelativeResidualDropThreshold )
                    {
                        mLoadStepCounter++;
                        aLoadFactor = mInitialLoadFactor
                                    + ( 1.0 - mInitialLoadFactor ) * std::min( 1.0, std::pow( ( (real)mLoadStepCounter ) / mNumLoadSteps, mExponent ) );

                        // log load factor
                        MORIS_LOG_INFO( "Updated load factor (Exponential): %7.5e in load step %d", aLoadFactor, mLoadStepCounter );
                    }

                    break;
                }
                case sol::SolverLoadControlType::UserDefined:
                {
                    MORIS_ERROR( false, "Solver_Load_Control::Solver_Load_Control - User Defined Strategy not implemented yet." );
                    break;
                }
                default:
                {
                    MORIS_ERROR( false, "Solver_Load_Control::eval - strategy not implemented.\n" );
                }
            }
        }
    }    // namespace NLA
}    // namespace moris