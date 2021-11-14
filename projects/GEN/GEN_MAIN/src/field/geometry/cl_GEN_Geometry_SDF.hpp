#ifndef MORIS_CL_GEN_GEOMETRY_SDF_HPP
#define MORIS_CL_GEN_GEOMETRY_SDF_HPP

#include "cl_GEN_Geometry.hpp"
#include "cl_GEN_Field_Discrete_Integration.hpp"
#include "cl_MTK_Mesh_Core.hpp"
#include "cl_Matrix.hpp"
#include "cl_Cell.hpp"

namespace moris
{
    namespace ge
    {
        class Geometry_SDF: public Geometry, public Field_Discrete_Integration
        {

            private:
                std::string mObjectPath = "";

                Matrix<DDRMat> mDummyMat;

            public:
                /**
                 * Constructor
                 *
                 * @param aMesh Mesh with the level set fields
                 * @param aFieldNames Names of the fields
                 */
                Geometry_SDF( std::string tObjectPath,
                        Geometry_Field_Parameters aParameters = {});

                /**
                 * Given a node index, returns the field value.
                 *
                 * @param aNodeIndex Node index
                 * @return Distance to this geometry
                 */
                real get_field_value(uint aNodeIndex);

                void evaluate_nodal_values();

                void reset_nodal_data();

                const Matrix<DDRMat>& get_dfield_dadvs(uint aNodeIndex)
                {
                    MORIS_ERROR( false, "get_dfield_dadvs(), not implemented for Geometry_SDF");
                    return mDummyMat;
                }


            private:

                /**
                 * Given a node index, evaluates the sensitivity of the geometry field with respect to all of the
                 * geometry variables. This is currently not implemented for a mesh field geometry.
                 *
                 * @param aNodeIndex Node index
                 * @return Vector of sensitivities
                 */
                const Matrix<DDRMat>& get_base_dfield_dadvs(
                        uint                  aNodeIndex,
                        const Matrix<DDRMat>& aCoordinates)
                {
                    MORIS_ERROR( false, "get_base_dfield_dadvs(), not implemented for Geometry_SDF");
                    return mDummyMat;
                }

        };
    }
}

#endif /* MORIS_CL_GEN_GEOMETRY_SDF_HPP */
