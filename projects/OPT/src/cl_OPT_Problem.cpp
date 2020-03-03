// Project header files
#include "cl_OPT_Problem.hpp" // OPT/src
#include "op_plus.hpp"
#include "fn_norm.hpp"

extern moris::Logger gLogger;

namespace moris
{
    namespace opt
    {
        Problem::Problem(Interface* aInterface) : mInterface(aInterface)
        {
        }

        // -------------------------------------------------------------------------------------------------------------

        Problem::~Problem()
        {
        }

        // -------------------------------------------------------------------------------------------------------------

        void Problem::initialize()
        {
            // Initialize ADVs
            mADVs = mInterface->initialize_advs(); // get some ADVs from the interface
            this->override_advs(); // user can override the interface ADVs
            mInterface->begin_new_analysis(mADVs); // potentially new ADVs set and passed back to interface to compute criteria

            // Get the criteria at the first step
            mCriteria = mInterface->get_criteria();

            // Initialize bounds and constraints
            mLowerBounds = mInterface->get_lower_adv_bounds();
            mUpperBounds = mInterface->get_upper_adv_bounds();
            mConstraintTypes = this->get_constraint_types();
            MORIS_ERROR(this->check_constraint_order(), "The constraints are not ordered properly (Eq, Ineq)"); //TODO move call to alg
        }

        // -------------------------------------------------------------------------------------------------------------

        uint Problem::get_num_equality_constraints()
        {
            uint tNumEqualityConstraints = 0;

            // Loop over the constraint types matrix
            for (uint tConstraintIndex = 0; tConstraintIndex < mConstraintTypes.numel(); tConstraintIndex++)
            {
                if (mConstraintTypes(tConstraintIndex) == 0)
                {
                    tNumEqualityConstraints++;
                }
            }

            return tNumEqualityConstraints;
        }

        // -------------------------------------------------------------------------------------------------------------

        void Problem::set_advs(Matrix<DDRMat> aNewADVs)
        {
            if (norm(aNewADVs - mADVs) < 1e-12)
            {
                return;
            }

            mADVs = aNewADVs;
            mInterface->begin_new_analysis(aNewADVs);
            mCriteria = mInterface->get_criteria();
        }

        // -------------------------------------------------------------------------------------------------------------

        Matrix<DDRMat> Problem::get_objective_gradient()
        {
            if (mUpdateObjectiveGradient)
            {
                this->compute_objective_gradient();
                mUpdateObjectiveGradient = false;
            }

            return mObjectiveGradient;
        }

        // -------------------------------------------------------------------------------------------------------------

        Matrix<DDRMat> Problem::get_constraint_gradient()
        {
            if (mUpdateConstraintGradient)
            {
                this->compute_constraint_gradient();
                mUpdateConstraintGradient = false;
            }

            return mConstraintGradient;
        }

        // -------------------------------------------------------------------------------------------------------------

        void Problem::scale_solution()
        {
            // TODO Need to decide on a framework for the scaling of the solution
        }

        // -------------------------------------------------------------------------------------------------------------

        void Problem::update_problem()
        {
            // TODO Need to decide on a framework for the update of the problem
        }

        // -------------------------------------------------------------------------------------------------------------

        void Problem::compute_objective_gradient()
        {
            if (mFiniteDifferenceObjectives) // finite difference
            {
                // Set perturbed ADVs and objectives
                Matrix<DDRMat> tOriginalADVs = mADVs;
                mObjectiveGradient.set_size(1, this->get_num_advs());
                real tObjectivePlus;
                real tObjectiveMinus;

                // FD each ADV
                for (uint tADVIndex = 0; tADVIndex < this->get_num_advs(); tADVIndex++)
                {
                    // Perturb forwards
                    mADVs(tADVIndex) += mEpsilon;
                    mInterface->begin_new_analysis(mADVs);
                    tObjectivePlus = this->get_objectives()(0);

                    // Perturb backwards
                    mADVs(tADVIndex) -= 2 * mEpsilon;
                    mInterface->begin_new_analysis(mADVs);
                    tObjectiveMinus = this->get_objectives()(0);

                    // Central difference
                    mObjectiveGradient(0, tADVIndex) = (tObjectivePlus - tObjectiveMinus) / (2 * mEpsilon);
                }
                mADVs = tOriginalADVs;
            }
            else // analytical
            {
                mObjectiveGradient = this->get_dobjective_dadv()
                                     + this->get_dobjective_dcriteria() * mInterface->get_dcriteria_dadv();
            }

        }

        // -------------------------------------------------------------------------------------------------------------

        void Problem::compute_constraint_gradient()
        {
            if (mFiniteDifferenceConstraints) // finite difference
            {
                // Set perturbed ADVs and objectives
                Matrix<DDRMat> tOriginalADVs = mADVs;
                mConstraintGradient.set_size(this->get_num_constraints(), this->get_num_advs());
                Matrix<DDRMat> tConstraintsPlus;
                Matrix<DDRMat> tConstraintsMinus;

                // FD each ADV
                for (uint tADVIndex = 0; tADVIndex < this->get_num_advs(); tADVIndex++)
                {
                    // Perturb forwards
                    mADVs(tADVIndex) += mEpsilon;
                    mInterface->begin_new_analysis(mADVs);
                    tConstraintsPlus = this->get_constraints();

                    // Perturb backwards
                    mADVs(tADVIndex) -= 2 * mEpsilon;
                    mInterface->begin_new_analysis(mADVs);
                    tConstraintsMinus = this->get_constraints();

                    // Central difference
                    mConstraintGradient.set_column(tADVIndex, (tConstraintsPlus - tConstraintsMinus) / (2 * mEpsilon));
                }
                mADVs = tOriginalADVs;
            }
            else // analytical
            {
                mConstraintGradient = this->get_dconstraint_dadv()
                                      + this->get_dconstraint_dcriteria() * mInterface->get_dcriteria_dadv();
            }
        }

        // -------------------------------------------------------------------------------------------------------------

        bool Problem::check_constraint_order()
        {
            // Checks that the constraint order is  1. equality constraints   (typ=0)
            //                                      2. inequality constraints (typ=1)

            int tSwitches = 1;
            for (uint tConstraintIndex = 0; tConstraintIndex < mConstraintTypes.numel(); tConstraintIndex++)
            {
                if (mConstraintTypes(tConstraintIndex) == tSwitches)
                {
                    tSwitches -= 1;
                }
            }
            return (tSwitches >= 0);
        }
    }
}
