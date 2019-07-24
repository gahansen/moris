
#include "cl_FEM_IWG_Isotropic_Spatial_Diffusion_Ghost.hpp"
#include "fn_trans.hpp"
#include "fn_eye.hpp"
#include "fn_dot.hpp"

namespace moris
{
    namespace fem
    {
//------------------------------------------------------------------------------

        IWG_Isotropic_Spatial_Diffusion_Ghost::IWG_Isotropic_Spatial_Diffusion_Ghost()
        {
            // set the residual dof type
            mResidualDofType = { MSI::Dof_Type::TEMP };

            // set the active dof type
            mActiveDofTypes = { { MSI::Dof_Type::TEMP } };

            // FIXME set a penalty
            mGammaGhost = 1.0;

            // FIXME set mesh parameter
            // Mesh parameter or parameters which it depends on must be fed to IWG from outside
            mMeshParameter = 1;

            // FIXME set order of Shape functions
            // Order must be fed to IWG from outside
            mOrder = 3;

            //FIXME forced diffusion parameter
            //      forced dimensions for 3D
            eye( mSpaceDim, mSpaceDim, mKappa );
            mKappa = 1.0 * mKappa;
        }

//------------------------------------------------------------------------------

        void IWG_Isotropic_Spatial_Diffusion_Ghost::compute_residual( Matrix< DDRMat >            & aResidual,
                                                                      Cell< Field_Interpolator* > & aLeftFieldInterpolators,
                                                                      Cell< Field_Interpolator* > & aRightFieldInterpolators )
        {
            // check, if order of shape functions is supported
            MORIS_ERROR( mOrder < 4, " Ghost stabilization for this order of shape fncts. not supported yet. " );

            // set field interpolators for left and right
            Field_Interpolator* tTemp_Left  = aLeftFieldInterpolators( 0 );
            Field_Interpolator* tTemp_Right = aRightFieldInterpolators( 0 );

            // compute the residual r_T
            uint tResSize_Left  = tTemp_Left ->get_number_of_space_time_coefficients();
            uint tResSize_Right = tTemp_Right->get_number_of_space_time_coefficients();

            // need a residual that has the size of the two IP elements combined tResSize = tResSize_Left + tResSize_Right
            aResidual.set_size( tResSize_Left + tResSize_Right, 1, 0.0);

            // --------- Ghost for linear shape functions ----------------------------------------------------------------

            // assemble matrix containing both left and right shape functions and their derivatives wrt. (x,y,z)

            // get derivatives from left and right shape functions
            Matrix <DDRMat> tBx_Left = tTemp_Left->Bx();
            uint tNumOfShapeFunctions_Left = tBx_Left.n_cols();

            Matrix <DDRMat> tBx_Right = tTemp_Right->Bx();
            uint tNumOfShapeFunctions_Right = tBx_Right.n_cols();

            // put left and right B-Matrices next to each other in Block matrix Bx_comined = [Bx_L, Bx_R]
            Matrix <DDRMat> tBx_combined( 3, tNumOfShapeFunctions_Left + tNumOfShapeFunctions_Right, 0.0 );
            for(uint i = 0; i < tNumOfShapeFunctions_Left; i++ )
            {
                tBx_combined( 0, i ) = tBx_Left( 0, i );
                tBx_combined( 1, i ) = tBx_Left( 1, i );
                tBx_combined( 2, i ) = tBx_Left( 2, i );
            }
            for(uint i = 0; i < tNumOfShapeFunctions_Right; i++)
            {
                tBx_combined( 0, tNumOfShapeFunctions_Left + i ) = - tBx_Right( 0, i );
                tBx_combined( 1, tNumOfShapeFunctions_Left + i ) = - tBx_Right( 1, i );
                tBx_combined( 2, tNumOfShapeFunctions_Left + i ) = - tBx_Right( 2, i );
            }

            // create vector containing jump in gradient
            Matrix <DDRMat> tGradX_combined = tTemp_Left->gradx( 1 ) - tTemp_Right->gradx( 1 );

            // compute residual ---------------
                aResidual = aResidual
                          + mGammaGhost * mMeshParameter // * mKappa                                // scaling parameters
                          * trans( tBx_combined ) * mNormal * trans( mNormal ) * tGradX_combined;   // matrices & vectors


            // --------- Ghost for quadratic shape functions -------------------------------------------------------------
            if ( mOrder >= 2 )
            {
                // assemble matrix containing both left and right shape functions and their 2nd derivatives wrt. (x,y,z)

                // get derivatives from left and right shape functions
                Matrix <DDRMat> tB2x_Left = tTemp_Left->eval_d2Ndx2();
                uint tNumOfShapeFunctions_Left = tB2x_Left.n_cols();

                Matrix <DDRMat> tB2x_Right = tTemp_Right->eval_d2Ndx2();
                uint tNumOfShapeFunctions_Right = tB2x_Right.n_cols();

                // create combined B-Matrix, put left and right B2x*n next to each other B2x_comined = [B2x_L, -B2x_R]
                Matrix <DDRMat> tB2x_combined( 6, tNumOfShapeFunctions_Left + tNumOfShapeFunctions_Right, 0.0 );

                // assemble into combined matrix
                for(uint i = 0; i < tNumOfShapeFunctions_Left; i++ )
                {
                    tB2x_combined( 0, i ) = tB2x_Left( 0, i );
                    tB2x_combined( 1, i ) = tB2x_Left( 1, i );
                    tB2x_combined( 2, i ) = tB2x_Left( 2, i );
                    tB2x_combined( 3, i ) = tB2x_Left( 3, i );
                    tB2x_combined( 4, i ) = tB2x_Left( 4, i );
                    tB2x_combined( 5, i ) = tB2x_Left( 5, i );
                }

                // assemble into combined matrix
                for(uint i = 0; i < tNumOfShapeFunctions_Right; i++ )
                {
                    tB2x_combined( 0, tNumOfShapeFunctions_Left + i ) = - tB2x_Right( 0, i );
                    tB2x_combined( 1, tNumOfShapeFunctions_Left + i ) = - tB2x_Right( 1, i );
                    tB2x_combined( 2, tNumOfShapeFunctions_Left + i ) = - tB2x_Right( 2, i );
                    tB2x_combined( 3, tNumOfShapeFunctions_Left + i ) = - tB2x_Right( 3, i );
                    tB2x_combined( 4, tNumOfShapeFunctions_Left + i ) = - tB2x_Right( 4, i );
                    tB2x_combined( 5, tNumOfShapeFunctions_Left + i ) = - tB2x_Right( 5, i );
                }

                // assemble gradient vector
                Matrix <DDRMat> tGrad2X_combined = tTemp_Left->gradx( 2 ) - tTemp_Right->gradx( 2 );

                // get normal matrix
                Matrix<DDRMat> tNormalMatrix_2 = this->get_normal_matrix(2);

                // compute residual ---------------
                aResidual = aResidual
                          + mGammaGhost * ( std::pow( mMeshParameter,3 ) ) // * mKappa                              // scaling parameters (p=2)
                          * trans( tB2x_combined ) * trans( tNormalMatrix_2 ) * tNormalMatrix_2 * tGrad2X_combined; // matrices & vectors (p=2)
            }

            // --------- Ghost for cubic shape functions -------------------------------------------------------------
            if ( mOrder >= 3 )
            {
                // assemble matrix containing both left and right shape functions and their 3nd derivatives wrt. (x,y,z)

                // get derivatives from left and right shape functions
                Matrix <DDRMat> tB3x_Left = tTemp_Left->eval_d3Ndx3();
                uint tNumOfShapeFunctions_Left = tB3x_Left.n_cols();

                Matrix <DDRMat> tB3x_Right = tTemp_Right->eval_d3Ndx3();
                uint tNumOfShapeFunctions_Right = tB3x_Right.n_cols();

                // create combined B-Matrix, put left and right B2x*n next to each other B3x_comined = [B3x_L, -B3x_R]
                Matrix <DDRMat> tB3x_combined( 10, tNumOfShapeFunctions_Left + tNumOfShapeFunctions_Right, 0.0 );

                // assemble into combined matrix
                for( uint i = 0; i < tNumOfShapeFunctions_Left; i++ )
                {
                    tB3x_combined( 0, i ) = tB3x_Left( 0, i );
                    tB3x_combined( 1, i ) = tB3x_Left( 1, i );
                    tB3x_combined( 2, i ) = tB3x_Left( 2, i );
                    tB3x_combined( 3, i ) = tB3x_Left( 3, i );
                    tB3x_combined( 4, i ) = tB3x_Left( 4, i );
                    tB3x_combined( 5, i ) = tB3x_Left( 5, i );
                    tB3x_combined( 6, i ) = tB3x_Left( 6, i );
                    tB3x_combined( 7, i ) = tB3x_Left( 7, i );
                    tB3x_combined( 8, i ) = tB3x_Left( 8, i );
                    tB3x_combined( 9, i ) = tB3x_Left( 9, i );
                }

                // assemble into combined matrix
                for( uint i = 0; i < tNumOfShapeFunctions_Right; i++ )
                {
                    tB3x_combined( 0, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 0, i );
                    tB3x_combined( 1, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 1, i );
                    tB3x_combined( 2, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 2, i );
                    tB3x_combined( 3, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 3, i );
                    tB3x_combined( 4, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 4, i );
                    tB3x_combined( 5, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 5, i );
                    tB3x_combined( 6, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 6, i );
                    tB3x_combined( 7, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 7, i );
                    tB3x_combined( 8, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 8, i );
                    tB3x_combined( 9, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 9, i );
                }

                // assemble gradient vector
                 Matrix <DDRMat> tGrad3X_combined = tTemp_Left->gradx( 3 ) - tTemp_Right->gradx( 3 );

                // get normal matrix
                Matrix<DDRMat> tNormalMatrix_3 = this->get_normal_matrix( 3 );

                // compute residual ---------------
                aResidual = aResidual
                          + mGammaGhost * ( std::pow( mMeshParameter, 5 ) ) // * mKappa                             // scaling parameters (p=2)
                          * trans( tB3x_combined ) * trans( tNormalMatrix_3 ) * tNormalMatrix_3 * tGrad3X_combined; // matrices & vectors (p=2)
            }
        }

//------------------------------------------------------------------------------

