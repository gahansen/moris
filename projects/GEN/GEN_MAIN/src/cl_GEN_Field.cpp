#include "cl_GEN_Field.hpp"

namespace moris
{
    namespace ge
    {

        //--------------------------------------------------------------------------------------------------------------

        Field::Field(Matrix<DDRMat>& aADVs,
                     Matrix<DDUMat> aFieldVariableIndices,
                     Matrix<DDUMat> aADVIndices,
                     Matrix<DDRMat> aConstantParameters)
                : mADVIndices(aADVIndices),
                  mConstantParameters(aConstantParameters),
                  mActiveVariables(aFieldVariableIndices.length() + mConstantParameters.length(), true)

        {
            // Check that the number of field variables indices equals the number of ADV indices, resize field variables
            MORIS_ERROR(aFieldVariableIndices.length() == aADVIndices.length(),
                        "ge::Field: Number of field variables indices must equal the number of ADV indices");

            // Resize field variables
            uint tNumInputs = aFieldVariableIndices.length() + mConstantParameters.length();
            mNumActiveVariables = tNumInputs;
            mFieldVariables.resize(tNumInputs);

            // Fill with pointers to ADVs
            for (uint tADVFillIndex = 0; tADVFillIndex < aFieldVariableIndices.length(); tADVFillIndex++)
            {
                mFieldVariables(aFieldVariableIndices(tADVFillIndex)) = &(aADVs(aADVIndices(tADVFillIndex)));
            }

            // Fill with constant parameters and identify these variables
            uint tParameterIndex = 0;
            for (uint tVariableIndex = 0; tVariableIndex < tNumInputs; tVariableIndex++)
            {
                if (mFieldVariables(tVariableIndex) == nullptr)
                {
                    mFieldVariables(tVariableIndex) = &(mConstantParameters(tParameterIndex++));
                    mActiveVariables(tVariableIndex) = false;
                    mNumActiveVariables--;
                }
            }
        }

        //--------------------------------------------------------------------------------------------------------------

        Field::Field(Matrix<DDRMat> aConstantParameters)
                : mConstantParameters(aConstantParameters),
                  mActiveVariables(aConstantParameters.length(), false),
                  mNumActiveVariables(0)
        {
            // Resize field variables
            uint tNumInputs = mConstantParameters.length();
            mFieldVariables.resize(tNumInputs);

            // Fill field variables
            for (uint tVariableIndex = 0; tVariableIndex < tNumInputs; tVariableIndex++)
            {
                mFieldVariables(tVariableIndex) = &(mConstantParameters(tVariableIndex));
            }
        }

        //--------------------------------------------------------------------------------------------------------------

        Field::~Field()
        {

        }

        //--------------------------------------------------------------------------------------------------------------

        Matrix<DDUMat> Field::get_adv_indices()
        {
            return mADVIndices;
        }

        //--------------------------------------------------------------------------------------------------------------

        void Field::evaluate_sensitivity(      uint            aIndex,
                                         const Matrix<DDRMat>& aCoordinates,
                                               Matrix<DDRMat>& aSensitivities)
        {
            // Evaluate all sensitivities
            this->evaluate_all_sensitivities(aIndex, aCoordinates, aSensitivities);

            // Return only what is needed
            uint tVariableIndex = 0;
            for (uint tSensitivityIndex = 0; tSensitivityIndex < mActiveVariables.size(); tSensitivityIndex++)
            {
                if (mActiveVariables(tVariableIndex))
                {
                    aSensitivities(tVariableIndex++) = aSensitivities(tSensitivityIndex);
                }
            }
            aSensitivities.resize(1, mNumActiveVariables);
        }

        //--------------------------------------------------------------------------------------------------------------

        void Field::add_child_node(uint aNodeIndex, std::shared_ptr<Child_Node> aChildNode)
        {
        }

        //--------------------------------------------------------------------------------------------------------------
    }
}

