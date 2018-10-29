/*
 * cl_HMR_Parameters.cpp
 *
 *  Created on: May 5, 2018
 *      Author: messe
 */

#include "assert.hpp"

#include "cl_HMR_Parameters.hpp" //HMR/src
#include "fn_print.hpp"
#include "fn_unique.hpp"

namespace moris
{
    namespace hmr
    {

// -----------------------------------------------------------------------------

    // creates a parameter list with default inputs
    ParameterList
    create_hmr_parameter_list()
    {
        ParameterList aParameterList;

        aParameterList.insert( "number_of_elements_per_dimension", std::string( "2, 2" ) );
        aParameterList.insert( "domain_dimensions", std::string( "1, 1" ) );
        aParameterList.insert( "domain_offset", std::string( "0, 0 ") );

        aParameterList.insert( "buffer_size", 2 );

        // this must be a string, because future versions will allow inputs
        // such as "2, 3"
        //aParameterList.insert( "interpolation_order", std::string( "1" ) );
        aParameterList.insert( "bspline_orders", std::string( "1" ) );
        aParameterList.insert( "lagrange_orders", std::string( "1" ) );

        aParameterList.insert( "verbose", 1 );
        aParameterList.insert( "truncate_bsplines", 1 );

        aParameterList.insert( "minimum_initial_refinement", 0 );

        return aParameterList;
    }

//--------------------------------------------------------------------------------

    // creates a parameter list with default inputs
    ParameterList
    load_hmr_parameter_list_from_xml( const std::string & aFilePath )
    {
        // initialize output object
        ParameterList aParameterList = create_hmr_parameter_list();

        // create temporary Parser object
        XML_Parser tParser( aFilePath );
        Cell< std::string > tFirst;
        Cell< std::string > tSecond;

        tParser.get_keys_from_subtree( "moris.hmr", "parameters", 0, tFirst, tSecond );


        for( uint k=0; k<tFirst.size(); ++k )
        {
            std::string tKey = tFirst( k );

            if( tKey == "number_of_elements_per_dimension" )
            {
                aParameterList.set("number_of_elements_per_dimension", tSecond( k ) );
            }
            else if( tKey == "domain_dimensions" )
            {
                aParameterList.set( "domain_dimensions", tSecond( k )  );
            }
            else if( tKey == "domain_offset" )
            {
                aParameterList.set("domain_offset", tSecond( k ) );
            }
            else if( tKey == "buffer_size" )
            {
                aParameterList.set( "buffer_size", ( sint ) std::stoi( tSecond( k ) ) );
            }
            else if( tKey == "bspline_orders" )
            {
                aParameterList.set( "bspline_orders", tSecond( k ) );
            }
            else if( tKey == "lagrange_orders" )
            {
                aParameterList.set( "lagrange_orders", tSecond( k ) );
            }
            else if( tKey == "minimum_initial_refinement" )
            {
                aParameterList.set( "minimum_initial_refinement", ( sint ) std::stoi( tSecond( k ) ) );
            }
            else if ( tKey == "verbose" )
            {
                aParameterList.set( "verbose", ( sint ) string_to_bool( tSecond( k ) ) );
            }
            else if ( tKey == "truncate_bsplines" )
            {
                aParameterList.set( "truncate_bsplines", ( sint ) string_to_bool( tSecond( k ) ) );
            }
        }

        return aParameterList;
    }

//--------------------------------------------------------------------------------

