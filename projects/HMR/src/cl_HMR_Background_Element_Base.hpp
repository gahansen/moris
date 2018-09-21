/*
 * clHMRElement.hpp
 *
 *  Created on: May 8, 2018
 *      Author: messe
 */

#ifndef SRC_HMR_CL_HMR_BACKGROUND_ELEMENT_BASE_HPP_
#define SRC_HMR_CL_HMR_BACKGROUND_ELEMENT_BASE_HPP_

#include <string>
#include "typedefs.hpp" //COR/src
#include "cl_Cell.hpp" //CON/src
#include "cl_Bitset.hpp" //CON/src
#include "cl_Matrix.hpp" //LINALG/src
#include "linalg_typedefs.hpp" //LINALG/src
#include "HMR_Globals.hpp" //HMR/src

namespace moris
{
    namespace hmr
    {
        /**
         * \brief Base class for templated Element
         *
         * Pointers to this class are storen in the background mesh.
         * This class contains level, position, neighborhood and parent-child
         * information, but none about Lagrange nodes or B-Spline basis.
         *
         */
        class Background_Element_Base
        {
//--------------------------------------------------------------------------------
        protected:
//--------------------------------------------------------------------------------

            //! Pointer to parent of an element. Points to null for elements
            //! on coarsest level.
            Background_Element_Base*    mParent;

            //! Global ID of an element. Unique and not to be changed after
            //! element is created.
            const luint                 mDomainID;

            //! Level on which element is defined. Can not be changed after element is created.
            const uint                  mLevel;

            //! Contains the ID of the proc that owns the element.
            //! For Aura elements, this value is updated by
            //! Background_Mesh_Base::synchronize_coarsest_aura
            moris_id                   mOwner;

            //! Tells if an element is active
            Bitset< gNumberOfPatterns > mActiveFlags;

            //! Tells if an element is refined
            Bitset< gNumberOfPatterns > mRefinedFlags;

            //! Special flag for padding elements
            bool                        mPaddingFlag  = false;

            //! Tells if the element has children.
            //! Not neccesarily identical to mRefinedFlag.
            bool                        mChildrenFlag = false;

            //! Tells if an element is flagged for refinement
            bool                        mRefinementQueueFlag = false;

            //! global index in whole domain, depends on pattern
            luint                       mDomainIndex[ gNumberOfPatterns ];

            //! index in memory, set by collect_all_elements from background mesh
            luint                       mMemoryIndex;

            //! flags indicating if the T-Matrix is supposed to be calculated
            Bitset< gNumberOfPatterns > mTMatrixFlags;

//--------------------------------------------------------------------------------
        public:
//--------------------------------------------------------------------------------

            /**
             * Default constuctor for element base class
             */
            Background_Element_Base(
                    Background_Element_Base * aParent,
                    const  uint             & aActivePattern,
                    const luint             & aID,
                    const  uint             & aLevel,
                    const  uint             & aOwner ) :
                        mParent     ( aParent ),
                        mDomainID   ( aID ),
                        mLevel      ( aLevel ),
                        mOwner      ( aOwner )
            {
                mActiveFlags.set( aActivePattern );
                mRefinedFlags.reset( aActivePattern);
            }

//--------------------------------------------------------------------------------

            /**
             * Default destructor for element base class. Virtual, does nothing.
             */
            virtual
            ~Background_Element_Base()
            {

            }

//--------------------------------------------------------------------------------

            /**
             * returns a unique system wide ID of the element
             *
             * @return    luint global ID of element
             */
            auto
            get_domain_id() const -> decltype( mDomainID )
            {
                return mDomainID;
            }


//--------------------------------------------------------------------------------
            /**
             * returns the level of an element
             *
             * @return   uint level of element
             */
            auto
            get_level() const -> decltype( mLevel )
            {
                return mLevel;
            }

//--------------------------------------------------------------------------------
            /**
             * Needed for the initialization process of the coarsest elements.
             * If the element is set as active, it can't be refined or be
             * a padding element.
             * Note that this function has no impact on potential children.
             *
             * @return void
             */
            void
            set_active_flag( const uint & aPattern )
            {
                // set active flag on
                mActiveFlags.set( aPattern );

                // an active element can not be refined at the same time
                mRefinedFlags.reset( aPattern );

                // an active element is not a padding element
                mPaddingFlag = false;

                // refine parents ( this is safe but not necessary )
                if( mLevel > 0 )
                {
                    if( ! mParent->is_refined( aPattern ) )
                    {
                        mParent->set_refined_flag( aPattern );
                    }
                }
            }

//--------------------------------------------------------------------------------

