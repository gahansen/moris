/*
 * cl_GE_Factory.hpp
 *
 *  Created on: Dec 28, 2018
 *      Author: sonne
 */
#ifndef SRC_DISTLINALG_CL_GE_FACTORY_HPP_
#define SRC_DISTLINALG_CL_GE_FACTORY_HPP_

#include <memory>
#include <iostream>

#include "cl_GE_Analytic.hpp"
#include "cl_GE_Discrete.hpp"
#include "cl_GE_Enums.hpp"
#include "cl_GE_Geometry.hpp"
#include "cl_GE_SDF.hpp"

#include "assert.hpp"


namespace moris
{
    namespace ge
    {

    class Ge_Factory
    {
    	public:
    		Ge_Factory();
    		~Ge_Factory();

    	    /**
    	     * @brief factory member function building GE types
    	     *
    	     * @param[in]  aGeomType    - determines the type of geometry
    	     * .
    	     * @param[out] tGeomPointer - GE pointer to base class.
    	     *
    	     */
    		std::shared_ptr< Geometry >
    		set_geometry_type( const enum GeomType aGeomType = GeomType::ANALYTIC );


        private:

        protected:
    };
    } /* namespace gen */
} /* namespace moris */

#endif /* SRC_DISTLINALG_CL_GE_FACTORY_HPP_ */