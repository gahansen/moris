
#include "catch.hpp"

#define protected public
#define private   public
//FEM/INT/src
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_Constitutive_Model.hpp"
#include "cl_FEM_Stabilization_Parameter.hpp"
#include "cl_FEM_Set.hpp"
#undef protected
#undef private

//LINALG/src
#include "fn_equal_to.hpp"
//FEM/INT/src
#include "cl_FEM_Field_Interpolator.hpp"
#include "cl_FEM_Property.hpp"
#include "cl_FEM_CM_Factory.hpp"
#include "cl_FEM_SP_Factory.hpp"
#include "fn_FEM_Check.hpp"

void tValFunc_SPFluid(
        moris::Matrix< moris::DDRMat >                 & aPropMatrix,
        moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
        moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix =
            aParameters( 0 )
            + aParameters( 0 ) * aFIManager->get_field_interpolators_for_type( moris::MSI::Dof_Type::TEMP )->val();
}

void tConstValFunc_SPFluid(
        moris::Matrix< moris::DDRMat >                 & aPropMatrix,
        moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
        moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 );
}

void tDerFunc_SPFluid(
        moris::Matrix< moris::DDRMat >                 & aPropMatrix,
        moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
        moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix =
            aParameters( 0 ) *
            aFIManager->get_field_interpolators_for_type( moris::MSI::Dof_Type::TEMP )->N();
}

using namespace moris;
using namespace fem;

TEST_CASE( "SP_Fluid", "[SP_Fluid]" )
{
    // define an epsilon environment
    real tEpsilon = 1E-6;

    // define a perturbation relative size
    real tPerturbation = 1E-6;

    // material parameter
    real tFluidDensity   = 1.0;
    real tFluidViscosity = 1.0;
    real tGammaNitsche   = 1.0;
    real tGammaGPmu      = 1.0;
    real tGammaGPu       = 1.0;
    real tGammaGPp       = 1.0;

    // loop on the space dimension
    for( uint iSpaceDim = 2; iSpaceDim < 4; iSpaceDim++ )
    {
        // set geometry inputs
        //------------------------------------------------------------------------------
        // create geometry type
        mtk::Geometry_Type tGeometryType = mtk::Geometry_Type::UNDEFINED;

        // create space coeff xHat
        Matrix< DDRMat > tXHat;

        // create evaluation point xi, tau
        Matrix< DDRMat > tParamPoint;

        // create list with number of coeffs
        Matrix< DDRMat > tNumCoeffs;

        // dof type list
        moris::Cell< MSI::Dof_Type > tVelDofTypes;
        moris::Cell< MSI::Dof_Type > tPDofTypes    = { MSI::Dof_Type::P };
        moris::Cell< MSI::Dof_Type > tTEMPDofTypes = { MSI::Dof_Type::TEMP };
        moris::Cell< MSI::Dof_Type > tVisDofTypes  = { MSI::Dof_Type::VISCOSITY };

        // gravity
        Matrix< DDRMat > tNormal;

        // switch on space dimension
        switch( iSpaceDim )
        {
            case 2 :
            {
                // set geometry type
                tGeometryType = mtk::Geometry_Type::QUAD;

                // fill space coeff xHat
                tXHat = {{ 0.0, 0.0 },
                        { 1.0, 0.0 },
                        { 1.0, 1.0 },
                        { 0.0, 1.0 }};

                // fill evaluation point xi, tau
                tParamPoint = {{ 0.35}, {-0.25}, { 0.0 }};

                // number of coefficients
                tNumCoeffs = {{ 8 },{ 18 },{ 32 }};

                // set velocity dof types
                tVelDofTypes = { MSI::Dof_Type::VX, MSI::Dof_Type::VY };

                // fill normal
                tNormal = {{0.87},{-0.23}};

                break;
            }
            case 3 :
            {
                // set geometry type
                tGeometryType = mtk::Geometry_Type::HEX;

                // fill space coeff xHat
                tXHat = {{ 0.0, 0.0, 0.0 },
                        { 1.0, 0.0, 0.0 },
                        { 1.0, 1.0, 0.0 },
                        { 0.0, 1.0, 0.0 },
                        { 0.0, 0.0, 1.0 },
                        { 1.0, 0.0, 1.0 },
                        { 1.0, 1.0, 1.0 },
                        { 0.0, 1.0, 1.0 }};

                // fill evaluation point xi, tau
                tParamPoint = {{ 0.35 }, {-0.25}, { 0.75}, { 0.0 }};

                // number of coefficients
                tNumCoeffs = {{ 16 },{ 54 },{ 128 }};

                // set velocity dof types
                tVelDofTypes = { MSI::Dof_Type::VX, MSI::Dof_Type::VY, MSI::Dof_Type::VZ };

                // fill normal
                tNormal = {{0.87},{-0.23},{0.12}};

                break;
            }
            default:
            {
                MORIS_ERROR( false, " QUAD or HEX only." );
                break;
            }
        }

        // space and time geometry interpolators
        //------------------------------------------------------------------------------
        // create a space geometry interpolation rule
        Interpolation_Rule tGIRule( tGeometryType,
                Interpolation_Type::LAGRANGE,
                mtk::Interpolation_Order::LINEAR,
                Interpolation_Type::LAGRANGE,
                mtk::Interpolation_Order::LINEAR );

        // create a space time geometry interpolator
        Geometry_Interpolator tGI = Geometry_Interpolator( tGIRule );

        // create time coeff tHat
        Matrix< DDRMat > tTHat = {{ 0.0 }, { 1.0 }};

        // set the coefficients xHat, tHat
        tGI.set_coeff( tXHat, tTHat );
        tGI.set_space_time( tParamPoint );

        // loop on the interpolation order
        for( uint iInterpOrder = 1; iInterpOrder < 4; iInterpOrder++ )
        {
            // field interpolators
            //------------------------------------------------------------------------------
            // create an interpolation order
            mtk::Interpolation_Order tInterpolationOrder;

            uint tNumCoeff;

            // switch on interpolation order
            switch( iInterpOrder )
            {
                case 1 :
                {
                    // set interpolation type
                    tInterpolationOrder = mtk::Interpolation_Order::LINEAR;

                    // get num of coefficients
                    tNumCoeff = tNumCoeffs( 0 );
                    break;
                }
                case 2 :
                {
                    // set interpolation type
                    tInterpolationOrder = mtk::Interpolation_Order::QUADRATIC;

                    // get num of coefficients
                    tNumCoeff =  tNumCoeffs( 1 );
                    break;
                }
                case 3 :
                {
                    // set interpolation type
                    tInterpolationOrder = mtk::Interpolation_Order::CUBIC;

                    // get num of coefficients
                    tNumCoeff =  tNumCoeffs( 2 );
                    break;
                }
                default:
                {
                    MORIS_ERROR( false, "LINEAR, QUADRATIC or CUBIC only.");
                    break;
                }
            }

            //create a space time interpolation rule
            Interpolation_Rule tFIRule ( tGeometryType,
                    Interpolation_Type::LAGRANGE,
                    tInterpolationOrder,
                    Interpolation_Type::LAGRANGE,
                    mtk::Interpolation_Order::LINEAR );

            // fill random coefficients for master FI
            Matrix< DDRMat > tMasterDOFHatVel = 10.0 * arma::randu( tNumCoeff, iSpaceDim );
            Matrix< DDRMat > tMasterDOFHatP   = 10.0 * arma::randu( tNumCoeff, 1 );
            Matrix< DDRMat > tMasterDOFHatVis = 10.0 * arma::randu( tNumCoeff, 1 );

            // create a cell of field interpolators
            Cell< Field_Interpolator* > tMasterFIs( 3 );

            // create the field interpolator velocity
            tMasterFIs( 0 ) = new Field_Interpolator( iSpaceDim, tFIRule, &tGI, tVelDofTypes );
            tMasterFIs( 0 )->set_coeff( tMasterDOFHatVel );
            tMasterFIs( 0 )->set_space_time( tParamPoint );

            // create the field interpolator pressure
            tMasterFIs( 1 ) = new Field_Interpolator( 1, tFIRule, &tGI, tPDofTypes );
            tMasterFIs( 1 )->set_coeff( tMasterDOFHatP );
            tMasterFIs( 1 )->set_space_time( tParamPoint );

            // create the field interpolator viscosity
            tMasterFIs( 2 ) = new Field_Interpolator( 1, tFIRule, &tGI, tVisDofTypes );
            tMasterFIs( 2 )->set_coeff( tMasterDOFHatVis );
            tMasterFIs( 2 )->set_space_time( tParamPoint );

            // create the properties
            std::shared_ptr< fem::Property > tPropFluidDensity = std::make_shared< fem::Property >();
            tPropFluidDensity->set_parameters( { {{ tFluidDensity }} } );
            tPropFluidDensity->set_val_function( tConstValFunc_SPFluid );

            std::shared_ptr< fem::Property > tPropFluidViscosity = std::make_shared< fem::Property >();
            tPropFluidViscosity->set_parameters( { {{ tFluidViscosity }} } );
            tPropFluidViscosity->set_val_function( tConstValFunc_SPFluid );

            // define stabilization parameters
            fem::SP_Factory tSPFactory;

            std::shared_ptr< fem::Stabilization_Parameter > tSPIncFlow =
                    tSPFactory.create_SP( fem::Stabilization_Type::INCOMPRESSIBLE_FLOW );
            tSPIncFlow->set_dof_type_list( {{ MSI::Dof_Type::VX, MSI::Dof_Type::VY }, { MSI::Dof_Type::P }}, mtk::Master_Slave::MASTER );
            tSPIncFlow->set_property( tPropFluidDensity, "Density", mtk::Master_Slave::MASTER );
            tSPIncFlow->set_property( tPropFluidViscosity, "Viscosity", mtk::Master_Slave::MASTER );
            tSPIncFlow->set_parameters( { {{ 36.0 }} } );
            tSPIncFlow->set_space_dim( 2 );

            std::shared_ptr< fem::Stabilization_Parameter > tSPNitsche =
                    tSPFactory.create_SP( fem::Stabilization_Type::VELOCITY_DIRICHLET_NITSCHE );
            tSPNitsche->set_dof_type_list( {{ MSI::Dof_Type::VX, MSI::Dof_Type::VY }}, mtk::Master_Slave::MASTER );
            tSPNitsche->set_property( tPropFluidDensity, "Density", mtk::Master_Slave::MASTER );
            tSPNitsche->set_property( tPropFluidViscosity, "Viscosity", mtk::Master_Slave::MASTER );
            tSPNitsche->set_parameters( { {{ tGammaNitsche }}, {{1.0}} } );

            std::shared_ptr< fem::Stabilization_Parameter > tSPViscousGhost =
                    tSPFactory.create_SP( fem::Stabilization_Type::VISCOUS_GHOST );
            tSPViscousGhost->set_parameters( {{{ tGammaGPmu }} });
            tSPViscousGhost->set_property( tPropFluidViscosity, "Viscosity", mtk::Master_Slave::MASTER );

            std::shared_ptr< fem::Stabilization_Parameter > tSPConvectiveGhost =
                    tSPFactory.create_SP( fem::Stabilization_Type::CONVECTIVE_GHOST );
            tSPConvectiveGhost->set_dof_type_list( {{ MSI::Dof_Type::VX, MSI::Dof_Type::VY }}, mtk::Master_Slave::MASTER );
            tSPConvectiveGhost->set_parameters( {{{ tGammaGPu }} });
            tSPConvectiveGhost->set_property( tPropFluidDensity, "Density", mtk::Master_Slave::MASTER );

            std::shared_ptr< fem::Stabilization_Parameter > tSPPressureGhost =
                    tSPFactory.create_SP( fem::Stabilization_Type::PRESSURE_GHOST );
            tSPPressureGhost->set_dof_type_list( {{ MSI::Dof_Type::VX, MSI::Dof_Type::VY }}, mtk::Master_Slave::MASTER );
            tSPPressureGhost->set_parameters( { {{ tGammaGPp }}, {{ 1.0 }} });
            tSPPressureGhost->set_property( tPropFluidViscosity, "Viscosity", mtk::Master_Slave::MASTER );
            tSPPressureGhost->set_property( tPropFluidDensity, "Density", mtk::Master_Slave::MASTER );

            // set a fem set pointer
            MSI::Equation_Set * tSet = new fem::Set();
            tSPIncFlow->set_set_pointer( reinterpret_cast< fem::Set* >( tSet ) );
            tSPNitsche->set_set_pointer( reinterpret_cast< fem::Set* >( tSet ) );
            tSPViscousGhost->set_set_pointer( reinterpret_cast< fem::Set* >( tSet ) );
            tSPConvectiveGhost->set_set_pointer( reinterpret_cast< fem::Set* >( tSet ) );
            tSPPressureGhost->set_set_pointer( reinterpret_cast< fem::Set* >( tSet ) );

            // set size for the set EqnObjDofTypeList
            tSPIncFlow->mSet->mUniqueDofTypeList.resize( 100, MSI::Dof_Type::END_ENUM );

            // set size and populate the set dof type map
            tSPIncFlow->mSet->mUniqueDofTypeMap.set_size( static_cast< int >( MSI::Dof_Type::END_ENUM ) + 1, 1, -1 );
            tSPIncFlow->mSet->mUniqueDofTypeMap( static_cast< int >( MSI::Dof_Type::VX ) )        = 0;
            tSPIncFlow->mSet->mUniqueDofTypeMap( static_cast< int >( MSI::Dof_Type::P ) )         = 1;
            tSPIncFlow->mSet->mUniqueDofTypeMap( static_cast< int >( MSI::Dof_Type::VISCOSITY ) ) = 2;

            // set size and populate the set master dof type map
            tSPIncFlow->mSet->mMasterDofTypeMap.set_size( static_cast< int >( MSI::Dof_Type::END_ENUM ) + 1, 1, -1 );
            tSPIncFlow->mSet->mMasterDofTypeMap( static_cast< int >( MSI::Dof_Type::VX ) )        = 0;
            tSPIncFlow->mSet->mMasterDofTypeMap( static_cast< int >( MSI::Dof_Type::P ) )         = 1;
            tSPIncFlow->mSet->mMasterDofTypeMap( static_cast< int >( MSI::Dof_Type::VISCOSITY ) ) = 2;

            // build global dof type list
            tSPIncFlow->get_global_dof_type_list();
            tSPNitsche->get_global_dof_type_list();
            tSPViscousGhost->get_global_dof_type_list();
            tSPConvectiveGhost->get_global_dof_type_list();
            tSPPressureGhost->get_global_dof_type_list();

            // set normal
            tSPIncFlow->set_normal( tNormal );
            tSPNitsche->set_normal( tNormal );
            tSPViscousGhost->set_normal( tNormal );
            tSPConvectiveGhost->set_normal( tNormal );
            tSPPressureGhost->set_normal( tNormal );

            // set order
            tSPIncFlow->set_interpolation_order( iInterpOrder );
            tSPNitsche->set_interpolation_order( iInterpOrder );
            tSPViscousGhost->set_interpolation_order( iInterpOrder );
            tSPConvectiveGhost->set_interpolation_order( iInterpOrder );
            tSPPressureGhost->set_interpolation_order( iInterpOrder );

            // create a field interpolator manager
            moris::Cell< moris::Cell< enum PDV_Type > > tDummyDv;
            Field_Interpolator_Manager tFIManager(
                    { tVelDofTypes, tPDofTypes, tVisDofTypes }, tDummyDv, tSet );

            // populate the field interpolator manager
            tFIManager.mFI = tMasterFIs;
            tFIManager.mIPGeometryInterpolator = &tGI;
            tFIManager.mIGGeometryInterpolator = &tGI;

            // set the interpolator manager to the set
            tSPIncFlow->mSet->mMasterFIManager = &tFIManager;

            // set SP field interpolator manager
            tSPIncFlow->set_field_interpolator_manager( &tFIManager );
            tSPNitsche->set_field_interpolator_manager( &tFIManager );
            tSPViscousGhost->set_field_interpolator_manager( &tFIManager );
            tSPConvectiveGhost->set_field_interpolator_manager( &tFIManager );
            tSPPressureGhost->set_field_interpolator_manager( &tFIManager );

//            // print for debug
//            std::cout<<"Case: Geometry "<<iSpaceDim<<" Order "<<iInterpOrder<<std::endl;

            // populate the requested master dof type for SP
            moris::Cell< moris::Cell< MSI::Dof_Type > > tMasterDofTypes =
                    tSPIncFlow->get_global_dof_type_list();

            // loop over requested dof type
            for( uint iRequestedDof = 0; iRequestedDof < tMasterDofTypes.size(); iRequestedDof++ )
            {
                // derivative dof type
                Cell< MSI::Dof_Type > tDofDerivative = tMasterDofTypes( iRequestedDof );

                // evaluate dspdu
                Matrix< DDRMat > tdspdu = tSPIncFlow->dSPdMasterDOF( tDofDerivative );

                // evaluate dfluxdu by FD
                Matrix< DDRMat > tdspduFD;
                tSPIncFlow->eval_dSPdDOF_FD( tDofDerivative, tdspduFD, tPerturbation );

                // check that analytical and FD match
                bool tCheckSPSUPGPSPG = fem::check( tdspdu, tdspduFD, tEpsilon );
                REQUIRE( tCheckSPSUPGPSPG );
            }

            // populate the requested master dof type for SP
            tMasterDofTypes = tSPNitsche->get_global_dof_type_list();

            // loop over requested dof type
            for( uint iRequestedDof = 0; iRequestedDof < tMasterDofTypes.size(); iRequestedDof++ )
            {
                // derivative dof type
                Cell< MSI::Dof_Type > tDofDerivative = tMasterDofTypes( iRequestedDof );

                // evaluate dspdu
                Matrix< DDRMat > tdspdu = tSPNitsche->dSPdMasterDOF( tDofDerivative );

                // evaluate dfluxdu by FD
                Matrix< DDRMat > tdspduFD;
                tSPNitsche->eval_dSPdDOF_FD( tDofDerivative, tdspduFD, tPerturbation );

                // check that analytical and FD match
                bool tCheckSPNitsche = fem::check( tdspdu, tdspduFD, tEpsilon );
                REQUIRE( tCheckSPNitsche );
            }

            // populate the requested master dof type for SP
            tMasterDofTypes = tSPViscousGhost->get_global_dof_type_list();

            // loop over requested dof type
            for( uint iRequestedDof = 0; iRequestedDof < tMasterDofTypes.size(); iRequestedDof++ )
            {
                // derivative dof type
                Cell< MSI::Dof_Type > tDofDerivative = tMasterDofTypes( iRequestedDof );

                // evaluate dspdu
                Matrix< DDRMat > tdspdu = tSPViscousGhost->dSPdMasterDOF( tDofDerivative );

                // evaluate dfluxdu by FD
                Matrix< DDRMat > tdspduFD;
                tSPViscousGhost->eval_dSPdDOF_FD( tDofDerivative, tdspduFD, tPerturbation );

                // check that analytical and FD match
                bool tCheckSPViscousGhost = fem::check( tdspdu, tdspduFD, tEpsilon );
                REQUIRE( tCheckSPViscousGhost );
            }

            // populate the requested master dof type for SP
            tMasterDofTypes = tSPConvectiveGhost->get_global_dof_type_list();

            // loop over requested dof type
            for( uint iRequestedDof = 0; iRequestedDof < tMasterDofTypes.size(); iRequestedDof++ )
            {
                // derivative dof type
                Cell< MSI::Dof_Type > tDofDerivative = tMasterDofTypes( iRequestedDof );

                // evaluate dspdu
                Matrix< DDRMat > tdspdu = tSPConvectiveGhost->dSPdMasterDOF( tDofDerivative );

                // evaluate dfluxdu by FD
                Matrix< DDRMat > tdspduFD;
                tSPConvectiveGhost->eval_dSPdDOF_FD( tDofDerivative, tdspduFD, tPerturbation );

                // check that analytical and FD match
                bool tCheckSPConvectiveGhost = fem::check( tdspdu, tdspduFD, tEpsilon );
                REQUIRE( tCheckSPConvectiveGhost );
            }

            // populate the requested master dof type for SP
            tMasterDofTypes = tSPPressureGhost->get_global_dof_type_list();

            // loop over requested dof type
            for( uint iRequestedDof = 0; iRequestedDof < tMasterDofTypes.size(); iRequestedDof++ )
            {
                // derivative dof type
                Cell< MSI::Dof_Type > tDofDerivative = tMasterDofTypes( iRequestedDof );

                // evaluate dspdu
                Matrix< DDRMat > tdspdu = tSPPressureGhost->dSPdMasterDOF( tDofDerivative );

                // evaluate dfluxdu by FD
                Matrix< DDRMat > tdspduFD;
                tSPPressureGhost->eval_dSPdDOF_FD( tDofDerivative, tdspduFD, tPerturbation );

                // check that analytical and FD match
                bool tCheckSPPressureGhost = fem::check( tdspdu, tdspduFD, tEpsilon );
                REQUIRE( tCheckSPPressureGhost );
            }

            // clean up
            tMasterFIs.clear();
        }
    }
}/*END_TEST_CASE*/

