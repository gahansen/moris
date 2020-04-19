/*
 * cl_FEM_IWG_Isotropic_Struc_Linear_Contact_Penalty.hpp
 *
 *  Created on: Jan 27, 2020
 *      Author: ritzert
 */

#ifndef PROJECTS_FEM_INT_SRC_CL_FEM_IWG_ISOTROPIC_STRUC_LINEAR_CONTACT_PENALTY_HPP_
#define PROJECTS_FEM_INT_SRC_CL_FEM_IWG_ISOTROPIC_STRUC_LINEAR_CONTACT_PENALTY_HPP_

#include <map>

#include "typedefs.hpp"                     //MRS/COR/src
#include "cl_Cell.hpp"                      //MRS/CON/src

#include "cl_Matrix.hpp"                    //LINALG/src
#include "linalg_typedefs.hpp"              //LINALG/src

#include "cl_FEM_Field_Interpolator.hpp"    //FEM/INT/src
#include "cl_FEM_IWG.hpp"                   //FEM/INT/src

namespace moris
{
    namespace fem
    {
//------------------------------------------------------------------------------

        class IWG_Isotropic_Struc_Linear_Contact_Penalty : public IWG
        {

        public:
            enum class IWG_Property_Type
            {
                MAX_ENUM
            };
            // Local string to property enum map
            std::map< std::string, IWG_Property_Type > mPropertyMap;

            enum class IWG_Constitutive_Type
            {
                ELAST_LIN_ISO,
                MAX_ENUM
            };

            // Local string to constitutive enum map
            std::map< std::string, IWG_Constitutive_Type > mConstitutiveMap;

            enum class IWG_Stabilization_Type
            {
                NITSCHE_INTERFACE,
                MAX_ENUM
            };

            // Local string to constitutive enum map
            std::map< std::string, IWG_Stabilization_Type > mStabilizationMap; // whats that?

            real mStabParam = 1500;

//------------------------------------------------------------------------------
            /*
             * constructor
             */
            IWG_Isotropic_Struc_Linear_Contact_Penalty();

//------------------------------------------------------------------------------
            /**
             * trivial destructor
             */
            ~IWG_Isotropic_Struc_Linear_Contact_Penalty(){};

//------------------------------------------------------------------------------
            /**
             * set property
             * @param[ in ] aProperty       a property pointer
             * @param[ in ] aPropertyString a string defining the property
             * @param[ in ] aIsMaster       an enum for master or slave
             */
            void set_property( std::shared_ptr< Property > aProperty,
                               std::string                 aPropertyString,
                               mtk::Master_Slave           aIsMaster = mtk::Master_Slave::MASTER )
            {
                // check that aPropertyString makes sense
                MORIS_ERROR( mPropertyMap.find( aPropertyString ) != mPropertyMap.end(),
                             "IWG_Isotropic_Struc_Linear_Contact_Penalty::set_property - Unknown aPropertyString." );

                // set the property in the property cell
                this->get_properties( aIsMaster )( static_cast< uint >( mPropertyMap[ aPropertyString ] ) ) = aProperty;
            }

//------------------------------------------------------------------------------
            /**
             * set constitutive model
             * @param[ in ] aConstitutiveModel  a constitutive model pointer
             * @param[ in ] aConstitutiveString a string defining the constitutive model
             * @param[ in ] aIsMaster           an enum for master or slave
             */
            void set_constitutive_model( std::shared_ptr< Constitutive_Model > aConstitutiveModel,
                                         std::string                           aConstitutiveString,
                                         mtk::Master_Slave                     aIsMaster = mtk::Master_Slave::MASTER )
            {
                // check that aConstitutiveString makes sense
                MORIS_ERROR( mConstitutiveMap.find( aConstitutiveString ) != mConstitutiveMap.end(),
                             "IWG_Isotropic_Struc_Linear_Contact_Penalty::set_constitutive_model - Unknown aConstitutiveString." );

                // set the constitutive model in the constitutive model cell
                this->get_constitutive_models( aIsMaster )( static_cast< uint >( mConstitutiveMap[ aConstitutiveString ] ) ) = aConstitutiveModel;
            }
//------------------------------------------------------------------------------
            /**
             * set stabilization parameter
             * @param[ in ] aStabilizationParameter a stabilization parameter pointer
             * @param[ in ] aStabilizationString    a string defining the stabilization parameter
             */
            void set_stabilization_parameter( std::shared_ptr< Stabilization_Parameter > aStabilizationParameter,
                                              std::string                                aStabilizationString )
            {
                // check that aConstitutiveString makes sense
                MORIS_ERROR( mStabilizationMap.find( aStabilizationString ) != mStabilizationMap.end(),
                             "IWG_Isotropic_Struc_Linear_Contact_Penalty::set_stabilization_parameter - Unknown aStabilizationString." );

                // set the stabilization parameter in the stabilization parameter cell
                this->get_stabilization_parameters()( static_cast< uint >( mStabilizationMap[ aStabilizationString ] ) ) = aStabilizationParameter;
            }

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
            void compute_drdpdv( real aWStar );

//------------------------------------------------------------------------------
        };
//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */


#endif /* PROJECTS_FEM_INT_SRC_CL_FEM_IWG_ISOTROPIC_STRUC_LINEAR_CONTACT_PENALTY_HPP_ */
