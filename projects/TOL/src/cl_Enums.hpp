/*
 * cl_tools_Enums.hpp
 *
 *  Created on: Oct 20, 2016
 *      Author: doble
 */

#ifndef SRC_TOOLS_CL_ENUMS_HPP_
#define SRC_TOOLS_CL_ENUMS_HPP_


enum class DerivativeType
{

    DIRECTIONAL_WRT_INDEPVARS,      //< Directional derivative wrt to independent variables.
    DIRECTIONAL_WRT_PARAMETERS,     //< Directional derivative wrt to function parameters.
    NONDIR_WRT_INDEPVARS,           //< Non-directional derivative (not post-multiplied) wrt to independent variables.
    NONDIR_WRT_PARAMETERS           //< Non-directional derivative (not post-multiplied) wrt to function parameters.

};

enum class DerivativeOrder
{
    ZEROTH_ORDER,       // zeroth order derivative
    FIRST_ORDER,        // first order derivative
    SECOND_ORDER        // second order derivative
};

enum class FunctionType
{
    LEVELSET_SPHERE ,// Analytical sphere equation
    LEVELSET_PLANE,
    LEVELSET_RANDOM
};





#endif /* SRC_TOOLS_CL_ENUMS_HPP_ */
