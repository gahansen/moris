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
#include "cl_FEM_Stabilization_Parameter.hpp"
#include "cl_FEM_CM_Factory.hpp"
#include "cl_FEM_IWG_Factory.hpp"
#include "cl_FEM_SP_Factory.hpp"

void tConstValFunction_UTIWGGGLSDIFFBULK
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 );
}

void tGeoValFunction_UTIWGGGLSDIFFBULK
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 ) * aFIManager->get_IP_geometry_interpolator()->valx()( 0 );
}

void tFIValFunction_UTIWGGGLSDIFFBULK
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 ) * aFIManager->get_field_interpolators_for_type( moris::MSI::Dof_Type::TEMP )->val();
}

void tFIDerFunction_UTIWGGGLSDIFFBULK
( moris::Matrix< moris::DDRMat >                 & aPropMatrix,
  moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
  moris::fem::Field_Interpolator_Manager         * aFIManager )
{
    aPropMatrix = aParameters( 0 ) * aFIManager->get_field_interpolators_for_type( moris::MSI::Dof_Type::TEMP )->N();
}


using namespace moris;
using namespace fem;


TEST_CASE( "IWG_GGLS_Diffusion_Phase_Change", "[moris],[fem],[IWG_GGLS_Diffusion_Phase_Change]" )
{
    // define an epsilon environment
    real tEpsilon = 1E-6;

    // define a perturbation relative size
    real tPerturbation = 1E-6;

    // create the properties ------------------------------------------------------------------- //

    // conductivity
    std::shared_ptr< fem::Property > tPropMasterConductivity = std::make_shared< fem::Property >();
    tPropMasterConductivity->set_parameters( {{{ 1.0}}, {{1.0 }}} );
    tPropMasterConductivity->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tPropMasterConductivity->set_val_function( tConstValFunction_UTIWGGGLSDIFFBULK );

    // density
    std::shared_ptr< fem::Property > tPropMasterDensity = std::make_shared< fem::Property >();
    tPropMasterDensity->set_parameters( {{{ 1.0}}} );
    tPropMasterDensity->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tPropMasterDensity->set_val_function( tConstValFunction_UTIWGGGLSDIFFBULK );

    // heat capacity
    std::shared_ptr< fem::Property > tPropMasterHeatCapacity = std::make_shared< fem::Property >();
    tPropMasterHeatCapacity->set_parameters( {{{ 1.0}}} );
    tPropMasterHeatCapacity->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tPropMasterHeatCapacity->set_val_function( tConstValFunction_UTIWGGGLSDIFFBULK );

    // latent heat
    std::shared_ptr< fem::Property > tPropMasterLatentHeat = std::make_shared< fem::Property >();
    tPropMasterLatentHeat->set_parameters( {{{ 100.0}}} );
    tPropMasterLatentHeat->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tPropMasterLatentHeat->set_val_function( tConstValFunction_UTIWGGGLSDIFFBULK );

    // lower phase change temp
    std::shared_ptr< fem::Property > tPropMasterTlower = std::make_shared< fem::Property >();
    tPropMasterTlower->set_parameters( {{{ 1.0 }}} );
    tPropMasterTlower->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tPropMasterTlower->set_val_function( tConstValFunction_UTIWGGGLSDIFFBULK );

    // upper phase change temp
    std::shared_ptr< fem::Property > tPropMasterTupper = std::make_shared< fem::Property >();
    tPropMasterTupper->set_parameters( {{{ 2.0 }}} );
    tPropMasterTupper->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tPropMasterTupper->set_val_function( tConstValFunction_UTIWGGGLSDIFFBULK );

    // phase change constant
    std::shared_ptr< fem::Property > tPropMasterPCconst = std::make_shared< fem::Property >();
    tPropMasterPCconst->set_parameters( {{{ 0.0 }}} );
    tPropMasterPCconst->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tPropMasterPCconst->set_val_function( tConstValFunction_UTIWGGGLSDIFFBULK );

    // temperature load
    std::shared_ptr< fem::Property > tPropMasterBodyLoad = nullptr;


    // define constitutive model ---------------------------------------------------------------- //
    fem::CM_Factory tCMFactory;

    std::shared_ptr< fem::Constitutive_Model > tCMMasterDiffLinIsoPC = tCMFactory.create_CM( fem::Constitutive_Type::DIFF_LIN_ISO_PC );
    tCMMasterDiffLinIsoPC->set_dof_type_list( {{ MSI::Dof_Type::TEMP }} );
    tCMMasterDiffLinIsoPC->set_property( tPropMasterConductivity, "Conductivity" );
    tCMMasterDiffLinIsoPC->set_property( tPropMasterDensity     , "Density" );
    tCMMasterDiffLinIsoPC->set_property( tPropMasterHeatCapacity, "Heat_Capacity" );
    tCMMasterDiffLinIsoPC->set_property( tPropMasterLatentHeat  , "Latent_Heat" );
    tCMMasterDiffLinIsoPC->set_property( tPropMasterTlower      , "Lower_PC_Temp" );
    tCMMasterDiffLinIsoPC->set_property( tPropMasterTupper      , "Upper_PC_Temp" );
    tCMMasterDiffLinIsoPC->set_property( tPropMasterPCconst     , "Phase_Change_Const" );
    tCMMasterDiffLinIsoPC->set_space_dim( 3 );

    // define stabilization parameter ----------------------------------------------------------- //
    fem::SP_Factory tSPFactory;

    std::shared_ptr< fem::Stabilization_Parameter > tSPGGLSParam
    = tSPFactory.create_SP( fem::Stabilization_Type::GGLS_DIFFUSION_PC );
    tSPGGLSParam->set_dof_type_list( {{ MSI::Dof_Type::TEMP }}, mtk::Master_Slave::MASTER );
    tSPGGLSParam->set_parameters( { {{ 1.0 }} });
    tSPGGLSParam->set_property( tPropMasterConductivity, "Conductivity", mtk::Master_Slave::MASTER );
    tSPGGLSParam->set_property( tPropMasterDensity, "Density", mtk::Master_Slave::MASTER );
    tSPGGLSParam->set_property( tPropMasterHeatCapacity, "Heat_Capacity", mtk::Master_Slave::MASTER );


    // define the IWGs
    fem::IWG_Factory tIWGFactory;

    std::shared_ptr< fem::IWG > tIWG = tIWGFactory.create_IWG( fem::IWG_Type::SPATIALDIFF_GGLS_PC );
    tIWG->set_residual_dof_type( { MSI::Dof_Type::TEMP } );
    tIWG->set_dof_type_list( {{ MSI::Dof_Type::TEMP }}, mtk::Master_Slave::MASTER );
    tIWG->set_constitutive_model( tCMMasterDiffLinIsoPC, "Diffusion_Phase_Change", mtk::Master_Slave::MASTER );
    tIWG->set_stabilization_parameter( tSPGGLSParam, "GGLS_Param");
    tIWG->set_property( tPropMasterBodyLoad, "Load", mtk::Master_Slave::MASTER );



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

