#include <string>
#include <catch.hpp>
#include <memory>
#include "assert.hpp"

#define protected public
#define private   public
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_IWG.hpp"
#include "cl_FEM_Set.hpp"
#undef protected
#undef private
//MTK/src
#include "cl_MTK_Enums.hpp"
//LINALG/src
#include "op_equal_equal.hpp"
//FEM/INT/src
#include "cl_FEM_Enums.hpp"
#include "cl_FEM_Field_Interpolator.hpp"
#include "cl_FEM_Property.hpp"
#include "cl_FEM_CM_Factory.hpp"
#include "cl_FEM_IWG_Factory.hpp"

void tConstValFunction_UTIWGDIFFBULK
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 );
}

void tGeoValFunction_UTIWGDIFFBULK
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 ) * aFIManager->get_IP_geometry_interpolator()->valx()( 0 );
}

void tFIValFunction_UTIWGDIFFBULK
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 ) * aFIManager->get_field_interpolators_for_type( moris::MSI::Dof_Type::TEMP )->val();
}

void tFIDerFunction_UTIWGDIFFBULK
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 ) * aFIManager->get_field_interpolators_for_type( moris::MSI::Dof_Type::TEMP )->N();
}

void tFIValDvFunction_UTIWGDIFFBULK
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 ) * aFIManager->get_field_interpolators_for_type( GEN_DV::DENSITY0 )->val();
}

void tFIDerDvFunction_UTIWGDIFFBULK
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 ) * aFIManager->get_field_interpolators_for_type( GEN_DV::DENSITY0 )->N();
}

using namespace moris;
using namespace fem;


