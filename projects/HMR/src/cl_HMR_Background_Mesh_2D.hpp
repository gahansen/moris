/*
 * cl_HMR_Background_Mesh_2D.hpp
 *
 *  Created on: Jun 21, 2018
 *      Author: messe
 */

#ifndef SRC_HMR_CL_HMR_BACKGROUND_MESH_2D_HPP_
#define SRC_HMR_CL_HMR_BACKGROUND_MESH_2D_HPP_

#include "cl_HMR_Background_Mesh.hpp" //HMR/src

namespace moris
{
    namespace hmr
    {
//--------------------------------------------------------------------------------

        template <>
        luint
        Background_Mesh< 2 >::calc_domain_id_of_element(
                const uint  & aLevel,
                const luint & aI,
                const luint & aJ ) const
        {
            if( aLevel < gMaxNumberOfLevels )
            {
                luint tI = aI + mMySubDomain.mAuraIJK[ aLevel ][ 0 ][ 0 ];
                luint tJ = aJ + mMySubDomain.mAuraIJK[ aLevel ][ 1 ][ 0 ];

                // test if input is valid
                if (    ( tI >= mDomain.mNumberOfElementsPerDimension[ aLevel ][ 0 ] )
                     || ( tJ >= mDomain.mNumberOfElementsPerDimension[ aLevel ][ 1 ] ) )
                {
                    // return error value
                    return gNoEntityID;
                }
                else
                {
                    // calculate domain id
                    return  mDomain.mLevelOffset[ aLevel ]
                        + tI
                        + tJ
                        * mDomain.mNumberOfElementsPerDimension[ aLevel ][ 0 ];
                }
            }
            else
            {
                // return error value
                return gNoEntityID;
            }
        }

//--------------------------------------------------------------------------------

        template <>
        luint
        Background_Mesh< 2 >::calc_subdomain_id_of_element(
                const uint  & aLevel,
                const luint & aI,
                const luint & aJ ) const
        {
            if( aLevel < gMaxNumberOfLevels )
            {
                // test if input is valid
                if ( ( aI >=  mMySubDomain.mNumberOfElementsPerDimension[ aLevel ][ 0 ] )
                        || ( aJ >=  mMySubDomain.mNumberOfElementsPerDimension[ aLevel ][ 1 ] ) )
                {
                    //return no value
                    return gNoEntityID;
                }
                else
                {
                    // calculate element ID
                    return mMySubDomain.mLevelOffset[ aLevel ] + aI + aJ*
                            mMySubDomain.mNumberOfElementsPerDimension[ aLevel ][ 0 ];
                }
            }
            else
            {
                // return error value
                return gNoEntityID;
            }
        }

//--------------------------------------------------------------------------------
        template <>
        void
        Background_Mesh< 2 >::calc_element_ids(
                const uint         & aLevel,
                const Matrix< DDLUMat > & aIJK,
                Matrix< DDLUMat >       & aIDs ) const
                {
            // reserve memory for output
            aIDs.set_size( 4, 1 );

            // child 0
            aIDs( 0 ) = calc_domain_id_of_element(
                    aLevel,
                    aIJK( 0, 0 ),
                    aIJK( 1, 0 ) );

            // child 1
            aIDs( 1 ) = calc_domain_id_of_element(
                    aLevel,
                    aIJK( 0, 1 ),
                    aIJK( 1, 1 ) );

            // child 2
            aIDs( 2 ) = calc_domain_id_of_element(
                    aLevel,
                    aIJK( 0, 2 ),
                    aIJK( 1, 2 ) );

            // child 3
            aIDs( 3 ) = calc_domain_id_of_element(
                    aLevel,
                    aIJK( 0, 3 ),
                    aIJK( 1, 3 ) );
        }

//--------------------------------------------------------------------------------

