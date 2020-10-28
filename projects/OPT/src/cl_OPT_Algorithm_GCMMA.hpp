#ifndef MORIS_CL_OPT_ALGORITHM_GCMMA_HPP_
#define MORIS_CL_OPT_ALGORITHM_GCMMA_HPP_

#include "core.hpp"
#include "cl_OPT_Algorithm.hpp"
#include "cl_Param_List.hpp"
#include "cl_OPT_Problem.hpp"

class OptAlgGCMMA : public moris::opt::Algorithm
{

private:
    bool mRunning = true;
    bool mPrint;
    moris::uint mResFlag = 0; // flag from GCMMA describing result of optimization algorithm
    moris::sint mMaxIterations; // maximum number of iterations
    moris::sint mMaxInnerIterations; // maximum inner iterations per every optimization iteration
    moris::real mNormDrop; // relative change in objective convergence criteria
    moris::real mAsympAdapt0; // initial asymptote adaptation factor
    moris::real mAsympShrink; // shrinking asymptote adaptation factor
    moris::real mAsympExpand; // expanding asymptote adaptation factor
    moris::real mStepSize; // GCMMA step size
    moris::real mPenalty; // GCMMA constraint penalty

    /**
     * @brief External function call for computing objective and constraints, to
     *        interface with gcmma library
     */
    friend void opt_alg_gcmma_func_wrap(
            OptAlgGCMMA* aOptAlgGCMMA,
            int          aIter,
            double*      aAdv,
            double&      aObjval,
            double*      aConval );

    /**
     * @brief External function call for computing sensitivities, to interface
     *        with gcmma library
     */
    friend void opt_alg_gcmma_grad_wrap(
            OptAlgGCMMA* aOptAlgGCMMA,
            double*      aAdv,
            double*      aD_Obj,
            double**     aD_Con,
            int*         aActive );

public:

    /**
     * Constructor
     */
    OptAlgGCMMA(moris::ParameterList aParameterList);

    /**
     * Destructor
     */
    ~OptAlgGCMMA();

    /**
     * @brief MORIS interface for solving of optimization problem using
     *        GCMMA
     *
     * @param[in] aOptProb Object of type Problem containing relevant
     *            data regarding ADVs, the objective and constraints
     */
    void solve( std::shared_ptr<moris::opt::Problem> aOptProb );

    /**
     * Communicates proc 0's running status to other procs so they know when to end.
     */
    void communicate_running_status();

    /**
     *@brief Prints result of the GCMMA algorithm based on mStopFlag
     */
    void printresult( );
};

#endif /* MORIS_CL_OPT_ALGORITHM_GCMMA_HPP_ */
