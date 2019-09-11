/*
 * cl_XTK_Hole_Seeder.cpp
 *
 *  Created on: Apr 23, 2019
 *      Author: doble
 */

#include "cl_XTK_Hole_Seeder.hpp"
#include "cl_Cell.hpp"
#include "cl_SphereBox.hpp"

namespace xtk
{

Hole_Seeder::Hole_Seeder( moris::mtk::Mesh* aMTKMesh,
                          moris::real       aRadiusX,
                          moris::real       aRadiusY,
                          moris::real       aRadiusZ,
                          moris::real       aNexp,
                          moris::uint       aNumInX,
                          moris::uint       aNumInY,
                          moris::uint       aNumInZ):
                         mMTKMesh(aMTKMesh),
                         mRadiusX(aRadiusX),
                         mRadiusY(aRadiusY),
                         mRadiusZ(aRadiusZ),
                         mNexp(aNexp),
                         mNumSpheresInX(aNumInX),
                         mNumSpheresInY(aNumInY),
                         mNumSpheresInZ(aNumInZ),
                         mSeededField(aMTKMesh->get_num_nodes(),1)
{

}

Hole_Seeder::Hole_Seeder( moris::real       aRadiusX,
                          moris::real       aRadiusY,
                          moris::real       aRadiusZ,
                          moris::real       aNexp,
                          moris::uint       aNumInX,
                          moris::uint       aNumInY,
                          moris::uint       aNumInZ):
                         mMTKMesh(nullptr),
                         mRadiusX(aRadiusX),
                         mRadiusY(aRadiusY),
                         mRadiusZ(aRadiusZ),
                         mNexp(aNexp),
                         mNumSpheresInX(aNumInX),
                         mNumSpheresInY(aNumInY),
                         mNumSpheresInZ(aNumInZ),
                         mSeededField(0,0)
{

}

void
Hole_Seeder::set_mesh( moris::mtk::Mesh* aMTKMesh)
{
    mMTKMesh = aMTKMesh;
    mSeededField.resize(aMTKMesh->get_num_nodes(),1);
}

void
Hole_Seeder::seed_field()
{
    MORIS_ASSERT(mMTKMesh!=nullptr,"No mesh to seed holes on provided");
    moris::uint tNumNodes = mMTKMesh->get_num_entities(EntityRank::NODE);
    moris::Matrix< moris::DDRMat > tCoords(tNumNodes,3);
    moris::Matrix< moris::DDRMat > tCoordsX(tNumNodes,1);
    moris::Matrix< moris::DDRMat > tCoordsY(tNumNodes,1);
    moris::Matrix< moris::DDRMat > tCoordsZ(tNumNodes,1);
    for(moris::moris_index i = 0; i <(moris::moris_index)tNumNodes; i++)
    {
        moris::Matrix< moris::DDRMat > tNodeCoord =  mMTKMesh->get_node_coordinate(i);
        tCoordsX(i) = tNodeCoord(0);
        tCoordsY(i) = tNodeCoord(1);
        tCoordsZ(i) = tNodeCoord(2);
        tCoords.get_row(i) = tNodeCoord.matrix_data();
    }

    // figure out bounding box
    moris::real tMaxX = tCoordsX.max();
    moris::real tMinX = tCoordsX.min();
    moris::real tMaxY = tCoordsY.max();
    moris::real tMinY = tCoordsY.min();
    moris::real tMaxZ = tCoordsZ.max();
    moris::real tMinZ = tCoordsZ.min();

    moris::real lx = tMaxX-tMinX;
    moris::real ly = tMaxY-tMinY;
    moris::real lz = tMaxZ-tMinZ;

    moris::real xOffset = lx/(mNumSpheresInX+1);
    moris::real yOffset = 0;
    if(mNumSpheresInY > 1)
    {
         yOffset = ly/(mNumSpheresInY-1);
    }
    else
    {
        yOffset = (tMaxY+tMinY)/2;
        tMinY = yOffset;
    }

    std::cout<<"yOff = "<<yOffset<<std::endl;
    moris::real zOffset = 0;
    if(mNumSpheresInZ > 1)
    {
        zOffset = lz/(mNumSpheresInZ-1);
    }
    else
    {
        zOffset = (tMaxZ+tMinZ)/2;
        tMinZ = zOffset;
    }


    moris::uint tNumSpheres = mNumSpheresInX*mNumSpheresInY*mNumSpheresInZ;

    moris::Cell<moris::Matrix<moris::DDRMat>> tCenters(tNumSpheres);

    moris::uint tCount = 0;
    for(moris::uint i = 0; i <mNumSpheresInX; i++)
    {
        for(moris::uint j = 0; j <mNumSpheresInY; j++)
        {
            for(moris::uint k = 0; k<mNumSpheresInZ; k++)
            {
                moris::Matrix<moris::DDRMat> tSphereCenter = {{tMinX + xOffset +  i*xOffset, tMinY+j*yOffset, tMinZ + k*zOffset  }};
                tCenters(tCount) = tSphereCenter;
                tCount++;
            }
        }
    }
    // construct spheres
    moris::Cell<xtk::Sphere_Box> tSpheres(tNumSpheres);
    for(moris::uint i = 0; i <tNumSpheres; i++)
    {
        tSpheres(i) = Sphere_Box(mRadiusX,mRadiusY,mRadiusZ,tCenters(i)(0),tCenters(i)(1),tCenters(i)(2),mNexp);
    }

    // iterate through node to compute a level set value at each node
    Cell<moris::Matrix<moris::DDRMat>> tSphereLSV(tNumNodes);
//    moris::real tNodeVal = 0;
    for(moris::uint i =0; i <tNumNodes; i++)
    {
        tSphereLSV(i) = moris::Matrix<moris::DDRMat>(1,tNumSpheres);

        // iterate through all spheres
        for(moris::uint iSphere =0; iSphere<tNumSpheres; iSphere++)
        {
            tSphereLSV(i)(iSphere) = tSpheres(iSphere).evaluate_field_value_with_coordinate(i,tCoords);
        }

        mSeededField(i) = tSphereLSV(i).min();
    }

    // impose bounds
    moris::real tUpperBound = 1.0;
    moris::real tLowerBound = -1.0;
    for(moris::uint i =0; i <tNumNodes; i++)
    {
        if(mSeededField(i) > tUpperBound)
        {
            mSeededField(i) = tUpperBound;
        }
        else if(mSeededField(i) < tLowerBound)
        {
            mSeededField(i) = tLowerBound;
        }
    }

}

moris::Matrix<moris::DDRMat> const &
Hole_Seeder::get_seeded_field()
{
    return mSeededField;
}

}