TEST_CASE( "IWG_Diffusion_Bulk", "[moris],[fem],[IWG_Diffusion_Bulk]" )
{
    // define an epsilon environment
    real tEpsilon = 1E-6;

    // define a perturbation relative size
    real tPerturbation = 1E-6;

    // create the properties
    std::shared_ptr< fem::Property > tPropMasterConductivity = std::make_shared< fem::Property > ();
    tPropMasterConductivity->set_parameters( { {{ 1.0 }} } );
    tPropMasterConductivity->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tPropMasterConductivity->set_val_function( tFIValFunction_UTIWGDIFFBULK );
    tPropMasterConductivity->set_dof_derivative_functions( { tFIDerFunction_UTIWGDIFFBULK } );

    std::shared_ptr< fem::Property > tPropMasterTempLoad = std::make_shared< fem::Property > ();
    tPropMasterTempLoad->set_parameters( { {{ 2.0 }} } );
    tPropMasterTempLoad->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tPropMasterTempLoad->set_val_function( tFIValFunction_UTIWGDIFFBULK );
    tPropMasterTempLoad->set_dof_derivative_functions( { tFIDerFunction_UTIWGDIFFBULK } );

    std::shared_ptr< fem::Property > tPropMasterDensity = std::make_shared< fem::Property > ();
    tPropMasterDensity->set_parameters( { {{ 3.0 }} } );
    tPropMasterDensity->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tPropMasterDensity->set_val_function( tFIValFunction_UTIWGDIFFBULK );
    tPropMasterDensity->set_dof_derivative_functions( { tFIDerFunction_UTIWGDIFFBULK } );

    std::shared_ptr< fem::Property > tPropMasterHeatCapacity = std::make_shared< fem::Property > ();
    tPropMasterHeatCapacity->set_parameters( { {{ 4.0 }} } );
    tPropMasterHeatCapacity->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tPropMasterHeatCapacity->set_val_function( tFIValFunction_UTIWGDIFFBULK );
    tPropMasterHeatCapacity->set_dof_derivative_functions( { tFIDerFunction_UTIWGDIFFBULK } );

    // define constitutive models
    fem::CM_Factory tCMFactory;

    std::shared_ptr< fem::Constitutive_Model > tCMMasterDiffLinIso = tCMFactory.create_CM( fem::Constitutive_Type::DIFF_LIN_ISO );
    tCMMasterDiffLinIso->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tCMMasterDiffLinIso->set_property( tPropMasterConductivity, "Conductivity" );
    tCMMasterDiffLinIso->set_space_dim( 3 );

    // define the IWGs
    fem::IWG_Factory tIWGFactory;

    std::shared_ptr< fem::IWG > tIWG = tIWGFactory.create_IWG( fem::IWG_Type::SPATIALDIFF_BULK );
    tIWG->set_residual_dof_type( { MSI::Dof_Type::TEMP } );
    tIWG->set_dof_type_list( {{ MSI::Dof_Type::TEMP }}, mtk::Master_Slave::MASTER );
    tIWG->set_constitutive_model( tCMMasterDiffLinIso, "Diffusion", mtk::Master_Slave::MASTER );
    tIWG->set_property( tPropMasterTempLoad, "Load", mtk::Master_Slave::MASTER );
    tIWG->set_property( tPropMasterDensity, "Density", mtk::Master_Slave::MASTER );
    tIWG->set_property( tPropMasterHeatCapacity, "HeatCapacity", mtk::Master_Slave::MASTER );

    // create evaluation point xi, tau
    //------------------------------------------------------------------------------
    Matrix< DDRMat > tParamPoint = {{ 0.35}, {-0.25}, { 0.75}, { 0.0 }};

    // space and time geometry interpolators
    //------------------------------------------------------------------------------
    // create a space geometry interpolation rule
    Interpolation_Rule tGIRule( mtk::Geometry_Type::HEX,
                                Interpolation_Type::LAGRANGE,
                                mtk::Interpolation_Order::LINEAR,
                                Interpolation_Type::LAGRANGE,
                                mtk::Interpolation_Order::LINEAR );

    // create a space time geometry interpolator
    Geometry_Interpolator tGI( tGIRule );

    // create space coeff xHat
    Matrix< DDRMat > tXHat = {{ 0.0, 0.0, 0.0 },
                              { 1.0, 0.0, 0.0 },
                              { 1.0, 1.0, 0.0 },
                              { 0.0, 1.0, 0.0 },
                              { 0.0, 0.0, 1.0 },
                              { 1.0, 0.0, 1.0 },
                              { 1.0, 1.0, 1.0 },
                              { 0.0, 1.0, 1.0 }};

    // create time coeff tHat
    Matrix< DDRMat > tTHat = {{ 0.0 }, { 1.0 }};

    // set the coefficients xHat, tHat
    tGI.set_coeff( tXHat, tTHat );

    // set the evaluation point
    tGI.set_space_time( tParamPoint );

    // field interpolators
    //------------------------------------------------------------------------------
    //create a space time interpolation rule
    Interpolation_Rule tFIRule ( mtk::Geometry_Type::HEX,
                                 Interpolation_Type::LAGRANGE,
                                 mtk::Interpolation_Order::LINEAR,
                                 Interpolation_Type::LAGRANGE,
                                 mtk::Interpolation_Order::LINEAR );

    // create random coefficients
    arma::Mat< double > tMatrix;
    tMatrix.randu( 16, 1 );
    Matrix< DDRMat > tDOFHat;
    tDOFHat.matrix_data() = 10.0 * tMatrix;

    // create a cell of field interpolators for IWG
    Cell< Field_Interpolator* > tFIs( 1 );

    // create the field interpolator
    tFIs( 0 ) = new Field_Interpolator( 1, tFIRule, &tGI, { MSI::Dof_Type::TEMP } );

    // set the coefficients uHat
    tFIs( 0 )->set_coeff( tDOFHat );

    //set the evaluation point xi, tau
    tFIs( 0 )->set_space_time( tParamPoint );

    // set a fem set pointer
    MSI::Equation_Set * tSet = new fem::Set();
    tIWG->set_set_pointer( static_cast< fem::Set* >( tSet ) );

    // set size for the set EqnObjDofTypeList
    tIWG->mSet->mUniqueDofTypeList.resize( 4, MSI::Dof_Type::END_ENUM );

    // set size and populate the set dof type map
    tIWG->mSet->mUniqueDofTypeMap.set_size( static_cast< int >( MSI::Dof_Type::END_ENUM ) + 1, 1, -1 );
    tIWG->mSet->mUniqueDofTypeMap( static_cast< int >( MSI::Dof_Type::TEMP ) ) = 0;

    // set size and populate the set master dof type map
    tIWG->mSet->mMasterDofTypeMap.set_size( static_cast< int >(MSI::Dof_Type::END_ENUM) + 1, 1, -1 );
    tIWG->mSet->mMasterDofTypeMap( static_cast< int >( MSI::Dof_Type::TEMP ) ) = 0;

    // set size and fill the set residual assembly map
    tIWG->mSet->mResDofAssemblyMap.resize( 1 );
    tIWG->mSet->mResDofAssemblyMap( 0 ) = { { 0, 15 } };

    // set size and fill the set jacobian assembly map
    tIWG->mSet->mJacDofAssemblyMap.resize( 1 );
    tIWG->mSet->mJacDofAssemblyMap( 0 ) = { { 0, 15 } };

    // set size and init the set residual and jacobian
    tIWG->mSet->mResidual.resize( 1 );
    tIWG->mSet->mResidual( 0 ).set_size( 16, 1, 0.0 );
    tIWG->mSet->mJacobian.set_size( 16, 16, 0.0 );

    // build global dof type list
    tIWG->get_global_dof_type_list();

    // populate the requested master dof type
    tIWG->mRequestedMasterGlobalDofTypes = {{ MSI::Dof_Type::TEMP }};

    // create a field interpolator manager
    moris::Cell< moris::Cell< enum MSI::Dof_Type > > tDummy;
    Field_Interpolator_Manager tFIManager( tDummy, tSet );

    // populate the field interpolator manager
    tFIManager.mFI = tFIs;
    tFIManager.mIPGeometryInterpolator = &tGI;
    tFIManager.mIGGeometryInterpolator = &tGI;

    // set IWG field interpolator manager
    tIWG->set_field_interpolator_manager( &tFIManager );

    // check evaluation of the residual for IWG
    //------------------------------------------------------------------------------
    // evaluate the residual
    tIWG->compute_residual( 1.0 );

    // check evaluation of the jacobian  by FD
    //------------------------------------------------------------------------------
    // init the jacobian for IWG and FD evaluation
    Matrix< DDRMat > tJacobian;
    Matrix< DDRMat > tJacobianFD;

    // check jacobian by FD
    bool tCheckJacobian = tIWG->check_jacobian( tPerturbation,
                                                tEpsilon,
                                                1.0,
                                                tJacobian,
                                                tJacobianFD );

    // require check is true
    REQUIRE( tCheckJacobian );

//    print( tJacobians( 0 ),   "tJacobians" );
//    print( tJacobiansFD( 0 ), "tJacobiansFD" );

}/*END_TEST_CASE*/

