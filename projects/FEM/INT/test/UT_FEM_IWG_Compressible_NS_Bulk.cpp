#include <string>
#include <catch.hpp>
#include <memory>
#include "assert.hpp"

#define protected public
#define private   public
//FEM//INT//src
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_IWG.hpp"
#include "cl_FEM_Set.hpp"
#undef protected
#undef private
//LINALG/src
#include "op_equal_equal.hpp"
//MTK/src
#include "cl_MTK_Enums.hpp"
//FEM//INT//src
#include "cl_FEM_Enums.hpp"
#include "cl_FEM_Field_Interpolator.hpp"
#include "cl_FEM_Property.hpp"
#include "cl_FEM_MM_Factory.hpp"
#include "cl_FEM_CM_Factory.hpp"
#include "cl_FEM_SP_Factory.hpp"
#include "cl_FEM_IWG_Factory.hpp"
#include "FEM_Test_Proxy/cl_FEM_Inputs_for_NS_Compressible_UT.cpp"

#include "fn_trans.hpp"
#include "fn_FEM_Check.hpp"

using namespace moris;
using namespace fem;

TEST_CASE( "IWG_Compressible_NS_Bulk_Perfect_Gas_Pressure_Primitive",
        "[IWG_Compressible_NS_Bulk_Perfect_Gas_Pressure_Primitive]" )
{
    // define an epsilon environment
    real tEpsilon = 1.0E-6;
    real tEpsilonCubic = 5.0E-6;

    // define a perturbation relative size
    real tPerturbation = 2.0E-4;
    real tPerturbationCubic = 5.0E-4;

    // init geometry inputs
    //------------------------------------------------------------------------------
    // create geometry type
    mtk::Geometry_Type tGeometryType = mtk::Geometry_Type::UNDEFINED;

    // create list of interpolation orders
    moris::Cell< mtk::Interpolation_Order > tInterpolationOrders = {
            mtk::Interpolation_Order::LINEAR,
            mtk::Interpolation_Order::QUADRATIC,
            mtk::Interpolation_Order::CUBIC };

    // create list of integration orders
    moris::Cell< mtk::Integration_Order > tIntegrationOrders = {
            mtk::Integration_Order::QUAD_2x2,
            mtk::Integration_Order::HEX_2x2x2 };

    // create list with number of coeffs
    Matrix< DDRMat > tNumCoeffs = {{ 8, 18, 32 },{ 16, 54, 128 }};

    // dof type list
    moris::Cell< MSI::Dof_Type > tPressureDof = { MSI::Dof_Type::P };
    moris::Cell< MSI::Dof_Type > tVelocityDof = { MSI::Dof_Type::VX };
    moris::Cell< MSI::Dof_Type > tTempDof     = { MSI::Dof_Type::TEMP };
    moris::Cell< moris::Cell< MSI::Dof_Type > > tDofTypes = { tPressureDof, tVelocityDof, tTempDof };
    moris::Cell< MSI::Dof_Type > tResidualDofTypes = { MSI::Dof_Type::P, MSI::Dof_Type::VX, MSI::Dof_Type::TEMP };

    // init IWG
    //------------------------------------------------------------------------------
    // create the properties

    // dynamic viscosity
    std::shared_ptr< fem::Property > tPropViscosity = std::make_shared< fem::Property >();
    tPropViscosity->set_parameters( { {{ 11.9 }} } );
    tPropViscosity->set_val_function( tConstValFunc );

    // isochoric heat capacity
    std::shared_ptr< fem::Property > tPropHeatCapacity = std::make_shared< fem::Property >();
    tPropHeatCapacity->set_parameters( { {{ 5.7 }} } );
    tPropHeatCapacity->set_val_function( tConstValFunc );

    // specific gas constant
    std::shared_ptr< fem::Property > tPropGasConstant = std::make_shared< fem::Property >();
    tPropGasConstant->set_parameters( { {{ 2.8 }} } );
    tPropGasConstant->set_val_function( tConstValFunc );

    // thermal conductivity
    std::shared_ptr< fem::Property > tPropConductivity = std::make_shared< fem::Property >();
    tPropConductivity->set_parameters( { {{ 3.7 }} } );
    tPropConductivity->set_val_function( tConstValFunc );

    // body force
    std::shared_ptr< fem::Property > tPropBodyForce3D = std::make_shared< fem::Property >();
    tPropBodyForce3D->set_val_function( tValFunc_BodyForce_3D );
    std::shared_ptr< fem::Property > tPropBodyForce2D = std::make_shared< fem::Property >();
    tPropBodyForce2D->set_val_function( tValFunc_BodyForce_2D );

    // define material model and assign properties
    fem::MM_Factory tMMFactory;

    std::shared_ptr< fem::Material_Model > tMMFluid =
            tMMFactory.create_CM( fem::Material_Type::PERFECT_GAS );
    tMMFluid->set_dof_type_list( {tPressureDof, tTempDof } );
    tMMFluid->set_property( tPropHeatCapacity, "IsochoricHeatCapacity" );
    tMMFluid->set_property( tPropGasConstant,  "SpecificGasConstant" );    

    // define constitutive model and assign properties
    fem::CM_Factory tCMFactory;

    std::shared_ptr< fem::Constitutive_Model > tCMMasterFluid =
            tCMFactory.create_CM( fem::Constitutive_Type::FLUID_COMPRESSIBLE_NEWTONIAN );
    tCMMasterFluid->set_dof_type_list( {tPressureDof, tVelocityDof, tTempDof } );
    tCMMasterFluid->set_property( tPropViscosity,    "DynamicViscosity" );
    tCMMasterFluid->set_property( tPropConductivity, "ThermalConductivity" );
    tCMMasterFluid->set_material_model( tMMFluid, "ThermodynamicMaterialModel" );

    // define the IWGs
    fem::IWG_Factory tIWGFactory;

    std::shared_ptr< fem::IWG > tIWG =
            tIWGFactory.create_IWG( fem::IWG_Type::COMPRESSIBLE_NS_BULK );

    tIWG->set_residual_dof_type( tResidualDofTypes );
    tIWG->set_dof_type_list( tDofTypes, mtk::Master_Slave::MASTER );
    tIWG->set_property( tPropViscosity,    "DynamicViscosity" );
    tIWG->set_property( tPropConductivity, "ThermalConductivity" );
    tIWG->set_material_model( tMMFluid, "FluidMM" );
    tIWG->set_constitutive_model( tCMMasterFluid, "FluidCM" );

    //------------------------------------------------------------------------------
    // set a fem set pointer

    MSI::Equation_Set * tSet = new fem::Set();
    static_cast<fem::Set*>(tSet)->set_set_type( fem::Element_Type::BULK );
    tMMFluid->set_set_pointer( static_cast< fem::Set* >( tSet ) );
    tCMMasterFluid->set_set_pointer( static_cast< fem::Set* >( tSet ) );
    tIWG->set_set_pointer( static_cast< fem::Set* >( tSet ) );

    // set size for the set EqnObjDofTypeList
    tIWG->mSet->mUniqueDofTypeList.resize( 100, MSI::Dof_Type::END_ENUM );

    // set size and populate the set dof type map
    tMMFluid->mSet->mUniqueDofTypeMap.set_size( static_cast< int >( MSI::Dof_Type::END_ENUM ) + 1, 1, -1 );
    tMMFluid->mSet->mUniqueDofTypeMap( static_cast< int >( MSI::Dof_Type::P ) )   = 0;
    tMMFluid->mSet->mUniqueDofTypeMap( static_cast< int >( MSI::Dof_Type::TEMP ) )  = 1;

    // set size and populate the set dof type map
    tIWG->mSet->mUniqueDofTypeMap.set_size( static_cast< int >( MSI::Dof_Type::END_ENUM ) + 1, 1, -1 );
    tIWG->mSet->mUniqueDofTypeMap( static_cast< int >( MSI::Dof_Type::P ) )     = 0;
    tIWG->mSet->mUniqueDofTypeMap( static_cast< int >( MSI::Dof_Type::VX ) )    = 1;
    tIWG->mSet->mUniqueDofTypeMap( static_cast< int >( MSI::Dof_Type::TEMP ) )  = 2;

    // set size and populate the set master dof type map
    tIWG->mSet->mMasterDofTypeMap.set_size( static_cast< int >( MSI::Dof_Type::END_ENUM ) + 1, 1, -1 );
    tIWG->mSet->mMasterDofTypeMap( static_cast< int >( MSI::Dof_Type::P ) )     = 0;
    tIWG->mSet->mMasterDofTypeMap( static_cast< int >( MSI::Dof_Type::VX ) )    = 1;
    tIWG->mSet->mMasterDofTypeMap( static_cast< int >( MSI::Dof_Type::TEMP ) )  = 2;

    // loop on the space dimension  
    for( uint iSpaceDim = 2; iSpaceDim < 4; iSpaceDim++ )
    {
        // output for debugging
        std::cout << "-------------------------------------------------------------------\n" << std::flush;
        std::cout << "Performing Tests For Number of Spatial dimensions: " << iSpaceDim << "\n" << std::flush;
        std::cout << "-------------------------------------------------------------------\n\n" << std::flush;

        // use correct body force for number of spatial dimensions
        if ( iSpaceDim == 2 )
            tIWG->set_property( tPropBodyForce2D, "BodyForce" );
        else if ( iSpaceDim == 3 )
            tIWG->set_property( tPropBodyForce3D, "BodyForce" );

        // switch on space dimension
        switch( iSpaceDim )
        {
            case 2 :
            {
                // set geometry type
                tGeometryType = mtk::Geometry_Type::QUAD;

                // set velocity dof types
                tVelocityDof = { MSI::Dof_Type::VX, MSI::Dof_Type::VY };
                break;
            }
            case 3 :
            {
                // set geometry type
                tGeometryType = mtk::Geometry_Type::HEX;

                // set velocity dof types
                tVelocityDof = { MSI::Dof_Type::VX, MSI::Dof_Type::VY, MSI::Dof_Type::VZ };
                break;
            }
            default:
            {
                MORIS_ERROR( false, "Unit Test Error: QUAD or HEX only." );
                break;
            }
        }

        // set space dimension to CM
        tMMFluid->set_space_dim( iSpaceDim );
        tCMMasterFluid->set_space_dim( iSpaceDim );

        // loop on the interpolation order      
        for( uint iInterpOrder = 1; iInterpOrder < 4; iInterpOrder++ )
        {
            // tune finite differencing for cubic shape functions
            if ( iInterpOrder == 3 )
            {
                tEpsilon = tEpsilonCubic;
                tPerturbation = tPerturbationCubic;
            }

            // output for debugging
            std::cout << "-------------------------------------------------------------------\n" << std::flush;
            std::cout << "-------------------------------------------------------------------\n" << std::flush;
            std::cout << "Performing Tests For Interpolation Order:" << iInterpOrder << "\n\n" << std::flush;

            // create an interpolation order
            mtk::Interpolation_Order tGIInterpolationOrder = tInterpolationOrders( iInterpOrder - 1 );

            //------------------------------------------------------------------------------
            // space and time geometry interpolators
            // create a space geometry interpolation rule
            mtk::Interpolation_Rule tGIRule( tGeometryType,
                    mtk::Interpolation_Type::LAGRANGE,
                    tGIInterpolationOrder,
                    mtk::Interpolation_Type::LAGRANGE,
                    mtk::Interpolation_Order::LINEAR );

            // create a space time geometry interpolator
            Geometry_Interpolator tGI = Geometry_Interpolator( tGIRule );

            // create time coeff tHat
            Matrix< DDRMat > tTHat = {{ 0.26 }, { 0.87 }};

            Matrix< DDRMat > tXHat;
            fill_xhat( tXHat, iSpaceDim, iInterpOrder );

            // set the coefficients xHat, tHat
            tGI.set_coeff( tXHat, tTHat );

            //------------------------------------------------------------------------------
            // integration points
            // get an integration order
            mtk::Integration_Order tIntegrationOrder = tIntegrationOrders( iSpaceDim - 2 );

            // create an integration rule
            mtk::Integration_Rule tIntegrationRule(
                    tGeometryType,
                    mtk::Integration_Type::GAUSS,
                    tIntegrationOrder,
                    mtk::Geometry_Type::LINE,
                    mtk::Integration_Type::GAUSS,
                    mtk::Integration_Order::BAR_1 );

            // create an integrator
            mtk::Integrator tIntegrator( tIntegrationRule );

            // get integration points
            Matrix< DDRMat > tIntegPoints;
            tIntegrator.get_points( tIntegPoints );

            //------------------------------------------------------------------------------
            // field interpolators
            // create an interpolation order
            mtk::Interpolation_Order tInterpolationOrder = tInterpolationOrders( iInterpOrder - 1 );

            // number of dof for interpolation order
            uint tNumCoeff = tNumCoeffs( iSpaceDim - 2, iInterpOrder - 1 );

            // get number of dof per type
            int tNumDofRho  = tNumCoeff;
            int tNumDofVel  = tNumCoeff * iSpaceDim;
            int tNumDofTemp = tNumCoeff;
            int tTotalNumDof = tNumDofRho + tNumDofVel + tNumDofTemp;

            //create a space time interpolation rule
            mtk::Interpolation_Rule tFIRule (
                    tGeometryType,
                    mtk::Interpolation_Type::LAGRANGE,
                    tInterpolationOrder,
                    mtk::Interpolation_Type::LAGRANGE,
                    mtk::Interpolation_Order::LINEAR );

            // fill coefficients for master FI
            Matrix< DDRMat > tMasterDOFHatRho;
            fill_RhoHat( tMasterDOFHatRho, iSpaceDim, iInterpOrder );
            Matrix< DDRMat > tMasterDOFHatVel;
            fill_UHat( tMasterDOFHatVel, iSpaceDim, iInterpOrder );
            Matrix< DDRMat > tMasterDOFHatTemp;
            fill_TempHat( tMasterDOFHatTemp, iSpaceDim, iInterpOrder );                 

            // create a cell of field interpolators for IWG
            Cell< Field_Interpolator* > tMasterFIs( tDofTypes.size() );

            // create the field interpolator density
            tMasterFIs( 0 ) = new Field_Interpolator( 1, tFIRule, &tGI, tPressureDof );
            tMasterFIs( 0 )->set_coeff( tMasterDOFHatRho );

            // create the field interpolator velocity
            tMasterFIs( 1 ) = new Field_Interpolator( iSpaceDim, tFIRule, &tGI, tVelocityDof );
            tMasterFIs( 1 )->set_coeff( tMasterDOFHatVel );

            // create the field interpolator pressure
            tMasterFIs( 2 ) = new Field_Interpolator( 1, tFIRule, &tGI, tTempDof );
            tMasterFIs( 2 )->set_coeff( tMasterDOFHatTemp );

            // set size and fill the set residual assembly map
            tIWG->mSet->mResDofAssemblyMap.resize( tDofTypes.size() );
            tIWG->mSet->mResDofAssemblyMap( 0 ) = { { 0, tNumDofRho - 1 } };
            tIWG->mSet->mResDofAssemblyMap( 1 ) = { { tNumDofRho, tNumDofRho + tNumDofVel - 1 } };
            tIWG->mSet->mResDofAssemblyMap( 2 ) = { { tNumDofRho + tNumDofVel, tTotalNumDof - 1 } };

            // set size and fill the set jacobian assembly map
            Matrix< DDSMat > tJacAssembly = {
                    { 0, tNumDofRho - 1 },
                    { tNumDofRho, tNumDofRho + tNumDofVel - 1 },
                    { tNumDofRho + tNumDofVel, tTotalNumDof - 1 } };
            tIWG->mSet->mJacDofAssemblyMap.resize( tDofTypes.size() );
            tIWG->mSet->mJacDofAssemblyMap( 0 ) = tJacAssembly;
            tIWG->mSet->mJacDofAssemblyMap( 1 ) = tJacAssembly;
            tIWG->mSet->mJacDofAssemblyMap( 2 ) = tJacAssembly;

            // set size and init the set residual and jacobian
            tIWG->mSet->mResidual.resize( 1 );
            tIWG->mSet->mResidual( 0 ).set_size(
                    tTotalNumDof,
                    1,
                    0.0 );
            tIWG->mSet->mJacobian.set_size(
                    tTotalNumDof,
                    tTotalNumDof,
                    0.0 );

            // build global dof type list
            tIWG->get_global_dof_type_list();

            // populate the requested master dof type
            tIWG->mRequestedMasterGlobalDofTypes = tDofTypes;

            // create a field interpolator manager
            moris::Cell< moris::Cell< enum PDV_Type > > tDummyDv;
            moris::Cell< moris::Cell< enum mtk::Field_Type > > tDummyField;
            Field_Interpolator_Manager tFIManager( tDofTypes, tDummyDv, tDummyField, tSet );

            // populate the field interpolator manager
            tFIManager.mFI = tMasterFIs;
            tFIManager.mIPGeometryInterpolator = &tGI;
            tFIManager.mIGGeometryInterpolator = &tGI;

            // set the interpolator manager to the set
            tIWG->mSet->mMasterFIManager = &tFIManager;

            // set IWG field interpolator manager
            tIWG->set_field_interpolator_manager( &tFIManager );

            // set the interpolator manager to the set
            tCMMasterFluid->mSet->mMasterFIManager = &tFIManager;

            // set IWG field interpolator manager
            tCMMasterFluid->set_field_interpolator_manager( &tFIManager );

            // loop over integration points
            uint tNumGPs = tIntegPoints.n_cols();
            for( uint iGP = 0; iGP < tNumGPs; iGP ++ )
            {
                // output for debugging
                std::cout << "-------------------------------------------------------------------\n" << std::flush;
                std::cout << "Looping over Gauss points. Current GP-#: " << iGP << "\n\n" << std::flush;

                // reset CM evaluation flags
                tCMMasterFluid->reset_eval_flags();

                // reset IWG evaluation flags
                tIWG->reset_eval_flags();

                // create evaluation point xi, tau
                Matrix< DDRMat > tParamPoint = tIntegPoints.get_column( iGP );

                // set integration point
                tCMMasterFluid->mSet->mMasterFIManager->set_space_time( tParamPoint );
                tIWG->mSet->mMasterFIManager->set_space_time( tParamPoint );

                // check evaluation of the residual for IWG
                //------------------------------------------------------------------------------
                // reset residual & jacobian
                tIWG->mSet->mResidual( 0 ).fill( 0.0 );      
                tIWG->mSet->mJacobian.fill( 0.0 );                  

                // check evaluation of the jacobian by FD
                //------------------------------------------------------------------------------

                // init the jacobian for IWG and FD evaluation
                Matrix< DDRMat > tJacobian = tIWG->mSet->get_jacobian();
                Matrix< DDRMat > tJacobianTest;
                Matrix< DDRMat > tJacobianFD;

                // check jacobian by FD
                bool tCheckJacobian = tIWG->check_jacobian_multi_residual(
                        tPerturbation,
                        tEpsilon,
                        1.0,
                        tJacobianTest,
                        tJacobianFD,
                        //true );
                        false );

                // print for debug
                if( !tCheckJacobian )
                {
                    std::cout << "Case: Spatial Dims: " << iSpaceDim << ",  Order: " << iInterpOrder << ",  iGP: " << iGP<<std::endl;
                }

                // require check is true
                REQUIRE( tCheckJacobian );
            }

            // clean up
            tMasterFIs.clear();
        }
    }
}/*END_TEST_CASE*/