#include <string>
#include <catch.hpp>
#include <memory>
#include "assert.hpp"

#define protected public
#define private public
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
#include "cl_FEM_CM_Factory.hpp"
#include "cl_FEM_SP_Factory.hpp"
#include "cl_FEM_IWG_Factory.hpp"
#include "FEM_Test_Proxy/cl_FEM_Inputs_for_NS_Compressible_UT.cpp"

#include "fn_trans.hpp"
#include "fn_FEM_Check.hpp"

using namespace moris;
using namespace fem;

//------------------------------------------------------------------------------

TEST_CASE("IWG_Compressible_NS_Density_Bulk_Ideal_Analytic",
          "[IWG_Compressible_NS_Density_Bulk_Ideal_Analytic]")
{
        // define an epsilon environment
        real tEpsilon = 1.0E-4;

        // dof type list
        moris::Cell<MSI::Dof_Type> tVelocityDof = {MSI::Dof_Type::VX};
        moris::Cell<MSI::Dof_Type> tTempDof     = {MSI::Dof_Type::TEMP};

        moris::Cell<moris::Cell<MSI::Dof_Type>> tDensityDof = { { MSI::Dof_Type::RHO } };
        moris::Cell<moris::Cell<MSI::Dof_Type>> tDofTypes   = {tDensityDof( 0 ), tVelocityDof, tTempDof};

        // init IWG
        //------------------------------------------------------------------------------
        // create the properties

        // dynamic viscosity
        std::shared_ptr<fem::Property> tPropViscosity = std::make_shared<fem::Property>();
        tPropViscosity->set_parameters({{{1.716e-5}}});
        tPropViscosity->set_val_function(tConstValFunc);

        // isochoric heat capacity
        std::shared_ptr<fem::Property> tPropHeatCapacity = std::make_shared<fem::Property>();
        tPropHeatCapacity->set_parameters({{{0.718e3}}});
        tPropHeatCapacity->set_val_function(tConstValFunc);

        // specific gas constant
        std::shared_ptr<fem::Property> tPropGasConstant = std::make_shared<fem::Property>();
        tPropGasConstant->set_parameters({{{287.058}}});
        tPropGasConstant->set_val_function(tConstValFunc);

        // thermal conductivity
        std::shared_ptr<fem::Property> tPropConductivity = std::make_shared<fem::Property>();
        tPropConductivity->set_parameters({{{24.35e-3}}});
        tPropConductivity->set_val_function(tConstValFunc);

        // define constitutive model and assign properties
        fem::CM_Factory tCMFactory;

        std::shared_ptr<fem::Constitutive_Model> tCMMasterFluid =
            tCMFactory.create_CM(fem::Constitutive_Type::FLUID_COMPRESSIBLE_IDEAL);
        tCMMasterFluid->set_dof_type_list({tDensityDof( 0 ), tVelocityDof, tTempDof});
        tCMMasterFluid->set_property(tPropViscosity, "DynamicViscosity");
        tCMMasterFluid->set_property(tPropHeatCapacity, "IsochoricHeatCapacity");
        tCMMasterFluid->set_property(tPropGasConstant, "SpecificGasConstant");
        tCMMasterFluid->set_property(tPropConductivity, "ThermalConductivity");

        // define the IWGs
        fem::IWG_Factory tIWGFactory;

        std::shared_ptr<fem::IWG> tIWG =
            tIWGFactory.create_IWG(fem::IWG_Type::COMPRESSIBLE_NS_DENSITY_BULK);
        tIWG->set_residual_dof_type(tDensityDof);
        tIWG->set_dof_type_list(tDofTypes, mtk::Master_Slave::MASTER);
        tIWG->set_constitutive_model(tCMMasterFluid, "Fluid");

        //------------------------------------------------------------------------------
        // set a fem set pointer

        MSI::Equation_Set *tSet = new fem::Set();
        static_cast<fem::Set *>(tSet)->set_set_type(fem::Element_Type::BULK);
        tIWG->set_set_pointer(static_cast<fem::Set *>(tSet));

        // set size for the set EqnObjDofTypeList
        tIWG->mSet->mUniqueDofTypeList.resize(100, MSI::Dof_Type::END_ENUM);

        // set size and populate the set dof type map
        tIWG->mSet->mUniqueDofTypeMap.set_size(static_cast<int>(MSI::Dof_Type::END_ENUM) + 1, 1, -1);
        tIWG->mSet->mUniqueDofTypeMap(static_cast<int>(MSI::Dof_Type::RHO)) = 0;
        tIWG->mSet->mUniqueDofTypeMap(static_cast<int>(MSI::Dof_Type::VX)) = 1;
        tIWG->mSet->mUniqueDofTypeMap(static_cast<int>(MSI::Dof_Type::TEMP)) = 2;

        // set size and populate the set master dof type map
        tIWG->mSet->mMasterDofTypeMap.set_size(static_cast<int>(MSI::Dof_Type::END_ENUM) + 1, 1, -1);
        tIWG->mSet->mMasterDofTypeMap(static_cast<int>(MSI::Dof_Type::RHO)) = 0;
        tIWG->mSet->mMasterDofTypeMap(static_cast<int>(MSI::Dof_Type::VX)) = 1;
        tIWG->mSet->mMasterDofTypeMap(static_cast<int>(MSI::Dof_Type::TEMP)) = 2;

        // only use 2D
        uint iSpaceDim = 2;

        // set geometry type
        mtk::Geometry_Type tGeometryType = mtk::Geometry_Type::QUAD;

        // set velocity dof types
        tVelocityDof = {MSI::Dof_Type::VX, MSI::Dof_Type::VY};

        // set space dimension to CM
        tCMMasterFluid->set_space_dim(2);

        // create an interpolation order
        mtk::Interpolation_Order tGIInterpolationOrder = mtk::Interpolation_Order::LINEAR;

        //------------------------------------------------------------------------------
        // space and time geometry interpolators
        // create a space geometry interpolation rule
        mtk::Interpolation_Rule tGIRule(tGeometryType,
                                   mtk::Interpolation_Type::LAGRANGE,
                                   tGIInterpolationOrder,
                                   mtk::Interpolation_Type::LAGRANGE,
                                   mtk::Interpolation_Order::LINEAR);

        // create a space time geometry interpolator
        Geometry_Interpolator tGI = Geometry_Interpolator(tGIRule);

        // create time coeff tHat
        Matrix<DDRMat> tTHat = {{0.0}, {0.4}};
        Matrix<DDRMat> tXHat = {{0.0, 0.0}, {0.3, 0.0}, {0.3, 1.0}, {0.0, 1.0}};

        // set the coefficients xHat, tHat
        tGI.set_coeff(tXHat, tTHat);

        //------------------------------------------------------------------------------
        // integration points
        // get an integration order
        mtk::Integration_Order tIntegrationOrder = mtk::Integration_Order::QUAD_2x2;

        // create an integration rule
        mtk::Integration_Rule tIntegrationRule(
            tGeometryType,
            mtk::Integration_Type::GAUSS,
            tIntegrationOrder,
            mtk::Geometry_Type::LINE,
            mtk::Integration_Type::GAUSS,
            mtk::Integration_Order::BAR_2);

        // create an integrator
        mtk::Integrator tIntegrator(tIntegrationRule);

        // get integration points
        Matrix<DDRMat> tIntegPoints;
        tIntegrator.get_points(tIntegPoints);

        //------------------------------------------------------------------------------
        // field interpolators
        // create an interpolation order
        mtk::Interpolation_Order tInterpolationOrder = mtk::Interpolation_Order::LINEAR;

        // number of dofs for interpolation order
        uint tNumCoeff = 8;

        // get number of dof per type
        int tNumDofRho = tNumCoeff;
        int tNumDofVel = tNumCoeff * iSpaceDim;
        int tNumDofTemp = tNumCoeff;
        int tTotalNumDof = tNumDofRho + tNumDofVel + tNumDofTemp;

        //create a space time interpolation rule
        mtk::Interpolation_Rule tFIRule(
            tGeometryType,
            mtk::Interpolation_Type::LAGRANGE,
            tInterpolationOrder,
            mtk::Interpolation_Type::LAGRANGE,
            mtk::Interpolation_Order::LINEAR);

        // fill coefficients for master FI
        Matrix<DDRMat> tMasterDOFHatRho =
            {{1.0, 1.2, 1.2, 1.0,
              1.1, 1.4, 1.4, 1.1}};
        tMasterDOFHatRho = trans(tMasterDOFHatRho);
        Matrix<DDRMat> tMasterDOFHatVel =
            {{0.0, 0.0},
             {1.1, 0.0},
             {1.1, 0.0},
             {0.0, 0.0},
             {2.2, 0.0},
             {4.3, 0.0},
             {4.3, 0.0},
             {2.2, 0.0}};
        Matrix<DDRMat> tMasterDOFHatTemp =
            {{273.3, 284.4, 284.4, 273.3,
              279.9, 297.7, 297.7, 279.9}};
        tMasterDOFHatTemp = trans(tMasterDOFHatTemp);

        // create a cell of field interpolators for IWG
        Cell<Field_Interpolator *> tMasterFIs(tDofTypes.size());

        // create the field interpolator density
        tMasterFIs(0) = new Field_Interpolator(1, tFIRule, &tGI, tDensityDof( 0 ));
        tMasterFIs(0)->set_coeff(tMasterDOFHatRho);

        // create the field interpolator velocity
        tMasterFIs(1) = new Field_Interpolator(iSpaceDim, tFIRule, &tGI, tVelocityDof);
        tMasterFIs(1)->set_coeff(tMasterDOFHatVel);

        // create the field interpolator pressure
        tMasterFIs(2) = new Field_Interpolator(1, tFIRule, &tGI, tTempDof);
        tMasterFIs(2)->set_coeff(tMasterDOFHatTemp);

        // set size and fill the set residual assembly map
        tIWG->mSet->mResDofAssemblyMap.resize(tDofTypes.size());
        tIWG->mSet->mResDofAssemblyMap(0) = {{0, tNumDofRho - 1}};
        tIWG->mSet->mResDofAssemblyMap(1) = {{tNumDofRho, tNumDofRho + tNumDofVel - 1}};
        tIWG->mSet->mResDofAssemblyMap(2) = {{tNumDofRho + tNumDofVel, tTotalNumDof - 1}};

        // set size and fill the set jacobian assembly map
        Matrix<DDSMat> tJacAssembly = {
            {0, tNumDofRho - 1},
            {tNumDofRho, tNumDofRho + tNumDofVel - 1},
            {tNumDofRho + tNumDofVel, tTotalNumDof - 1}};
        tIWG->mSet->mJacDofAssemblyMap.resize(tDofTypes.size());
        tIWG->mSet->mJacDofAssemblyMap(0) = tJacAssembly;
        tIWG->mSet->mJacDofAssemblyMap(1) = tJacAssembly;
        tIWG->mSet->mJacDofAssemblyMap(2) = tJacAssembly;

        // set size and init the set residual and jacobian
        tIWG->mSet->mResidual.resize(1);
        tIWG->mSet->mResidual(0).set_size(
            tTotalNumDof,
            1,
            0.0);
        tIWG->mSet->mJacobian.set_size(
            tTotalNumDof,
            tTotalNumDof,
            0.0);

        // build global dof type list
        tIWG->get_global_dof_type_list();

        // populate the requested master dof type
        tIWG->mRequestedMasterGlobalDofTypes = tDofTypes;

        // create a field interpolator manager
        moris::Cell<moris::Cell<enum PDV_Type>> tDummyDv;
        moris::Cell< moris::Cell< enum mtk::Field_Type > > tDummyField;
        Field_Interpolator_Manager tFIManager(tDofTypes, tDummyDv, tDummyField, tSet);

        // populate the field interpolator manager
        tFIManager.mFI = tMasterFIs;
        tFIManager.mIPGeometryInterpolator = &tGI;
        tFIManager.mIGGeometryInterpolator = &tGI;

        // set the interpolator manager to the set
        tIWG->mSet->mMasterFIManager = &tFIManager;

        // set IWG field interpolator manager
        tIWG->set_field_interpolator_manager(&tFIManager);

        // set the interpolator manager to the set
        tCMMasterFluid->mSet->mMasterFIManager = &tFIManager;

        // set IWG field interpolator manager
        tCMMasterFluid->set_field_interpolator_manager(&tFIManager);

        // init the jacobian for IWG
        Matrix<DDRMat> tResidual;
        Matrix<DDRMat> tJacobian;

        // loop over integration points
        uint tNumGPs = tIntegPoints.n_cols();
        for (uint iGP = 0; iGP < tNumGPs; iGP++)
        {
                // output for debugging
                //std::cout << "-------------------------------------------------------------------\n" << std::flush;
                //std::cout << "Looping over Gauss points. Current GP-#: " << iGP << "\n\n" << std::flush;

                // reset CM evaluation flags
                tCMMasterFluid->reset_eval_flags();

                // reset IWG evaluation flags
                tIWG->reset_eval_flags();

                // create evaluation point xi, tau
                Matrix<DDRMat> tParamPoint = tIntegPoints.get_column(iGP);

                // set integration point
                tCMMasterFluid->mSet->mMasterFIManager->set_space_time(tParamPoint);
                tIWG->mSet->mMasterFIManager->set_space_time(tParamPoint);

                // reset residual and jacobian
                tIWG->mSet->mResidual(0).fill(0.0);
                tIWG->mSet->mJacobian.fill(0.0);

                // compute residual & jacobian
                tIWG->compute_residual(0.15 * 0.2);
                tIWG->compute_jacobian(0.15 * 0.2);

                // init the jacobian for IWG
                if (iGP == 0)
                {
                        tResidual = tIWG->mSet->mResidual(0);
                        tJacobian = tIWG->mSet->mJacobian;
                }
                else
                {
                        tResidual += tIWG->mSet->mResidual(0);
                        tJacobian += tIWG->mSet->mJacobian;
                }

                // debug: print matrices
                //print( trans( tResidual ), "tResidual" );
                //print( tJacobian, "tJacobian" );
        }

        // Analytical residual from Matlab code
        Matrix<DDRMat> tResidualAnalytical = {{+3.537e-01, -3.312e-01, -3.312e-01, +3.537e-01, +5.864e-01, -5.639e-01, -5.639e-01, +5.864e-01,
                                               +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00,
                                               +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00,
                                               +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00, +0.000e+00}};

        tResidualAnalytical = trans(tResidualAnalytical);

        // check jacobian against analytical solution
        bool tCheckResidual = fem::check(tResidual, tResidualAnalytical, tEpsilon);
        REQUIRE(tCheckResidual);

        // clean up
        tMasterFIs.clear();

} /*END_TEST_CASE*/

