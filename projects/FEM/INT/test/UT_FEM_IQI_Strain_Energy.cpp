/*
 * UT_FEM_IQI_Strain_Energy.cpp
 *
 *  Created on: Dec 5, 2019
 *      Author: noel
 */

#include <string>
#include <catch.hpp>
#include <memory>

#include "assert.hpp"

#define protected public
#define private   public
//FEM/INT/src
#include "cl_FEM_Model.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_FEM_IQI.hpp"
#include "cl_FEM_Set.hpp"
#undef protected
#undef private
//FEM/INT/src
#include "cl_FEM_Enums.hpp"                                //FEM//INT/src
#include "cl_FEM_Field_Interpolator.hpp"
#include "cl_FEM_Property.hpp"
#include "cl_FEM_CM_Factory.hpp"
#include "cl_FEM_IQI_Factory.hpp"
#include "FEM_Test_Proxy/cl_FEM_Design_Variable_Interface_Proxy.hpp"
//FEM/MSI/src
#include "cl_MSI_Design_Variable_Interface.hpp"
//MTK/src
#include "cl_MTK_Enums.hpp"
//LINALG/src
#include "op_equal_equal.hpp"

void tConstValFunction_UTIQISTRAINENERGY
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 );
}


void tFIValDvFunction_UTIQISTRAINENERGY
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 ) * aFIManager->get_field_interpolators_for_type( moris::PDV_Type::DENSITY )->val();
}

void tFIDerDvFunction_UTIQISTRAINENERGY
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 ) * aFIManager->get_field_interpolators_for_type( moris::PDV_Type::DENSITY )->N();
}

using namespace moris;
using namespace fem;

