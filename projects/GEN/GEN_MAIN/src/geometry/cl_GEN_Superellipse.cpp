#include "cl_GEN_Superellipse.hpp"

namespace moris
{
    namespace ge
    {

        //--------------------------------------------------------------------------------------------------------------

        Superellipse::Superellipse(
                Matrix<DDRMat>& aADVs,
                Matrix<DDUMat>  aGeometryVariableIndices,
                Matrix<DDUMat>  aADVIndices,
                Matrix<DDRMat>  aConstantParameters,
                Matrix<DDSMat>  aNumRefinements,
                Matrix<DDSMat>  aNumPatterns,
                sint            aRefinementFunctionIndex,
                sint            aBSplineMeshIndex,
                real            aBSplineLowerBound,
                real            aBSplineUpperBound)
        : Field(aADVs,
                aGeometryVariableIndices,
                aADVIndices,
                aConstantParameters,
                aNumRefinements,
                aNumPatterns,
                aRefinementFunctionIndex,
                aBSplineMeshIndex,
                aBSplineLowerBound,
                aBSplineUpperBound)
        {
            MORIS_ERROR(aGeometryVariableIndices.length() + aConstantParameters.length() == 8,
                    "A GEN Super-ellipse must be created with a total of exactly 8 variables (ADVs + constant parameters).");

            MORIS_ERROR(*(mFieldVariables(2)) > 0 and *(mFieldVariables(3)) > 0,
                    "A GEN Super-ellipse must be created with positive semi-diameters.");

            MORIS_ERROR(std::abs(std::fmod(*(mFieldVariables(4)),2.0)) < 1e-12,
                    "A GEN Super-ellipse must be created with an even exponent.");
        }

        //--------------------------------------------------------------------------------------------------------------

        Superellipse::Superellipse(
                sol::Dist_Vector* aOwnedADVs,
                Matrix<DDUMat>    aGeometryVariableIndices,
                Matrix<DDUMat>    aADVIndices,
                Matrix<DDRMat>    aConstantParameters,
                Matrix<DDSMat>  aNumRefinements,
                Matrix<DDSMat>  aNumPatterns,
                sint              aRefinementFunctionIndex,
                sint              aBSplineMeshIndex,
                real              aBSplineLowerBound,
                real              aBSplineUpperBound)
                : Field(aOwnedADVs,
                        aGeometryVariableIndices,
                        aADVIndices,
                        aConstantParameters,
                        aNumRefinements,
                        aNumPatterns,
                        aRefinementFunctionIndex,
                        aBSplineMeshIndex,
                        aBSplineLowerBound,
                        aBSplineUpperBound)
        {
            MORIS_ERROR(aGeometryVariableIndices.length() + aConstantParameters.length() == 8,
                        "A GEN Super-ellipse must be created with a total of exactly 8 variables (ADVs + constant parameters).");

            MORIS_ERROR(*(mFieldVariables(2)) > 0 and *(mFieldVariables(3)) > 0,
                        "A GEN Super-ellipse must be created with positive semi-diameters.");

            MORIS_ERROR(std::abs(std::fmod(*(mFieldVariables(4)),2.0)) < 1e-12,
                        "A GEN Super-ellipse must be created with an even exponent.");
        }

        //--------------------------------------------------------------------------------------------------------------

        Superellipse::Superellipse(
                real aXCenter,
                real aYCenter,
                real aXSemidiameter,
                real aYSemidiameter,
                real aExponent,
                real aScaling,
                real aRegularization,
                real aShift,
                Matrix<DDSMat>  aNumRefinements,
                Matrix<DDSMat>  aNumPatterns,
                sint aRefinementFunctionIndex,
                sint aBSplineMeshIndex,
                real aBSplineLowerBound,
                real aBSplineUpperBound)
        : Field(Matrix<DDRMat>({{aXCenter, aYCenter, aXSemidiameter, aYSemidiameter, aExponent, aScaling, aRegularization, aShift}}),
                aNumRefinements,
                aNumPatterns,
                aRefinementFunctionIndex,
                aBSplineMeshIndex,
                aBSplineLowerBound,
                aBSplineUpperBound)
        {
            MORIS_ERROR(*(mFieldVariables(2)) > 0 and *(mFieldVariables(3)) > 0,
                    "A GEN Super-ellipse must be created with positive semi-diameters.");

            MORIS_ERROR(std::abs(std::fmod(*(mFieldVariables(4)),2.0)) < 1e-12,
                    "A GEN Super-ellipse must be created with an even exponent.");
        }