        template <>
        luint
        Background_Mesh< 2 >::calc_subdomain_id_from_global_id(
                const uint         & aLevel,
                const luint        & aID) const
        {
            if( aLevel < gMaxNumberOfLevels )
            {
                // subtract level offset from ID
                luint tID = aID - mDomain.mLevelOffset[ aLevel ];

                // calculate global ij position
                luint tJ = tID / mDomain.mNumberOfElementsPerDimension[ aLevel ][ 0 ];
                luint tI = tID - tJ*mDomain.mNumberOfElementsPerDimension[ aLevel ][ 0 ];

                // calculate local ij position
                tI -= mMySubDomain.mAuraIJK[ aLevel ][ 0 ][ 0 ];
                tJ -= mMySubDomain.mAuraIJK[ aLevel ][ 1 ][ 0 ];

                return this->calc_subdomain_id_of_element( aLevel, tI, tJ);
            }
            else
            {
                // return error value
                return gNoEntityID;
            }
       }

//--------------------------------------------------------------------------------

        template <>
        void
        Background_Mesh< 2 >::create_coarsest_frame()
        {
            // calculate number of elements in frame
            luint tNumberOfElements = (  mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ]
                                       - mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ] + 1 )
                                    * (  mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ]
                                       - mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ] + 1 );

            // clear coarsest element list
            mCoarsestElements.clear();

            // assign memory
            mCoarsestElements.resize( tNumberOfElements, nullptr );

            // initialize counter
            luint tCount = 0;

            // loop over domain
            for( luint j=mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ];
                    j<=mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ];
                    ++j)
            {
                for( luint i=mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ];
                        i<=mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ];
                        ++i)
                {
                    // add element from mCoarsestElementsIncludingAura
                    mCoarsestElements( tCount ++ ) =
                            mCoarsestElementsIncludingAura(
                                    calc_subdomain_id_of_element( 0, i, j ) );
                }
            }
        }

//-------------------------------------------------------------------------------

        template <>
        void
        Background_Mesh< 2 >::initialize_coarsest_elements()
        {
            // assign memory for coarsest elements
            mCoarsestElementsIncludingAura.resize(
                    mMySubDomain.mNumberOfElementsOnLevelZero,
                    nullptr );

            // calculate number of elements on level zero per direction
            Matrix< DDLUMat > tNumberOfElements =
                    get_number_of_subdomain_elements_per_direction_on_level_zero();

            luint* tIJK = new luint[ 2 ];

            // initialize counter
            luint tCount = 0;

            // add elements on level zero
            for( luint j=0; j<tNumberOfElements( 1 ); ++j )
            {
                tIJK[ 1 ] = j;
                for( luint i=0; i<tNumberOfElements( 0 ); ++i )
                {
                    tIJK[ 0 ] = i;

                    insert_zero_level_element(
                            tCount++,
                            new Background_Element< 2, 4, 8 >(
                                    ( Background_Element_Base* ) nullptr,
                                    mActivePattern,
                                    tIJK,
                                    this->calc_domain_id_of_element( 0, i, j ) ,
                                    ( uint ) 0,
                                    ( uint ) 0,
                                    ( uint ) gNoProcOwner ) );
                }
            }

            delete [] tIJK;
        }

//-------------------------------------------------------------------------------
        template <>
        void
        Background_Mesh< 2 >::finalize_coarsest_elements()
        {
            // set boundaries for loop
            luint tImin[ 9 ];
            luint tImax[ 9 ];
            luint tJmin[ 9 ];
            luint tJmax[ 9 ];

            // create quadrants for aura elements
            // quadrant 0
            tImin[ 0 ] = 0;
            tImax[ 0 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ] - 1;
            tJmin[ 0 ] = 0;
            tJmax[ 0 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ] - 1;

            // quadrant 1
            tImin[ 1 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ];
            tImax[ 1 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ];
            tJmin[ 1 ] = 0;
            tJmax[ 1 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ] - 1;

            // quadrant 2
            tImin[ 2 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ] + 1;
            tImax[ 2 ] = mMySubDomain.mNumberOfElementsPerDimension[ 0 ][ 0 ] - 1;
            tJmin[ 2 ] = 0;
            tJmax[ 2 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ] - 1;

            // quadrant 3
            tImin[ 3 ] = 0;
            tImax[ 3 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ] - 1;
            tJmin[ 3 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ];
            tJmax[ 3 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ];

            // quadrant 4
            tImin[ 4 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ];
            tImax[ 4 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ];
            tJmin[ 4 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ];
            tJmax[ 4 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ];

            // quadrant 5
            tImin[ 5 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ] + 1;
            tImax[ 5 ] = mMySubDomain.mNumberOfElementsPerDimension[ 0 ][ 0 ] - 1;
            tJmin[ 5 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ];
            tJmax[ 5 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ];

            // quadrant 6
            tImin[ 6 ] = 0;
            tImax[ 6 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ]-1;
            tJmin[ 6 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ]+1;
            tJmax[ 6 ] = mMySubDomain.mNumberOfElementsPerDimension[ 0 ][ 1 ] - 1;

            // quadrant 7
            tImin[ 7 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ];
            tImax[ 7 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ];
            tJmin[ 7 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ] + 1;
            tJmax[ 7 ] = mMySubDomain.mNumberOfElementsPerDimension[ 0 ][ 1 ] - 1;

            // quadrant 8
            tImin[ 8 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ] + 1;
            tImax[ 8 ] = mMySubDomain.mNumberOfElementsPerDimension[ 0 ][ 0 ] - 1;
            tJmin[ 8 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ] + 1;
            tJmax[ 8 ] = mMySubDomain.mNumberOfElementsPerDimension[ 0 ][ 1 ] - 1;

            // loop over all quadrants
            for( uint q=0; q<9; ++q )
            {
                // loop over my own elments
                if ( mMyProcNeighbors( q ) == par_rank() )
                {
                    // this is an active element
                    for( auto j=tJmin[ q ]; j<=tJmax[ q ]; ++j )
                    {
                        for( auto i=tImin[ q ]; i<=tImax[ q ]; ++i )
                        {
                            // get local id == local index for level 0
                            auto tIndex = calc_subdomain_id_of_element( 0, i, j );

                            // assume that all non owned elements are padding elements
                            mCoarsestElementsIncludingAura( tIndex )->set_active_flag( mActivePattern );

                            // set owner ( in this case: myself )
                            mCoarsestElementsIncludingAura( tIndex )->set_owner( mMyProcNeighbors( q ) );
                        }
                    }
                }
                else if ( mMyProcNeighbors( q ) != gNoProcNeighbor )
                {
                    // count elements for aura
                    uint tCount =   ( tImax[ q ] - tImin[ q ] + 1 )
                                  * ( tJmax[ q ] - tJmin[ q ] + 1 );

                    // set size for matrix

                    mCoarsestAura( q ).set_size( tCount, 1 );

                    // reset counter
                    tCount = 0;

                    // this is an active element of a neigbor proc
                    for( auto j=tJmin[ q ]; j<=tJmax[ q ]; ++j )
                    {
                        for( auto i=tImin[ q ]; i<=tImax[ q ]; ++i )
                        {
                            // get local id == local index for level 0
                            auto tIndex = calc_subdomain_id_of_element( 0, i, j );

                            // assume that all non owned elements are padding elements
                            mCoarsestElementsIncludingAura( tIndex )->set_padding_flag();

                            // set owner
                            mCoarsestElementsIncludingAura( tIndex )->set_owner( mMyProcNeighbors( q ) );

                            // add element index to aura
                            mCoarsestAura( q )( tCount++ ) = tIndex;
                        }
                    }
                }
                else
                {
                    // this is definetly a padding element
                    for( auto j=tJmin[ q ]; j<=tJmax[ q ]; ++j )
                    {
                        for( auto i=tImin[ q ]; i<=tImax[ q ]; ++i )
                        {
                            // get local id == local index for level 0
                            auto tIndex = calc_subdomain_id_of_element( 0, i, j );

                            // deactivate element
                            mCoarsestElementsIncludingAura( tIndex )->set_padding_flag();

                            // padding element does not belong to anybody
                            mCoarsestElementsIncludingAura( tIndex )->set_owner( gNoProcOwner );
                        }
                    }
                }
            }

            // create quadrants for inverse aura

            // quadrant 0
            luint tDelta = mParameters->get_padding_size() - 1;
            tImin[ 0 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ];
            tImax[ 0 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ] + tDelta;
            tJmin[ 0 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ];
            tJmax[ 0 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ] + tDelta;

            // quadrant 1
            tImin[ 1 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ];
            tImax[ 1 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ];
            tJmin[ 1 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ];
            tJmax[ 1 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ] + tDelta;

            // quadrant 2
            tImin[ 2 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ] - tDelta;
            tImax[ 2 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ];
            tJmin[ 2 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ];
            tJmax[ 2 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ] + tDelta;

            // quadrant 3
            tImin[ 3 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ];
            tImax[ 3 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ] + tDelta;
            tJmin[ 3 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ];
            tJmax[ 3 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ];

            // quadrant 4
            tImin[ 4 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ];
            tImax[ 4 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ];
            tJmin[ 4 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ];
            tJmax[ 4 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ];

            // quadrant 5
            tImin[ 5 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ] - tDelta;
            tImax[ 5 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ];
            tJmin[ 5 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 0 ];
            tJmax[ 5 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ];

            // quadrant 6
            tImin[ 6 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ];
            tImax[ 6 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ] + tDelta;
            tJmin[ 6 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ] - tDelta;
            tJmax[ 6 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ];

            // quadrant 7
            tImin[ 7 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 0 ];
            tImax[ 7 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ];
            tJmin[ 7 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ] - tDelta;
            tJmax[ 7 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ];

            // quadrant 8
            tImin[ 8 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ] - tDelta;
            tImax[ 8 ] = mMySubDomain.mFrameIJK[ 0 ][ 0 ][ 1 ];
            tJmin[ 8 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ] - tDelta;
            tJmax[ 8 ] = mMySubDomain.mFrameIJK[ 0 ][ 1 ][ 1 ];

            // loop over all possible neighbors
            for( uint q=0; q<9; ++q )
            {
                // check if neigbor exists and is not myself
                if (       mMyProcNeighbors( q ) != gNoProcNeighbor
                        && mMyProcNeighbors( q ) != par_rank() )
                {
                    // count elements for inverse aura
                    luint tCount =   ( tImax[ q ] - tImin[ q ] + 1 )
                                   * ( tJmax[ q ] - tJmin[ q ] + 1 );

                    mCoarsestInverseAura( q ).set_size( tCount, 1 );

                    // reset counter
                    tCount = 0;

                    // loop over all j-positions
                    for( auto j=tJmin[ q ]; j<=tJmax[ q ]; ++j )
                    {
                        // loop over all i-positions
                        for( auto i=tImin[ q ]; i<=tImax[ q ]; ++i )
                        {
                            // add subdomain id of element into matrix
                            mCoarsestInverseAura( q )( tCount++ )
                                = calc_subdomain_id_of_element( 0, i, j );
                        }
                    }
                }
            }
        }

//-------------------------------------------------------------------------------

        template <>
        void
        Background_Mesh< 2 >::refine_element( Background_Element_Base * aElement )
        {
            // only perform if element is not refined already
            // and element is below max defined level

            if ( aElement->get_level() < gMaxNumberOfLevels-1 )
            {
                if ( ! aElement->has_children()  )
                {
                    // get owner of element
                    uint tOwner = aElement->get_owner();

                    // get level of new element
                    auto tLevel = aElement->get_level() + 1 ;

                    // get ijk positions of children
                    Matrix< DDLUMat > tIJK;
                    aElement->get_ijk_of_children( tIJK );

                    // ask background mesh for IDs of children
                    Matrix< DDLUMat > tIDs;
                    this->calc_element_ids(
                            tLevel,
                            tIJK,
                            tIDs );

                    // temporary array for ijk position
                    luint tCIJK[ 2 ];

                    // child 0
                    tCIJK[ 0 ] = tIJK( 0, 0 );
                    tCIJK[ 1 ] = tIJK( 1, 0 );
                    aElement->insert_child( new Background_Element< 2, 4, 8 >(
                            aElement,
                            mActivePattern,
                            tCIJK,
                            tIDs( 0 ),
                            tLevel ,
                            ( uint ) 0,
                            tOwner ) );

                    // child 1
                    tCIJK[ 0 ] = tIJK( 0, 1 );
                    tCIJK[ 1 ] = tIJK( 1, 1 );
                    aElement->insert_child( new Background_Element< 2, 4, 8 >(
                            aElement,
                            mActivePattern,
                            tCIJK,
                            tIDs( 1 ),
                            tLevel ,
                            ( uint ) 1,
                            tOwner ) );

                    // child 2
                    tCIJK[ 0 ] = tIJK( 0, 2 );
                    tCIJK[ 1 ] = tIJK( 1, 2 );
                    aElement->insert_child( new Background_Element< 2, 4, 8 >(
                            aElement,
                            mActivePattern,
                            tCIJK,
                            tIDs( 2 ),
                            tLevel ,
                            ( uint ) 2,
                            tOwner ) );

                    // child 3
                    tCIJK[ 0 ] = tIJK( 0, 3 );
                    tCIJK[ 1 ] = tIJK( 1, 3 );
                    aElement->insert_child( new Background_Element< 2, 4, 8 >(
                            aElement,
                            mActivePattern,
                            tCIJK,
                            tIDs( 3 ),
                            tLevel ,
                            ( uint ) 3,
                            tOwner ) );

                    // set refined switch
                    aElement->set_refined_flag( mActivePattern );

                    // test if this is a padding element
                    if ( aElement->is_padding() )
                    {
                        // loop over all children
                        for( uint k=0; k<4; ++k )
                        {
                            // get pointer to child and set refinement flag
                            aElement->get_child( k )->set_padding_flag();
                        }
                    }
                }
                else // element has children
                {
                    // activate children if they are deactive
                    for( uint k=0; k<4; ++k )
                    {
                        // get child
                        auto tChild = aElement->get_child( k );

                        // test if child is deactive
                        if ( tChild->is_deactive( mActivePattern ) )
                        {
                            // activate child
                            tChild->set_active_flag( mActivePattern );
                        }
                    }

                    // refine element
                    aElement->set_refined_flag( mActivePattern );
                }
            }
        }

