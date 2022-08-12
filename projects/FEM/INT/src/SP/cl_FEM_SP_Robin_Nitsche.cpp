// FEM/INT/src
#include "cl_FEM_SP_Robin_Nitsche.hpp"
#include "cl_FEM_Field_Interpolator.hpp"    //FEM/INT/src
#include "cl_FEM_Cluster.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"

namespace moris
{
    namespace fem
    {

        //------------------------------------------------------------------------------

        SP_Robin_Nitsche::SP_Robin_Nitsche()
        {
            // set the property pointer cell size
            mMasterProp.resize( static_cast< uint >( Property_Type::MAX_ENUM ), nullptr );

            // populate the map
            mPropertyMap[ "NeumannPenalty" ] = static_cast< uint >( Property_Type::NEUMANN_PENALTY );
        }

        //------------------------------------------------------------------------------

        void
        SP_Robin_Nitsche::set_dof_type_list(
                moris::Cell< moris::Cell< MSI::Dof_Type > >& aDofTypes,
                moris::Cell< std::string >&                  aDofStrings,
                mtk::Master_Slave                            aIsMaster )
        {
            // switch on master slave
            switch ( aIsMaster )
            {
                case mtk::Master_Slave::MASTER:
                {
                    // set dof type list
                    mMasterDofTypes = aDofTypes;

                    // loop on dof type
                    for ( uint iDof = 0; iDof < aDofTypes.size(); iDof++ )
                    {
                        // get dof string
                        std::string tDofString = aDofStrings( iDof );

                        // get dof type
                        MSI::Dof_Type tDofType = aDofTypes( iDof )( 0 );

                        // if velocity
                        if ( tDofString == "THETA" )
                        {
                            mMasterDofTemp = tDofType;
                        }
                        else
                        {
                            // create error message
                            std::string tErrMsg =
                                    std::string( "SP_Velocity_SlipBoundary_Nitsche::set_dof_type_list - Unknown aDofString : " ) + tDofString;
                            MORIS_ERROR( false, tErrMsg.c_str() );
                        }
                    }
                    break;
                }

                case mtk::Master_Slave::SLAVE:
                {
                    // set dof type list
                    mSlaveDofTypes = aDofTypes;
                    break;
                }

                default:
                    MORIS_ERROR( false, "SP_Velocity_SlipBoundary_Nitsche::set_dof_type_list - unknown master slave type." );
            }
        }

        //------------------------------------------------------------------------------

        moris::Cell< std::tuple<
                fem::Measure_Type,
                mtk::Primary_Void,
                mtk::Master_Slave > >
        SP_Robin_Nitsche::get_cluster_measure_tuple_list()
        {
            return { mElementSizeTuple };
        }

        //------------------------------------------------------------------------------

        void
        SP_Robin_Nitsche::eval_SP()
        {
            // get element size cluster measure value
            real tElementSize = mCluster->get_cluster_measure(
                                                std::get< 0 >( mElementSizeTuple ),
                                                std::get< 1 >( mElementSizeTuple ),
                                                std::get< 2 >( mElementSizeTuple ) )
                                        ->val()( 0 );

            const std::shared_ptr< Property >& tPropNeumannPen =
                    mMasterProp( static_cast< uint >( Property_Type::NEUMANN_PENALTY ) );

            // check that properties are set
            MORIS_ASSERT( tPropNeumannPen,
                    "SP_Robin_Nitsche::eval_SP - slip length need to be defined.\n" );

            // set size of vector of stabilization values
            mPPVal.set_size( 2, 1 );

            // compute stabilization parameters for tangential direction
            // note: stabilization parameter mParameters( 2 )( 0 ) is 1/gamma^t in Juntunen abd Stenberg 2009
            mPPVal( 0 ) = mParameters( 0 )( 0 ) / ( mParameters( 0 )( 0 ) * tPropNeumannPen->val()( 0 ) + tElementSize );
            mPPVal( 1 ) = tElementSize / ( mParameters( 0 )( 0 ) * tPropNeumannPen->val()( 0 ) + tElementSize );
        }

        //------------------------------------------------------------------------------

        void
        SP_Robin_Nitsche::eval_dSPdMasterDOF(
                const moris::Cell< MSI::Dof_Type >& aDofTypes )
        {
            // get element size cluster measure value
            real tElementSize = mCluster->get_cluster_measure(
                                                std::get< 0 >( mElementSizeTuple ),
                                                std::get< 1 >( mElementSizeTuple ),
                                                std::get< 2 >( mElementSizeTuple ) )
                                        ->val()( 0 );

            // get the dof type index
            const uint tDofIndex = mMasterGlobalDofTypeMap( static_cast< uint >( aDofTypes( 0 ) ) );
            // get the dof type FI
            Field_Interpolator* tFIDerivative =
                    mMasterFIManager->get_field_interpolators_for_type( aDofTypes( 0 ) );

            // get number of dofs
            const uint tNumDofs = tFIDerivative->get_number_of_space_time_coefficients();

            // set size for dSPdMasterDof
            mdPPdMasterDof( tDofIndex ).set_size( 2, tNumDofs );

            const std::shared_ptr< Property >& tPropNeumannPen =
                    mMasterProp( static_cast< uint >( Property_Type::NEUMANN_PENALTY ) );

            // if slip length depend on the dof
            if ( tPropNeumannPen->check_dof_dependency( aDofTypes ) )
            {
                // get the derivative of the first paramater and second parameter
                mdPPdMasterDof( tDofIndex ).get_row( 0 ) = -std::pow( mParameters( 0 )( 0 ) / ( mParameters( 0 )( 0 ) * tPropNeumannPen->val()( 0 ) + tElementSize ), 2.0 )    //
                                                         * tPropNeumannPen->dPropdDOF( aDofTypes );
                mdPPdMasterDof( tDofIndex ).get_row( 1 ) = -std::pow( tElementSize / ( mParameters( 0 )( 0 ) * tPropNeumannPen->val()( 0 ) + tElementSize ), 2.0 )    //
                                                         * tPropNeumannPen->dPropdDOF( aDofTypes );
            }
        }

        //------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */