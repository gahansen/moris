/*
 * cl_SDF_Parameters.hpp
 *
 *  Created on: Sep 30, 2018
 *      Author: messe
 */

#ifndef PROJECTS_GEN_SDF_SRC_CL_SDF_PARAMETERS_HPP_
#define PROJECTS_GEN_SDF_SRC_CL_SDF_PARAMETERS_HPP_

#include "typedefs.hpp"
#include "cl_Cell.hpp"
#include "cl_Param_List.hpp"
#include "cl_XML_Parser.hpp"

namespace moris
{
    namespace sdf
    {
//-------------------------------------------------------------------------------

        typedef Param_List< boost::variant< sint, real, std::string  > > ParameterList;

        ParameterList
        create_sdf_parameter_list();

//-------------------------------------------------------------------------------

        ParameterList
        create_sdf_object_parameter_list();

//-------------------------------------------------------------------------------

        void
        load_sdf_parameter_list_from_xml(
                const std::string            & aFilePath,
                ParameterList                & aGlobalParameters,
                moris::Cell< ParameterList > & aObjectParameters );

//-------------------------------------------------------------------------------
    }
}


#endif /* PROJECTS_GEN_SDF_SRC_CL_SDF_PARAMETERS_HPP_ */