    /*
     * parameter list constructor
     */
    Parameters::Parameters( ParameterList & aParameterList )
    {
        this->string_to_mat(
                aParameterList.get< std::string >("number_of_elements_per_dimension"),
                mNumberOfElementsPerDimension );

        // check sanity of input
        MORIS_ERROR(
                mNumberOfElementsPerDimension.length() == 2 ||
                mNumberOfElementsPerDimension.length() == 3,
                "Number of elements must be a matrix of length 2 or 3.");

        // get domain dimensions
        this->string_to_mat(
                        aParameterList.get< std::string >("domain_dimensions"),
                        mDomainDimensions );

        // check sanity of input
        MORIS_ERROR(
                mNumberOfElementsPerDimension.length() ==
                mDomainDimensions.length(),
                "length of domain_dimensions must be equal to number_of_elements_per_dimension.");

        // get domain offset
        this->string_to_mat(
                aParameterList.get< std::string >("domain_offset"),
                mDomainOffset );

        // check sanity of input
        MORIS_ERROR(
                mNumberOfElementsPerDimension.length() ==
                mDomainOffset.length(),
                "length of domain_offset must be equal to number_of_elements_per_dimension.");

        // set buffer size
        this->set_buffer_size(  aParameterList.get< sint >("buffer_size") );

        // set interpolation orders
        Matrix< DDUMat > tBSplineOrders;
        Matrix< DDUMat > tLagrangeOrders;

        this->string_to_mat( aParameterList.get< std::string >("bspline_orders"),
                tBSplineOrders );

        this->string_to_mat( aParameterList.get< std::string >("lagrange_orders"),
                tLagrangeOrders );

        // set B-Spline and Lagrange orders and create mesh maps
        this->set_mesh_orders( tBSplineOrders, tLagrangeOrders );

        // set verbose fag
        this->set_verbose( aParameterList.get< sint >("verbose") == 1 );

        // set truncation flag
        this->set_bspline_truncation( (bool) aParameterList.get< sint >("truncate_bsplines") );

        // set minimum initial refinement
        this->set_minimum_initial_refimenent(
                aParameterList.get< sint >("minimum_initial_refinement") );

    }

//--------------------------------------------------------------------------------

    void
    Parameters::copy_selected_parameters( const Parameters & aParameters )
    {
        // buffer size
        this->set_buffer_size( aParameters.get_buffer_size() );

        // verbosity flag
        this->set_verbose( aParameters.is_verbose() );

        // truncation flag
        this->set_bspline_truncation( aParameters.truncate_bsplines() );

        // gmsh scaling factor
        this->set_gmsh_scale( aParameters.get_gmsh_scale() );

        this->set_minimum_initial_refimenent( aParameters.get_minimum_initial_refimenent() );
    }

//--------------------------------------------------------------------------------

    void
    Parameters::copy_selected_parameters( ParameterList & aParameterList )
    {
        // crete a temporary parameter object
        Parameters tParameters( aParameterList );

        // copy values into myself
        this->copy_selected_parameters( tParameters );
    }

//--------------------------------------------------------------------------------

        void
        Parameters::error( const std::string & aMessage ) const
        {
            if( par_rank() == 0 )
            {

                std::fprintf( stdout, aMessage.c_str() );
                exit( -1 );
            }
        }

//--------------------------------------------------------------------------------

        void
        Parameters::error_if_locked( const std::string & aFunctionName ) const
        {
            if( mParametersAreLocked )
            {
                std::string tMessage
                    = "Error: calling function Parameters->" + aFunctionName +
                    "() is forbidden since parameters are locked.";

                this->error( tMessage );
            }
        }

//--------------------------------------------------------------------------------

        void
        Parameters::lock()
        {
            mParametersAreLocked = true;
        }

//--------------------------------------------------------------------------------
        void
        Parameters::print() const
        {
            if ( mVerbose && par_rank() == 0 )
            {
                std::fprintf( stdout, "\n" );
                std::fprintf( stdout, "--------------------------------------------------------------------------------\n" ) ;
                std::fprintf( stdout, "  user defined settings\n" ) ;
                std::fprintf( stdout, "--------------------------------------------------------------------------------\n" ) ;
                std::fprintf( stdout, "\n" );
                if ( mNumberOfElementsPerDimension.length() == 1 )
                {
                    std::fprintf( stdout, "  elements per dimension ....... : %lu\n",
                            ( long unsigned int ) mNumberOfElementsPerDimension ( 0 ) );
                }
                else if (  mNumberOfElementsPerDimension.length() == 2 )
                {
                    std::fprintf( stdout, "  elements per dimension ....... : %lu x %lu\n",
                            ( long unsigned int ) mNumberOfElementsPerDimension ( 0 ),
                            ( long unsigned int ) mNumberOfElementsPerDimension ( 1 ) );
                }
                else if (  mNumberOfElementsPerDimension.length() == 3 )
                {
                    std::fprintf( stdout, "  elements per dimension ....... : %lu x %lu x %lu\n",
                            ( long unsigned int ) mNumberOfElementsPerDimension ( 0 ),
                            ( long unsigned int ) mNumberOfElementsPerDimension ( 1 ),
                            ( long unsigned int ) mNumberOfElementsPerDimension ( 3 )
                    );
                }
                std::fprintf( stdout,     "  buffer size .................. : %lu\n", ( long unsigned int ) mBufferSize );
                std::fprintf( stdout,     "  max polynomial ............... : %lu\n", ( long unsigned int ) mMaxPolynomial );
                std::fprintf( stdout, "\n" );
                std::fprintf( stdout, "--------------------------------------------------------------------------------\n" ) ;
                std::fprintf( stdout, "  automatically defined settings\n" ) ;
                std::fprintf( stdout, "--------------------------------------------------------------------------------\n" ) ;
                std::fprintf( stdout, "\n" );
                std::fprintf( stdout,     "  dimension .................... : %u\n", ( unsigned int ) this->get_number_of_dimensions() );
                std::fprintf( stdout,     "  padding size ................. : %lu\n", ( long unsigned int ) this->get_padding_size() );
                std::fprintf( stdout, "\n");
            }
        }

//--------------------------------------------------------------------------------

