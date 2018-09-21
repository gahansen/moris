/*
 * cl_MSI_Node.hpp
 *
 *  Created on: Aug 22, 2018
 *      Author: messe
 */

#ifndef PROJECTS_FEM_MSI_SRC_CL_MSI_NODE_HPP_
#define PROJECTS_FEM_MSI_SRC_CL_MSI_NODE_HPP_

#include "typedefs.hpp"           //MRS/COR/src
#include "cl_MTK_Vertex.hpp"      //MTK/src
#include "cl_FEM_Node_Base.hpp"      //MTK/src

namespace moris
{
    namespace fem
    {
//------------------------------------------------------------------------------

        class Node : public Node_Base
        {
            const mtk::Vertex * mVertex;
            sint            mID;
            sint         mIndex;

//------------------------------------------------------------------------------
        public:
//------------------------------------------------------------------------------

            /**
             * constructor
             */
            Node( const mtk::Vertex * aVertex ) : mVertex( aVertex )
            {
                // FIXME : this needs to be decoupled
                mID    = aVertex->get_id();
                mIndex = aVertex->get_index();
            }

//------------------------------------------------------------------------------

            /**
             * destructor
             */
            ~Node(){};

//------------------------------------------------------------------------------

            /**
             * returns the owner of this node
             */
            auto
            get_owner() const -> decltype( mVertex->get_owner() )
            {
                return mVertex->get_owner();
            }

//------------------------------------------------------------------------------

            /**
             * returns the T-Matrix of this node
             */
            const Matrix< DDRMat > *
            get_t_matrix() const
            {
                return mVertex->get_interpolation()->get_weights();
            }

//------------------------------------------------------------------------------

            /**
             * returns the B-Spline IDs of this node
             */
            Matrix< IdMat >
            get_adof_ids() const
            {
                return mVertex->get_interpolation()->get_ids();
            }

 //------------------------------------------------------------------------------

            /**
             * returns the B-Spline IDs of this node
             */
            Matrix< IndexMat >
			get_adof_indices() const
			{
            	return mVertex->get_interpolation()->get_indices();
			}
//------------------------------------------------------------------------------

            /**
             * returns the proc owners of the IDs of this node
             */
            Matrix< IdMat >
            get_adof_owners() const
            {
                return mVertex->get_interpolation()->get_owners();
            }

//------------------------------------------------------------------------------

            /**
             * set the ID of this node
             *
             * @param[ in ] aID  id for this node
             */
            void
            set_id( const moris_id & aID )
            {
                mID = aID;
            }

//------------------------------------------------------------------------------

            /**
             * get the ID of this node
             *
             * @param[ in ] aID  id for this node
             */
            moris_id
            get_id() const
            {
                return mID;
            }

//------------------------------------------------------------------------------

            /**
             * set the ID of this node
             *
             * @param[ in ] aID  id for this node
             */
            void
            set_index( const moris_index & aIndex )
            {
                mIndex = aIndex;
            }

//------------------------------------------------------------------------------

            /**
             * get the Index of this node
             *
             * @param[ in ] aID  id for this node
             */
            moris_index
            get_index() const
            {
                return mIndex;
            }

//------------------------------------------------------------------------------
        };

//------------------------------------------------------------------------------
    } /* namespace MSI */
} /* namespace moris */



#endif /* PROJECTS_FEM_MSI_SRC_CL_MSI_NODE_HPP_ */