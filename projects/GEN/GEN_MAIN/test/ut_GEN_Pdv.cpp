#include "catch.hpp"
#include "cl_Matrix.hpp"

#include "fn_GEN_create_geometries.hpp"
#include "fn_GEN_create_properties.hpp"

#include "fn_PRM_GEN_Parameters.hpp"

#define protected public
#define private   public
#include "cl_GEN_Geometry_Engine.hpp"
#include "cl_GEN_Pdv_Host_Manager.hpp"
#undef protected
#undef private

namespace moris
{
    namespace ge
    {

        //--------------------------------------------------------------------------------------------------------------

        // Dummy values so I don't need to create a model for the sensitivity test
        uint tNumADVs = 36;
        Matrix<DDRMat> tDiqiDpdv(1, tNumADVs, 1.0);
        Matrix<DDRMat> Pdv_Host_Manager::compute_diqi_dadv()
        {
            return tDiqiDpdv * this->compute_dpdv_dadv();
        }

        //--------------------------------------------------------------------------------------------------------------

        TEST_CASE("Interpolation PDV creation test", "[gen], [pdv], [interpolation pdv]")
        {
            if( par_size() == 1)
            {
                // Create PDV_Type host manager
                Pdv_Host_Manager tPdvHostManager;

                tPdvHostManager.mPdvTypeList = {PDV_Type::DENSITY, PDV_Type::TEMPERATURE, PDV_Type::ELASTIC_MODULUS};
                tPdvHostManager.mPdvTypeMap.set_size(10, 1, -1);
                tPdvHostManager.mPdvTypeMap( 3 ) = 0;
                tPdvHostManager.mPdvTypeMap( 4 ) = 1;
                tPdvHostManager.mPdvTypeMap( 5 ) = 2;

                // ----------------- Interpolation PDVs ---------------------- //
                // Node indices per set
                Cell<Matrix<DDSMat>> tIpNodeIndicesPerSet(2);
                tIpNodeIndicesPerSet(0).resize(4, 1);
                tIpNodeIndicesPerSet(1).resize(4, 1);
                tIpNodeIndicesPerSet(0) = {{0, 1, 2, 3}};
                tIpNodeIndicesPerSet(1) = {{2, 3, 4, 5}};

                Cell<Matrix<DDSMat>> tIpNodeIdsPerSet(2);
                tIpNodeIdsPerSet(0).resize(4, 1);
                tIpNodeIdsPerSet(1).resize(4, 1);
                tIpNodeIdsPerSet(0) = {{0, 1, 2, 3}};
                tIpNodeIdsPerSet(1) = {{2, 3, 4, 5}};

                Cell<Matrix<DDSMat>> tIpNodeOwnersPerSet(2);
                tIpNodeOwnersPerSet(0).resize(4, 1);
                tIpNodeOwnersPerSet(1).resize(4, 1);
                tIpNodeOwnersPerSet(0) = {{0, 0, 0, 0}};
                tIpNodeOwnersPerSet(1) = {{0, 0, 0, 0}};

                // PDV_Type types per set
                Cell<Cell<Cell<PDV_Type>>> tIpPdvTypes(2);
                tIpPdvTypes(0).resize(2);
                tIpPdvTypes(1).resize(2);
                tIpPdvTypes(0)(0).resize(1);
                tIpPdvTypes(0)(1).resize(1);
                tIpPdvTypes(1)(0).resize(1);
                tIpPdvTypes(1)(1).resize(1);
                tIpPdvTypes(0)(0)(0) = PDV_Type::DENSITY;
                tIpPdvTypes(0)(1)(0) = PDV_Type::TEMPERATURE;
                tIpPdvTypes(1)(0)(0) = PDV_Type::TEMPERATURE;
                tIpPdvTypes(1)(1)(0) = PDV_Type::ELASTIC_MODULUS;

                // Create PDV_Type hosts
                tPdvHostManager.create_interpolation_pdv_hosts(
                        tIpNodeIndicesPerSet,
                        tIpNodeIdsPerSet,
                        tIpNodeOwnersPerSet,
                        Cell<Matrix<F31RMat>>(6),
                        tIpPdvTypes);

                // Set PDVs
                for (uint tMeshSetIndex = 0; tMeshSetIndex < 2; tMeshSetIndex++)
                {
                    for (uint tNodeIndex = 0; tNodeIndex < 4; tNodeIndex++)
                    {
                        for (uint tPdvIndex = 0; tPdvIndex < 2; tPdvIndex++)
                        {
                            tPdvHostManager.create_interpolation_pdv(
                                    (uint)tIpNodeIndicesPerSet(tMeshSetIndex)(tNodeIndex),
                                    tIpPdvTypes(tMeshSetIndex)(tPdvIndex)(0),
                                    (real)tMeshSetIndex);
                        }
                    }
                }

                tPdvHostManager.create_pdv_ids();

                // Check PDVs
                Cell<Matrix<DDRMat>> tPdvValues;
                for (uint tMeshSetIndex = 0; tMeshSetIndex < 2; tMeshSetIndex++)
                {
                    for (uint tPdvIndex = 0; tPdvIndex < 2; tPdvIndex++)
                    {
                        tPdvValues.clear();
                        tPdvHostManager.get_ip_pdv_value(tIpNodeIndicesPerSet(tMeshSetIndex), tIpPdvTypes(tMeshSetIndex)(tPdvIndex), tPdvValues);

                        for (uint tNodeIndex = 0; tNodeIndex < 4; tNodeIndex++)
                        {
                            CHECK(tPdvValues(0)(tNodeIndex) == tMeshSetIndex +
                                    (tMeshSetIndex == 0) * (tNodeIndex > 1) *
                                    (tIpPdvTypes(tMeshSetIndex)(tPdvIndex)(0) == PDV_Type::TEMPERATURE));
                        }
                    }
                }

                // ------------------- Check global map ----------------------- //
                const Matrix<DDSMat> & tLocalGlobalMap = tPdvHostManager.get_my_local_global_map();

                REQUIRE(tLocalGlobalMap.length() == 14);
                for (int tGlobalPdvIndex = 0; tGlobalPdvIndex < 14; tGlobalPdvIndex++)
                {
                    CHECK(tLocalGlobalMap(tGlobalPdvIndex) == tGlobalPdvIndex);
                }
            }
        }