        /**
         * sets the mesh orders according to given matrix
         */
        void
        Parameters::set_lagrange_orders( const Matrix< DDUMat > & aMeshOrders )
        {
            // test if calling this function is allowed
            this->error_if_locked("set_lagrange_orders" );

            MORIS_ERROR( aMeshOrders.max() <= 3, "Polynomial degree must be between 1 and 3" );
            MORIS_ERROR( 1 <= aMeshOrders.min() , "Polynomial degree must be between 1 and 3" );

            mLagrangeOrders = aMeshOrders;

            // make sure that max polynomial is up to date
            this->update_max_polynomial_and_truncated_buffer();
        }

//--------------------------------------------------------------------------------

        /**
         * sets the mesh orders according to given matrix
         */
        void
        Parameters::set_bspline_orders( const Matrix< DDUMat > & aMeshOrders )
        {
            // test if calling this function is allowed
            this->error_if_locked("set_lagrange_orders" );

            MORIS_ERROR( aMeshOrders.max() <= 3, "Polynomial degree must be between 1 and 3" );
            MORIS_ERROR( 1 <= aMeshOrders.min() , "Polynomial degree must be between 1 and 3" );

            mBSplineOrders = aMeshOrders;

            // make sure that max polynomial is up to date
            this->update_max_polynomial_and_truncated_buffer();

        }

//--------------------------------------------------------------------------------

        void
        Parameters::update_max_polynomial_and_truncated_buffer()
        {
            mMaxPolynomial =
                    ( mLagrangeOrders.max() > mBSplineOrders.max() ) ?
                            (mLagrangeOrders.max() ) : ( mBSplineOrders.max() );

            if ( mBSplineTruncationFlag )
            {
                mBufferSize = mMaxPolynomial;
            }
        }

//--------------------------------------------------------------------------------

        auto
        Parameters::get_padding_size() const -> decltype ( mBufferSize )
        {
            // returns the larger value of max polynomial abd buffer size.
            // in the future, filter with will be regarded here
            return ( mBufferSize > mMaxPolynomial )
                    ? ( mBufferSize ) : ( mMaxPolynomial );
        }

//--------------------------------------------------------------------------------

        void
        Parameters::set_number_of_elements_per_dimension(
                const Matrix< DDLUMat > & aNumberOfElementsPerDimension )
        {
            // test if calling this function is allowed
            this->error_if_locked("set_number_of_elements_per_dimension");

            // check sanity of input
            MORIS_ERROR(
                    aNumberOfElementsPerDimension.length() == 2 ||
                    aNumberOfElementsPerDimension.length() == 3,
                    "Number of elements must be a matrix of length 2 or 3.");

            mNumberOfElementsPerDimension = aNumberOfElementsPerDimension;

            // auto setting for dimensions and offset
            this->set_default_dimensions_and_offset();
        }

//--------------------------------------------------------------------------------

        void
        Parameters::set_number_of_elements_per_dimension(
                const luint & aElementsX,
                const luint & aElementsY )
        {
            // test if calling this function is allowed
            this->error_if_locked("set_number_of_elements_per_dimension");

            mNumberOfElementsPerDimension.set_size( 2, 1 );
            mNumberOfElementsPerDimension( 0 ) = aElementsX;
            mNumberOfElementsPerDimension( 1 ) = aElementsY;

            // auto setting for dimensions and offset
            this->set_default_dimensions_and_offset();

        }

//--------------------------------------------------------------------------------

