/*
 * cl_FEM_IQI_Latent_Heat_Absorption.hpp
 *
 *  Created on: Jul 10, 2020
 *      Author: wunsch
 */

#ifndef PROJECTS_FEM_INT_SRC_CL_FEM_IQI_LATENT_HEAT_ABSORPTION_HPP_
#define PROJECTS_FEM_INT_SRC_CL_FEM_IQI_LATENT_HEAT_ABSORPTION_HPP_

#include <map>

#include "typedefs.hpp"                     //MRS/COR/src
#include "cl_Cell.hpp"                      //MRS/CON/src

#include "cl_Matrix.hpp"                    //LINALG/src
#include "linalg_typedefs.hpp"              //LINALG/src

#include "cl_FEM_IQI.hpp"                   //FEM/INT/src

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        class IQI_Latent_Heat_Absorption : public IQI
        {

                //------------------------------------------------------------------------------

                enum class IQI_Property_Type
                {
                        DENSITY,
                        LATENT_HEAT,
                        PC_TEMP,
                        PHASE_STATE_FUNCTION,
                        PHASE_CHANGE_CONST,
                        MAX_ENUM
                };

                // Local string to property enum map
                std::map< std::string, IQI_Property_Type > mPropertyMap;

            public:
                //------------------------------------------------------------------------------
                /*
                 * constructor
                 */
                IQI_Latent_Heat_Absorption();

                //------------------------------------------------------------------------------
                /**
                 * trivial destructor
                 */
                ~IQI_Latent_Heat_Absorption(){};

                //------------------------------------------------------------------------------
                /**
                 * set property
                 * @param[ in ] aProperty       a property pointer
                 * @param[ in ] aPropertyString a string describing the property
                 * @param[ in ] aIsMaster       enum master or slave
                 */
                void set_property(
                        std::shared_ptr< Property > aProperty,
                        std::string                 aPropertyString,
                        mtk::Master_Slave           aIsMaster = mtk::Master_Slave::MASTER );

            private:

                //------------------------------------------------------------------------------
                /**
                 * compute the quantity of interest
                 * @param[ in ] aQI quantity of interest matrix to fill
                 */
                void compute_QI( Matrix< DDRMat > & aQI );

                //------------------------------------------------------------------------------
                /**
                 * compute the derivative of the quantity of interest wrt dof types
                 * @param[ in ] aDofType group of dof types wrt which derivatives are evaluated
                 * @param[ in ] adQIdu   derivative of quantity of interest matrix to fill
                 */
                void compute_dQIdu(
                        moris::Cell< MSI::Dof_Type > & aDofType,
                        Matrix< DDRMat >             & adQIdu );

                //------------------------------------------------------------------------------
        };
    }/* end namespace fem */
} /* end namespace moris */

#endif /* PROJECTS_FEM_INT_SRC_CL_FEM_IQI_LATENT_HEAT_ABSORPTION_HPP_ */