TEST_CASE("IQI_Strain_Energy", "[moris],[fem],[IQI_Strain_Energy]")
{
    // define an epsilon environment
    real tEpsilon = 1E-6;

    // define a perturbation relative size
    real tPerturbation = 1E-6;

    // create the properties
    std::shared_ptr<fem::Property> tPropMasterEMod = std::make_shared<fem::Property>();
    tPropMasterEMod->set_parameters({{{1.0}}});
    tPropMasterEMod->set_dv_type_list( {{ PDV_Type::DENSITY }} );
    tPropMasterEMod->set_val_function( tFIValDvFunction_UTIQISTRAINENERGY );
    tPropMasterEMod->set_dv_derivative_functions( { tFIDerDvFunction_UTIQISTRAINENERGY } );

    std::shared_ptr< fem::Property > tPropMasterNu = std::make_shared< fem::Property > ();
    tPropMasterNu->set_parameters( { {{ 0.3 }} } );
    tPropMasterNu->set_val_function( tConstValFunction_UTIQISTRAINENERGY );

    // define constitutive models
    fem::CM_Factory tCMFactory;

    std::shared_ptr< fem::Constitutive_Model > tCMMasterElastLinIso = tCMFactory.create_CM( fem::Constitutive_Type::STRUC_LIN_ISO );
    tCMMasterElastLinIso->set_dof_type_list( {{ MSI::Dof_Type::UX, MSI::Dof_Type::UY, MSI::Dof_Type::UZ }} );
    tCMMasterElastLinIso->set_property( tPropMasterEMod, "YoungsModulus" );
    tCMMasterElastLinIso->set_property( tPropMasterNu, "PoissonRatio" );
    tCMMasterElastLinIso->set_space_dim( 3 );

    // define the IWGs
    fem::IQI_Factory tIQIFactory;

    std::shared_ptr< fem::IQI > tIQI = tIQIFactory.create_IQI( fem::IQI_Type::STRAIN_ENERGY );
    tIQI->set_constitutive_model( tCMMasterElastLinIso, "Elast", mtk::Master_Slave::MASTER );
    tIQI->set_name("Strain Energy");

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
    tXHat = 10.0 * tXMatrix;

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
    tMatrix.randu( 8, 3 );
    Matrix< DDRMat > tDOFHat;
    tDOFHat = 10.0 * tMatrix;

    // create a cell of field interpolators for IWG
    moris::Cell< Field_Interpolator* > tFIs( 1 );

    // create the field interpolator
    tFIs( 0 ) = new Field_Interpolator( 3, tFIRule, &tGI, { MSI::Dof_Type::UX, MSI::Dof_Type::UY, MSI::Dof_Type::UZ } );

    // set the coefficients uHat
    tFIs( 0 )->set_coeff( tDOFHat );

    //set the evaluation point xi, tau
    tFIs( 0 )->set_space_time( tParamPoint );

    // create random dv coefficients
    arma::Mat< double > tMatrixDv;
    tMatrixDv.randu( 8, 1 );
    Matrix< DDRMat > tDvHat;
    tDvHat = 10.0 * tMatrixDv;

    // create a cell of field interpolators for IWG
    moris::Cell< Field_Interpolator* > tDvFIs( 1 );

    // create the field interpolator
    tDvFIs( 0 ) = new Field_Interpolator( 1, tFIRule, &tGI, { PDV_Type::DENSITY } );

    // set the coefficients uHat
    tDvFIs( 0 )->set_coeff( tDvHat );

    //set the evaluation point xi, tau
    tDvFIs( 0 )->set_space_time( tParamPoint );

    // create a fem set pointer
    MSI::Equation_Set * tSet = new fem::Set();

    // FEM parameter lists
    Cell<Cell<ParameterList>> tParameterList;
    tParameterList.resize( 6 );

    tParameterList( 4 ).push_back( prm::create_IQI_parameter_list() );
    tParameterList( 4 )( 0 ).set( "IQI_name",                   "Strain Energy");
    tParameterList( 4 )( 0 ).set( "IQI_type",                   static_cast< uint >( fem::IQI_Type::STRAIN_ENERGY ) );
    tParameterList( 4 )( 0 ).set( "normalization",              "design" );

    // create computation  parameter list
    tParameterList( 5 ).resize( 1 );
    tParameterList( 5 )( 0 ) = prm::create_computation_parameter_list();

    // Create FEM model
    FEM_Model tModel;
    tModel.set_parameter_list(tParameterList);
    tModel.set_requested_IQI_names({"Strain Energy"});
    tSet->set_equation_model(&tModel);

    // Create IQI
    tModel.initialize(nullptr);

    // create a GEN/MSI interface
    MSI::Design_Variable_Interface * tGENMSIInterface = new fem::FEM_Design_Variable_Interface_Proxy();
    tModel.set_design_variable_interface( tGENMSIInterface );

    // set fem set pointer for IQI
    tIQI->set_set_pointer( static_cast< fem::Set* >( tSet ) );

    // set size for the set mUniqueDofTypeList
    tIQI->mSet->mUniqueDofTypeList.resize( 4, MSI::Dof_Type::END_ENUM );

    // set size for the set mUniqueDvTypeList
    tIQI->mSet->mUniqueDvTypeList.resize( 4, PDV_Type::UNDEFINED );

    // set size and populate the set dof type map
    tIQI->mSet->mUniqueDofTypeMap.set_size( static_cast< int >( MSI::Dof_Type::END_ENUM ) + 1, 1, -1 );
    tIQI->mSet->mUniqueDofTypeMap( static_cast< int >( MSI::Dof_Type::UX ) ) = 0;

    // set size and populate the set master dof type map
    tIQI->mSet->mMasterDofTypeMap.set_size( static_cast< int >(MSI::Dof_Type::END_ENUM ) + 1, 1, -1 );
    tIQI->mSet->mMasterDofTypeMap( static_cast< int >( MSI::Dof_Type::UX ) ) = 0;

    // set size and populate the set dof type map
    tIQI->mSet->mUniqueDvTypeMap.set_size( static_cast< int >( PDV_Type::UNDEFINED ) + 1, 1, -1 );
    tIQI->mSet->mUniqueDvTypeMap( static_cast< int >( PDV_Type::DENSITY ) ) = 0;

    // set size and populate the set master dof type map
    tIQI->mSet->mMasterDvTypeMap.set_size( static_cast< int >( PDV_Type::UNDEFINED ) + 1, 1, -1 );
    tIQI->mSet->mMasterDvTypeMap( static_cast< int >( PDV_Type::DENSITY ) ) = 0;

    // set size and populate residual assembly map
    tIQI->mSet->mResDofAssemblyMap.resize( 1 );
    tIQI->mSet->mResDofAssemblyMap( 0 ) = { { 0, 23 } };

    // set size and populate jacobian assembly map
    tIQI->mSet->mJacDofAssemblyMap.resize( 1 );
    tIQI->mSet->mJacDofAssemblyMap( 0 ) = { { 0, 23 } };

    // set size and fill the set dv assembly map
    tIQI->mSet->mPdvMatAssemblyMap.resize( 1 );
    tIQI->mSet->mPdvMatAssemblyMap( 0 ) = { { 0, 7 } };

    // set size and init the set residual and jacobian
    tIQI->mSet->mResidual.resize( 1 );
    tIQI->mSet->mResidual( 0 ).set_size( 24, 1, 0.0 );

    // set size and init the set residual and jacobian
    tIQI->mSet->mQI.resize( 1 );
    tIQI->mSet->mQI( 0 ).set_size( 1, 1, 0.0 );

    // populate the requested master dof type
    tIQI->mRequestedMasterGlobalDofTypes = {{ MSI::Dof_Type::UX }};

    moris::Cell< moris::Cell< enum fem::IQI_Type > > tRequestedIQITypes( 1 );
    tRequestedIQITypes( 0 ).resize( 1, fem::IQI_Type::STRAIN_ENERGY );

    tSet->create_requested_IQI_type_map();

    // create a field interpolator manager
    moris::Cell< moris::Cell< enum MSI::Dof_Type > > tDummy;
    Field_Interpolator_Manager tFIManager( tDummy, tSet );

    // populate the field interpolator manager
    tFIManager.mFI   = tFIs;
    tFIManager.mDvFI = tDvFIs;
    tFIManager.mIPGeometryInterpolator = &tGI;
    tFIManager.mIGGeometryInterpolator = &tGI;

    // set the interpolator manager to the set
    tIQI->mSet->mMasterFIManager = &tFIManager;

    // set IWG field interpolator manager
    tIQI->set_field_interpolator_manager( &tFIManager );

    // check evaluation of the quantity of interest
    //------------------------------------------------------------------------------
    // evaluate the quantity of interest
    tModel.initialize_IQIs();
    tModel.compute_IQIs();
    CHECK(tModel.get_IQI_values()(0)(0) = 1.0);

    Matrix< DDRMat > tdQIdu;
    Matrix< DDRMat > tdQIduFD;
    bool tCheckdQIdu = tIQI->check_dQIdu_FD( 1.0,
                                             tPerturbation,
                                             tEpsilon,
                                             tdQIdu,
                                             tdQIduFD );
    CHECK( tCheckdQIdu );

} /*END_TEST_CASE*/
