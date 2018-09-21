/*
 * cl_HMR_BSpline_Element_Quad4.hpp
 *
 *  Created on: July 26, 2018
 *  using MATLAB
 */
 
#ifndef SRC_HMR_CL_HMR_BSPLINE_ELEMENT_QUAD4_HPP_
#define SRC_HMR_CL_HMR_BSPLINE_ELEMENT_QUAD4_HPP_

#include "cl_HMR_BSpline_Element.hpp" //HMR/src
#include "fn_HMR_get_basis_neighbors_2d.hpp" //HMR/src

namespace moris
{
    namespace hmr
    {
// ----------------------------------------------------------------------------

        /**
        * Returns the geometry type of this element
        *
        * @return mtk::Geometry_Type
        */
        template<>
        mtk::Geometry_Type
        BSpline_Element< 2, 4 >::get_geometry_type() const
        {
            return mtk::Geometry_Type::QUAD;
        }

// ----------------------------------------------------------------------------

        /**
         * node IDs needed for VTK output
         *
         * @param[out] moris::Matrix< DDLUMat > 
         *
         * @return void
         *
         */
        template<>
        void
        BSpline_Element< 2, 4 >::get_basis_indices_for_vtk(
            Matrix< DDLUMat > & aBasis )
        {
            // loop over all nodes
            for( uint k=0; k<4; ++k )
            {
                aBasis( k ) = mBasis[ k ]->get_memory_index();
            }
        }
// ----------------------------------------------------------------------------

        /**
         * returns the ijk position of a given basis
         *
         * @param[in]  aBasisNumber   element local number of basis
         * @param[out] aIJK           proc local ijk position of this basis
         *
         * @return void
         *
         */
        template<>
        void
        BSpline_Element< 2, 4 >::get_ijk_of_basis(
            const uint & aBasisNumber, 
            luint      * aIJK ) 
        {
            // get element local coordinate
            switch ( aBasisNumber )
            {
                case( 0 ) :
                {
                    aIJK[ 0 ] = 0 ;
                    aIJK[ 1 ] = 0 ;
                    break;
                }
                case( 1 ) :
                {
                    aIJK[ 0 ] = 1 ;
                    aIJK[ 1 ] = 0 ;
                    break;
                }
                case( 2 ) :
                {
                    aIJK[ 0 ] = 1 ;
                    aIJK[ 1 ] = 1 ;
                    break;
                }
                case( 3 ) :
                {
                    aIJK[ 0 ] = 0 ;
                    aIJK[ 1 ] = 1 ;
                    break;
                }
            }

            // get position of element on background mesh
            const luint * tElIJK = mElement->get_ijk();

            // add element offset
            aIJK[ 0 ] += tElIJK[ 0 ];
            aIJK[ 1 ] += tElIJK[ 1 ];
        }

// ----------------------------------------------------------------------------