            /**
             * Needed for the initialization process of the coarsest elements.
             * If the element is set as refined, it can't be active/
             * Note that this function has no impact on potential children.
             *
             * @return void
             */
            void
            set_refined_flag( const uint & aPattern )
            {
                // a refined element is not active
                mActiveFlags.reset( aPattern );

                // set element as refined
                mRefinedFlags.set( aPattern );

                // remove element from refinement queue
                mRefinementQueueFlag = false;

                // refine parents ( this is safe but not necessary )
                if( mLevel > 0 )
                {
                    if( ! mParent->is_refined( aPattern ) )
                    {
                        mParent->set_refined_flag( aPattern );
                    }
                }
            }

//--------------------------------------------------------------------------------

            /**
             * Needed for the initialization process of the coarsest elements.
             * If the element is a padding element, it can't be active, and is
             * always refined.
             * Note that this function has no impact on potential children.
             *
             * @return void
             */
            void
            set_padding_flag()
            {
                // padding elements are never active
                mActiveFlags.reset();

                // padding elements are always refined
                for( uint k=0; k<gNumberOfPatterns; ++k )
                {
                    mRefinedFlags.set( k );
                }

                // set padding switch of element
                mPaddingFlag = true;

                // padding elements are not owned by any proc
                mOwner       = gNoProcOwner;
            }

 //--------------------------------------------------------------------------------

            /**
             * Tells which processor the element belongs to.
             * Note that padding elements are not owned by any proc.
             * This value is then UINT_MAX
             *
             * @return uint  ID of proc owing this element
             */
            auto
            get_owner() const -> decltype ( mOwner )
            {
                return mOwner;
            }

//--------------------------------------------------------------------------------

            /**
             * sets the owner of an element
             *
             * @return void
             */
            void
            set_owner( const moris_id & aOwner)
            {
                mOwner = aOwner;
            }
//--------------------------------------------------------------------------------

            /**
             * ID of ancestor at coarsest level
             *
             * @return luint ID of parent on top level
             */
            luint
            get_ancestor_id()
            {
                // get parent of element
                Background_Element_Base* tParent = this;

                for( uint k=mLevel; k>0; --k )
                {
                    tParent = tParent->get_parent();
                }

                return tParent->get_domain_id();
            }

//--------------------------------------------------------------------------------

            /**
             * tells if an element is refined
             *
             * @return bool   true if refined
             */
            bool
            is_refined( const uint & aPattern ) const
            {
                return mRefinedFlags.test( aPattern );
            }

//--------------------------------------------------------------------------------

            /**
             * tells if an element is active
             *
             * @return bool   true if active
             */
            bool
            is_active( const uint & aPattern ) const
            {
                return mActiveFlags.test( aPattern );
            }

//--------------------------------------------------------------------------------

            /**
             * tells if an element is deactive
             */
            bool
            is_deactive ( const uint & aPattern )
            {
                return ! (
                           mActiveFlags.test( aPattern )
                        || mRefinedFlags.test( aPattern ) );
            }

//--------------------------------------------------------------------------------

            /**
             * tells if an element is a padding element
             *
             * @return bool   true if padding
             */
            bool
            is_padding() const
            {
                return mPaddingFlag;
            }

//--------------------------------------------------------------------------------

            /**
             * tells if an element has children. In a consistent mesh,
             * any element that is refined but not a padding element must
             * have children. Padding elements on the finest level have no children.
             *
             * @return bool   true if children exist
             */
            bool
            has_children() const
            {
                return mChildrenFlag;
            }
//--------------------------------------------------------------------------------

            /**
             * tells if an element has children. Special variant needed for
             * neighbors
             *
             * @param[in] aPattern       regarded activation pattern
             *
             * @return bool   true if children exist on the current pattern
             */
            bool
            has_children( const uint & aPattern ) const
            {
                if ( mPaddingFlag )
                {
                    return mChildrenFlag;
                }
                else
                {
                    return mRefinedFlags.test( aPattern );
                }
            }

//--------------------------------------------------------------------------------

            /**
             * tells if an element is on the refinement queue
             *
             * @return bool   true if flagged for refinement
             */
            bool
            is_queued_for_refinement() const
            {
                return mRefinementQueueFlag;
            }

//--------------------------------------------------------------------------------

            /**
             * flags an element for refinement
             *
             * @return void
             */
            void
            put_on_refinement_queue()
            {
                mRefinementQueueFlag = true;
            }

//--------------------------------------------------------------------------------

            /**
             * unflags an element for refinement
             *
             * @return void
             */
            void
            remove_from_refinement_queue()
            {
                mRefinementQueueFlag = false;
            }

//--------------------------------------------------------------------------------

            /**
             * Returns a pointer to the parent of an element. If the element
             * is on level zero, a null pointer will be returned.
             *
             * @return Element_Base* pointer to parent
             */
            Background_Element_Base*
            get_parent()
            {
                return mParent;
            }
//--------------------------------------------------------------------------------