        void
        Parameters::set_number_of_elements_per_dimension(
                const luint & aElementsX,
                const luint & aElementsY,
                const luint & aElementsZ )
        {
            // test if calling this function is allowed
            this->error_if_locked("set_number_of_elements_per_dimension");

            mNumberOfElementsPerDimension.set_size( 3, 1 );
            mNumberOfElementsPerDimension( 0 ) = aElementsX;
            mNumberOfElementsPerDimension( 1 ) = aElementsY;
            mNumberOfElementsPerDimension( 2 ) = aElementsZ;

            // auto setting for dimensions and offset
            this->set_default_dimensions_and_offset();
        }

//--------------------------------------------------------------------------------

       void
       Parameters::set_default_dimensions_and_offset()
       {
           // test if calling this function is allowed
           this->error_if_locked("set_default_dimensions_and_offset");

           auto tNumberOfDimensions = mNumberOfElementsPerDimension.length();

           // auto set for domain dimensions
           if ( mDomainDimensions.length() == 0 )
           {
               mDomainDimensions.set_size( tNumberOfDimensions, 1, 1.0 );
           }

           // auto set offset
           if ( mDomainOffset.length() == 0 )
           {
               mDomainOffset.set_size( tNumberOfDimensions, 1, 0.0 );
           }

       }
//--------------------------------------------------------------------------------

        void
        Parameters::set_domain_dimensions( const Matrix< DDRMat > & aDomainDimensions )
        {
            // test if calling this function is allowed
            this->error_if_locked("set_domain_dimensions");


            // check sanity of input
            MORIS_ERROR(
                    aDomainDimensions.length() == 2 ||
                    aDomainDimensions.length() == 3,
                    "Domain Dimensions must be a matrix of length 2 or 3.");

            MORIS_ERROR(
                    aDomainDimensions.max() > 0.0,
                    "Domain Dimensions be greater than zero");

            mDomainDimensions = aDomainDimensions;
        }

//--------------------------------------------------------------------------------

        void
        Parameters::set_domain_dimensions(
                const real & aDomainDimensionsX,
                const real & aDomainDimensionsY )
        {
            // test if calling this function is allowed
            this->error_if_locked("set_domain_dimensions");


            // check sanity of input
            MORIS_ERROR( aDomainDimensionsX > 0.0,
                        "aDomainDimensionsX must be greater than zero");

            MORIS_ERROR( aDomainDimensionsY > 0.0,
                         "aDomainDimensionsY must be greater than zero");

            mDomainDimensions.set_size( 2, 1 );
            mDomainDimensions( 0 ) = aDomainDimensionsX;
            mDomainDimensions( 1 ) = aDomainDimensionsY;
        }

//--------------------------------------------------------------------------------

        void
        Parameters::set_domain_dimensions(
                const real & aDomainDimensionsX,
                const real & aDomainDimensionsY,
                const real & aDomainDimensionsZ)
        {
            // test if calling this function is allowed
            this->error_if_locked("set_domain_dimensions");


            // check sanity of input
            MORIS_ERROR( aDomainDimensionsX > 0.0,
                    "aDomainDimensionsX must be greater than zero");

            MORIS_ERROR( aDomainDimensionsY > 0.0,
                    "aDomainDimensionsY must be greater than zero");

            MORIS_ERROR( aDomainDimensionsZ > 0.0,
                         "aDomainDimensionsZ must be greater than zero");

            mDomainDimensions.set_size( 3, 1 );
            mDomainDimensions( 0 ) = aDomainDimensionsX;
            mDomainDimensions( 1 ) = aDomainDimensionsY;
            mDomainDimensions( 2 ) = aDomainDimensionsZ;
        }

//--------------------------------------------------------------------------------

        void
        Parameters::set_domain_offset( const Matrix< DDRMat > & aDomainOffset )
        {
            // test if calling this function is allowed
            this->error_if_locked("set_domain_offset");

            // check sanity of input
            MORIS_ERROR(
                    aDomainOffset.length() == 2 ||
                    aDomainOffset.length() == 3,
                    "Domain Offset must be a matrix of length 2 or 3.");

            mDomainOffset = aDomainOffset;
        }

//--------------------------------------------------------------------------------

