/*
 * Copyright (c) 2022 University of Colorado
 * Licensed under the MIT license. See LICENSE.txt file in the MORIS root for details.
 *
 *------------------------------------------------------------------------------------
 *
 * cl_HMR_Mesh_Interpolation.hpp
 *
 */

#ifndef PROJECTS_HMR_SRC_CL_HMR_MESH_INTERPOLATION_HPP_
#define PROJECTS_HMR_SRC_CL_HMR_MESH_INTERPOLATION_HPP_

#include "cl_HMR_Mesh.hpp"
#include "cl_MTK_Interpolation_Mesh.hpp"

namespace moris
{
    namespace hmr
    {
        class Interpolation_Mesh_HMR : public virtual Mesh, public mtk::Interpolation_Mesh
        {
            public:

                Interpolation_Mesh_HMR(
                        std::shared_ptr< Database >   aDatabase,
                        const uint                  & aLagrangeMeshIndex)
            : Mesh( aDatabase,
                    aLagrangeMeshIndex )
            {
            }

                Interpolation_Mesh_HMR(
                        std::shared_ptr< Database >   aDatabase,
                        const uint                  & aLagrangeOrder,
                        const uint                  & aLagrangePattern )
                : Mesh( aDatabase,
                        aLagrangeOrder,
                        aLagrangePattern )
                {
                }

                Interpolation_Mesh_HMR(
                        std::shared_ptr< Database >   aDatabase,
                        const uint                  & aOrder,
                        const uint                  & aLagrangePattern,
                        const uint                  & aBsplinePattern)
                : Mesh( aDatabase,
                        aOrder,
                        aLagrangePattern,
                        aBsplinePattern )
                {
                }

                Interpolation_Mesh_HMR(
                        std::shared_ptr< Database >   aDatabase,
                        const uint                  & aLagrangeOrder,
                        const uint                  & aLagrangePattern,
                        const uint                  & aBSplineOrder,
                        const uint                  & aBsplinePattern)
                : Mesh( aDatabase,
                        aLagrangeOrder,
                        aLagrangePattern,
                        aBSplineOrder,
                        aBsplinePattern )
                {
                }

                ~Interpolation_Mesh_HMR()
                {
                }
        };
    }
}
#endif /* PROJECTS_HMR_SRC_CL_HMR_MESH_INTERPOLATION_HPP_ */