//-------------------------------------------------------------------------------

        template <>
        void
        Background_Mesh< 2 >::collect_neighbors_on_level_zero()
        {
            //   -----------
            //  | 7 | 2 | 6 |
            //   -----------
            //  | 3 |   | 1 |
            //   -----------
            //  | 4 | 0 | 5 |
            //   -----------
            // maximum i
            luint tIMax = mMySubDomain.mNumberOfElementsPerDimension[ 0 ][ 0 ];

            // maximum j
            luint tJMax = mMySubDomain.mNumberOfElementsPerDimension[ 0 ][ 1 ];

            // initialize element counter
            luint tCount = 0;

            // matrix containing neighbor IDs
            luint tNeighborIndex[ 8 ];
            // loop over all J directions
            for( luint j=0; j<tJMax; ++j )
            {
                for (luint i=0; i<tIMax; ++i )
                {
                    // calculate neighbor elements
                    tNeighborIndex[ 0 ]
                        = this->calc_subdomain_id_of_element( 0, i  , j-1 );

                    tNeighborIndex[ 1 ]
                        = this->calc_subdomain_id_of_element( 0, i+1, j  );

                    tNeighborIndex[ 2 ]
                        = this->calc_subdomain_id_of_element( 0, i  , j+1 );

                    tNeighborIndex[ 3 ]
                        = this->calc_subdomain_id_of_element( 0, i-1, j  );

                    tNeighborIndex[ 4 ]
                         = this->calc_subdomain_id_of_element( 0, i-1, j-1 );

                    tNeighborIndex[ 5 ]
                        = this->calc_subdomain_id_of_element( 0, i+1, j-1 );

                    tNeighborIndex[ 6 ]
                        = this->calc_subdomain_id_of_element( 0, i+1, j+1 );

                    tNeighborIndex[ 7 ]
                        = this->calc_subdomain_id_of_element( 0, i-1, j+1 );

                    // get element
                    Background_Element_Base * tElement
                    = mCoarsestElementsIncludingAura( tCount++ );

                    // loop over all possible neighbors
                    for( uint n=0; n<8; ++n )
                    {
                        // test if neighbor exists
                        if ( tNeighborIndex[ n ] != gNoEntityID )
                        {
                            // insert neighbor
                            tElement->insert_neighbor( n,
                                    mCoarsestElementsIncludingAura( tNeighborIndex[ n ] ) );
                        }
                    }
                }
            }
        }

