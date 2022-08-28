/*
 * Copyright (c) 2022 University of Colorado
 * Licensed under the MIT license. See LICENSE.txt file in the MORIS root for details.
 *
 *------------------------------------------------------------------------------------
 *
 * fn_determine_cell_topology.hpp
 *
 */

#ifndef SRC_fn_determine_cell_topology
#define SRC_fn_determine_cell_topology

#include "cl_Mesh_Enums.hpp"
#include "cl_MTK_Enums.hpp"
#include "fn_MTK_Interpolation_Enum_Int_Conversion.hpp"

namespace xtk
{
    //------------------------------------------------------------------------------

    enum CellTopology
    determine_cell_topology(
            uint aNumSpatialDims,
            uint aPolynomialOrder,
            enum CellShape aCellShape )
    {
        // --------------------------------------------------
        // 2D
        // --------------------------------------------------

        // get number of spatial dimensions and decide on cell topology
        if ( aNumSpatialDims == 2 )
        {
            if ( aCellShape == CellShape::SIMPLEX )
            {
                switch ( aPolynomialOrder )
                {
                    case 1:
                    {
                        return CellTopology::TRI3;
                        break;
                    }

                    case 2:
                    {
                        return CellTopology::TRI6;
                        break;
                    }

                    case 3:
                    {
                        return CellTopology::TRI10;
                        break;
                    }

                    default:
                    {
                        MORIS_ERROR( false, "determine_cell_topology() - cell topology can only be determined for polynomial orders 1,2, or 3" );
                        return CellTopology::INVALID;
                        break;
                    }
                }
            }
            else if ( aCellShape == CellShape::RECTANGULAR )
            {
                switch ( aPolynomialOrder )
                {
                    case 1:
                    {
                        return CellTopology::QUAD4;
                        break;
                    }

                    case 2:
                    {
                        return CellTopology::QUAD9;
                        break;
                    }

                    case 3:
                    {
                        return CellTopology::QUAD16;
                        break;
                    }

                    default:
                    {
                        MORIS_ERROR( false, "determine_cell_topology() - cell topology can only be determined for polynomial orders 1,2, or 3" );
                        return CellTopology::INVALID;
                        break;
                    }
                }
            }
            else
            {
                MORIS_ERROR( false, "determine_cell_topology() - cell topology can only be determined for rectangular or simplex elements" );
                return CellTopology::INVALID;
            }
        }

        // --------------------------------------------------
        // 3D
        // --------------------------------------------------

        else if ( aNumSpatialDims == 3 )
        {
            if ( aCellShape == CellShape::SIMPLEX )
            {
                switch ( aPolynomialOrder )
                {
                    case 1:
                    {
                        return CellTopology::TET4;
                        break;
                    }

                    case 2:
                    {
                        return CellTopology::TET10;
                        break;
                    }

                    // case 3:
                    // {
                    //     return CellTopology::TET20;
                    //     break;
                    // }

                    default:
                    {
                        MORIS_ERROR( false, "determine_cell_topology() - cell topology can only be determined for polynomial orders 1,2, or 3" );
                        return CellTopology::INVALID;
                        break;
                    }
                }
            }
            else if ( aCellShape == CellShape::RECTANGULAR )
            {
                switch ( aPolynomialOrder )
                {
                    case 1:
                    {
                        return CellTopology::HEX8;
                        break;
                    }

                    case 2:
                    {
                        return CellTopology::HEX27;
                        break;
                    }

                    case 3:
                    {
                        return CellTopology::HEX64;
                        break;
                    }

                    default:
                    {
                        MORIS_ERROR( false, "determine_cell_topology() - cell topology can only be determined for polynomial orders 1,2, or 3" );
                        return CellTopology::INVALID;
                        break;
                    }
                }
            }
            else
            {
                MORIS_ERROR( false, "determine_cell_topology() - cell topology can only be determined for rectangular or simplex elements" );
                return CellTopology::INVALID;
            }
        }

        // --------------------------------------------------

        else
        {
            MORIS_ERROR( false, "determine_cell_topology() - function only works for 2D or 3D" );
            return CellTopology::INVALID;
        }
    }

    //------------------------------------------------------------------------------