        void IWG_Isotropic_Spatial_Diffusion_Ghost::compute_jacobian( Cell< Matrix< DDRMat > >    & aJacobians,
                                                                      Cell< Field_Interpolator* > & aLeftFieldInterpolators,
                                                                      Cell< Field_Interpolator* > & aRightFieldInterpolators )
        {
            // check, if order of shape functions is supported
            MORIS_ERROR( mOrder < 4, " IWG_Isotropic_Spatial_Diffusion_Ghost::compute_jacobian - Ghost stabilization for this order of shape fncts. not supported yet. " );

            // set field interpolators for left and right
            Field_Interpolator* tTemp_Left  = aLeftFieldInterpolators( 0 );
            Field_Interpolator* tTemp_Right = aRightFieldInterpolators( 0 );

            // set the jacobian size
            aJacobians.resize( 1 );

            // compute the jacobian j_T_T
            uint tNumOfBases_Left = tTemp_Left->get_number_of_space_time_bases();
            uint tNumOfBases_Right = tTemp_Right->get_number_of_space_time_bases();
            aJacobians( 0 ).set_size( tNumOfBases_Left + tNumOfBases_Right, tNumOfBases_Left + tNumOfBases_Right, 0.0 );

            // --------- Ghost for linear shape functions ----------------------------------------------------------------

            // assemble matrix containing both left and right shape functions and their derivatives wrt. (x,y,z)

            // get derivatives from left and right shape functions
            Matrix <DDRMat> tBx_Left = tTemp_Left->Bx();
            uint tNumOfShapeFunctions_Left = tBx_Left.n_cols();

            Matrix <DDRMat> tBx_Right = tTemp_Right->Bx();
            uint tNumOfShapeFunctions_Right = tBx_Right.n_cols();

            // put left and right B-Matrices next to each other in Block matrix Bx_comined = [Bx_L, Bx_R]
            Matrix <DDRMat> tBx_combined( 3, tNumOfShapeFunctions_Left + tNumOfShapeFunctions_Right, 0.0 );
            for( uint i = 0; i < tNumOfShapeFunctions_Left; i++ )
            {
                tBx_combined( 0, i ) = tBx_Left( 0, i );
                tBx_combined( 1, i ) = tBx_Left( 1, i );
                tBx_combined( 2, i ) = tBx_Left( 2, i );
            }
            for( uint i = 0; i < tNumOfShapeFunctions_Right; i++ )
            {
                tBx_combined( 0, tNumOfShapeFunctions_Left + i ) = - tBx_Right( 0, i );
                tBx_combined( 1, tNumOfShapeFunctions_Left + i ) = - tBx_Right( 1, i );
                tBx_combined( 2, tNumOfShapeFunctions_Left + i ) = - tBx_Right( 2, i );
            }

            // compute Jacobian ---------------
            aJacobians( 0 ) = aJacobians( 0 )
                            + mGammaGhost * mMeshParameter // * mKappa                           // scaling parameters
                            * trans( tBx_combined ) * mNormal * trans( mNormal ) * tBx_combined; // matrices & vectors

            // --------- Ghost for quadratic shape functions -------------------------------------------------------------
            if (mOrder >= 2)
            {
                // assemble matrix containing both left and right shape functions and their 2nd derivatives wrt. (x,y,z)

                // get derivatives from left and right shape functions
                Matrix <DDRMat> tB2x_Left = tTemp_Left->eval_d2Ndx2();
                uint tNumOfShapeFunctions_Left = tB2x_Left.n_cols();

                Matrix <DDRMat> tB2x_Right = tTemp_Right->eval_d2Ndx2();
                uint tNumOfShapeFunctions_Right = tB2x_Right.n_cols();

                // create combined B-Matrix, put left and right B2x*n next to each other B2x_comined = [B2x_L, -B2x_R]
                Matrix <DDRMat> tB2x_combined( 6, tNumOfShapeFunctions_Left + tNumOfShapeFunctions_Right, 0.0 );

                // assemble into combined matrix
                for( uint i = 0; i < tNumOfShapeFunctions_Left; i++ )
                {
                    tB2x_combined( 0, i ) = tB2x_Left( 0, i );
                    tB2x_combined( 1, i ) = tB2x_Left( 1, i );
                    tB2x_combined( 2, i ) = tB2x_Left( 2, i );
                    tB2x_combined( 3, i ) = tB2x_Left( 3, i );
                    tB2x_combined( 4, i ) = tB2x_Left( 4, i );
                    tB2x_combined( 5, i ) = tB2x_Left( 5, i );
                }

                //  assemble into combined matrix
                for( uint i = 0; i < tNumOfShapeFunctions_Right; i++ )
                {
                    tB2x_combined( 0, tNumOfShapeFunctions_Left + i ) = - tB2x_Right( 0, i );
                    tB2x_combined( 1, tNumOfShapeFunctions_Left + i ) = - tB2x_Right( 1, i );
                    tB2x_combined( 2, tNumOfShapeFunctions_Left + i ) = - tB2x_Right( 2, i );
                    tB2x_combined( 3, tNumOfShapeFunctions_Left + i ) = - tB2x_Right( 3, i );
                    tB2x_combined( 4, tNumOfShapeFunctions_Left + i ) = - tB2x_Right( 4, i );
                    tB2x_combined( 5, tNumOfShapeFunctions_Left + i ) = - tB2x_Right( 5, i );
                }

                // get normal matrix
                Matrix<DDRMat> tNormalMatrix_2 = this->get_normal_matrix(2);

                // compute Jacobian ---------------
                aJacobians( 0 ) = aJacobians( 0 )
                                + mGammaGhost * ( std::pow( mMeshParameter, 3 ) ) // * mKappa                              // scaling parameters (p=2)
                                * trans( tB2x_combined ) * trans( tNormalMatrix_2 ) * tNormalMatrix_2 * tB2x_combined; // matrices & vectors (p=2)
            }

            // --------- Ghost for cubic shape functions -------------------------------------------------------------
            if ( mOrder >= 3 )
            {
                // assemble matrix containing both left and right shape functions and their 2nd derivatives wrt. (x,y,z)

                // get derivatives from left and right shape functions
                Matrix <DDRMat> tB3x_Left = tTemp_Left->eval_d3Ndx3();
                uint tNumOfShapeFunctions_Left = tB3x_Left.n_cols();

                Matrix <DDRMat> tB3x_Right = tTemp_Right->eval_d3Ndx3();
                uint tNumOfShapeFunctions_Right = tB3x_Right.n_cols();

                // create combined B-Matrix, put left and right B2x*n next to each other B3x_comined = [B3x_L, -B3x_R]
                Matrix <DDRMat> tB3x_combined( 10, tNumOfShapeFunctions_Left + tNumOfShapeFunctions_Right, 0.0 );

                // assemble into combined matrix
                for( uint i = 0; i < tNumOfShapeFunctions_Left; i++ )
                {
                    tB3x_combined( 0, i ) = tB3x_Left( 0, i );
                    tB3x_combined( 1, i ) = tB3x_Left( 1, i );
                    tB3x_combined( 2, i ) = tB3x_Left( 2, i );
                    tB3x_combined( 3, i ) = tB3x_Left( 3, i );
                    tB3x_combined( 4, i ) = tB3x_Left( 4, i );
                    tB3x_combined( 5, i ) = tB3x_Left( 5, i );
                    tB3x_combined( 6, i ) = tB3x_Left( 6, i );
                    tB3x_combined( 7, i ) = tB3x_Left( 7, i );
                    tB3x_combined( 8, i ) = tB3x_Left( 8, i );
                    tB3x_combined( 9, i ) = tB3x_Left( 9, i );
                }

                // assemble into combined matrix
                for( uint i = 0; i < tNumOfShapeFunctions_Right; i++ )
                {
                    tB3x_combined( 0, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 0, i );
                    tB3x_combined( 1, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 1, i );
                    tB3x_combined( 2, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 2, i );
                    tB3x_combined( 3, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 3, i );
                    tB3x_combined( 4, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 4, i );
                    tB3x_combined( 5, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 5, i );
                    tB3x_combined( 6, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 6, i );
                    tB3x_combined( 7, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 7, i );
                    tB3x_combined( 8, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 8, i );
                    tB3x_combined( 9, tNumOfShapeFunctions_Left + i ) = - tB3x_Right( 9, i );
                }

                // get normal matrix
                Matrix<DDRMat> tNormalMatrix_3 = this->get_normal_matrix(3);

                // compute Jacobian ---------------
                aJacobians( 0 ) =   aJacobians( 0 )
                                + mGammaGhost * ( std::pow( mMeshParameter, 5 ) ) // * mKappa                         // scaling parameters (p=2)
                                * trans( tB3x_combined ) * trans( tNormalMatrix_3 ) * tNormalMatrix_3 * tB3x_combined; // matrices & vectors (p=2)
            }
        }

//------------------------------------------------------------------------------

