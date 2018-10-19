/*
 * cl_SDF_Generator.hpp
 *
 *  Created on: Oct 4, 2018
 *      Author: messe
 */

#ifndef PROJECTS_GEN_SDF_SRC_CL_SDF_GENERATOR_HPP_
#define PROJECTS_GEN_SDF_SRC_CL_SDF_GENERATOR_HPP_

#include <string>
#include <memory>

#include "typedefs.hpp"
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"

#include "cl_MTK_Mesh.hpp"
#include "cl_SDF_Object.hpp"
namespace moris
{
    namespace sdf
    {
//-------------------------------------------------------------------------------

        class SDF_Generator
        {
            //! file containing object data
            Object mObject;

            //! verbosity flag
            bool          mVerboseFlag = false;
//-------------------------------------------------------------------------------
public:
//-------------------------------------------------------------------------------
            /**
             * constructor with pointer
             */

            SDF_Generator( const std::string & aObjectPath,
                           const bool aVerboseFlag = true );


//-------------------------------------------------------------------------------

            /**
             * trivial destructor
             */
            ~SDF_Generator(){};

//-------------------------------------------------------------------------------

            /**
             * performs a raycast for an MTK mesh and returns Matrices with
             * element IDs and indices
             */
            void
            raycast(  mtk::Mesh          * aMesh,
                    Matrix< IndexMat > & aElementsAtSurface );

//-------------------------------------------------------------------------------

            /**
             * performs a raycast for an MTK mesh and returns Matrices with
             * element IDs and indices ( shared pointer version )
             */
            void
            raycast( std::shared_ptr< mtk::Mesh > aMesh,
                    Matrix< IndexMat >            & aElementsAtSurface );

//-------------------------------------------------------------------------------

            /**
             * performs a raycast for an MTK mesh and returns Matrices with
             * element IDs and indices
             */
            void
            raycast(  mtk::Mesh        * aMesh,
                    Matrix< IndexMat > & aElementsAtSurface,
                    Matrix< IndexMat > & aElementsInVolume );

//-------------------------------------------------------------------------------

            /**
             * performs a raycast for an MTK mesh and returns Matrices with
             * element IDs and indices ( shared pointer version )
             */
            void
            raycast( std::shared_ptr< mtk::Mesh > aMesh,
                    Matrix< IndexMat >           & aElementsAtSurface,
                    Matrix< IndexMat >           & aElementsInVolume );

//-------------------------------------------------------------------------------

            /**
             * calculates the SDF for a given mesh
             */
            void
            calculate_sdf(
                    mtk::Mesh          * aMesh,
                    Matrix< DDRMat>    & aSDF );

//-------------------------------------------------------------------------------

            /**
             * calculates the SDF for a given mesh ( shared pointer version )
             */
            void
            calculate_sdf(
                    std::shared_ptr< mtk::Mesh > aMesh,
                    Matrix< DDRMat>              & aSDF );

//-------------------------------------------------------------------------------
        };

//-------------------------------------------------------------------------------
    } /* namespace sdf */
} /* namespace moris */

#endif /* PROJECTS_GEN_SDF_SRC_CL_SDF_GENERATOR_HPP_ */
