#include "cl_FEM_IWG_L2.hpp"

#include "op_times.hpp" //LINALG/src
#include "fn_norm.hpp"  //LINALG/src
#include "fn_trans.hpp" //LINALG/src
#include "fn_dot.hpp"   //LINALG/src
#include "fn_print.hpp" //LINALG/src
#include "cl_FEM_Element.hpp"

namespace moris
{
    namespace fem
    {
//------------------------------------------------------------------------------
    IWG_L2::IWG_L2( const real aAlpha )
    {
        // set the residual dof type
        mResidualDofType = { MSI::Dof_Type::L2 };

        // set the active dof types
        mActiveDofTypes = { { MSI::Dof_Type::L2 } };

        // set alpha
        this->set_alpha( aAlpha );
    }

//------------------------------------------------------------------------------

    void IWG_L2::set_alpha( const real aAlpha  )
    {

        mAlpha = aAlpha;

        if(  aAlpha == 0.0 )
        {
            mComputeFunction
                = & IWG_L2::compute_jacobian_and_residual_without_alpha;

            mComputeJacFunction
                = & IWG_L2::compute_jacobian_without_alpha;

            mComputeResFunction
                = & IWG_L2::compute_residual_without_alpha;
        }
        else
        {
            mComputeFunction
                = & IWG_L2::compute_jacobian_and_residual_with_alpha;

            mComputeJacFunction
                = & IWG_L2::compute_jacobian_with_alpha;

            mComputeResFunction
                = & IWG_L2::compute_residual_with_alpha;
        }
    }

//------------------------------------------------------------------------------
//
//        void
//        IWG_L2::compute_jacobian_and_residual(
//                Matrix< DDRMat >       & aJacobian,
//                Matrix< DDRMat >       & aResidual,
//                const Matrix< DDRMat > & aNodalDOF,
//                const Matrix< DDRMat > & aNodalWeakBC,
//                const uint             & aPointIndex )
//        {
//            ( this->*mComputeFunction )(
//                    aJacobian,
//                    aResidual,
//                    aNodalDOF,
//                    aNodalWeakBC,
//                    aPointIndex );
//        }

    void IWG_L2::compute_jacobian_and_residual( Cell< Matrix< DDRMat > >    & aJacobians,
                                                      Matrix< DDRMat >      & aResidual,
                                                Cell< Field_Interpolator* > & aFieldInterpolators )
    {
        // call the right mComputeFunction for residual and jacobian evaluations
        ( this->*mComputeFunction )( aJacobians,
                                     aResidual,
                                     aFieldInterpolators );
    }

//------------------------------------------------------------------------------
//
//        real
//        IWG_L2::compute_integration_error(
//                const Matrix< DDRMat >                    & aNodalDOF,
//                real (*aFunction)( const Matrix< DDRMat > & aPoint ) ,
//                const uint                                & aPointIndex )
//        {
//            mN->compute( aPointIndex );
//
//            Matrix< DDRMat > tCoords = mN->matrix_data() * mInterpolator->get_node_coords();
//
//            // get shape function
//            Matrix< DDRMat > tPhiHat = mN->matrix_data() * aNodalDOF.matrix_data();
//
//            return std::pow( tPhiHat( 0 ) - aFunction( tCoords ), 2 );
//        }

//------------------------------------------------------------------------------
//
//        void
//        IWG_L2::compute_jacobian_and_residual_without_alpha(
//                Matrix< DDRMat >       & aJacobian,
//                Matrix< DDRMat >       & aResidual,
//                const Matrix< DDRMat > & aNodalDOF,
//                const Matrix< DDRMat > & aNodalWeakBC,
//                const uint             & aPointIndex )
//        {
//
//            // get shape function
//            mN->compute( aPointIndex );
//
//            // calculate Jacobian
//            aJacobian = trans( mN ) * mN;
//            aResidual = aJacobian * ( aNodalDOF - aNodalWeakBC );
//        }

        void IWG_L2::compute_jacobian_and_residual_without_alpha( Cell< Matrix< DDRMat > >    & aJacobians,
                                                                  Matrix< DDRMat >            & aResidual,
                                                                  Cell< Field_Interpolator* > & aFieldInterpolators )
        {
            // set field interpolator
            Field_Interpolator* tFI = aFieldInterpolators( 0 );

            // compute Jacobian
            aJacobians( 0 ) = trans( tFI->N() ) * tFI->N();

            // compute residual
            //FIXME mNodalWeakBCs
            aResidual = aJacobians( 0 ) * ( tFI->get_coeff() - mNodalWeakBCs );
        }

//------------------------------------------------------------------------------
//
//        void
//        IWG_L2::compute_jacobian_and_residual_with_alpha(
//                Matrix< DDRMat >       & aJacobian,
//                Matrix< DDRMat >       & aResidual,
//                const Matrix< DDRMat > & aNodalDOF,
//                const Matrix< DDRMat > & aNodalWeakBC,
//                const uint             & aPointIndex )
//        {
//
//            // get shape function
//            mN->compute( aPointIndex );
//
//            // compute derivative
//            mB->compute( aPointIndex );
//
//            // calculate Jacobian
//            aJacobian = trans( mN ) * mN + mAlpha * ( trans( mB ) * mB );
//
//            aResidual = aJacobian * ( aNodalDOF - aNodalWeakBC );
//        }

        void IWG_L2::compute_jacobian_and_residual_with_alpha( Cell< Matrix< DDRMat > >    & aJacobians,
                                                               Matrix< DDRMat >            & aResidual,
                                                               Cell< Field_Interpolator* > & aFieldInterpolators)
        {
            // set field interpolator
            Field_Interpolator* tFI = aFieldInterpolators( 0 );

            // compute Jacobian
            aJacobians( 0 ) = trans( tFI->N() ) * tFI->N() + mAlpha * ( trans( tFI->Bx() ) * tFI->Bx() );

            // compute residual
            //FIXME: mNodalWeakBCs
            aResidual = aJacobians( 0 ) * ( tFI->get_coeff() - mNodalWeakBCs );
        }

//------------------------------------------------------------------------------
//
//        real
//        IWG_L2::interpolate_scalar_at_point(
//                                    const Matrix< DDRMat > & aNodalWeakBC,
//                                    const uint             & aPointIndex )
//        {
//            // get shape function
//            mN->compute( aPointIndex );
//
//            // return interpolation
//            return dot( mN->matrix() , aNodalWeakBC );
//        }

//------------------------------------------------------------------------------

        void IWG_L2::compute_jacobian( Cell< Matrix< DDRMat > >    & aJacobians,
                                       Cell< Field_Interpolator* > & aFieldInterpolators )
        {
            // call the right mComputeJacFunction for jacobian evaluation
            ( this->*mComputeJacFunction )( aJacobians,
                                            aFieldInterpolators );
        }

//------------------------------------------------------------------------------

        void IWG_L2::compute_jacobian_without_alpha( Cell< Matrix< DDRMat > >    & aJacobians,
                                                     Cell< Field_Interpolator* > & aFieldInterpolators )
        {
            // set field interpolator
            Field_Interpolator* tFI = aFieldInterpolators( 0 );

            // compute Jacobian
            aJacobians( 0 ) = trans( tFI->N() ) * tFI->N();
        }

//------------------------------------------------------------------------------

        void IWG_L2::compute_jacobian_with_alpha( Cell< Matrix< DDRMat > >    & aJacobians,
                                                  Cell< Field_Interpolator* > & aFieldInterpolators )
        {
            // set field interpolator
            Field_Interpolator* tFI = aFieldInterpolators( 0 );

            // compute Jacobian
            aJacobians( 0 ) = trans( tFI->N() ) * tFI->N() + mAlpha * ( trans( tFI->Bx() ) * tFI->Bx() );
        }

//------------------------------------------------------------------------------

        void IWG_L2::compute_residual( Matrix< DDRMat >            & aResidual,
                                       Cell< Field_Interpolator* > & aFieldInterpolators )
        {
            // call the right mComputeResFunction for residual evaluation
            ( this->*mComputeResFunction )( aResidual,
                                            aFieldInterpolators );
        }

//------------------------------------------------------------------------------

        void IWG_L2::compute_residual_without_alpha( Matrix< DDRMat >            & aResidual,
                                                     Cell< Field_Interpolator* > & aFieldInterpolators )
        {
            // set field interpolator
            Field_Interpolator* tFI = aFieldInterpolators( 0 );

            // compute Jacobian
            //FIXME: mNodalWeakBCs
            aResidual = trans( tFI->N() ) * ( tFI->val() - tFI->N() * mNodalWeakBCs );
        }

//------------------------------------------------------------------------------

        void IWG_L2::compute_residual_with_alpha( Matrix< DDRMat >            & aResidual,
                                                  Cell< Field_Interpolator* > & aFieldInterpolators )
        {
            // set field interpolator
            Field_Interpolator* tFI = aFieldInterpolators( 0 );

            // compute Jacobian
            //FIXME mNodalWeakBCs
            aResidual = trans( tFI->N() ) * ( tFI->val() - tFI->N() * mNodalWeakBCs )
                      + mAlpha * trans( tFI->Bx() ) * ( tFI->gradx( 1 ) - tFI->Bx() * mNodalWeakBCs );
        }

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */
