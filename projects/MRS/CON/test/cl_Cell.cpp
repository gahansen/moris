// Third-party header files.
#include <catch.hpp>
#include <iostream>

// MORIS project header files.
#include "core.hpp"
#include "cl_Cell.hpp" // CON/src

// ----------------------------------------------------------------------------

TEST_CASE(
        "moris::Cell" )
{

    SECTION( "moris::Cell operator=")
    {
        moris::Cell< moris::uint > myval = { 4 };
        moris::Cell< moris::uint > myCell1 = { 10, 2, 3 };

        // Test with single value
        moris::Cell< moris::uint > val1;
        val1 = myval;

        REQUIRE( val1(0) == 4 );

        // Test with row Cell
        moris::Cell< moris::uint > Cell1;
        Cell1 = myCell1;

        REQUIRE( Cell1(0) == 10 );
        REQUIRE( Cell1(1) == 2 );
        REQUIRE( Cell1(2) == 3 );
    }

    SECTION( "moris::Cell size constructor" )
    {
        moris::Cell< moris::uint > myCell1( 10, 4  );
        moris::Cell< moris::real > myCell2( 10, 3.0 );

        REQUIRE( myCell1( 5 ) == 4   );
        REQUIRE( myCell2( 5 ) == 3.0 );
    }

    SECTION( "moris::Cell.size()",
             "moris::Cell.empty()" )
    {
        moris::Cell< moris::uint > myCell1 = {10, 2, 3};

        moris::Cell< moris::uint > myCell2;

        moris::size_t Cell_size = myCell1.size();

        bool isempty = myCell2.empty();

        REQUIRE( Cell_size == 3 );
        REQUIRE( isempty == true );
    }

    SECTION( "moris::Cell.append()")
    {
        moris::Cell< moris::uint > myCell1 = { 4, 5, 9, 8 };
        moris::Cell< moris::uint > myCell2 = { 10, 2, 3 };

        myCell1.append(myCell2);

        REQUIRE( myCell1(0) == 4 );  REQUIRE( myCell1(1) == 5 );
        REQUIRE( myCell1(2) == 9 );  REQUIRE( myCell1(3) == 8 );
        REQUIRE( myCell1(4) == 10 ); REQUIRE( myCell1(5) == 2 );
        REQUIRE( myCell1(6) == 3 );
    }

}