        void
        Parameters::set_domain_offset(
                const real & aDomainOffsetX,
                const real & aDomainOffsetY )
        {
            // test if calling this function is allowed
            this->error_if_locked("set_domain_offset");

            mDomainOffset.set_size( 2, 1 );
            mDomainOffset( 0 ) = aDomainOffsetX;
            mDomainOffset( 1 ) = aDomainOffsetY;
        }

//--------------------------------------------------------------------------------

        void
        Parameters::set_domain_offset(
                const real & aDomainOffsetX,
                const real & aDomainOffsetY,
                const real & aDomainOffsetZ )
        {
            // test if calling this function is allowed
            this->error_if_locked("set_domain_offset");

            mDomainOffset.set_size( 3, 1 );
            mDomainOffset( 0 ) = aDomainOffsetX;
            mDomainOffset( 1 ) = aDomainOffsetY;
            mDomainOffset( 2 ) = aDomainOffsetZ;
        }

//--------------------------------------------------------------------------------

        Matrix< DDLUMat >
        Parameters::get_domain_ijk() const
        {
            // ask settings for number of dimensions
            auto tNumberOfDimensions = get_number_of_dimensions();

            // calculate padding size
            auto tPaddingSize = get_padding_size();

            // allocate output matrix
            Matrix< DDLUMat > aDomain( 2, tNumberOfDimensions );

            // write beginning and ending of ijk domain in output matrix
            for ( uint k=0; k<tNumberOfDimensions; ++k )
            {
                aDomain( 0, k ) = tPaddingSize;
                aDomain( 1, k ) = aDomain( 0, k )
                        + mNumberOfElementsPerDimension( k ) - 1;
            }

            return aDomain;
        }

//--------------------------------------------------------------------------------

        /**
         * returns with, height and length of specified domain
         *
         * @return Matrix< DDRMat >
         */
        Matrix< DDRMat >
        Parameters::get_domain_dimensions() const
        {
            // see if dimensions have been set
            if( mDomainDimensions.length() != 0 )
            {
                // return user defined dimensions
                return mDomainDimensions;
            }
            else
            {
                // use default setting:

                // dimensions
                uint tNumberOfDimensions
                    = mNumberOfElementsPerDimension.length();

                // return defalult values
                Matrix< DDRMat > aDimensions( tNumberOfDimensions, 1 );

                // loop over all dimensions
                for( uint k=0; k<tNumberOfDimensions; ++k )
                {
                    // cast element number to real
                    aDimensions(k) = ( real ) mNumberOfElementsPerDimension( k );
                }

                // return domain so that element length equals unity
                return aDimensions;
            }
        }

//-------------------------------------------------------------------------------

        /**
         * sets the patterns for the Lagrange Meshes
         */
        void
        Parameters::set_lagrange_patterns( const Matrix< DDUMat > & aPatterns )
        {
            // test if calling this function is allowed
            this->error_if_locked("set_lagrange_patterns");

            // test sanity of input
            MORIS_ERROR( aPatterns.length() == mLagrangeOrders.length(),
                    "set_lagrange_patterns() : referred refinement pattern does not exist. Call set_lagrange_orders() first." );

            mLagrangePatterns = aPatterns;
        }

//-------------------------------------------------------------------------------

        /**
         * sets the patterns for the Lagrange Meshes
         */
        void
        Parameters::set_bspline_patterns( const Matrix< DDUMat > & aPatterns )
        {
            // test if calling this function is allowed
            this->error_if_locked("set_bspline_patterns");

            // test sanity of input
            MORIS_ERROR( aPatterns.length() == mBSplineOrders.length(),
                    "set_bspline_patterns() : referred refinement pattern does not exist. Call set_bspline_orders() first." );

            mBSplinePatterns = aPatterns;
        }
// -----------------------------------------------------------------------------

        void
        Parameters::set_mesh_orders_simple( const uint & aMaxOrder )
        {
            // test if calling this function is allowed
            this->error_if_locked( "set_mesh_orders_simple" );

            Matrix< DDUMat > tOrder( 1, 1, aMaxOrder );

            this->set_mesh_orders( tOrder, tOrder );
        }

//--------------------------------------------------------------------------------

