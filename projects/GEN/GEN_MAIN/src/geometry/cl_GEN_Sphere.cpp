#include "cl_GEN_Sphere.hpp"

namespace moris
{
    namespace ge
    {

        //--------------------------------------------------------------------------------------------------------------

        Sphere::Sphere(Matrix<DDRMat>& aADVs,
                       Matrix<DDUMat>  aGeometryVariableIndices,
                       Matrix<DDUMat>  aADVIndices,
                       Matrix<DDRMat>  aConstantParameters,
                       sint            aNumRefinements,
                       sint            aRefinementFunctionIndex,
                       sint            aBSplineMeshIndex,
                       real            aBSplineLowerBound,
                       real            aBSplineUpperBound)
                : Field(aADVs,
                        aGeometryVariableIndices,
                        aADVIndices,
                        aConstantParameters,
                        aNumRefinements,
                        aRefinementFunctionIndex,
                        aBSplineMeshIndex,
                        aBSplineLowerBound,
                        aBSplineUpperBound)
        {
            MORIS_ERROR(aGeometryVariableIndices.length() + aConstantParameters.length() == 4,
                        "A GEN Sphere must be created with a total of exactly 4 variables (ADVs + constant parameters)");
        }

        //--------------------------------------------------------------------------------------------------------------

        Sphere::Sphere(sol::Dist_Vector* aOwnedADVs,
                       Matrix<DDUMat>    aGeometryVariableIndices,
                       Matrix<DDUMat>    aADVIndices,
                       Matrix<DDRMat>    aConstantParameters,
                       sint              aNumRefinements,
                       sint              aRefinementFunctionIndex,
                       sint              aBSplineMeshIndex,
                       real              aBSplineLowerBound,
                       real              aBSplineUpperBound)
                : Field(aOwnedADVs,
                        aGeometryVariableIndices,
                        aADVIndices,
                        aConstantParameters,
                        aNumRefinements,
                        aRefinementFunctionIndex,
                        aBSplineMeshIndex,
                        aBSplineLowerBound,
                        aBSplineUpperBound)
        {
            MORIS_ERROR(aGeometryVariableIndices.length() + aConstantParameters.length() == 4,
                        "A GEN Sphere must be created with a total of exactly 4 variables (ADVs + constant parameters)");
        }

        //--------------------------------------------------------------------------------------------------------------

        Sphere::Sphere(real aXCenter,
                       real aYCenter,
                       real aZCenter,
                       real aRadius,
                       sint aNumRefinements,
                       sint aRefinementFunctionIndex,
                       sint aBSplineMeshIndex,
                       real aBSplineLowerBound,
                       real aBSplineUpperBound)
                : Field(Matrix<DDRMat>({{aXCenter, aYCenter, aZCenter, aRadius}}),
                        aNumRefinements,
                        aRefinementFunctionIndex,
                        aBSplineMeshIndex,
                        aBSplineLowerBound,
                        aBSplineUpperBound)
        {
        }

        //--------------------------------------------------------------------------------------------------------------

        real Sphere::evaluate_field_value(const Matrix<DDRMat>& aCoordinates)
        {
            // Get variables
            real tXCenter = *(mFieldVariables(0));
            real tYCenter = *(mFieldVariables(1));
            real tZCenter = *(mFieldVariables(2));
            real tRadius = *(mFieldVariables(3));

            // Evaluate field
            return sqrt(pow(aCoordinates(0) - tXCenter, 2)
                      + pow(aCoordinates(1) - tYCenter, 2)
                      + pow(aCoordinates(2) - tZCenter, 2)) - tRadius;
        }

        //--------------------------------------------------------------------------------------------------------------

        void Sphere::evaluate_all_sensitivities(const Matrix<DDRMat>& aCoordinates, Matrix<DDRMat>& aSensitivities)
        {
            // Get variables
            real tXCenter = *(mFieldVariables(0));
            real tYCenter = *(mFieldVariables(1));
            real tZCenter = *(mFieldVariables(2));

            // Calculate sensitivities
            aSensitivities.resize(1, 4);
            real tConstant = sqrt(pow(aCoordinates(0) - tXCenter, 2)
                    + pow(aCoordinates(1) - tYCenter, 2)
                    + pow(aCoordinates(2) - tZCenter, 2));
            tConstant = tConstant ? 1 / tConstant : 0.0;
            aSensitivities(0) = tConstant * (tXCenter - aCoordinates(0));
            aSensitivities(1) = tConstant * (tYCenter - aCoordinates(1));
            aSensitivities(2) = tConstant * (tZCenter - aCoordinates(2));
            aSensitivities(3) = -1;
        }

        //--------------------------------------------------------------------------------------------------------------

    }
}
