/*
 * cl_FEM_CM_Struc_Linear_Isotropic.hpp
 *
 *  Created on: Sep 17, 2019
 *      Author: noel
 */

#ifndef SRC_FEM_CL_FEM_CM_STRUC_LINEAR_ISOTROPIC_HPP_
#define SRC_FEM_CL_FEM_CM_STRUC_LINEAR_ISOTROPIC_HPP_

#include "typedefs.hpp"                     //MRS/COR/src
#include "cl_Cell.hpp"                      //MRS/CON/src

#include "cl_Matrix.hpp"                    //LINALG/src
#include "linalg_typedefs.hpp"              //LINALG/src

#include "cl_FEM_Field_Interpolator.hpp"    //FEM/INT/src
#include "cl_FEM_Constitutive_Model.hpp"    //FEM/INT/src

namespace moris
{
    namespace fem
    {
//------------------------------------------------------------------------------

        class CM_Struc_Linear_Isotropic : public Constitutive_Model
        {

//------------------------------------------------------------------------------
        public:
            enum class Property_Type
            {
                EMOD,
                NU,
                CTE,
                TEMP_REF,
                MAX_ENUM
            };

            // Local string to property enum map
            std::map< std::string, CM_Struc_Linear_Isotropic::Property_Type > mPropertyMap;

        private:
            // Plane stress or plane strain
            Model_Type mModelType = Model_Type::UNDEFINED;

//------------------------------------------------------------------------------
        public:
            /*
             * trivial constructor
             */
            CM_Struc_Linear_Isotropic()
            {
                // set the constitutive type
                mConstitutiveType = fem::Constitutive_Type::STRUC_LIN_ISO;

                // set the property pointer cell size
                mProperties.resize( static_cast< uint >( CM_Struc_Linear_Isotropic::Property_Type::MAX_ENUM ), nullptr );

                // populate the map
                mPropertyMap[ "YoungsModulus" ]         = CM_Struc_Linear_Isotropic::Property_Type::EMOD;
                mPropertyMap[ "PoissonRatio" ]          = CM_Struc_Linear_Isotropic::Property_Type::NU;
                mPropertyMap[ "CTE" ]                   = CM_Struc_Linear_Isotropic::Property_Type::CTE;
                mPropertyMap[ "ReferenceTemperature" ]  = CM_Struc_Linear_Isotropic::Property_Type::TEMP_REF;

            };

//------------------------------------------------------------------------------
            /**
             * trivial destructor
             */
            ~CM_Struc_Linear_Isotropic(){};

//------------------------------------------------------------------------------
            /**
             * set a property pointer
             * @param[ in ] aProperty     a property pointer
             * @param[ in ] aPropertyType a string defining the property
             */
             void set_property( std::shared_ptr< fem::Property > aProperty,
                                std::string                      aPropertyString )
             {
                 // FIXME check that property type make sense?

                 // set the property in the property cell
                 mProperties( static_cast< uint >( mPropertyMap[ aPropertyString ] ) ) = aProperty;
             };

//------------------------------------------------------------------------------
            /**
             * evaluate the constitutive model flux
             * @param[ in ] aFlux a matrix to fill with evaluation
             */
            void eval_flux();

//------------------------------------------------------------------------------
            /**
             * evaluate the constitutive model test flux
             */
            void eval_testFlux();

//------------------------------------------------------------------------------
            /**
             * evaluate the constitutive model traction
             * @param[ in ] aNormal normal
             */
            void eval_traction( const Matrix< DDRMat > & aNormal );

//------------------------------------------------------------------------------
            /**
             * evaluate the constitutive model test traction
             * @param[ in ] aNormal   normal
             */
            void eval_testTraction( const Matrix< DDRMat > & aNormal );

//------------------------------------------------------------------------------
            /**
             * evaluate the constitutive model strain
             * @param[ in ] aStrain a matrix to fill with evaluation
             */
            void eval_strain();

//------------------------------------------------------------------------------
            /**
             * evaluate the constitutive model test strain
             * @param[ in ] aTestStrain a matrix to fill with evaluation
             */
            void eval_testStrain();

//------------------------------------------------------------------------------
            /**
             * evaluate the constitutive model matrix
             * @param[ in ] aConst a matrix to fill with evaluation
             */
            void eval_const();

//------------------------------------------------------------------------------
            /**
             * evaluate the constitutive model flux derivative wrt to a dof type
             * @param[ in ] aDofTypes  a dof type wrt which the derivative is evaluated
             * @param[ in ] adFluxdDOF a matrix to fill with derivative evaluation
             */
            void eval_dFluxdDOF( const moris::Cell< MSI::Dof_Type > & aDofTypes );

//------------------------------------------------------------------------------
            /**
             * evaluate the constitutive model traction derivative wrt to a dof type
             * @param[ in ] aDofTypes a dof type wrt which the derivative is evaluated
             * @param[ in ] aNormal   normal
             */
            void eval_dTractiondDOF( const moris::Cell< MSI::Dof_Type > & aDofTypes,
                                     const Matrix< DDRMat >             & aNormal );

//------------------------------------------------------------------------------
            /**
             * evaluate the constitutive model test traction derivative wrt to a dof type
             * @param[ in ] aDofTypes a dof type wrt which the derivative is evaluated
             * @param[ in ] aNormal   normal
             */
            void eval_dTestTractiondDOF( const moris::Cell< MSI::Dof_Type > & aDofTypes,
                                         const Matrix< DDRMat >             & aNormal,
                                         const Matrix< DDRMat >             & aJump );

//------------------------------------------------------------------------------
            /**
             * evaluate the constitutive model strain derivative wrt to a dof type
             * @param[ in ] aDofTypes    a dof type wrt which the derivative is evaluated
             * @param[ in ] adStraindDOF a matrix to fill with derivative evaluation
             */
            void eval_dStraindDOF( const moris::Cell< MSI::Dof_Type > & aDofTypes );

//------------------------------------------------------------------------------
            /**
             * evaluate the constitutive model matrix derivative wrt to a dof type
             * @param[ in ] aDofTypes   a dof type wrt which the derivative is evaluated
             * @param[ in ] adConstdDOF a matrix to fill with derivative evaluation
             */
            void eval_dConstdDOF( const moris::Cell< MSI::Dof_Type > & aDofTypes );

//------------------------------------------------------------------------------

            void flatten_normal( const Matrix< DDRMat > & aNormal,
                                       Matrix< DDRMat > & aFlattenedNormal );

//------------------------------------------------------------------------------

            void get_isotropic_thermal_expansion_vector( Matrix< DDRMat > & aTheramlExpansionVector );

//------------------------------------------------------------------------------

            /**
             * Sets the option to use a plane stress or plane strain elasticity model
             *
             * @param aModelType Either Model_Type::PLANE_STRESS or Model_Type::PLANE_STRAIN. Default
             * is Model_Type::UNDEFINED which uses neither.
             */
            void set_model_type(Model_Type aModelType);

//------------------------------------------------------------------------------
        };
//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

#endif /* SRC_FEM_CL_FEM_CM_STRUC_LINEAR_ISOTROPIC_HPP_ */
