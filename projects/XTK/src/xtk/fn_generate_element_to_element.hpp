/*
 * fn_generate_element_to_element.hpp
 *
 *  Created on: Feb 8, 2018
 *      Author: ktdoble
 */

#ifndef XTK_SRC_XTK_FN_GENERATE_ELEMENT_TO_ELEMENT_HPP_
#define XTK_SRC_XTK_FN_GENERATE_ELEMENT_TO_ELEMENT_HPP_

#include "linalg/cl_XTK_Matrix_Base.hpp"
#include "assert/fn_xtk_assert.hpp"

// Unordered Map Include
#include <unordered_map>


namespace xtk
{

/*
 * Generates element to element connectivity from face to element connectivity. A dummy value is needed because
 * not all faces have the same number of elements attached to them and the same goes for element to element connectivity
 * @param[in]  aFaceToElement         - Face to element matrix that can contain dummy values
 * @param[in]  aNumElements           - Number of elements
 * @param[in]  aNumFacesPerElement    - Number of elements
 * @param[in]  aDummyVal              - Indicates a dummy entry
 * @param[out] Element to Element connectivity
 */
template<typename Integer, typename Integer_Matrix>
moris::Mat_New<Integer, Integer_Matrix>
generate_element_to_element(moris::Mat_New<Integer, Integer_Matrix> const & aFaceToElement,
                            Integer const & aNumElements,
                            Integer const & aNumFacesPerElement,
                            Integer const & aDummyValue)
{

    // Initialize Sizes and Variables used in routine
    Integer tElementIndex        = 0;
    Integer tNumFaces            = aFaceToElement.n_rows();
    Integer tMaxNumElementToFace = aFaceToElement.n_cols();

    // Initialize Element to Element with size number of elements x number of faces per element filled with a dummy value.
    moris::Mat_New<Integer, Integer_Matrix> tElementToElement(aNumElements,aNumFacesPerElement,aDummyValue);

    // Initialize a Counter to count how many neighbors a given element has which allows for easy input of information in element to element
    moris::Mat_New<Integer, Integer_Matrix> tElementToElementCount(1,aNumElements,0);


    // Loop over all faces
    for(Integer i = 0; i < tNumFaces; i++)
    {
        // Loop over all elements connected to that face
        for(Integer j = 0; j< tMaxNumElementToFace; j++)
        {
            // Get the element index (for clarity)
            tElementIndex = aFaceToElement(i,j);

            // If the element index is a dummy value break because this means there are no more elements attached to this face
            if(tElementIndex == aDummyValue)
            {
                break;
            }

            // Get the number of neighbors this element has (reference)
            Integer & tCountIndex = tElementToElementCount(0,tElementIndex);

            // Loop over all the  other faces
            for(Integer k = 0; k<tMaxNumElementToFace; k++)
            {
                // Don't add own element ot element to element
                if(k == j)
                {
                    continue;
                }
                // If you see the dummy value break the k for loop
                if(aFaceToElement(i,k) == aDummyValue)
                {
                    break;
                }

                // Set the element neighbor
                tElementToElement(tElementIndex,tCountIndex) = aFaceToElement(i,k);

                // Increment the count on this element
                tCountIndex++;

                // Increment k;
                k++;
            }
        }
    }

    return tElementToElement;
}



/*
 * Generates element to element connectivity from face to element connectivity for non sequential element indices in the face
 * to element connectivity. A dummy value is needed because not all faces have the same number of elements attached to them
 * and the same goes for element to element connectivity. The overhead is in the map construction but once that has been created
 * the algorithm is identical in speed to the sequential version.
 * @param[in]  aFaceToElement         - Face to element matrix that can contain dummy values
 * @param[in]  aElementIndices        - Elements to In Face To Element connectivity
 * @param[in]  aNumElements           - Number of elements
 * @param[in]  aNumFacesPerElement    - Number of elements
 * @param[in]  aDummyVal              - Indicates a dummy entry
 * @param[out] Element to Element connectivity
 */
template<typename Integer, typename Integer_Matrix>
moris::Mat_New<Integer, Integer_Matrix>
generate_element_to_element_nonsequential(moris::Mat_New<Integer, Integer_Matrix> const & aFaceToElement,
                                          std::unordered_map<Integer,Integer> & aElementLocalIndex,
                                          Integer const & aNumElements,
                                          Integer const & aNumFacesPerElement,
                                          Integer const & aDummyValue)
{
    // Initialize Sizes and Variables used in routine
    Integer tElementIndex        = 0;
    Integer tNumFaces            = aFaceToElement.n_rows();
    Integer tMaxNumElementToFace = aFaceToElement.n_cols();

    // Initialize Element to Element with size number of elements x number of faces per element filled with a dummy value.
    moris::Mat_New<Integer, Integer_Matrix> tElementToElement(aNumElements,aNumFacesPerElement,aDummyValue);

    // Initialize a Counter to count how many neighbors a given element has which allows for easy input of information in element to element
    moris::Mat_New<Integer, Integer_Matrix> tElementToElementCount(1,aNumElements,0);


    // Loop over all faces
    for(Integer i = 0; i < tNumFaces; i++)
    {
        // Loop over all elements connected to that face
        for(Integer j = 0; j< tMaxNumElementToFace; j++)
        {

            // If the element index is a dummy value break because this means there are no more elements attached to this face
            if(aFaceToElement(i,j) == aDummyValue)
            {
                break;
            }

            // Get the element index from map
            tElementIndex = aElementLocalIndex[aFaceToElement(i,j)];

            // Get the number of neighbors this element has (reference)
            Integer & tCountIndex = (tElementToElementCount)(0,tElementIndex);

            // Loop over all the  other faces
            for(Integer k = 0; k<tMaxNumElementToFace; k++)
            {
                // Don't add own element to element to element
                if(k == j)
                {
                    continue;
                }
                // If you see the dummy value break the k for loop
                if(aFaceToElement(i,k) == aDummyValue)
                {
                    break;
                }

                // Set the element neighbor
                (tElementToElement)(tElementIndex,tCountIndex) = aElementLocalIndex[aFaceToElement(i,k)];

                // Increment the count on this element
                tCountIndex++;

                // Increment k;
                k++;
            }
        }
    }

    return tElementToElement;
}




}
#endif /* XTK_SRC_XTK_FN_GENERATE_ELEMENT_TO_ELEMENT_HPP_ */
