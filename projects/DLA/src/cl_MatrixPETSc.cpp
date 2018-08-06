/*
 * MatrixPETSc.cpp
 *
 *  Created on: Jan 10, 2018
 *      Author: schmidt
 */
#include "cl_MatrixPETSc.hpp"

#include <cstddef>
#include <cassert>
#include <algorithm>
#include <iostream>

// TPL header files

// ----------------------------------------------------------------------------
Matrix_PETSc::Matrix_PETSc(       moris::Solver_Input * aInput,
                            const moris::Map_Class    * aMap ) : Sparse_Matrix( aMap )
{
    moris::uint               aNumMyDofs          = aInput->get_num_my_dofs();
    moris::Mat< int >         aMyLocaltoGlobalMap = aInput->get_my_local_global_map();
    moris::Mat< moris::uint > aMyConstraintDofs   = aInput->get_constr_dof();

    // Fixme Implement nonzero algorithm
    PetscInt     tNonzeros =16;
    PetscInt     tNumMyDofs = aNumMyDofs;
    moris::uint tNumGlobalDofs=  aNumMyDofs;

    // sum up all distributed dofs
#ifdef MORIS_HAVE_PARALLEL
        MPI_Allreduce(&aNumMyDofs,&tNumGlobalDofs,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
#endif

    //FIXME insert boolian array for BC-- insert NumGlobalElements-- size
    DirichletBCVec.set_size( tNumGlobalDofs, 1, 0 );

    // build BC vector
    this->dirichlet_BC_vector( DirichletBCVec, aMyConstraintDofs );

    // Build PETSc AO map
    //mPETScMap = new Map_PETSc( aNumMyDofs, aMyLocaltoGlobalMap, aMyConstraintDofs );

    // Create and set Matrix
    MatCreate( PETSC_COMM_WORLD, &mPETScMat );

    MatSetSizes( mPETScMat, tNumMyDofs, tNumMyDofs, PETSC_DETERMINE, PETSC_DETERMINE );
    MatSetFromOptions( mPETScMat );
    MatMPIAIJSetPreallocation( mPETScMat, tNonzeros, NULL, tNonzeros, NULL );

    //FIXME extra matrix for serial (performance)
    //MatSeqAIJSetPreallocation(mPETScMat, tNonzeros, NULL);

    MatSetUp( mPETScMat );
}

// ----------------------------------------------------------------------------
Matrix_PETSc::~Matrix_PETSc()
{
    MatDestroy( &mPETScMat );
}

void Matrix_PETSc::fill_matrix( const moris::uint               & aNumMyDof,
                                const moris::Mat< moris::real > & aA_val,
                                const moris::Mat< int >         & aEleDofConectivity)
{
    moris::Mat< int >tTempElemDofs( aNumMyDof, 1 );
    tTempElemDofs = aEleDofConectivity;

    //loop over elemental dofs
        for ( moris::uint Ij=0; Ij< aNumMyDof; Ij++ )
        {
            //set constrDof to neg value
            if ( DirichletBCVec( aEleDofConectivity(Ij,0),   0) == 1 )
             {
                 tTempElemDofs( Ij, 0 ) = -1;
             }
        }

    // Applying Petsc map AO
    AOApplicationToPetsc( mMap->get_petsc_map(), aNumMyDof, mem_pointer( tTempElemDofs ) );

    MatSetValues( mPETScMat, aNumMyDof, mem_pointer( tTempElemDofs ), aNumMyDof, mem_pointer( tTempElemDofs ), mem_pointer( aA_val ), ADD_VALUES );
    //MatSetValuesBlocked();                                                      //important+
}

void Matrix_PETSc::matrix_global_asembly()
{
    MatAssemblyBegin( mPETScMat, MAT_FINAL_ASSEMBLY );
    MatAssemblyEnd( mPETScMat, MAT_FINAL_ASSEMBLY );

    //MatView(A, PETSC_VIEWER_STDOUT_(PETSC_COMM_WORLD) );
}

void Matrix_PETSc::dirichlet_BC_vector(       moris::Mat< moris::uint > & aDirichletBCVec,
                                        const moris::Mat< uint >        & aMyConstraintDofs )
{
    //build vector with constraint values. unconstraint=0 constraint =1. change this to true/false
    for ( moris::uint Ik=0; Ik< aMyConstraintDofs.n_rows(); Ik++ )
    {
        aDirichletBCVec( aMyConstraintDofs( Ik, 0 )     ,0 )  = 1;
    }
}
