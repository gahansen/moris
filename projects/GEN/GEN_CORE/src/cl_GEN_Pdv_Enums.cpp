#include "cl_GEN_Pdv_Enums.hpp"

namespace moris
{

    //------------------------------------------------------------------------------------------------------------------

    moris::map< std::string, PDV_Type > get_pdv_type_map()
    {
        moris::map< std::string, PDV_Type > tPdvTypeMap;

        tPdvTypeMap["X_COORDINATE"]     = PDV_Type::X_COORDINATE;
        tPdvTypeMap["Y_COORDINATE"]     = PDV_Type::Y_COORDINATE;
        tPdvTypeMap["Z_COORDINATE"]     = PDV_Type::Z_COORDINATE;
        tPdvTypeMap["DENSITY"]          = PDV_Type::DENSITY;
        tPdvTypeMap["TEMPERATURE"]      = PDV_Type::TEMPERATURE;
        tPdvTypeMap["ELASTIC_MODULUS"]  = PDV_Type::ELASTIC_MODULUS;
        tPdvTypeMap["LS1"]              = PDV_Type::LS1;
        tPdvTypeMap["LS2"]              = PDV_Type::LS2;
        tPdvTypeMap[""]                 = PDV_Type::UNDEFINED;
        return tPdvTypeMap;
    }

    //------------------------------------------------------------------------------------------------------------------

}