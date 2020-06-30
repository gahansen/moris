/*
 * cl_WRK_Performer_Manager.hpp
 *
 *  Created on: Feb 19, 2020
 *      Author: schmidt
 */

#ifndef PROJECTS_FEM_MDL_SRC_CL_WRK_PERFORMER_MANAGER_HPP_
#define PROJECTS_FEM_MDL_SRC_CL_WRK_PERFORMER_MANAGER_HPP_

#include "typedefs.hpp"                       //MRS/COR/src
#include "cl_Cell.hpp"                        //MRS/CON/src

#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_MTK_Enums.hpp"
#include "cl_Communication_Tools.hpp"

namespace xtk
{
    class Model;
}

namespace moris
{
    class Library_IO;
    //------------------------------------------------------------------------------
    namespace hmr
    {
        class HMR;
    }
    namespace mtk
    {
        class Mesh_Manager;
    }
    namespace ge
    {
        class Geometry_Engine;
    }
    namespace mdl
    {
        class Model;
    }
    namespace opt
    {
        class Manager;
    }

    namespace wrk
    {
        class Workflow;

        //------------------------------------------------------------------------------

        class Performer_Manager
        {
                std::shared_ptr< Library_IO > mLibrary = nullptr;

                moris::Cell< std::shared_ptr< mtk::Mesh_Manager > >        mMTKPerformer;
                moris::Cell< std::shared_ptr< hmr::HMR > >                 mHMRPerformer;
                moris::Cell< std::shared_ptr< ge::Geometry_Engine > >      mGENPerformer;
                moris::Cell< std::shared_ptr< xtk::Model > >               mXTKPerformer;
                moris::Cell< std::shared_ptr< mdl::Model > >               mMDLPerformer;
                moris::Cell< std::shared_ptr< opt::Manager > >             mOPTPerformer;

                friend class wrk::Workflow;

            public:

                //------------------------------------------------------------------------------
                /**
                 * constructor
                 * @param[ in ] aMesh          mesh for this problem
                 */
                Performer_Manager( std::shared_ptr< Library_IO > aLibrary );

                //------------------------------------------------------------------------------
                /**
                 * destructor
                 */
                ~Performer_Manager();

                void initialize_performers();

                void set_performer_cooperations();

                void create_xtk();

                //------------------------------------------------------------------------------
        };
    } /* namespace mdl */
} /* namespace moris */


#endif /* PROJECTS_FEM_MDL_SRC_CL_WRK_PERFORMER_MANAGER_HPP_ */
