#ifndef MORIS_IOS_CL_TRACER_HPP_
#define MORIS_IOS_CL_TRACER_HPP_

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstring>

#include "cl_Cell.hpp"

#include "cl_GlobalClock.hpp"
#include "cl_Tracer_Enums.hpp"

#include "typedefs.hpp"
#include "IO_Tools.hpp"


//extern moris::GlobalClock gClock;
moris::GlobalClock gClock;

namespace moris
{
class Tracer
    {

    //-------------------------------- PRIVATE --------------------------------//
    private:

    // class has no member variables / is empty


    //-------------------------------- PUPLIC ---------------------------------//
    public:

    // constructor: perform sign in operation if called
    Tracer( enum moris::EntityBase aEntityBase, enum moris::EntityType aEntityType, enum moris::EntityAction aEntityAction )
    {
        gClock.sign_in( aEntityBase, aEntityType, aEntityAction );
    };

    // destructor: automatically perform sign out operation when tracer is destructed
    ~Tracer()
    {
        gClock.sign_out();
    };


    }; // class Tracer
} // namespace moris

#endif  /* MORIS_IOS_CL_TRACER_HPP_ */