//------------------------------------------------------------------------------

TEST_CASE("IWG_Compressible_NS_Density_Bulk_VdW_Analytic",
          "[IWG_Compressible_NS_Density_Bulk_VdW_Analytic]")
{
        // define an epsilon environment
        real tEpsilon = 1.0E-4;

        // dof type list
        moris::Cell<MSI::Dof_Type> tVelocityDof = {MSI::Dof_Type::VX};
        moris::Cell<MSI::Dof_Type> tTempDof     = {MSI::Dof_Type::TEMP};

        moris::Cell<moris::Cell<MSI::Dof_Type>> tDensityDof = { { MSI::Dof_Type::RHO } };
        moris::Cell<moris::Cell<MSI::Dof_Type>> tDofTypes   = {tDensityDof( 0 ), tVelocityDof, tTempDof};

        // init IWG
        //------------------------------------------------------------------------------
        // create the properties

        // dynamic viscosity
        std::shared_ptr<fem::Property> tPropViscosity = std::make_shared<fem::Property>();
        tPropViscosity->set_parameters({{{9.12e-6}}});
        tPropViscosity->set_val_function(tConstValFunc);

        // isochoric heat capacity
        std::shared_ptr<fem::Property> tPropHeatCapacity = std::make_shared<fem::Property>();
        tPropHeatCapacity->set_parameters({{{0.149e3}}});
        tPropHeatCapacity->set_val_function(tConstValFunc);

        // specific gas constant
        std::shared_ptr<fem::Property> tPropGasConstant = std::make_shared<fem::Property>();
        tPropGasConstant->set_parameters({{{276.488}}});
        tPropGasConstant->set_val_function(tConstValFunc);

        // thermal conductivity
        std::shared_ptr<fem::Property> tPropConductivity = std::make_shared<fem::Property>();
        tPropConductivity->set_parameters({{{20.01e-3}}});
        tPropConductivity->set_val_function(tConstValFunc);

        // Capillariy Constant
        std::shared_ptr<fem::Property> tPropCapillarity = std::make_shared<fem::Property>();
        tPropCapillarity->set_parameters({{{6.0e-11}}});
        tPropCapillarity->set_val_function(tConstValFunc);

        // First VdW constant
        std::shared_ptr<fem::Property> tPropFirstVdWconst = std::make_shared<fem::Property>();
        tPropFirstVdWconst->set_parameters({{{616.01}}});
        tPropFirstVdWconst->set_val_function(tConstValFunc);

        // Second VdW constant
        std::shared_ptr<fem::Property> tPropSecondVdWconst = std::make_shared<fem::Property>();
        tPropSecondVdWconst->set_parameters({{{454.54545}}});
        tPropSecondVdWconst->set_val_function(tConstValFunc);

        // define constitutive model and assign properties
        fem::CM_Factory tCMFactory;

        std::shared_ptr<fem::Constitutive_Model> tCMMasterFluid =
            tCMFactory.create_CM(fem::Constitutive_Type::FLUID_COMPRESSIBLE_VDW);
        tCMMasterFluid->set_dof_type_list({tDensityDof( 0 ), tVelocityDof, tTempDof});
        tCMMasterFluid->set_property(tPropViscosity, "DynamicViscosity");
        tCMMasterFluid->set_property(tPropHeatCapacity, "IsochoricHeatCapacity");
        tCMMasterFluid->set_property(tPropGasConstant, "SpecificGasConstant");
        tCMMasterFluid->set_property(tPropConductivity, "ThermalConductivity");
        tCMMasterFluid->set_property(tPropCapillarity, "CapillarityCoefficient");
        tCMMasterFluid->set_property(tPropFirstVdWconst, "FirstVdWconstant");
        tCMMasterFluid->set_property(tPropSecondVdWconst, "SecondVdWconstant");

        // define the IWGs
        fem::IWG_Factory tIWGFactory;

        std::shared_ptr<fem::IWG> tIWG =
            tIWGFactory.create_IWG(fem::IWG_Type::COMPRESSIBLE_NS_DENSITY_BULK);
        tIWG->set_residual_dof_type(tDensityDof);
        tIWG->set_dof_type_list(tDofTypes, mtk::Master_Slave::MASTER);
        tIWG->set_constitutive_model(tCMMasterFluid, "Fluid");

        //------------------------------------------------------------------------------
        // set a fem set pointer

        MSI::Equation_Set *tSet = new fem::Set();
        static_cast<fem::Set *>(tSet)->set_set_type(fem::Element_Type::BULK);
        tIWG->set_set_pointer(static_cast<fem::Set *>(tSet));

        // set size for the set EqnObjDofTypeList
        tIWG->mSet->mUniqueDofTypeList.resize(100, MSI::Dof_Type::END_ENUM);

        // set size and populate the set dof type map
        tIWG->mSet->mUniqueDofTypeMap.set_size(static_cast<int>(MSI::Dof_Type::END_ENUM) + 1, 1, -1);
        tIWG->mSet->mUniqueDofTypeMap(static_cast<int>(MSI::Dof_Type::RHO)) = 0;
        tIWG->mSet->mUniqueDofTypeMap(static_cast<int>(MSI::Dof_Type::VX)) = 1;
        tIWG->mSet->mUniqueDofTypeMap(static_cast<int>(MSI::Dof_Type::TEMP)) = 2;

        // set size and populate the set master dof type map
        tIWG->mSet->mMasterDofTypeMap.set_size(static_cast<int>(MSI::Dof_Type::END_ENUM) + 1, 1, -1);
        tIWG->mSet->mMasterDofTypeMap(static_cast<int>(MSI::Dof_Type::RHO)) = 0;
        tIWG->mSet->mMasterDofTypeMap(static_cast<int>(MSI::Dof_Type::VX)) = 1;
        tIWG->mSet->mMasterDofTypeMap(static_cast<int>(MSI::Dof_Type::TEMP)) = 2;

        // only use 2D
        uint iSpaceDim = 2;

        // set geometry type
        mtk::Geometry_Type tGeometryType = mtk::Geometry_Type::QUAD;

        // set velocity dof types
        tVelocityDof = {MSI::Dof_Type::VX, MSI::Dof_Type::VY};

        // set space dimension to CM
        tCMMasterFluid->set_space_dim(2);

        // create an interpolation order
        mtk::Interpolation_Order tGIInterpolationOrder = mtk::Interpolation_Order::LINEAR;

        //------------------------------------------------------------------------------
        // space and time geometry interpolators
        // create a space geometry interpolation rule
        mtk::Interpolation_Rule tGIRule(tGeometryType,
                                   mtk::Interpolation_Type::LAGRANGE,
                                   tGIInterpolationOrder,
                                   mtk::Interpolation_Type::LAGRANGE,
                                   mtk::Interpolation_Order::LINEAR);

        // create a space time geometry interpolator
        Geometry_Interpolator tGI = Geometry_Interpolator(tGIRule);

        // create time coeff tHat
        Matrix<DDRMat> tTHat = {{0.0}, {0.4}};
        Matrix<DDRMat> tXHat = {{0.0, 0.0}, {0.3, 0.0}, {0.3, 1.0}, {0.0, 1.0}};

        // set the coefficients xHat, tHat
        tGI.set_coeff(tXHat, tTHat);

        //------------------------------------------------------------------------------
        // integration points
        // get an integration order
        mtk::Integration_Order tIntegrationOrder = mtk::Integration_Order::QUAD_3x3;

        // create an integration rule
        mtk::Integration_Rule tIntegrationRule(
            tGeometryType,
            mtk::Integration_Type::GAUSS,
            tIntegrationOrder,
            mtk::Geometry_Type::LINE,
            mtk::Integration_Type::GAUSS,
            mtk::Integration_Order::BAR_3);

        // create an integrator
        mtk::Integrator tIntegrator(tIntegrationRule);

        // get integration points
        Matrix<DDRMat> tIntegPoints;
        Matrix<DDRMat> tIntegWeights;
        tIntegrator.get_points(tIntegPoints);
        tIntegrator.get_weights(tIntegWeights);

        //------------------------------------------------------------------------------
        // field interpolators
        // create an interpolation order
        mtk::Interpolation_Order tInterpolationOrder = mtk::Interpolation_Order::QUADRATIC;

        // number of dofs for interpolation order
        uint tNumCoeff = 18;

        // get number of dof per type
        int tNumDofRho = tNumCoeff;
        int tNumDofVel = tNumCoeff * iSpaceDim;
        int tNumDofTemp = tNumCoeff;
        int tTotalNumDof = tNumDofRho + tNumDofVel + tNumDofTemp;

        //create a space time interpolation rule
        mtk::Interpolation_Rule tFIRule(
            tGeometryType,
            mtk::Interpolation_Type::LAGRANGE,
            tInterpolationOrder,
            mtk::Interpolation_Type::LAGRANGE,
            mtk::Interpolation_Order::LINEAR);

        // fill coefficients for master FI
        Matrix<DDRMat> tMasterDOFHatRho =
            {{101.0, 122.2, 122.2, 101.0, 117.7, 122.2, 117.7, 101.0, 117.7,
              111.1, 144.4, 144.4, 111.1, 133.3, 144.4, 133.3, 111.1, 133.3}};
        tMasterDOFHatRho = trans(tMasterDOFHatRho);

        Matrix<DDRMat> tMasterDOFHatVel =
            {{0.0, 1.1, 1.1, 0.0, 0.6, 1.1, 0.6, 0.0, 0.6,
              2.2, 4.3, 4.3, 2.2, 3.7, 4.3, 3.7, 2.2, 3.7},
             {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
              0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};
        tMasterDOFHatVel = trans(tMasterDOFHatVel);

        Matrix<DDRMat> tMasterDOFHatTemp =
            {{273.3, 284.4, 284.4, 273.3, 278.8, 284.4, 278.8, 273.3, 278.8,
              279.9, 297.7, 297.7, 279.9, 287.7, 297.7, 287.7, 279.9, 287.7}};
        tMasterDOFHatTemp = trans(tMasterDOFHatTemp);

        // create a cell of field interpolators for IWG
        Cell<Field_Interpolator *> tMasterFIs(tDofTypes.size());

        // create the field interpolator density
        tMasterFIs(0) = new Field_Interpolator(1, tFIRule, &tGI, tDensityDof( 0 ));
        tMasterFIs(0)->set_coeff(tMasterDOFHatRho);

        // create the field interpolator velocity
        tMasterFIs(1) = new Field_Interpolator(iSpaceDim, tFIRule, &tGI, tVelocityDof);
        tMasterFIs(1)->set_coeff(tMasterDOFHatVel);

        // create the field interpolator pressure
        tMasterFIs(2) = new Field_Interpolator(1, tFIRule, &tGI, tTempDof);
        tMasterFIs(2)->set_coeff(tMasterDOFHatTemp);

        // set size and fill the set residual assembly map
        tIWG->mSet->mResDofAssemblyMap.resize(tDofTypes.size());
        tIWG->mSet->mResDofAssemblyMap(0) = {{0, tNumDofRho - 1}};
        tIWG->mSet->mResDofAssemblyMap(1) = {{tNumDofRho, tNumDofRho + tNumDofVel - 1}};
        tIWG->mSet->mResDofAssemblyMap(2) = {{tNumDofRho + tNumDofVel, tTotalNumDof - 1}};

        // set size and fill the set jacobian assembly map
        Matrix<DDSMat> tJacAssembly = {
            {0, tNumDofRho - 1},
            {tNumDofRho, tNumDofRho + tNumDofVel - 1},
            {tNumDofRho + tNumDofVel, tTotalNumDof - 1}};
        tIWG->mSet->mJacDofAssemblyMap.resize(tDofTypes.size());
        tIWG->mSet->mJacDofAssemblyMap(0) = tJacAssembly;
        tIWG->mSet->mJacDofAssemblyMap(1) = tJacAssembly;
        tIWG->mSet->mJacDofAssemblyMap(2) = tJacAssembly;

        // set size and init the set residual and jacobian
        tIWG->mSet->mResidual.resize(1);
        tIWG->mSet->mResidual(0).set_size(
            tTotalNumDof,
            1,
            0.0);
        tIWG->mSet->mJacobian.set_size(
            tTotalNumDof,
            tTotalNumDof,
            0.0);

        // build global dof type list
        tIWG->get_global_dof_type_list();

        // populate the requested master dof type
        tIWG->mRequestedMasterGlobalDofTypes = tDofTypes;

        // create a field interpolator manager
        moris::Cell<moris::Cell<enum PDV_Type>> tDummyDv;
        moris::Cell< moris::Cell< enum mtk::Field_Type > > tDummyField;
        Field_Interpolator_Manager tFIManager(tDofTypes, tDummyDv, tDummyField, tSet);

        // populate the field interpolator manager
        tFIManager.mFI = tMasterFIs;
        tFIManager.mIPGeometryInterpolator = &tGI;
        tFIManager.mIGGeometryInterpolator = &tGI;

        // set the interpolator manager to the set
        tIWG->mSet->mMasterFIManager = &tFIManager;

        // set IWG field interpolator manager
        tIWG->set_field_interpolator_manager(&tFIManager);

        // set the interpolator manager to the set
        tCMMasterFluid->mSet->mMasterFIManager = &tFIManager;

        // set IWG field interpolator manager
        tCMMasterFluid->set_field_interpolator_manager(&tFIManager);

        // init the jacobian for IWG
        Matrix<DDRMat> tResidual;
        Matrix<DDRMat> tJacobian;

        // list of integration weights
        Matrix<DDRMat> tGaussWeights = {{}};

        // loop over integration points
        uint tNumGPs = tIntegPoints.n_cols();
        for (uint iGP = 0; iGP < tNumGPs; iGP++)
        {
                // output for debugging
                //std::cout << "-------------------------------------------------------------------\n" << std::flush;
                //std::cout << "Looping over Gauss points. Current GP-#: " << iGP << "\n\n" << std::flush;

                // reset CM evaluation flags
                tCMMasterFluid->reset_eval_flags();

                // reset IWG evaluation flags
                tIWG->reset_eval_flags();

                // create evaluation point xi, tau
                Matrix<DDRMat> tParamPoint = tIntegPoints.get_column(iGP);

                // set integration point
                tCMMasterFluid->mSet->mMasterFIManager->set_space_time(tParamPoint);
                tIWG->mSet->mMasterFIManager->set_space_time(tParamPoint);

                // reset residual and jacobian
                tIWG->mSet->mResidual(0).fill(0.0);
                tIWG->mSet->mJacobian.fill(0.0);

                // compute residual & jacobian // FIXME: factor 6.0, where is it coming from?
                tIWG->compute_residual( tIntegWeights( iGP ) * 0.015 * 6.0 );
                tIWG->compute_jacobian( tIntegWeights( iGP ) * 0.015 * 6.0 );

                // init the jacobian for IWG
                if (iGP == 0)
                {
                        tResidual = tIWG->mSet->mResidual(0);
                        tJacobian = tIWG->mSet->mJacobian;
                }
                else
                {
                        tResidual += tIWG->mSet->mResidual(0);
                        tJacobian += tIWG->mSet->mJacobian;
                }

                // debug: print matrices
                //std::cout << "Integration Weight: " << tIntegWeights( iGP ) << " \n" << std::flush;
                //print( tParamPoint, "tParamPoint" );
                //print( tIWG->mSet->mResidual(0), "tResidual" );
                //print( tJacobian, "tJacobian" );
        }

        // debug: print matrices
        //print(tResidual, "tResidual");
        //print( tJacobian, "tJacobian" );

        // Analytical residual from Matlab code // FIXME: factor 4.0 on some entries, where is it coming from?
        Matrix<DDRMat> tResidualAnalytical = { 
                { +25.27108, -52.78321, -52.78321, +25.27108, +29.87962, -52.78321 * 4.0, +29.87962, +25.27108 * 4.0, +29.87962 * 4.0,
                  +46.60742, -85.21412, -85.21412, +46.60742, +40.97420, -85.21412 * 4.0, +40.97420, +46.60742 * 4.0, +40.97420 * 4.0,

                  +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, 
                  +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0,

                  +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, 
                  +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0,
                   
                  +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, 
                  +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0, +0.000e+0 } }; 

        // transpose                  
        tResidualAnalytical = trans(tResidualAnalytical);               

        // check jacobian against analytical solution
        bool tCheckResidual = fem::check(tResidual, tResidualAnalytical, tEpsilon);
        REQUIRE(tCheckResidual);

        // clean up
        tMasterFIs.clear();

} /*END_TEST_CASE*/


// -----------------------------------------------------------------------------------------------------
// FROM MATLAB CODE
// -----------------------------------------------------------------------------------------------------

// Input for Matlab code ---------------------
// rdof = [ 101.0 122.2 117.7 
//          111.1 144.4 133.3 ]';
//
// vdof = [   0.0   1.1   0.6
//            2.2   4.3   3.7 ]';
//
// tdof = [ 273.3 284.4 278.8 
//          279.9 297.7 287.7 ]';

// Dof map Matlab --> MORIS
// { 1, 2, 2, 1, 3, 2, 3, 1, 3}

//  Residual from Matlab code ----------------

// RHO residual ----------------

// +25.27108
// -52.78321
// +29.87962

// +46.60742
// -85.21412
// +40.97420

// { +25.27108, -52.78321, -52.78321, +25.27108, +29.87962, -52.78321, +29.87962, +25.27108, +29.87962,
//   +46.60742, -85.21412, -85.21412, +46.60742, +40.97420, -85.21412, +40.97420, +46.60742, +40.97420 }


// VX residual -----------------

// +733595.8
// -802116.8
// +68702.02

// +750445.1
// -835697.6
// +85569.41

// { +733595.8, -802116.8, -802116.8, +733595.8, +68702.02, -802116.8, +68702.02, +733595.8, +68702.02,
//   +750445.1, -835697.6, -835697.6, +750445.1, +85569.41, -835697.6, +85569.41, +750445.1, +85569.41 }


// TEMP residual ---------------

// +60669.55
// +277921.9
// -570823.0

// +39181.54
// +770629.1
// -1055798

// { +60669.55, +277921.9, +277921.9, +60669.55, -570823.0, +277921.9, -570823.0, +60669.55, -570823.0, 
//   +39181.54, +770629.1, +770629.1, +39181.54,  -1055798, +770629.1,  -1055798, +39181.54,  -1055798 }
