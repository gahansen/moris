/*
 * cl_FEM_IWG_Compressible_NS_Bulk.hpp
 *
 *  Created on: Feb 10, 2021
 *      Author: wunsch
 *
 * IWG for unified NS equations using flux matrices
 * operating on all residual DoF types simultaneously
 */

#ifndef SRC_FEM_CL_FEM_IWG_COMPRESSIBLE_NS_BULK_HPP_
#define SRC_FEM_CL_FEM_IWG_COMPRESSIBLE_NS_BULK_HPP_

#include <map>
#include "typedefs.hpp"                     //MRS/COR/src
#include "cl_Cell.hpp"                      //MRS/CON/src

#include "cl_Matrix.hpp"                    //LINALG/src
#include "linalg_typedefs.hpp"              //LINALG/src

#include "cl_FEM_IWG.hpp"                   //FEM/INT/src

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        class IWG_Compressible_NS_Bulk : public IWG
        {
                //------------------------------------------------------------------------------

            private:

                // default dof types (FIXME: only primitive vars for now)
                MSI::Dof_Type mDofDensity     = MSI::Dof_Type::RHO;
                MSI::Dof_Type mDofPressure    = MSI::Dof_Type::P;
                MSI::Dof_Type mDofVelocity    = MSI::Dof_Type::VX;
                MSI::Dof_Type mDofTemperature = MSI::Dof_Type::TEMP;

                // flag indicating what variable set is being used
                fem::Variable_Set mVariableSet = fem::Variable_Set::UNDEFINED;

                // storage for flux jacobians
                bool mFluxAMatEval = true;
                bool mFluxADofMatEval = true;
                bool mFluxKMatEval = true;
                bool mFluxKDofMatEval = true;
                bool mVarVecEval = true;
                bool mVarDofVecEval = true;

                // vector and matrix containing field variables and their spatial derivatives
                Matrix< DDRMat > mY;
                Matrix< DDRMat > mdYdt;
                Matrix< DDRMat > mdYdx;

                Matrix< DDRMat > mYDOF;
                Matrix< DDRMat > mdYdtDOF;
                moris::Cell< Matrix< DDRMat > > mdYdxDOF;

                // cells of matrices containing the A flux matrices and their DoF derivatives
                moris::Cell< Matrix< DDRMat > > mA;
                moris::Cell< moris::Cell< Matrix< DDRMat > > > mADOF;
                
                // cells of matrices containing the K flux matrices and their DoF derivatives
                moris::Cell< moris::Cell< Matrix< DDRMat > > > mK;
                moris::Cell< moris::Cell< Matrix< DDRMat > > > mKDOF;

                // (cells of) matrices containing the product of the K flux matrices with the 
                // spatial derivative of the variable set vector (and their DoF derivatives)
                Matrix< DDRMat > mKYj;
                moris::Cell< Matrix< DDRMat > > mKYjDOF;


                //------------------------------------------------------------------------------

            public:

                // local property enums
                enum class IWG_Property_Type
                {
                    DYNAMIC_VISCOSITY,
                    THERMAL_CONDUCTIVITY,
                    BODY_FORCE,
                    BODY_HEAT_LOAD,
                    MAX_ENUM
                };

                // local constitutive enums
                enum class IWG_Material_Type
                {
                    FLUID_MM,
                    MAX_ENUM
                };

                // local constitutive enums
                enum class IWG_Constitutive_Type
                {
                    FLUID_CM,
                    MAX_ENUM
                };

                //------------------------------------------------------------------------------
                /*
                 *  constructor
                 */
                IWG_Compressible_NS_Bulk();

                //------------------------------------------------------------------------------
                /**
                 * trivial destructor
                 */
                ~IWG_Compressible_NS_Bulk(){};

                //------------------------------------------------------------------------------
                /**
                 * reset eval flags specific to this IWG
                 */
                void reset_spec_eval_flags();

                //------------------------------------------------------------------------------
                /**
                 * compute the residual
                 * @param[ in ] aWStar weight associated to the evaluation point
                 */
                void compute_residual( real aWStar );

                //------------------------------------------------------------------------------
                /**
                 * compute the jacobian
                 * @param[ in ] aWStar weight associated to the evaluation point
                 */
                void compute_jacobian( real aWStar );

                //------------------------------------------------------------------------------
                /**
                 * compute the residual and the jacobian
                 * @param[ in ] aWStar weight associated to the evaluation point
                 */
                void compute_jacobian_and_residual( real aWStar );

                //------------------------------------------------------------------------------
                /**
                 * compute the derivative of the residual wrt design variables
                 * @param[ in ] aWStar weight associated to the evaluation point
                 */
                void compute_dRdp( real aWStar );

            private:
                //------------------------------------------------------------------------------
                /**
                 * compute the residual strong form
                 * @param[ in ] aRM a matrix to fill with RM
                 * @param[ in ] aRC a matrix to fill with RC
                 */
                void compute_residual_strong_form(
                        Matrix< DDRMat > & aRM,
                        real             & aRC );

                //------------------------------------------------------------------------------
                /**
                 * compute the residual strong form
                 * @param[ in ] aDofTypes a list of dof type wrt which
                 *                        the derivative is requested
                 * @param[ in ] aJM       a matrix to fill with dRMdDof
                 * @param[ in ] aJC       a matrix to fill with dRCdDof
                 */
                void compute_jacobian_strong_form(
                        moris::Cell< MSI::Dof_Type >   aDofTypes,
                        Matrix< DDRMat >             & aJM,
                        Matrix< DDRMat >             & aJC );

                //------------------------------------------------------------------------------
                // FIXME provided directly by the field interpolator?
                /**
                 * compute the term dnNdtn
                 * @param[ in ] adnNdtn a matrix to fill with dnNdtn
                 */
                void compute_dnNdtn( Matrix< DDRMat > & adnNdtn );

                //------------------------------------------------------------------------------
                /**
                 * Compute Flux matrices for residual computation
                 */
                void compute_Flux_Matrices();

                //------------------------------------------------------------------------------
                /**
                 * check that the set of residual DoF types is valid
                 * and supported by the implementation
                 */
                bool check_residual_dof_types();

                //------------------------------------------------------------------------------
                /**
                 * check that the set of DoF dependencies is valid
                 * and supported by the implementation
                 */
                bool check_dof_dependencies();

                //------------------------------------------------------------------------------
                /**
                 * assemble the state variables and their derivatives
                 * into vectors and matrices
                 */
                void assemble_variable_set();

                //------------------------------------------------------------------------------
                /**
                 * assemble the derivatives of the state variables and their spatial derivatives
                 * wrt. to the DoF types into matrices and cells
                 */
                void assemble_variable_DOF_set();                

                //------------------------------------------------------------------------------
                /**
                 * evaluate the A flux matrices
                 */
                void eval_A_matrices();     

                //------------------------------------------------------------------------------
                /**
                 * evaluate the DoF derivatives of the A flux matrices for the Jacobians
                 */
                void eval_A_DOF_matrices();
                
                void eval_A0_DOF();
                void eval_A1_DOF(); 
                void eval_A2_DOF(); 
                void eval_A3_DOF();                  

                //------------------------------------------------------------------------------
                /**
                 * evaluate the product of the K flux matrices with the 
                 * spatial derivative of the variable set vector
                 */
                void eval_KYj();
                
                //------------------------------------------------------------------------------
                /**
                 * evaluate the derivative of the product of the K flux matrices with the 
                 * spatial derivative of the variable set vector with respect to the DoFs
                 */
                void eval_KYj_DOF();  

                //------------------------------------------------------------------------------
                /**
                 * evaluate the K flux matrices
                 */
                void eval_K_matrices();      

                //------------------------------------------------------------------------------
                /**
                 * evaluate the DoF derivatives of the K flux matrices for the Jacobians
                 */
                void eval_K_DOF_matrices();     

        };
        //------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

#endif /* SRC_FEM_CL_FEM_IWG_COMPRESSIBLE_NS_VELOCITY_BULK_HPP_ */