/*
 * cl_NLA_Solver_Interface_Proxy.cpp
 *
 *  Created on: Jun 18, 2018
 *      Author: schmidt
 */
#include "cl_NLA_Solver_Interface_Proxy.hpp"
#include "cl_Communication_Tools.hpp" // COM/src
#include "cl_NLA_Newton_Solver.hpp"
#include "cl_Vector.hpp"

using namespace moris;
using namespace NLA;

NLA_Solver_Interface_Proxy::NLA_Solver_Interface_Proxy()
{
}

NLA_Solver_Interface_Proxy::NLA_Solver_Interface_Proxy( const moris::uint aNumMyDofs,
                                                        const moris::uint aNumElements,
                                                        const moris::sint aNX,
                                                        const moris::sint aNY,
                                                        Matrix< DDRMat > ( *aFunctionRes )( const moris::sint aNX, const moris::sint aNY, Matrix< DDRMat > tMyValues, const moris::uint aEquationObjectInd ),
                                                        Matrix< DDRMat > ( *aFunctionJac )( const moris::sint aNX, const moris::sint aNY, Matrix< DDRMat > tMyValues, const moris::uint aEquationObjectInd ),
                                                        Matrix< DDSMat > ( *aFunctionTopo )( const moris::sint aNX, const moris::sint aNY, const moris::uint aEquationObjectInd ) )
{
    mUseMatrixMarketFiles = false;

    mFunctionRes = aFunctionRes;
    mFunctionJac = aFunctionJac;
    mFunctionTopology = aFunctionTopo;

    mNX = aNX;
    mNY = aNY;

    mNumMyDofs = aNumMyDofs;
    mNumElements = aNumElements;

    mMyGlobalElements.resize( mNumMyDofs, 1 );
    for ( moris::uint Ik = 0; Ik < mNumMyDofs; Ik++ )
    {
        mMyGlobalElements( Ik, 0 ) = Ik;
    }
}

void NLA_Solver_Interface_Proxy::set_solution_vector( Dist_Vector * aSolutionVector )
{
    mSolutionVector = aSolutionVector;

    mSolutionVector->extract_copy( mMySolVec );
}