//-------------------------------------------------------------------------------

        template <>
        void
        Background_Mesh< 2 >::calc_corner_nodes_of_element(
                const Background_Element_Base   * aElement,
                Matrix< DDRMat >                     & aNodeCoords )
        {
            // get ijk position of element
            const luint * tIJK   = aElement->get_ijk();

            // get level of element
            const uint   tLevel = aElement->get_level();

            aNodeCoords.set_size( 2, 4 );

            // calculate node 0
            aNodeCoords( 0, 0 ) =  ( tIJK[ 0 ]
                + mMySubDomain.mAuraIJK[ tLevel ][ 0 ][ 0 ] )
                * mElementLength[ tLevel ][ 0 ]
                + mDomainOffset[ 0 ];
            aNodeCoords( 1, 0 ) =  ( tIJK[ 1 ]
                + mMySubDomain.mAuraIJK[ tLevel ][ 1 ][ 0 ] )
                * mElementLength[ tLevel ][ 1 ]
                + mDomainOffset[ 1 ];

            // node 1
            aNodeCoords( 0, 1 ) =    aNodeCoords ( 0, 0 )
                + mElementLength[ tLevel ][ 0 ];

            aNodeCoords( 1, 1 ) = aNodeCoords ( 1, 0 );
            // node 2
            aNodeCoords( 0, 2 ) = aNodeCoords ( 0, 1 );
            aNodeCoords( 1, 2 ) = aNodeCoords ( 1, 1 )
                + mElementLength[ tLevel ][ 1 ];

            // node 3
            aNodeCoords( 0, 3 ) = aNodeCoords ( 0, 0 );
            aNodeCoords( 1, 3 ) = aNodeCoords ( 1, 2 );
        }

//-------------------------------------------------------------------------------
        template <>
        void
        Background_Mesh< 2 >::calc_center_of_element(
                const Background_Element_Base   * aElement,
                Matrix< DDRMat >                       & aNodeCoords )
        {
            // get ijk position of element
            const luint * tIJK   = aElement->get_ijk();

            // get level of element
            const uint   tLevel = aElement->get_level();

            aNodeCoords.set_size( 2, 1 );
            aNodeCoords( 0 ) =  ( 0.5 + tIJK[ 0 ]
                                  + mMySubDomain.mAuraIJK[ tLevel ][ 0 ][ 0 ] )
                                * mElementLength[ tLevel ][ 0 ]
                                + mDomainOffset[ 0 ];

            aNodeCoords( 1 ) =  ( 0.5 + tIJK[ 1 ]
                                 + mMySubDomain.mAuraIJK[ tLevel ][ 1 ][ 0 ] )
                                * mElementLength[ tLevel ][ 1 ]
                                + mDomainOffset[ 1 ];
        }

//-------------------------------------------------------------------------------

    } /* namespace hmr */
}


#endif /* SRC_HMR_CL_HMR_BACKGROUND_MESH_2D_HPP_ */