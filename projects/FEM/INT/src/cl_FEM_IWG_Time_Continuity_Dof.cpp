//FEM/INT/src
#include "cl_FEM_IWG_Time_Continuity_Dof.hpp"
#include "cl_FEM_Set.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"
//LINALG/src
#include "fn_trans.hpp"

namespace moris
{
    namespace fem
    {

//------------------------------------------------------------------------------
        IWG_Time_Continuity_Dof::IWG_Time_Continuity_Dof()
        {
            // set size for the property pointer cell
            mMasterProp.resize( static_cast< uint >( IWG_Property_Type::MAX_ENUM ), nullptr );

            // populate the property map
            mPropertyMap[ "WeightCurrent" ]  = IWG_Property_Type::WEIGHT_CURRENT;
            mPropertyMap[ "WeightPrevious" ] = IWG_Property_Type::WEIGHT_PREVIOUS;
            mPropertyMap[ "InitialCondition" ] = IWG_Property_Type::INITIAL_CONDITION;

        }

//------------------------------------------------------------------------------
        void IWG_Time_Continuity_Dof::compute_residual( real aWStar )
        {
            // check master field interpolators
#ifdef DEBUG
            this->check_field_interpolators();
#endif

            // get master index for residual dof type, indices for assembly
            uint tMasterDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::MASTER );
            uint tMasterResStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
            uint tMasterResStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

            // get residual dof type field interpolator for current time step
            Field_Interpolator * tFICurrent
            = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get residual dof type field interpolator for previous time step
            Field_Interpolator * tFIPrevious
            = mMasterPreviousFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get current weight property
            std::shared_ptr< Property > tPropWeightCurrent
            = mMasterProp( static_cast< uint >( IWG_Property_Type::WEIGHT_CURRENT ) );

            // get previous weight property
            std::shared_ptr< Property > tPropWeightPrevious
            = mMasterProp( static_cast< uint >( IWG_Property_Type::WEIGHT_PREVIOUS ) );

            // get previous weight property
            std::shared_ptr< Property > tPropInitialCondition
            = mMasterProp( static_cast< uint >( IWG_Property_Type::INITIAL_CONDITION ) );

              // compute the residual
            if( mMasterFIManager->get_IP_geometry_interpolator()->valt()( 0 ) == 0.0 )
            {
                // compute the jump
                Matrix< DDRMat > tJump = tPropWeightCurrent->val()( 0 ) * tFICurrent->val()
                                       - tPropWeightPrevious->val()( 0 ) * tPropInitialCondition->val();

                // add contribution to residual
                mSet->get_residual()( 0 )( { tMasterResStartIndex, tMasterResStopIndex }, { 0, 0 } )
                += aWStar * ( trans( tFICurrent->N() ) * tJump );
            }
            else
            {
                // compute the jump
                Matrix< DDRMat > tJump = tPropWeightCurrent->val()( 0 ) * tFICurrent->val()
                                       - tPropWeightPrevious->val()( 0 ) * tFIPrevious->val();

                // add contribution to residual
                mSet->get_residual()( 0 )( { tMasterResStartIndex, tMasterResStopIndex }, { 0, 0 } )
                += aWStar * ( trans( tFICurrent->N() ) * tJump );
            }
        }

//------------------------------------------------------------------------------
        void IWG_Time_Continuity_Dof::compute_jacobian( real aWStar )
        {
#ifdef DEBUG
            // check master field interpolators
            this->check_field_interpolators();
#endif

            // get master index for residual dof type, indices for assembly
            uint tMasterDofIndex      = mSet->get_dof_index_for_type( mResidualDofType( 0 ), mtk::Master_Slave::MASTER );
            uint tMasterResStartIndex = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 0 );
            uint tMasterResStopIndex  = mSet->get_res_dof_assembly_map()( tMasterDofIndex )( 0, 1 );

            // get residual dof type field interpolator for current time step
            Field_Interpolator * tFICurrent
            = mMasterFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get residual dof type field interpolator for previous time step
            Field_Interpolator * tFIPrevious
            = mMasterPreviousFIManager->get_field_interpolators_for_type( mResidualDofType( 0 ) );

            // get current weight property
            std::shared_ptr< Property > tPropWeightCurrent
            = mMasterProp( static_cast< uint >( IWG_Property_Type::WEIGHT_CURRENT ) );

            // get previous weight property
            std::shared_ptr< Property > tPropWeightPrevious
            = mMasterProp( static_cast< uint >( IWG_Property_Type::WEIGHT_PREVIOUS ) );

            // compute the jump
            Matrix< DDRMat > tJump = tPropWeightCurrent->val()( 0 ) * tFICurrent->val()
                                   - tPropWeightPrevious->val()( 0 ) * tFIPrevious->val();

            // get the number of master dof type dependencies
            uint tNumDofDependencies = mRequestedMasterGlobalDofTypes.size();

            // loop over master dof type dependencies
            for( uint iDOF = 0; iDOF < tNumDofDependencies; iDOF++ )
            {
                // get the treated dof type
                Cell< MSI::Dof_Type > tDofType = mRequestedMasterGlobalDofTypes( iDOF );

                // get the index for dof type, indices for assembly
                sint tDofDepIndex         = mSet->get_dof_index_for_type( tDofType( 0 ), mtk::Master_Slave::MASTER );
                uint tMasterDepStartIndex = mSet->get_jac_dof_assembly_map()( tMasterDofIndex )( tDofDepIndex, 0 );
                uint tMasterDepStopIndex  = mSet->get_jac_dof_assembly_map()( tMasterDofIndex )( tDofDepIndex, 1 );

                // if residual dof type
                if( tDofType( 0 ) == mResidualDofType( 0 ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex },
                                          { tMasterDepStartIndex, tMasterDepStopIndex } )
                    += aWStar * ( trans( tFICurrent->N() ) * tPropWeightCurrent->val()( 0 ) * tFICurrent->N() );
                }

                // if current weight property has dependency on the dof type
                if ( tPropWeightCurrent->check_dof_dependency( tDofType ) )
                {
                    // add contribution to jacobian
                    mSet->get_jacobian()( { tMasterResStartIndex, tMasterResStopIndex },
                                          { tMasterDepStartIndex, tMasterDepStopIndex } )
                    += aWStar * ( trans( tFICurrent->N() ) * tFICurrent->val() * tPropWeightCurrent->dPropdDOF( tDofType ) );
                }

                // FIXME no derivative wrt previous dof type
                // FIXME no derivative with the previous weight
            }
        }

//------------------------------------------------------------------------------
        void IWG_Time_Continuity_Dof::compute_jacobian_and_residual( real aWStar )
        {
            MORIS_ERROR( false, "IWG_Time_Continuity_Dof::compute_jacobian_and_residual - Not implemented." );
        }

//------------------------------------------------------------------------------
        void IWG_Time_Continuity_Dof::compute_dRdp( real aWStar )
        {
            MORIS_ERROR( false, "IWG_Time_Continuity_Dof::compute_dRdp - Not implemented." );
        }

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */