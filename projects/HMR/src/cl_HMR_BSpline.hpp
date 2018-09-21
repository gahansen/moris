/*
 * cl_HMR_Lagrange_Node.hpp
 *
 *  Created on: June 12, 2018
 *      Author: messe
 */

#ifndef SRC_HMR_CL_HMR_BSPLINE_HPP_
#define SRC_HMR_CL_HMR_BSPLINE_HPP_

#include "cl_HMR_Basis.hpp" //HMR/src

namespace moris
{
    namespace hmr
    {
//------------------------------------------------------------------------------
        /**
         * \brief BSpline Class
         *
         * uint N: number of dimensions (1, 2, or 3)
         * uint C: number of children   ( (P+2)^N)
         */
        template< uint N, uint C, uint B  >
        class BSpline : public Basis
        {
            //! memory position in active cell
            luint   mActiveIndex = gNoEntityID;

            //! local ijk position on proc
            luint   mIJK[ N ];

            //! global coordinates
            real    mXYZ[ N ] = { 0 };

            //! flag telling if the basis is active
            bool    mActiveFlag = false;

            //! flag telling if the basis is refined
            bool    mRefinedFlag = false;

            //! flag that tells if the Neighbor array is allocated
            bool    mNeighborsFlag = false;

            //! flag that tells of the children array is allocated
            bool    mChildrenFlag = false;

            //! container with neighbors on the same level
            //Basis** mNeighbors;
            Basis* mNeighbors[ B ] = { nullptr };

            //! container with children
            Basis** mChildren;
            //Basis* mChildren [ C ] = { nullptr };

            //! Parent counter. Only needed for testing.
            uint mNumberOfParents = 0;
            uint mParentCounter = 0;

            //! container for parents
            Basis** mParents;
//------------------------------------------------------------------------------
        public:
// -----------------------------------------------------------------------------

            /**
             * default constructor
             *
             * @param[in]   aIJK        ijk position of node
             * @param[in]   aLevel      level on which basis exists
             * @param[in]   aOwner      owner of basis
             */
            BSpline(
                    const luint * aIJK,
                    const  uint & aLevel,
                    const  uint & aOwner ) : Basis( aLevel, aOwner )
            {
                // save ijk position in memory.
                for( uint k=0; k<N; ++k )
                {
                    mIJK[ k ] = aIJK[ k ];
                }

                // set used flag on by default
                mUsedFlag = true;
            }

//------------------------------------------------------------------------------

            /**
             * Destructor
             */
            ~BSpline()
            {
                // test if basis has elements
                if ( mNumberOfConnectedElements != 0 )
                {
                    delete [] mElements;
                }

                /* // test if this basis has neighbors
                if ( mNeighborsFlag )
                {
                    delete [] mNeighbors;
                } */

                // test if this basis has children
                if ( mChildrenFlag )
                {
                    delete [] mChildren;
                }

                // test if parent container is used
                if ( mNumberOfParents != 0 )
                {
                    delete [] mParents;
                }

            };

//------------------------------------------------------------------------------

            /**
             * Sets the state of this basis to "active".
             *
             * @return void
             */
            void
            set_active_flag()
            {
                // set active flag on
                mActiveFlag  = true;

                // an active element can not be refined at the same time
                mRefinedFlag = false;
            }

//------------------------------------------------------------------------------

            /**
             *Sets the state of this basis to "refined".
             *
             * @return void
             */
            void
            set_refined_flag()
            {
                // a refined element is not active
                mActiveFlag  = false;

                // set element as refined
                mRefinedFlag = true;
            }

//------------------------------------------------------------------------------

            /**
             *Sets the state of this basis to "deactive".
             *
             * @return void
             */
            void
            set_deactive_flag()
            {
                // a refined element is not active
                mActiveFlag  = false;

                // set element as refined
                mRefinedFlag = false;
            }

//------------------------------------------------------------------------------

            /**
             * tells if a Basis is active
             *
             * @return bool   true if active
             */
            bool
            is_active()
            {
                return mActiveFlag;
            }

//------------------------------------------------------------------------------

            /**
             * tells if a Basis is refined
             *
             * @return bool   true if refined
             */
            bool
            is_refined()
            {
                return mRefinedFlag;
            }

//------------------------------------------------------------------------------

            /**
             * Returns an array of size [N] telling the proc local ijk-position
             * of the B-Spline on the current level.
             *
             * @return luint pointer to array containing ijk-position
             *               careful: node must not go out of scope.
             */
            const luint *
            get_ijk( ) const
            {
                return mIJK;
            }

// -----------------------------------------------------------------------------

            /**
             * set XYZ coordinates
             *
             * @param[in] aXYZ    array containing coordinates
             *
             * @return void
             */
            void
            set_xyz( const real * aXYZ )
            {
                // save ijk position in memory.
                for( uint k=0; k<N; ++k )
                {
                    mXYZ[ k ] = aXYZ[ k ];
                }
            }

// -----------------------------------------------------------------------------

            /**
             * Returns an array of size [N] telling the xyz-position
             * of the B-Spline
             *
             * @return double pointer to array containing xyz-position
             *               careful: node must not go out of scope.
             */
            const real *
            get_xyz() const
            {
                return mXYZ;
            }

// -----------------------------------------------------------------------------

            /**
             * reserves the memory for the  neighbor container
             *
             * @return void
             */
            void
            init_neighbor_container()
            {
                // reserve array
                /* mNeighbors = new Basis*[ B ];

                // reset array
                for( uint k=0; k<B; ++k )
                {
                    mNeighbors[ k ] = nullptr;
                } */

                // set flag
                mNeighborsFlag = true;
            }

// -----------------------------------------------------------------------------

            /**
             * Tells if children of this basis have been processed already
             */
            bool
            has_children()
            {
                return mChildrenFlag;
            }

// -----------------------------------------------------------------------------

            /**
             * reserves the memory for the  neighbor container
             *
             * @return void
             */
            void
            init_children_container()
            {
                // reserve array
                mChildren = new Basis*[ C ];

                // reset array
                for( uint k=0; k<C; ++k )
                {
                    mChildren[ k ] = nullptr;
                }

                // set flag
                mChildrenFlag = true;
            }

// -----------------------------------------------------------------------------

            /**
             * inserts a child to the specified position
             *
             * @param[ in ] aChildNumber    index of child
             * @param[ in ] aChild          pointer to child
             *
             * @return void
             */
            void
            insert_child(
                    const uint & aChildNumber,
                    Basis      * aChild )
            {
                mChildren[ aChildNumber ] = aChild;
            }

// -----------------------------------------------------------------------------

            /**
             * returns the pointer to a child at specified position
             *
             * @param[ in ] aChildNumber    index of child
             *
             * @return Basis*               pointer to child
             */
            Basis*
            get_child( const uint & aChildNumber )
            {
                if( mChildrenFlag )
                {
                    return mChildren[ aChildNumber ];
                }
                else
                {
                    return nullptr;
                }
            }

// -----------------------------------------------------------------------------

            /**
             * Returns the specified neighbor of a basis.
             * Numbering scheme is the same as used for elements.
             * Returns nullptr if neighbor does not exist
             *
             * @param[ in ] aNeighborNumber    index of neighbor
             *
             * @return Basis*
             */
            Basis*
            get_neighbor( const uint &  aNeighborNumber )
            {
                return mNeighbors[ aNeighborNumber ];
            }

// -----------------------------------------------------------------------------

            void
            insert_neighbor(
                    const uint & aNeighborNumber,
                    Basis      * aNeighbor )
            {
                mNeighbors[ aNeighborNumber ] = aNeighbor;
            }

// -----------------------------------------------------------------------------

            void
            flag_descendants()
            {
                if ( mFlag == false )
                {
                    // flag myself
                    mFlag = true;

                    // flag children
                    // test if children exist
                    if ( mChildrenFlag )
                    {
                        // loop over all children
                        for( uint k=0; k<C; ++k )
                        {
                            // test if child exists
                            if ( mChildren[ k ] != NULL )
                            {
                                mChildren[ k ]->flag_descendants();
                            }
                        }
                    }
                }
            }
// -----------------------------------------------------------------------------

            void
            unflag_descendants()
            {
                if ( mFlag == true )
                {
                    // unflag myself
                    mFlag = false;

                    // flag children
                    // test if children exist
                    if ( mChildrenFlag )
                    {
                        // loop over all children
                        for( uint k=0; k<C; ++k )
                        {
                            // test if child exists
                            if ( mChildren[ k ] != NULL )
                            {
                                mChildren[ k ]->unflag_descendants();
                            }
                        }
                    }
                }
            }

// -----------------------------------------------------------------------------

            // counts fagged basis
            void
            count_descendants( luint & aBasisCount )
            {
                // test if self has been flagged
                if ( mFlag )
                {
                    // add self to counter
                    ++aBasisCount;

                    // test if children exist
                    if ( mChildrenFlag )
                    {
                        // count children
                        for( uint k=0; k<C; ++k )
                        {
                            // test if child exists
                            if ( mChildren[ k ] != NULL )
                            {
                                mChildren[ k ]->count_descendants( aBasisCount );
                            }
                        }
                    }

                    // flag this basis
                    mFlag = false;
                }
            }

// -----------------------------------------------------------------------------

            // counts inflagged basis
            void
            collect_descendants(
                    Cell< Basis* > & aBasisList,
                    luint          & aBasisCount )
            {
                // test if self has been flagged
                if ( ! mFlag )
                {
                    // add self to list
                    aBasisList( aBasisCount++ ) = this;


                    // test if children exist
                    if ( mChildrenFlag )
                    {
                        // add children to list
                        for( uint k=0; k<C; ++k )
                        {
                            // test if child exists
                            if ( mChildren[ k ] != NULL )
                            {
                                mChildren[ k ]->collect_descendants( aBasisList, aBasisCount );
                            }
                        }
                    }

                    // flag this basis
                    mFlag = true;
                }
            }

// ----------------------------------------------------------------------------

            /**
             * Increments the parent counter. Needed for parent identification.
             */
            void
            increment_parent_counter()
            {
                ++mNumberOfParents;
            }
// -----------------------------------------------------------------------------

            void
            insert_parent( Basis * aParent )
            {
                if ( mParentCounter == 0 )
                {
                    // reserve array
                    mParents = new Basis*[ mNumberOfParents ];

                    // reset array
                    for( uint k=0; k<mNumberOfParents; ++k )
                    {
                        mParents[ k ] = nullptr;
                    }
                }
                mParents[ mParentCounter++ ] = aParent;
            }

// -----------------------------------------------------------------------------

            Basis*
            get_parent( const uint & aParentNumber )
            {
                return mParents[ aParentNumber ];
            }

// -----------------------------------------------------------------------------

            uint
            get_number_of_parents()
            {
                return mNumberOfParents;
            }

// -----------------------------------------------------------------------------

            void
            set_active_index( const luint & aIndex )
            {
                mActiveIndex = aIndex;
            }

//------------------------------------------------------------------------------

            luint
            get_active_index()
            {
                return mActiveIndex;
            }

//------------------------------------------------------------------------------

        };
//------------------------------------------------------------------------------

    } /* namespace hmr */
} /* namespace moris */

#endif /* SRC_HMR_CL_HMR_BSPLINE_HPP_ */