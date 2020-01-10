
/*
 * UT_VIS_Visualization_Mesh.cpp
 *
 *  Created on: Dez 02, 2019
 *      Author: schmidt
 */

#include "catch.hpp"
#include "typedefs.hpp"
#include "cl_Map.hpp"
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "fn_equal_to.hpp"

#include "cl_HMR_Mesh_Interpolation.hpp"
#include "cl_HMR.hpp"
#include "cl_HMR_Background_Mesh.hpp" //HMR/src
#include "cl_HMR_BSpline_Mesh_Base.hpp" //HMR/src
#include "cl_HMR_Element.hpp" //HMR/src
#include "cl_HMR_Factory.hpp" //HMR/src
#include "cl_HMR_Field.hpp"
#include "cl_HMR_Lagrange_Mesh_Base.hpp" //HMR/src
#include "cl_HMR_Parameters.hpp" //HMR/src

#include "cl_Mesh_Factory.hpp"
#include "cl_MTK_Mesh_Tools.hpp"
#include "cl_MTK_Mesh_Data_Input.hpp"
#include "cl_MTK_Scalar_Field_Info.hpp"
#include "cl_MTK_Mesh.hpp"
#include "cl_MTK_Mesh_Manager.hpp"
#include "cl_MTK_Interpolation_Mesh.hpp"
#include "cl_MTK_Integration_Mesh.hpp"

#include "cl_XTK_Model.hpp"
#include "cl_XTK_Enriched_Integration_Mesh.hpp"
#include "cl_XTK_Enriched_Interpolation_Mesh.hpp"
#include "../projects/GEN/src/geometry/cl_GEN_Geom_Field.hpp"
#include "../projects/GEN/src/geometry/cl_GEN_Geometry.hpp"

#include "../projects/GEN/src/geometry/cl_GEN_Geometry.hpp"

#include "cl_VIS_Factory.hpp"

#include "cl_MTK_Writer_Exodus.hpp"
#include "cl_MTK_Reader_Exodus.hpp"

#define protected public
#define private   public
#include "cl_VIS_Factory.hpp"
#include "cl_VIS_Visualization_Mesh.hpp"
#undef protected
#undef private

moris::real PlaneVisTest(const moris::Matrix< moris::DDRMat > & aPoint )
{
    moris::real mXC = 0.11;
    moris::real mYC = 0.11;
    moris::real mNx = 1.0;
    moris::real mNy = 0.0;
    return (mNx*(aPoint(0)-mXC) + mNy*(aPoint(1)-mYC));
}

