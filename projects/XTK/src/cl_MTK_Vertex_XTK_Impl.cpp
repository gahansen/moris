/*
 * cl_MTK_Vertex_XTK_Impl.cpp
 *
 *  Created on: Mar 8, 2019
 *      Author: doble
 */

#include "cl_MTK_Vertex_XTK_Impl.hpp"
#include "cl_XTK_Background_Mesh.hpp"

namespace moris
{
    namespace mtk
    {
        //------------------------------------------------------------------------------

        Vertex_XTK::Vertex_XTK(){}

        //------------------------------------------------------------------------------

        Vertex_XTK::Vertex_XTK(moris::moris_id aVertexId,
                               moris::moris_index aVertexIndex,
                               xtk::Background_Mesh * aBackgroundMeshPtr)
            : mVertexId(aVertexId),
              mVertexIndex(aVertexIndex),
              mBackgroundMeshPtr(aBackgroundMeshPtr){

              }

        //------------------------------------------------------------------------------

        Vertex_XTK::Vertex_XTK(mtk::Vertex * aBackgroundMeshVertex)
            : mVertexId(aBackgroundMeshVertex->get_id()),
              mVertexIndex(aBackgroundMeshVertex->get_index()),
              mBackgroundMeshVertex(aBackgroundMeshVertex)
        {
        }

        //------------------------------------------------------------------------------

        Vertex_XTK::~Vertex_XTK(){}

        //------------------------------------------------------------------------------

        void
        Vertex_XTK::set_vertex_interpolation(Vertex_Interpolation_XTK * aVertexInterpolation)
        {
            MORIS_ASSERT(aVertexInterpolation != nullptr, "aVertexInterpolation provided is a null ptr");
            mVertexInterpolation = aVertexInterpolation;
        }
        //------------------------------------------------------------------------------

        Matrix<DDRMat>
        Vertex_XTK::get_coords() const
        {
            MORIS_ASSERT(mBackgroundMeshPtr != nullptr || mBackgroundMeshVertex != nullptr, "Background Mesh Pointer and Background Vertex pointer is null in XTK vertex");
            MORIS_ASSERT(!(mBackgroundMeshPtr == nullptr && mBackgroundMeshVertex == nullptr), "Both pointers are not null");
            if (mBackgroundMeshPtr != nullptr)
            {
                return mBackgroundMeshPtr->get_selected_node_coordinates_loc_inds({{mVertexIndex}});
            }
            else if (mBackgroundMeshVertex != nullptr)
            {
                return mBackgroundMeshVertex->get_coords();
            }
            else
            {
                MORIS_ERROR(0, "Invalid get_coord implementation");
                return moris::Matrix<moris::DDRMat>(0, 0);
            }
        }
        //------------------------------------------------------------------------------
        moris_id
        Vertex_XTK::get_id() const
        {
            return mVertexId;
        }

        //------------------------------------------------------------------------------
        
        moris_index
        Vertex_XTK::get_index() const
        {
            return mVertexIndex;
        }

        //------------------------------------------------------------------------------
        moris_index
        Vertex_XTK::get_owner() const
        {
            MORIS_ERROR(false, "Function not implemented in xtk vertex");
            return 0;
        }
        //------------------------------------------------------------------------------
        Vertex_Interpolation *
        Vertex_XTK::get_interpolation(const uint aOrder)
        {
            MORIS_ASSERT(mVertexInterpolation != nullptr, "mInterpolation is a null ptr");
            return mVertexInterpolation;
        }

        //------------------------------------------------------------------------------
        const Vertex_Interpolation *
        Vertex_XTK::get_interpolation(const uint aOrder) const
        {
            MORIS_ASSERT(mVertexInterpolation != nullptr, "mInterpolation is a null ptr");
            return mVertexInterpolation;
        }
        //------------------------------------------------------------------------------
        uint
        Vertex_XTK::get_level() const
        {
            return 0;
        }

        //------------------------------------------------------------------------------
        size_t
        Vertex_XTK::capacity()
        {
            size_t tTotal = 0;
            tTotal += sizeof(mVertexId);
            tTotal += sizeof(mVertexIndex);
            tTotal += sizeof(mVertexInterpolation);
            tTotal += sizeof(mBackgroundMeshVertex);
            tTotal += sizeof(mBackgroundMeshPtr);
            return tTotal;
        }
        //------------------------------------------------------------------------------


    } // namespace mtk
} // namespace moris