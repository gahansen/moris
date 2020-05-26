/*
 * cl_FEM_SP_Master_Weight_Interface.hpp
 *
 *  Created on: Nov 18, 2019
 *      Author: noel
 */

#ifndef PROJECTS_FEM_INT_SRC_CL_FEM_SP_MASTER_WEIGHT_INTERFACE_HPP_
#define PROJECTS_FEM_INT_SRC_CL_FEM_SP_MASTER_WEIGHT_INTERFACE_HPP_

#include <map>

#include "typedefs.hpp"                     //MRS/COR/src
#include "cl_Cell.hpp"                      //MRS/CON/src

#include "cl_Matrix.hpp"                    //LINALG/src
#include "linalg_typedefs.hpp"              //LINALG/src

#include "cl_FEM_Field_Interpolator.hpp"    //FEM/INT/src
#include "cl_FEM_Constitutive_Model.hpp"    //FEM/INT/src
#include "cl_FEM_Stabilization_Parameter.hpp"     //FEM/INT/src
#include "cl_FEM_Cluster.hpp"

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        class SP_Master_Weight_Interface : public Stabilization_Parameter
        {

            private:

                // Cluster measures for the SP
                real mMasterVolume     = 0.5; // volume on master
                real mSlaveVolume      = 0.5; // volume on slave
                real mInterfaceSurface = 1.0; // surface on master/slave interface

                //------------------------------------------------------------------------------
            public:

                // Property type for the SP
                enum class SP_Property_Type
                {
                    MATERIAL,
                    MAX_ENUM
                };

                // Local string to property enum map
                std::map< std::string, SP_Property_Type > mPropertyMap;

                //------------------------------------------------------------------------------
                /*
                 * constructor
                 */
                SP_Master_Weight_Interface();

                //------------------------------------------------------------------------------
                /**
                 * trivial destructor
                 */
                ~SP_Master_Weight_Interface(){};

                //------------------------------------------------------------------------------
                /**
                 * reset the cluster measures required for this SP
                 */
                void reset_cluster_measures();

                //------------------------------------------------------------------------------
                /**
                 * set property
                 * @param[ in ] aProperty       a property pointer
                 * @param[ in ] aPropertyString a string defining the property
                 * @param[ in ] aIsMaster       an enum for master or slave
                 */
                void set_property(
                        std::shared_ptr< Property > aProperty,
                        std::string                 aPropertyString,
                        mtk::Master_Slave           aIsMaster = mtk::Master_Slave::MASTER );

                //------------------------------------------------------------------------------
                /**
                 * evaluate the stabilization parameter value
                 */
                void eval_SP();

                //------------------------------------------------------------------------------
                /**
                 * evaluate the stabilization parameter derivative wrt to a master dof type
                 * @param[ in ] aDofTypes a dof type wrt which the derivative is evaluated
                 * dSPdMasterDOF ( 1 x numDerDof )
                 */
                void eval_dSPdMasterDOF( const moris::Cell< MSI::Dof_Type > & aDofTypes );

                //------------------------------------------------------------------------------
                /**
                 * evaluate the stabilization parameter derivative wrt to a slave dof type
                 * @param[ in ] aDofTypes a dof type wrt which the derivative is evaluated
                 * dSPdSlaveDOF ( 1 x numDerDof )
                 */
                void eval_dSPdSlaveDOF( const moris::Cell< MSI::Dof_Type > & aDofTypes );

                //------------------------------------------------------------------------------
                /**
                 * evaluate the penalty parameter derivative wrt to a master dv type
                 * @param[ in ] aDvTypes a dv type wrt which the derivative is evaluated
                 * dPPdMasterDV ( 1 x numDerDv )
                 */
                void eval_dSPdMasterDV( const moris::Cell< PDV_Type > & aDvTypes )
                {
                    MORIS_ERROR( false, "SP_Master_Weight_Interface::eval_dSPdMasterDV: not implemented." );
                }

                //------------------------------------------------------------------------------
                /**
                 * evaluate the penalty parameter derivative wrt to a slave dv type
                 * @param[ in ] aDvTypes a dv type wrt which the derivative is evaluated
                 * dSPdSlaveDV ( 1 x numDerDv )
                 */
                void eval_dSPdSlaveDV( const moris::Cell< PDV_Type > & aDvTypes )
                {
                    MORIS_ERROR( false, "SP_Master_Weight_Interface::eval_dSPdSlaveDV: not implemented." );
                }
                //------------------------------------------------------------------------------
        };
        //------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

#endif /* PROJECTS_FEM_INT_SRC_CL_FEM_SP_MASTER_WEIGHT_INTERFACE_HPP_ */
