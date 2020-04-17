/*
 * cl_FEM_SP_Velocity_Dirichlet_Nitsche.hpp
 *
 *  Created on: Mar 25, 2020
 *  Author: noel
 */

#ifndef SRC_FEM_CL_FEM_SP_VELOCITY_DIRICHLET_NITSCHE_HPP_
#define SRC_FEM_CL_FEM_SP_VELOCITY_DIRICHLET_NITSCHE_HPP_

#include <map>
//MRS/CON/src
#include "typedefs.hpp"
#include "cl_Cell.hpp"
//LINALG/src
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
//FEM/INT/src
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
     * Stabilization parameter for Dirichlet BC on velocity for fluid problem
     * applied with Nitsche's formulation
     * gamma_N = alpha_N * ( viscosity / h + density * norm_inf( u ) / 6.0 )
     * from Schott et al. (2015)
     */
        class SP_Velocity_Dirichlet_Nitsche : public Stabilization_Parameter
        {

//------------------------------------------------------------------------------
        private:

            // element size
            real mElementSize = 1.0;

        public:

            // property type for the SP
            enum class Property_Type
            {
                VISCOSITY,  // fluid viscosity
                DENSITY,    // fluid density
                MAX_ENUM
            };

            // local string to property enum map
            std::map< std::string, Property_Type > mPropertyMap;

            /*
             * Rem: mParameters( 0 ) - alpha_N
             */

//------------------------------------------------------------------------------
            /*
             * constructor
             */
            SP_Velocity_Dirichlet_Nitsche()
            {
                // set the property pointer cell size
                mMasterProp.resize( static_cast< uint >( Property_Type::MAX_ENUM ), nullptr );

                // populate the map
                mPropertyMap[ "Viscosity" ] = Property_Type::VISCOSITY;
                mPropertyMap[ "Density" ]   = Property_Type::DENSITY;

                // populate the dof map (default)
                mMasterDofMap[ "Velocity" ] = MSI::Dof_Type::VX;
            }

//------------------------------------------------------------------------------
            /**
             * trivial destructor
             */
            ~SP_Velocity_Dirichlet_Nitsche(){};

//------------------------------------------------------------------------------
            /**
             * reset the cluster measures required for this SP
             */
            void reset_cluster_measures()
            {
                // evaluate element size from the cluster
                mElementSize = mCluster->compute_cluster_cell_length_measure( mtk::Primary_Void::PRIMARY,
                                                                              mtk::Master_Slave::MASTER );
            }

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
                             "SP_Velocity_Dirichlet_Nitsche::set_property - Unknown aPropertyString." );

                // set the property in the property cell
                this->get_properties( aIsMaster )( static_cast< uint >( mPropertyMap[ aPropertyString ] ) ) = aProperty;
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
            void eval_dSPdMasterDOF( const moris::Cell< MSI::Dof_Type > & aDofTypes );

//------------------------------------------------------------------------------
            /**
             * evaluate the penalty parameter derivative wrt to a master dv type
             * @param[ in ] aDvTypes a dv type wrt which the derivative is evaluated
             */
            void eval_dSPdMasterDV( const moris::Cell< GEN_DV > & aDvTypes )
            {
                MORIS_ERROR( false, "SP_Velocity_Dirichlet_Nitsche::eval_dSPdMasterDV - not implemented." );
            }

//------------------------------------------------------------------------------
        };
//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

#endif /* SRC_FEM_CL_FEM_SP_VELOCITY_DIRICHLET_NITSCHE_HPP_ */