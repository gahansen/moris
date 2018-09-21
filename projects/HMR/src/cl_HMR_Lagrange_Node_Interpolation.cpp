#include "cl_HMR_Lagrange_Node_Interpolation.hpp"

namespace moris
{
    namespace hmr
    {
// ----------------------------------------------------------------------------

    void
    Lagrange_Node_Interpolation::set_weights( const Matrix< DDRMat > & aTMatrix )
    {
        mWeights = aTMatrix;
    }

// ----------------------------------------------------------------------------

    const Matrix< DDRMat > *
    Lagrange_Node_Interpolation::get_weights() const
    {
        return & mWeights;
    }

// ----------------------------------------------------------------------------

    void
    Lagrange_Node_Interpolation::set_coefficients(
            Cell< mtk::Vertex* > & aCoefficients )
    {
        mCoefficients = aCoefficients;
    }

// ----------------------------------------------------------------------------

    Cell< mtk::Vertex* > &
    Lagrange_Node_Interpolation::get_coefficients()
    {
        return mCoefficients;
    }

// ----------------------------------------------------------------------------

    const Cell< mtk::Vertex* > &
    Lagrange_Node_Interpolation::get_coefficients() const
    {
        return mCoefficients;
    }

// ----------------------------------------------------------------------------

    uint
    Lagrange_Node_Interpolation::get_number_of_coefficients() const
    {
        return mCoefficients.size();
    }

// ----------------------------------------------------------------------------

    Matrix< IdMat >
    Lagrange_Node_Interpolation::get_ids() const
    {
        // get number of basis
        uint tNumberOfBasis = this->get_number_of_coefficients();

        // allocate output matrix
        Matrix< IdMat > aIDs( tNumberOfBasis, 1 );

        // loop over all basis
        for( uint k=0; k<tNumberOfBasis; ++k )
        {
            aIDs( k ) = mCoefficients( k )->get_id();
        }

        // return id matrix
        return aIDs;
    }

// ----------------------------------------------------------------------------

    Matrix< IndexMat >
    Lagrange_Node_Interpolation::get_indices() const
    {
        // get number of basis
        uint tNumberOfBasis = this->get_number_of_coefficients();

        // allocate output matrix
        Matrix< IndexMat > aIndices( tNumberOfBasis, 1 );

        // loop over all basis
        for( uint k=0; k<tNumberOfBasis; ++k )
        {
            aIndices( k ) = mCoefficients( k )->get_index();
        }

        // return id matrix
        return aIndices;
    }

// ----------------------------------------------------------------------------

    Matrix< IdMat >
    Lagrange_Node_Interpolation::get_owners() const
    {
        // get number of basis
        uint tNumberOfBasis = this->get_number_of_coefficients();

        // allocate output matrix
        Matrix< IdMat > aOwners( tNumberOfBasis, 1 );

        // loop over all basis
        for( uint k=0; k<tNumberOfBasis; ++k )
        {
            aOwners( k ) = mCoefficients( k )->get_owner();
        }

        // return id matrix
        return aOwners;
    }

// ----------------------------------------------------------------------------
    } /* namespace hmr */
} /* namespace moris */
