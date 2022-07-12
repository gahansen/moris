#include "cl_FEM_Set.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_IQI_Jump_Traction.hpp"
#include "fn_dot.hpp"

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        IQI_Jump_Traction::IQI_Jump_Traction()
        {
            mFEMIQIType = fem::IQI_Type::JUMP_TRACTION;

            // set size for the constitutive model pointer cell
            mMasterCM.resize( static_cast< uint >( IQI_Constitutive_Type::MAX_ENUM ), nullptr );
            mSlaveCM.resize( static_cast< uint >( IQI_Constitutive_Type::MAX_ENUM ), nullptr );

            // populate the constitutive map
            mConstitutiveMap[ "ElastLinIso" ] = static_cast< uint >( IQI_Constitutive_Type::ELAST_LIN_ISO );
        }

        //------------------------------------------------------------------------------

        void
        IQI_Jump_Traction::compute_QI( Matrix< DDRMat >& aQI )
        {
            // get the elasticity constitutive model
            const std::shared_ptr< Constitutive_Model >& tCMMasterElasticity =
                    mMasterCM( static_cast< uint >( IQI_Constitutive_Type::ELAST_LIN_ISO ) );
            const std::shared_ptr< Constitutive_Model >& tCMSlaveElasticity =
                    mSlaveCM( static_cast< uint >( IQI_Constitutive_Type::ELAST_LIN_ISO ) );

            // evaluate average traction difference
            const Matrix< DDRMat > tTractionJump =
                    tCMMasterElasticity->traction( mNormal ) - tCMSlaveElasticity->traction( mNormal );

            // based on the IQI index select the norm or the individual component
            switch ( mIQITypeIndex )
            {
                case -1:
                {
                    aQI = dot( tTractionJump, tTractionJump );
                    break;
                }
                case 0:
                {
                    aQI = { tTractionJump( 0 ) };
                    break;
                }
                case 1:
                {
                    aQI = { tTractionJump( 1 ) };
                    break;
                }
                case 2:
                {
                    aQI = { tTractionJump( 2 ) };
                    break;
                }

                default:
                {
                    MORIS_ERROR( false,
                            "IQI_Jump_Traction::compute_QI - incorrect vector index." );
                }
            }
        }

        //------------------------------------------------------------------------------

        void
        IQI_Jump_Traction::compute_QI( real aWStar )
        {
            // get index for QI
            sint tQIIndex = mSet->get_QI_assembly_index( mName );

            // get the elasticity constitutive model
            const std::shared_ptr< Constitutive_Model >& tCMMasterElasticity =
                    mMasterCM( static_cast< uint >( IQI_Constitutive_Type::ELAST_LIN_ISO ) );
            const std::shared_ptr< Constitutive_Model >& tCMSlaveElasticity =
                    mSlaveCM( static_cast< uint >( IQI_Constitutive_Type::ELAST_LIN_ISO ) );

            // evaluate average traction difference
            const Matrix< DDRMat > tTractionJump =
                    tCMMasterElasticity->traction( mNormal ) - tCMSlaveElasticity->traction( mNormal );

            // initialize the matrix
            Matrix< DDRMat > tMat;

            // based on the IQI index select the norm or the individual component
            switch ( mIQITypeIndex )
            {
                case -1:
                {
                    tMat = dot( tTractionJump, tTractionJump );
                    break;
                }
                case 0:
                {
                    tMat = { tTractionJump( 0 ) };
                    break;
                }
                case 1:
                {
                    tMat = { tTractionJump( 1 ) };
                    break;
                }
                case 2:
                {
                    tMat = { tTractionJump( 2 ) };
                    break;
                }

                default:
                {
                    MORIS_ERROR( false,
                            "IQI_Jump_Traction::compute_QI - incorrect vector index." );
                }
            }

            mSet->get_QI()( tQIIndex ) += aWStar * tMat;
        }

        //------------------------------------------------------------------------------

        void
        IQI_Jump_Traction::compute_dQIdu( real aWStar )
        {
            MORIS_ERROR( false, "Not Implemented for psedudo error for double sided set " );
        }

        //------------------------------------------------------------------------------

        void
        IQI_Jump_Traction::compute_dQIdu(
                moris::Cell< MSI::Dof_Type >& aDofType,
                Matrix< DDRMat >&             adQIdu )
        {
            MORIS_ERROR( false, "Not Implemented for psedudo error for double sided set " );
        }

        //------------------------------------------------------------------------------

        //------------------------------------------------------------------------------

    } /* end namespace fem */
} /* end namespace moris */
