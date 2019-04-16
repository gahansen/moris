/*
 * cl_DLA_Solver_Interface.hpp
 *
 *  Created on: Apr 6, 2018
 *      Author: schmidt
 */

#ifndef SRC_DISTLINALG_CL_SOLVER_INPUT_HPP_
#define SRC_DISTLINALG_CL_SOLVER_INPUT_HPP_

#include "cl_Matrix.hpp"
#include "cl_Cell.hpp"
#include "linalg_typedefs.hpp"

#include "cl_DLA_Geometric_Multigrid.hpp"

namespace moris
{
    class Dist_Vector;
    class Sparse_Matrix;

    namespace mtk
    {
        class Mesh;
    }

    namespace MSI
    {
        enum class Dof_Type;
    }

    class Solver_Interface
{
private:
        dla::Geometric_Multigrid * mGeoMultigrid;

        // Dummy member variable
        moris::Matrix< DDUMat >                        mMat1;
        moris::Matrix< DDSMat >                        mMat5;
        moris::Cell< Matrix< DDUMat > >                mMat2;
        moris::Cell< Matrix< DDSMat > >                mMat3;
        moris::Cell< moris::Cell< Matrix< DDSMat > > > mMat4;

public:
    /** Destructor */
    virtual ~Solver_Interface(){};

    virtual void set_solution_vector( Dist_Vector * aSolutionVector )
    { MORIS_ERROR( false, "Solver_Interface::set_solution_vector: not set."); };

    void set_time_levels_for_type( const enum MSI::Dof_Type aDofType,
                                   const moris::uint   aNumTimeLevels )
    { MORIS_ERROR( false, "Solver_Interface::set_solution_vector: not set."); };

    virtual void set_solution_vector_prev_time_step( Dist_Vector * aSolutionVector )
    { MORIS_ERROR( false, "Solver_Interface::set_solution_vector: not set."); };

    virtual void set_time( const Matrix< DDRMat> & aTime )
    { MORIS_ERROR( false, "Solver_Interface::set_solution_vector: not set."); };

    virtual void set_requested_dof_types( const moris::Cell< enum MSI::Dof_Type > aListOfDofTypes )
    { MORIS_ERROR( false, "Solver_Interface::set_requested_dof_types: not set."); };

    // local dimension of the problem
    virtual moris::uint             get_num_my_dofs()         =0;

    virtual uint get_max_num_global_dofs() = 0;

    // local-to-global map
    virtual moris::Matrix< DDSMat > get_my_local_global_map() =0;

    virtual moris::Matrix< DDSMat > get_my_local_global_overlapping_map( )
    {
        moris::Matrix< DDSMat > aMat;
        //MORIS_ERROR( false, "Solver_Interface::get_my_local_global_overlapping_map(): Virtual class not overwritten" );
        return aMat;
    };

    // number local elements
    virtual moris::uint             get_num_my_elements()     =0;

    virtual moris::Matrix< DDUMat > get_constr_dof()          =0;

    virtual moris::Matrix< DDSMat > & get_time_level_Ids_minus()
    {
        MORIS_ERROR( false, "Solver_Interface::get_time_level_Ids_minus: not set.");
        return mMat5;
    };

    virtual moris::Matrix< DDSMat > & get_time_level_Ids_plus()
    {
        MORIS_ERROR( false, "Solver_Interface::get_time_level_Ids_plus: not set.");
        return mMat5;
    };

    virtual void get_element_matrix(const moris::uint             & aMyElementInd,
                                          moris::Matrix< DDRMat > & aElementMatrix) =0;

    virtual void get_element_topology(const moris::uint             & aMyElementInd,
                                            moris::Matrix< DDSMat > & aElementTopology) =0;

    virtual void get_element_rhs(const moris::uint             & aMyElementInd,
                                       moris::Matrix< DDRMat > & aElementRHS ) =0;

    //------------------------------------------------------------
    virtual void set_lambda_value( const moris::real & aLambda )
    {
        MORIS_ERROR( false, "Solver_Interface::set_lambda_value: not set.");
    }
    //------------------------------------------------------------

    virtual void use_matrix_market_files( ) { MORIS_ERROR(false,"error in use_matrix_market_files"); }

    virtual const char * get_matrix_market_path( )
    {
        //assert(0);
        return NULL;
    }

    virtual mtk::Mesh * get_mesh_pointer_for_multigrid()
    {
        MORIS_ERROR(false, "Solver_Interface::get_mesh_pointer_for_multigrid, Only works with MSI and multigrid");
        return nullptr;
    };

//------------------------------------------------------------------------------
    virtual void read_multigrid_maps( const moris::uint               aLevel,
                                      const moris::Matrix< DDSMat > & aExtFineIndices,
                                      const moris::sint               aTypeTimeIdentifier,
                                            moris::Matrix< DDSMat > & aInternalFineIndices )
    {
        MORIS_ERROR(false, "Solver_Interface::read_multigrid_maps, Only works with MSI and multigrid");
    };

//------------------------------------------------------------------------------
    virtual const moris::Cell< Matrix< DDUMat > > & get_lists_of_ext_index_multigrid()
    {
        MORIS_ERROR(false, "Solver_Interface::get_lists_of_ext_index_multigrid, Only works with MSI and multigrid");
        return mMat2;
    };

    virtual const moris::Cell< Matrix< DDSMat > > & get_lists_of_multigrid_identifiers()
    {
        MORIS_ERROR(false, "Solver_Interface::get_lists_of_ext_index_multigrid, Only works with MSI and multigrid");
        return mMat3;
    };

    virtual const moris::Cell< moris::Cell< Matrix< DDSMat > > > & get_multigrid_map( )
    {
        MORIS_ERROR(false, "Solver_Interface::get_multigrid_map, Only works with MSI and multigrid");
        return mMat4;
    };


    virtual const moris::Matrix< DDUMat > & get_number_remaining_dofs()
    {
        MORIS_ERROR(false, "Solver_Interface::get_number_remaining_dofs, Only works with MSI and multigrid");
        return mMat1;
    };

//------------------------------------------------------------------------------
    void build_multigrid_operators()
    {
        mGeoMultigrid = new dla::Geometric_Multigrid( this );
    };

    dla::Geometric_Multigrid * get_multigrid_operator_pointer()
    {
        return mGeoMultigrid;
    };

//---------------------------------------------------------------------------------------------------------
    void build_graph( moris::Sparse_Matrix * aMat );

//---------------------------------------------------------------------------------------------------------
    void fill_matrix_and_RHS( moris::Sparse_Matrix * aMat,
                              moris::Dist_Vector   * aVectorRHS );

//---------------------------------------------------------------------------------------------------------
    void fill_matrix_and_RHS( moris::Sparse_Matrix * aMat,
                              moris::Dist_Vector   * aVectorRHS,
                              moris::Dist_Vector   * aFullSolutionVector );

    void assemble_jacobian( moris::Sparse_Matrix * aMat,
                            moris::Dist_Vector   * aFullSolutionVector );

    void assemble_RHS( moris::Dist_Vector * aVectorRHS,
                       moris::Dist_Vector * aFullSolutionVector );
};
}


#endif /* SRC_DISTLINALG_CL_SOLVER_INPUT_HPP_ */
