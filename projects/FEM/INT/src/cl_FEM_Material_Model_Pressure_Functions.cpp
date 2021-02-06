/*
 * cl_FEM_Material_Model_Pressure_Functions.cpp
 *
 *  Created on: Feb 2, 2021
 *      Author: wunsch
 */

#include "cl_FEM_Material_Model.hpp"
#include "cl_FEM_Set.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------
        // RETURN FUNCTIONS FOR DENSITY (SECOND EQUATION OF STATE)
        //------------------------------------------------------------------------------

        // if thermodynamic state variable is dependent compute and retrieve value from storage
        const Matrix< DDRMat > & Material_Model::pressure_dep()
        {
            // if the pressure was not evaluated
            if( mPressureEval )
            {
                // evaluate the pressure
                this->eval_pressure();

                // set bool for evaluation
                mPressureEval = false;
            }
            // return the pressure value
            return mPressure;
        }

        // trivial operation: get value from FI
        const Matrix< DDRMat > & Material_Model::pressure_triv()
        {
            // return the pressure value
            return mFIManager->get_field_interpolators_for_type( mDofPressure )->val();
        }

        //------------------------------------------------------------------------------

        // if thermodynamic state variable is dependent compute and retrieve value from storage
        const Matrix< DDRMat > & Material_Model::PressureDot_dep()
        {
            // if the flux was not evaluated
            if( mPressureDotEval )
            {
                // evaluate the flux
                this->eval_PressureDot();

                // set bool for evaluation
                mPressureDotEval = false;
            }
            // return the flux value
            return mPressureDot;
        }   

        // trivial operation: get value from FI
        const Matrix< DDRMat > & Material_Model::PressureDot_triv()
        {
            // return the pressure rate of change
            return mFIManager->get_field_interpolators_for_type( mDofPressure )->gradt( 1 );
        }             

        //------------------------------------------------------------------------------

        // if thermodynamic state variable is dependent compute and retrieve value from storage
        const Matrix< DDRMat > & Material_Model::dnPressuredxn_dep( uint aOrder )
        {
            switch ( aOrder )
            {
                case 1: // first derivative
                {    
                    if ( mdPressuredxEval )
                    {
                        // evaluate the flux
                        this->eval_dPressuredx();
    
                        // set bool for evaluation
                        mdPressuredxEval = false;
                    }
    
                    // return the flux value
                    return mdPressuredx;
                }
    
                case 2: // second derivative
                {
    
                    if ( md2Pressuredx2Eval )
                    {
                        // evaluate the flux
                        this->eval_d2Pressuredx2();
    
                        // set bool for evaluation
                        md2Pressuredx2Eval = false;
                    }
    
                    // return the flux value
                    return md2Pressuredx2;
                }
    
                default:
                {
                    MORIS_ERROR( false, "Material_Model::dnPressuredxn - aOrder unknown, only 1 and 2 supported." );
                    return mdPressuredx;
                }
            }
        }

        // trivial operation: get values from FI
        const Matrix< DDRMat > & Material_Model::dnPressuredxn_triv( uint aOrder )
        {
            // return the pressure rate of change
            return mFIManager->get_field_interpolators_for_type( mDofPressure )->gradx( aOrder );
        }         

        //-----------------------------------------------------------------------------
        //-----------------------------------------------------------------------------

        // if thermodynamic state variable is dependent compute and retrieve values from storage
        const Matrix< DDRMat > & Material_Model::PressureDOF_dep( const moris::Cell< MSI::Dof_Type > & aDofType )
        {
            // if aDofType is not an active dof type for the MM
            MORIS_ERROR(
                    this->check_dof_dependency( aDofType ),
                    "Material_Model::PressureDOF - no dependency in this dof type." );

            // get the dof index
            uint tDofIndex = mGlobalDofTypeMap( static_cast< uint >( aDofType( 0 ) ) );

            // if the derivative has not been evaluated yet
            if( mPressureDofEval( tDofIndex ) )
            {
                // evaluate the derivative
                this->eval_PressureDOF( aDofType );

                // set bool for evaluation
                mPressureDofEval( tDofIndex ) = false;
            }

            // return the derivative
            return mPressureDof( tDofIndex );
        }

        // trivial operation: get values from FI
        const Matrix< DDRMat > & Material_Model::PressureDOF_triv( const moris::Cell< MSI::Dof_Type > & aDofType )
        {
            // check DOF deriv is wrt to own DOF-type is with 
            // FIXME: this might need to be changed to provide a zero matrix
            MORIS_ASSERT( aDofType( 0 ) == mDofPressure, 
                "Material_Model::PressureDOF_dep - Requesting DoF derivative of primitive variable wrt. to another DoF type." );

            // return the pressure rate of change
            return mFIManager->get_field_interpolators_for_type( mDofPressure )->N();
        } 

        //-----------------------------------------------------------------------------

        // if thermodynamic state variable is dependent compute and retrieve values from storage
        const Matrix< DDRMat > & Material_Model::PressureDotDOF_dep( const moris::Cell< MSI::Dof_Type > & aDofType )
        {
            // if aDofType is not an active dof type for the MM
            MORIS_ERROR(
                    this->check_dof_dependency( aDofType ),
                    "Material_Model::PressureDotDOF_dep - no dependency in this dof type." );

            // get the dof index
            uint tDofIndex = mGlobalDofTypeMap( static_cast< uint >( aDofType( 0 ) ) );

            // if the derivative has not been evaluated yet
            if( mPressureDotDofEval( tDofIndex ) )
            {
                // evaluate the derivative
                this->eval_PressureDotDOF( aDofType );

                // set bool for evaluation
                mPressureDotDofEval( tDofIndex ) = false;
            }

            // return the derivative
            return mPressureDotDof( tDofIndex );
        }

        // trivial operation: get values from FI
        const Matrix< DDRMat > & Material_Model::PressureDotDOF_triv( const moris::Cell< MSI::Dof_Type > & aDofType )
        {
            // check DOF deriv is wrt to own DOF-type is with 
            // FIXME: this might need to be changed to provide a zero matrix
            MORIS_ASSERT( aDofType( 0 ) == mDofPressure, 
                "Material_Model::PressureDotDOF_triv - Requesting DoF derivative of primitive variable wrt. to another DoF type." );

            // return the pressure rate of change
            return mFIManager->get_field_interpolators_for_type( mDofPressure )->dnNdtn( 1 );
        }         

        //-----------------------------------------------------------------------------

        // if thermodynamic state variable is dependent compute and retrieve values from storage
        const Matrix< DDRMat > & Material_Model::dnPressuredxnDOF_dep( const moris::Cell< MSI::Dof_Type > & aDofType, uint aOrder )
        {
            // if aDofType is not an active dof type for the MM
            MORIS_ERROR(
                    this->check_dof_dependency( aDofType ),
                    "Material_Model::dnPressuredxnDOF - no dependency in this dof type." );

            // get the dof index
            uint tDofIndex = mGlobalDofTypeMap( static_cast< uint >( aDofType( 0 ) ) );

            switch ( aOrder )
            {
                case 1: // first derivative
                {    
                    // if the derivative has not been evaluated yet
                    if( mdPressuredxDofEval( tDofIndex ) )
                    {
                        // evaluate the derivative
                        this->eval_dPressuredxDOF( aDofType );
    
                        // set bool for evaluation
                        mdPressuredxDofEval( tDofIndex ) = false;
                    }
    
                    // return the derivative
                    return mdPressuredxDof( tDofIndex );
                }
    
                case 2: // second derivative
                {    
                    // if the derivative has not been evaluated yet
                    if( md2Pressuredx2DofEval( tDofIndex ) )
                    {
                        // evaluate the derivative
                        this->eval_d2Pressuredx2DOF( aDofType );
    
                        // set bool for evaluation
                        md2Pressuredx2DofEval( tDofIndex ) = false;
                    }
    
                    // return the derivative
                    return md2Pressuredx2Dof( tDofIndex );
                }
    
                default:
                {
                    MORIS_ERROR( false, "Material_Model::dnPressuredxnDOF_dep - aOrder unknown, only 1 and 2 supported." );
                    return mdPressuredxDof( 0 );
                }
            }
        }    

        // trivial operation: get values from FI
        const Matrix< DDRMat > & Material_Model::dnPressuredxnDOF_triv( const moris::Cell< MSI::Dof_Type > & aDofType, uint aOrder )
        {
            // check DOF deriv is wrt to own DOF-type is with 
            // FIXME: this might need to be changed to provide a zero matrix
            MORIS_ASSERT( aDofType( 0 ) == mDofPressure, 
                "Material_Model::dnPressuredxnDOF_triv - Requesting DoF derivative of primitive variable wrt. to another DoF type." );

            // return the pressure rate of change
            return mFIManager->get_field_interpolators_for_type( mDofPressure )->dnNdxn( aOrder );
        }    

        //-----------------------------------------------------------------------------

    }/* end_fem_namespace */
}/* end_moris_namespace */