namespace moris
{
    namespace vis
    {

TEST_CASE("Visualization Mesh Output","[VIS],[Vizualization_Mesh_Output]")
    {
        if(par_size() == 1)
            {
                std::string tFieldName = "Geometry";

                moris::uint tLagrangeMeshIndex = 0;
                moris::uint tBSplineMeshIndex = 0;

                moris::hmr::Parameters tParameters;

                tParameters.set_number_of_elements_per_dimension( { {20}, {10} } );
                tParameters.set_domain_dimensions({ {2}, {1} });
                tParameters.set_domain_offset({ {-1.0}, {-0.0} });
                tParameters.set_bspline_truncation( true );

                tParameters.set_output_meshes( { {0} } );

                tParameters.set_lagrange_orders  ( { {1} });
                tParameters.set_lagrange_patterns({ {0} });

                tParameters.set_bspline_orders   ( { {1} } );
                tParameters.set_bspline_patterns ( { {0} } );

                tParameters.set_side_sets({{1},{2},{3},{4} });

                tParameters.set_refinement_buffer( 1 );
                tParameters.set_staircase_buffer( 1 );

                Cell< Matrix< DDUMat > > tLagrangeToBSplineMesh( 1 );
                tLagrangeToBSplineMesh( 0 ) = { {0} };

                tParameters.set_lagrange_to_bspline_mesh( tLagrangeToBSplineMesh );

                hmr::HMR tHMR( tParameters );

                std::shared_ptr< moris::hmr::Mesh > tMesh = tHMR.create_mesh( tLagrangeMeshIndex );

                // create field
                std::shared_ptr< moris::hmr::Field > tPlaneField  = tMesh->create_field( tFieldName, tLagrangeMeshIndex );

                tPlaneField->evaluate_scalar_function( PlaneVisTest);

                for( uint k=0; k<2; ++k )
                {
                    tHMR.flag_surface_elements_on_working_pattern( tPlaneField );
                    tHMR.perform_refinement_based_on_working_pattern( 0 );
                    tPlaneField->evaluate_scalar_function( PlaneVisTest);
                }

                tHMR.finalize();

//                tHMR.save_to_exodus( 0, "./xtk_exo/xtk_hmr_2d_enr_ip2.e" );

                std::shared_ptr< hmr::Interpolation_Mesh_HMR > tInterpMesh = tHMR.create_interpolation_mesh( tLagrangeMeshIndex  );

                moris::ge::GEN_Geom_Field tPlaneFieldAsGeom( tPlaneField );

                moris::Cell< moris::ge::GEN_Geometry* > tGeometryVector = {&tPlaneFieldAsGeom};

                size_t tModelDimension = 2;
                moris::ge::GEN_Phase_Table tPhaseTable (1,  Phase_Table_Structure::EXP_BASE_2);
                moris::ge::GEN_Geometry_Engine tGeometryEngine(tGeometryVector,tPhaseTable,tModelDimension);

                xtk::Model tXTKModel(tModelDimension,tInterpMesh.get(),tGeometryEngine);
                tXTKModel.mVerbose = false;

                //Specify decomposition Method and Cut Mesh ---------------------------------------
                Cell<enum Subdivision_Method> tDecompositionMethods = {Subdivision_Method::NC_REGULAR_SUBDIVISION_QUAD4, Subdivision_Method::C_TRI3};
                tXTKModel.decompose(tDecompositionMethods);

                tXTKModel.perform_basis_enrichment(EntityRank::BSPLINE_1,0);

                xtk::Enriched_Interpolation_Mesh & tEnrInterpMesh = tXTKModel.get_enriched_interp_mesh();
                xtk::Enriched_Integration_Mesh   & tEnrIntegMesh = tXTKModel.get_enriched_integ_mesh();

                // place the pair in mesh manager
                mtk::Mesh_Manager tMeshManager;
                tMeshManager.register_mesh_pair(&tEnrInterpMesh, &tEnrIntegMesh);

                //----------------------------------------------------------------------------------------------

//                mtk::Mesh* tMesh11 = new Visualization_Mesh( &tMeshManager, 0 );

                vis::VIS_Factory tVisFactory(&tMeshManager, 0);

//                mtk::Mesh * tVisMesh = tVisFactory.create_visualization_mesh();
//
//                Writer_Exodus writer(tVisMesh);
//                std::string tPrefix = std::getenv("MORISROOT");
//                std::string tMeshFilePath = tPrefix + "build";
//                writer.write_mesh(tMeshFilePath, "Vis_Mesh_2.exo");
//
//                moris::Cell<const moris::mtk::Cell*> tElementsInBlock = tVisMesh->get_block_set_cells("HMR_dummy_c_p0");
//
//                uint tNumElements = tElementsInBlock.size();
//                moris::Matrix<moris::DDRMat> tetField(tNumElements, 1, 4);
//                moris::Cell<std::string> tElementalFieldNames(1);
//                tElementalFieldNames(0) = "pressure";
//
//                for(uint Ik = 0; Ik<tNumElements;Ik++)
//                {
//                	tetField( Ik ) = Ik;
//                }
//
//                writer.set_elemental_fields(tElementalFieldNames);
//                writer.set_time(0.0);
//                writer.write_elemental_field("HMR_dummy_c_p0", "pressure", tetField);
//
//                writer.close_file();
    }
    }
    }
}

