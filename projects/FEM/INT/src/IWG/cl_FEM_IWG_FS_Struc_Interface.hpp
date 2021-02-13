/*
 * cl_FEM_IWG_FS_Struc_Interface.hpp
 *
 *  Created on: JUn 05, 2020
 *      Author: noel
 */

#ifndef SRC_FEM_CL_FEM_IWG_FS_STRUC_INTERFACE_HPP_
#define SRC_FEM_CL_FEM_IWG_FS_STRUC_INTERFACE_HPP_

#include <map>

#include "typedefs.hpp"                     //MRS/COR/src
#include "cl_Cell.hpp"                      //MRS/CON/src

#include "cl_Matrix.hpp"                    //LINALG/src
#include "linalg_typedefs.hpp"              //LINALG/src

#include "cl_FEM_Field_Interpolator.hpp"    //FEM/INT/src
#include "cl_FEM_IWG.hpp"                   //FEM/INT/src

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        class IWG_FS_Struc_Interface : public IWG
        {

            public:

                //------------------------------------------------------------------------------
                /*
                 * constructor
                 */
                IWG_FS_Struc_Interface();

                //------------------------------------------------------------------------------
                /**
                 * trivial destructor
                 */
                ~IWG_FS_Struc_Interface(){};

                //------------------------------------------------------------------------------
                /**
                 * compute the residual
                 * @param[ in ] aWStar weight associated to the evaluation point
                 */
                void compute_residual( real aWStar );

                //------------------------------------------------------------------------------
                /**
                 * compute the jacobian
                 * @param[ in ] aWStar weight associated to the evaluation point
                 */
                void compute_jacobian( real aWStar );

                //------------------------------------------------------------------------------
                /**
                 * compute the residual and the jacobian
                 * @param[ in ] aWStar weight associated to the evaluation point
                 */
                void compute_jacobian_and_residual( real aWStar );

                //------------------------------------------------------------------------------
                /**
                 * compute the derivative of the residual wrt design variables
                 * @param[ in ] aWStar weight associated to the evaluation point
                 */
                void compute_dRdp( real aWStar );

                //------------------------------------------------------------------------------
        };
        //------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

#endif /* SRC_FEM_CL_FEM_IWG_FS_STRUC_INTERFACE_HPP_ */