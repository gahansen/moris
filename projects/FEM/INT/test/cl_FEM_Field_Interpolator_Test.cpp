#include "catch.hpp"
#include "cl_FEM_Field_Interpolator.hpp" //FEM/INT/src

using namespace moris;
using namespace fem;

TEST_CASE( "Field_Interpolator", "[moris],[fem],[FieldInterpolator]" )
{

    // define an epsilon environment
    double tEpsilon = 1E-12;

    SECTION( "Field Interpolator : Space bar2 - Time bar2" )
    {
        // space time geometry interpolator
        //------------------------------------------------------------------------------
        //create a bar2 space element
        Matrix< DDRMat > tXHat( 2, 1 );
        tXHat( 0, 0 ) = -1.0;
        tXHat( 1, 0 ) =  3.0;

        //create a bar2 time element
        Matrix< DDRMat > tTHat( 2, 1 );
        tTHat( 0 ) = 0.0;
        tTHat( 1 ) = 5.0;

        //create a space geometry interpolation rule
        Interpolation_Rule tGeomInterpRule( mtk::Geometry_Type::LINE,
                                            Interpolation_Type::LAGRANGE,
                                            mtk::Interpolation_Order::LINEAR,
                                            Interpolation_Type::LAGRANGE,
                                            mtk::Interpolation_Order::LINEAR );

        //create a space and a time geometry interpolator
        Geometry_Interpolator* tGeomInterpolator = new Geometry_Interpolator( tGeomInterpRule );

        //set the coefficients xHat, tHat
        tGeomInterpolator->set_coeff( tXHat, tTHat );

        // field interpolator
        //------------------------------------------------------------------------------
        //create a space time interpolation rule
        Interpolation_Rule tInterpolationRule ( mtk::Geometry_Type::LINE,
                                                Interpolation_Type::LAGRANGE,
                                                mtk::Interpolation_Order::LINEAR,
                                                Interpolation_Type::LAGRANGE,
                                                mtk::Interpolation_Order::LINEAR );

        //create a field interpolator
        uint tNumberOfFields = 1;
        Field_Interpolator tFieldInterpolator( tNumberOfFields,
                                               tInterpolationRule,
                                               tGeomInterpolator );

        //create scalar field discretized value tUHat
        Interpolation_Function_Base * tSpaceInterpolation = tInterpolationRule.create_space_interpolation_function();
        Interpolation_Function_Base * tTimeInterpolation  = tInterpolationRule.create_time_interpolation_function();

        Matrix< DDRMat > tSpaceParamCoord = tSpaceInterpolation->get_param_coords();
        tSpaceParamCoord = trans( tSpaceParamCoord );
        Matrix< DDRMat > tTimeParamCoord  = tTimeInterpolation->get_param_coords();
        tTimeParamCoord = trans( tTimeParamCoord );

        uint tNSpaceBases     = tFieldInterpolator.get_number_of_space_bases();
        uint tNTimeBases      = tFieldInterpolator.get_number_of_time_bases();
        uint tNSpaceTimeBases = tFieldInterpolator.get_number_of_space_time_bases();
        Matrix< DDRMat > tUHat( tNSpaceTimeBases , tNumberOfFields );
        Matrix< DDRMat > t1, x1;
        real a1 =  1.0, b1 = 2.0, b2 = 3.0, c1 = 4.0;
        for ( moris::uint Ik = 0; Ik < tNTimeBases; Ik++ )
        {
            t1 = tGeomInterpolator->valt( tTimeParamCoord.get_row(Ik) );
            for ( moris::uint Jk = 0; Jk < tNSpaceBases; Jk++ )
            {
                x1 = tGeomInterpolator->valx( tSpaceParamCoord.get_row( Jk ) );
                tUHat( (Ik*tNSpaceBases)+Jk, 0 ) = a1 + b1*x1(0) + b2*t1(0) + c1*x1(0)*t1(0);
            }
        }

        //set the coefficients uHat
        tFieldInterpolator.set_coeff( tUHat );

        // create evaluation point xi, tau
        Matrix< DDRMat > tXi ( 1, 1, 0.35);
        Matrix< DDRMat > tTau( 1, 1, 0.70);
        Matrix< DDRMat > tParamPoint = {{ tXi( 0 ) },
                                        { tTau( 0 ) }};

        //set the evaluation point xi, tau
        tFieldInterpolator.set_space_time( tParamPoint );

        // check evaluations
        //------------------------------------------------------------------------------
        // real for check
        real test;

        //evaluate space and time at xi, tau
        Matrix< DDRMat > x = tGeomInterpolator->valx( tXi );
        Matrix< DDRMat > t = tGeomInterpolator->valt( tTau );

        //check field value at xi, tau
        Matrix< DDRMat > u = tFieldInterpolator.val();
        Matrix< DDRMat > uExact( 1, 1 , a1 + b1*x(0) + b2*t(0) + c1*x(0)*t(0) );
        test = u( 0, 0 ) - uExact( 0, 0 );
        REQUIRE( ( test < tEpsilon ) );

        //check field first space derivative at xi, tau
        Matrix< DDRMat > tdudx = tFieldInterpolator.gradx( 1 );
        Matrix< DDRMat > tdudxExact( 1, 1, b1 + c1*t(0) );
        test = tdudx(0,0) - tdudxExact(0,0);
        REQUIRE( ( test < tEpsilon ) );

        //check field second space derivative at xi, tau
        Matrix< DDRMat > td2udx2 = tFieldInterpolator.gradx( 2 );
        Matrix< DDRMat > td2udx2Exact( 1, 1, 0 );        // set the space and time derivative order for the field

        test = td2udx2( 0, 0 ) - td2udx2Exact( 0, 0 );
        REQUIRE( ( test < tEpsilon ) );

        //check field first time derivative at xi, tau
        Matrix< DDRMat > tdudt = tFieldInterpolator.gradt( 1 );
        Matrix< DDRMat > tdudtExact( 1, 1,  b2 + c1*x(0) );
        test = tdudt( 0, 0 ) - tdudtExact( 0, 0 );
        REQUIRE( ( test < tEpsilon ) );

        //check field second time derivative at xi, tau
        Matrix< DDRMat > td2udt2 = tFieldInterpolator.gradt( 2 );
        Matrix< DDRMat > td2udt2Exact( 1, 1, 0 );
        test = td2udt2( 0, 0 ) - td2udt2Exact( 0, 0 );
        REQUIRE( ( test < tEpsilon ) );

        // delete pointers
        delete tGeomInterpolator;
        delete tSpaceInterpolation;
        delete tTimeInterpolation;
    }

    SECTION( "Field Interpolator : Space quad4 - Time bar2" )
        {
            // space and time geometry interpolators
            //------------------------------------------------------------------------------
            //create a quad4 space element
            Matrix< DDRMat > tXHat( 4, 2 );
            tXHat( 0, 0 ) = 0.0; tXHat( 0, 1 ) = 0.0;
            tXHat( 1, 0 ) = 3.0; tXHat( 1, 1 ) = 1.25;
            tXHat( 2, 0 ) = 4.5; tXHat( 2, 1 ) = 4.0;
            tXHat( 3, 0 ) = 1.0; tXHat( 3, 1 ) = 3.25;

            //create a line time element
            Matrix< DDRMat > tTHat( 2, 1 );
            tTHat( 0 ) = 0.0;
            tTHat( 1 ) = 5.0;

            //create a space geometry interpolation rule
            Interpolation_Rule tGeomInterpRule( mtk::Geometry_Type::QUAD,
                                                Interpolation_Type::LAGRANGE,
                                                mtk::Interpolation_Order::LINEAR,
                                                Interpolation_Type::LAGRANGE,
                                                mtk::Interpolation_Order::LINEAR );

            //create a space and a time geometry interpolator
            Geometry_Interpolator* tGeomInterpolator = new Geometry_Interpolator( tGeomInterpRule );

            //set the coefficients xHat, tHat
            tGeomInterpolator->set_coeff( tXHat, tTHat );

            // field interpolator
            //------------------------------------------------------------------------------
            //create a space time interpolation rule
            Interpolation_Rule tInterpolationRule ( mtk::Geometry_Type::QUAD,
                                                    Interpolation_Type::LAGRANGE,
                                                    mtk::Interpolation_Order::LINEAR,
                                                    Interpolation_Type::LAGRANGE,
                                                    mtk::Interpolation_Order::LINEAR );
            //create a field interpolator
            uint tNumberOfFields = 1;
            Field_Interpolator tFieldInterpolator( tNumberOfFields,
                                                   tInterpolationRule,
                                                   tGeomInterpolator );

            //create scalar field coefficients tUHat
            uint tNSpaceTimeBases = tFieldInterpolator.get_number_of_space_time_bases();
            Matrix< DDRMat > tUHat( tNSpaceTimeBases , tNumberOfFields );
            tUHat ( 0 ) = 1;
            tUHat ( 1 ) = 29.5;
            tUHat ( 2 ) = 112;
            tUHat ( 3 ) = 29;
            tUHat ( 4 ) = 21;
            tUHat ( 5 ) = 333.25;
            tUHat ( 6 ) = 1127;
            tUHat ( 7 ) = 322.75;

            //set the coefficients uHat
            tFieldInterpolator.set_coeff( tUHat );

            // create evaluation point xi, tau
            Matrix< DDRMat > tXi( 2, 1 );
            tXi( 0, 0 ) =  0.35;
            tXi( 1, 0 ) = -0.25;
            Matrix< DDRMat > tTau( 1, 1, 0.70 );
            Matrix< DDRMat > tParamPoint = { { tXi( 0 ) },
                                             { tXi( 1 ) },
                                             { tTau( 0 ) }};

            //set the evaluation point xi, tau
            tFieldInterpolator.set_space_time( tParamPoint );

            // hex8 for comparison
            //------------------------------------------------------------------------------
            // coefficients xHat for the HEX8,
            // built from xHat and tHat for the space time element
            Matrix< DDRMat > tCheckXHat( 8, 3 );
            tCheckXHat( 0, 0 ) = 0.0; tCheckXHat( 0, 1 ) = 0.0;  tCheckXHat( 0, 2 ) = 0.0;
            tCheckXHat( 1, 0 ) = 3.0; tCheckXHat( 1, 1 ) = 1.25; tCheckXHat( 1, 2 ) = 0.0;
            tCheckXHat( 2, 0 ) = 4.5; tCheckXHat( 2, 1 ) = 4.0;  tCheckXHat( 2, 2 ) = 0.0;
            tCheckXHat( 3, 0 ) = 1.0; tCheckXHat( 3, 1 ) = 3.25; tCheckXHat( 3, 2 ) = 0.0;
            tCheckXHat( 4, 0 ) = 0.0; tCheckXHat( 4, 1 ) = 0.0;  tCheckXHat( 4, 2 ) = 5.0;
            tCheckXHat( 5, 0 ) = 3.0; tCheckXHat( 5, 1 ) = 1.25; tCheckXHat( 5, 2 ) = 5.0;
            tCheckXHat( 6, 0 ) = 4.5; tCheckXHat( 6, 1 ) = 4.0;  tCheckXHat( 6, 2 ) = 5.0;
            tCheckXHat( 7, 0 ) = 1.0; tCheckXHat( 7, 1 ) = 3.25; tCheckXHat( 7, 2 ) = 5.0;
            //Matrix< DDRMat > tCheckTHat( 1, 1, 0.0 );
            //create a line time element
            Matrix< DDRMat > tCheckTHat( 2, 1 );
            tCheckTHat( 0 ) = 0.0;
            tCheckTHat( 1 ) = 5.0;

            //create a space geometry interpolation rule
            Interpolation_Rule tCheckGeomRule ( mtk::Geometry_Type::HEX,
                                                Interpolation_Type::LAGRANGE,
                                                mtk::Interpolation_Order::LINEAR,
                                                Interpolation_Type::LAGRANGE,
                                                mtk::Interpolation_Order::LINEAR );

            //create a space geometry interpolator
            Geometry_Interpolator* tCheckGeomInterpolator = new Geometry_Interpolator( tCheckGeomRule );

            //set the coefficients xHat
            tCheckGeomInterpolator->set_coeff( tCheckXHat, tCheckTHat );

            //create a space interpolation rule
            Interpolation_Rule tCheckFieldRule ( mtk::Geometry_Type::HEX,
                                                 Interpolation_Type::LAGRANGE,
                                                 mtk::Interpolation_Order::LINEAR,
                                                 Interpolation_Type::CONSTANT,
                                                 mtk::Interpolation_Order::CONSTANT );


            //create a space field interpolator
            Field_Interpolator tCheckFieldInterpolator( tNumberOfFields,
                                                        tCheckFieldRule,
                                                        tCheckGeomInterpolator );

            //set the coefficients uHat
            tCheckFieldInterpolator.set_coeff( tUHat );

            // evaluation point xi for the HEX8,
            // built from xi and tau for the space time element
            Matrix< DDRMat > tCheckXi( 4, 1 );
            tCheckXi( 0 ) = tXi( 0 );
            tCheckXi( 1 ) = tXi( 1 );
            tCheckXi( 2 ) = tTau( 0 );
            tCheckXi( 3 ) = 0.0;

            //set the evaluation point xi
            tCheckFieldInterpolator.set_space_time( tCheckXi );

            // check evaluations
            //------------------------------------------------------------------------------
            //value of x and t at xi, tau
            Matrix< DDRMat > x = tGeomInterpolator->valx( tXi );
            Matrix< DDRMat > t = tGeomInterpolator->valt( tTau );

            //real for test
            double test1, test2, test3, test4;

            //check field value at xi, tau
            Matrix< DDRMat > u      = tFieldInterpolator.val();
            Matrix< DDRMat > uExact = tCheckFieldInterpolator.val();
            test1 = u( 0, 0 ) - uExact( 0, 0 );
            REQUIRE( ( test1 < tEpsilon ) );

            //check field first space and time derivative at xi, tau
            Matrix< DDRMat > tdudx      = tFieldInterpolator.gradx( 1 );
            Matrix< DDRMat > tdudt      = tFieldInterpolator.gradt( 1 );
            Matrix< DDRMat > tdudxExact = tCheckFieldInterpolator.gradx( 1 );

            test1 = tdudx( 0, 0 ) - tdudxExact( 0, 0 );
            test2 = tdudx( 1, 0 ) - tdudxExact( 1, 0 );
            test3 = tdudt( 0, 0 ) - tdudxExact( 2, 0 );
            REQUIRE( ( test1 < tEpsilon ) );
            REQUIRE( ( test2 < tEpsilon ) );
            REQUIRE( ( test3 < tEpsilon ) );

            //check field second space and time derivative at xi, tau
            Matrix< DDRMat > td2udx2 = tFieldInterpolator.gradx( 2 );
            Matrix< DDRMat > td2udt2 = tFieldInterpolator.gradt( 2 );
            Matrix< DDRMat > td2udx2Exact = tCheckFieldInterpolator.gradx( 2 );
            test1 = td2udx2( 0, 0 ) - td2udx2Exact( 0, 0 );
            test2 = td2udx2( 1, 0 ) - td2udx2Exact( 1, 0 );
            test3 = td2udx2( 2, 0 ) - td2udx2Exact( 5, 0 );
            test4 = td2udt2( 0, 0 ) - td2udx2Exact( 2, 0 );
            REQUIRE( ( test1 < tEpsilon ) );
            REQUIRE( ( test2 < tEpsilon ) );
            REQUIRE( ( test3 < tEpsilon ) );
            REQUIRE( ( test4 < tEpsilon ) );

            // delete pointers
            delete tGeomInterpolator;
            delete tCheckGeomInterpolator;
        }

    SECTION( "Field Interpolator : Space bar3 - Time bar2" )
    {
        // create space and time geometry interpolators
        //------------------------------------------------------------------------------
        //create a bar2 space element
        Matrix< DDRMat > tXHat( 2, 1 );
        tXHat( 0, 0 ) = -1.0;
        tXHat( 1, 0 ) =  3.0;

        //create a bar2 time element
        Matrix< DDRMat > tTHat( 2, 1 );
        tTHat( 0 ) = 0.0;
        tTHat( 1 ) = 5.0;

        //create a space geometry interpolation rule
        Interpolation_Rule tGeomInterpRule( mtk::Geometry_Type::LINE,
                                            Interpolation_Type::LAGRANGE,
                                            mtk::Interpolation_Order::LINEAR,
                                            Interpolation_Type::LAGRANGE,
                                            mtk::Interpolation_Order::LINEAR);

        //create a space and a time geometry interpolator
        Geometry_Interpolator* tGeomInterpolator = new Geometry_Interpolator( tGeomInterpRule );

        //set the coefficients xHat, tHat
        tGeomInterpolator->set_coeff( tXHat, tTHat);

        // create space time field interpolator
        //------------------------------------------------------------------------------
        //create a space time interpolation rule
        Interpolation_Rule tInterpolationRule ( mtk::Geometry_Type::LINE,
                                                Interpolation_Type::LAGRANGE,
                                                mtk::Interpolation_Order::QUADRATIC,
                                                Interpolation_Type::LAGRANGE,
                                                mtk::Interpolation_Order::LINEAR );

        //create a field interpolator
        uint tNumberOfFields = 1;
        Field_Interpolator tFieldInterpolator( tNumberOfFields,
                                               tInterpolationRule,
                                               tGeomInterpolator );

        //create scalar field discretized value tUHat
        Interpolation_Function_Base * tSpaceInterpolation = tInterpolationRule.create_space_interpolation_function();
        Interpolation_Function_Base * tTimeInterpolation  = tInterpolationRule.create_time_interpolation_function();

        Matrix< DDRMat > tSpaceParamCoord = tSpaceInterpolation->get_param_coords();
        tSpaceParamCoord = trans( tSpaceParamCoord );
        Matrix< DDRMat > tTimeParamCoord  = tTimeInterpolation->get_param_coords();
        tTimeParamCoord = trans( tTimeParamCoord );

        uint tNSpaceBases     = tFieldInterpolator.get_number_of_space_bases();
        uint tNTimeBases      = tFieldInterpolator.get_number_of_time_bases();
        uint tNSpaceTimeBases = tFieldInterpolator.get_number_of_space_time_bases();
        Matrix< DDRMat > tUHat( tNSpaceTimeBases , tNumberOfFields );


        Matrix< DDRMat > t1, x1;
        real a1 =  1.0, b1 = 2.0, b2 = 3.0, c1 = 4.0;
        for ( moris::uint Ik = 0; Ik < tNTimeBases; Ik++ )
        {
            t1 = tGeomInterpolator->valt( tTimeParamCoord.get_row( Ik ) );
            for ( moris::uint Jk = 0; Jk < tNSpaceBases; Jk++ )
            {
                x1 = tGeomInterpolator->valx( tSpaceParamCoord.get_row( Jk ) );
                tUHat( (Ik*tNSpaceBases)+Jk, 0 ) = a1 + b1*x1(0) + b2*t1(0) + c1*x1(0)*t1(0);
            }
        }

        //set the coefficients uHat of the
        tFieldInterpolator.set_coeff( tUHat );

        //evaluation point xi, tau
        Matrix< DDRMat > tXi( 1, 1, 0.35 );
        Matrix< DDRMat > tTau( 1, 1, 0.70 );
        Matrix< DDRMat > tParamPoint = { { tXi( 0 ) },
                                         { tTau( 0 ) }};

        //set the evaluation point xi, tau
        tFieldInterpolator.set_space_time( tParamPoint );

        // check
        //------------------------------------------------------------------------------
        // double for check, x and t for check at xi, tau
        double test;
        Matrix< DDRMat > t = tGeomInterpolator->valt( tTau );
        Matrix< DDRMat > x = tGeomInterpolator->valx( tXi );

        //check field value at xi, tau
        Matrix< DDRMat > u = tFieldInterpolator.val();
        Matrix< DDRMat > uExact( 1, 1, a1 + b1*x(0) + b2*t(0) + c1*x(0)*t(0) );
        test = u( 0, 0 ) - uExact( 0, 0 );
        REQUIRE( ( test < tEpsilon ) );

        //check field first space derivative at xi, tau
        Matrix <DDRMat> tdudx = tFieldInterpolator.gradx( 1 );
        Matrix< DDRMat > tdudxExact( 1, 1, b1 + c1*t(0) );
        test = tdudx( 0, 0 ) - tdudxExact(0,0);
        REQUIRE( ( test < tEpsilon ) );

        //check field second space derivative at xi, tau
        Matrix< DDRMat > td2udx2 = tFieldInterpolator.gradx( 2 );
        Matrix< DDRMat > td2udx2Exact( 1, 1 );
        td2udx2Exact( 0 ) = 0;
        test = td2udx2( 0, 0 ) - td2udx2Exact( 0, 0 );
        REQUIRE( ( test < tEpsilon ) );

        //check field first time derivative at xi, tau
        Matrix< DDRMat > tdudt = tFieldInterpolator.gradt( 1 );
        Matrix< DDRMat > tdudtExact( 1, 1, b2 + c1*x(0) );
        test = tdudt( 0, 0 ) - tdudtExact( 0, 0 );
        REQUIRE( ( test < tEpsilon ) );

        //check field second time derivative at xi, tau
        Matrix< DDRMat > td2udt2 = tFieldInterpolator.gradt( 2 );
        Matrix< DDRMat > td2udt2Exact( 1, 1 , 0);
        test = td2udt2(0,0) - td2udt2Exact(0,0);
        REQUIRE( ( test < tEpsilon ) );

        // delete pointers
        delete tGeomInterpolator;
        delete tSpaceInterpolation;
        delete tTimeInterpolation;
    }

//------------------------------------------------------------------------------
}