TEST_CASE( "IWG_Diffusion_Bulk_Geo_Prop", "[moris],[fem],[IWG_Diff_Bulk_Geo_Prop]" )
{
    // define an epsilon environment
    real tEpsilon = 1E-6;

    // define aperturbation relative size
    real tPerturbation = 1E-6;

    // create the properties
    std::shared_ptr< fem::Property > tPropMasterConductivity = std::make_shared< fem::Property > ();
    tPropMasterConductivity->set_parameters( { {{ 1.0 }} } );
    tPropMasterConductivity->set_val_function( tGeoValFunction_UTIWGDIFFBULK );

    std::shared_ptr< fem::Property > tPropMasterTempLoad = std::make_shared< fem::Property > ();
    tPropMasterTempLoad->set_parameters( { {{ 1.0 }} } );
    tPropMasterTempLoad->set_val_function( tGeoValFunction_UTIWGDIFFBULK );

    // define constitutive models
    fem::CM_Factory tCMFactory;

    std::shared_ptr< fem::Constitutive_Model > tCMMasterDiffLinIso = tCMFactory.create_CM( fem::Constitutive_Type::DIFF_LIN_ISO );
    tCMMasterDiffLinIso->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tCMMasterDiffLinIso->set_property( tPropMasterConductivity, "Conductivity" );
    tCMMasterDiffLinIso->set_space_dim( 3 );

    // define the IWGs
    fem::IWG_Factory tIWGFactory;

    std::shared_ptr< fem::IWG > tIWG = tIWGFactory.create_IWG( fem::IWG_Type::SPATIALDIFF_BULK );
    tIWG->set_residual_dof_type( { MSI::Dof_Type::TEMP } );
    tIWG->set_dof_type_list( {{ MSI::Dof_Type::TEMP }}, mtk::Master_Slave::MASTER );
    tIWG->set_constitutive_model( tCMMasterDiffLinIso, "Diffusion", mtk::Master_Slave::MASTER );
    tIWG->set_property( tPropMasterTempLoad, "Load", mtk::Master_Slave::MASTER );

    // create evaluation point xi, tau
    //------------------------------------------------------------------------------
    Matrix< DDRMat > tParamPoint = {{ 0.35}, {-0.25}, { 0.75}, { 0.0 }};

    // space and time geometry interpolators
    //------------------------------------------------------------------------------
    // create a space geometry interpolation rule
    Interpolation_Rule tGIRule( mtk::Geometry_Type::HEX,
                                Interpolation_Type::LAGRANGE,
                                mtk::Interpolation_Order::LINEAR,
                                Interpolation_Type::LAGRANGE,
                                mtk::Interpolation_Order::LINEAR );

    // create a space time geometry interpolator
    Geometry_Interpolator tGI( tGIRule );

    // create space coeff xHat
    Matrix< DDRMat > tXHat = {{ 0.0, 0.0, 0.0 },
                              { 1.0, 0.0, 0.0 },
                              { 1.0, 1.0, 0.0 },
                              { 0.0, 1.0, 0.0 },
                              { 0.0, 0.0, 1.0 },
                              { 1.0, 0.0, 1.0 },
                              { 1.0, 1.0, 1.0 },
                              { 0.0, 1.0, 1.0 }};

    // create time coeff tHat
    Matrix< DDRMat > tTHat = {{ 0.0 }, { 1.0 }};

    // set the coefficients xHat, tHat
    tGI.set_coeff( tXHat, tTHat );

    // set the evaluation point
    tGI.set_space_time( tParamPoint );

    // field interpolators
    //------------------------------------------------------------------------------
    //create a space time interpolation rule
    Interpolation_Rule tFIRule ( mtk::Geometry_Type::HEX,
                                 Interpolation_Type::LAGRANGE,
                                 mtk::Interpolation_Order::LINEAR,
                                 Interpolation_Type::CONSTANT,
                                 mtk::Interpolation_Order::CONSTANT );

    // create random coefficients
    arma::Mat< double > tMatrix;
    tMatrix.randu( 8, 1 );
    Matrix< DDRMat > tDOFHat;
    tDOFHat.matrix_data() = 10.0 * tMatrix;

    // create a cell of field interpolators for IWG
    Cell< Field_Interpolator* > tFIs( 1 );

    // create the field interpolator
    tFIs( 0 ) = new Field_Interpolator( 1, tFIRule, &tGI, { MSI::Dof_Type::TEMP } );

    // set the coefficients uHat
    tFIs( 0 )->set_coeff( tDOFHat );

    //set the evaluation point xi, tau
    tFIs( 0 )->set_space_time( tParamPoint );

    MSI::Equation_Set * tSet = new fem::Set();

    tIWG->set_set_pointer(static_cast<fem::Set*>(tSet));

    tIWG->mSet->mUniqueDofTypeList.resize( 4, MSI::Dof_Type::END_ENUM );

    tIWG->mSet->mUniqueDofTypeMap.set_size( static_cast< int >(MSI::Dof_Type::END_ENUM) + 1, 1, -1 );
    tIWG->mSet->mUniqueDofTypeMap( static_cast< int >(MSI::Dof_Type::TEMP) ) = 0;

    tIWG->mSet->mMasterDofTypeMap.set_size( static_cast< int >(MSI::Dof_Type::END_ENUM) + 1, 1, -1 );
    tIWG->mSet->mMasterDofTypeMap( static_cast< int >(MSI::Dof_Type::TEMP) ) = 0;

    tIWG->mSet->mResDofAssemblyMap.resize( 1 );
    tIWG->mSet->mJacDofAssemblyMap.resize( 1 );
    tIWG->mSet->mResDofAssemblyMap( 0 ) = { { 0, 7 } };
    tIWG->mSet->mJacDofAssemblyMap( 0 ) = { { 0, 7 } };

    tIWG->mSet->mResidual.resize( 1 );
    tIWG->mSet->mResidual( 0 ).set_size( 8, 1, 0.0 );
    tIWG->mSet->mJacobian.set_size( 8, 8, 0.0 );

    // build global dof type list
    tIWG->get_global_dof_type_list();

    tIWG->mRequestedMasterGlobalDofTypes = {{ MSI::Dof_Type::TEMP }};

    moris::Cell< moris::Cell< enum MSI::Dof_Type > > tDummy;
    Field_Interpolator_Manager tFIManager( tDummy, tSet );

    tFIManager.mFI = tFIs;
    tFIManager.mIPGeometryInterpolator = &tGI;
    tFIManager.mIGGeometryInterpolator = &tGI;

    // set IWG field interpolator manager
    tIWG->set_field_interpolator_manager( &tFIManager );

    // check evaluation of the residual for IWG
    //------------------------------------------------------------------------------
    // evaluate the residual
    tIWG->compute_residual( 1.0 );

    // check evaluation of the jacobian  by FD
    //------------------------------------------------------------------------------
    // init the jacobian for IWG and FD evaluation
    Matrix< DDRMat > tJacobians;
    Matrix< DDRMat > tJacobiansFD;

    // check jacobian by FD
    bool tCheckJacobian = tIWG->check_jacobian( tPerturbation,
                                                tEpsilon,
                                                1.0,
                                                tJacobians,
                                                tJacobiansFD );
    // require check is true
    REQUIRE( tCheckJacobian );

    // clean up
    tFIs.clear();

}/* END_TEST_CASE */

