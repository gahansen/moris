/*
 * cl_FEM_Element_Sideset.hpp
 *
 *  Created on: Mar 07, 2019
 *      Author: noel
 */

#ifndef SRC_FEM_CL_FEM_ELEMENT_SIDESET_HPP_
#define SRC_FEM_CL_FEM_ELEMENT_SIDESET_HPP_

#include "assert.h"
#include "cl_FEM_Element.hpp" //FEM/INT/src

namespace moris
{
    namespace fem
    {
//------------------------------------------------------------------------------
    /**
     * \brief Element_Sideset class
     */
    class Element_Sideset : public Element
    {

//------------------------------------------------------------------------------
    protected:
//------------------------------------------------------------------------------
        //moris::Cell< mtk::Cell > mSidesetCell;

//------------------------------------------------------------------------------
    public:
//------------------------------------------------------------------------------

        /**
         * constructor
         *
         * @param[ in ]     pointer to mesh interface object
         * @param[ in ]     cell of pointers to integrand of weak form of governing eqs.
         * @param[ in ]     cell of pointer to fem nodes
         */
        Element_Sideset( mtk::Cell                 * aCell,
                         moris::Cell< IWG* >       & aIWGs,
                         moris::Cell< Node_Base* > & aNodes );
//------------------------------------------------------------------------------
        /**
         * destructor
         */
        ~Element_Sideset();

//------------------------------------------------------------------------------
        /**
         * compute jacobian over the element
         */
        void compute_jacobian();

//------------------------------------------------------------------------------
        /**
         * compute residual over the element
         */
        void compute_residual();

//------------------------------------------------------------------------------
        /**
         * compute jacobian and residual over the element
         */
        void compute_jacobian_and_residual();

//------------------------------------------------------------------------------
    protected:
//------------------------------------------------------------------------------
        /**
         * create the field interpolators for the element
         */
        Cell< Field_Interpolator* >
        create_element_field_interpolators
        ( Geometry_Interpolator* aGeometryInterpolator );

//------------------------------------------------------------------------------
        /**
         * set the field interpolators coefficients
         */
        void
        set_element_field_interpolators_coefficients
        ( Cell< Field_Interpolator* > & aFieldInterpolators );

//------------------------------------------------------------------------------
        /**
         * get the field interpolators for an IWG
         */
        Cell< Field_Interpolator* >
        get_IWG_field_interpolators( IWG*                        & aIWG,
                                     Cell< Field_Interpolator* > & aFieldInterpolators );
//------------------------------------------------------------------------------
        /**
         * set the initial sizes and values for mJacobianElement and mResidualElement
         */
        void
        initialize_mJacobianElement_and_mResidualElement
        ( Cell< Field_Interpolator* > & aFieldInterpolators );

//------------------------------------------------------------------------------
    };

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */


#endif /* SRC_FEM_CL_FEM_ELEMENT_SIDESET_HPP_ */