        void
        Parameters::set_mesh_orders(
                          const Matrix< DDUMat > & aBSplineOrders,
                          const Matrix< DDUMat > & aLagrangeOrders )
        {

            // test if calling this function is allowed
            this->error_if_locked( "set_mesh_orders" );

            Matrix< DDUMat > tBSplineOrders;
            Matrix< DDUMat > tLagrangeOrders;

            // step 1: make both orders unique
            unique( aBSplineOrders, tBSplineOrders );
            unique( aLagrangeOrders, tLagrangeOrders );

            // step 2: make sure that input is sane
            MORIS_ERROR( tBSplineOrders.min() > 0,
                    "Error in input, zero order B-Spline is not supported" );

            MORIS_ERROR( tBSplineOrders.max() <= 3,
                               "Error in input, B-Spline orders above 3 are not supported" );

            MORIS_ERROR( tLagrangeOrders.min() > 0,
                    "Error in input, zero order Lagrange is not supported" );

            MORIS_ERROR( tLagrangeOrders.max() <= 3,
                    "Error in input, B-Lagrange orders above 3 are not supported" );

            // special case for cubic output
            bool tHaveCubicLagrange = tLagrangeOrders.max() == 3;

            // step 2: number of meshes
            uint tNumberOfBSplineMeshes = tBSplineOrders.length();
            uint tNumberOfLagrangeMeshes = tLagrangeOrders.length();

            // step 3 : allocate B-Spline orders and patterns
            mBSplineOrders.set_size( 2*tNumberOfBSplineMeshes, 1 );
            mBSplinePatterns.set_size( 2*tNumberOfBSplineMeshes, 1 );

            // this map links orders with input B-Spline mesh
            mBSplineInputMap.set_size( 4, 1, MORIS_UINT_MAX );

            // this map links orders with output B-Spline mesh
            mBSplineOutputMap.set_size( 4, 1, MORIS_UINT_MAX );

            for( uint k=0; k<tNumberOfBSplineMeshes; ++k )
            {
                mBSplineOrders( k ) = tBSplineOrders( k );
                mBSplinePatterns( k ) = this->get_input_pattern();
                mBSplineInputMap( tBSplineOrders( k ) ) = k;

                mBSplineOrders( k+tNumberOfBSplineMeshes ) = tBSplineOrders( k );
                mBSplinePatterns( k+tNumberOfBSplineMeshes ) = this->get_output_pattern();
                mBSplineOutputMap( tBSplineOrders( k ) ) = k+tNumberOfBSplineMeshes;
            }

            // step 4: allocate Lagrange orders
            mUnionMeshes.set_size( tLagrangeOrders.max(), 1, MORIS_UINT_MAX );

            if( tHaveCubicLagrange )
            {
                mLagrangeOrders.set_size( 3*tNumberOfLagrangeMeshes + 1, 1 );
                mLagrangePatterns.set_size( 3*tNumberOfLagrangeMeshes + 1, 1 );

                mRefinedOutputMesh = 3*tNumberOfLagrangeMeshes;
                mLagrangeOrders( mRefinedOutputMesh ) = 2;

                // special pattern for output
                mLagrangePatterns( mRefinedOutputMesh ) = this->get_refined_output_pattern();
            }
            else
            {
                mLagrangeOrders.set_size( 3*tNumberOfLagrangeMeshes, 1 );
                mLagrangePatterns.set_size( 3*tNumberOfLagrangeMeshes, 1 );
                mRefinedOutputMesh = MORIS_UINT_MAX;
            }
            for( uint k=0; k<tNumberOfLagrangeMeshes; ++k )
            {
                mLagrangeOrders( k ) = tLagrangeOrders( k );
                mLagrangePatterns( k ) = this->get_input_pattern();
                mLagrangeOrders( k+tNumberOfLagrangeMeshes ) = tLagrangeOrders( k );
                mLagrangePatterns( k+tNumberOfLagrangeMeshes ) = this->get_output_pattern();
                mLagrangeOrders( k+2*tNumberOfLagrangeMeshes ) = tLagrangeOrders( k );
                mLagrangePatterns( k+2*tNumberOfLagrangeMeshes ) = this->get_union_pattern();
                mUnionMeshes( k ) = k+2*tNumberOfLagrangeMeshes;
            }

            // set value for padding
            mMaxPolynomial = std::max( mLagrangeOrders.max(), mBSplineOrders.max() );

            // overwrite buffer
            if( mBSplineTruncationFlag )
            {
                mBufferSize = std::max( mBufferSize, mMaxPolynomial );
            }
        }

//--------------------------------------------------------------------------------

