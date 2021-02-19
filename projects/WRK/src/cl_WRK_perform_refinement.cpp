#include "cl_WRK_Performer.hpp"
#include "cl_HMR.hpp"
#include "cl_HMR_Mesh.hpp"
#include "cl_WRK_perform_refinement.hpp"
#include "HMR_Globals.hpp"

#include "cl_MTK_Field.hpp"

#include "cl_Param_List.hpp"

namespace moris
{
    namespace wrk
    {

        Refinement_Mini_Performer::Refinement_Mini_Performer(
                ParameterList                 & aParameterlist,
                std::shared_ptr< Library_IO >   aLibrary )
        : mLibrary( aLibrary )
        {
            // set field names
            moris::Cell< std::string > tFieldNames;
            string_to_cell(
                    aParameterlist.get< std::string >( "field_names" ),
                    tFieldNames );

            mParameters.mFieldNames = tFieldNames;

            // set refinement level
            Matrix< DDUMat > tRefinementLevel;
            string_to_mat(
                    aParameterlist.get< std::string >( "levels_of_refinement" ),
                    tRefinementLevel );

            mParameters.mRefinementLevel = tRefinementLevel;

            // set refinementpattern
            Matrix< DDUMat > tRefinementPattern;
            string_to_mat(
                    aParameterlist.get< std::string >( "refinement_pattern" ),
                    tRefinementPattern );

            mParameters.mRefinementPattern = tRefinementPattern;

        }

        //--------------------------------------------------------------------------------------------------------------

        void Refinement_Mini_Performer::perform_refinement(
                Cell< mtk::Field >       & aFields,
                std::shared_ptr<hmr::HMR>  aHMR )
        {

        }

        //--------------------------------------------------------------------------------------------------------------

        void Refinement_Mini_Performer::perform_refinement_old(
                std::shared_ptr<hmr::HMR>          aHMR,
                Cell< std::shared_ptr<Performer> > aPerformers,
                bool                               aSimultaneous)
        {
            moris::sint tMaxNumRefinements = get_max_refinement_level( aPerformers );

            moris::Matrix< DDSMat > tMeshIndices;
            moris::uint             tNumMeshes = 0;

            get_all_refinement_mesh_indices(
                    aPerformers,
                    tMeshIndices,
                    tNumMeshes );

            // sint tRefinementNumber = 0;
            sint tNumPerformers = aPerformers.size();

            for (uint Ii = 0; Ii < tNumMeshes; Ii++)
            {
                sint tMeshIndex = tMeshIndices( Ii );

                for (sint Ij = 0; Ij < tMaxNumRefinements; Ij++)
                {
                    // Create mesh //FIXME
                    std::shared_ptr<hmr::Mesh> tMesh = aHMR->create_mesh( tMeshIndex );

                    uint tLagrangeMeshPattern = tMesh->get_lagrange_mesh_pattern();

                    for (sint Ik = 0; Ik < tNumPerformers; Ik++)
                    {
                        // Queue refinement
                        queue_single_refinement(aHMR, tMesh, aPerformers( Ik ), Ij, tMeshIndex);
                    }

                    //refine
                    // Perform refinement and update index
                    if (true)
                    {
                        aHMR->perform_refinement( tLagrangeMeshPattern );
                        aHMR->update_refinement_pattern( tLagrangeMeshPattern );
                    }

                    //if (tPerformRefinement)
                    //{
                    //    aHMR->perform_refinement_based_on_working_pattern( 0, false );
                    //}
                }
            }

            for (uint Ii = 0; Ii < tNumMeshes; Ii++)
            {
                sint tMeshIndex = tMeshIndices( Ii );

                while ( true )
                {
                    // Create mesh //FIXME
                    std::cout<<"MeshIndex: "<<tMeshIndex<<std::endl;
                    std::shared_ptr<hmr::Mesh> tMesh = aHMR->create_mesh( tMeshIndex );

                    uint tLagrangeMeshPattern = tMesh->get_lagrange_mesh_pattern();

                    uint tNumQueuedElements = 0;

                    for (sint Ik = 0; Ik < tNumPerformers; Ik++)
                    {
                        // Queue refinement
                        tNumQueuedElements += queue_low_level_elements_for_refinement(aHMR, tMesh, aPerformers( Ik ), tMeshIndex);
                    }

                    if( tNumQueuedElements == 0 )
                    {
                        break;
                    }

                    //refine
                    // Perform refinement and update index
                    if (true)
                    {
                        aHMR->perform_refinement( tLagrangeMeshPattern );
                        aHMR->update_refinement_pattern( tLagrangeMeshPattern );
                    }

                    //if (tPerformRefinement)
                    //{
                    //    aHMR->perform_refinement_based_on_working_pattern( 0, false );
                    //}
                    break;
                }
            }
        }

        //--------------------------------------------------------------------------------------------------------------

        void Refinement_Mini_Performer::queue_single_refinement(std::shared_ptr<hmr::HMR>  aHMR,
                std::shared_ptr<hmr::Mesh> aMesh,
                std::shared_ptr<Performer> aPerformer,
                sint                       aRefinementNumber,
                sint                       aMeshIndex )
        {
            //uint tLagrangeMeshPattern = aMesh->get_lagrange_mesh_pattern();

            // Loop over fields
            for (uint Ik = 0; Ik < aPerformer->get_num_refinement_fields(); Ik++)
            {
                const moris::Matrix< DDSMat > & tNumRefinements      = aPerformer->get_num_refinements( Ik );
                const moris::Matrix< DDSMat > & tLagrangeMeshIndices = aPerformer->get_refinement_mesh_indices( Ik );

                // loop over tLagrangeMeshIndices // if aMeshIndex put in queue
                for (uint Ii = 0; Ii < tLagrangeMeshIndices.numel(); Ii++)
                {
                    if( tLagrangeMeshIndices( Ii ) == aMeshIndex )
                    {
                        if( tNumRefinements( Ii ) > aRefinementNumber )
                        {
                            // Loop over nodes and get field values
                            Matrix<DDRMat> tFieldValues(aMesh->get_num_nodes(), 1);
                            for (uint tNodeIndex = 0; tNodeIndex < aMesh->get_num_nodes(); tNodeIndex++)
                            {
                                tFieldValues(tNodeIndex) = aPerformer->get_field_value(Ik, tNodeIndex, aMesh->get_node_coordinate(tNodeIndex));
                            }

                            // Put elements on queue and set flag for refinement
                            aHMR->based_on_field_put_elements_on_queue(tFieldValues, 0, aPerformer->get_refinement_function_index(Ik, aRefinementNumber));
                        }
                    }
                }
            }
        }

        //--------------------------------------------------------------------------------------------------------------

        uint Refinement_Mini_Performer::queue_low_level_elements_for_refinement(
                std::shared_ptr<hmr::HMR>  aHMR,
                std::shared_ptr<hmr::Mesh> aMesh,
                std::shared_ptr<Performer> aPerformer,
                sint                       aMeshIndex )
        {
            uint tNumElements = 0;
            // Loop over fields
            for (uint Ik = 0; Ik < aPerformer->get_num_refinement_fields(); Ik++)
            {
                const moris::Matrix< DDSMat > & tLagrangeMeshIndices = aPerformer->get_refinement_mesh_indices( Ik );

                // loop over tLagrangeMeshIndices // if aMeshIndex put in queue
                for (uint Ii = 0; Ii < tLagrangeMeshIndices.numel(); Ii++)
                {
                    if( tLagrangeMeshIndices( Ii ) == aMeshIndex )
                    {
                        // Loop over nodes and get field values
                        Matrix<DDRMat> tFieldValues(aMesh->get_num_nodes(), 1);
                        for (uint tNodeIndex = 0; tNodeIndex < aMesh->get_num_nodes(); tNodeIndex++)
                        {
                            tFieldValues(tNodeIndex) = aPerformer->get_field_value(Ik, tNodeIndex, aMesh->get_node_coordinate(tNodeIndex));
                        }

                        // Put elements on queue and set flag for refinement //FIXME this is untested for a refinement function,
                        tNumElements += aHMR->based_on_field_put_low_level_elements_on_queue(tFieldValues, 0, aPerformer->get_refinement_function_index(Ik, 0));
                    }
                }
            }

            return tNumElements;
        }

        //--------------------------------------------------------------------------------------------------------------

        moris::sint Refinement_Mini_Performer::get_max_refinement_level( const Cell< std::shared_ptr<Performer> > & aPerformers )
        {
            sint tMaxNumRefinements = 0;

            for (uint Ia = 0; Ia < aPerformers.size(); Ia++)
            {
                uint tNumFields = aPerformers( Ia )->get_num_refinement_fields();

                // Loop over fields
                for (uint Ik = 0; Ik < tNumFields; Ik++)
                {
                    const moris::Matrix< DDSMat > & tNumRefinements = aPerformers( Ia )->get_num_refinements( Ik );

                    for (uint Ii = 0; Ii < tNumRefinements.numel(); Ii++)
                    {
                        tMaxNumRefinements = std::max( tMaxNumRefinements, tNumRefinements( Ii ));
                    }
                }
            }

            return tMaxNumRefinements;
        }

        //--------------------------------------------------------------------------------------------------------------

        void Refinement_Mini_Performer::get_all_refinement_mesh_indices(
                const Cell< std::shared_ptr<Performer> > & aPerformers,
                moris::Matrix< DDSMat >                  & aAllPatternMap,
                moris::uint                              & aNumPattern )
        {
            moris::Matrix< DDSMat > tCombinedPattern( hmr::gNumberOfPatterns, 1 , -1 );

            aNumPattern = 0;

            for (uint Ia = 0; Ia < aPerformers.size(); Ia++ )
            {
                uint tNumFields = aPerformers( Ia )->get_num_refinement_fields();

                // Loop over fields
                for (uint Ik = 0; Ik < tNumFields; Ik++)
                {
                    const moris::Matrix< DDSMat > & tRefinementMeshIndex = aPerformers( Ia )->get_refinement_mesh_indices( Ik );

                    for (uint Ii = 0; Ii < tRefinementMeshIndex.numel(); Ii++)
                    {
                        if( tCombinedPattern( tRefinementMeshIndex( Ii ) ) == -1)
                        {
                            tCombinedPattern( tRefinementMeshIndex( Ii ) ) = 1;

                            aNumPattern++;
                        }
                    }
                }
            }

            aAllPatternMap.set_size( aNumPattern, 1 , -1 );

            uint tCounter = 0;

            for (uint Ia = 0; Ia < tCombinedPattern.numel(); Ia++ )
            {
                if( tCombinedPattern( Ia ) == 1 )
                {
                    aAllPatternMap( tCounter++ ) = Ia;
                }
            }
        }
    }
}