    enum CellTopology
    determine_cell_topology(
            uint aNumSpatialDims,
            enum mtk::Interpolation_Order aInterpolationOrder,
            enum CellShape aCellShape )
    {
        // call the above function with the enum replaced by integer
        return determine_cell_topology( aNumSpatialDims, mtk::ip_order_enum_to_uint( aInterpolationOrder ), aCellShape );
    }

    //------------------------------------------------------------------------------

    uint
    determine_num_nodes(
            uint aNumSpatialDims,
            uint aPolynomialOrder,
            enum CellShape aCellShape )
    {
        // --------------------------------------------------
        // 2D
        // --------------------------------------------------

        // get number of spatial dimensions and decide on cell topology
        if ( aNumSpatialDims == 2 )
        {
            if ( aCellShape == CellShape::SIMPLEX )
            {
                switch ( aPolynomialOrder )
                {
                    // TRI3
                    case 1:
                    {
                        return 3;
                        break;
                    }

                    // TRI6
                    case 2:
                    {
                        return 6;
                        break;
                    }

                    // TRI10
                    case 3:
                    {
                        return 10;
                        break;
                    }

                    default:
                    {
                        MORIS_ERROR( false, "determine_num_nodes() - cell topology can only be determined for polynomial orders 1,2, or 3" );
                        return 0;
                        break;
                    }
                }
            }
            else if ( aCellShape == CellShape::RECTANGULAR )
            {
                switch ( aPolynomialOrder )
                {
                    // QUAD4
                    case 1:
                    {
                        return 4;
                        break;
                    }

                    // QUAD9
                    case 2:
                    {
                        return 9;
                        break;
                    }

                    // QUAD16
                    case 3:
                    {
                        return 16;
                        break;
                    }

                    default:
                    {
                        MORIS_ERROR( false, "determine_num_nodes() - number of nodes can only be determined for polynomial orders 1,2, or 3" );
                        return 0;
                        break;
                    }
                }
            }
            else
            {
                MORIS_ERROR( false, "determine_num_nodes() - number of nodes can only be determined for rectangular or simplex elements" );
                return 0;
            }
        }

        // --------------------------------------------------
        // 3D
        // --------------------------------------------------

        else if ( aNumSpatialDims == 3 )
        {
            if ( aCellShape == CellShape::SIMPLEX )
            {
                switch ( aPolynomialOrder )
                {
                    // TET4
                    case 1:
                    {
                        return 4;
                        break;
                    }

                    // TET10
                    case 2:
                    {
                        return 10;
                        break;
                    }

                    // TET20
                    case 3:
                    {
                        return 20;
                        break;
                    }

                    default:
                    {
                        MORIS_ERROR( false, "determine_num_nodes() - number of nodes can only be determined for polynomial orders 1,2, or 3" );
                        return 0;
                        break;
                    }
                }
            }
            else if ( aCellShape == CellShape::RECTANGULAR )
            {
                switch ( aPolynomialOrder )
                {
                    // HEX8
                    case 1:
                    {
                        return 8;
                        break;
                    }

                    // HEX27
                    case 2:
                    {
                        return 27;
                        break;
                    }

                    // HEX64
                    case 3:
                    {
                        return 64;
                        break;
                    }

                    default:
                    {
                        MORIS_ERROR( false, "determine_num_nodes() - number of nodes can only be determined for polynomial orders 1,2, or 3" );
                        return 0;
                        break;
                    }
                }
            }
            else
            {
                MORIS_ERROR( false, "determine_num_nodes() - number of nodes can only be determined for rectangular or simplex elements" );
                return 0;
            }
        }

        // --------------------------------------------------

        else
        {
            MORIS_ERROR( false, "xtk::determine_num_nodes() - function only works for 2D or 3D" );
            return 0;
        }
    }

    //------------------------------------------------------------------------------

    uint
    determine_num_nodes(
            uint aNumSpatialDims,
            enum mtk::Interpolation_Order aInterpolationOrder,
            enum CellShape aCellShape )
    {
        // call the above function with the enum replaced by integer
        return determine_num_nodes( aNumSpatialDims, mtk::ip_order_enum_to_uint( aInterpolationOrder ), aCellShape );
    }

    //------------------------------------------------------------------------------
}

#endif /* fn_determine_cell_topology.hpp */

