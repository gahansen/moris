/*
 * Copyright (c) 2022 University of Colorado
 * Licensed under the MIT license. See LICENSE.txt file in the MORIS root for details.
 *
 *------------------------------------------------------------------------------------
 *
 * cl_MIG.cpp
 *
 */

#include "cl_MIG.hpp"
#include "cl_GEN_Geometry_Engine.hpp"
#include "cl_MIG_Mesh_Editor.hpp"
#include "cl_MIG_Periodic_2D.hpp"
#include "cl_MIG_Periodic_3D.hpp"
#include "cl_MTK_Mesh_DataBase_IG.hpp"
#include "cl_Tracer.hpp"

namespace moris::mig
{
    // ----------------------------------------------------------------------------
    MIG::MIG( std::shared_ptr< moris::mtk::Mesh_Manager > aMeshManager,
        moris::ParameterList&                             aParameterList,
        moris::ge::Geometry_Engine*                       aGeometryEngine ) :
        mMeshManager( aMeshManager ),
        mParameterList( aParameterList ),
        mGeometryEngine( aGeometryEngine )
    {}

    // ----------------------------------------------------------------------------

    void
    MIG::perform()
    {
        Tracer tTracer("MIG", "No Type", "Perform");

        // get the integration mesh from mesh manager
         mtk::Integration_Mesh* tEnrIntegMesh = mMeshManager->get_mesh_pair( 0 ).get_integration_mesh();

        // get the side sets that pbc will be applied
        std::string tMeshSideSetNames = mParameterList.get< std::string >( "periodic_side_set_pair" );

        // if it is not the default value perform periodic boundary condition
        if ( tMeshSideSetNames != "" )
        {
            //initialize the objects
            mig::Periodic_2D tPeriodic2D;
            mig::Periodic_3D tPeriodic3D;

            // depending on the dimension call the 2d or 3d case
            if ( tEnrIntegMesh->get_spatial_dim() == 2 )
            {
                tPeriodic2D = mig::Periodic_2D( mMeshManager, 0, mParameterList, mGeometryEngine->get_num_phases() );
                tPeriodic2D.perform();
            }
            else
            {
                tPeriodic3D = mig::Periodic_3D( mMeshManager, 0, mParameterList, mGeometryEngine->get_num_phases() );
                tPeriodic3D.perform();
            }

            // cast the parent pointer to child pointer in order to
            mtk::Integration_Mesh_DataBase_IG* tDataBaseIGMesh = dynamic_cast< mtk::Integration_Mesh_DataBase_IG* >( tEnrIntegMesh );

            mig::Periodic_Mesh_Editor tPeriodicMeshEditor;

            if ( tEnrIntegMesh->get_spatial_dim() == 2 )
            {
                tPeriodicMeshEditor = mig::Periodic_Mesh_Editor( tDataBaseIGMesh, &tPeriodic2D );
            }
            else
            {
                tPeriodicMeshEditor = mig::Periodic_Mesh_Editor( tDataBaseIGMesh, &tPeriodic3D );
            }

            //set the ge
            tPeriodicMeshEditor.set_geometry_engine( mGeometryEngine );

            //perform call adds data generated to the database mesh
            tPeriodicMeshEditor.perform();
        }

    }
}// namespace moris::mig

