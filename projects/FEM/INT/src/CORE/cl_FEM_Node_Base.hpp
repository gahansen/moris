/*
 * Copyright (c) 2022 University of Colorado
 * Licensed under the MIT license. See LICENSE.txt file in the MORIS root for details.
 *
 *------------------------------------------------------------------------------------
 *
 * cl_FEM_Node_Base.hpp
 *
 */

#ifndef PROJECTS_FEM_SRC_CL_FEM_NODE_BASE_HPP_
#define PROJECTS_FEM_SRC_CL_FEM_NODE_BASE_HPP_

#include "typedefs.hpp"
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_MTK_Vertex.hpp"      //MTK/src
#include "cl_GEN_Pdv_Enums.hpp"

namespace moris
{
    namespace fem
    {
        class Node_Base
        {
            private:
                moris_index mNodeIndex;
                moris_index mNodeId;

                //------------------------------------------------------------------------------

                //------------------------------------------------------------------------------
            public:
                //------------------------------------------------------------------------------

                /**
                 * destructor
                 */
                virtual
                ~Node_Base(){};

                //------------------------------------------------------------------------------

                /**
                 * returns the T-Matrix of this node
                 */

                virtual const Matrix< DDRMat > *
                get_t_matrix(  const uint aOrder ) const
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::get_t_matrix()" );
                    return nullptr;
                }

                //------------------------------------------------------------------------------

                virtual Matrix< IdMat >
                get_adof_ids( const uint aOrder ) const
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::get_adof_ids()" );
                    return  Matrix< IdMat >(0,0);
                }

                //------------------------------------------------------------------------------

                virtual Matrix< IndexMat >
                get_adof_indices(  const uint aOrder ) const
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::get_adof_indices()" );
                    return  Matrix< IndexMat >(0,0);
                }

                //------------------------------------------------------------------------------

                /**
                 * returns the proc owners of the IDs of this node
                 */

                virtual Matrix< IdMat >
                get_adof_owners(  const uint aOrder ) const
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::get_adof_owners()" );
                    return  Matrix< IdMat >(0,0);
                }

                //------------------------------------------------------------------------------

                /**
                 * get the ID of this node
                 *
                 */

                virtual moris_id
                get_id() const
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::get_id()" );
                    return gNoID;
                }

                //------------------------------------------------------------------------------

                /**
                 * get the ID of this node
                 *
                 */

                virtual moris_index
                get_index() const
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::get_index()" );
                    return gNoIndex;
                }

                //------------------------------------------------------------------------------

                /**
                 * set the ID of this node
                 *
                 * @param[ in ] aID  id for this node
                 */

                void
                set_id( const moris_id aId )
                {
                    mNodeId = aId;
                }

                //------------------------------------------------------------------------------

                /**
                 * set the index of this node
                 *
                 * @param[ in ] aIndex  id for this node
                 */

                void
                set_index( const moris_id aIndex )
                {
                    mNodeIndex = aIndex;
                }

                //------------------------------------------------------------------------------

                /**
                 * set the index of this node
                 *
                 * @param[ in ] aIndex  id for this node
                 */

                virtual bool
                id_owned(  )
                {
                    MORIS_ERROR( false, "Enterd virtual function Node_Base::id_owned()" );
                    return false;
                }

                //------------------------------------------------------------------------------
                /**
                 * get vertex coordinates (if relevant)
                 * @param[ out ] aIndex  id for this node
                 */
                virtual void get_vertex_coords( Matrix< DDRMat > & aVertexCoords )
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::get_vertex_coords()" );
                }

                //------------------------------------------------------------------------------
                /**
                 * get vertex active flags (if relevant)
                 * @param[ out ] aPdvTypes
                 * @param[ out ] aIsActiveDv
                 */
                virtual void get_vertex_xyz_active_flags(
                        Matrix< DDSMat >                    & aIsActiveDv,
                        const moris::Cell < enum PDV_Type > & aPdvTypes )
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::get_vertex_active_flags()" );
                }

                //------------------------------------------------------------------------------
                /**
                 * set vertex active flags (if relevant)
                 * @param[ out ] aIsActiveDv
                 */
                virtual void set_vertex_xyz_active_flags(
                        moris::Cell< Matrix< DDSMat > > & aIsActiveDv )
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::set_vertex_active_flags()" );
                }

                //------------------------------------------------------------------------------
                /**
                 * get vertex pdv ids (if relevant)
                 * @param[ out ] aPdvTypes
                 * @param[ out ] aIsActiveDv
                 */
                virtual void get_vertex_xyz_pdv_ids(
                        Matrix< DDSMat >                    & aXYZPdvIds,
                        const moris::Cell < enum PDV_Type > & aPdvTypes )
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::get_vertex_xyz_pdv_ids()" );
                }

                //------------------------------------------------------------------------------
                /**
                 * set vertex active flags (if relevant)
                 * @param[ out ] aIsActiveDv
                 */
                virtual void set_vertex_xyz_pdv_ids(
                        moris::Cell< Matrix< DDSMat > > & aXYZPvIds )
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::set_vertex_xyz_pdv_ids()" );
                }

                virtual void set_local_xyz_pdv_assembly_index(
                        moris_index   aLocalPdvAssemblyIndex,
                        enum PDV_Type aPdvType )
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::set_local_xyz_pdv_assembly_index()" );
                }

                virtual void reset_local_xyz_pdv_assembly_index()
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::reset_local_xyz_pdv_assembly_index()" );
                }

                virtual void get_local_xyz_pdv_assembly_indices(
                                        Matrix< DDSMat >                    & aXYZLocalAssemblyIndices,
                                        const moris::Cell < enum PDV_Type > & aPdvTypes )
                {
                    MORIS_ERROR( false, "Entered virtual function Node_Base::get_local_xyz_pdv_assembly_indices()" );
                }

                //------------------------------------------------------------------------------

        };
    } /* namespace fem */
} /* namespace moris */

#endif /* PROJECTS_FEM_SRC_CL_FEM_NODE_BASE_HPP_ */

