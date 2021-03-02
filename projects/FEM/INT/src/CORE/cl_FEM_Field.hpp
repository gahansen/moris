/*
 * cl_FEM_Field.hpp
 *
 *  Created on: Jan 19, 2021
 *      Author: schmidt
 */

#ifndef PROJECTS_HMR_SRC_CL_FEM_FIELD_HPP_
#define PROJECTS_HMR_SRC_CL_FEM_FIELD_HPP_

#include <memory>

#include "typedefs.hpp"
#include "cl_Mesh_Enums.hpp"
#include "cl_MTK_Enums.hpp"
#include "cl_MTK_Mesh_Core.hpp"
#include "cl_MTK_Mesh_Manager.hpp"
#include "cl_MTK_Interpolation_Mesh.hpp"
#include "cl_MTK_Field.hpp"

namespace moris
{
    namespace mtk
    {
        class Field;
    }
    namespace fem
    {
        //------------------------------------------------------------------------------

        //------------------------------------------------------------------------------

        class Field : public mtk::Field
        {
            private:

                enum mtk::Field_Type mFieldType = mtk::Field_Type::UNDEFINED;

                std::string          mIQIName;

                std::string          mOutpurFileName;


                //------------------------------------------------------------------------------
            public :
                //------------------------------------------------------------------------------

                Field( mtk::Mesh_Pair * aMeshPair,
                       uint const                         & aDiscretizationMeshIndex =0 );

                //------------------------------------------------------------------------------

                ~Field();

                //------------------------------------------------------------------------------

                void set_field_type( const mtk::Field_Type & aType );

                //-----------------------------------------------------------------------------

                void set_field_from_file( const std::string & aString );

                //-----------------------------------------------------------------------------

                void set_field_to_file( const std::string & aString );

                //-----------------------------------------------------------------------------

                void set_IQI_name( const std::string & aString );

                //-----------------------------------------------------------------------------

                const std::string & get_IQI_name();

                //-----------------------------------------------------------------------------

                void get_nodal_values(
                        Matrix< IndexMat > const   & aNodeIndex,
                        Matrix< DDRMat >              & aNodalValues,
                        Cell< mtk::Field_Type > const & aFieldTypes);

                //-----------------------------------------------------------------------------

                /**
                 * @brief child class implementation: computes and stores nodal values
                 */
                virtual void compute_nodal_values()
                {
                    MORIS_ERROR(false,"fem::Field::compute_nodal_values - not implemented.\n");
                }

                // ----------------------------------------------------------------------------------------------

                /**
                 * @brief child class implementation: computes derivatives of nodal values
                 */
                virtual void compute_derivatives_of_field_value(
                        Matrix< DDRMat >       & aDerivatives,
                        Matrix< DDUMat >       & aCoefIndices,
                        uint             const & aNodeIndex,
                        uint             const & aFieldIndex)
                {
                    MORIS_ERROR(false,"fem::Field::compute_derivatives_of_field_value - not implemented.\n");
                }

                //-----------------------------------------------------------------------------

        };

        //------------------------------------------------------------------------------
    } /* namespace mtk */
} /* namespace moris */

#endif /* PROJECTS_HMR_SRC_CL_FEM_FIELD_HPP_ */
