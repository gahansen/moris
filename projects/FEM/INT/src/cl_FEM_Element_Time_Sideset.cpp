#include <iostream>
//FEM/INT/src
#include "cl_FEM_Element_Time_Sideset.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_Set.hpp"
//FEM/MSI/src
#include "cl_MSI_Equation_Model.hpp"
#include "cl_MSI_Design_Variable_Interface.hpp"

namespace moris
{
    namespace fem
    {

        //------------------------------------------------------------------------------

        Element_Time_Sideset::Element_Time_Sideset(
                mtk::Cell const  * aCell,
                Set              * aElementBlock,
                Cluster          * aCluster,
                moris::moris_index aCellIndexInCluster )
        : Element( aCell, aElementBlock, aCluster, aCellIndexInCluster )
        {}

        //------------------------------------------------------------------------------

        Element_Time_Sideset::~Element_Time_Sideset(){}

        //------------------------------------------------------------------------------

        void Element_Time_Sideset::init_ig_geometry_interpolator()
        {
            // get geometry interpolator
            Geometry_Interpolator * tIGGI =
                    mSet->get_field_interpolator_manager()->get_IG_geometry_interpolator();
            Geometry_Interpolator * tPreviousIGGI =
                    mSet->get_field_interpolator_manager_previous_time()->get_IG_geometry_interpolator();

            // get physical space and current and previous time coordinates for IG element
            Matrix< DDRMat > tIGPhysSpaceCoords = mMasterCell->get_vertex_coords();
            Matrix< DDRMat > tIGPhysTimeCoords( 1, 1,
                    mCluster->mInterpolationElement->get_time()( 0 ) );
            Matrix< DDRMat > tIGPhysPreviousTimeCoords( 1, 1,
                    mCluster->mInterpolationElement->get_previous_time()( 1 ) );

            // get master parametric space and current and previous time coordinates for IG element
            Matrix< DDRMat > tIGParamSpaceCoords =
                    mCluster->get_primary_cell_local_coords_on_side_wrt_interp_cell( mCellIndexInCluster );
            Matrix< DDRMat > tIGParamTimeCoords( 1, 1, -1.0 );
            Matrix< DDRMat > tIGParamPreviousTimeCoords( 1, 1, 1.0 );

            // set physical space and current time coefficients for IG element GI
            tIGGI->set_space_coeff( tIGPhysSpaceCoords );
            tIGGI->set_time_coeff(  tIGPhysTimeCoords );

            // set physical space and previous time coefficients for IG element GI
            tPreviousIGGI->set_space_coeff( tIGPhysSpaceCoords );
            tPreviousIGGI->set_time_coeff(  tIGPhysPreviousTimeCoords );

            // set parametric space and current time coefficients for IG element GI
            tIGGI->set_space_param_coeff( tIGParamSpaceCoords );
            tIGGI->set_time_param_coeff(  tIGParamTimeCoords );

            // set parametric space and previous time coefficients for IG element GI
            tPreviousIGGI->set_space_param_coeff( tIGParamSpaceCoords );
            tPreviousIGGI->set_time_param_coeff(  tIGParamPreviousTimeCoords );
        }

        //------------------------------------------------------------------------------

        void Element_Time_Sideset::init_ig_geometry_interpolator(
                Matrix< DDSMat > & aGeoLocalAssembly )
        {
            // get geometry interpolator
            Geometry_Interpolator * tIGGI =
                    mSet->get_field_interpolator_manager()->get_IG_geometry_interpolator();
            Geometry_Interpolator * tPreviousIGGI =
                    mSet->get_field_interpolator_manager_previous_time()->get_IG_geometry_interpolator();

            // get physical space and current and previous time coordinates for IG element
            Matrix< DDRMat > tIGPhysSpaceCoords = mMasterCell->get_vertex_coords();
            Matrix< DDRMat > tIGPhysTimeCoords( 1, 1,
                    mCluster->mInterpolationElement->get_time()( 0 ) );
            Matrix< DDRMat > tIGPhysPreviousTimeCoords( 1, 1,
                    mCluster->mInterpolationElement->get_previous_time()( 1 ) );

            // get master parametric space and current and previous time coordinates for IG element
            Matrix< DDRMat > tIGParamSpaceCoords =
                    mCluster->get_primary_cell_local_coords_on_side_wrt_interp_cell( mCellIndexInCluster );
            Matrix< DDRMat > tIGParamTimeCoords( 1, 1, -1.0 );
            Matrix< DDRMat > tIGParamPreviousTimeCoords( 1, 1, 1.0 );

            // get the local cluster assembly indices
            if( mSet->get_geo_pdv_assembly_flag() )
            {
                // get the vertices indices for IG element
                Matrix< IndexMat > tVertexIndices = mMasterCell->get_vertex_inds();

                // get the requested geo pdv types
                moris::Cell < enum PDV_Type > tGeoPdvType;
                mSet->get_ig_unique_dv_types_for_set( tGeoPdvType );

                // get local assembly indices
                mSet->get_equation_model()->get_integration_xyz_pdv_assembly_indices(
                        tVertexIndices,
                        tGeoPdvType,
                        aGeoLocalAssembly );
            }

            // set physical space and current time coefficients for IG element GI
            tIGGI->set_space_coeff( tIGPhysSpaceCoords );
            tIGGI->set_time_coeff(  tIGPhysTimeCoords );

            // set physical space and previous time coefficients for IG element GI
            tPreviousIGGI->set_space_coeff( tIGPhysSpaceCoords );
            tPreviousIGGI->set_time_coeff(  tIGPhysPreviousTimeCoords );

            // set parametric space and current time coefficients for IG element GI
            tIGGI->set_space_param_coeff( tIGParamSpaceCoords );
            tIGGI->set_time_param_coeff(  tIGParamTimeCoords );

            // set parametric space and previous time coefficients for IG element GI
            tPreviousIGGI->set_space_param_coeff( tIGParamSpaceCoords );
            tPreviousIGGI->set_time_param_coeff(  tIGParamPreviousTimeCoords );
        }

        //------------------------------------------------------------------------------

        void Element_Time_Sideset::compute_residual()
        {
            // set physical and parametric space and time coefficients for IG element
            this->init_ig_geometry_interpolator();

            // get number of IWGs
            uint tNumIWGs = mSet->get_number_of_requested_IWGs();

            // loop over integration points
            uint tNumIntegPoints = mSet->get_number_of_integration_points();
            for( uint iGP = 0; iGP < tNumIntegPoints; iGP++ )
            {
                // get integration point location in the reference surface
                const Matrix< DDRMat > & tLocalIntegPoint =
                        mSet->get_integration_points().get_column( iGP );

                // set evaluation point for interpolators (FIs and GIs)
                mSet->get_field_interpolator_manager()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );
                mSet->get_field_interpolator_manager_previous_time()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );

                // compute detJ of integration domain
                real tDetJ = mSet->get_field_interpolator_manager()->get_IG_geometry_interpolator()->det_J();

                // skip if detJ smaller than threshold
                if ( tDetJ < Geometry_Interpolator::sDetJInvJacLowerLimit )
                {
//                    MORIS_LOG_INFO("Element_Time_Sideset::compute_residual: Skip quadrature point evaluation due to small detJ (%e)\n.",tDetJ);
                    continue;
                }

                // compute integration point weight
                real tWStar = mSet->get_integration_weights()( iGP ) * tDetJ;

