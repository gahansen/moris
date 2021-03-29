
//FEM/INT/src
#include "cl_FEM_SP_Compressible_Dirichlet_Nitsche.hpp"
#include "cl_FEM_Cluster.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"

namespace moris
{
    namespace fem
    {

        //------------------------------------------------------------------------------
        
        SP_Compressible_Dirichlet_Nitsche::SP_Compressible_Dirichlet_Nitsche()
        {
            // set the property pointer cell size
            mMasterProp.resize( static_cast< uint >( Property_Type::MAX_ENUM ), nullptr );

            // populate the map
            mPropertyMap[ "DynamicViscosity" ] = static_cast< uint >( Property_Type::VISCOSITY );
            mPropertyMap[ "ThermalConductivity" ] = static_cast< uint >( Property_Type::CONDUCTIVITY );
        }

        //------------------------------------------------------------------------------

        void SP_Compressible_Dirichlet_Nitsche::reset_cluster_measures()
        {
            // evaluate element size from the cluster
            mElementSize = mCluster->compute_cluster_cell_length_measure(
                    mtk::Primary_Void::PRIMARY,
                    mtk::Master_Slave::MASTER );
        }

        //------------------------------------------------------------------------------

        void SP_Compressible_Dirichlet_Nitsche::set_dof_type_list(
                moris::Cell< moris::Cell< MSI::Dof_Type > > & aDofTypes,
                moris::Cell< std::string >                  & aDofStrings,
                mtk::Master_Slave                             aIsMaster )
        {
            // switch on master slave
            switch ( aIsMaster )
            {
                case mtk::Master_Slave::MASTER :
                {
                    // set dof type list
                    mMasterDofTypes = aDofTypes;

                    // loop on dof type
                    for( uint iDof = 0; iDof < aDofTypes.size(); iDof++ )
                    {
                        // get dof string
                        std::string tDofString = aDofStrings( iDof );

                        // get dof type
                        MSI::Dof_Type tDofType = aDofTypes( iDof )( 0 );

                        // if velocity
                        if( tDofString == "Velocity" )
                        {
                            mMasterDofVelocity = tDofType;
                        }
                        else
                        {
                            // create error message
                            std::string tErrMsg =
                                    std::string( "SP_Compressible_Dirichlet_Nitsche::set_dof_type_list - Unknown aDofString : ") +
                                    tDofString;
                            MORIS_ERROR( false , tErrMsg.c_str() );
                        }
                    }
                    break;
                }

                case mtk::Master_Slave::SLAVE :
                {
                    // set dof type list
                    mSlaveDofTypes = aDofTypes;
                    break;
                }

                default:
                    MORIS_ERROR( false, "SP_Compressible_Dirichlet_Nitsche::set_dof_type_list - unknown master slave type." );
            }
        }

        //------------------------------------------------------------------------------

        void SP_Compressible_Dirichlet_Nitsche::eval_SP()
        {
            // get the viscosity and density property
            std::shared_ptr< Property > & tPropViscosity    = mMasterProp( static_cast< uint >( Property_Type::VISCOSITY ) );
            std::shared_ptr< Property > & tPropThermConduct = mMasterProp( static_cast< uint >( Property_Type::CONDUCTIVITY ) );

            // time step size
            real tDeltat = mMasterFIManager->get_IP_geometry_interpolator()->get_time_step();

            // set correct size for the vector of values
            mPPVal.set_size( mSpaceDim + 2, 1, 0.0 );

            // check size of input paramters
            MORIS_ASSERT( mParameters.size() == mSpaceDim + 2, 
                    "SP_Compressible_Dirichlet_Nitsche::eval_SP() - number of input parameters incorrect, relative to number of spatial dimensions" );

            // compute the contribution to the first equation
            mPPVal( 0 ) = mParameters( 0 )( 0 ) * tDeltat / mElementSize;

            // compute contribution to the last equation
            mPPVal( mSpaceDim + 1 ) = mParameters( mSpaceDim + 1 )( 0 ) * tPropThermConduct->val()( 0 ) / mElementSize;

            // compute stabilization parameter value for velocity residual
            for ( uint iDim = 0; iDim < mSpaceDim; iDim++ )
            {
                mPPVal( iDim + 1 ) = mParameters( iDim + 1 )( 0 ) * ( tPropViscosity->val()( 0 ) / mElementSize );
            }
        }

        //------------------------------------------------------------------------------

        void SP_Compressible_Dirichlet_Nitsche::eval_dSPdMasterDOF(
                const moris::Cell< MSI::Dof_Type > & aDofTypes )
        {
            // get the dof type index
            uint tDofIndex = mMasterGlobalDofTypeMap( static_cast< uint >( aDofTypes( 0 ) ) );

            // get the dof type FI
            Field_Interpolator * tFIDerivative =
                    mMasterFIManager->get_field_interpolators_for_type( aDofTypes( 0 ) );

            // get number of space time basis functions
            uint tNumBases = tFIDerivative->get_number_of_space_time_coefficients();

            // set size for dSPdMasterDof
            mdPPdMasterDof( tDofIndex ).set_size( mSpaceDim + 2, tNumBases, 0.0 );

            // get the viscosity and density property
            std::shared_ptr< Property > & tPropViscosity    = mMasterProp( static_cast< uint >( Property_Type::VISCOSITY ) );
            std::shared_ptr< Property > & tPropThermConduct = mMasterProp( static_cast< uint >( Property_Type::CONDUCTIVITY ) );

            // compute stabilization parameter deriviative value for velocity residual
            for ( uint iDim = 0; iDim < mSpaceDim; iDim++ )
            {
                mdPPdMasterDof( tDofIndex )( { iDim + 1, iDim + 1 }, { 0, tNumBases } ) +=
                        mParameters( iDim + 1 )( 0 ) * tPropViscosity->dPropdDOF( aDofTypes ) / mElementSize;
            }

            // compute stabilization parameter deriviative value for temperature residual
            if( tPropThermConduct->check_dof_dependency( aDofTypes ) )
            {
                // compute contribution from thermal conductivity
                mdPPdMasterDof( tDofIndex )( { mSpaceDim + 1, mSpaceDim + 1 }, { 0, tNumBases } ) +=
                        mParameters( mSpaceDim + 1 )( 0 ) * tPropThermConduct->dPropdDOF( aDofTypes ) / mElementSize;
            }
        }

        //------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

