#include <string>
#include <iostream>
#include "typedefs.hpp"
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_FEM_Field_Interpolator_Manager.hpp"
#include "cl_MSI_Equation_Object.hpp"
#include "cl_TSA_Time_Solver.hpp"
#include "cl_DLA_Solver_Interface.hpp"
#include "cl_DLA_Linear_Solver_Aztec.hpp"
#include "fn_PRM_FEM_Parameters.hpp"
#include "fn_PRM_MSI_Parameters.hpp"
#include "fn_PRM_SOL_Parameters.hpp"
#include "fn_PRM_VIS_Parameters.hpp"
#include "fn_PRM_HMR_Parameters.hpp"
#include "fn_PRM_GEN_Parameters.hpp"
#include "fn_PRM_XTK_Parameters.hpp"
#include "fn_PRM_OPT_Parameters.hpp"
#include "fn_equal_to.hpp"

#include "AztecOO.h"


#ifdef  __cplusplus
extern "C"
{

#endif
//------------------------------------------------------------------------------
namespace moris
{

    //------------------------------------------------------------------------------
    //-------------------------------- QUICK SETUP ---------------------------------
    //------------------------------------------------------------------------------

    // include/exclude Interface Nitsche Dirichlet boundary for debugging
    bool tHaveDirichlet = true;

    //include/exclude Ghost IWG for debugging
    bool tHaveGhost = true;

    // Output Config --------------------------------------------------
    // set to true for vis output, set to false for sensitivity validation
    bool tOutputCriterion    = false;
    std::string tHDF5Path    = "SA_Cut_Bar_Static.hdf5";
    std::string tLibraryName = "SA_Cut_Bar_Static.so";
    std::string tOutputFile  = "SA_Cut_Bar_Static.exo";

    // Geometry Parameters --------------------------------------------
    moris::real tXlength = 0.1;
    moris::real tYlength = 0.5;
    moris::real tPcmFinRatio = 0.9;
    moris::real tDeltaRatio = 0.05;
    moris::real tPcmFinRatioMin = tPcmFinRatio - tDeltaRatio;
    moris::real tPcmFinRatioMax = tPcmFinRatio + tDeltaRatio;
    std::string tInterfacePos = std::to_string( tPcmFinRatio * tYlength );

    // Solver Configuration -------------------------------------------   
    moris::real tNLARelResNormDrop = 1.0e-07;
    moris::real tNLARelaxationParameter = 1.0;
    moris::sint tNLAMaxIter = 10;

    // material parameters --------------------------------------------

    // conductor material
    std::string tDensityFin = "1.0";
    std::string tHeatCapFin = "50.0";
    std::string tThermConductFin = "50.0";

    // heat storage material 
    std::string tDensityPCM = "1.0";
    std::string tHeatCapPCM = "50.0";
    std::string tThermConductPCM = "1.0";
    std::string tLatentHeatPCM = "1000.0"; 
    std::string tPCTemp = "20.0";
    std::string tPCTempRange = "6.0";

    // initial & boundary conditions ----------------------------------
    std::string tHeatFlux = "1000.0";
    std::string tImposedTemperature = "10.0";

    // IQI Configuration ----------------------------------------------
    std::string tMaxTempReference = "10.0";
    std::string tMaxTempExponent = "2.0";

    // Mesh sets ------------------------------------------------------

    // Bulk sets
    std::string tFinBulk = "HMR_dummy_n_p3,HMR_dummy_c_p3";
    std::string tPcmBulk = "HMR_dummy_n_p1,HMR_dummy_c_p1";
    std::string tTotalDomain = tFinBulk + "," + tPcmBulk;

    // Side sets
    std::string tFinPcmInterface  = "dbl_iside_p0_3_p1_1";
    std::string tFinNeumannInterface  = "SideSet_3_n_p3,SideSet_3_c_p3";
    std::string tPCMDirichletInterface = "SideSet_1_n_p1,SideSet_1_c_p1";

    // Ghost sets
    std::string tFinGhost = "ghost_p3";
    std::string tPcmGhost = "ghost_p1";

    // HMR parameters -------------------------------------------------
    std::string tNumElemsPerDim = "1, 40";
    std::string tDomainDims = "0.16, 0.6";
    std::string tDomainOffset = "-0.0342356,-0.031345";  

    //------------------------------------------------------------------------------
    //-------------------------------- FUNCTIONS -----------------------------------
    //------------------------------------------------------------------------------

    /* ------------------------------------------------------------------------ */
    // PROPERTY FUNCTIONS (incl. INITIAL & BOUNDARY CONDITIONS)
    /* ------------------------------------------------------------------------ */       

    // Constant function for properties
    void Func_Const( 
            moris::Matrix< moris::DDRMat >                 & aPropMatrix,
            moris::Cell< moris::Matrix< moris::DDRMat > >  & aParameters,
            moris::fem::Field_Interpolator_Manager         * aFIManager )
    {
        aPropMatrix = aParameters( 0 );
    }

    /* ------------------------------------------------------------------------ */
    // DUMMY FUNCTIONS
    /* ------------------------------------------------------------------------ */       

    bool Output_Criterion( moris::tsa::Time_Solver * aTimeSolver )
    {
        return tOutputCriterion;
    }

    moris::Matrix< DDRMat > Func_Dummy_Sensitivity(
            const moris::Matrix< DDRMat >     & aCoordinates,
            const moris::Cell< moris::real* > & aGeometryParameters )
            {
        moris::Matrix< DDRMat > aReturnValue = {{0.0}};
        return aReturnValue;
            }

    /* ------------------------------------------------------------------------ */
    // FOR SWEEP
    /* ------------------------------------------------------------------------ */

    moris::Matrix< moris::DDSMat > get_constraint_types()
            {
        Matrix<DDSMat> tConstraintTypes( 1, 1, 1 );
        return tConstraintTypes;
            }

    moris::Matrix< moris::DDRMat > compute_objectives(Matrix<DDRMat> aADVs, moris::Matrix< moris::DDRMat > aCriteria)
            {
        moris::Matrix< moris::DDRMat > tObjectives( 1, 1, aCriteria(0) );
        return tObjectives;
            }

    moris::Matrix< moris::DDRMat > compute_constraints(Matrix<DDRMat> aADVs, moris::Matrix< moris::DDRMat > aCriteria)
            {
        moris::Matrix< moris::DDRMat > tConstraints( 1, 1, aCriteria(1) );
        return tConstraints;
            }

    moris::Matrix< moris::DDRMat > compute_dobjective_dadv(Matrix<DDRMat> aADVs, moris::Matrix< moris::DDRMat > aCriteria)
            {
        moris::Matrix< moris::DDRMat > tDObjectiveDADV( 1, aADVs.length(), 0.0 );
        return tDObjectiveDADV;
            }

    moris::Matrix< moris::DDRMat > compute_dobjective_dcriteria(moris::Matrix< moris::DDRMat > aADVs, moris::Matrix< moris::DDRMat > aCriteria)
            {
        moris::Matrix< moris::DDRMat > tDObjectiveDCriteria( 1, 2, 0.0 );
        tDObjectiveDCriteria(0) = 1.0;
        return tDObjectiveDCriteria;
            }

    moris::Matrix< moris::DDRMat > compute_dconstraint_dadv(moris::Matrix< moris::DDRMat > aADVs, moris::Matrix< moris::DDRMat > aCriteria)
            {
        moris::Matrix< moris::DDRMat > tDConstraintDADV( 1, aADVs.length(), 0.0 );
        return tDConstraintDADV;
            }

    moris::Matrix< moris::DDRMat > compute_dconstraint_dcriteria(moris::Matrix< moris::DDRMat > aADVs, moris::Matrix< moris::DDRMat > aCriteria)
            {
        moris::Matrix< moris::DDRMat > tDConstraintDCriteria( 1, 2, 0.0 );
        tDConstraintDCriteria(1) = 1.0;
        return tDConstraintDCriteria;
            }

    /* ------------------------------------------------------------------------ */
    // PARAMETER LISTS
    /* ------------------------------------------------------------------------ */    

    void HMRParameterList( moris::Cell< moris::Cell< ParameterList > > & tParameterlist )
    {
        tParameterlist.resize( 1 );
        tParameterlist( 0 ).resize( 1 );

        tParameterlist( 0 )( 0 ) = prm::create_hmr_parameter_list();

        tParameterlist( 0 )( 0 ).set( "number_of_elements_per_dimension", tNumElemsPerDim );
        tParameterlist( 0 )( 0 ).set( "domain_dimensions",                tDomainDims );
        tParameterlist( 0 )( 0 ).set( "domain_offset",                    tDomainOffset );
        tParameterlist( 0 )( 0 ).set( "domain_sidesets",                  "1,2,3,4");
        tParameterlist( 0 )( 0 ).set( "lagrange_output_meshes",           "0");

        tParameterlist( 0 )( 0 ).set( "lagrange_orders",   "1" );
        tParameterlist( 0 )( 0 ).set( "bspline_orders",    "1" );
        tParameterlist( 0 )( 0 ).set( "lagrange_pattern",  "0" );
        tParameterlist( 0 )( 0 ).set( "bspline_pattern",   "0" );

        tParameterlist( 0 )( 0 ).set( "lagrange_to_bspline", "0") ;

        tParameterlist( 0 )( 0 ).set( "truncate_bsplines",  1 );
        tParameterlist( 0 )( 0 ).set( "refinement_buffer",  0 );
        tParameterlist( 0 )( 0 ).set( "staircase_buffer",   0 );
        tParameterlist( 0 )( 0 ).set( "initial_refinement", 0 );

        tParameterlist( 0 )( 0 ).set( "use_multigrid",  0 );
        tParameterlist( 0 )( 0 ).set( "severity_level", 0 );

        tParameterlist( 0 )( 0 ).set( "adaptive_refinement_level", 0 );
    }

    void OPTParameterList( moris::Cell< moris::Cell< ParameterList > > & tParameterlist )
    {
        tParameterlist.resize( 3 );
        tParameterlist( 0 ).resize( 1 );
        tParameterlist( 1 ).resize( 0 );
        tParameterlist( 2 ).resize( 1 );

        tParameterlist(0)(0) = moris::prm::create_opt_problem_parameter_list();
        tParameterlist(0)(0).set( "is_optimization_problem", true );
        tParameterlist(0)(0).set( "problem", "user_defined" );
        tParameterlist(0)(0).set( "library", tLibraryName );

        tParameterlist(2)(0) = moris::prm::create_sweep_parameter_list();
        tParameterlist(2)(0).set( "print", true );
        tParameterlist(2)(0).set( "hdf5_path", tHDF5Path );
        tParameterlist(2)(0).set( "num_evaluations_per_adv", "1" );
        tParameterlist(2)(0).set( "include_bounds", false );
        tParameterlist(2)(0).set( "finite_difference_type", "all" );
    }

    void XTKParameterList( moris::Cell< moris::Cell< ParameterList > > & tParameterlist )
    {
        tParameterlist.resize( 1 );
        tParameterlist( 0 ).resize( 1 );

        tParameterlist( 0 )( 0 ) = prm::create_xtk_parameter_list();
        tParameterlist( 0 )( 0 ).set( "decompose",                 true );
        tParameterlist( 0 )( 0 ).set( "decomposition_type",        "conformal") ;
        tParameterlist( 0 )( 0 ).set( "enrich",                    true );
        tParameterlist( 0 )( 0 ).set( "basis_rank",                "bspline") ;
        tParameterlist( 0 )( 0 ).set( "enrich_mesh_indices",       "0") ;
        tParameterlist( 0 )( 0 ).set( "ghost_stab",                true );
        tParameterlist( 0 )( 0 ).set( "multigrid",                 false );
        tParameterlist( 0 )( 0 ).set( "verbose",                   true );
        tParameterlist( 0 )( 0 ).set( "print_enriched_ig_mesh",    true );
        tParameterlist( 0 )( 0 ).set( "exodus_output_XTK_ig_mesh", true );
        tParameterlist( 0 )( 0 ).set( "high_to_low_dbl_side_sets", true );
    }

    void GENParameterList( moris::Cell< moris::Cell< ParameterList > > & tParameterlist )
    {
        tParameterlist.resize( 3 );
        tParameterlist( 0 ).resize( 1 );

        // Main GEN parameter list
        tParameterlist( 0 )( 0 ) = prm::create_gen_parameter_list();
        tParameterlist( 0 )( 0 ).set("initial_advs"      , std::to_string(tYlength * tPcmFinRatioMin));
        tParameterlist( 0 )( 0 ).set("lower_bounds"      , std::to_string(tYlength * tPcmFinRatioMin));
        tParameterlist( 0 )( 0 ).set("upper_bounds"      , std::to_string(tYlength * tPcmFinRatioMax));       
        tParameterlist( 0 )( 0 ).set("IQI_types"         , "IQIMaxTemp,IQIBulkVolume");

        // init geometry counter
        uint tGeoCounter = 0;

        // Geometry parameter lists
        tParameterlist( 1 ).push_back( prm::create_geometry_parameter_list() );
        tParameterlist( 1 )( tGeoCounter ).set( "type", "plane");
        tParameterlist( 1 )( tGeoCounter ).set( "constant_parameters", "-1.0, 0.0, 1.0, 0.0");
        tParameterlist( 1 )( tGeoCounter ).set( "multigeometry_id", "boundary");
        tGeoCounter++;

        tParameterlist( 1 ).push_back( prm::create_geometry_parameter_list() );
        tParameterlist( 1 )( tGeoCounter ).set( "type", "plane");
        tParameterlist( 1 )( tGeoCounter ).set( "geometry_variable_indices", "1");
        tParameterlist( 1 )( tGeoCounter ).set( "adv_indices", "0");
        tParameterlist( 1 )( tGeoCounter ).set( "constant_parameters", "0.0, 0.0, 1.0");
        tGeoCounter++;
    }

    void FEMParameterList( moris::Cell< moris::Cell< ParameterList > > & tParameterList )
    {
        // create a cell of cell of parameter list for fem
        tParameterList.resize( 6 );

        //------------------------------------------------------------------------------
        // init property counter
        uint tPropCounter = 0;

        // Density of conductor material
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ) = prm::create_property_parameter_list();
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropFinDensity") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tDensityFin );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Thermal conductivity of conductor material
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropFinConductivity") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tThermConductFin );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Heat capacity of conductor material
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropFinHeatCapacity") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tHeatCapFin );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Density of storage material
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ) = prm::create_property_parameter_list();
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropPcmDensity") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tDensityPCM );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Thermal conductivity of storage material
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropPcmConductivity") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tThermConductPCM );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Heat capacity of storage material
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropPcmHeatCapacity") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tHeatCapPCM );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Latent heat capacity of storage material
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropLatentHeat") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tLatentHeatPCM );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Melt temperature of storage material
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropPCTemp") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tPCTemp );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Phase change function 
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropPhaseState") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      "2.0") ;
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Melting range of storage material 
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropPCconst") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tPCTempRange );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Neumann BC
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropNeumannBC") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tHeatFlux );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Dirichlet BC
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropImposedTemperature") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tImposedTemperature );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Dummy latent heat for non-pc material
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropDummyLatentHeat") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      "0.0") ;
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropDummyPCTemp") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      "10000.0") ;
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Reference Temperature for MAX_DOF - IQI
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropMaxTempReference") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tMaxTempReference );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        // Exponent for MAX_DOF - IQI
        tParameterList( 0 ).push_back( prm::create_property_parameter_list() );
        tParameterList( 0 )( tPropCounter ).set( "property_name",            "PropMaxTempExponent") ;
        tParameterList( 0 )( tPropCounter ).set( "function_parameters",      tMaxTempExponent );
        tParameterList( 0 )( tPropCounter ).set( "value_function",           "Func_Const") ;
        tPropCounter++;

        //------------------------------------------------------------------------------

        // init CM counter
        uint tCMCounter = 0;

        // constitutive model for thermal storage material 
        tParameterList( 1 ).push_back( prm::create_constitutive_model_parameter_list() );
        tParameterList( 1 )( tCMCounter ).set( "constitutive_name", "CMDiffusionPcm") ;
        tParameterList( 1 )( tCMCounter ).set( "constitutive_type", static_cast< uint >( fem::Constitutive_Type::DIFF_LIN_ISO ) );
        tParameterList( 1 )( tCMCounter ).set( "dof_dependencies",  std::pair< std::string, std::string >( "TEMP", "Temperature" ) );
        tParameterList( 1 )( tCMCounter ).set( "properties",
                "PropPcmConductivity,Conductivity;" 
                "PropPcmDensity,Density;" 
                "PropPcmHeatCapacity,HeatCapacity") ;
        tCMCounter++;

        // constitutive model for thermal conductor material 
        tParameterList( 1 ).push_back( prm::create_constitutive_model_parameter_list() );
        tParameterList( 1 )( tCMCounter ).set( "constitutive_name", "CMDiffusionFin") ;
        tParameterList( 1 )( tCMCounter ).set( "constitutive_type", static_cast< uint >( fem::Constitutive_Type::DIFF_LIN_ISO ) );
        tParameterList( 1 )( tCMCounter ).set( "dof_dependencies",  std::pair< std::string, std::string >( "TEMP", "Temperature" ) );
        tParameterList( 1 )( tCMCounter ).set( "properties",
                "PropFinConductivity,Conductivity;"
                "PropFinDensity,Density;"
                "PropFinHeatCapacity,HeatCapacity") ;
        tCMCounter++;

        //------------------------------------------------------------------------------

        // init SP counter
        uint tSPCounter = 0;

        // Ghost parameter for fin
        tParameterList( 2 ).push_back( prm::create_stabilization_parameter_parameter_list() );
        tParameterList( 2 )( tSPCounter ).set( "stabilization_name",      "SPGPTempFin") ;
        tParameterList( 2 )( tSPCounter ).set( "stabilization_type",      static_cast< uint >( fem::Stabilization_Type::GHOST_DISPL ) );
        tParameterList( 2 )( tSPCounter ).set( "function_parameters",     "0.01") ;
        tParameterList( 2 )( tSPCounter ).set( "master_properties",       "PropFinConductivity,Material") ;
        tSPCounter++;

        // Ghost parameter for PCM
        tParameterList( 2 ).push_back( prm::create_stabilization_parameter_parameter_list() );
        tParameterList( 2 )( tSPCounter ).set( "stabilization_name",      "SPGPTempPcm") ;
        tParameterList( 2 )( tSPCounter ).set( "stabilization_type",      static_cast< uint >( fem::Stabilization_Type::GHOST_DISPL ) );
        tParameterList( 2 )( tSPCounter ).set( "function_parameters",     "0.01") ;
        tParameterList( 2 )( tSPCounter ).set( "master_properties",       "PropPcmConductivity,Material") ;
        tSPCounter++;

        // GGLS parameter for fin
        tParameterList( 2 ).push_back( prm::create_stabilization_parameter_parameter_list() );
        tParameterList( 2 )( tSPCounter ).set( "stabilization_name",      "SPGGLSDiffusionFin") ;
        tParameterList( 2 )( tSPCounter ).set( "stabilization_type",      static_cast< uint >( fem::Stabilization_Type::GGLS_DIFFUSION ) );
        tParameterList( 2 )( tSPCounter ).set( "master_dof_dependencies", std::pair< std::string, std::string >( "TEMP", "Temperature" ) );
        tParameterList( 2 )( tSPCounter ).set( "master_properties",
                "PropFinConductivity, Conductivity;"      
                "PropFinDensity     , Density;"           
                "PropFinHeatCapacity, HeatCapacity;"      
                "PropDummyLatentHeat, LatentHeat;"        
                "PropDummyPCTemp    , PCTemp;"            
                "PropPhaseState     , PhaseStateFunction;"
                "PropPCconst        , PhaseChangeConst")    ;
        tSPCounter++;

        // GGLS parameter for thermal storage material
        tParameterList( 2 ).push_back( prm::create_stabilization_parameter_parameter_list() );
        tParameterList( 2 )( tSPCounter ).set( "stabilization_name",      "SPGGLSDiffusionPcm") ;
        tParameterList( 2 )( tSPCounter ).set( "stabilization_type",      static_cast< uint >( fem::Stabilization_Type::GGLS_DIFFUSION ) );
        tParameterList( 2 )( tSPCounter ).set( "master_dof_dependencies", std::pair< std::string, std::string >( "TEMP", "Temperature" ) );
        tParameterList( 2 )( tSPCounter ).set( "master_properties",
                "PropPcmConductivity, Conductivity;"       
                "PropPcmDensity     , Density;"            
                "PropPcmHeatCapacity, HeatCapacity;"       
                "PropDummyLatentHeat, LatentHeat;"         
                "PropDummyPCTemp    , PCTemp;"             
                "PropPhaseState     , PhaseStateFunction;" 
                "PropPCconst        , PhaseChangeConst")    ;
        tSPCounter++;

        // Interface Dirichlet SP              
        tParameterList( 2 ).push_back( prm::create_stabilization_parameter_parameter_list() );
        tParameterList( 2 )( tSPCounter ).set( "stabilization_name",  "SPInterfaceNitsche") ;
        tParameterList( 2 )( tSPCounter ).set( "stabilization_type",  static_cast< uint >( fem::Stabilization_Type::NITSCHE_INTERFACE ) );
        tParameterList( 2 )( tSPCounter ).set( "function_parameters", "100.0") ;
        tParameterList( 2 )( tSPCounter ).set( "master_properties",   "PropFinConductivity,Material") ;
        tParameterList( 2 )( tSPCounter ).set( "slave_properties",    "PropPcmConductivity,Material") ;
        tSPCounter++;

        // Boundary Dirichlet SP  
        tParameterList( 2 ).push_back( prm::create_stabilization_parameter_parameter_list() );
        tParameterList( 2 )( tSPCounter ).set( "stabilization_name",      "SPNitscheTemp") ;
        tParameterList( 2 )( tSPCounter ).set( "stabilization_type",      static_cast< uint >( fem::Stabilization_Type::DIRICHLET_NITSCHE ) );
        tParameterList( 2 )( tSPCounter ).set( "function_parameters",     "10.0") ;
        tParameterList( 2 )( tSPCounter ).set( "master_properties",       "PropPcmConductivity,Material") ;
        tSPCounter++;

        //------------------------------------------------------------------------------
        // init IWG counter
        uint tIWGCounter = 0;

        // Bulk IWG for conductor material
        tParameterList( 3 ).push_back( prm::create_IWG_parameter_list() );
        tParameterList( 3 )( tIWGCounter ).set( "IWG_name",                   "IWGDiffusionFinBulk") ;
        tParameterList( 3 )( tIWGCounter ).set( "IWG_type",                   static_cast< uint >( fem::IWG_Type::SPATIALDIFF_BULK ) );
        tParameterList( 3 )( tIWGCounter ).set( "dof_residual",               "TEMP") ;
        tParameterList( 3 )( tIWGCounter ).set( "master_dof_dependencies",    "TEMP") ;
        tParameterList( 3 )( tIWGCounter ).set( "master_constitutive_models", "CMDiffusionFin,Diffusion") ;
        tParameterList( 3 )( tIWGCounter ).set( "stabilization_parameters",   "SPGGLSDiffusionFin,GGLSParam") ;
        tParameterList( 3 )( tIWGCounter ).set( "mesh_set_names",             tFinBulk );
        tIWGCounter++;

        // Bulk IWG for thermal storage material
        tParameterList( 3 ).push_back( prm::create_IWG_parameter_list() );
        tParameterList( 3 )( tIWGCounter ).set( "IWG_name",                   "IWGDiffusionPcmBulk") ;
        tParameterList( 3 )( tIWGCounter ).set( "IWG_type",                   static_cast< uint >( fem::IWG_Type::SPATIALDIFF_BULK ) );
        tParameterList( 3 )( tIWGCounter ).set( "dof_residual",               "TEMP") ;
        tParameterList( 3 )( tIWGCounter ).set( "master_dof_dependencies",    "TEMP") ;
        tParameterList( 3 )( tIWGCounter ).set( "master_constitutive_models", "CMDiffusionPcm,Diffusion") ;
        tParameterList( 3 )( tIWGCounter ).set( "stabilization_parameters",   "SPGGLSDiffusionPcm,GGLSParam") ;
        tParameterList( 3 )( tIWGCounter ).set( "mesh_set_names",             tPcmBulk );
        tIWGCounter++;

        // Interface Dirichlet BC              
        tParameterList( 3 ).push_back( prm::create_IWG_parameter_list() );
        tParameterList( 3 )( tIWGCounter ).set( "IWG_name",                   "IWGInterfaceFinPcm") ;
        tParameterList( 3 )( tIWGCounter ).set( "IWG_type",                   static_cast< uint >( fem::IWG_Type::SPATIALDIFF_INTERFACE ) );
        tParameterList( 3 )( tIWGCounter ).set( "dof_residual",               "TEMP") ;
        tParameterList( 3 )( tIWGCounter ).set( "master_dof_dependencies",    "TEMP") ;
        tParameterList( 3 )( tIWGCounter ).set( "slave_dof_dependencies",     "TEMP") ;
        tParameterList( 3 )( tIWGCounter ).set( "master_constitutive_models", "CMDiffusionFin,Diffusion") ;
        tParameterList( 3 )( tIWGCounter ).set( "slave_constitutive_models",  "CMDiffusionPcm,Diffusion") ;
        tParameterList( 3 )( tIWGCounter ).set( "stabilization_parameters",   "SPInterfaceNitsche ,NitscheInterface")   ;
        tParameterList( 3 )( tIWGCounter ).set( "mesh_set_names",             tFinPcmInterface );
        tIWGCounter++;

        // Imposed heat flux
        tParameterList( 3 ).push_back( prm::create_IWG_parameter_list() );
        tParameterList( 3 )( tIWGCounter ).set( "IWG_name",                   "IWGInletFlux") ;
        tParameterList( 3 )( tIWGCounter ).set( "IWG_type",                   static_cast< uint >( fem::IWG_Type::SPATIALDIFF_NEUMANN ) );
        tParameterList( 3 )( tIWGCounter ).set( "dof_residual",               "TEMP") ;
        tParameterList( 3 )( tIWGCounter ).set( "master_dof_dependencies",    "TEMP") ;
        tParameterList( 3 )( tIWGCounter ).set( "master_properties",          "PropNeumannBC,Neumann") ;
        tParameterList( 3 )( tIWGCounter ).set( "mesh_set_names",             tFinNeumannInterface );
        tIWGCounter++;

        // Imposed temperature
        tParameterList( 3 ).push_back( prm::create_IWG_parameter_list() );
        tParameterList( 3 )( tIWGCounter ).set( "IWG_name",                   "IWGOutletTemp") ;
        tParameterList( 3 )( tIWGCounter ).set( "IWG_type",                   static_cast< uint >( fem::IWG_Type::SPATIALDIFF_DIRICHLET_UNSYMMETRIC_NITSCHE ) );
        tParameterList( 3 )( tIWGCounter ).set( "dof_residual",               "TEMP") ;
        tParameterList( 3 )( tIWGCounter ).set( "master_dof_dependencies",    "TEMP") ;
        tParameterList( 3 )( tIWGCounter ).set( "master_properties",          "PropImposedTemperature,Dirichlet") ;
        tParameterList( 3 )( tIWGCounter ).set( "master_constitutive_models", "CMDiffusionPcm,Diffusion") ;
        tParameterList( 3 )( tIWGCounter ).set( "stabilization_parameters",   "SPNitscheTemp,DirichletNitsche") ;
        tParameterList( 3 )( tIWGCounter ).set( "mesh_set_names",             tPCMDirichletInterface );
        tIWGCounter++;

        if ( tHaveGhost )
        {
            // Fin Ghost
            tParameterList( 3 ).push_back( prm::create_IWG_parameter_list() );
            tParameterList( 3 )( tIWGCounter ).set( "IWG_name",                   std::string("IWGFinGhost") );
            tParameterList( 3 )( tIWGCounter ).set( "IWG_type",                   static_cast< uint >( fem::IWG_Type::GHOST_NORMAL_FIELD ) );
            tParameterList( 3 )( tIWGCounter ).set( "dof_residual",               std::string("TEMP") );
            tParameterList( 3 )( tIWGCounter ).set( "master_dof_dependencies",    std::string("TEMP") );
            tParameterList( 3 )( tIWGCounter ).set( "slave_dof_dependencies",     std::string("TEMP") );
            tParameterList( 3 )( tIWGCounter ).set( "stabilization_parameters",   std::string("SPGPTempFin,GhostSP") );
            tParameterList( 3 )( tIWGCounter ).set( "mesh_set_names",             tFinGhost );
            tIWGCounter++;

            // PCM Ghost
            tParameterList( 3 ).push_back( prm::create_IWG_parameter_list() );
            tParameterList( 3 )( tIWGCounter ).set( "IWG_name",                   std::string("IWGPcmGhost") );
            tParameterList( 3 )( tIWGCounter ).set( "IWG_type",                   static_cast< uint >( fem::IWG_Type::GHOST_NORMAL_FIELD ) );
            tParameterList( 3 )( tIWGCounter ).set( "dof_residual",               std::string("TEMP") );
            tParameterList( 3 )( tIWGCounter ).set( "master_dof_dependencies",    std::string("TEMP") );
            tParameterList( 3 )( tIWGCounter ).set( "slave_dof_dependencies",     std::string("TEMP") );
            tParameterList( 3 )( tIWGCounter ).set( "stabilization_parameters",   std::string("SPGPTempPcm,GhostSP") );
            tParameterList( 3 )( tIWGCounter ).set( "mesh_set_names",             tPcmGhost );
            tIWGCounter++;
        }

        //------------------------------------------------------------------------------
        // init IQI counter
        uint tIQICounter = 0;

        // IQI - Nodal Temperature Field
        tParameterList( 4 ).push_back( prm::create_IQI_parameter_list() );
        tParameterList( 4 )( tIQICounter ).set( "IQI_name",                   "IQIBulkTEMP") ;
        tParameterList( 4 )( tIQICounter ).set( "IQI_type",                   static_cast< uint >( fem::IQI_Type::DOF ) );
        tParameterList( 4 )( tIQICounter ).set( "master_dof_dependencies",    "TEMP") ;
        tParameterList( 4 )( tIQICounter ).set( "vectorial_field_index",      0 );
        tParameterList( 4 )( tIQICounter ).set( "mesh_set_names",             tTotalDomain );
        tIQICounter++;

        // Volume IQI - Total Volume
        tParameterList( 4 ).push_back( prm::create_IQI_parameter_list() );
        tParameterList( 4 )( tIQICounter ).set( "IQI_name",                   "IQIBulkVolume") ;
        tParameterList( 4 )( tIQICounter ).set( "IQI_type",                   static_cast< uint >( fem::IQI_Type::VOLUME ) );
        tParameterList( 4 )( tIQICounter ).set( "master_dof_dependencies",    "TEMP") ;
        tParameterList( 4 )( tIQICounter ).set( "mesh_set_names",             tPcmBulk );
        tIQICounter++;

        // Max Temperature IQI
        tParameterList( 4 ).push_back( prm::create_IQI_parameter_list() );
        tParameterList( 4 )( tIQICounter ).set( "IQI_name",                   "IQIMaxTemp") ;
        tParameterList( 4 )( tIQICounter ).set( "IQI_type",                   static_cast< uint >( fem::IQI_Type::MAX_DOF ) );
        tParameterList( 4 )( tIQICounter ).set( "master_dof_dependencies",    "TEMP") ;
        tParameterList( 4 )( tIQICounter ).set( "vectorial_field_index",      0 );
        tParameterList( 4 )( tIQICounter ).set( "master_properties",          "PropMaxTempReference,ReferenceValue;"
                "PropMaxTempExponent,Exponent" );
        tParameterList( 4 )( tIQICounter ).set( "mesh_set_names",             tTotalDomain );
        tIQICounter++;

        // create computation  parameter list
        tParameterList( 5 ).resize( 1 );
        tParameterList( 5 )( 0 ) = prm::create_computation_parameter_list();
    }

    void SOLParameterList( moris::Cell< moris::Cell< ParameterList > > & tParameterlist )
    {
        tParameterlist.resize( 7 );
        for( uint Ik = 0; Ik < 7; Ik ++)
        {
            tParameterlist( Ik ).resize( 1 );
        }

        tParameterlist( 0 )( 0 ) = moris::prm::create_linear_algorithm_parameter_list( sol::SolverType::BELOS_IMPL );

        tParameterlist( 1 )( 0 ) = moris::prm::create_linear_solver_parameter_list();

        tParameterlist( 2 )( 0 ) = moris::prm::create_nonlinear_algorithm_parameter_list();
        tParameterlist( 2 )( 0 ).set("NLA_rel_res_norm_drop", tNLARelResNormDrop );
        tParameterlist( 2 )( 0 ).set("NLA_relaxation_parameter", tNLARelaxationParameter );
        tParameterlist( 2 )( 0 ).set("NLA_max_iter", tNLAMaxIter );
        tParameterlist( 2 )( 0 ).set("NLA_combined_res_jac_assembly", false );

        tParameterlist( 3 )( 0 ) = moris::prm::create_nonlinear_solver_parameter_list();
        tParameterlist( 3 )( 0 ).set("NLA_DofTypes"      , "TEMP") ;

        tParameterlist( 4 )( 0 ) = moris::prm::create_time_solver_algorithm_parameter_list();

        tParameterlist( 5 )( 0 ) = moris::prm::create_time_solver_parameter_list();
        tParameterlist( 5 )( 0 ).set("TSA_DofTypes",            "TEMP") ;
        tParameterlist( 5 )( 0 ).set("TSA_Initialize_Sol_Vec",  "TEMP,0.0") ;
        tParameterlist( 5 )( 0 ).set("TSA_Output_Indices",      "0") ;
        tParameterlist( 5 )( 0 ).set("TSA_Output_Crteria",      "Output_Criterion") ;
        tParameterlist( 5 )( 0 ).set("TSA_time_level_per_type", "TEMP,1") ;

        tParameterlist( 6 )( 0 ) = moris::prm::create_solver_warehouse_parameterlist();
    }

    void MSIParameterList( moris::Cell< moris::Cell< ParameterList > > & tParameterlist )
    {
        tParameterlist.resize( 1 );
        tParameterlist( 0 ).resize( 1 );

        tParameterlist( 0 )( 0 ) = prm::create_msi_parameter_list();
    }

    void VISParameterList( moris::Cell< moris::Cell< ParameterList > > & tParameterlist )
    {
        tParameterlist.resize( 1 );
        tParameterlist( 0 ).resize( 2 );

        tParameterlist( 0 )( 0 ) = prm::create_vis_parameter_list();
        tParameterlist( 0 )( 0 ).set( "File_Name"  , std::pair< std::string, std::string >( "./", tOutputFile ) );
        tParameterlist( 0 )( 0 ).set( "Mesh_Type"  , static_cast< uint >( vis::VIS_Mesh_Type::STANDARD ) );

        tParameterlist( 0 )( 0 ).set( "Set_Names"  , tTotalDomain );
        tParameterlist( 0 )( 0 ).set( "Field_Names",  "TEMP,MAX_DOF" ) ;
        tParameterlist( 0 )( 0 ).set( "Field_Type" ,  "NODAL,GLOBAL" ) ;
        tParameterlist( 0 )( 0 ).set( "IQI_Names",  "IQIBulkTEMP,IQIMaxTemp" ) ;    
    }

    //------------------------------------------------------------------------------
}

//------------------------------------------------------------------------------
#ifdef  __cplusplus
}
#endif