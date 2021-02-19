#include "fn_WRK_perform_remeshing.hpp"
#include "cl_WRK_Performer.hpp"
#include "cl_HMR.hpp"
#include "cl_HMR_Mesh.hpp"
#include "cl_HMR_Database.hpp"
#include "cl_HMR_File.hpp"
#include "HMR_Globals.hpp"
#include "cl_MTK_Field.hpp"
#include "cl_MTK_Mapper.hpp"
#include "cl_HMR_Mesh_Interpolation.hpp"
#include "cl_HMR_Mesh_Integration.hpp"

#include <memory>

namespace moris
{
    namespace wrk
    {


        //--------------------------------------------------------------------------------------------------------------

        void perform_remeshing(
                mtk::Field                                 * aSourceField,
                moris::Cell< std::shared_ptr< hmr::HMR > > & aHMRPerformers )
        {
            std::pair< moris_index, std::shared_ptr<mtk::Mesh_Manager> > tMeshPairIn = aSourceField->get_mesh_pair();

            moris::mtk::Mesh * tSourceMesh = tMeshPairIn .second->get_interpolation_mesh( tMeshPairIn .first );

            MORIS_ERROR( tSourceMesh->get_mesh_type() == MeshType::HMR,
                    "Mapper::map_input_field_to_output_field() Source mesh is not and HMR mesh" );

            std::shared_ptr< hmr::Database > tHMRDatabase = tSourceMesh->get_HMR_database();

            //get Lagrange and discretization pattern
            //uint tSourceLagrangePattern = tSourceMesh->get_HMR_lagrange_mesh()->get_activation_pattern();
            //uint tTSourceBSPattern = tSourceMesh->
            //        get_HMR_lagrange_mesh()->
            //        get_bspline_pattern( aSourceField->get_discretization_mesh_index() );

            uint tSourceLagrangeOrder = aSourceField->get_lagrange_order();
            uint tDiscretizationOrder = aSourceField->get_discretization_order();

            Matrix< DDLUMat > aElementCounterPerLevelAndPattern;
            moris::Cell< Matrix< DDLUMat > > aElementPerPattern;

            hmr::File tFile;
            tFile.save_refinement_pattern(
                    tSourceMesh->get_HMR_lagrange_mesh(),
                    aSourceField->get_discretization_mesh_index(),
                    aElementCounterPerLevelAndPattern,
                    aElementPerPattern );

            hmr::Parameters * tParameters = aHMRPerformers( 0 )->get_parameters();

            //FIXME adjust parameters hier. eg no initial refinement

            std::shared_ptr< hmr::HMR > tHMRPerformerNew =
                    std::make_shared< hmr::HMR >( tParameters );

            std::shared_ptr< hmr::Database > tHMRDatabaseNew = tHMRPerformerNew->get_database();

            tHMRDatabase->load_refinement_pattern(
                    aElementCounterPerLevelAndPattern,
                    aElementPerPattern);









            // create union mesh
            hmr::Interpolation_Mesh_HMR * tOldInterpolationMesh = new hmr::Interpolation_Mesh_HMR(
                    tHMRDatabaseNew,
                    tSourceLagrangeOrder,
                    5,
                    tDiscretizationOrder,
                    6); // order, Lagrange pattern, bspline pattern

            // Create mesh manager
            std::shared_ptr<mtk::Mesh_Manager> tMeshManager = std::make_shared<mtk::Mesh_Manager>();

            // Register mesh pair
            uint tMeshIndexOld = tMeshManager->register_mesh_pair( tOldInterpolationMesh, nullptr );

            mtk::Field tFieldOld( tMeshManager, tMeshIndexOld );



            mtk::Mapper tMapper;

            tMapper.map_input_field_to_output_field( &tFieldOld, nullptr);

        }


    }
}
