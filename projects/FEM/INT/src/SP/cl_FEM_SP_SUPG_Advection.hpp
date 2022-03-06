/*
 * cl_FEM_SP_SUPG_Advection.hpp
 *
 *  Created on: Apr 14, 2020
 *  Author: noel
 */

#ifndef SRC_FEM_CL_FEM_SP_SUPG_ADVECTION_HPP_
#define SRC_FEM_CL_FEM_SP_SUPG_ADVECTION_HPP_

#include <map>
// MRS/CON/src
#include "typedefs.hpp"
#include "cl_Cell.hpp"
// LINALG/src
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
// FEM/INT/src
#include "cl_FEM_Field_Interpolator.hpp"
#include "cl_FEM_Constitutive_Model.hpp"
#include "cl_FEM_Stabilization_Parameter.hpp"
#include "cl_FEM_Cluster.hpp"

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------
        /*
         * Stabilization parameter for SUPG stabilization on diffusion-advection
         * tau_T =
         * from Tezduyar & Osawa (2000)
         */
        class SP_SUPG_Advection : public Stabilization_Parameter
        {

            //------------------------------------------------------------------------------

          private:
            // default dof type
            MSI::Dof_Type mMasterDofScalarField = MSI::Dof_Type::TEMP;
            MSI::Dof_Type mMasterDofVelocity    = MSI::Dof_Type::VX;

            // property type for the SP
            enum class Property_Type
            {
                CONDUCTIVITY,
                HEAT_CAPACITY,
                DENSITY,
                LATENT_HEAT,
                PC_TEMP,
                PHASE_STATE_FUNCTION,
                PHASE_CHANGE_CONST,
                SOURCE,
                MAX_ENUM
            };

            // internal threshold
            const real mEpsilon = MORIS_REAL_EPS;

            // flag for evaluation
            bool                    mLengthScaleEval = true;
            moris::Matrix< DDBMat > mdLengthScaledMasterDofEval;

            // storage
            real                            mLengthScale;
            moris::Cell< Matrix< DDRMat > > mdLengthScaledMasterDof;

            /*
             * Rem: mParameters
             * betaTime - 0 for steady-state,
             *            otherwise betaTime scales time step; usually should set to one
             */

            // parameters
            real mBetaTime = 1.0;

            // set parameter bool
            bool mSetBetaTime = false;

            //------------------------------------------------------------------------------
            /*
             * function to compute effective conductivity
             */
            real compute_effective_conductivity();

            //------------------------------------------------------------------------------
            /*
             * function to compute dof derivatives of effective conductivity
             *
             * @param[out] tEffectiveConductivitydu - matrix with dof derivatives; properly
             *             sized before function is called but not set to zero
             * @param[in]  aDofTypess - doftype with respect to which derivatives are computed
             *
             * @return     true if the effective conductivity depends on dof type
             */
            bool compute_derivative_of_effective_conductivity(
                    Matrix< DDRMat >&                   aEffectiveConductivitydu,
                    const moris::Cell< MSI::Dof_Type >& aDofTypess );

          public:
            //------------------------------------------------------------------------------
            /*
             * constructor
             */
            SP_SUPG_Advection();

            //------------------------------------------------------------------------------
            /**
             * trivial destructor
             */
            ~SP_SUPG_Advection() {}

            //------------------------------------------------------------------------------
            /**
             * set parameters
             */
            void set_parameters( moris::Cell< Matrix< DDRMat > > aParameters );

            //------------------------------------------------------------------------------
            /**
             * reset evaluation flags
             * child implementation
             */
            void reset_eval_flags();

            //------------------------------------------------------------------------------
            /**
             * set dof types
             * @param[ in ] aDofTypes a cell of cell of dof types
             * @param[ in ] aDofStrings list of strings describing the dof types
             * @param[ in ] aIsMaster enum for master or slave
             */
            void set_dof_type_list(
                    moris::Cell< moris::Cell< MSI::Dof_Type > >& aDofTypes,
                    moris::Cell< std::string >&                  aDofStrings,
                    mtk::Master_Slave                            aIsMaster = mtk::Master_Slave::MASTER );

            //------------------------------------------------------------------------------
            /**
             * create a global dof type list including constitutive and property dependencies
             * child implementation
             */
            void build_global_dof_type_list();

            //------------------------------------------------------------------------------
            /**
             * set dv types
             * @param[ in ] aDvTypes   a cell of group of dv types
             * @param[ in ] aDvStrings list of strings describing the dv types
             * @param[ in ] aIsMaster enum for master or slave
             */
            void
            set_dv_type_list(
                    moris::Cell< moris::Cell< PDV_Type > >& aDvTypes,
                    moris::Cell< std::string >&             aDvStrings,
                    mtk::Master_Slave                       aIsMaster = mtk::Master_Slave::MASTER )
            {
                Stabilization_Parameter::set_dv_type_list( aDvTypes, aIsMaster );
            }

            //------------------------------------------------------------------------------
            /**
             * evaluate the stabilization parameter value
             */
            void eval_SP();

            //------------------------------------------------------------------------------
            /**
             * evaluate the stabilization parameter derivative wrt to a master dof type
             * @param[ in ] aDofTypes a dof type wrt which the derivative is evaluated
             */
            void eval_dSPdMasterDOF( const moris::Cell< MSI::Dof_Type >& aDofTypes );

            //------------------------------------------------------------------------------
            /**
             * evaluate the penalty parameter derivative wrt to a master dv type
             * @param[ in ] aDvTypes a dv type wrt which the derivative is evaluated
             */
            void
            eval_dSPdMasterDV( const moris::Cell< PDV_Type >& aDvTypes )
            {
                MORIS_ERROR( false, "SP_SUPG_Advection::eval_dSPdMasterDV - not implemented." );
            }

          private:
            //------------------------------------------------------------------------------
            /**
             * return the length scale
             * @param[ out ] mLengthScale length scale for SUPG
             */
            real length_scale();

            /**
             * evaluate the length scale parameter
             */
            void eval_length_scale();

            //------------------------------------------------------------------------------
            /**
             * return the length scale derivative wrt to a master dof type
             * @param[ in ] aDofTypes a dof type wrt which the derivative is evaluated
             */
            const Matrix< DDRMat >& dlengthscaledmasteru( const moris::Cell< MSI::Dof_Type >& aDofTypes );

            /**
             * evaluate the length scale derivative wrt to a master dof type
             * @param[ in ] aDofTypes a dof type wrt which the derivative is evaluated
             */
            void eval_dlengthscaledmasteru( const moris::Cell< MSI::Dof_Type >& aDofTypes );

            //------------------------------------------------------------------------------
        };
        //------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

#endif /* SRC_FEM_CL_FEM_SP_VELOCITY_DIRICHLET_NITSCHE_HPP_ */
