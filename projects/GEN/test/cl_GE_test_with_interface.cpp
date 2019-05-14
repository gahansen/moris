/*
 * cl_GE_test_with_proxy.cpp
 *
 *  Created on: Apr 4, 2019
 *      Author: sonne
 */

#include "../src/cl_GE_Core.hpp"
#include "catch.hpp"

// GE includes
//------------------------------------------------------------------------------
#include "cl_GE_Factory.hpp"
#include "cl_GE_Interface_Proxy.hpp"

//------------------------------------------------------------------------------
// linalg includes

#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "fn_all_true.hpp"
#include "fn_equal_to.hpp"
#include "op_equal_equal.hpp"
//------------------------------------------------------------------------------

using namespace moris;
using namespace ge;
// assumed user-defined function (sphere)
real
proxy_sphere_function( const Matrix< DDRMat > & aCoordinate,
                       Cell< real >       aInputs )
{   /* aCoordinate = point vector to determine value at (x,y,z)
     * aInputs(0)  = x location of center;      aInputs(1)  = y location of center
     * aInputs(2)  = z location of center;      aInputs(3)  = radius of sphere */
    real tFuncVal = (aCoordinate(0,0) - aInputs(0))*(aCoordinate(0,0) - aInputs(0)) +
                    (aCoordinate(0,1) - aInputs(1))*(aCoordinate(0,1) - aInputs(1)) +
                    (aCoordinate(0,2) - aInputs(2))*(aCoordinate(0,2) - aInputs(2)) -
                    (aInputs(3)*aInputs(3));
    return tFuncVal;
}


TEST_CASE("interface_to_main","[GE],[interfaceTest]")

{

}

//------------------------------------------------------------------------------

