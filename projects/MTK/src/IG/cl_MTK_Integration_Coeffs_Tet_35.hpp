/*
 * Copyright (c) 2022 University of Colorado
 * Licensed under the MIT license. See LICENSE.txt file in the MORIS root for details.
 *
 *------------------------------------------------------------------------------------
 *
 * cl_MTK_Integration_Coeffs_Tet_35.hpp
 *
 */

#ifndef SRC_MTK_CL_MTK_INTEGRATION_COEFFS_TET_35_HPP_
#define SRC_MTK_CL_MTK_INTEGRATION_COEFFS_TET_35_HPP_

// MRS/COR/src
#include "typedefs.hpp"
// LINALG/src
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
// MTK/src
#include "cl_MTK_Enums.hpp"
#include "cl_MTK_Integration_Coeffs.hpp"

namespace moris
{
    namespace mtk
    {

        //------------------------------------------------------------------------------

        template<>
        uint
        Integration_Coeffs<
                Integration_Type::GAUSS,
                Integration_Order::TET_35 >::get_number_of_dimensions()
        {
            return 3;
        }

        //------------------------------------------------------------------------------

        template<>
        uint
        Integration_Coeffs<
                Integration_Type::GAUSS,
                Integration_Order::TET_35 >::get_number_of_points()
        {
            return 35;
        }

        //------------------------------------------------------------------------------

        template<>
        void
        Integration_Coeffs<
                Integration_Type::GAUSS,
                Integration_Order::TET_35 >::get_points( Matrix< DDRMat >& aIntegrationPoints )
        {
            aIntegrationPoints = {
                { //
                        0.9197896733368800,
                        0.0267367755543735,
                        0.0267367755543735,
                        0.0267367755543735,
                        0.1740356302468940,
                        0.7477598884818090,
                        0.1740356302468940,
                        0.7477598884818090,
                        0.1740356302468940,
                        0.7477598884818090,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.4547545999844830,
                        0.4547545999844830,
                        0.4547545999844830,
                        0.0452454000155172,
                        0.0452454000155172,
                        0.0452454000155172,
                        0.5031186450145980,
                        0.2232010379623150,
                        0.2232010379623150,
                        0.5031186450145980,
                        0.2232010379623150,
                        0.2232010379623150,
                        0.5031186450145980,
                        0.2232010379623150,
                        0.2232010379623150,
                        0.0504792790607720,
                        0.0504792790607720,
                        0.0504792790607720,
                        0.2500000000000000 },
                { //
                        0.0267367755543735,
                        0.9197896733368800,
                        0.0267367755543735,
                        0.0267367755543735,
                        0.7477598884818090,
                        0.1740356302468940,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.1740356302468940,
                        0.7477598884818090,
                        0.1740356302468940,
                        0.7477598884818090,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.4547545999844830,
                        0.0452454000155172,
                        0.0452454000155172,
                        0.4547545999844830,
                        0.4547545999844830,
                        0.0452454000155172,
                        0.2232010379623150,
                        0.5031186450145980,
                        0.2232010379623150,
                        0.2232010379623150,
                        0.5031186450145980,
                        0.2232010379623150,
                        0.0504792790607720,
                        0.0504792790607720,
                        0.0504792790607720,
                        0.5031186450145980,
                        0.2232010379623150,
                        0.2232010379623150,
                        0.2500000000000000 },
                { 0.0267367755543735,
                        0.0267367755543735,
                        0.0267367755543735,
                        0.9197896733368800,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.7477598884818090,
                        0.1740356302468940,
                        0.0391022406356488,
                        0.0391022406356488,
                        0.7477598884818090,
                        0.1740356302468940,
                        0.7477598884818090,
                        0.1740356302468940,
                        0.0452454000155172,
                        0.0452454000155172,
                        0.4547545999844830,
                        0.0452454000155172,
                        0.4547545999844830,
                        0.4547545999844830,
                        0.0504792790607720,
                        0.0504792790607720,
                        0.0504792790607720,
                        0.2232010379623150,
                        0.2232010379623150,
                        0.5031186450145980,
                        0.2232010379623150,
                        0.2232010379623150,
                        0.5031186450145980,
                        0.2232010379623150,
                        0.2232010379623150,
                        0.5031186450145980,
                        0.2500000000000000 }
            };
        }

        //------------------------------------------------------------------------------

        template<>
        void
        Integration_Coeffs<
                Integration_Type::GAUSS,
                Integration_Order::TET_35 >::get_weights( Matrix< DDRMat >& aIntegrationWeights )
        {
            aIntegrationWeights = {
                { //
                        0.0021900463965388,
                        0.0021900463965388,
                        0.0021900463965388,
                        0.0021900463965388,
                        0.0143395670177665,
                        0.0143395670177665,
                        0.0143395670177665,
                        0.0143395670177665,
                        0.0143395670177665,
                        0.0143395670177665,
                        0.0143395670177665,
                        0.0143395670177665,
                        0.0143395670177665,
                        0.0143395670177665,
                        0.0143395670177665,
                        0.0143395670177665,
                        0.0250305395686746,
                        0.0250305395686746,
                        0.0250305395686746,
                        0.0250305395686746,
                        0.0250305395686746,
                        0.0250305395686746,
                        0.0479839333057554,
                        0.0479839333057554,
                        0.0479839333057554,
                        0.0479839333057554,
                        0.0479839333057554,
                        0.0479839333057554,
                        0.0479839333057554,
                        0.0479839333057554,
                        0.0479839333057554,
                        0.0479839333057554,
                        0.0479839333057554,
                        0.0479839333057554,
                        0.0931745731195340 }
            };
        }

        //------------------------------------------------------------------------------
    } /* namespace mtk */
} /* namespace moris */
#endif /* SRC_MTK_CL_MTK_INTEGRATION_COEFFS_TET_35_HPP_ */
