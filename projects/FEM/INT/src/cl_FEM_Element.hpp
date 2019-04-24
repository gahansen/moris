/*
 * cl_FEM_Element.hpp
 *
 *  Created on: Apr 20, 2019
 *      Author: Schmidt
 */

#ifndef SRC_FEM_CL_FEM_ELEMENT_HPP_
#define SRC_FEM_CL_FEM_ELEMENT_HPP_

#include "assert.h"
#include <cmath>

#include "typedefs.hpp"                     //MRS/COR/src
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_Cell.hpp"
#include "cl_MTK_Cell.hpp"                  //MTK/src
#include "cl_MSI_Equation_Object.hpp"       //FEM/MSI/src
#include "cl_FEM_Enums.hpp"                 //FEM/INT/src
#include "cl_FEM_Node.hpp"                  //FEM/INT/src
#include "cl_FEM_IWG.hpp"                   //FEM/INT/src
#include "cl_FEM_Geometry_Interpolator.hpp" //FEM/INT/src
#include "cl_FEM_Field_Interpolator.hpp"    //FEM/INT/src
#include "cl_FEM_Integrator.hpp"            //FEM/INT/src

#include "cl_FEM_Element_Block.hpp"   //FEM/INT/src
#include "cl_FEM_Cluster.hpp"   //FEM/INT/src

namespace moris
{
    namespace fem
    {
    class Element_Block;
//------------------------------------------------------------------------------
    /**
     * \brief element class that communicates with the mesh interface
     */
    class Element
    {

    protected:

        //! pointer to cell on mesh
        const mtk::Cell * mCell;

        moris::Cell< mtk::Cell const * > mInterpCells;

        //! node indices of this element
        //  @node: MTK interface returns copy of vertices. T
        //         storing the indices in private matrix is faster,
        //         but might need more memory
        moris::Matrix< IndexMat > mNodeIndices;

        uint                      mNumOfIWGs;

        moris::Matrix< DDSMat >   mInterpDofTypeMap;

        Element_Block      * mElementBlock = nullptr;
        Cluster            * mCluster      = nullptr;
//------------------------------------------------------------------------------
    public:
//------------------------------------------------------------------------------

        Element( mtk::Cell    const * aCell,
                 Element_Block      * aElementBlock,
                 Cluster            * aCluster) : mElementBlock( aElementBlock )
        {
            // fill the bulk mtk::Cell pointer //FIXME
            mCell = aCell;

            mCluster = aCluster;

            // select the element nodes from aNodes and fill mNodeObj
            // get vertices from cell
            moris::Cell< mtk::Vertex* > tVertices = aCell->get_vertex_pointers();

            // get number of nodes from cell
            uint tNumOfNodes = tVertices.size();

            // set size of Weak BCs
            mCluster->get_weak_bcs().set_size( tNumOfNodes, 1 );             // FIXME

            // get the number of IWGs
            mNumOfIWGs = mElementBlock->get_num_IWG(); //FIXME

            //FIXME
            mInterpDofTypeMap     = mElementBlock->get_interpolator_dof_type_map();
        };
//------------------------------------------------------------------------------
        /**
         * trivial destructor
         */
        ~Element()
        {
        };

//------------------------------------------------------------------------------

        virtual void compute_jacobian() = 0;

//------------------------------------------------------------------------------

        virtual void compute_residual() = 0;

//------------------------------------------------------------------------------

        virtual void compute_jacobian_and_residual() = 0;

//------------------------------------------------------------------------------
    protected:
//------------------------------------------------------------------------------
        /**
         * compute element volume
         */
        real compute_element_volume( Geometry_Interpolator* aGeometryInterpolator )
        {
            //FIXME: enforced Intergation_Type and Integration_Order
            Integration_Rule tIntegrationRule( mCell->get_geometry_type(),
                                               Integration_Type::GAUSS,
                                               mElementBlock->get_integration_order(),
                                               Integration_Type::GAUSS,
                                               Integration_Order::BAR_1 );

            // create an integrator for the ith IWG
            Integrator tIntegrator( tIntegrationRule );

            //get number of integration points
            uint tNumOfIntegPoints = tIntegrator.get_number_of_points();

            // get integration points
            Matrix< DDRMat > tIntegPoints = tIntegrator.get_points();

            // get integration weights
            Matrix< DDRMat > tIntegWeights = tIntegrator.get_weights();

            // init volume
            real tVolume = 0;

            // loop over integration points
            for( uint iGP = 0; iGP < tNumOfIntegPoints; iGP++ )
            {
                // compute integration point weight x detJ
                real tWStar = aGeometryInterpolator->det_J( tIntegPoints.get_column( iGP ) )
                            * tIntegWeights( iGP );

                // add contribution to jacobian from evaluation point
                //FIXME: include a thickness if 2D
                tVolume = tVolume + tWStar;
            }

            // FIXME: compute the element size + switch 1D, 2D, 3D
            //real he = std::pow( 6*tVolume/M_PI, 1.0/3.0 );
            //real he = std::pow( 4*tVolume/M_PI, 1.0/2.0 );
            //std::cout<<he<<std::endl;

            return tVolume;
        }

//------------------------------------------------------------------------------
    };

//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

#endif /* SRC_FEM_CL_FEM_ELEMENT_HPP_ */
