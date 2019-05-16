/*
 * cl_FEM_Cluster.hpp
 *
 *  Created on: Apr 11, 2019
 *      Author: schmidt
 */
#include <iostream>

#include "cl_FEM_Element.hpp" //FEM/INT/src
#include "cl_FEM_Cluster.hpp"   //FEM/INT/src

namespace moris
{
    namespace fem
    {
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------

        void Cluster::compute_jacobian()
        {
            print(this->mTime ,"this->mTime ");
            print(mInterpolationCell->get_vertex_coords(),"mInterpolationCell->get_vertex_coords()");
            // set the IP geometry interpolator coefficients
            mElementBlock->get_block_IP_geometry_interpolator()->set_coeff( mInterpolationCell->get_vertex_coords(), this->mTime );
            // fixme param coeff from cluster
            mElementBlock->get_block_IP_geometry_interpolator()->set_param_coeff();

            //Fixme do this only once
            this->get_my_pdof_values();

            this->initialize_mJacobianElement();

            this->set_field_interpolators_coefficients();

            for ( uint Ik = 0; Ik < mInterpElements.size(); Ik++ )
            {
                mInterpElements( Ik )->compute_jacobian();
            }
        }

//------------------------------------------------------------------------------

        void Cluster::compute_residual()
        {
            print(this->mTime ,"this->mTime ");
            print(mInterpolationCell->get_vertex_coords(),"mInterpolationCell->get_vertex_coords()");
            // set the IP geometry interpolator coefficients
            mElementBlock->get_block_IP_geometry_interpolator()->set_coeff( mInterpolationCell->get_vertex_coords(), this->mTime );
            // fixme param coeff from cluster
            mElementBlock->get_block_IP_geometry_interpolator()->set_param_coeff();

            this->get_my_pdof_values();

            this->initialize_mResidualElement();

            this->set_field_interpolators_coefficients();

            for ( uint Ik = 0; Ik < mInterpElements.size(); Ik++ )
            {
                mInterpElements( Ik )->compute_residual();
            }
        }

//------------------------------------------------------------------------------

         void Cluster::initialize_mJacobianElement()
         {
//             mJacobianElement.resize( mElementBlock->get_num_interpolators() * mElementBlock->get_num_interpolators() );
//
//             uint tTotalDof = 0;
//             for( uint i = 0; i < mElementBlock->get_num_interpolators(); i++ )
//             {
//                 // get number of pdofs for the ith dof type
//                 uint tNumOfDofi = mElementBlock->get_block_field_interpolator()( i )->get_number_of_space_time_coefficients();
//
//                 // get total number of dof
//                 tTotalDof = tTotalDof + tNumOfDofi;
//
//                 for( uint j = 0; j < mElementBlock->get_num_interpolators(); j++ )
//                 {
//                     // get number of pdofs for the ith dof type
//                     uint tNumOfDofj = mElementBlock->get_block_field_interpolator()( j )->get_number_of_space_time_coefficients();
//
//                     // set mResidualElement size
//                     mJacobianElement( i * mElementBlock->get_num_interpolators() + j ).set_size( tNumOfDofi, tNumOfDofj, 0.0 );
//                 }
//             }

//             std::cout<<tTotalDof<<std::endl;
             uint tTotalDof = mElementBlock->get_total_number_of_dofs();
             mJacobian.set_size( tTotalDof, tTotalDof, 0.0 );
         }

//------------------------------------------------------------------------------

         void Cluster::initialize_mResidualElement()
         {
//             mResidualElement.resize( mElementBlock->get_num_interpolators() );
//
//             uint tTotalDof = 0;
//             for( uint i = 0; i < mElementBlock->get_num_interpolators(); i++ )
//             {
//                 // get number of pdofs for the ith dof type
//                 uint tNumOfDofi = mElementBlock->get_block_field_interpolator()( i )->get_number_of_space_time_coefficients();
//
//                 // get total number of dof
//                 tTotalDof = tTotalDof + tNumOfDofi;
//
//                 // set mResidualElement size
//                 mResidualElement( i ).set_size( tNumOfDofi, 1, 0.0 );
//             }

//             std::cout<<tTotalDof<<std::endl;
             mResidual.set_size( mElementBlock->get_total_number_of_dofs(), 1, 0.0 );
         }

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */
