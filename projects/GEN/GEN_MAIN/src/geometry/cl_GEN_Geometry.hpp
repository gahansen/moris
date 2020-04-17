/*
 * cl_GEN_Geometry.hpp
 *
 *  Created on: Jun 21, 2017
 *      Author: ktdoble
 */

#ifndef PROJECTS_GEN_GEN_MAIN_SRC_NEW_GEOMETRY_CL_GEN_GEOMETRY_HPP_
#define PROJECTS_GEN_GEN_MAIN_SRC_NEW_GEOMETRY_CL_GEN_GEOMETRY_HPP_


#include "cl_Matrix.hpp"
#include "cl_Mesh_Enums.hpp"

#include "fn_Exec_load_user_library.hpp"

#include "cl_GEN_Field.hpp"

namespace moris
{
namespace ge
{

/*
 * Any geometry must inherit either the discrete or analytic functions interfaces provided in include/geometry
 * For examples on creating analytic or discrete geometries see examples/cl_Geometry_Examples.cpp.
 */

class GEN_Geometry
{
public:

    virtual	
    ~GEN_Geometry()
    {
    }
    /*
     * **************************************************************************************
     *              REQUIRED INTERFACE FOR BOTH ANALYTIC AND DISCRETE GEOMETRY
     * **************************************************************************************
     */

    /*
     * @brief evaluates the analytic function defined in the input file
     */
    virtual void eval( moris::real                      & aReturnValue,
                       const moris::Matrix< DDRMat >    & aPoint,
                       const moris::Cell< moris::real > & aConst )
    {
        MORIS_ERROR( false, "GEN_Geometry::eval() - evaluation function not implemented for this geometry type" );
    }

    /**
     * This tells the user whether the given geometry is an analytical expression
     * @param[out] True if analytic geometry (i.e. Sphere from an equation)
     */
    virtual bool is_analytic() const = 0;

    virtual bool is_func_pointer()
    {
    	return false;
    }

    /**
     *
     */
    virtual void get_dphi_dp_size(moris::size_t & aNumRows, moris::size_t & aNumCols) const
    {
        MORIS_ERROR( false, "GEN_Geometry::get_dphi_dp_size() - not implemented for this geometry type " );
    }


    /*
     * **************************************************************************************
     *                             ANALYTIC GEOMETRY INTERFACE
     * **************************************************************************************
     */
    virtual
    moris::uint get_num_des_vars() const
    {
        MORIS_ERROR(0,"GEN_Geometry::get_num_des_vars() - not implemented");
        return 0;
    }

    /*
     * Given a node coordinate, the geometry needs to return the distance to the nearest function.
     */
    virtual moris::real evaluate_field_value_with_coordinate( moris::size_t const & aRowIndex,
                                                              moris::Matrix< moris::DDRMat > const & aCoordinates ) const
    {
        std::cout<<"GEN_Geometry::evaluate_field_value_with_coordinate() - not implemented. This could be due to a geometry not being based on an analytic expression.";
        return 0;
    }

    /*
     * Given a node coordinate @param[in] aCoordinates, the function returns a matrix of relevant node coordinates
     * Where each cell represents a design variable x,y,z vector
     */
    virtual moris::Matrix< moris::DDRMat > evaluate_sensitivity_dphi_dp_with_coordinate( moris::size_t const & aRowIndex,
                                                                                         moris::Matrix< moris::DDRMat > const & aCoordinates ) const
    {
        MORIS_ASSERT(false,"cl_GEN_Geometry::evaluate_sensitivity_dphi_dp_with_coordinate() - Not implemented. This could be due to a geometry not being based on an analytic expression.");
        return moris::Matrix< moris::DDRMat >();
    }


    /*
     * **************************************************************************************
     *                             DISCRETE GEOMETRY INTERFACE
     * **************************************************************************************
     */

    virtual GEN_Field* get_field_pointer()
    {
        MORIS_ASSERT(false, "GEN_Geometry::get_field_pointer() - not implemented");
        return new GEN_Field();
    }
    /*
     * Given a node index and rank, provide the field value or minimum distance to a geometry feature
     * NOTE: THIS CURRENTLY REQUIRES THE BACKGROUND MESH AND GEOMETRY ARE COINCIDENT (NEEDS AN OBJECT THAT MAPS BETWEEN THE TWO)
     */
    virtual moris::real access_field_value_with_entity_index(
                moris::moris_index     aEntityIndex,
                enum moris::EntityRank aEntityRank) const
    {
        MORIS_ASSERT(false, " access_field_value_with_entity_index not implemented. This could be due to a geometry not being based on a mesh.");
        return 0;
    }


    /*
     * Given a local coordinate, node index and entity rank, the function returns a matrix of relevant node coordinates
     *  NOTE: THIS CURRENTLY REQUIRES THE BACKGROUND MESH AND GEOMETRY ARE COINCIDENT (NEEDS AN OBJECT THAT MAPS BETWEEN THE TWO)
     */
    virtual
    moris::Matrix< moris::DDRMat >
    evaluate_sensitivity_dphi_dp(moris::Matrix< moris::DDRMat > const & aLocalCoordinate, moris::size_t aEntityIndex, enum moris::EntityRank aEntityRank)
    {
//        std::cout<<" evaluate_sensitivity_dx_dp not implemented. This could be due to a geometry not being based on a mesh.";
        return moris::Matrix< moris::DDRMat >(1,1,0);
    }

    /*
     * Returns the advs that the provided node indices are dependent on
     */
     virtual moris::Matrix< moris::IndexMat > get_node_adv_indices(moris::Matrix< moris::IndexMat > const & aNodeIndices)
    {
         std::cout<<" get_node_adv_indices not implemented, This could be due to a geometry not being based on a mesh.";
         return moris::Matrix< moris::IndexMat >(1,1,0);
    }



};
}
}



#endif /* PROJECTS_GEN_GEN_MAIN_SRC_NEW_GEOMETRY_CL_GEN_GEOMETRY_HPP_ */