            /**
             * Returns a pointer to a child of an element. If the element
             * has no children, a null pointer will be returned.
             *
             * @param[in] aIndex                  Index of requested child
             * @return Background_Element_Base *  pointer to selected child
             */
            virtual Background_Element_Base*
            get_child( const uint& aIndex ) = 0;

//--------------------------------------------------------------------------------

            /**
             * Returns an array of size [N] telling the proc local ijk-position
             * of the element on the current level.
             *
             * @return luint pointer to array containing ijk-position
             *               careful: element must not go out of scope.
             */
            virtual const luint *
            get_ijk( ) const = 0;

//--------------------------------------------------------------------------------

            /**
             * This function is called by the background mesh during refinement.
             * The child pointer is put into the member array mChildren.
             *
             * @param[in] aChild   pointer of child to be added
             *
             * @return void
             */
            virtual void
            insert_child( Background_Element_Base* aChild ) = 0 ;

//--------------------------------------------------------------------------------

            /**
             * Tells which child number an element is. This information is needed
             * for the T-Matrix.
             *
             * @return uint    index between 0 and 3 (2D) or 0 and 7 (3D)
             */
            virtual uint
            get_child_index() const = 0;

//--------------------------------------------------------------------------------
            /**
             * Test a bit in the child index bitset
             *
             * @param[in]    aBit    index of bit to test
             *
             * @return bool
             */
            virtual bool
            test_child_index_bit( const uint & aBit ) const = 0;

//--------------------------------------------------------------------------------

            /**
             * This function is called by the background mesh.
             * The pointer of the neighbor is put into the member array mNeighbors.
             *
             * @param[in] aIndex      number of neighbor
             * @param[in] aNeighbor   pointer of neighbor to be added
             *
             * @return void
             */
            virtual void
            insert_neighbor(
                    const uint              & aIndex,
                    Background_Element_Base * aNeighbor ) = 0 ;

//--------------------------------------------------------------------------------

            /**
             * Returns a pointer to a neighbor of an element.
             *
             * @param[ in ] aIndex  index of requested neighbor
             *
             * @return Background_Element_Base* pointer to requested neighbor
             */
            virtual Background_Element_Base*
            get_neighbor( const uint & aIndex ) = 0;

//--------------------------------------------------------------------------------

            /**
             * This function is needed by the background mesh during refinement.
             * The ijk-position of a child is needed to calculate the local and
             * global ID of the child element.
             *
             * param[ out ]  Matrix< DDUMat > of size <number of dimensions>
             *                                *< number of children >
             * @return void
             */
            virtual void
            get_ijk_of_children( Matrix< DDLUMat > & aIJK ) const = 0 ;

//--------------------------------------------------------------------------------
            /**
             * Recursive function that counts all active descendants of an element.
             * If the element is not refined, the function returns one, not zero.
             * This function is needed by the background mesh in order
             * to determine the size of mActiveElements.
             *
             * @param[inout] aCount   Counter to be incremented
             *
             * @return void
             */
            virtual void
            get_number_of_active_descendants( const uint & aPattern, luint & aCount ) const = 0 ;

//--------------------------------------------------------------------------------

            /**
             * Recursive function that counts all descendants of an element plus
             * the element itself.
             *
             * param[inout] aCount   Counter to be incremented
             *
             * @return void
             */
            virtual void
            get_number_of_descendants( luint & aCount ) const = 0 ;

//--------------------------------------------------------------------------------

            /**
             * To be called after the cell aElementList has been allocated
             * to the size given by  get_number_of_descendants().
             * Returns an array that consists all related elements, including
             * the element itself.
             *
             * @param[inout] aElementList  cell to which the pointers are added
             * @param[inout] aElementCount   Counter to be incremented
             *
             * @return void
             */
            virtual void
            collect_descendants(
                    Cell< Background_Element_Base* > & aElementList,
                    luint                            & aElementCount )= 0;

//--------------------------------------------------------------------------------

            /**
             * To be called after the cell aElementList has been allocated
             * to the size given by  get_number_of_active_descendants().
             * Needed by the background mesh to update mActiveElements.
             *
             * @param[in]    aPattern      activation scheme this operation is performed on
             * @param[inout] aElementList  cell to which the pointers are added
             * @param[inout] aCount        Counter to be incremented
             *
             * @return void
             *
             */
            virtual void
            collect_active_descendants(
                    const uint                       & aPattern,
                    Cell< Background_Element_Base* > & aElementList,
                    luint                            & aElementCount ) = 0;

//--------------------------------------------------------------------------------

            /**
             * Function for debugging that prints all neighbors of the element
             * to the screen.
             *
             * @return void
             */
            virtual void
            print_neighbors( const uint & aPattern ) = 0;

//--------------------------------------------------------------------------------

            /**
             * Recursive function that loops up to a specified level and counts
             * active and refined elements on that level.
             *
             * @param[in]     aLevel    level to be considered
             * @param[inout]  aCount    counter for elements
             */
            virtual void
            count_elements_on_level(
                    const uint& aLevel,
                    luint& aElementCount ) = 0;

//--------------------------------------------------------------------------------

            /**
             * Recursive function that loops up to a specified level and collects
             * active and refined elements on that level.
             *
             * @param[in]     aLevel          level to be considered
             * @param[inout]  aElementList    cell to which the pointers are added
             * @param[inout]  aElementCount   counter for elements
             */
            virtual void
            collect_elements_on_level(
                    const uint                       & aLevel,
                    Cell< Background_Element_Base* > & aElementList,
                    luint                            & aElementCount ) = 0;

//-------------------------------------------------------------------------------

            /**
             * called by BackgroundMesh->update_database()
             * depends on selected activation pattern
             */
            virtual void
            collect_neighbors( const uint & aPattern ) = 0;

//-------------------------------------------------------------------------------

            /**
             * Returns a cell with pointers to elements on the same level,
             * if they exist.
             *
             * @param[ in  ] aOrder       degree of neighborship
             * @param[ out ] aNeighbors   cell containing found neighbors
             */
            virtual void
            get_neighbors_from_same_level(
                    const uint                        & aOrder,
                    Cell< Background_Element_Base * > & aNeighbors ) = 0;

//-------------------------------------------------------------------------------

            /**
             * set global index on proc domain
             *
             * param[in]  aIndex    new index of element
             *
             * @return void
             */
            void
            set_domain_index( const uint& aPattern, const luint & aIndex )
            {
                mDomainIndex[ aPattern ] = aIndex;
            }

//-------------------------------------------------------------------------------

            /**
             * get global index on proc domain
             *
             * @return luint global index of element
             */
            luint
            get_domain_index( const uint & aPattern )
            {
               return mDomainIndex[ aPattern ];
            }

//-------------------------------------------------------------------------------

            /**
             * sets memory index to specified value
             *
             * @param[in] aIndex   index to be set
             *
             * @return void
             */
            void
            set_memory_index( const luint& aIndex )
            {
                mMemoryIndex = aIndex;
            }

//-------------------------------------------------------------------------------

            /**
             * returns the memory index of this element
             *
             * @return luint   memory index of this element
             */
            auto
            get_memory_index() const -> decltype( mMemoryIndex )
            {
                return mMemoryIndex;
            }

//-------------------------------------------------------------------------------

            /**
             * coarsen this element
             */
            void
            coarsen( const uint & aPattern )
            {
                MORIS_ERROR(
                        mActiveFlags.test( aPattern ),
                        "Can only coarsen active elements." );

                // deactivate this element
                this->deactivate( aPattern );

                // activate parent
                mParent->set_active_flag( aPattern );
            }

//-------------------------------------------------------------------------------

            /**
             * deactivate this element
             */
            void
            deactivate( const uint & aPattern )
            {
                // deactivate self
                mActiveFlags.reset( aPattern );
                mRefinedFlags.reset( aPattern );
            }

//-------------------------------------------------------------------------------

            /**
             * creates a bitset that describes the pedigree path
             *
             */
            virtual void
            endcode_pedigree_path(
                    luint        & aAncestorID,
                    Matrix< DDUMat >  & aPedigreeList,
                    luint        & aCounter ) = 0;

//-------------------------------------------------------------------------------

            virtual luint
            get_length_of_pedigree_path() = 0;

//-------------------------------------------------------------------------------

            /**
             * set the T-Matrix flag
             */
            void
            set_t_matrix_flag( const uint & aIndex )
            {
                mTMatrixFlags.set( aIndex );
            }

//-------------------------------------------------------------------------------

            /**
             * unset the T-Matrix flag
             */
            void
            unset_t_matrix_flag( const uint & aIndex )
            {
                mTMatrixFlags.reset( aIndex );
            }

//-------------------------------------------------------------------------------

            /**
             * query the T-Matrix flag
             */
            bool
            get_t_matrix_flag( const uint & aIndex ) const
            {
                return mTMatrixFlags.test( aIndex );
            }

//-------------------------------------------------------------------------------

            /**
             * Returns the number of counted flags.
             */
            uint
            count_t_matrix_flags() const
            {
                return mTMatrixFlags.count();
            }

//-------------------------------------------------------------------------------

            /**
             * Returns a uint of the T-Matrix flags. Needed for communication
             */
            uint
            t_matrix_flags_to_uint() const
            {
                return mTMatrixFlags.to_ulong();
            }

//-------------------------------------------------------------------------------

        }; /* Background_Element_Base */
    } /* namespace hmr */
} /* namespace moris */

#endif /* SRC_MESH_CL_HMR_ELEMENT_HPP_ */