        void
        Parameters::check_sanity() const
        {
            if ( par_rank() == 0 )
            {


                // get dimensions
                auto tNumberOfDimensions = this->get_number_of_dimensions();

                // check dimensions
                MORIS_ERROR(
                        mNumberOfElementsPerDimension.length() == tNumberOfDimensions,
                        "Number of Elements Per Dimension does not match" );

                MORIS_ERROR(
                        mDomainDimensions.length() == tNumberOfDimensions,
                        "Domain dimensions and Number of Elements per dimension do not match");

                MORIS_ERROR(
                        mDomainOffset.length() == tNumberOfDimensions,
                        "Domain offset and Number of Elements per dimension do not match");


                // get number of B-Spline meshes
                auto tNumberOfBSplineMeshes = mBSplineOrders.length();

                MORIS_ERROR(
                        mBSplinePatterns.length() == tNumberOfBSplineMeshes,
                        "B-Spline pattern list does not match number of B-Splines" );

                // get number of Lagrange meshes
                auto tNumberOfLagrangeMeshes = mLagrangeOrders.length();

                MORIS_ERROR(
                        mLagrangePatterns.length() == tNumberOfLagrangeMeshes,
                        "Lagrange pattern list does not match number of Lagrange meshes" );
            }
        }

//--------------------------------------------------------------------------------

        void
        Parameters::string_to_mat( const std::string & aString, Matrix< DDRMat > & aMat ) const
        {

            uint tCount = std::count( aString.begin(), aString.end(), ',') + 1;

            std::string tString( aString );

            // allocate memory
            aMat.set_size( tCount, 1 );

            // reset counter
            tCount = 0;

            // reset position
            size_t tPos = 0;

            // reset string
            tString = aString;


            while( tPos < tString.size() )
            {
                // find string
                tPos = tString.find( "," );

                // copy value into output matrix
                if( tPos <  tString.size() )
                {
                    aMat( tCount++ ) = stod(  tString.substr( 0, tPos ) );
                    tString =  tString.substr( tPos+1, tString.size() );
                }

            }
            // copy value into output matrix
            aMat( tCount++ ) = stod( tString );
        }

//--------------------------------------------------------------------------------

        void
        Parameters::string_to_mat( const std::string & aString, Matrix< DDUMat > & aMat ) const
        {
            std::string tString( aString );

            uint tCount = std::count( aString.begin(), aString.end(), ',') + 1;

            // allocate memory
            aMat.set_size( tCount, 1 );

            // reset counter
            tCount = 0;

            // reset position
            size_t tPos = 0;

            // reset string
            tString = aString;


            while( tPos < tString.size() )
            {
                // find string
                tPos = tString.find( "," );

                // copy value into output matrix
                if( tPos <  tString.size() )
                {
                    aMat( tCount++ ) = stoi(  tString.substr( 0, tPos ) );
                    tString =  tString.substr( tPos+1, tString.size() );
                }

            }
            // copy value into output matrix
            aMat( tCount++ ) = stoi( tString );
        }

//--------------------------------------------------------------------------------

        void
        Parameters::string_to_mat( const std::string & aString, Matrix< DDLUMat > & aMat ) const
        {
            std::string tString( aString );

            uint tCount = std::count( aString.begin(), aString.end(), ',') + 1;

            // allocate memory
            aMat.set_size( tCount, 1 );

            // reset counter
            tCount = 0;

            // reset position
            size_t tPos = 0;

            // reset string
            tString = aString;


            while( tPos < tString.size() )
            {
                // find string
                tPos = tString.find( "," );

                // copy value into output matrix
                if( tPos <  tString.size() )
                {
                    aMat( tCount++ ) = stoi(  tString.substr( 0, tPos ) );
                    tString =  tString.substr( tPos+1, tString.size() );
                }

            }
            // copy value into output matrix
            aMat( tCount++ ) = stoi( tString );
        }
//--------------------------------------------------------------------------------

    } /* namespace hmr */
} /* namespace moris */
