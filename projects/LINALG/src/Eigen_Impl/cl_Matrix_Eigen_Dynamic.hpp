/*
 * cl_Matrix_Eigen_Dynamic.hpp
 *
 *  Created on: Aug 24, 2018
 *      Author: doble
 */

#ifndef PROJECTS_LINALG_SRC_EIGEN_IMPL_CL_MATRIX_EIGEN_DYNAMIC_HPP_
#define PROJECTS_LINALG_SRC_EIGEN_IMPL_CL_MATRIX_EIGEN_DYNAMIC_HPP_

#include "cl_Matrix.hpp"
#include "Eigen/Dense"

namespace moris
{
template<typename Type>
class Mat_New<Type, Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic>>
{
private:
    Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic> mMatrix;

public:
    Mat_New()
    {

    };

    Mat_New(size_t const & aNumRows,
            size_t const & aNumCols):
                mMatrix(aNumRows,aNumCols)
    {

    }

    // template constructor
    Mat_New(Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic> const & X ):
                mMatrix(X)
     {

     }


    // template constructor
    template< typename A >
    Mat_New(A const & X ):
                mMatrix(X)
     {

     }

    Mat_New(size_t const & aNumRows,
        size_t const & aNumCols,
        Type   const & aFillVal):
            mMatrix( aNumRows, aNumCols )
    {
        mMatrix.fill(aFillVal);
    }

    Mat_New(std::initializer_list<std::initializer_list<Type> > const & aInitList)
    {
        size_t i = 0;
        size_t j = 0;
        size_t tNumRows = aInitList.size();
        size_t tNumColumns = aInitList.begin()->size();

        mMatrix = Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic>(tNumRows, tNumColumns);

        for(const auto tRow : aInitList) // loop over number of rows
        {
            MORIS_ASSERT(tRow.size() == aInitList.begin()->size(),
                       "The number of elements in one of the rows does not equal the number of columns.");

            for(const auto tCol : tRow) // loop over every value in the row
            {
                mMatrix(i, j) = tCol;
                ++j;
            }
            j = 0;
            ++i;
        }
    }

    // Copy operations
    Mat_New<Type,Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic>>
    copy()
    {
        Mat_New<Type,Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic>> tMatCopy(this->n_rows(),this->n_cols());
        tMatCopy.matrix_data() = mMatrix;
        return tMatCopy;
    }

    void
    resize(const size_t & aNumRows,
           const size_t & aNumCols)
    {
        mMatrix.conservativeResize(aNumRows, aNumCols);
    }

    void
    fill(const Type & aFillValue)
    {
        mMatrix.fill(aFillValue);
    }


    /**
     * Get the number of columns in a data set, similar to Matlab cols().
     *
     * @return Number of columns.
     */
    size_t
    n_cols() const
    {
        return mMatrix.cols();
    }

    /**
     * Get the number of rows in a data set, similar to Matlab rows().
     *
     * @return Number of rows.
     */
    size_t
    n_rows() const
    {
        return mMatrix.rows();
    }

    /**
     * Returns the number of elements in the %matrix.
     *
     * @return Number of elements in the %matrix.
     *
     */
    size_t
    numel() const
    {
        return mMatrix.size();
    }

    void set_row(size_t aRowIndex, Mat_New<Type, Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic>> & aRow)
    {
        MORIS_ASSERT(aRow.n_rows() == 1, "aRow needs to be a row matrix");
        MORIS_ASSERT(aRowIndex < this->n_rows(), "Specified row index out of bounds");
        MORIS_ASSERT(aRow.n_cols() == this->n_cols(),
                   "Dimension mismatch (argument matrix and member matrix do not have same number of columns)");

        size_t tROW_INDEX = 0;
        mMatrix.row(aRowIndex) = aRow.matrix_data().row(tROW_INDEX);
    }

    void set_column(size_t aColumnIndex, Mat_New<Type, Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic>> & aColumn)
    {

        MORIS_ASSERT(aColumn.n_cols() == 1, "aColumn needs to be a column matrix");
        MORIS_ASSERT(aColumnIndex < this->n_cols(), "Specified column index out of bounds");
        MORIS_ASSERT(aColumn.n_rows() == this->n_rows(),
                   "Dimension mismatch (argument matrix and member matrix do not have same number of rows)");

        size_t tCOLUMN_INDEX = 0;
        mMatrix.col(aColumnIndex) = aColumn.matrix_data().col(tCOLUMN_INDEX);
    }


    void
    get_column(size_t aColumnIndex,
               Mat_New<Type, Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic>> & aColumn) const
    {
        MORIS_ASSERT(aColumn.n_cols() == 1,"aColumn needs to be a column matrix");
        MORIS_ASSERT(aColumnIndex < this->n_cols(),"Specified column index out of bounds");
        MORIS_ASSERT(aColumn.n_rows() == this->n_rows(),"Dimension mismatch (argument matrix and member matrix do not have same number of rows)");
        const size_t tCOLUMN_INDEX = 0;
        aColumn.matrix_data().col(tCOLUMN_INDEX) = mMatrix.col(aColumnIndex);
    }

    Mat_New<Type, Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic>>
    get_column(size_t aColumnIndex) const
    {
        MORIS_ASSERT(aColumnIndex < this->n_cols(),"Specified column index out of bounds");
        const size_t tCOLUMN_INDEX = 0;
        return mMatrix.col(aColumnIndex);
    }

    void get_row(size_t aRowIndex, Mat_New<Type, Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic>> & aRow) const
    {
        MORIS_ASSERT(aRow.n_rows() == 1,"aRow needs to be a row matrix");
        MORIS_ASSERT(aRowIndex < this->n_rows(),"Specified row index out of bounds");
        MORIS_ASSERT(aRow.n_cols() == this->n_cols(),"Dimension mismatch (argument matrix and member matrix do not have same number of columns)");

        const size_t tROW_INDEX = 0;
        aRow.mMatrix.row(tROW_INDEX) = mMatrix.row(aRowIndex);
    }

    Mat_New<Type, Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic>>
    get_row(size_t aRowIndex) const
    {
        MORIS_ASSERT(aRowIndex < this->n_rows(),"Specified row index out of bounds");
        const size_t tROW_INDEX = 0;
        return mMatrix.row(aRowIndex);
    }


    const Type*
    data() const
    {
        return mMatrix.data();
    }

    inline
    Eigen::Matrix<Type, Eigen::Dynamic, Eigen::Dynamic> &
    matrix_data()
    {
        return mMatrix;
    }

    Type
    max() const
    {
        return mMatrix.maxCoeff( );
    }

    Type
    min() const
    {
         return mMatrix.minCoeff( ) ;
    }

    /**
     * @brief Overloaded moris::Matrix_Base::operator()
     *
     * @param[in] aRowIndex Row index for which data should be accessed.
     * @param[in] aColIndex Column index for which data should be accessed.
     */
    inline
    Type &
    operator()( size_t const & aRowIndex,
                size_t const & aColIndex )
    {
        return mMatrix(aRowIndex,aColIndex);
    }

    /**
     * @brief Overloaded moris::Matrix_Base::operator()
     *
     * @param[in] aRowIndex Row index for which data should be accessed.
     * @param[in] aColIndex Column index for which data should be accessed.
     */
    const Type &
    operator()(const size_t & aRowIndex,
               const size_t & aColIndex) const
    {
        return mMatrix(aRowIndex,aColIndex);
    }


};
}


#endif /* PROJECTS_LINALG_SRC_EIGEN_IMPL_CL_MATRIX_EIGEN_DYNAMIC_HPP_ */