        //--------------------------------------------------------------------------------------------------------------

        real Superellipse::evaluate_field_value(const Matrix<DDRMat>& aCoordinates)
        {
            // Get variables
            real tXCenter        = *(mFieldVariables(0));
            real tYCenter        = *(mFieldVariables(1));
            real tXSemidiameter  = *(mFieldVariables(2));
            real tYSemidiameter  = *(mFieldVariables(3));
            real tExponent       = *(mFieldVariables(4));
            real tScaling        = *(mFieldVariables(5));
            real tRegularization = *(mFieldVariables(6));
            real tShift          = *(mFieldVariables(7));

            // Evaluate field
            real tConstant = pow(
                    pow((aCoordinates(0) - tXCenter) / tXSemidiameter, tExponent) +
                    pow((aCoordinates(1) - tYCenter) / tYSemidiameter, tExponent) +
                    pow( tRegularization                             , tExponent), 1.0 / tExponent) - tRegularization;

            real tLevelset = tScaling * (tConstant - 1.0);

            // Ensure that level set value is not approx. zero at evaluation point
            if ( std::abs(tLevelset < tShift))
            {
                tLevelset += tLevelset<0.0 ? -tShift : tShift;
            }

            return tLevelset;
        }

        //--------------------------------------------------------------------------------------------------------------

        void Superellipse::evaluate_all_sensitivities(const Matrix<DDRMat>& aCoordinates, Matrix<DDRMat>& aSensitivities)
        {
            // Get variables
            real tXCenter        = *(mFieldVariables(0));
            real tYCenter        = *(mFieldVariables(1));
            real tXSemidiameter  = *(mFieldVariables(2));
            real tYSemidiameter  = *(mFieldVariables(3));
            real tExponent       = *(mFieldVariables(4));
            real tScaling        = *(mFieldVariables(5));
            real tRegularization = *(mFieldVariables(6));

            // Constant in all calculations
            real tConstant0 = pow(
                    pow((aCoordinates(0) - tXCenter)/tXSemidiameter,tExponent) +
                    pow((aCoordinates(1) - tYCenter)/tYSemidiameter,tExponent) +
                    pow( tRegularization                           ,tExponent),(1.0/tExponent - 1.0));

            real tConstant1 = pow((aCoordinates(0) - tXCenter)/tXSemidiameter,tExponent - 1.0);
            real tConstant2 = pow((aCoordinates(1) - tYCenter)/tYSemidiameter,tExponent - 1.0);

            // Calculate sensitivities
            aSensitivities.set_size(1, 8);

            aSensitivities(0) = -tScaling*tConstant1*tConstant0/tXSemidiameter;
            aSensitivities(1) = -tScaling*tConstant2*tConstant0/tYSemidiameter;

            aSensitivities(2) = -tScaling*(aCoordinates(0) - tXCenter)*tConstant1*tConstant0/pow(tXSemidiameter,2.0);
            aSensitivities(3) = -tScaling*(aCoordinates(1) - tYCenter)*tConstant2*tConstant0/pow(tYSemidiameter,2.0);

            // the reminder sensitivities are typically not used and therefore not calculated
            aSensitivities(4) = MORIS_REAL_MAX;
            aSensitivities(5) = MORIS_REAL_MAX;
            aSensitivities(6) = MORIS_REAL_MAX;
            aSensitivities(7) = MORIS_REAL_MAX;
        }

        //--------------------------------------------------------------------------------------------------------------

    }
}