        /**
        * Links each basis of an element with neighbor basis.
        *
        * @param[inout] aAllElementsOnProc   cell containing all B-Spline
        *                                    elements including the aura
        * @return void
        */
        template<>
        void
        BSpline_Element< 2, 4 >::link_basis_with_neighbors(
              moris::Cell< Element* > & aAllElementsOnProc )
        {
             // initialize frame of basis around basis from this element
             Basis* tBasis[ 12 ] = { nullptr };

             // get pointer to neighbor  0
             Element* tNeighbor = this->get_neighbor( aAllElementsOnProc, 0 );

             // test if neighbor  0 exists
             if ( tNeighbor != NULL )
             {
                 // copy pointers into frame
                 tBasis[   1 ] = tNeighbor->get_basis(   0 );
                 tBasis[   2 ] = tNeighbor->get_basis(   1 );
             }

             // get pointer to neighbor  1
             tNeighbor = this->get_neighbor( aAllElementsOnProc, 1 );

             // test if neighbor  1 exists
             if ( tNeighbor != NULL )
             {
                 // copy pointers into frame
                 tBasis[   5 ] = tNeighbor->get_basis(   1 );
                 tBasis[   7 ] = tNeighbor->get_basis(   2 );
             }

             // get pointer to neighbor  2
             tNeighbor = this->get_neighbor( aAllElementsOnProc, 2 );

             // test if neighbor  2 exists
             if ( tNeighbor != NULL )
             {
                 // copy pointers into frame
                 tBasis[   9 ] = tNeighbor->get_basis(   3 );
                 tBasis[  10 ] = tNeighbor->get_basis(   2 );
             }

             // get pointer to neighbor  3
             tNeighbor = this->get_neighbor( aAllElementsOnProc, 3 );

             // test if neighbor  3 exists
             if ( tNeighbor != NULL )
             {
                 // copy pointers into frame
                 tBasis[   4 ] = tNeighbor->get_basis(   0 );
                 tBasis[   6 ] = tNeighbor->get_basis(   3 );
             }

             // get pointer to neighbor  4
             tNeighbor = this->get_neighbor( aAllElementsOnProc, 4 );

             // test if neighbor  4 exists
             if ( tNeighbor != NULL )
             {
                 // copy pointers into frame
                 tBasis[   0 ] = tNeighbor->get_basis(   0 );
                 tBasis[   1 ] = tNeighbor->get_basis(   1 );
                 tBasis[   4 ] = tNeighbor->get_basis(   3 );
             }

             // get pointer to neighbor  5
             tNeighbor = this->get_neighbor( aAllElementsOnProc, 5 );

             // test if neighbor  5 exists
             if ( tNeighbor != NULL )
             {
                 // copy pointers into frame
                 tBasis[   2 ] = tNeighbor->get_basis(   0 );
                 tBasis[   3 ] = tNeighbor->get_basis(   1 );
                 tBasis[   5 ] = tNeighbor->get_basis(   2 );
             }

             // get pointer to neighbor  6
             tNeighbor = this->get_neighbor( aAllElementsOnProc, 6 );

             // test if neighbor  6 exists
             if ( tNeighbor != NULL )
             {
                 // copy pointers into frame
                 tBasis[   7 ] = tNeighbor->get_basis(   1 );
                 tBasis[  10 ] = tNeighbor->get_basis(   3 );
                 tBasis[  11 ] = tNeighbor->get_basis(   2 );
             }

             // get pointer to neighbor  7
             tNeighbor = this->get_neighbor( aAllElementsOnProc, 7 );

             // test if neighbor  7 exists
             if ( tNeighbor != NULL )
             {
                 // copy pointers into frame
                 tBasis[   6 ] = tNeighbor->get_basis(   0 );
                 tBasis[   8 ] = tNeighbor->get_basis(   3 );
                 tBasis[   9 ] = tNeighbor->get_basis(   2 );
             }

             // test if basis 0 exists
             if ( mBasis[   0 ] != NULL )
             {
                 // test if basis 0 has been processed
                 if ( ! mBasis[   0 ]->is_flagged() )
                 {
                     // link neighbors of basis 0
                     mBasis[   0 ]->insert_neighbor(  0, tBasis[   1 ] ); 
                     mBasis[   0 ]->insert_neighbor(  1, mBasis[   1 ] ); 
                     mBasis[   0 ]->insert_neighbor(  2, mBasis[   3 ] ); 
                     mBasis[   0 ]->insert_neighbor(  3, tBasis[   4 ] ); 
                     mBasis[   0 ]->insert_neighbor(  4, tBasis[   0 ] ); 
                     mBasis[   0 ]->insert_neighbor(  5, tBasis[   2 ] ); 
                     mBasis[   0 ]->insert_neighbor(  6, mBasis[   2 ] ); 
                     mBasis[   0 ]->insert_neighbor(  7, tBasis[   6 ] ); 

                     // flag this basis
                     mBasis[   0 ]->flag();
                 }

             }

             // test if basis 1 exists
             if ( mBasis[   1 ] != NULL )
             {
                 // test if basis 1 has been processed
                 if ( ! mBasis[   1 ]->is_flagged() )
                 {
                     // link neighbors of basis 1
                     mBasis[   1 ]->insert_neighbor(  0, tBasis[   2 ] ); 
                     mBasis[   1 ]->insert_neighbor(  1, tBasis[   5 ] ); 
                     mBasis[   1 ]->insert_neighbor(  2, mBasis[   2 ] ); 
                     mBasis[   1 ]->insert_neighbor(  3, mBasis[   0 ] ); 
                     mBasis[   1 ]->insert_neighbor(  4, tBasis[   1 ] ); 
                     mBasis[   1 ]->insert_neighbor(  5, tBasis[   3 ] ); 
                     mBasis[   1 ]->insert_neighbor(  6, tBasis[   7 ] ); 
                     mBasis[   1 ]->insert_neighbor(  7, mBasis[   3 ] ); 

                     // flag this basis
                     mBasis[   1 ]->flag();
                 }

             }

             // test if basis 2 exists
             if ( mBasis[   2 ] != NULL )
             {
                 // test if basis 2 has been processed
                 if ( ! mBasis[   2 ]->is_flagged() )
                 {
                     // link neighbors of basis 2
                     mBasis[   2 ]->insert_neighbor(  0, mBasis[   1 ] ); 
                     mBasis[   2 ]->insert_neighbor(  1, tBasis[   7 ] ); 
                     mBasis[   2 ]->insert_neighbor(  2, tBasis[  10 ] ); 
                     mBasis[   2 ]->insert_neighbor(  3, mBasis[   3 ] ); 
                     mBasis[   2 ]->insert_neighbor(  4, mBasis[   0 ] ); 
                     mBasis[   2 ]->insert_neighbor(  5, tBasis[   5 ] ); 
                     mBasis[   2 ]->insert_neighbor(  6, tBasis[  11 ] ); 
                     mBasis[   2 ]->insert_neighbor(  7, tBasis[   9 ] ); 

                     // flag this basis
                     mBasis[   2 ]->flag();
                 }

             }

             // test if basis 3 exists
             if ( mBasis[   3 ] != NULL )
             {
                 // test if basis 3 has been processed
                 if ( ! mBasis[   3 ]->is_flagged() )
                 {
                     // link neighbors of basis 3
                     mBasis[   3 ]->insert_neighbor(  0, mBasis[   0 ] ); 
                     mBasis[   3 ]->insert_neighbor(  1, mBasis[   2 ] ); 
                     mBasis[   3 ]->insert_neighbor(  2, tBasis[   9 ] ); 
                     mBasis[   3 ]->insert_neighbor(  3, tBasis[   6 ] ); 
                     mBasis[   3 ]->insert_neighbor(  4, tBasis[   4 ] ); 
                     mBasis[   3 ]->insert_neighbor(  5, mBasis[   1 ] ); 
                     mBasis[   3 ]->insert_neighbor(  6, tBasis[  10 ] ); 
                     mBasis[   3 ]->insert_neighbor(  7, tBasis[   8 ] ); 

                     // flag this basis
                     mBasis[   3 ]->flag();
                 }

             }

        }
// ----------------------------------------------------------------------------

        /**
        * Refines the basis of an element
        *
        * @param[inout] aBasisNumber         element local index of basis that is to be refined
        * @param[inout] aBasisCounter        counter to keep track of generated basis
        *
        * @return void
        */
        template<>
        void
        BSpline_Element< 2, 4 >::refine_basis( const uint & aBasisNumber, luint & aBasisCounter )
        {
            // get pointer to basis
            Basis* tBasis = mBasis[ aBasisNumber ];

            // test if basis exists
            if ( tBasis != NULL )
            {
                // test if basis has been refined already
                if ( ! tBasis->has_children() ) 
                {
                   // create temporary container for children
                   tBasis->init_children_container();

                   // pointer to basis neighbor
                   Basis* tNeighbor;

                   // get neighbor 0
                   tNeighbor = tBasis->get_neighbor( 0 );

                   // test if neighbor 0 exists
                   if ( tNeighbor != NULL )
                   {
                       // test if neighbor has children
                       if ( tNeighbor->has_children() )
                       {
                           // copy children of neighbor
                           tBasis->insert_child(  0, tNeighbor->get_child(  6 ) );
                           tBasis->insert_child(  1, tNeighbor->get_child(  7 ) );
                           tBasis->insert_child(  2, tNeighbor->get_child(  8 ) );
                       }
                   }

                   // get neighbor 1
                   tNeighbor = tBasis->get_neighbor( 1 );

                   // test if neighbor 1 exists
                   if ( tNeighbor != NULL )
                   {
                       // test if neighbor has children
                       if ( tNeighbor->has_children() )
                       {
                           // copy children of neighbor
                           tBasis->insert_child(  2, tNeighbor->get_child(  0 ) );
                           tBasis->insert_child(  5, tNeighbor->get_child(  3 ) );
                           tBasis->insert_child(  8, tNeighbor->get_child(  6 ) );
                       }
                   }

                   // get neighbor 2
                   tNeighbor = tBasis->get_neighbor( 2 );

                   // test if neighbor 2 exists
                   if ( tNeighbor != NULL )
                   {
                       // test if neighbor has children
                       if ( tNeighbor->has_children() )
                       {
                           // copy children of neighbor
                           tBasis->insert_child(  6, tNeighbor->get_child(  0 ) );
                           tBasis->insert_child(  7, tNeighbor->get_child(  1 ) );
                           tBasis->insert_child(  8, tNeighbor->get_child(  2 ) );
                       }
                   }

                   // get neighbor 3
                   tNeighbor = tBasis->get_neighbor( 3 );

                   // test if neighbor 3 exists
                   if ( tNeighbor != NULL )
                   {
                       // test if neighbor has children
                       if ( tNeighbor->has_children() )
                       {
                           // copy children of neighbor
                           tBasis->insert_child(  0, tNeighbor->get_child(  2 ) );
                           tBasis->insert_child(  3, tNeighbor->get_child(  5 ) );
                           tBasis->insert_child(  6, tNeighbor->get_child(  8 ) );
                       }
                   }

                   // get neighbor 4
                   tNeighbor = tBasis->get_neighbor( 4 );

                   // test if neighbor 4 exists
                   if ( tNeighbor != NULL )
                   {
                       // test if neighbor has children
                       if ( tNeighbor->has_children() )
                       {
                           // copy children of neighbor
                           tBasis->insert_child(  0, tNeighbor->get_child(  8 ) );
                       }
                   }

                   // get neighbor 5
                   tNeighbor = tBasis->get_neighbor( 5 );

                   // test if neighbor 5 exists
                   if ( tNeighbor != NULL )
                   {
                       // test if neighbor has children
                       if ( tNeighbor->has_children() )
                       {
                           // copy children of neighbor
                           tBasis->insert_child(  2, tNeighbor->get_child(  6 ) );
                       }
                   }

                   // get neighbor 6
                   tNeighbor = tBasis->get_neighbor( 6 );

                   // test if neighbor 6 exists
                   if ( tNeighbor != NULL )
                   {
                       // test if neighbor has children
                       if ( tNeighbor->has_children() )
                       {
                           // copy children of neighbor
                           tBasis->insert_child(  8, tNeighbor->get_child(  0 ) );
                       }
                   }

                   // get neighbor 7
                   tNeighbor = tBasis->get_neighbor( 7 );

                   // test if neighbor 7 exists
                   if ( tNeighbor != NULL )
                   {
                       // test if neighbor has children
                       if ( tNeighbor->has_children() )
                       {
                           // copy children of neighbor
                           tBasis->insert_child(  6, tNeighbor->get_child(  2 ) );
                       }
                   }

                   // level of child basis
                   uint tLevel = tBasis->get_level() + 1;

                   // position of basis
                   const luint* tParentIJ  = tBasis->get_ijk();

                   // minumum i-position
                   luint tIMin = 2*tParentIJ[ 0 ];

                   // minumum j-position
                   luint tJMin = 2*tParentIJ[ 1 ];

                   // maximum i-position
                   luint tIMax = tIMin + 3;

                   // maximum j-position
                   luint tJMax = tJMin + 3;

                   // initialize counter
                   uint tCount = 0;

                   // loop over all positions
                   for( luint j=tJMin; j<tJMax; ++j )
                   {
                       for( luint i=tIMin; i<tIMax; ++i )
                       {
                           // test if child does not exist
                           if( tBasis->get_child( tCount ) == NULL )
                           {
                               // calculate i-j position of child
                               luint tIJ[ 2 ] = { i, j };

                               // create child
                               tBasis->insert_child( tCount, 
                                   new BSpline< 2, 9, 8 >( tIJ, tLevel, gNoProcOwner ) );

                               // increment basis counter
                               ++aBasisCounter;
                           }

                           // increment counter
                           ++tCount;
                       }
                   }
                }
            }
        }

// ----------------------------------------------------------------------------

