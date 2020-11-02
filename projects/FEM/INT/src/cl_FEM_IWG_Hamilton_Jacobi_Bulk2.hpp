/*
 * cl_FEM_IWG_Hamilton_Jacobi_Bulk2.hpp
 *
 *  Created on: Feb 27, 2019
 *      Author: noel
 */

#ifndef SRC_FEM_CL_FEM_IWG_HAMILTON_JACOBI_BULK2_HPP_
#define SRC_FEM_CL_FEM_IWG_HAMILTON_JACOBI_BULK2_HPP_

#include "typedefs.hpp"                     //MRS/COR/src
#include "cl_Cell.hpp"                      //MRS/CON/src

#include "cl_Matrix.hpp"                    //LINALG/src
#include "linalg_typedefs.hpp"              //LINALG/src

#include "cl_FEM_IWG.hpp"                   //FEM/INT/src

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        class IWG_Hamilton_Jacobi_Bulk2 : public IWG
        {

                //------------------------------------------------------------------------------
            public:
                //------------------------------------------------------------------------------
                /*
                 *  constructor
                 */
                IWG_Hamilton_Jacobi_Bulk2();

                //------------------------------------------------------------------------------
                /**
                 * trivial destructor
                 */
                ~IWG_Hamilton_Jacobi_Bulk2(){};

                //------------------------------------------------------------------------------
                /**
                 * compute the residual
                 * @param[ in ] aResidual cell of residual vector to fill
                 */
                void compute_residual( real tWStar );

                //------------------------------------------------------------------------------
                /**
                 * compute the jacobian
                 * @param[ in ] aJacobians cell of cell of jacobian matrices to fill
                 */
                void compute_jacobian( real tWStar );

                //------------------------------------------------------------------------------
                /**
                 * compute the residual and the jacobian
                 * @param[ in ] aJacobians cell of cell of jacobian matrices to fill
                 * @param[ in ] aResidual  cell of residual vectors to fill
                 */
                void compute_jacobian_and_residual( moris::Cell< moris::Cell< Matrix< DDRMat > > > & aJacobians,
                        moris::Cell< Matrix< DDRMat > >                & aResidual );

                //------------------------------------------------------------------------------
        };
        //------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

#endif /* SRC_FEM_CL_FEM_IWG_HAMILTON_JACOBI_BULK_HPP_ */
