/*
 * cl_XTK_Multigrid.hpp
 *
 *  Created on: Mar 04, 2020
 *      Author: schmidt
 */

#ifndef XTK_SRC_XTK_CL_XTK_MULTIGRID_HPP_
#define XTK_SRC_XTK_CL_XTK_MULTIGRID_HPP_

// XTKL: Linalg Includes
#include "cl_Matrix.hpp"
#include "cl_XTK_Matrix_Base_Utilities.hpp"

// Std includes
#include <limits>

// XTKL: XTK Includes
#include "cl_Cell.hpp"
#include "cl_XTK_Model.hpp"
#include "cl_XTK_Child_Mesh.hpp"
#include "cl_XTK_Cut_Mesh.hpp"
#include "fn_Pairing.hpp"
#include "fn_equal_to.hpp"

// Mesh includes
#include "cl_MTK_Mesh.hpp"
#include "cl_MTK_Cell.hpp"
#include "cl_Mesh_Enums.hpp"
#include "cl_XTK_Background_Mesh.hpp"
#include "cl_Mesh_Enums.hpp"

#include "fn_unique.hpp"

namespace xtk
{

class Model;

class Multigrid
{
private:

    xtk::Model * mXTKModelPtr = nullptr;

    moris::Cell< moris_index > mEnrichedBasisToBackgroundBasis;

    moris::Cell< moris::Matrix< DDSMat > > mFineBasisToCoarseBasis;
    moris::Cell< moris::Matrix< DDSMat > > mCoarseBasisToFineBasis;
    moris::Cell< moris::Matrix< DDRMat > > mCoarseBasisToFineBasisWeights;

    moris::Matrix< DDRMat >                mEnrichedBasisLevel;

    uint mNumBasis;

public:
    Multigrid(){};

//------------------------------------------------------------------------------

    Multigrid( xtk::Model * aModel );


//------------------------------------------------------------------------------

    ~Multigrid(){};

//------------------------------------------------------------------------------

    void create_fine_to_coarse_relationship();

//------------------------------------------------------------------------------

    void create_coarse_to_fine_relationship();

//------------------------------------------------------------------------------

    void create_coarse_to_fine_weights();

//------------------------------------------------------------------------------

    void build_enriched_coeff_to_background_coeff_map();

//------------------------------------------------------------------------------

    uint get_num_interpolations()
    {
        return 1;
    };

//-------------------------------------------------------------------------------

    uint get_max_level( const moris_index aInterpolationIndex )
    {
        moris::mtk::Interpolation_Mesh & tInterpolationMesh = mXTKModelPtr->get_background_mesh().get_mesh_data();

        return tInterpolationMesh.get_max_level( aInterpolationIndex );
    };

//-------------------------------------------------------------------------------

    uint get_num_basis( const moris_index aInterpolationIndex )
    {
        return mNumBasis;
    }

//-------------------------------------------------------------------------------

    uint get_basis_level( const moris_index aInterpolationIndex,
                          const moris_index aBasisIndex )
    {
        return mEnrichedBasisLevel( aBasisIndex );
    }

//-------------------------------------------------------------------------------

    uint get_num_coarse_basis_of_basis( const moris_index aInterpolationIndex,
                                        const moris_index aBasisIndex )
    {
        return mFineBasisToCoarseBasis( aBasisIndex ).numel();
    }

//-------------------------------------------------------------------------------

    uint get_coarse_basis_index_of_basis( const moris_index aInterpolationIndex,
                                          const moris_index aBasisIndex,
                                          const moris_index aCoarseParentIndexForBasis )
    {
        return mFineBasisToCoarseBasis( aBasisIndex )( aCoarseParentIndexForBasis );
    }

//-------------------------------------------------------------------------------

    moris::Matrix< DDSMat > get_fine_basis_inds_of_basis( const moris_index aInterpolationIndex,
                                                          const moris_index aBasisIndex )
    {
        return mCoarseBasisToFineBasis( aBasisIndex );
    }

//-------------------------------------------------------------------------------

    moris::Matrix< DDRMat > get_fine_basis_weights_of_basis( const moris_index aInterpolationIndex,
                                                             const moris_index aBasisIndex )
    {
        return mCoarseBasisToFineBasisWeights( aBasisIndex );
    }

//-------------------------------------------------------------------------------

#ifdef DEBUG
    void save_to_vtk( const std::string & aFilePath );
#endif
//------------------------------------------------------------------------------

    void build_basis_exodus_information();

//------------------------------------------------------------------------------

#ifdef DEBUG
private:
    moris::Cell< moris::Matrix< DDRMat > > mEnrichedBasisCoords;

    moris::Matrix< DDRMat >             mEnrichedBasisStatus;
#endif




};
}
#endif /* XTK_SRC_XTK_CL_XTK_MULTIGRID_HPP_ */
