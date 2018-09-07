#include <catch.hpp>

#include "typedefs.hpp"
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "fn_chol_l.hpp"

TEST_CASE("moris::chol_l",
          "[linalgebra],[chol_l]")
{
    moris::Matrix< moris::real,  moris::DDRMat>  tA = { { 4, 12, -16 } ,  { 12, 37, -43 } , { -16, -43, 98 } };

    moris::Matrix< moris::real,  moris::DDRMat> tL = chol_l( tA );

    REQUIRE( tL( 0, 0 ) ==  2 );
    REQUIRE( tL( 1, 0 ) ==  6 );
    REQUIRE( tL( 2, 0 ) == -8 );
    REQUIRE( tL( 0, 1 ) ==  0 );
    REQUIRE( tL( 1, 1 ) ==  1 );
    REQUIRE( tL( 2, 1 ) ==  5 );
    REQUIRE( tL( 0, 2 ) ==  0 );
    REQUIRE( tL( 1, 2 ) ==  0 );
    REQUIRE( tL( 2, 2 ) ==  3 );

}