        //--------------------------------------------------------------------------------------------------------------

        TEST_CASE("PDV sensitivities test", "[gen], [pdv], [sensitivity], [pdv sensitivity]")
        {
//            // Create PDV_Type host manager
//            Pdv_Host_Manager tPdvHostManager;
//            tPdvHostManager.set_num_advs(tNumADVs);
//
//            // Create discrete property
//            ParameterList tParameterList = moris::prm::create_gen_property_parameter_list();;
//            tParameterList.set("type", "discrete");
//            tParameterList.set("property_variable_indices", "all");
//            tParameterList.set("adv_indices", "all");
//            tParameterList.set("pdv_type", "DENSITY");
//
//            // Create property
//            Matrix<DDRMat> tADVs(tNumADVs, 1);
//            std::shared_ptr<Property> tProperty = create_property(tParameterList, tADVs, Cell<std::shared_ptr<moris::ge::Property>>(0));
//
//            // Node indices per set
//            Cell<Matrix<DDSMat>> tIpNodeIndicesPerSet(1);
//            tIpNodeIndicesPerSet(0).resize(tNumADVs, 1);
//            for (uint tNodeIndex = 0; tNodeIndex < tNumADVs; tNodeIndex++)
//            {
//                tIpNodeIndicesPerSet(0)(tNodeIndex) = tNodeIndex;
//            }
//
//            // PDV_Type types per set
//            Cell<Cell<Cell<PDV_Type>>> tIpPdvTypes(1);
//            tIpPdvTypes(0).resize(1);
//            tIpPdvTypes(0)(0).resize(1);
//            tIpPdvTypes(0)(0)(0) = PDV_Type::DENSITY;
//
//            // Create PDV_Type hosts
//            tPdvHostManager.create_interpolation_pdv_hosts(tIpNodeIndicesPerSet, Cell<Matrix<F31RMat>>(tNumADVs), tIpPdvTypes);
//
//            // Set PDVs
//            for (uint tNodeIndex = 0; tNodeIndex < tNumADVs; tNodeIndex++)
//            {
//                tPdvHostManager.create_interpolation_pdv(uint(tIpNodeIndicesPerSet(0)(tNodeIndex)), tIpPdvTypes(0)(0)(0), tProperty);
//            }
//
//            // Check sensitivities
//            CHECK(norm(tPdvHostManager.compute_diqi_dadv() - tDiqiDpdv) <= 1E-12);
        }

        //--------------------------------------------------------------------------------------------------------------

    }
}