        void IWG_Isotropic_Spatial_Diffusion_Ghost::compute_jacobian_and_residual
            ( Cell< Matrix< DDRMat > >    & aJacobians,
              Matrix< DDRMat >            & aResidual,
              Cell< Field_Interpolator* > & aLeftFieldInterpolators,
              Cell< Field_Interpolator* > & aRightFieldInterpolators )
        {
            MORIS_ERROR( false, "IWG_Isotropic_Spatial_Diffusion_Ghost::compute_jacobian_and_residual - Not supported." );
        }


//------------------------------------------------------------------------------

        Matrix<DDRMat> IWG_Isotropic_Spatial_Diffusion_Ghost::get_normal_matrix (uint aOrderGhost)
        {
            // init the normal matrix
            Matrix< DDRMat > tNormalMatrix;

            // switch on the ghost order
            switch( aOrderGhost )
            {
                case ( 1 ):
                {
                    // set the normal matrix size
                    tNormalMatrix.set_size( 3, 1, 0.0 );
                    return tNormalMatrix = mNormal;
                    break;
                }

                case ( 2 ):
                {
                    // set the normal matrix size
                    tNormalMatrix.set_size( 3, 6, 0.0 );

                    // fill the normal matrix
                    tNormalMatrix( 0, 0 ) = mNormal( 0 );
                    tNormalMatrix( 1, 1 ) = mNormal( 1 );
                    tNormalMatrix( 2, 2 ) = mNormal( 2 );

                    tNormalMatrix( 0, 3 ) = mNormal( 1 );
                    tNormalMatrix( 0, 4 ) = mNormal( 2 );

                    tNormalMatrix( 1, 1 ) = mNormal( 0 );
                    tNormalMatrix( 1, 5 ) = mNormal( 2 );

                    tNormalMatrix( 2, 3 ) = mNormal( 1 );
                    tNormalMatrix( 2, 5 ) = mNormal( 0 );

                    return tNormalMatrix;
                    break;
                }

                case ( 3 ):
                {
                    // set the normal matrix size
                    tNormalMatrix.set_size( 6, 10, 0.0 );

                    tNormalMatrix( 0, 0 ) = mNormal( 0 );
                    tNormalMatrix( 1, 1 ) = mNormal( 1 );
                    tNormalMatrix( 2, 2 ) = mNormal( 2 );

                    tNormalMatrix( 0, 3 ) = mNormal( 1 );
                    tNormalMatrix( 0, 4 ) = mNormal( 2 );

                    tNormalMatrix( 1, 5 ) = mNormal( 0 );
                    tNormalMatrix( 1, 6 ) = mNormal( 2 );

                    tNormalMatrix( 2, 7 ) = mNormal( 0 );
                    tNormalMatrix( 2, 8 ) = mNormal( 1 );

                    real tSqrtOf2 = std::sqrt( 2 );

                    tNormalMatrix( 3, 3 ) = tSqrtOf2 * mNormal( 0 );
                    tNormalMatrix( 3, 5 ) = tSqrtOf2 * mNormal( 1 );
                    tNormalMatrix( 3, 9 ) = tSqrtOf2 * mNormal( 2 );

                    tNormalMatrix( 4, 6 ) = tSqrtOf2 * mNormal( 1 );
                    tNormalMatrix( 4, 8 ) = tSqrtOf2 * mNormal( 2 );
                    tNormalMatrix( 4, 9 ) = tSqrtOf2 * mNormal( 0 );

                    tNormalMatrix( 5, 4 ) = tSqrtOf2 * mNormal( 0 );
                    tNormalMatrix( 5, 7 ) = tSqrtOf2 * mNormal( 2 );
                    tNormalMatrix( 5, 9 ) = tSqrtOf2 * mNormal( 1 );

                    return tNormalMatrix;
                    break;
                }

                default:
                {
                    MORIS_ERROR( false, "IWG_Isotropic_Spatial_Diffusion_Ghost::get_normal_matrix\n"
                                        "Ghost stabilization for this order of shape functions not supported yet." );
                    return tNormalMatrix;
                    break;
                }
            }
        }

//------------------------------------------------------------------------------

        void IWG_Isotropic_Spatial_Diffusion_Ghost::set_interpolation_order ( uint aOrder )
        {
            // check that the order is supported
            MORIS_ERROR( aOrder < 4 , "IWG_Isotropic_Spatial_Diffusion_Ghost::set_interpolation_order \n"
                                      "Ghost stabilization for this order not supported yet." );
            // set the order
            mOrder = aOrder;
        }


//------------------------------------------------------------------------------

        void IWG_Isotropic_Spatial_Diffusion_Ghost::set_penalty_factor ( real aGamma )
        {
            mGammaGhost = aGamma;
        }


//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */