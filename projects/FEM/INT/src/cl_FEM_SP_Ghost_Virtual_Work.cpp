
#include "cl_FEM_SP_Ghost_Virtual_Work.hpp" //FEM/INT/src
#include "cl_FEM_Cluster.hpp"              //FEM/INT/src
#include "cl_FEM_Field_Interpolator_Manager.hpp"              //FEM/INT/src

namespace moris
{
    namespace fem
    {

//------------------------------------------------------------------------------
        void SP_Ghost_Virtual_Work::eval_SP()
        {
            // compute stabilization parameter value
            mPPVal = mParameters( 0 ) * std::pow( mElementSize, 2 * ( mOrder - 1 ) + 1 );
        }

//------------------------------------------------------------------------------
        void SP_Ghost_Virtual_Work::reset_cluster_measures()
        {
            // evaluate element size from the cluster
            mElementSize = mCluster->compute_cluster_cell_length_measure( mtk::Primary_Void::PRIMARY,
                                                                          mtk::Master_Slave::MASTER );
        }

//------------------------------------------------------------------------------
        void SP_Ghost_Virtual_Work::eval_dSPdMasterDOF( const moris::Cell< MSI::Dof_Type > & aDofTypes )
        {
            // get the dof type as a uint
            uint tDofType = static_cast< uint >( aDofTypes( 0 ) );

            // get the dof type index
            uint tDofIndex = mMasterGlobalDofTypeMap( tDofType );

            // reset the matrix
            mdPPdMasterDof( tDofIndex ).set_size( 1, mMasterFIManager->get_field_interpolators_for_type( aDofTypes( 0 ) )->get_number_of_space_time_coefficients(), 0.0 );
        }

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */


