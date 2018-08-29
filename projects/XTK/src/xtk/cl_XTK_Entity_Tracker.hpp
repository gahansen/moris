/*
 * cl_XTK_Entity_Tracker.hpp
 *
 *  Created on: Jun 28, 2017
 *      Author: ktdoble
 */

#ifndef SRC_XTK_CL_XTK_ENTITY_TRACKER_HPP_
#define SRC_XTK_CL_XTK_ENTITY_TRACKER_HPP_

// Standard Includes
#include <memory>

#include "linalg/cl_XTK_Matrix.hpp"
// XTKL: Container includes
#include "containers/cl_XTK_Cell.hpp"

// XTKL: Logging and Assertion Includes
#include "assert/fn_xtk_assert.hpp"
#include "ios/cl_Logger.hpp"

// XTKL: Linear Algebra Includes

namespace xtk
{
template<typename Real, typename Integer, typename Real_Matrix, typename Integer_Matrix>
class Entity_Tracker
{
public:

    // Forward declaration
    Integer INTEGER_MAX = std::numeric_limits<Integer>::max();
    /**
     * Constructor which initializes data structure for a specified amount of entities and children
     * @param aEntityRanktoTrack - The entity rank of the parent entity that is being tracked
     * @param aChildEntityRank - The child entity rank which are placed on the parent entity
     * @param aNumEntitiestoTrack - Total number of parent entities which are being tracked
     * @param aNumChildrenAllowed - Number of children allowed on a parent entity
     */
    Entity_Tracker(enum EntityRank aEntityRanktoTrack,
                   enum EntityRank aChildEntityRank,
                   Integer aNumEntitiestoTrack,
                   Integer aNumChildrenAllowed) :
    mReqCounter(0),
    mChildrenAllowed(aNumChildrenAllowed),
    mUseMarker(aNumEntitiestoTrack, 1, 0),
    mEntityTrackerInfo(aNumEntitiestoTrack, aNumChildrenAllowed * 3, INTEGER_MAX),
    mRequestIndexTracker(aNumEntitiestoTrack, 1, INTEGER_MAX)
    {

    }

    ~Entity_Tracker()
    {
    }

    /**
     * Tell the entity to mark an entity as used. Used here means that the parent entity is having a child entity placed on it
     * @param aEntityIndex Entity index to mark as used
     */
    void mark_entity_as_used(Integer aEntityIndex)
    {
        mUseMarker(aEntityIndex, 0) = true;
    }

    /**
     * Set the local index of the child entity being created ( if this function returns false this probably indicates a hanging node has been sent)
     * @param aParentEntityIndex - parent entity
     * @param aSecondaryIndex - unique identifier of a child entity (cantor pairing) for when multiple children are created on one parent entity
     * @param aChildEntityIndex - Child entity index
     */
    bool set_child_entity_lcl_index(Integer aParentEntityIndex, Integer aSecondaryIndex, Integer aChildEntityIndex)
    {
        Integer tLoc = get_child_location(aParentEntityIndex, aSecondaryIndex);
        bool tChildSet = false;
        if(tLoc!= INTEGER_MAX)
        {
            tChildSet = true;
            mEntityTrackerInfo(aParentEntityIndex, tLoc + 2 * mChildrenAllowed) = aChildEntityIndex;
        }
        return tChildSet;
    }

    /**
     * Same as above but for the global id of the child entity. This is the location entiy
     * @param aParentEntityIndex - parent entity
     * @param aSecondaryIndex - unqiue identifier of a child entity (i.e. cantor pairing of node ids on an edge) for when multiple children are created on one parent entity
     * @param aChildEntityIndex - Child entity index
     */
    bool set_child_entity_glb_id(Integer aParentEntityIndex, Integer aSecondaryIndex, Integer aChildEntityId)
    {
        Integer tLoc = get_child_location(aParentEntityIndex, aSecondaryIndex);
        bool tChildSet = false;
        if(tLoc!= INTEGER_MAX)
        {
            tChildSet = true;
            mEntityTrackerInfo(aParentEntityIndex, tLoc + mChildrenAllowed) = aChildEntityId;
        }

        return tChildSet;
    }

    /**
     * Returns whether the entity with index aEntityIndex has been marked as used by mark_entity_as_used function
     * @param aEntityIndex - Parent entity index
     * @return
     */
    bool is_parent_entity_used(Integer aEntityIndex)
    {
        bool tUsed = mUseMarker(aEntityIndex, 0);
        return tUsed;
    }

    /**
     * Same as above but for when more than 1 children are allowed. Sets new request if unused
     * Returns Null ptr if entity has not been used
     *         Cell 0 - NULL if not used, otherwise it has a garbage address
     *         Cell 1 - Index Pointer
     *         Cell 2 - Id    Pointer
     *
     */
    Cell<Integer*> is_parent_entity_used(Integer aEntityIndex, Integer aSecondaryIndex)
    {
        XTK_ASSERT(mChildrenAllowed != 1, "If only one child is allowed then secondary index is not needed. Use other is_parent_entity_used(aEntityIndex) because it is faster");

        // Intialize as null pointers
        Cell<Integer*> tAnswer(3);
        tAnswer(0) = NULL;

        bool used = false;
        for (Integer i = 0; i < mUseMarker(aEntityIndex, 0); i++)
        {
            if (mEntityTrackerInfo(aEntityIndex, i) == aSecondaryIndex)
            {
                tAnswer(0) = &mEntityTrackerInfo(aEntityIndex, i + mChildrenAllowed);
                tAnswer(1) = &mEntityTrackerInfo(aEntityIndex, i + mChildrenAllowed); // Id pointer
                tAnswer(2) = &mEntityTrackerInfo(aEntityIndex, i + 2 * mChildrenAllowed); // Index pointer
                used = true;
            }
        }

        // If used was never marked true the entity has not been used. So mark it as used.
        if (used == false)
        {
            mEntityTrackerInfo(aEntityIndex, mUseMarker(aEntityIndex, 0)) = aSecondaryIndex;
            tAnswer(1) = &mEntityTrackerInfo(aEntityIndex, mUseMarker(aEntityIndex, 0) + mChildrenAllowed);
            tAnswer(2) = &mEntityTrackerInfo(aEntityIndex, mUseMarker(aEntityIndex, 0) + 2 * mChildrenAllowed);
            mUseMarker(aEntityIndex, 0)++;}

        return tAnswer;
    }

    Integer*
    get_index_pointer(Integer aParentEntityIndex)
    {
        return &mEntityTrackerInfo(aParentEntityIndex, 2);
    }

    Integer*
    get_id_pointer(Integer aParentEntityIndex)
    {
        return &mEntityTrackerInfo(aParentEntityIndex, 1);
    }

    Integer get_request_index_from_entity_index(Integer aEntityIndex)
    {
        if (mRequestIndexTracker(aEntityIndex, 0) == INTEGER_MAX)
        {
            mRequestIndexTracker(aEntityIndex, 0) = mReqCounter;
            mUseMarker(aEntityIndex) = true;
            mReqCounter++;
        }

        return mRequestIndexTracker(aEntityIndex);
    }

    Integer get_num_children_allowed()
    {
        return mChildrenAllowed;
    }

    // DEBUGGING FUNCTION
    void print()
    {

        Integer tCol = mEntityTrackerInfo.n_cols();
        for (Integer i = 0; i < mEntityTrackerInfo.n_rows(); i++)
        {
            std::cout << i << " | ";

            for(Integer iC = 0; iC<tCol; iC++)
            {
                   std::cout<< " "<<  mEntityTrackerInfo(i,iC);
            }

            std::cout<<std::endl;
        }
    }
private:
    Integer mReqCounter;
    Integer mChildrenAllowed;     // Number of children allowed
    moris::Mat_New<Integer, Integer_Matrix> mUseMarker;           // Marks how many times an entity has been used
    moris::Mat_New<Integer, Integer_Matrix> mEntityTrackerInfo;   // Requests point to a location in this matrix (Id then indices)
    moris::Mat_New<Integer, Integer_Matrix> mRequestIndexTracker;

    /*
     * Returns the child index for a given parent index (if this function returns the maximum integer value thiis indicates a hanging node)
     */
    Integer get_child_location(Integer aParentIndex, Integer aSecondaryIndex)
    {
        Integer tLoc = INTEGER_MAX;

        XTK_ASSERT(aParentIndex < mEntityTrackerInfo.n_rows(), "Attempted to access entity outside of entity tracker bounds.");
        for (Integer i = 0; i < mChildrenAllowed; i++)
        {
            if (mEntityTrackerInfo(aParentIndex, i) == aSecondaryIndex)
            {
                tLoc = i;
            }
        }

        return tLoc;
    }

};
}



#endif /* SRC_XTK_CL_XTK_ENTITY_TRACKER_HPP_ */
