/*
 * cl_Solver_Input_Test.hpp
 *
 *  Created on: Jun 18, 2018
 *      Author: schmidt
 */
#ifndef SRC_DISTLINALG_CL_SOLVER_INPUT_TEST_HPP_
#define SRC_DISTLINALG_CL_SOLVER_INPUT_TEST_HPP_

#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_Solver_Input.hpp"

namespace moris
{
class Solver_Input_Test : public Solver_Input
{
private:
    moris::uint mNumMyDofs;                           // local dimension of the problem
    moris::Matrix< DDSMat > mMyGlobalElements;             // local-to-global map
    moris::uint mNumElements;                         // number local elements
    moris::Matrix< DDSMat > mEleDofConectivity;             // element - dof conectivities
    moris::Matrix< DDRMat > mElementMatrixValues;   // dense element matrix entries
    moris::uint mNumDofsPerElement;                   // dofs per element
    moris::Matrix< DDUMat > mMyConstraintDofs;     // constraint dofs
    moris::Matrix< DDRMat > mMyRHSValues;          // Vector with RHS values

    bool mUseMatrixMarketFiles;                       // determines is matrix and RHS comes from MatrixMarket files

public :
    Solver_Input_Test();

    // ----------------------------------------------------------------------------------------------
    ~Solver_Input_Test(){};

    // ----------------------------------------------------------------------------------------------
    // local dimension of the problem
    uint get_num_my_dofs(){ return mNumMyDofs; };

    // ----------------------------------------------------------------------------------------------
    // local-to-global map
    Matrix< DDSMat > get_my_local_global_map(){ return mMyGlobalElements; };

    // ----------------------------------------------------------------------------------------------
    // element dofs
    uint get_num_element_dof(){return mNumDofsPerElement; };

    // ----------------------------------------------------------------------------------------------
    // number of elements on proc
    uint get_num_my_elements(){return mNumElements; };

    // ----------------------------------------------------------------------------------------------
    void get_element_matrix(const uint  & aMyElementInd,
                            Matrix< DDRMat > & aElementMatrix)
    { aElementMatrix = mElementMatrixValues; };

    // ----------------------------------------------------------------------------------------------
    void  get_element_topology(const uint             & aMyElementInd,
                                     Matrix< DDSMat > & aElementTopology)
    { aElementTopology = mEleDofConectivity; };

    // ----------------------------------------------------------------------------------------------
    Matrix< DDUMat > get_constr_dof(){ return mMyConstraintDofs; };

    // ----------------------------------------------------------------------------------------------
    void get_element_rhs(const uint            & aMyElementInd,
                         Matrix< DDRMat >           & aElementRHS )
    { aElementRHS = mMyRHSValues; };

    // ----------------------------------------------------------------------------------------------

    void use_matrix_market_files( )
    {
        mUseMatrixMarketFiles = true;
    };

    // ----------------------------------------------------------------------------------------------

    const char* get_matrix_market_path( )
    {
        if ( mUseMatrixMarketFiles == true )
        {
            const char* tFilePath ="/home/schmidt/codes/MORIS/test/src/distlinalg/";
            return tFilePath;
        }
        else
        {
            return NULL;
        }
    };
};
}
#endif /* SRC_DISTLINALG_CL_SOLVER_INPUT_TEST_HPP_ */
