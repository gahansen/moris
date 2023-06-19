/*
* Copyright (c) 2022 University of Colorado
* Licensed under the MIT license. See LICENSE.txt file in the MORIS root for details.
*
*------------------------------------------------------------------------------------
*
* cl_Mesh_Enums.cpp
*
*/

#include "cl_Mesh_Enums.hpp"

std::string get_enum_str( enum CellTopology aCellTopology )
{
    switch ( aCellTopology )
    {
        case CellTopology::TRI3:
            return "TRI3";
        case CellTopology::QUAD4:
            return "QUAD4";
        case CellTopology::QUAD8:
            return "QUAD8";
        case CellTopology::TET4:
            return "TET4";
        case CellTopology::TET10:
            return "TET10";
        case CellTopology::HEX8:
            return "HEX8";
        case CellTopology::HEX20:
            return "HEX20";
        case CellTopology::HEX27:
            return "HEX27";
        case CellTopology::HEX64:
            return "HEX64";
        case CellTopology::PRISM6:
            return "PRISM6";
        case CellTopology::INVALID:
            return "INVALID";
        case CellTopology::END_ENUM:
            return "END_ENUM";
        default:
            return "invalid cell topology enum provided";
    }
}

//------------------------------------------------------------------------------

uint get_order_from_topology( CellTopology aCellTopology )
{
    switch ( aCellTopology )
    {
        case CellTopology::TRI3:
        case CellTopology::QUAD4:
        case CellTopology::TET4:
        case CellTopology::PRISM6:
        case CellTopology::HEX8:
            return 1;
        case CellTopology::QUAD8:
        case CellTopology::TET10:
        case CellTopology::HEX20:
        case CellTopology::HEX27:
            return 2;
        case CellTopology::HEX64:
            return 3;
        case CellTopology::INVALID:
        case CellTopology::END_ENUM:
        default:
            return 0;
    }
}

//------------------------------------------------------------------------------

namespace moris
{
    std::string get_enum_str( EntityRank aCellTopology )
    {
        switch ( aCellTopology )
        {
            case EntityRank::NODE:
                return "NODE";
            case EntityRank::EDGE:
                return "EDGE";
            case EntityRank::FACE:
                return "FACE";
            case EntityRank::ELEMENT:
                return "ELEMENT";
            case EntityRank::BSPLINE:
                return "BSPLINE";
            case EntityRank::BSPLINE_2:
                return "BSPLINE_2";
            case EntityRank::BSPLINE_3:
                return "BSPLINE_3";
            case EntityRank::INVALID:
                return "INVALID";
            default:
                return "Unrecognized Enum provided to get_enum_str";
        }
    }

    //------------------------------------------------------------------------------

    EntityRank get_entity_rank_from_str( const std::string& aString )
    {
        if ( aString.compare( "NODE" ) == 0 || aString.compare( "node" ) == 0 ) { return EntityRank::NODE; }
        else if ( aString.compare( "EDGE" ) == 0 || aString.compare( "edge" ) == 0 )
        {
            return EntityRank::EDGE;
        }
        else if ( aString.compare( "FACE" ) == 0 || aString.compare( "face" ) == 0 )
        {
            return EntityRank::FACE;
        }
        else if ( aString.compare( "ELEMENT" ) == 0 || aString.compare( "element" ) == 0 )
        {
            return EntityRank::ELEMENT;
        }
        else if ( aString.compare( "BSPLINE" ) == 0 || aString.compare( "bspline" ) == 0 )
        {
            return EntityRank::BSPLINE;
        }
        else if ( aString.compare( "BSPLINE_2" ) == 0 || aString.compare( "bspline_2" ) == 0 )
        {
            return EntityRank::BSPLINE_2;
        }
        else if ( aString.compare( "BSPLINE_3" ) == 0 || aString.compare( "bspline_3" ) == 0 )
        {
            return EntityRank::BSPLINE_3;
        }
        else if ( aString.compare( "INVALID" ) == 0 || aString.compare( "invalid" ) == 0 )
        {
            return EntityRank::INVALID;
        }
        else
        {
            MORIS_ERROR( false, "Invliad entity rank string" );
            return EntityRank::INVALID;
        };
    }

    //------------------------------------------------------------------------------

    EntityRank get_entity_rank_from_index( moris_index aEntityRankIndex )
    {
        if ( aEntityRankIndex == 0 ) { return EntityRank::NODE; }
        else if ( aEntityRankIndex == 1 )
        {
            return EntityRank::EDGE;
        }
        else if ( aEntityRankIndex == 2 )
        {
            return EntityRank::FACE;
        }
        else if ( aEntityRankIndex == 3 )
        {
            return EntityRank::ELEMENT;
        }
        else
        {
            MORIS_ERROR( false, "Invalid index entity rank string" );
            return EntityRank::INVALID;
        };
    }
}
