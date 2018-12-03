/*
 * fn_HMR_Background_Element_Neighbors_3D.hpp
 *
 *  Created on: November 27, 2018
 *  using MATLAB
 */
 
#ifndef SRC_HMR_FN_HMR_BACKGROUND_ELEMENT_NEIGHBORS_3D_HPP_
#define SRC_HMR_FN_HMR_BACKGROUND_ELEMENT_NEIGHBORS_3D_HPP_

#include "typedefs.hpp"
#include "cl_Cell.hpp"
#include "cl_HMR_Background_Element_Base.hpp"
#include "cl_HMR_Background_Element.hpp"

namespace moris
{
    namespace hmr
    {
// ----------------------------------------------------------------------------

        template <>
        void
        Background_Element< 3, 8, 26, 6, 12 >::get_neighbors_from_same_level(
            const uint                        & aOrder,
            Cell< Background_Element_Base * > & aNeighbors )
        {
             // make sure order is not too big
             MORIS_ASSERT( 0 < aOrder && aOrder <= 3, "Neighbor order too big.");

             // array that contains max size
             uint tArraySize[ 4 ] = { 0, 26, 124, 342 };

             // initialize temporary neighbor array
             Cell< Background_Element_Base * >
             tNeighbors( tArraySize[ aOrder ], nullptr );

             // fill first frame
             for ( uint k=0; k<26; ++k)
             {
                 // test if neighbor exists
                 if ( mNeighbors[ k ] != NULL )
                 {
                     // test if neighbor is on same level
                     if ( mNeighbors[ k ]->get_level() == mLevel )
                     {
                         // copy neighbor into array
                         tNeighbors( k ) = mNeighbors[ k ];
                     }
                 }
             }

             // temporary variable containing a neighbor
             Background_Element_Base * tNeighbor = nullptr;

             if ( aOrder >= 2 )
             {
                 // test if neighbor 0 exists
                 if ( tNeighbors( 0 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 0
                     tNeighbor =  tNeighbors( 0 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 69 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 69 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 0
                     tNeighbor =  tNeighbors( 0 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 53 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 53 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 0
                     tNeighbor =  tNeighbors( 0 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 68 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 68 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 0
                     tNeighbor =  tNeighbors( 0 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 70 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 70 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 0
                     tNeighbor =  tNeighbors( 0 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 85 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 85 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 0
                     tNeighbor =  tNeighbors( 0 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 52 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 52 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 0
                     tNeighbor =  tNeighbors( 0 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 54 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 54 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 0
                     tNeighbor =  tNeighbors( 0 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 84 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 84 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 0
                     tNeighbor =  tNeighbors( 0 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 86 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 86 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 1 exists
                 if ( tNeighbors( 1 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 1
                     tNeighbor =  tNeighbors( 1 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 75 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 75 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 1
                     tNeighbor =  tNeighbors( 1 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 59 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 59 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 1
                     tNeighbor =  tNeighbors( 1 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 73 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 73 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 1
                     tNeighbor =  tNeighbors( 1 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 77 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 77 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 1
                     tNeighbor =  tNeighbors( 1 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 91 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 91 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 1
                     tNeighbor =  tNeighbors( 1 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 57 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 57 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 1
                     tNeighbor =  tNeighbors( 1 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 61 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 61 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 1
                     tNeighbor =  tNeighbors( 1 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 89 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 89 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 1
                     tNeighbor =  tNeighbors( 1 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 93 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 93 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 2 exists
                 if ( tNeighbors( 2 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 2
                     tNeighbor =  tNeighbors( 2 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 80 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 80 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 2
                     tNeighbor =  tNeighbors( 2 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 64 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 64 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 2
                     tNeighbor =  tNeighbors( 2 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 81 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 81 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 2
                     tNeighbor =  tNeighbors( 2 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 79 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 79 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 2
                     tNeighbor =  tNeighbors( 2 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 96 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 96 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 2
                     tNeighbor =  tNeighbors( 2 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 65 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 65 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 2
                     tNeighbor =  tNeighbors( 2 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 63 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 63 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 2
                     tNeighbor =  tNeighbors( 2 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 97 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 97 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 2
                     tNeighbor =  tNeighbors( 2 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 95 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 95 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 3 exists
                 if ( tNeighbors( 3 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 3
                     tNeighbor =  tNeighbors( 3 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 74 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 74 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 3
                     tNeighbor =  tNeighbors( 3 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 58 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 58 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 3
                     tNeighbor =  tNeighbors( 3 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 72 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 72 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 3
                     tNeighbor =  tNeighbors( 3 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 76 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 76 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 3
                     tNeighbor =  tNeighbors( 3 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 90 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 90 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 3
                     tNeighbor =  tNeighbors( 3 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 56 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 56 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 3
                     tNeighbor =  tNeighbors( 3 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 60 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 60 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 3
                     tNeighbor =  tNeighbors( 3 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 88 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 88 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 3
                     tNeighbor =  tNeighbors( 3 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 92 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 92 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 4 exists
                 if ( tNeighbors( 4 ) != NULL )
                 {
                     // get neighbor 4 of neighbor 4
                     tNeighbor =  tNeighbors( 4 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 38 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 38 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 4
                     tNeighbor =  tNeighbors( 4 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 33 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 33 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 4
                     tNeighbor =  tNeighbors( 4 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 39 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 39 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 4
                     tNeighbor =  tNeighbors( 4 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 43 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 43 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 4
                     tNeighbor =  tNeighbors( 4 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 37 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 37 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 4
                     tNeighbor =  tNeighbors( 4 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 32 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 32 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 4
                     tNeighbor =  tNeighbors( 4 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 34 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 34 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 4
                     tNeighbor =  tNeighbors( 4 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 44 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 44 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 4
                     tNeighbor =  tNeighbors( 4 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 42 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 42 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 5 exists
                 if ( tNeighbors( 5 ) != NULL )
                 {
                     // get neighbor 5 of neighbor 5
                     tNeighbor =  tNeighbors( 5 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 111 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 111 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 5
                     tNeighbor =  tNeighbors( 5 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 106 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 106 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 5
                     tNeighbor =  tNeighbors( 5 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 112 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 112 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 5
                     tNeighbor =  tNeighbors( 5 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 116 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 116 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 5
                     tNeighbor =  tNeighbors( 5 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 110 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 110 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 5
                     tNeighbor =  tNeighbors( 5 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 105 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 105 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 5
                     tNeighbor =  tNeighbors( 5 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 107 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 107 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 5
                     tNeighbor =  tNeighbors( 5 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 117 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 117 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 5
                     tNeighbor =  tNeighbors( 5 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 115 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 115 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 6 exists
                 if ( tNeighbors( 6 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 53 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 53 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 33 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 33 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 28 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 28 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 34 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 34 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 38 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 38 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 32 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 32 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 52 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 52 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 54 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 54 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 69 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 69 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 27 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 27 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 29 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 29 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 39 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 39 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 37 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 37 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 68 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 68 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 6
                     tNeighbor =  tNeighbors( 6 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 70 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 70 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 7 exists
                 if ( tNeighbors( 7 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 59 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 59 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 39 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 39 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 34 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 34 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 40 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 40 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 44 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 44 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 38 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 38 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 57 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 57 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 61 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 61 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 75 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 75 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 33 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 33 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 35 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 35 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 45 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 45 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 43 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 43 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 73 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 73 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 7
                     tNeighbor =  tNeighbors( 7 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 77 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 77 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 8 exists
                 if ( tNeighbors( 8 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 64 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 64 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 43 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 43 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 38 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 38 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 44 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 44 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 48 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 48 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 42 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 42 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 65 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 65 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 63 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 63 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 80 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 80 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 37 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 37 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 39 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 39 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 49 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 49 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 47 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 47 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 81 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 81 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 8
                     tNeighbor =  tNeighbors( 8 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 79 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 79 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 9 exists
                 if ( tNeighbors( 9 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 58 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 58 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 37 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 37 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 32 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 32 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 38 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 38 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 42 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 42 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 36 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 36 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 56 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 56 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 60 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 60 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 74 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 74 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 31 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 31 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 33 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 33 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 43 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 43 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 41 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 41 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 72 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 72 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 9
                     tNeighbor =  tNeighbors( 9 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 76 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 76 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 10 exists
                 if ( tNeighbors( 10 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 68 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 68 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 72 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 72 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 52 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 52 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 56 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 56 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 67 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 67 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 69 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 69 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 74 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 74 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 84 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 84 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 88 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 88 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 51 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 51 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 53 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 53 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 58 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 58 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 83 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 83 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 85 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 85 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 10
                     tNeighbor =  tNeighbors( 10 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 90 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 90 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 11 exists
                 if ( tNeighbors( 11 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 70 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 70 ) = tNeighbor;
                         }
                     }

                     // get neighbor 1 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 73 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 73 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 54 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 54 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 57 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 57 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 69 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 69 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 71 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 71 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 75 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 75 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 86 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 86 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 89 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 89 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 53 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 53 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 55 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 55 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 59 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 59 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 85 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 85 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 87 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 87 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 11
                     tNeighbor =  tNeighbors( 11 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 91 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 91 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 12 exists
                 if ( tNeighbors( 12 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 77 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 77 ) = tNeighbor;
                         }
                     }

                     // get neighbor 2 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 81 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 81 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 61 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 61 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 65 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 65 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 75 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 75 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 82 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 82 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 80 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 80 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 93 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 93 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 97 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 97 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 59 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 59 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 66 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 66 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 64 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 64 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 91 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 91 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 98 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 98 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 12
                     tNeighbor =  tNeighbors( 12 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 96 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 96 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 13 exists
                 if ( tNeighbors( 13 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 79 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 79 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 76 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 76 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 63 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 63 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 60 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 60 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 74 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 74 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 80 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 80 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 78 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 78 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 95 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 95 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 92 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 92 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 58 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 58 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 64 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 64 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 62 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 62 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 90 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 90 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 96 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 96 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 13
                     tNeighbor =  tNeighbors( 13 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 94 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 94 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 14 exists
                 if ( tNeighbors( 14 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 85 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 85 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 106 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 106 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 69 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 69 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 84 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 84 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 86 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 86 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 101 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 101 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 107 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 107 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 111 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 111 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 105 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 105 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 68 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 68 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 70 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 70 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 100 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 100 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 102 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 102 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 112 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 112 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 14
                     tNeighbor =  tNeighbors( 14 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 110 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 110 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 15 exists
                 if ( tNeighbors( 15 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 91 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 91 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 112 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 112 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 75 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 75 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 89 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 89 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 93 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 93 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 107 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 107 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 113 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 113 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 117 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 117 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 111 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 111 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 73 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 73 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 77 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 77 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 106 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 106 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 108 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 108 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 118 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 118 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 15
                     tNeighbor =  tNeighbors( 15 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 116 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 116 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 16 exists
                 if ( tNeighbors( 16 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 96 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 96 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 116 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 116 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 80 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 80 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 97 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 97 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 95 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 95 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 111 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 111 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 117 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 117 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 121 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 121 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 115 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 115 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 81 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 81 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 79 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 79 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 110 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 110 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 112 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 112 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 122 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 122 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 16
                     tNeighbor =  tNeighbors( 16 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 120 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 120 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 17 exists
                 if ( tNeighbors( 17 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 90 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 90 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 110 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 110 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 74 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 74 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 88 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 88 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 92 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 92 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 105 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 105 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 111 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 111 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 115 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 115 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 109 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 109 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 72 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 72 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 76 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 76 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 104 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 104 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 106 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 106 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 116 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 116 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 17
                     tNeighbor =  tNeighbors( 17 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 114 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 114 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 18 exists
                 if ( tNeighbors( 18 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 52 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 52 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 56 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 56 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 32 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 32 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 27 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 27 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 33 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 33 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 37 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 37 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 31 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 31 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 51 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 51 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 53 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 53 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 58 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 58 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 68 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 68 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 72 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 72 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 26 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 26 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 28 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 28 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 38 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 38 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 36 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 36 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 67 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 67 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 69 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 69 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 18
                     tNeighbor =  tNeighbors( 18 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 74 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 74 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 19 exists
                 if ( tNeighbors( 19 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 54 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 54 ) = tNeighbor;
                         }
                     }

                     // get neighbor 1 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 57 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 57 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 34 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 34 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 29 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 29 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 35 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 35 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 39 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 39 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 33 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 33 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 53 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 53 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 55 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 55 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 59 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 59 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 70 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 70 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 73 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 73 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 28 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 28 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 30 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 30 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 40 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 40 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 38 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 38 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 69 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 69 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 71 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 71 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 19
                     tNeighbor =  tNeighbors( 19 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 75 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 75 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 20 exists
                 if ( tNeighbors( 20 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 61 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 61 ) = tNeighbor;
                         }
                     }

                     // get neighbor 2 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 65 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 65 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 44 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 44 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 39 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 39 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 45 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 45 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 49 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 49 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 43 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 43 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 59 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 59 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 66 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 66 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 64 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 64 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 77 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 77 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 81 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 81 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 38 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 38 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 40 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 40 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 50 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 50 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 48 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 48 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 75 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 75 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 82 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 82 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 20
                     tNeighbor =  tNeighbors( 20 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 80 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 80 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 21 exists
                 if ( tNeighbors( 21 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 63 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 63 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 60 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 60 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 42 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 42 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 37 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 37 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 43 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 43 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 47 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 47 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 41 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 41 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 58 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 58 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 64 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 64 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 62 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 62 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 79 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 79 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 76 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 76 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 36 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 36 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 38 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 38 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 48 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 48 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 46 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 46 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 74 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 74 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 80 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 80 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 21
                     tNeighbor =  tNeighbors( 21 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 78 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 78 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 22 exists
                 if ( tNeighbors( 22 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 84 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 84 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 88 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 88 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 105 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 105 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 68 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 68 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 72 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 72 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 83 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 83 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 85 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 85 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 90 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 90 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 100 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 100 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 106 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 106 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 110 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 110 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 104 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 104 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 67 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 67 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 69 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 69 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 74 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 74 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 99 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 99 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 101 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 101 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 111 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 111 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 22
                     tNeighbor =  tNeighbors( 22 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 109 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 109 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 23 exists
                 if ( tNeighbors( 23 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 86 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 86 ) = tNeighbor;
                         }
                     }

                     // get neighbor 1 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 89 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 89 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 107 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 107 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 70 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 70 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 73 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 73 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 85 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 85 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 87 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 87 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 91 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 91 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 102 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 102 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 108 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 108 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 112 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 112 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 106 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 106 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 69 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 69 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 71 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 71 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 75 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 75 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 101 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 101 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 103 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 103 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 113 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 113 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 23
                     tNeighbor =  tNeighbors( 23 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 111 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 111 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 24 exists
                 if ( tNeighbors( 24 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 93 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 93 ) = tNeighbor;
                         }
                     }

                     // get neighbor 2 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 97 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 97 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 117 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 117 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 77 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 77 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 81 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 81 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 91 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 91 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 98 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 98 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 96 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 96 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 112 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 112 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 118 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 118 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 122 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 122 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 116 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 116 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 75 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 75 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 82 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 82 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 80 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 80 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 111 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 111 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 113 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 113 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 123 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 123 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 24
                     tNeighbor =  tNeighbors( 24 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 121 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 121 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 25 exists
                 if ( tNeighbors( 25 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 95 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 95 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 92 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 92 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 115 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 115 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 79 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 79 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 76 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 76 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 90 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 90 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 96 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 96 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 94 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 94 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 110 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 110 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 116 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 116 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 120 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 120 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 114 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 114 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 74 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 74 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 80 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 80 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 78 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 78 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 109 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 109 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 111 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 111 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 121 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 121 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 25
                     tNeighbor =  tNeighbors( 25 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 119 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 119 ) = tNeighbor;
                         }
                     }

                 }
             if ( aOrder >= 3 )
             {
                 // test if neighbor 26 exists
                 if ( tNeighbors( 26 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 174 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 174 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 180 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 180 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 132 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 132 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 125 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 125 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 133 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 133 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 139 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 139 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 131 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 131 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 173 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 173 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 175 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 175 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 182 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 182 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 198 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 198 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 204 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 204 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 124 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 124 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 126 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 126 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 140 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 140 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 138 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 138 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 197 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 197 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 199 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 199 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 26
                     tNeighbor =  tNeighbors( 26 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 206 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 206 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 27 exists
                 if ( tNeighbors( 27 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 175 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 175 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 133 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 133 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 126 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 126 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 134 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 134 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 140 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 140 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 132 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 132 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 174 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 174 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 176 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 176 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 199 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 199 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 125 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 125 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 127 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 127 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 141 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 141 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 139 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 139 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 198 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 198 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 27
                     tNeighbor =  tNeighbors( 27 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 200 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 200 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 28 exists
                 if ( tNeighbors( 28 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 176 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 176 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 134 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 134 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 127 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 127 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 135 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 135 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 141 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 141 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 133 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 133 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 175 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 175 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 177 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 177 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 200 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 200 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 126 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 126 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 128 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 128 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 142 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 142 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 140 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 140 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 199 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 199 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 28
                     tNeighbor =  tNeighbors( 28 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 201 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 201 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 29 exists
                 if ( tNeighbors( 29 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 177 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 177 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 135 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 135 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 128 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 128 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 136 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 136 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 142 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 142 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 134 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 134 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 176 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 176 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 178 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 178 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 201 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 201 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 127 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 127 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 129 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 129 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 143 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 143 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 141 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 141 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 200 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 200 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 29
                     tNeighbor =  tNeighbors( 29 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 202 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 202 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 30 exists
                 if ( tNeighbors( 30 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 178 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 178 ) = tNeighbor;
                         }
                     }

                     // get neighbor 1 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 181 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 181 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 136 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 136 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 129 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 129 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 137 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 137 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 143 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 143 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 135 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 135 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 177 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 177 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 179 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 179 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 183 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 183 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 202 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 202 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 205 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 205 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 128 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 128 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 130 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 130 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 144 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 144 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 142 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 142 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 201 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 201 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 203 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 203 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 30
                     tNeighbor =  tNeighbors( 30 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 207 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 207 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 31 exists
                 if ( tNeighbors( 31 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 182 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 182 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 139 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 139 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 132 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 132 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 140 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 140 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 146 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 146 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 138 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 138 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 180 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 180 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 184 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 184 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 206 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 206 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 131 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 131 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 133 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 133 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 147 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 147 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 145 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 145 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 204 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 204 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 31
                     tNeighbor =  tNeighbors( 31 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 208 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 208 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 32 exists
                 if ( tNeighbors( 32 ) != NULL )
                 {
                     // get neighbor 4 of neighbor 32
                     tNeighbor =  tNeighbors( 32 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 140 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 140 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 32
                     tNeighbor =  tNeighbors( 32 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 133 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 133 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 32
                     tNeighbor =  tNeighbors( 32 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 141 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 141 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 32
                     tNeighbor =  tNeighbors( 32 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 147 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 147 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 32
                     tNeighbor =  tNeighbors( 32 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 139 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 139 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 32
                     tNeighbor =  tNeighbors( 32 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 132 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 132 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 32
                     tNeighbor =  tNeighbors( 32 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 134 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 134 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 32
                     tNeighbor =  tNeighbors( 32 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 148 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 148 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 32
                     tNeighbor =  tNeighbors( 32 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 146 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 146 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 33 exists
                 if ( tNeighbors( 33 ) != NULL )
                 {
                     // get neighbor 4 of neighbor 33
                     tNeighbor =  tNeighbors( 33 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 141 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 141 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 33
                     tNeighbor =  tNeighbors( 33 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 134 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 134 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 33
                     tNeighbor =  tNeighbors( 33 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 142 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 142 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 33
                     tNeighbor =  tNeighbors( 33 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 148 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 148 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 33
                     tNeighbor =  tNeighbors( 33 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 140 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 140 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 33
                     tNeighbor =  tNeighbors( 33 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 133 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 133 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 33
                     tNeighbor =  tNeighbors( 33 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 135 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 135 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 33
                     tNeighbor =  tNeighbors( 33 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 149 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 149 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 33
                     tNeighbor =  tNeighbors( 33 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 147 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 147 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 34 exists
                 if ( tNeighbors( 34 ) != NULL )
                 {
                     // get neighbor 4 of neighbor 34
                     tNeighbor =  tNeighbors( 34 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 142 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 142 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 34
                     tNeighbor =  tNeighbors( 34 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 135 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 135 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 34
                     tNeighbor =  tNeighbors( 34 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 143 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 143 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 34
                     tNeighbor =  tNeighbors( 34 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 149 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 149 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 34
                     tNeighbor =  tNeighbors( 34 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 141 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 141 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 34
                     tNeighbor =  tNeighbors( 34 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 134 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 134 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 34
                     tNeighbor =  tNeighbors( 34 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 136 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 136 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 34
                     tNeighbor =  tNeighbors( 34 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 150 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 150 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 34
                     tNeighbor =  tNeighbors( 34 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 148 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 148 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 35 exists
                 if ( tNeighbors( 35 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 183 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 183 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 143 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 143 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 136 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 136 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 144 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 144 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 150 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 150 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 142 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 142 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 181 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 181 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 185 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 185 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 207 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 207 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 135 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 135 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 137 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 137 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 151 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 151 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 149 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 149 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 205 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 205 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 35
                     tNeighbor =  tNeighbors( 35 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 209 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 209 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 36 exists
                 if ( tNeighbors( 36 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 184 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 184 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 146 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 146 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 139 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 139 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 147 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 147 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 153 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 153 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 145 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 145 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 182 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 182 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 186 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 186 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 208 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 208 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 138 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 138 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 140 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 140 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 154 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 154 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 152 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 152 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 206 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 206 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 36
                     tNeighbor =  tNeighbors( 36 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 210 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 210 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 37 exists
                 if ( tNeighbors( 37 ) != NULL )
                 {
                     // get neighbor 4 of neighbor 37
                     tNeighbor =  tNeighbors( 37 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 147 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 147 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 37
                     tNeighbor =  tNeighbors( 37 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 140 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 140 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 37
                     tNeighbor =  tNeighbors( 37 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 148 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 148 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 37
                     tNeighbor =  tNeighbors( 37 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 154 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 154 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 37
                     tNeighbor =  tNeighbors( 37 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 146 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 146 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 37
                     tNeighbor =  tNeighbors( 37 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 139 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 139 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 37
                     tNeighbor =  tNeighbors( 37 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 141 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 141 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 37
                     tNeighbor =  tNeighbors( 37 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 155 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 155 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 37
                     tNeighbor =  tNeighbors( 37 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 153 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 153 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 38 exists
                 if ( tNeighbors( 38 ) != NULL )
                 {
                     // get neighbor 4 of neighbor 38
                     tNeighbor =  tNeighbors( 38 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 148 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 148 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 38
                     tNeighbor =  tNeighbors( 38 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 141 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 141 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 38
                     tNeighbor =  tNeighbors( 38 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 149 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 149 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 38
                     tNeighbor =  tNeighbors( 38 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 155 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 155 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 38
                     tNeighbor =  tNeighbors( 38 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 147 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 147 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 38
                     tNeighbor =  tNeighbors( 38 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 140 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 140 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 38
                     tNeighbor =  tNeighbors( 38 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 142 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 142 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 38
                     tNeighbor =  tNeighbors( 38 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 156 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 156 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 38
                     tNeighbor =  tNeighbors( 38 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 154 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 154 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 39 exists
                 if ( tNeighbors( 39 ) != NULL )
                 {
                     // get neighbor 4 of neighbor 39
                     tNeighbor =  tNeighbors( 39 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 149 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 149 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 39
                     tNeighbor =  tNeighbors( 39 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 142 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 142 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 39
                     tNeighbor =  tNeighbors( 39 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 150 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 150 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 39
                     tNeighbor =  tNeighbors( 39 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 156 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 156 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 39
                     tNeighbor =  tNeighbors( 39 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 148 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 148 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 39
                     tNeighbor =  tNeighbors( 39 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 141 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 141 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 39
                     tNeighbor =  tNeighbors( 39 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 143 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 143 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 39
                     tNeighbor =  tNeighbors( 39 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 157 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 157 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 39
                     tNeighbor =  tNeighbors( 39 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 155 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 155 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 40 exists
                 if ( tNeighbors( 40 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 185 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 185 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 150 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 150 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 143 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 143 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 151 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 151 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 157 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 157 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 149 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 149 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 183 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 183 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 187 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 187 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 209 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 209 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 142 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 142 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 144 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 144 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 158 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 158 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 156 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 156 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 207 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 207 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 40
                     tNeighbor =  tNeighbors( 40 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 211 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 211 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 41 exists
                 if ( tNeighbors( 41 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 186 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 186 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 153 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 153 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 146 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 146 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 154 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 154 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 160 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 160 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 152 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 152 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 184 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 184 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 188 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 188 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 210 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 210 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 145 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 145 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 147 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 147 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 161 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 161 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 159 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 159 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 208 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 208 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 41
                     tNeighbor =  tNeighbors( 41 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 212 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 212 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 42 exists
                 if ( tNeighbors( 42 ) != NULL )
                 {
                     // get neighbor 4 of neighbor 42
                     tNeighbor =  tNeighbors( 42 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 154 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 154 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 42
                     tNeighbor =  tNeighbors( 42 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 147 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 147 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 42
                     tNeighbor =  tNeighbors( 42 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 155 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 155 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 42
                     tNeighbor =  tNeighbors( 42 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 161 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 161 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 42
                     tNeighbor =  tNeighbors( 42 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 153 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 153 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 42
                     tNeighbor =  tNeighbors( 42 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 146 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 146 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 42
                     tNeighbor =  tNeighbors( 42 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 148 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 148 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 42
                     tNeighbor =  tNeighbors( 42 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 162 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 162 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 42
                     tNeighbor =  tNeighbors( 42 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 160 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 160 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 43 exists
                 if ( tNeighbors( 43 ) != NULL )
                 {
                     // get neighbor 4 of neighbor 43
                     tNeighbor =  tNeighbors( 43 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 155 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 155 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 43
                     tNeighbor =  tNeighbors( 43 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 148 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 148 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 43
                     tNeighbor =  tNeighbors( 43 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 156 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 156 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 43
                     tNeighbor =  tNeighbors( 43 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 162 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 162 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 43
                     tNeighbor =  tNeighbors( 43 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 154 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 154 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 43
                     tNeighbor =  tNeighbors( 43 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 147 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 147 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 43
                     tNeighbor =  tNeighbors( 43 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 149 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 149 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 43
                     tNeighbor =  tNeighbors( 43 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 163 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 163 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 43
                     tNeighbor =  tNeighbors( 43 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 161 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 161 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 44 exists
                 if ( tNeighbors( 44 ) != NULL )
                 {
                     // get neighbor 4 of neighbor 44
                     tNeighbor =  tNeighbors( 44 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 156 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 156 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 44
                     tNeighbor =  tNeighbors( 44 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 149 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 149 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 44
                     tNeighbor =  tNeighbors( 44 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 157 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 157 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 44
                     tNeighbor =  tNeighbors( 44 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 163 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 163 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 44
                     tNeighbor =  tNeighbors( 44 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 155 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 155 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 44
                     tNeighbor =  tNeighbors( 44 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 148 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 148 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 44
                     tNeighbor =  tNeighbors( 44 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 150 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 150 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 44
                     tNeighbor =  tNeighbors( 44 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 164 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 164 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 44
                     tNeighbor =  tNeighbors( 44 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 162 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 162 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 45 exists
                 if ( tNeighbors( 45 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 187 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 187 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 157 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 157 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 150 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 150 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 158 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 158 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 164 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 164 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 156 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 156 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 185 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 185 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 189 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 189 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 211 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 211 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 149 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 149 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 151 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 151 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 165 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 165 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 163 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 163 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 209 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 209 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 45
                     tNeighbor =  tNeighbors( 45 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 213 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 213 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 46 exists
                 if ( tNeighbors( 46 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 191 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 191 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 188 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 188 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 160 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 160 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 153 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 153 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 161 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 161 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 167 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 167 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 159 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 159 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 186 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 186 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 192 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 192 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 190 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 190 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 215 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 215 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 212 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 212 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 152 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 152 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 154 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 154 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 168 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 168 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 166 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 166 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 210 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 210 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 216 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 216 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 46
                     tNeighbor =  tNeighbors( 46 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 214 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 214 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 47 exists
                 if ( tNeighbors( 47 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 192 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 192 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 161 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 161 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 154 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 154 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 162 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 162 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 168 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 168 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 160 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 160 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 193 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 193 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 191 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 191 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 216 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 216 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 153 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 153 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 155 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 155 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 169 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 169 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 167 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 167 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 217 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 217 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 47
                     tNeighbor =  tNeighbors( 47 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 215 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 215 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 48 exists
                 if ( tNeighbors( 48 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 193 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 193 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 162 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 162 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 155 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 155 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 163 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 163 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 169 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 169 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 161 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 161 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 194 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 194 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 192 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 192 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 217 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 217 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 154 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 154 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 156 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 156 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 170 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 170 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 168 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 168 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 218 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 218 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 48
                     tNeighbor =  tNeighbors( 48 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 216 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 216 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 49 exists
                 if ( tNeighbors( 49 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 194 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 194 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 163 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 163 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 156 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 156 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 164 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 164 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 170 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 170 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 162 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 162 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 195 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 195 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 193 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 193 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 218 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 218 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 155 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 155 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 157 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 157 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 171 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 171 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 169 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 169 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 219 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 219 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 49
                     tNeighbor =  tNeighbors( 49 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 217 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 217 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 50 exists
                 if ( tNeighbors( 50 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 189 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 189 ) = tNeighbor;
                         }
                     }

                     // get neighbor 2 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 195 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 195 ) = tNeighbor;
                         }
                     }

                     // get neighbor 4 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 4 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 164 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 164 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 157 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 157 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 165 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 165 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 171 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 171 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 163 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 163 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 187 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 187 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 196 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 196 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 194 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 194 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 213 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 213 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 219 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 219 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 156 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 156 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 158 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 158 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 172 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 172 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 170 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 170 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 211 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 211 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 220 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 220 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 50
                     tNeighbor =  tNeighbors( 50 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 218 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 218 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 51 exists
                 if ( tNeighbors( 51 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 198 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 198 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 204 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 204 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 174 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 174 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 180 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 180 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 197 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 197 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 199 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 199 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 206 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 206 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 222 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 222 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 228 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 228 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 173 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 173 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 175 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 175 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 182 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 182 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 221 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 221 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 223 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 223 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 51
                     tNeighbor =  tNeighbors( 51 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 230 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 230 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 52 exists
                 if ( tNeighbors( 52 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 52
                     tNeighbor =  tNeighbors( 52 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 199 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 199 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 52
                     tNeighbor =  tNeighbors( 52 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 175 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 175 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 52
                     tNeighbor =  tNeighbors( 52 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 198 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 198 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 52
                     tNeighbor =  tNeighbors( 52 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 200 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 200 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 52
                     tNeighbor =  tNeighbors( 52 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 223 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 223 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 52
                     tNeighbor =  tNeighbors( 52 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 174 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 174 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 52
                     tNeighbor =  tNeighbors( 52 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 176 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 176 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 52
                     tNeighbor =  tNeighbors( 52 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 222 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 222 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 52
                     tNeighbor =  tNeighbors( 52 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 224 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 224 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 53 exists
                 if ( tNeighbors( 53 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 53
                     tNeighbor =  tNeighbors( 53 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 200 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 200 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 53
                     tNeighbor =  tNeighbors( 53 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 176 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 176 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 53
                     tNeighbor =  tNeighbors( 53 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 199 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 199 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 53
                     tNeighbor =  tNeighbors( 53 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 201 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 201 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 53
                     tNeighbor =  tNeighbors( 53 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 224 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 224 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 53
                     tNeighbor =  tNeighbors( 53 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 175 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 175 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 53
                     tNeighbor =  tNeighbors( 53 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 177 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 177 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 53
                     tNeighbor =  tNeighbors( 53 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 223 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 223 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 53
                     tNeighbor =  tNeighbors( 53 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 225 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 225 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 54 exists
                 if ( tNeighbors( 54 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 54
                     tNeighbor =  tNeighbors( 54 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 201 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 201 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 54
                     tNeighbor =  tNeighbors( 54 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 177 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 177 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 54
                     tNeighbor =  tNeighbors( 54 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 200 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 200 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 54
                     tNeighbor =  tNeighbors( 54 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 202 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 202 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 54
                     tNeighbor =  tNeighbors( 54 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 225 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 225 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 54
                     tNeighbor =  tNeighbors( 54 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 176 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 176 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 54
                     tNeighbor =  tNeighbors( 54 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 178 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 178 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 54
                     tNeighbor =  tNeighbors( 54 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 224 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 224 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 54
                     tNeighbor =  tNeighbors( 54 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 226 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 226 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 55 exists
                 if ( tNeighbors( 55 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 202 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 202 ) = tNeighbor;
                         }
                     }

                     // get neighbor 1 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 205 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 205 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 178 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 178 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 181 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 181 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 201 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 201 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 203 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 203 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 207 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 207 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 226 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 226 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 229 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 229 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 177 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 177 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 179 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 179 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 183 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 183 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 225 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 225 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 227 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 227 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 55
                     tNeighbor =  tNeighbors( 55 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 231 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 231 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 56 exists
                 if ( tNeighbors( 56 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 56
                     tNeighbor =  tNeighbors( 56 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 206 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 206 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 56
                     tNeighbor =  tNeighbors( 56 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 182 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 182 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 56
                     tNeighbor =  tNeighbors( 56 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 204 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 204 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 56
                     tNeighbor =  tNeighbors( 56 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 208 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 208 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 56
                     tNeighbor =  tNeighbors( 56 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 230 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 230 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 56
                     tNeighbor =  tNeighbors( 56 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 180 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 180 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 56
                     tNeighbor =  tNeighbors( 56 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 184 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 184 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 56
                     tNeighbor =  tNeighbors( 56 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 228 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 228 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 56
                     tNeighbor =  tNeighbors( 56 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 232 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 232 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 57 exists
                 if ( tNeighbors( 57 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 57
                     tNeighbor =  tNeighbors( 57 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 207 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 207 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 57
                     tNeighbor =  tNeighbors( 57 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 183 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 183 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 57
                     tNeighbor =  tNeighbors( 57 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 205 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 205 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 57
                     tNeighbor =  tNeighbors( 57 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 209 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 209 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 57
                     tNeighbor =  tNeighbors( 57 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 231 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 231 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 57
                     tNeighbor =  tNeighbors( 57 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 181 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 181 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 57
                     tNeighbor =  tNeighbors( 57 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 185 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 185 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 57
                     tNeighbor =  tNeighbors( 57 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 229 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 229 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 57
                     tNeighbor =  tNeighbors( 57 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 233 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 233 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 58 exists
                 if ( tNeighbors( 58 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 58
                     tNeighbor =  tNeighbors( 58 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 208 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 208 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 58
                     tNeighbor =  tNeighbors( 58 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 184 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 184 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 58
                     tNeighbor =  tNeighbors( 58 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 206 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 206 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 58
                     tNeighbor =  tNeighbors( 58 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 210 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 210 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 58
                     tNeighbor =  tNeighbors( 58 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 232 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 232 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 58
                     tNeighbor =  tNeighbors( 58 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 182 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 182 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 58
                     tNeighbor =  tNeighbors( 58 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 186 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 186 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 58
                     tNeighbor =  tNeighbors( 58 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 230 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 230 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 58
                     tNeighbor =  tNeighbors( 58 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 234 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 234 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 59 exists
                 if ( tNeighbors( 59 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 59
                     tNeighbor =  tNeighbors( 59 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 209 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 209 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 59
                     tNeighbor =  tNeighbors( 59 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 185 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 185 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 59
                     tNeighbor =  tNeighbors( 59 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 207 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 207 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 59
                     tNeighbor =  tNeighbors( 59 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 211 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 211 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 59
                     tNeighbor =  tNeighbors( 59 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 233 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 233 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 59
                     tNeighbor =  tNeighbors( 59 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 183 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 183 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 59
                     tNeighbor =  tNeighbors( 59 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 187 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 187 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 59
                     tNeighbor =  tNeighbors( 59 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 231 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 231 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 59
                     tNeighbor =  tNeighbors( 59 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 235 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 235 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 60 exists
                 if ( tNeighbors( 60 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 60
                     tNeighbor =  tNeighbors( 60 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 210 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 210 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 60
                     tNeighbor =  tNeighbors( 60 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 186 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 186 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 60
                     tNeighbor =  tNeighbors( 60 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 208 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 208 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 60
                     tNeighbor =  tNeighbors( 60 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 212 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 212 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 60
                     tNeighbor =  tNeighbors( 60 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 234 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 234 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 60
                     tNeighbor =  tNeighbors( 60 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 184 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 184 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 60
                     tNeighbor =  tNeighbors( 60 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 188 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 188 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 60
                     tNeighbor =  tNeighbors( 60 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 232 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 232 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 60
                     tNeighbor =  tNeighbors( 60 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 236 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 236 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 61 exists
                 if ( tNeighbors( 61 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 61
                     tNeighbor =  tNeighbors( 61 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 211 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 211 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 61
                     tNeighbor =  tNeighbors( 61 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 187 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 187 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 61
                     tNeighbor =  tNeighbors( 61 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 209 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 209 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 61
                     tNeighbor =  tNeighbors( 61 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 213 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 213 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 61
                     tNeighbor =  tNeighbors( 61 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 235 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 235 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 61
                     tNeighbor =  tNeighbors( 61 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 185 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 185 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 61
                     tNeighbor =  tNeighbors( 61 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 189 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 189 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 61
                     tNeighbor =  tNeighbors( 61 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 233 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 233 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 61
                     tNeighbor =  tNeighbors( 61 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 237 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 237 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 62 exists
                 if ( tNeighbors( 62 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 215 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 215 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 212 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 212 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 191 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 191 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 188 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 188 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 210 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 210 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 216 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 216 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 214 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 214 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 239 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 239 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 236 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 236 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 186 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 186 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 192 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 192 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 190 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 190 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 234 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 234 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 240 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 240 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 62
                     tNeighbor =  tNeighbors( 62 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 238 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 238 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 63 exists
                 if ( tNeighbors( 63 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 63
                     tNeighbor =  tNeighbors( 63 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 216 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 216 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 63
                     tNeighbor =  tNeighbors( 63 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 192 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 192 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 63
                     tNeighbor =  tNeighbors( 63 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 217 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 217 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 63
                     tNeighbor =  tNeighbors( 63 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 215 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 215 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 63
                     tNeighbor =  tNeighbors( 63 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 240 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 240 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 63
                     tNeighbor =  tNeighbors( 63 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 193 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 193 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 63
                     tNeighbor =  tNeighbors( 63 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 191 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 191 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 63
                     tNeighbor =  tNeighbors( 63 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 241 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 241 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 63
                     tNeighbor =  tNeighbors( 63 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 239 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 239 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 64 exists
                 if ( tNeighbors( 64 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 64
                     tNeighbor =  tNeighbors( 64 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 217 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 217 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 64
                     tNeighbor =  tNeighbors( 64 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 193 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 193 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 64
                     tNeighbor =  tNeighbors( 64 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 218 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 218 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 64
                     tNeighbor =  tNeighbors( 64 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 216 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 216 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 64
                     tNeighbor =  tNeighbors( 64 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 241 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 241 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 64
                     tNeighbor =  tNeighbors( 64 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 194 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 194 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 64
                     tNeighbor =  tNeighbors( 64 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 192 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 192 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 64
                     tNeighbor =  tNeighbors( 64 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 242 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 242 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 64
                     tNeighbor =  tNeighbors( 64 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 240 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 240 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 65 exists
                 if ( tNeighbors( 65 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 65
                     tNeighbor =  tNeighbors( 65 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 218 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 218 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 65
                     tNeighbor =  tNeighbors( 65 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 194 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 194 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 65
                     tNeighbor =  tNeighbors( 65 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 219 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 219 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 65
                     tNeighbor =  tNeighbors( 65 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 217 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 217 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 65
                     tNeighbor =  tNeighbors( 65 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 242 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 242 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 65
                     tNeighbor =  tNeighbors( 65 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 195 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 195 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 65
                     tNeighbor =  tNeighbors( 65 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 193 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 193 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 65
                     tNeighbor =  tNeighbors( 65 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 243 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 243 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 65
                     tNeighbor =  tNeighbors( 65 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 241 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 241 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 66 exists
                 if ( tNeighbors( 66 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 213 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 213 ) = tNeighbor;
                         }
                     }

                     // get neighbor 2 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 219 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 219 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 189 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 189 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 195 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 195 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 211 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 211 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 220 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 220 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 218 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 218 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 237 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 237 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 243 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 243 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 187 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 187 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 196 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 196 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 194 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 194 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 235 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 235 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 244 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 244 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 66
                     tNeighbor =  tNeighbors( 66 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 242 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 242 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 67 exists
                 if ( tNeighbors( 67 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 222 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 222 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 228 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 228 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 198 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 198 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 204 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 204 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 221 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 221 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 223 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 223 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 230 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 230 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 246 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 246 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 252 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 252 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 197 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 197 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 199 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 199 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 206 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 206 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 245 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 245 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 247 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 247 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 67
                     tNeighbor =  tNeighbors( 67 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 254 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 254 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 68 exists
                 if ( tNeighbors( 68 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 68
                     tNeighbor =  tNeighbors( 68 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 223 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 223 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 68
                     tNeighbor =  tNeighbors( 68 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 199 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 199 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 68
                     tNeighbor =  tNeighbors( 68 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 222 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 222 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 68
                     tNeighbor =  tNeighbors( 68 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 224 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 224 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 68
                     tNeighbor =  tNeighbors( 68 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 247 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 247 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 68
                     tNeighbor =  tNeighbors( 68 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 198 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 198 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 68
                     tNeighbor =  tNeighbors( 68 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 200 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 200 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 68
                     tNeighbor =  tNeighbors( 68 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 246 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 246 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 68
                     tNeighbor =  tNeighbors( 68 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 248 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 248 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 69 exists
                 if ( tNeighbors( 69 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 69
                     tNeighbor =  tNeighbors( 69 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 224 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 224 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 69
                     tNeighbor =  tNeighbors( 69 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 200 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 200 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 69
                     tNeighbor =  tNeighbors( 69 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 223 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 223 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 69
                     tNeighbor =  tNeighbors( 69 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 225 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 225 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 69
                     tNeighbor =  tNeighbors( 69 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 248 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 248 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 69
                     tNeighbor =  tNeighbors( 69 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 199 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 199 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 69
                     tNeighbor =  tNeighbors( 69 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 201 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 201 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 69
                     tNeighbor =  tNeighbors( 69 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 247 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 247 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 69
                     tNeighbor =  tNeighbors( 69 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 249 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 249 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 70 exists
                 if ( tNeighbors( 70 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 70
                     tNeighbor =  tNeighbors( 70 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 225 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 225 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 70
                     tNeighbor =  tNeighbors( 70 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 201 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 201 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 70
                     tNeighbor =  tNeighbors( 70 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 224 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 224 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 70
                     tNeighbor =  tNeighbors( 70 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 226 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 226 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 70
                     tNeighbor =  tNeighbors( 70 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 249 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 249 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 70
                     tNeighbor =  tNeighbors( 70 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 200 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 200 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 70
                     tNeighbor =  tNeighbors( 70 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 202 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 202 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 70
                     tNeighbor =  tNeighbors( 70 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 248 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 248 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 70
                     tNeighbor =  tNeighbors( 70 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 250 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 250 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 71 exists
                 if ( tNeighbors( 71 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 226 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 226 ) = tNeighbor;
                         }
                     }

                     // get neighbor 1 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 229 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 229 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 202 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 202 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 205 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 205 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 225 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 225 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 227 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 227 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 231 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 231 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 250 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 250 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 253 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 253 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 201 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 201 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 203 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 203 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 207 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 207 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 249 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 249 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 251 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 251 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 71
                     tNeighbor =  tNeighbors( 71 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 255 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 255 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 72 exists
                 if ( tNeighbors( 72 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 72
                     tNeighbor =  tNeighbors( 72 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 230 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 230 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 72
                     tNeighbor =  tNeighbors( 72 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 206 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 206 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 72
                     tNeighbor =  tNeighbors( 72 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 228 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 228 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 72
                     tNeighbor =  tNeighbors( 72 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 232 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 232 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 72
                     tNeighbor =  tNeighbors( 72 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 254 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 254 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 72
                     tNeighbor =  tNeighbors( 72 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 204 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 204 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 72
                     tNeighbor =  tNeighbors( 72 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 208 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 208 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 72
                     tNeighbor =  tNeighbors( 72 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 252 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 252 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 72
                     tNeighbor =  tNeighbors( 72 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 256 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 256 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 73 exists
                 if ( tNeighbors( 73 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 73
                     tNeighbor =  tNeighbors( 73 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 231 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 231 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 73
                     tNeighbor =  tNeighbors( 73 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 207 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 207 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 73
                     tNeighbor =  tNeighbors( 73 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 229 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 229 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 73
                     tNeighbor =  tNeighbors( 73 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 233 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 233 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 73
                     tNeighbor =  tNeighbors( 73 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 255 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 255 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 73
                     tNeighbor =  tNeighbors( 73 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 205 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 205 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 73
                     tNeighbor =  tNeighbors( 73 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 209 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 209 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 73
                     tNeighbor =  tNeighbors( 73 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 253 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 253 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 73
                     tNeighbor =  tNeighbors( 73 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 257 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 257 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 74 exists
                 if ( tNeighbors( 74 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 74
                     tNeighbor =  tNeighbors( 74 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 232 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 232 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 74
                     tNeighbor =  tNeighbors( 74 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 208 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 208 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 74
                     tNeighbor =  tNeighbors( 74 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 230 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 230 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 74
                     tNeighbor =  tNeighbors( 74 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 234 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 234 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 74
                     tNeighbor =  tNeighbors( 74 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 256 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 256 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 74
                     tNeighbor =  tNeighbors( 74 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 206 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 206 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 74
                     tNeighbor =  tNeighbors( 74 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 210 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 210 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 74
                     tNeighbor =  tNeighbors( 74 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 254 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 254 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 74
                     tNeighbor =  tNeighbors( 74 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 258 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 258 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 75 exists
                 if ( tNeighbors( 75 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 75
                     tNeighbor =  tNeighbors( 75 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 233 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 233 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 75
                     tNeighbor =  tNeighbors( 75 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 209 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 209 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 75
                     tNeighbor =  tNeighbors( 75 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 231 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 231 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 75
                     tNeighbor =  tNeighbors( 75 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 235 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 235 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 75
                     tNeighbor =  tNeighbors( 75 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 257 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 257 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 75
                     tNeighbor =  tNeighbors( 75 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 207 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 207 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 75
                     tNeighbor =  tNeighbors( 75 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 211 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 211 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 75
                     tNeighbor =  tNeighbors( 75 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 255 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 255 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 75
                     tNeighbor =  tNeighbors( 75 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 259 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 259 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 76 exists
                 if ( tNeighbors( 76 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 76
                     tNeighbor =  tNeighbors( 76 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 234 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 234 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 76
                     tNeighbor =  tNeighbors( 76 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 210 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 210 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 76
                     tNeighbor =  tNeighbors( 76 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 232 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 232 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 76
                     tNeighbor =  tNeighbors( 76 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 236 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 236 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 76
                     tNeighbor =  tNeighbors( 76 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 258 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 258 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 76
                     tNeighbor =  tNeighbors( 76 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 208 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 208 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 76
                     tNeighbor =  tNeighbors( 76 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 212 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 212 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 76
                     tNeighbor =  tNeighbors( 76 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 256 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 256 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 76
                     tNeighbor =  tNeighbors( 76 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 260 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 260 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 77 exists
                 if ( tNeighbors( 77 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 77
                     tNeighbor =  tNeighbors( 77 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 235 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 235 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 77
                     tNeighbor =  tNeighbors( 77 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 211 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 211 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 77
                     tNeighbor =  tNeighbors( 77 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 233 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 233 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 77
                     tNeighbor =  tNeighbors( 77 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 237 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 237 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 77
                     tNeighbor =  tNeighbors( 77 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 259 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 259 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 77
                     tNeighbor =  tNeighbors( 77 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 209 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 209 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 77
                     tNeighbor =  tNeighbors( 77 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 213 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 213 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 77
                     tNeighbor =  tNeighbors( 77 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 257 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 257 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 77
                     tNeighbor =  tNeighbors( 77 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 261 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 261 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 78 exists
                 if ( tNeighbors( 78 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 239 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 239 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 236 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 236 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 215 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 215 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 212 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 212 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 234 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 234 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 240 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 240 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 238 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 238 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 263 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 263 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 260 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 260 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 210 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 210 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 216 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 216 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 214 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 214 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 258 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 258 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 264 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 264 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 78
                     tNeighbor =  tNeighbors( 78 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 262 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 262 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 79 exists
                 if ( tNeighbors( 79 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 79
                     tNeighbor =  tNeighbors( 79 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 240 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 240 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 79
                     tNeighbor =  tNeighbors( 79 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 216 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 216 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 79
                     tNeighbor =  tNeighbors( 79 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 241 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 241 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 79
                     tNeighbor =  tNeighbors( 79 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 239 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 239 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 79
                     tNeighbor =  tNeighbors( 79 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 264 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 264 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 79
                     tNeighbor =  tNeighbors( 79 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 217 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 217 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 79
                     tNeighbor =  tNeighbors( 79 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 215 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 215 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 79
                     tNeighbor =  tNeighbors( 79 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 265 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 265 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 79
                     tNeighbor =  tNeighbors( 79 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 263 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 263 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 80 exists
                 if ( tNeighbors( 80 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 80
                     tNeighbor =  tNeighbors( 80 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 241 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 241 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 80
                     tNeighbor =  tNeighbors( 80 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 217 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 217 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 80
                     tNeighbor =  tNeighbors( 80 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 242 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 242 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 80
                     tNeighbor =  tNeighbors( 80 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 240 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 240 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 80
                     tNeighbor =  tNeighbors( 80 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 265 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 265 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 80
                     tNeighbor =  tNeighbors( 80 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 218 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 218 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 80
                     tNeighbor =  tNeighbors( 80 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 216 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 216 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 80
                     tNeighbor =  tNeighbors( 80 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 266 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 266 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 80
                     tNeighbor =  tNeighbors( 80 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 264 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 264 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 81 exists
                 if ( tNeighbors( 81 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 81
                     tNeighbor =  tNeighbors( 81 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 242 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 242 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 81
                     tNeighbor =  tNeighbors( 81 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 218 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 218 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 81
                     tNeighbor =  tNeighbors( 81 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 243 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 243 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 81
                     tNeighbor =  tNeighbors( 81 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 241 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 241 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 81
                     tNeighbor =  tNeighbors( 81 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 266 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 266 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 81
                     tNeighbor =  tNeighbors( 81 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 219 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 219 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 81
                     tNeighbor =  tNeighbors( 81 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 217 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 217 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 81
                     tNeighbor =  tNeighbors( 81 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 267 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 267 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 81
                     tNeighbor =  tNeighbors( 81 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 265 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 265 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 82 exists
                 if ( tNeighbors( 82 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 237 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 237 ) = tNeighbor;
                         }
                     }

                     // get neighbor 2 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 243 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 243 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 213 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 213 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 219 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 219 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 235 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 235 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 244 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 244 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 242 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 242 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 261 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 261 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 267 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 267 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 211 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 211 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 220 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 220 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 218 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 218 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 259 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 259 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 268 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 268 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 82
                     tNeighbor =  tNeighbors( 82 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 266 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 266 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 83 exists
                 if ( tNeighbors( 83 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 246 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 246 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 252 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 252 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 222 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 222 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 228 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 228 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 245 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 245 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 247 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 247 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 254 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 254 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 270 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 270 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 276 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 276 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 221 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 221 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 223 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 223 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 230 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 230 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 269 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 269 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 271 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 271 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 83
                     tNeighbor =  tNeighbors( 83 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 278 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 278 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 84 exists
                 if ( tNeighbors( 84 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 84
                     tNeighbor =  tNeighbors( 84 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 247 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 247 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 84
                     tNeighbor =  tNeighbors( 84 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 223 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 223 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 84
                     tNeighbor =  tNeighbors( 84 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 246 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 246 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 84
                     tNeighbor =  tNeighbors( 84 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 248 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 248 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 84
                     tNeighbor =  tNeighbors( 84 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 271 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 271 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 84
                     tNeighbor =  tNeighbors( 84 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 222 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 222 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 84
                     tNeighbor =  tNeighbors( 84 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 224 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 224 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 84
                     tNeighbor =  tNeighbors( 84 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 270 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 270 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 84
                     tNeighbor =  tNeighbors( 84 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 272 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 272 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 85 exists
                 if ( tNeighbors( 85 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 85
                     tNeighbor =  tNeighbors( 85 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 248 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 248 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 85
                     tNeighbor =  tNeighbors( 85 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 224 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 224 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 85
                     tNeighbor =  tNeighbors( 85 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 247 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 247 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 85
                     tNeighbor =  tNeighbors( 85 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 249 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 249 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 85
                     tNeighbor =  tNeighbors( 85 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 272 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 272 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 85
                     tNeighbor =  tNeighbors( 85 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 223 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 223 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 85
                     tNeighbor =  tNeighbors( 85 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 225 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 225 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 85
                     tNeighbor =  tNeighbors( 85 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 271 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 271 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 85
                     tNeighbor =  tNeighbors( 85 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 273 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 273 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 86 exists
                 if ( tNeighbors( 86 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 86
                     tNeighbor =  tNeighbors( 86 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 249 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 249 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 86
                     tNeighbor =  tNeighbors( 86 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 225 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 225 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 86
                     tNeighbor =  tNeighbors( 86 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 248 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 248 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 86
                     tNeighbor =  tNeighbors( 86 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 250 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 250 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 86
                     tNeighbor =  tNeighbors( 86 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 273 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 273 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 86
                     tNeighbor =  tNeighbors( 86 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 224 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 224 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 86
                     tNeighbor =  tNeighbors( 86 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 226 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 226 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 86
                     tNeighbor =  tNeighbors( 86 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 272 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 272 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 86
                     tNeighbor =  tNeighbors( 86 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 274 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 274 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 87 exists
                 if ( tNeighbors( 87 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 250 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 250 ) = tNeighbor;
                         }
                     }

                     // get neighbor 1 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 253 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 253 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 226 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 226 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 229 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 229 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 249 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 249 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 251 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 251 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 255 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 255 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 274 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 274 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 277 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 277 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 225 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 225 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 227 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 227 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 231 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 231 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 273 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 273 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 275 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 275 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 87
                     tNeighbor =  tNeighbors( 87 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 279 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 279 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 88 exists
                 if ( tNeighbors( 88 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 88
                     tNeighbor =  tNeighbors( 88 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 254 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 254 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 88
                     tNeighbor =  tNeighbors( 88 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 230 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 230 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 88
                     tNeighbor =  tNeighbors( 88 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 252 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 252 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 88
                     tNeighbor =  tNeighbors( 88 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 256 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 256 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 88
                     tNeighbor =  tNeighbors( 88 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 278 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 278 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 88
                     tNeighbor =  tNeighbors( 88 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 228 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 228 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 88
                     tNeighbor =  tNeighbors( 88 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 232 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 232 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 88
                     tNeighbor =  tNeighbors( 88 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 276 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 276 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 88
                     tNeighbor =  tNeighbors( 88 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 280 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 280 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 89 exists
                 if ( tNeighbors( 89 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 89
                     tNeighbor =  tNeighbors( 89 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 255 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 255 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 89
                     tNeighbor =  tNeighbors( 89 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 231 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 231 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 89
                     tNeighbor =  tNeighbors( 89 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 253 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 253 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 89
                     tNeighbor =  tNeighbors( 89 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 257 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 257 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 89
                     tNeighbor =  tNeighbors( 89 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 279 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 279 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 89
                     tNeighbor =  tNeighbors( 89 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 229 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 229 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 89
                     tNeighbor =  tNeighbors( 89 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 233 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 233 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 89
                     tNeighbor =  tNeighbors( 89 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 277 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 277 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 89
                     tNeighbor =  tNeighbors( 89 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 281 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 281 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 90 exists
                 if ( tNeighbors( 90 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 90
                     tNeighbor =  tNeighbors( 90 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 256 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 256 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 90
                     tNeighbor =  tNeighbors( 90 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 232 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 232 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 90
                     tNeighbor =  tNeighbors( 90 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 254 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 254 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 90
                     tNeighbor =  tNeighbors( 90 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 258 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 258 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 90
                     tNeighbor =  tNeighbors( 90 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 280 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 280 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 90
                     tNeighbor =  tNeighbors( 90 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 230 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 230 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 90
                     tNeighbor =  tNeighbors( 90 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 234 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 234 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 90
                     tNeighbor =  tNeighbors( 90 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 278 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 278 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 90
                     tNeighbor =  tNeighbors( 90 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 282 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 282 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 91 exists
                 if ( tNeighbors( 91 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 91
                     tNeighbor =  tNeighbors( 91 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 257 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 257 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 91
                     tNeighbor =  tNeighbors( 91 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 233 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 233 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 91
                     tNeighbor =  tNeighbors( 91 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 255 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 255 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 91
                     tNeighbor =  tNeighbors( 91 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 259 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 259 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 91
                     tNeighbor =  tNeighbors( 91 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 281 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 281 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 91
                     tNeighbor =  tNeighbors( 91 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 231 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 231 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 91
                     tNeighbor =  tNeighbors( 91 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 235 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 235 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 91
                     tNeighbor =  tNeighbors( 91 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 279 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 279 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 91
                     tNeighbor =  tNeighbors( 91 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 283 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 283 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 92 exists
                 if ( tNeighbors( 92 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 92
                     tNeighbor =  tNeighbors( 92 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 258 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 258 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 92
                     tNeighbor =  tNeighbors( 92 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 234 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 234 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 92
                     tNeighbor =  tNeighbors( 92 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 256 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 256 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 92
                     tNeighbor =  tNeighbors( 92 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 260 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 260 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 92
                     tNeighbor =  tNeighbors( 92 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 282 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 282 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 92
                     tNeighbor =  tNeighbors( 92 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 232 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 232 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 92
                     tNeighbor =  tNeighbors( 92 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 236 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 236 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 92
                     tNeighbor =  tNeighbors( 92 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 280 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 280 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 92
                     tNeighbor =  tNeighbors( 92 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 284 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 284 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 93 exists
                 if ( tNeighbors( 93 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 93
                     tNeighbor =  tNeighbors( 93 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 259 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 259 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 93
                     tNeighbor =  tNeighbors( 93 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 235 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 235 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 93
                     tNeighbor =  tNeighbors( 93 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 257 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 257 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 93
                     tNeighbor =  tNeighbors( 93 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 261 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 261 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 93
                     tNeighbor =  tNeighbors( 93 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 283 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 283 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 93
                     tNeighbor =  tNeighbors( 93 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 233 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 233 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 93
                     tNeighbor =  tNeighbors( 93 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 237 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 237 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 93
                     tNeighbor =  tNeighbors( 93 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 281 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 281 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 93
                     tNeighbor =  tNeighbors( 93 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 285 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 285 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 94 exists
                 if ( tNeighbors( 94 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 263 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 263 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 260 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 260 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 239 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 239 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 236 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 236 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 258 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 258 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 264 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 264 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 262 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 262 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 287 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 287 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 284 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 284 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 234 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 234 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 240 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 240 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 238 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 238 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 282 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 282 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 288 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 288 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 94
                     tNeighbor =  tNeighbors( 94 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 286 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 286 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 95 exists
                 if ( tNeighbors( 95 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 95
                     tNeighbor =  tNeighbors( 95 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 264 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 264 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 95
                     tNeighbor =  tNeighbors( 95 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 240 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 240 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 95
                     tNeighbor =  tNeighbors( 95 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 265 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 265 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 95
                     tNeighbor =  tNeighbors( 95 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 263 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 263 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 95
                     tNeighbor =  tNeighbors( 95 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 288 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 288 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 95
                     tNeighbor =  tNeighbors( 95 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 241 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 241 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 95
                     tNeighbor =  tNeighbors( 95 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 239 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 239 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 95
                     tNeighbor =  tNeighbors( 95 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 289 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 289 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 95
                     tNeighbor =  tNeighbors( 95 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 287 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 287 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 96 exists
                 if ( tNeighbors( 96 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 96
                     tNeighbor =  tNeighbors( 96 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 265 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 265 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 96
                     tNeighbor =  tNeighbors( 96 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 241 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 241 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 96
                     tNeighbor =  tNeighbors( 96 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 266 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 266 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 96
                     tNeighbor =  tNeighbors( 96 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 264 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 264 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 96
                     tNeighbor =  tNeighbors( 96 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 289 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 289 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 96
                     tNeighbor =  tNeighbors( 96 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 242 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 242 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 96
                     tNeighbor =  tNeighbors( 96 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 240 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 240 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 96
                     tNeighbor =  tNeighbors( 96 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 290 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 290 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 96
                     tNeighbor =  tNeighbors( 96 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 288 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 288 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 97 exists
                 if ( tNeighbors( 97 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 97
                     tNeighbor =  tNeighbors( 97 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 266 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 266 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 97
                     tNeighbor =  tNeighbors( 97 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 242 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 242 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 97
                     tNeighbor =  tNeighbors( 97 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 267 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 267 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 97
                     tNeighbor =  tNeighbors( 97 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 265 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 265 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 97
                     tNeighbor =  tNeighbors( 97 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 290 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 290 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 97
                     tNeighbor =  tNeighbors( 97 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 243 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 243 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 97
                     tNeighbor =  tNeighbors( 97 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 241 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 241 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 97
                     tNeighbor =  tNeighbors( 97 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 291 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 291 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 97
                     tNeighbor =  tNeighbors( 97 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 289 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 289 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 98 exists
                 if ( tNeighbors( 98 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 261 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 261 ) = tNeighbor;
                         }
                     }

                     // get neighbor 2 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 267 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 267 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 237 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 237 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 243 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 243 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 259 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 259 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 268 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 268 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 266 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 266 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 285 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 285 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 291 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 291 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 235 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 235 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 244 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 244 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 242 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 242 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 283 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 283 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 292 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 292 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 98
                     tNeighbor =  tNeighbors( 98 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 290 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 290 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 99 exists
                 if ( tNeighbors( 99 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 270 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 270 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 276 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 276 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 301 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 301 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 246 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 246 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 252 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 252 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 269 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 269 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 271 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 271 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 278 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 278 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 294 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 294 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 302 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 302 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 308 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 308 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 300 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 300 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 245 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 245 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 247 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 247 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 254 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 254 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 293 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 293 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 295 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 295 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 309 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 309 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 99
                     tNeighbor =  tNeighbors( 99 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 307 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 307 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 100 exists
                 if ( tNeighbors( 100 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 271 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 271 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 302 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 302 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 247 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 247 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 270 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 270 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 272 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 272 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 295 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 295 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 303 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 303 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 309 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 309 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 301 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 301 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 246 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 246 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 248 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 248 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 294 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 294 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 296 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 296 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 310 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 310 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 100
                     tNeighbor =  tNeighbors( 100 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 308 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 308 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 101 exists
                 if ( tNeighbors( 101 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 272 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 272 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 303 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 303 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 248 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 248 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 271 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 271 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 273 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 273 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 296 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 296 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 304 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 304 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 310 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 310 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 302 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 302 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 247 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 247 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 249 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 249 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 295 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 295 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 297 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 297 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 311 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 311 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 101
                     tNeighbor =  tNeighbors( 101 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 309 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 309 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 102 exists
                 if ( tNeighbors( 102 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 273 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 273 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 304 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 304 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 249 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 249 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 272 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 272 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 274 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 274 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 297 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 297 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 305 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 305 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 311 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 311 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 303 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 303 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 248 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 248 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 250 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 250 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 296 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 296 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 298 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 298 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 312 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 312 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 102
                     tNeighbor =  tNeighbors( 102 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 310 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 310 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 103 exists
                 if ( tNeighbors( 103 ) != NULL )
                 {
                     // get neighbor 0 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 0 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 274 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 274 ) = tNeighbor;
                         }
                     }

                     // get neighbor 1 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 277 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 277 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 305 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 305 ) = tNeighbor;
                         }
                     }

                     // get neighbor 6 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 6 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 250 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 250 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 253 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 253 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 273 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 273 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 275 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 275 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 279 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 279 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 298 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 298 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 306 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 306 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 312 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 312 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 304 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 304 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 249 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 249 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 251 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 251 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 255 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 255 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 297 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 297 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 299 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 299 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 313 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 313 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 103
                     tNeighbor =  tNeighbors( 103 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 311 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 311 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 104 exists
                 if ( tNeighbors( 104 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 278 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 278 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 308 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 308 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 254 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 254 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 276 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 276 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 280 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 280 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 301 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 301 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 309 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 309 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 315 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 315 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 307 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 307 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 252 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 252 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 256 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 256 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 300 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 300 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 302 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 302 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 316 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 316 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 104
                     tNeighbor =  tNeighbors( 104 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 314 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 314 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 105 exists
                 if ( tNeighbors( 105 ) != NULL )
                 {
                     // get neighbor 5 of neighbor 105
                     tNeighbor =  tNeighbors( 105 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 309 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 309 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 105
                     tNeighbor =  tNeighbors( 105 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 302 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 302 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 105
                     tNeighbor =  tNeighbors( 105 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 310 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 310 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 105
                     tNeighbor =  tNeighbors( 105 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 316 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 316 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 105
                     tNeighbor =  tNeighbors( 105 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 308 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 308 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 105
                     tNeighbor =  tNeighbors( 105 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 301 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 301 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 105
                     tNeighbor =  tNeighbors( 105 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 303 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 303 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 105
                     tNeighbor =  tNeighbors( 105 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 317 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 317 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 105
                     tNeighbor =  tNeighbors( 105 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 315 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 315 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 106 exists
                 if ( tNeighbors( 106 ) != NULL )
                 {
                     // get neighbor 5 of neighbor 106
                     tNeighbor =  tNeighbors( 106 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 310 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 310 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 106
                     tNeighbor =  tNeighbors( 106 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 303 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 303 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 106
                     tNeighbor =  tNeighbors( 106 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 311 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 311 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 106
                     tNeighbor =  tNeighbors( 106 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 317 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 317 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 106
                     tNeighbor =  tNeighbors( 106 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 309 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 309 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 106
                     tNeighbor =  tNeighbors( 106 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 302 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 302 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 106
                     tNeighbor =  tNeighbors( 106 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 304 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 304 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 106
                     tNeighbor =  tNeighbors( 106 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 318 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 318 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 106
                     tNeighbor =  tNeighbors( 106 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 316 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 316 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 107 exists
                 if ( tNeighbors( 107 ) != NULL )
                 {
                     // get neighbor 5 of neighbor 107
                     tNeighbor =  tNeighbors( 107 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 311 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 311 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 107
                     tNeighbor =  tNeighbors( 107 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 304 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 304 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 107
                     tNeighbor =  tNeighbors( 107 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 312 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 312 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 107
                     tNeighbor =  tNeighbors( 107 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 318 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 318 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 107
                     tNeighbor =  tNeighbors( 107 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 310 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 310 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 107
                     tNeighbor =  tNeighbors( 107 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 303 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 303 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 107
                     tNeighbor =  tNeighbors( 107 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 305 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 305 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 107
                     tNeighbor =  tNeighbors( 107 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 319 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 319 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 107
                     tNeighbor =  tNeighbors( 107 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 317 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 317 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 108 exists
                 if ( tNeighbors( 108 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 279 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 279 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 312 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 312 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 255 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 255 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 277 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 277 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 281 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 281 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 305 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 305 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 313 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 313 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 319 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 319 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 311 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 311 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 253 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 253 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 257 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 257 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 304 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 304 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 306 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 306 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 320 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 320 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 108
                     tNeighbor =  tNeighbors( 108 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 318 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 318 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 109 exists
                 if ( tNeighbors( 109 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 280 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 280 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 315 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 315 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 256 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 256 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 278 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 278 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 282 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 282 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 308 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 308 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 316 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 316 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 322 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 322 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 314 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 314 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 254 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 254 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 258 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 258 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 307 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 307 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 309 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 309 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 323 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 323 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 109
                     tNeighbor =  tNeighbors( 109 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 321 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 321 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 110 exists
                 if ( tNeighbors( 110 ) != NULL )
                 {
                     // get neighbor 5 of neighbor 110
                     tNeighbor =  tNeighbors( 110 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 316 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 316 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 110
                     tNeighbor =  tNeighbors( 110 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 309 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 309 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 110
                     tNeighbor =  tNeighbors( 110 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 317 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 317 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 110
                     tNeighbor =  tNeighbors( 110 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 323 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 323 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 110
                     tNeighbor =  tNeighbors( 110 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 315 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 315 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 110
                     tNeighbor =  tNeighbors( 110 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 308 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 308 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 110
                     tNeighbor =  tNeighbors( 110 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 310 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 310 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 110
                     tNeighbor =  tNeighbors( 110 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 324 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 324 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 110
                     tNeighbor =  tNeighbors( 110 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 322 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 322 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 111 exists
                 if ( tNeighbors( 111 ) != NULL )
                 {
                     // get neighbor 5 of neighbor 111
                     tNeighbor =  tNeighbors( 111 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 317 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 317 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 111
                     tNeighbor =  tNeighbors( 111 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 310 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 310 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 111
                     tNeighbor =  tNeighbors( 111 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 318 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 318 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 111
                     tNeighbor =  tNeighbors( 111 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 324 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 324 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 111
                     tNeighbor =  tNeighbors( 111 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 316 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 316 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 111
                     tNeighbor =  tNeighbors( 111 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 309 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 309 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 111
                     tNeighbor =  tNeighbors( 111 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 311 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 311 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 111
                     tNeighbor =  tNeighbors( 111 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 325 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 325 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 111
                     tNeighbor =  tNeighbors( 111 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 323 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 323 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 112 exists
                 if ( tNeighbors( 112 ) != NULL )
                 {
                     // get neighbor 5 of neighbor 112
                     tNeighbor =  tNeighbors( 112 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 318 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 318 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 112
                     tNeighbor =  tNeighbors( 112 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 311 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 311 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 112
                     tNeighbor =  tNeighbors( 112 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 319 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 319 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 112
                     tNeighbor =  tNeighbors( 112 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 325 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 325 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 112
                     tNeighbor =  tNeighbors( 112 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 317 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 317 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 112
                     tNeighbor =  tNeighbors( 112 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 310 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 310 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 112
                     tNeighbor =  tNeighbors( 112 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 312 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 312 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 112
                     tNeighbor =  tNeighbors( 112 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 326 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 326 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 112
                     tNeighbor =  tNeighbors( 112 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 324 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 324 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 113 exists
                 if ( tNeighbors( 113 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 281 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 281 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 319 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 319 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 257 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 257 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 279 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 279 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 283 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 283 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 312 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 312 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 320 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 320 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 326 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 326 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 318 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 318 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 255 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 255 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 259 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 259 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 311 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 311 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 313 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 313 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 327 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 327 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 113
                     tNeighbor =  tNeighbors( 113 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 325 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 325 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 114 exists
                 if ( tNeighbors( 114 ) != NULL )
                 {
                     // get neighbor 3 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 282 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 282 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 322 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 322 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 258 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 258 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 280 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 280 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 284 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 284 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 315 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 315 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 323 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 323 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 329 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 329 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 321 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 321 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 256 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 256 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 260 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 260 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 314 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 314 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 316 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 316 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 330 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 330 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 114
                     tNeighbor =  tNeighbors( 114 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 328 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 328 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 115 exists
                 if ( tNeighbors( 115 ) != NULL )
                 {
                     // get neighbor 5 of neighbor 115
                     tNeighbor =  tNeighbors( 115 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 323 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 323 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 115
                     tNeighbor =  tNeighbors( 115 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 316 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 316 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 115
                     tNeighbor =  tNeighbors( 115 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 324 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 324 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 115
                     tNeighbor =  tNeighbors( 115 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 330 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 330 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 115
                     tNeighbor =  tNeighbors( 115 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 322 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 322 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 115
                     tNeighbor =  tNeighbors( 115 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 315 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 315 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 115
                     tNeighbor =  tNeighbors( 115 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 317 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 317 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 115
                     tNeighbor =  tNeighbors( 115 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 331 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 331 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 115
                     tNeighbor =  tNeighbors( 115 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 329 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 329 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 116 exists
                 if ( tNeighbors( 116 ) != NULL )
                 {
                     // get neighbor 5 of neighbor 116
                     tNeighbor =  tNeighbors( 116 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 324 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 324 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 116
                     tNeighbor =  tNeighbors( 116 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 317 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 317 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 116
                     tNeighbor =  tNeighbors( 116 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 325 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 325 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 116
                     tNeighbor =  tNeighbors( 116 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 331 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 331 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 116
                     tNeighbor =  tNeighbors( 116 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 323 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 323 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 116
                     tNeighbor =  tNeighbors( 116 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 316 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 316 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 116
                     tNeighbor =  tNeighbors( 116 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 318 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 318 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 116
                     tNeighbor =  tNeighbors( 116 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 332 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 332 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 116
                     tNeighbor =  tNeighbors( 116 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 330 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 330 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 117 exists
                 if ( tNeighbors( 117 ) != NULL )
                 {
                     // get neighbor 5 of neighbor 117
                     tNeighbor =  tNeighbors( 117 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 325 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 325 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 117
                     tNeighbor =  tNeighbors( 117 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 318 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 318 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 117
                     tNeighbor =  tNeighbors( 117 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 326 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 326 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 117
                     tNeighbor =  tNeighbors( 117 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 332 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 332 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 117
                     tNeighbor =  tNeighbors( 117 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 324 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 324 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 117
                     tNeighbor =  tNeighbors( 117 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 317 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 317 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 117
                     tNeighbor =  tNeighbors( 117 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 319 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 319 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 117
                     tNeighbor =  tNeighbors( 117 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 333 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 333 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 117
                     tNeighbor =  tNeighbors( 117 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 331 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 331 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 118 exists
                 if ( tNeighbors( 118 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 283 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 283 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 326 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 326 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 259 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 259 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 281 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 281 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 285 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 285 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 319 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 319 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 327 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 327 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 333 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 333 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 325 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 325 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 257 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 257 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 261 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 261 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 318 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 318 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 320 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 320 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 334 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 334 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 118
                     tNeighbor =  tNeighbors( 118 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 332 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 332 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 119 exists
                 if ( tNeighbors( 119 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 287 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 287 ) = tNeighbor;
                         }
                     }

                     // get neighbor 3 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 3 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 284 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 284 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 329 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 329 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 263 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 263 ) = tNeighbor;
                         }
                     }

                     // get neighbor 9 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 9 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 260 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 260 ) = tNeighbor;
                         }
                     }

                     // get neighbor 10 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 10 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 282 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 282 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 288 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 288 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 286 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 286 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 322 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 322 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 330 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 330 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 336 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 336 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 328 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 328 ) = tNeighbor;
                         }
                     }

                     // get neighbor 18 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 18 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 258 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 258 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 264 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 264 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 262 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 262 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 321 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 321 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 323 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 323 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 337 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 337 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 119
                     tNeighbor =  tNeighbors( 119 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 335 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 335 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 120 exists
                 if ( tNeighbors( 120 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 288 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 288 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 330 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 330 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 264 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 264 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 289 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 289 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 287 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 287 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 323 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 323 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 331 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 331 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 337 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 337 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 329 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 329 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 265 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 265 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 263 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 263 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 322 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 322 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 324 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 324 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 338 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 338 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 120
                     tNeighbor =  tNeighbors( 120 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 336 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 336 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 121 exists
                 if ( tNeighbors( 121 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 289 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 289 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 331 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 331 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 265 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 265 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 290 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 290 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 288 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 288 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 324 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 324 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 332 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 332 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 338 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 338 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 330 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 330 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 266 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 266 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 264 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 264 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 323 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 323 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 325 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 325 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 339 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 339 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 121
                     tNeighbor =  tNeighbors( 121 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 337 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 337 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 122 exists
                 if ( tNeighbors( 122 ) != NULL )
                 {
                     // get neighbor 2 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 290 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 290 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 332 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 332 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 266 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 266 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 291 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 291 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 289 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 289 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 325 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 325 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 333 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 333 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 339 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 339 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 331 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 331 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 267 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 267 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 265 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 265 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 324 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 324 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 326 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 326 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 340 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 340 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 122
                     tNeighbor =  tNeighbors( 122 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 338 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 338 ) = tNeighbor;
                         }
                     }

                 }
                 // test if neighbor 123 exists
                 if ( tNeighbors( 123 ) != NULL )
                 {
                     // get neighbor 1 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 1 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 285 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 285 ) = tNeighbor;
                         }
                     }

                     // get neighbor 2 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 2 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 291 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 291 ) = tNeighbor;
                         }
                     }

                     // get neighbor 5 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 5 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 333 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 333 ) = tNeighbor;
                         }
                     }

                     // get neighbor 7 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 7 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 261 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 261 ) = tNeighbor;
                         }
                     }

                     // get neighbor 8 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 8 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 267 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 267 ) = tNeighbor;
                         }
                     }

                     // get neighbor 11 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 11 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 283 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 283 ) = tNeighbor;
                         }
                     }

                     // get neighbor 12 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 12 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 292 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 292 ) = tNeighbor;
                         }
                     }

                     // get neighbor 13 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 13 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 290 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 290 ) = tNeighbor;
                         }
                     }

                     // get neighbor 14 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 14 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 326 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 326 ) = tNeighbor;
                         }
                     }

                     // get neighbor 15 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 15 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 334 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 334 ) = tNeighbor;
                         }
                     }

                     // get neighbor 16 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 16 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 340 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 340 ) = tNeighbor;
                         }
                     }

                     // get neighbor 17 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 17 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 332 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 332 ) = tNeighbor;
                         }
                     }

                     // get neighbor 19 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 19 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 259 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 259 ) = tNeighbor;
                         }
                     }

                     // get neighbor 20 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 20 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 268 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 268 ) = tNeighbor;
                         }
                     }

                     // get neighbor 21 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 21 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 266 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 266 ) = tNeighbor;
                         }
                     }

                     // get neighbor 22 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 22 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 325 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 325 ) = tNeighbor;
                         }
                     }

                     // get neighbor 23 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 23 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 327 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 327 ) = tNeighbor;
                         }
                     }

                     // get neighbor 24 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 24 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 341 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 341 ) = tNeighbor;
                         }
                     }

                     // get neighbor 25 of neighbor 123
                     tNeighbor =  tNeighbors( 123 )->get_neighbor( 25 );

                     // test if neighbor exists and was not copied yet
                     if ( tNeighbor != NULL && tNeighbors( 339 ) == NULL )
                     {
                         // test if neighbor is on same level
                         if ( tNeighbor->get_level() == mLevel )
                         {
                             // copy pointer in big array
                             tNeighbors( 339 ) = tNeighbor;
                         }
                     }

                 }
             } // end order 3
             } // end order 2

             // initialize element counter
             uint tCount = 0;

             // count number of existing elements
             for( auto tNeighbor : tNeighbors )
             {
                 if ( tNeighbor != NULL )
                 {
                     ++tCount;
                 }
             }

             // allocate output Cell
             aNeighbors.resize( tCount, nullptr );

             // reset counter
             tCount = 0;

             // copy existing elements
             for( auto tNeighbor : tNeighbors )
             {
                 if ( tNeighbor != NULL )
                 {
                     aNeighbors( tCount++ ) = tNeighbor;
                 }
             }
        }

// ----------------------------------------------------------------------------
    } /* namespace hmr */
} /* namespace moris */

#endif /* SRC_HMR_FN_HMR_BACKGROUND_ELEMENT_NEIGHBORS_3D_HPP_ */