TEST_CASE( "IWG_Diffusion_Bulk_Dv_Prop", "[moris],[fem],[IWG_Diff_Bulk_Dv_Prop]" )
{
    // define an epsilon environment
    real tEpsilon = 1E-6;

    // define aperturbation relative size
    real tPerturbation = 1E-6;

    // create the properties
    std::shared_ptr< fem::Property > tPropMasterConductivity = std::make_shared< fem::Property > ();
    tPropMasterConductivity->set_parameters( { {{ 1.0 }} } );
    tPropMasterConductivity->set_dv_type_list( {{ GEN_DV::DENSITY0 }} );
    tPropMasterConductivity->set_val_function( tFIValDvFunction_UTIWGDIFFBULK );
    tPropMasterConductivity->set_dv_derivative_functions( { tFIDerDvFunction_UTIWGDIFFBULK } );

    std::shared_ptr< fem::Property > tPropMasterTempLoad = std::make_shared< fem::Property > ();
    tPropMasterTempLoad->set_parameters( { {{ 1.0 }} } );
    tPropMasterTempLoad->set_val_function( tGeoValFunction_UTIWGDIFFBULK );

    // define constitutive models
    fem::CM_Factory tCMFactory;

    std::shared_ptr< fem::Constitutive_Model > tCMMasterDiffLinIso = tCMFactory.create_CM( fem::Constitutive_Type::DIFF_LIN_ISO );
    tCMMasterDiffLinIso->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tCMMasterDiffLinIso->set_property( tPropMasterConductivity, "Conductivity" );
    tCMMasterDiffLinIso->set_space_dim( 3 );

    // define the IWGs
    fem::IWG_Factory tIWGFactory;

    std::shared_ptr< fem::IWG > tIWG = tIWGFactory.create_IWG( fem::IWG_Type::SPATIALDIFF_BULK );
    tIWG->set_residual_dof_type( { MSI::Dof_Type::TEMP } );
    tIWG->set_dof_type_list( {{ MSI::Dof_Type::TEMP }}, mtk::Master_Slave::MASTER );
    tIWG->set_constitutive_model( tCMMasterDiffLinIso, "Diffusion", mtk::Master_Slave::MASTER );
    tIWG->set_property( tPropMasterTempLoad, "Load", mtk::Master_Slave::MASTER );

    // create evaluation point xi, tau
    //------------------------------------------------------------------------------
    Matrix< DDRMat > tParamPoint = {{ 0.35}, {-0.25}, { 0.75}, { 0.0 }};

    // space and time geometry interpolators
    //------------------------------------------------------------------------------
    // create a space geometry interpolation rule
    Interpolation_Rule tGIRule( mtk::Geometry_Type::HEX,
                                Interpolation_Type::LAGRANGE,
                                mtk::Interpolation_Order::LINEAR,
                                Interpolation_Type::LAGRANGE,
                                mtk::Interpolation_Order::LINEAR );

    // create a space time geometry interpolator
    Geometry_Interpolator tGI( tGIRule );

    // create space coeff xHat
    arma::Mat< double > tXMatrix;
    tXMatrix.randu( 8, 3 );
    Matrix< DDRMat > tXHat;
    tXHat.matrix_data() = 10.0 * tXMatrix;

    // create time coeff tHat
    Matrix< DDRMat > tTHat = {{ 0.0 }, { 1.0 }};

    // set the coefficients xHat, tHat
    tGI.set_coeff( tXHat, tTHat );

    // set the evaluation point
    tGI.set_space_time( tParamPoint );

    // field interpolators
    //------------------------------------------------------------------------------
    //create a space time interpolation rule
    Interpolation_Rule tFIRule ( mtk::Geometry_Type::HEX,
                                 Interpolation_Type::LAGRANGE,
                                 mtk::Interpolation_Order::LINEAR,
                                 Interpolation_Type::CONSTANT,
                                 mtk::Interpolation_Order::CONSTANT );

    // create random coefficients
    arma::Mat< double > tMatrix;
    tMatrix.randu( 8, 1 );
    Matrix< DDRMat > tDOFHat;
    tDOFHat.matrix_data() = 10.0 * tMatrix;

    // create a cell of field interpolators for IWG
    Cell< Field_Interpolator* > tFIs( 1 );

    // create the field interpolator
    tFIs( 0 ) = new Field_Interpolator( 1, tFIRule, &tGI, { MSI::Dof_Type::TEMP } );

    // set the coefficients uHat
    tFIs( 0 )->set_coeff( tDOFHat );

    //set the evaluation point xi, tau
    tFIs( 0 )->set_space_time( tParamPoint );

    // create random coefficients
    arma::Mat< double > tDvMatrix;
    tDvMatrix.randu( 8, 1 );
    Matrix< DDRMat > tDvHat;
    tDvHat.matrix_data() = 10.0 * tDvMatrix;

    // create a cell of dv field interpolators for IWG
    Cell< Field_Interpolator* > tDvFIs( 1 );

    // create the field interpolator
    tDvFIs( 0 ) = new Field_Interpolator( 1, tFIRule, &tGI, { GEN_DV::DENSITY0 } );

    // set the coefficients
    tDvFIs( 0 )->set_coeff( tDvHat );

    //set the evaluation point xi, tau
    tDvFIs( 0 )->set_space_time( tParamPoint );

    // create a fem set
    MSI::Equation_Set * tSet = new fem::Set();

    tIWG->set_set_pointer(static_cast<fem::Set*>(tSet));

    tIWG->mSet->mUniqueDofTypeList.resize( 4, MSI::Dof_Type::END_ENUM );
    tIWG->mSet->mUniqueDvTypeList.resize( 5, GEN_DV::END_ENUM );

    tIWG->mSet->mUniqueDofTypeMap.set_size( static_cast< int >(MSI::Dof_Type::END_ENUM) + 1, 1, -1 );
    tIWG->mSet->mUniqueDofTypeMap( static_cast< int >(MSI::Dof_Type::TEMP) ) = 0;

    tIWG->mSet->mMasterDofTypeMap.set_size( static_cast< int >(MSI::Dof_Type::END_ENUM) + 1, 1, -1 );
    tIWG->mSet->mMasterDofTypeMap( static_cast< int >(MSI::Dof_Type::TEMP) ) = 0;

    tIWG->mSet->mUniqueDvTypeMap.set_size( static_cast< int >( GEN_DV::END_ENUM ) + 1, 1, -1 );
    tIWG->mSet->mUniqueDvTypeMap( static_cast< int >( GEN_DV::DENSITY0 ) ) = 0;

    tIWG->mSet->mMasterDvTypeMap.set_size( static_cast< int >( GEN_DV::END_ENUM ) + 1, 1, -1 );
    tIWG->mSet->mMasterDvTypeMap( static_cast< int >( GEN_DV::DENSITY0 ) ) = 0;

    tIWG->mSet->mResDofAssemblyMap.resize( 1 );
    tIWG->mSet->mResDofAssemblyMap( 0 ) = { { 0, 7 } };

    tIWG->mSet->mDvAssemblyMap.resize( 1 );
    tIWG->mSet->mDvAssemblyMap( 0 ) = { { 0, 7 } };

    tIWG->mSet->mResidual.resize( 1 );
    tIWG->mSet->mResidual( 0 ).set_size( 8, 1, 0.0 );

    // build global dof type list
    tIWG->get_global_dof_type_list();
    tIWG->get_global_dv_type_list();

    tIWG->mRequestedMasterGlobalDofTypes = {{ MSI::Dof_Type::TEMP }};

    moris::Cell< moris::Cell< enum MSI::Dof_Type > > tDummy;
    Field_Interpolator_Manager tFIManager( tDummy, tSet );

    tFIManager.mFI = tFIs;
    tFIManager.mDvFI = tDvFIs;
    tFIManager.mIPGeometryInterpolator = &tGI;
    tFIManager.mIGGeometryInterpolator = &tGI;

    // set the interpolator manager to the set
    tIWG->mSet->mMasterFIManager = &tFIManager;

    // set IWG field interpolator manager
    tIWG->set_field_interpolator_manager( &tFIManager );

    // check evaluation of drdpdv  by FD
    //------------------------------------------------------------------------------
    // init the jacobian for IWG and FD evaluation
    Cell< Matrix< DDRMat > > tdRdpMatFD;
    Cell< Matrix< DDRMat > > tdRdpGeoFD;
    Cell< Matrix< DDSMat > > tIsActive = { {{ 1 },{ 1 },{ 1 },{ 1 },{ 1 },{ 1 },{ 1 },{ 1 }},
                                           {{ 1 },{ 1 },{ 1 },{ 1 },{ 1 },{ 1 },{ 1 },{ 1 }},
                                           {{ 1 },{ 1 },{ 1 },{ 1 },{ 1 },{ 1 },{ 1 },{ 1 }} };

    // check jacobian by FD
    tIWG->compute_dRdp_FD_material( 1.0,
                                    tPerturbation,
                                    tdRdpMatFD );

    tIWG->compute_dRdp_FD_geometry( 1.0,
                                    tPerturbation,
                                    tIsActive,
                                    tdRdpGeoFD );

    // print for debug
    //print( tdrdpdvMatFD( 0 ), "tdrdpdvMatFD" );
    //print( tdrdpdvGeoFD( 0 ), "tdrdpdvGeoFD" );

    // clean up
    tFIs.clear();
    tDvFIs.clear();

}/* END_TEST_CASE */