        /**
        * Refines a B-Spline element
        *
        * @param[inout] aAllElementsOnProc   cell containing all B-Spline
        *                                    elements including the aura
        * @param[inout] aBasisCounter        counter to keep track of generated basis
        *
        * @return void
        */
        template<>
        void
        BSpline_Element< 2, 4 >::refine( moris::Cell< Element* > & aAllElementsOnProc, luint & aBasisCounter )
        {
            // refine basis if they have not been refined already
            for( uint k=0; k<4; ++k )
            {
                this->refine_basis( k, aBasisCounter );
            }

            // initialize temporary basis pattern
            Basis* tBasis[ 9 ] = { nullptr };

            // populate basis pattern
            if ( mBasis[   0 ] != NULL )
            {
                if ( tBasis[   0 ] == NULL )
                {
                    tBasis[   0 ] = mBasis[   0 ]->get_child(   4 );
                }
                if ( tBasis[   1 ] == NULL )
                {
                    tBasis[   1 ] = mBasis[   0 ]->get_child(   5 );
                }
                if ( tBasis[   3 ] == NULL )
                {
                    tBasis[   3 ] = mBasis[   0 ]->get_child(   7 );
                }
                if ( tBasis[   4 ] == NULL )
                {
                    tBasis[   4 ] = mBasis[   0 ]->get_child(   8 );
                }
            }

            if ( mBasis[   1 ] != NULL )
            {
                if ( tBasis[   1 ] == NULL )
                {
                    tBasis[   1 ] = mBasis[   1 ]->get_child(   3 );
                }
                if ( tBasis[   2 ] == NULL )
                {
                    tBasis[   2 ] = mBasis[   1 ]->get_child(   4 );
                }
                if ( tBasis[   4 ] == NULL )
                {
                    tBasis[   4 ] = mBasis[   1 ]->get_child(   6 );
                }
                if ( tBasis[   5 ] == NULL )
                {
                    tBasis[   5 ] = mBasis[   1 ]->get_child(   7 );
                }
            }

            if ( mBasis[   2 ] != NULL )
            {
                if ( tBasis[   4 ] == NULL )
                {
                    tBasis[   4 ] = mBasis[   2 ]->get_child(   0 );
                }
                if ( tBasis[   5 ] == NULL )
                {
                    tBasis[   5 ] = mBasis[   2 ]->get_child(   1 );
                }
                if ( tBasis[   7 ] == NULL )
                {
                    tBasis[   7 ] = mBasis[   2 ]->get_child(   3 );
                }
                if ( tBasis[   8 ] == NULL )
                {
                    tBasis[   8 ] = mBasis[   2 ]->get_child(   4 );
                }
            }

            if ( mBasis[   3 ] != NULL )
            {
                if ( tBasis[   3 ] == NULL )
                {
                    tBasis[   3 ] = mBasis[   3 ]->get_child(   1 );
                }
                if ( tBasis[   4 ] == NULL )
                {
                    tBasis[   4 ] = mBasis[   3 ]->get_child(   2 );
                }
                if ( tBasis[   6 ] == NULL )
                {
                    tBasis[   6 ] = mBasis[   3 ]->get_child(   4 );
                }
                if ( tBasis[   7 ] == NULL )
                {
                    tBasis[   7 ] = mBasis[   3 ]->get_child(   5 );
                }
            }


            // initialize child container
            Element * tChildren[ 4 ];

            // populate child container
            for( uint k=0; k<4; ++k)
            {
                tChildren[ k ] = aAllElementsOnProc(
                    mElement->get_child( k )->get_memory_index() );
            }

            // assign basis to child 1
            tChildren[ 0 ]->insert_basis(  0, tBasis[   0 ] );
            tChildren[ 0 ]->insert_basis(  1, tBasis[   1 ] );
            tChildren[ 0 ]->insert_basis(  2, tBasis[   4 ] );
            tChildren[ 0 ]->insert_basis(  3, tBasis[   3 ] );

            // assign basis to child 2
            tChildren[ 1 ]->insert_basis(  0, tBasis[   1 ] );
            tChildren[ 1 ]->insert_basis(  1, tBasis[   2 ] );
            tChildren[ 1 ]->insert_basis(  2, tBasis[   5 ] );
            tChildren[ 1 ]->insert_basis(  3, tBasis[   4 ] );

            // assign basis to child 3
            tChildren[ 2 ]->insert_basis(  0, tBasis[   3 ] );
            tChildren[ 2 ]->insert_basis(  1, tBasis[   4 ] );
            tChildren[ 2 ]->insert_basis(  2, tBasis[   7 ] );
            tChildren[ 2 ]->insert_basis(  3, tBasis[   6 ] );

            // assign basis to child 4
            tChildren[ 3 ]->insert_basis(  0, tBasis[   4 ] );
            tChildren[ 3 ]->insert_basis(  1, tBasis[   5 ] );
            tChildren[ 3 ]->insert_basis(  2, tBasis[   8 ] );
            tChildren[ 3 ]->insert_basis(  3, tBasis[   7 ] );

            // set basis flag of element
            mChildrenBasisFlag = true;
        }

// ----------------------------------------------------------------------------
    } /* namespace hmr */
} /* namespace moris */

#endif /* SRC_HMR_CL_HMR_BSPLINE_ELEMENT_QUAD4_HPP_ */