                // loop over the IWGs
                for( uint iIWG = 0; iIWG < tNumIWGs; iIWG++ )
                {
                    // get requested IWG
                    const std::shared_ptr< IWG > & tReqIWG = mSet->get_requested_IWGs()( iIWG );

                    // reset IWG
                    tReqIWG->reset_eval_flags();

                    // compute Jacobian at evaluation point
                    tReqIWG->compute_residual( tWStar );

                    // compute Jacobian at evaluation point
                    // compute off-diagonal Jacobian for staggered solve
                    tReqIWG->compute_jacobian( tWStar );
                }
            }
        }

        //------------------------------------------------------------------------------

        void Element_Time_Sideset::compute_jacobian()
        {
            // set physical and parametric space and time coefficients for IG element
            this->init_ig_geometry_interpolator();

            // get number of IWGs
            uint tNumIWGs = mSet->get_number_of_requested_IWGs();

            // loop over integration points
            uint tNumIntegPoints = mSet->get_number_of_integration_points();
            for( uint iGP = 0; iGP < tNumIntegPoints; iGP++ )
            {
                // get local integration point location
                const Matrix< DDRMat > & tLocalIntegPoint =
                        mSet->get_integration_points().get_column( iGP );

                // set evaluation point for interpolators (FIs and GIs)
                mSet->get_field_interpolator_manager()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );
                mSet->get_field_interpolator_manager_previous_time()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );

                // compute detJ of integration domain
                real tDetJ = mSet->get_field_interpolator_manager()->get_IG_geometry_interpolator()->det_J();

                // skip if detJ smaller than threshold
                if ( tDetJ < Geometry_Interpolator::sDetJInvJacLowerLimit )
                {
//                    MORIS_LOG_INFO("Element_Time_Sideset::compute_jacobian: Skip quadrature point evaluation due to small detJ (%e)\n.",tDetJ);
                    continue;
                }

                // compute integration point weight
                real tWStar = mSet->get_integration_weights()( iGP ) * tDetJ;

                // loop over the IWGs
                for( uint iIWG = 0; iIWG < tNumIWGs; iIWG++ )
                {
                    // get requested IWG
                    const std::shared_ptr< IWG > & tReqIWG = mSet->get_requested_IWGs()( iIWG );

                    // reset IWG
                    tReqIWG->reset_eval_flags();

                    if( mSet->mEquationModel->get_is_adjoint_off_diagonal_time_contribution() )
                    {
                        tReqIWG->compute_jacobian_previous( tWStar );
                    }
                    else
                    {
                        // compute Jacobian at evaluation point
                        tReqIWG->compute_jacobian( tWStar );
                    }
                }
            }
        }

        //------------------------------------------------------------------------------

        void Element_Time_Sideset::compute_jacobian_and_residual()
        {
            // set physical and parametric space and time coefficients for IG element
            this->init_ig_geometry_interpolator();

            // get number of IWGs
            uint tNumIWGs = mSet->get_number_of_requested_IWGs();

            // loop over integration points
            uint tNumIntegPoints = mSet->get_number_of_integration_points();
            for( uint iGP = 0; iGP < tNumIntegPoints; iGP++ )
            {
                // get local integration point location
                const Matrix< DDRMat > & tLocalIntegPoint =
                        mSet->get_integration_points().get_column( iGP );

                // set evaluation point for interpolators (FIs and GIs)
                mSet->get_field_interpolator_manager()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );
                mSet->get_field_interpolator_manager_previous_time()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );

                // compute integration point weight
                // compute detJ of integration domain
                real tDetJ = mSet->get_field_interpolator_manager()->get_IG_geometry_interpolator()->det_J();

                // skip if detJ smaller than threshold
                if ( tDetJ < Geometry_Interpolator::sDetJInvJacLowerLimit )
                {
//                    MORIS_LOG_INFO("Element_Time_Sideset::compute_jacobian_and_residual: Skip quadrature point evaluation due to small detJ (%e)\n.",tDetJ);
                    continue;
                }

                // compute integration point weight
                real tWStar = mSet->get_integration_weights()( iGP ) * tDetJ;

                // loop over the IWGs
                for( uint iIWG = 0; iIWG < tNumIWGs; iIWG++ )
                {
                    // get requested IWG
                    const std::shared_ptr< IWG > & tReqIWG = mSet->get_requested_IWGs()( iIWG );

                    // reset IWG
                    tReqIWG->reset_eval_flags();

                    if( mSet->mEquationModel->get_is_forward_analysis() )
                    {
                        // compute Jacobian at evaluation point
                        tReqIWG->compute_residual( tWStar );
                    }

                    // compute Jacobian at evaluation point
                    tReqIWG->compute_jacobian( tWStar );
                }
            }
        }

        //------------------------------------------------------------------------------

        void Element_Time_Sideset::compute_dRdp()
        {
            // set physical and parametric space and time coefficients for IG element
            Matrix< DDSMat > tGeoLocalAssembly;
            this->init_ig_geometry_interpolator( tGeoLocalAssembly );

            // get number of IWGs
            uint tNumIWGs = mSet->get_number_of_requested_IWGs();

            // loop over integration points
            uint tNumIntegPoints = mSet->get_number_of_integration_points();
            for( uint iGP = 0; iGP < tNumIntegPoints; iGP++ )
            {
                // get integration point location in the reference surface
                const Matrix< DDRMat > & tLocalIntegPoint =
                        mSet->get_integration_points().get_column( iGP );

                // set evaluation point for interpolators (FIs and GIs)
                mSet->get_field_interpolator_manager()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );
                mSet->get_field_interpolator_manager_previous_time()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );

                // compute detJ of integration domain
                real tDetJ = mSet->get_field_interpolator_manager()->get_IG_geometry_interpolator()->det_J();

                // skip if detJ smaller than threshold
                if ( tDetJ < Geometry_Interpolator::sDetJInvJacLowerLimit )
                {
//                    MORIS_LOG_INFO("Element_Time_Sideset::compute_dRdp: Skip quadrature point evaluation due to small detJ (%e)\n.",tDetJ);
                    continue;
                }

                // compute integration point weight
                real tWStar = mSet->get_integration_weights()( iGP ) * tDetJ;

                // loop over the IWGs
                for( uint iIWG = 0; iIWG < tNumIWGs; iIWG++ )
                {
                    // get requested IWG
                    const std::shared_ptr< IWG > & tReqIWG = mSet->get_requested_IWGs()( iIWG );

                    // reset IWG
                    tReqIWG->reset_eval_flags();

                    // compute dRdpMat at evaluation point
                    tReqIWG->compute_dRdp( tWStar );
                }
            }
        }

        //------------------------------------------------------------------------------

        void Element_Time_Sideset::compute_dRdp_FD()
        {
            // get finite difference scheme type
            fem::FDScheme_Type tFDScheme =
                    mSet->get_finite_difference_scheme_for_sensitivity_analysis();

            // get the finite difference perturbation size
            real tFDPerturbation = mSet->get_finite_difference_perturbation_size();

            // set physical and parametric space and time coefficients for IG element
            Matrix< DDSMat > tGeoLocalAssembly;
            this->init_ig_geometry_interpolator( tGeoLocalAssembly );

            // get number of IWGs
            uint tNumIWGs = mSet->get_number_of_requested_IWGs();

            // loop over integration points
            uint tNumIntegPoints = mSet->get_number_of_integration_points();
            for( uint iGP = 0; iGP < tNumIntegPoints; iGP++ )
            {
                // get integration point location in the reference surface
                const Matrix< DDRMat > & tLocalIntegPoint =
                        mSet->get_integration_points().get_column( iGP );

                // set evaluation point for interpolators (FIs and GIs)
                mSet->get_field_interpolator_manager()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );
                mSet->get_field_interpolator_manager_previous_time()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );

                // compute detJ of integration domain
                real tDetJ = mSet->get_field_interpolator_manager()->get_IG_geometry_interpolator()->det_J();

                // skip if detJ smaller than threshold
                if ( tDetJ < Geometry_Interpolator::sDetJInvJacLowerLimit )
                {
//                    MORIS_LOG_INFO("Element_Time_Sideset::compute_dRdp_FD: Skip quadrature point evaluation due to small detJ (%e)\n.",tDetJ);
                    continue;
                }

                // compute integration point weight
                real tWStar = mSet->get_integration_weights()( iGP ) * tDetJ;

                // loop over the IWGs
                for( uint iIWG = 0; iIWG < tNumIWGs; iIWG++ )
                {
                    // get requested IWG
                    const std::shared_ptr< IWG > & tReqIWG = mSet->get_requested_IWGs()( iIWG );

                    // reset IWG
                    tReqIWG->reset_eval_flags();

                    // compute dRdpMat at evaluation point
                    tReqIWG->compute_dRdp_FD_material(
                            tWStar,
                            tFDPerturbation,
                            tFDScheme );

                    // compute dRdpGeo at evaluation point
                    if( mSet->get_geo_pdv_assembly_flag() )
                    {
                        tReqIWG->compute_dRdp_FD_geometry(
                                tWStar,
                                tFDPerturbation,
                                tGeoLocalAssembly,
                                tFDScheme );
                    }
                }
            }
        }

        //------------------------------------------------------------------------------

        void Element_Time_Sideset::compute_QI()
        {
            // set physical and parametric space and time coefficients for IG element
            this->init_ig_geometry_interpolator();

            // get number of IQIs
            uint tNumIQIs = mSet->get_number_of_requested_IQIs();

            // FIXME create a cell of IQI values
            moris::Cell< Matrix< DDRMat > > tQIValues( tNumIQIs );

            // loop over integration points
            uint tNumIntegPoints = mSet->get_number_of_integration_points();
            for( uint iGP = 0; iGP < tNumIntegPoints; iGP++ )
            {
                // get the ith integration point in the IG param space
                const Matrix< DDRMat > & tLocalIntegPoint =
                        mSet->get_integration_points().get_column( iGP );

                // set evaluation point for interpolators (FIs and GIs)
                mSet->get_field_interpolator_manager()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );
                mSet->get_field_interpolator_manager_previous_time()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );

                // compute detJ of integration domain
                real tDetJ = mSet->get_field_interpolator_manager()->get_IG_geometry_interpolator()->det_J();

                // skip if detJ smaller than threshold
                if ( tDetJ < Geometry_Interpolator::sDetJInvJacLowerLimit )
                {
//                    MORIS_LOG_INFO("Element_Time_Sideset::compute_QI: Skip quadrature point evaluation due to small detJ (%e)\n.",tDetJ);
                    continue;
                }

                // compute integration point weight
                real tWStar = mSet->get_integration_weights()( iGP ) * tDetJ;

                // loop over the IQIs
                for( uint iIQI = 0; iIQI < tNumIQIs; iIQI++ )
                {
                    // reset IQI
                    mSet->get_requested_IQIs()( iIQI )->reset_eval_flags();

                    // compute QI at evaluation point
                    mSet->get_requested_IQIs()( iIQI )->add_QI_on_set( tWStar );
                }
            }
        }

        //------------------------------------------------------------------------------

        void Element_Time_Sideset::compute_dQIdu()
        {
            // set physical and parametric space and time coefficients for IG element
            this->init_ig_geometry_interpolator();

            // get number of IQIs
            uint tNumIQIs = mSet->get_number_of_requested_IQIs();

            // loop over integration points
            uint tNumIntegPoints = mSet->get_number_of_integration_points();
            for( uint iGP = 0; iGP < tNumIntegPoints; iGP++ )
            {
                // get the ith integration point in the IG param space
                const Matrix< DDRMat > & tLocalIntegPoint =
                        mSet->get_integration_points().get_column( iGP );

                // set evaluation point for interpolators (FIs and GIs)
                mSet->get_field_interpolator_manager()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );
                mSet->get_field_interpolator_manager_previous_time()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );

                // compute detJ of integration domain
                real tDetJ = mSet->get_field_interpolator_manager()->get_IG_geometry_interpolator()->det_J();

                // skip if detJ smaller than threshold
                if ( tDetJ < Geometry_Interpolator::sDetJInvJacLowerLimit )
                {
//                    MORIS_LOG_INFO("Element_Time_Sideset::compute_dQIdu: Skip quadrature point evaluation due to small detJ (%e)\n.",tDetJ);
                    continue;
                }

                // compute integration point weight
                real tWStar = mSet->get_integration_weights()( iGP ) * tDetJ;

                // loop over the IQIs
                for( uint iIQI = 0; iIQI < tNumIQIs; iIQI++ )
                {
                    // reset IWG
                    mSet->get_requested_IQIs()( iIQI )->reset_eval_flags();

                    // compute dQIdu at evaluation point
                    mSet->get_requested_IQIs()( iIQI )->add_dQIdu_on_set( tWStar );
                }
            }
        }

        //------------------------------------------------------------------------------

        void Element_Time_Sideset::compute_dQIdp_explicit()
        {
            // set physical and parametric space and time coefficients for IG element
            Matrix< DDSMat > tGeoLocalAssembly;
            this->init_ig_geometry_interpolator( tGeoLocalAssembly );

            // get number of IWGs
            uint tNumIQIs = mSet->get_number_of_requested_IQIs();

            // loop over integration points
            uint tNumIntegPoints = mSet->get_number_of_integration_points();
            for( uint iGP = 0; iGP < tNumIntegPoints; iGP++ )
            {
                // get the ith integration point in the IG param space
                const Matrix< DDRMat > & tLocalIntegPoint =
                        mSet->get_integration_points().get_column( iGP );

                // set evaluation point for interpolators (FIs and GIs)
                mSet->get_field_interpolator_manager()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );
                mSet->get_field_interpolator_manager_previous_time()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );

                // compute detJ of integration domain
                real tDetJ = mSet->get_field_interpolator_manager()->get_IG_geometry_interpolator()->det_J();

                // skip if detJ smaller than threshold
                if ( tDetJ < Geometry_Interpolator::sDetJInvJacLowerLimit )
                {
//                    MORIS_LOG_INFO("Element_Time_Sideset::compute_dQIdp_explicit: Skip quadrature point evaluation due to small detJ (%e)\n.",tDetJ);
                    continue;
                }

                // compute integration point weight
                real tWStar = mSet->get_integration_weights()( iGP ) * tDetJ;

                // loop over the IQIs
                for( uint iIQI = 0; iIQI < tNumIQIs; iIQI++ )
                {
                    // reset IWG
                    mSet->get_requested_IQIs()( iIQI )->reset_eval_flags();

                    // compute dQIdpMat at evaluation point
                    mSet->get_requested_IQIs()( iIQI )->compute_dQIdp( tWStar );
                }
            }
        }

        //------------------------------------------------------------------------------

        void Element_Time_Sideset::compute_dQIdp_explicit_FD()
        {
            // get finite difference scheme type
            fem::FDScheme_Type tFDScheme =
                    mSet->get_finite_difference_scheme_for_sensitivity_analysis();

            // get the finite difference perturbation size
            real tFDPerturbation = mSet->get_finite_difference_perturbation_size();

            // set physical and parametric space and time coefficients for IG element
            Matrix< DDSMat > tGeoLocalAssembly;
            this->init_ig_geometry_interpolator( tGeoLocalAssembly );

            // get number of IWGs
            uint tNumIQIs = mSet->get_number_of_requested_IQIs();

            // loop over integration points
            uint tNumIntegPoints = mSet->get_number_of_integration_points();
            for( uint iGP = 0; iGP < tNumIntegPoints; iGP++ )
            {
                // get the ith integration point in the IG param space
                const Matrix< DDRMat > & tLocalIntegPoint =
                        mSet->get_integration_points().get_column( iGP );

                // set evaluation point for interpolators (FIs and GIs)
                mSet->get_field_interpolator_manager()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );
                mSet->get_field_interpolator_manager_previous_time()->
                        set_space_time_from_local_IG_point( tLocalIntegPoint );

                // compute detJ of integration domain
                real tDetJ = mSet->get_field_interpolator_manager()->get_IG_geometry_interpolator()->det_J();

                // skip if detJ smaller than threshold
                if ( tDetJ < Geometry_Interpolator::sDetJInvJacLowerLimit )
                {
//                    MORIS_LOG_INFO("Element_Time_Sideset::compute_dQIdp_explicit_FD: Skip quadrature point evaluation due to small detJ (%e)\n.",tDetJ);
                    continue;
                }

                // compute integration point weight
                real tWStar = mSet->get_integration_weights()( iGP ) * tDetJ;

                // loop over the IQIs
                for( uint iIQI = 0; iIQI < tNumIQIs; iIQI++ )
                {
                    // reset IWG
                    mSet->get_requested_IQIs()( iIQI )->reset_eval_flags();

                    // compute dQIdpMat at evaluation point
                    mSet->get_requested_IQIs()( iIQI )->compute_dQIdp_FD_material(
                            tWStar,
                            tFDPerturbation,
                            tFDScheme );

                    // compute dQIdpGeo at evaluation point
                    if( mSet->get_geo_pdv_assembly_flag() )
                    {
                        mSet->get_requested_IQIs()( iIQI )->compute_dQIdp_FD_geometry(
                                tWStar,
                                tFDPerturbation,
                                tGeoLocalAssembly,
                                tFDScheme );
                    }
                }
            }
        }

        //------------------------------------------------------------------------------

    } /* namespace fem */
} /* namespace moris */
