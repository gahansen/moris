
#include "cl_Matrix.hpp" //LNA/src
#include "linalg_typedefs.hpp" //LNA/src
#include "fn_inv.hpp" //LNA/src
#include "fn_det.hpp" //LNA/src
#include "fn_trans.hpp"
#include "fn_norm.hpp"
#include "fn_reshape.hpp"
#include "op_times.hpp" //LNA/src
#include "op_equal_equal.hpp" //LNA/src

#include "cl_FEM_Field_Interpolator.hpp" //FEM/INT/src

namespace moris
{
    namespace fem
    {

//------------------------------------------------------------------------------

        Field_Interpolator::Field_Interpolator( const uint               & aNumberOfFields,
                                                const Interpolation_Rule & aFieldInterpolationRule,
                                                Geometry_Interpolator    & aGeometryInterpolator )
                                              : mNumberOfFields( aNumberOfFields )
        {
            // create a spaceOnlyflag ( true if space interpolation only )
            mSpaceOnlyFlag = false;
            if ( aFieldInterpolationRule.get_time_interpolation_order() == mtk::Interpolation_Order::CONSTANT)
            {
                mSpaceOnlyFlag = true;
            }

            // create space and time interpolation function
            mSpaceInterpolation = aFieldInterpolationRule.create_space_interpolation_function();
            mTimeInterpolation  = aFieldInterpolationRule.create_time_interpolation_function();

            // set the geometry interpolator
            mGeometryInterpolator = & aGeometryInterpolator;

            //get number of space, time dimensions
            mNSpaceDim = mSpaceInterpolation->get_number_of_dimensions();
            mNTimeDim  = mTimeInterpolation->get_number_of_dimensions();

            //check dimension consistency
            MORIS_ERROR( ( mNSpaceDim == mGeometryInterpolator->get_number_of_space_dimensions() ) ,
                         "Field_Interpolator - Space dimension inconsistency." );
            MORIS_ERROR( ( mNTimeDim  == mGeometryInterpolator->get_number_of_time_dimensions() ),
                         "Field_Interpolator - Time dimension inconsistency.");

            //get number of space, time, and space time basis
            mNSpaceBases = mSpaceInterpolation->get_number_of_bases();
            mNTimeBases  = mTimeInterpolation->get_number_of_bases();
            mNFieldBases = mNSpaceBases*mNTimeBases;

            // set default xi, tau
            mXi.set_size( mNSpaceDim, 1, 0.0 );
            mTau.set_size( mNTimeDim, 1, 0.0 );

            //set default uHat
            mUHat.set_size( mNFieldBases, mNumberOfFields, 0.0 );
        }

//------------------------------------------------------------------------------

        Field_Interpolator::~Field_Interpolator()
        {
            if( mSpaceInterpolation != NULL )
            {
                delete mSpaceInterpolation;
            }
            if( mTimeInterpolation != NULL )
            {
                delete mTimeInterpolation;
            }
        }

//------------------------------------------------------------------------------

        void Field_Interpolator::set_space_time( const Matrix< DDRMat > & aXi,
                                                 const Matrix< DDRMat > & aTau )
        {
            // check this is a space time interpolation
            MORIS_ERROR( !mSpaceOnlyFlag,
                         "Field_Interpolator - set_space_time - space only.");

            // check input size aXi
            MORIS_ASSERT( ( ( aXi.n_cols() == mXi.n_cols() ) && ( aXi.n_rows() == mXi.n_rows() )),
                          "Field_Interpolator - set_space_time - Wrong input size (aXi).");

            // check input size aXi
            MORIS_ASSERT( ( ( aTau.n_cols() == mTau.n_cols() ) && ( aTau.n_rows() == mTau.n_rows() )),
                          "Field_Interpolator - set_space_time - Wrong input size (aTau).");

            //check input values are between -1 and 1 for aXi
            for ( moris::uint Ik = 0; Ik < mXi.n_cols(); Ik++ )
            {
                MORIS_ASSERT( ( ( aXi(Ik) <= 1 ) && ( aXi(Ik) >= -1 )),
                             "Field_Interpolator - set_space_time - Wrong input value (aXi).");
            }

            // check input values are between -1 and 1 for aTau
            for ( moris::uint Ik = 0; Ik < mTau.n_cols(); Ik++ )
            {
                MORIS_ASSERT( ( ( aTau(Ik) <= 1 ) && ( aTau(Ik) >= -1 )),
                             "Field_Interpolator - set_space_time - Wrong input value (aTau).");
            }

            // set input value
             mXi  = aXi;
             mTau = aTau;
        }

//------------------------------------------------------------------------------

        void Field_Interpolator::set_space( const Matrix< DDRMat > & aXi)
        {
            // check input size aXi
            MORIS_ASSERT( ( ( aXi.n_cols() == mXi.n_cols() ) && ( aXi.n_rows() == mXi.n_rows() )),
                          "Field_Interpolator - set_space_time - Wrong input size (aXi).");

            //check input values are between -1 and 1 for aXi
            for ( moris::uint Ik = 0; Ik < mXi.n_cols(); Ik++ )
            {
                MORIS_ASSERT( ( ( aXi(Ik) <= 1 ) && ( aXi(Ik) >= -1 )),
                             "Field_Interpolator - set_space_time - Wrong input value (aXi).");
            }

            // set input value
            mXi  = aXi;
        }

//------------------------------------------------------------------------------

        void Field_Interpolator::set_coeff( const Matrix< DDRMat > & aUHat )
        {
            //check the input size
            MORIS_ASSERT( ( ( aUHat.n_cols() == mUHat.n_cols() ) && ( aUHat.n_rows() == mUHat.n_rows() )),
                          "Field_Interpolator - set_coeff - Wrong input size (aUHat).");

            // set the coefficients
            mUHat = aUHat;
        }

//------------------------------------------------------------------------------

         Matrix < DDRMat> Field_Interpolator::N()
         {
             //evaluate space and time SF at Xi, Tau
             Matrix < DDRMat > tNSpace = mSpaceInterpolation->eval_N( mXi );
             Matrix < DDRMat > tNTime  = mTimeInterpolation->eval_N( mTau );

             //evaluate space time SF by multiplying space and time SF
             Matrix < DDRMat > tNField = reshape( trans( tNSpace ) * tNTime, 1, mNFieldBases);
             return tNField;

         }
//------------------------------------------------------------------------------

        Matrix< DDRMat > Field_Interpolator::Bx()
        {
            // evaluate dNSpacedXi for the field time interpolation and transpose
            Matrix< DDRMat> tdNSpacedXi = mSpaceInterpolation->eval_dNdXi( mXi );
            tdNSpacedXi = trans( tdNSpacedXi );

            // evaluate NTime for the field time interpolation
            Matrix < DDRMat > tNTime  = mTimeInterpolation->eval_N( mTau );

            // set size dNFielddXi for the field
            Matrix< DDRMat> tdNFielddXi ( mNSpaceDim, mNFieldBases );

            // build the space time dNFielddXi row by row
            for ( moris::uint Ik = 0; Ik < mNSpaceDim; Ik++ )
            {
                tdNFielddXi.get_row(Ik) = reshape( tdNSpacedXi.get_column(Ik) * tNTime , 1, mNFieldBases );
            }

            // evaluate the space Jacobian from the geometry interpolator
            Matrix< DDRMat > tdNGeodXi = mGeometryInterpolator->dNdXi( mXi );
            Matrix< DDRMat > tJGeot    = mGeometryInterpolator->space_jacobian( tdNGeodXi );

            // compute first derivative of the SF wrt x
            Matrix< DDRMat> tdNFielddx( mNSpaceDim, mNFieldBases );
            tdNFielddx = inv( tJGeot ) * tdNFielddXi;
            return tdNFielddx;
        }

//------------------------------------------------------------------------------

        Matrix< DDRMat > Field_Interpolator::eval_d2Ndx2()
        {
            // get first and second derivatives of space SF wrt xi
            Matrix< DDRMat > tdNGeodxi   = mGeometryInterpolator->dNdXi( mXi );
            Matrix< DDRMat > td2NGeodxi2 = mGeometryInterpolator->d2NdXi2( mXi );

            // get matrices for second space derivatives from geometry interpolator
            Matrix< DDRMat > tJGeot, tKGeot, tLGeot;
            mGeometryInterpolator->space_jacobian_and_matrices_for_second_derivatives( tJGeot,
                                                                                       tKGeot,
                                                                                       tLGeot,
                                                                                       tdNGeodxi,
                                                                                       td2NGeodxi2 );

            // get the derivatives of the space time SF wrt x
            Matrix< DDRMat > tdNFielddx = this->Bx();

            // evaluate N for the field time interpolation
            Matrix< DDRMat > tNTime = mTimeInterpolation->eval_N( mTau );

            // evaluate d2Ndxi2 for the field space interpolation
            Matrix< DDRMat > td2NSpacedxi2 = mSpaceInterpolation->eval_d2NdXi2( mXi );
            td2NSpacedxi2 = trans( td2NSpacedxi2 );

            // get the number of rows for td2NFielddxi2
            uint tNSecondDerivatives = td2NGeodxi2.n_rows();

            // compute td2NFielddxi2 row by row
            Matrix< DDRMat > td2NFielddxi2( tNSecondDerivatives, mNFieldBases );
            for ( moris::uint Ik = 0; Ik < tNSecondDerivatives; Ik++ )
            {
                td2NFielddxi2.get_row( Ik ) = reshape( td2NSpacedxi2.get_column(Ik) * tNTime , 1, mNFieldBases );
            }

            //build the second derivatives of the space time SF wrt x
            Matrix< DDRMat > td2NFielddx2 = inv( tLGeot ) * ( td2NFielddxi2 - tKGeot * tdNFielddx );
            return td2NFielddx2;
        }
//------------------------------------------------------------------------------

        Matrix< DDRMat > Field_Interpolator::Bt()
        {
            // check this is a space time interpolation
            MORIS_ERROR( !mSpaceOnlyFlag,
                         "Field_Interpolator - Bt - space only.");

            //set first derivative of SF wrt t matrix
            Matrix< DDRMat > tdNFielddt( mNTimeDim, mNFieldBases );

            // evaluate dNdTau for the field time interpolation
            Matrix< DDRMat > tdNTimedTau = mTimeInterpolation->eval_dNdXi( mTau );

            // evaluate N for the field space interpolation
            Matrix < DDRMat > tNSpace = mSpaceInterpolation->eval_N( mXi );

            // build the space time dNdXi row by row
            tNSpace = trans(tNSpace);
            for ( moris::uint Ik = 0; Ik < mNTimeDim; Ik++ )
            {
                 tdNFielddt.get_row(Ik) = reshape( tNSpace * tdNTimedTau.get_row(Ik), 1, mNFieldBases);
            }

            // evaluate the Jacobian from the space geometry interpolator
            Matrix< DDRMat > tdNGeodTau = mGeometryInterpolator->dNdTau( mTau );
            Matrix< DDRMat > tJGeot = mGeometryInterpolator->time_jacobian( tdNGeodTau );

            // transform output matrix to dNdX
            tdNFielddt = inv( tJGeot ) * tdNFielddt;
            return tdNFielddt;
        }

//------------------------------------------------------------------------------

        Matrix< DDRMat > Field_Interpolator::eval_d2Ndt2()
        {
            // check this is a space time interpolation
            MORIS_ERROR( !mSpaceOnlyFlag,
                         "Field_Interpolator - eval_d2Ndt2 - space only.");

            //set second derivative of SF wrt t matrix
            Matrix< DDRMat > d2NFielddt2;

            // get first and second derivatives of space SF wrt tau
            Matrix< DDRMat > tdNGeodtau   = mGeometryInterpolator->dNdTau( mTau );
            Matrix< DDRMat > td2NGeodtau2 = mGeometryInterpolator->d2NdTau2( mTau );

            // get matrices for second derivatives from space geometry interpolator
            Matrix< DDRMat > tJGeot, tKGeot, tLGeot;
            mGeometryInterpolator->time_jacobian_and_matrices_for_second_derivatives( tJGeot,
                                                                                      tKGeot,
                                                                                      tLGeot,
                                                                                      tdNGeodtau,
                                                                                      td2NGeodtau2);

            // get the derivatives of the space time SF wrt t
            Matrix< DDRMat > tdNFielddt = this->Bt();

            //get the second derivatives of the space time SF wrt tau

            // get N for the field space interpolation and transpose
            Matrix< DDRMat > tNSpace       = mSpaceInterpolation->eval_N( mXi );
            tNSpace = trans( tNSpace );

            // get d2Ndtau2 for the field time interpolation
            Matrix< DDRMat > td2NTimedtau2 = mTimeInterpolation->eval_d2NdXi2( mTau );

            // get the number of rows for td2NFielddtau2
            uint tNSecondDerivatives = td2NGeodtau2.n_rows();

            // compute second derivatives of the space time SF wrt tau row by row
            Matrix< DDRMat > td2NFielddtau2( tNSecondDerivatives, mNFieldBases );
            for ( moris::uint Ik = 0; Ik < tNSecondDerivatives; Ik++ )
            {
                td2NFielddtau2.get_row(Ik) = reshape( tNSpace * td2NTimedtau2.get_row(Ik) , 1, mNFieldBases );
            }

            //build the second derivatives of the space time SF wrt t
            d2NFielddt2 = inv( tLGeot ) * (td2NFielddtau2 - tKGeot * tdNFielddt);
            return d2NFielddt2;
        }
//------------------------------------------------------------------------------

        Matrix< DDRMat > Field_Interpolator::val()
        {
            // evaluate the space time shape functions at Xi, Tau
            Matrix< DDRMat > tNField = this->N();

            //evaluate the field
            return tNField * mUHat ;
        }

//------------------------------------------------------------------------------

        Matrix< DDRMat > Field_Interpolator::gradx( const uint & aDerivativeOrder )
        {
            switch ( aDerivativeOrder )
            {
                case( 1 ) :
                {
                    // evaluate the first space derivative of the shape functions at xi, tau
                    Matrix< DDRMat > tdNFielddx = this->Bx();

                    //evaluate the field space derivative
                    return tdNFielddx * mUHat ;
                    break;
                }
                case ( 2 ) :
                {
                    // evaluate the second space derivative of the shape functions at xi, tau
                    Matrix< DDRMat > td2NFielddx2 = this->eval_d2Ndx2();

                    //evaluate the field space derivative
                    return td2NFielddx2 * mUHat ;
                    break;
                }
                default :
                {
                    MORIS_ERROR( false, "Field_Interpolator - gradx - Derivative order not implemented." );
                    Matrix< DDRMat > tEmpty;
                    return tEmpty;
                    break;
                }
            }
        }

//------------------------------------------------------------------------------

        Matrix< DDRMat > Field_Interpolator::gradt( const uint & aDerivativeOrder )
        {
            // check this is a space time interpolation
            MORIS_ERROR( !mSpaceOnlyFlag,
                         "Field_Interpolator - gradt - space only.");

            switch ( aDerivativeOrder )
            {
                case( 1 ) :
                {
                    // evaluate the first space derivative of the shape functions at xi, tau
                    Matrix< DDRMat > tdNFdt = this->Bt();

                    //evaluate the field space derivative
                    return tdNFdt * mUHat ;
                    break;
                }
                case ( 2 ) :
                {
                    // evaluate the second space derivative of the shape functions at xi, tau
                    Matrix< DDRMat > td2NFdt2 = this->eval_d2Ndt2();

                    //evaluate the field space derivative
                    return td2NFdt2 * mUHat ;
                    break;
                }
                default :
                {
                    MORIS_ERROR( false, "Field_Interpolator - gradt - Derivative order not implemented." );
                    Matrix< DDRMat > tEmpty;
                    return tEmpty;
                    break;
                }
            }
        }
//------------------------------------------------------------------------------


    } /* namespace fem */
} /* namespace moris */

