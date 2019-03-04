
#include "cl_FEM_IWG_Olsson_CLS_Interface.hpp"

#include "fn_trans.hpp"
#include "fn_dot.hpp"

namespace moris
{
    namespace fem
    {
//------------------------------------------------------------------------------

//        IWG_Olsson_CLS_Interface::IWG_Olsson_CLS_Interface( const real aFieldUpperBound,
//                                                            const real aFieldLowerBound,
//                                                            const real aMethodParameter )
        IWG_Olsson_CLS_Interface::IWG_Olsson_CLS_Interface()
        {
            //FIXME set field upper and lower bound
            mPhiUB = 1.0;
            mPhiLB = 0.0;

            //FIXME set Olsson CLS epsilon parameter
            mEpsilon = 1.0;

            // set the residual dof type
            //FIXME: level set scalar field not UX
            mResidualDofType = MSI::Dof_Type::UX;

            // set the active dof type
            //FIXME: level set scalar field not UX
            //       level set normal field not UY
            mActiveDofTypes = {{ MSI::Dof_Type::UX },
                               { MSI::Dof_Type::UY }};

        }

//------------------------------------------------------------------------------

        void IWG_Olsson_CLS_Interface::compute_residual( Matrix< DDRMat >            & aResidual,
                                                         Cell< Field_Interpolator* > & aFieldInterpolators )
        {
            // set field interpolators
            Field_Interpolator* phi  = aFieldInterpolators( 0 );
            Field_Interpolator* nPhi = aFieldInterpolators( 1 );

            //FIXME set the interface normal
            Matrix< DDRMat > aInterfaceNormal( phi->gradx( 1 ).n_cols() , 1, 1.0 );

            //compute the residual
            aResidual = trans( phi->N() )
                      * ( ( phi->val()( 0 ) - mPhiLB ) * ( mPhiUB - phi->val()( 0 ) ) - mEpsilon * dot( phi->gradx( 1 ), nPhi->val() ) )
                      * trans( nPhi->val() ) * aInterfaceNormal;
        }

//------------------------------------------------------------------------------

        void IWG_Olsson_CLS_Interface::compute_jacobian( Cell< Matrix< DDRMat > >    & aJacobians,
                                                         Cell< Field_Interpolator* > & aFieldInterpolators )
        {
            // set field interpolators
            Field_Interpolator* phi  = aFieldInterpolators( 0 );
            Field_Interpolator* nPhi = aFieldInterpolators( 1 );

            //FIXME set the interface normal
            Matrix< DDRMat > aInterfaceNormal( phi->gradx( 1 ).n_cols() , 1, 1.0 );

            // compute the jacobian
            aJacobians( 0 ) = trans( phi->N() )
                            * ( ( mPhiLB + mPhiUB - 2 * phi->val()( 0 ) ) * phi->N() - mEpsilon * trans( nPhi->val() ) * phi->Bx() )
                            * dot( nPhi->val(), aInterfaceNormal ) ;

            aJacobians( 1 ) = trans( phi->N() ) * ( ( ( phi->val()( 0 ) - mPhiLB ) * ( mPhiUB - phi->val()( 0 ) )
                                                   - 2 * mEpsilon * dot( phi->gradx( 1 ), nPhi->val() ) ) * nPhi->N() ) * aInterfaceNormal;
        }

//------------------------------------------------------------------------------

        void IWG_Olsson_CLS_Interface::compute_jacobian_and_residual( Cell< Matrix< DDRMat > >    & aJacobians,
                                                                      Matrix< DDRMat >            & aResidual,
                                                                      Cell< Field_Interpolator* > & aFieldInterpolators )
        {
            // set field interpolators
            Field_Interpolator* phi  = aFieldInterpolators( 0 );
            Field_Interpolator* nPhi = aFieldInterpolators( 1 );

            //FIXME set the interface normal
            Matrix< DDRMat > aInterfaceNormal( phi->gradx( 1 ).n_cols() , 1, 1.0 );

            //compute the residual
            aResidual = trans( phi->N() )
                      * ( ( phi->val()( 0 ) - mPhiLB ) * ( mPhiUB - phi->val()( 0 ) ) - mEpsilon * dot( phi->gradx( 1 ), nPhi->val() ) )
                      * trans( nPhi->val() ) * aInterfaceNormal;

            // compute the jacobian
            aJacobians( 0 ) = phi->N()
                            * ( ( mPhiLB + mPhiUB - 2 * phi->val()( 0 ) ) * phi->N() - mEpsilon * trans( nPhi->val() ) * phi->Bx() )
                            * dot( nPhi->val(), aInterfaceNormal ) ;

            aJacobians( 1 ) = trans( phi->N() ) * ( ( ( phi->val()( 0 ) - mPhiLB ) * ( mPhiUB - phi->val()( 0 ) )
                                                   - 2 * mEpsilon * dot( phi->gradx( 1 ), nPhi->val() ) ) * nPhi->N() ) * aInterfaceNormal;
        }

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */
