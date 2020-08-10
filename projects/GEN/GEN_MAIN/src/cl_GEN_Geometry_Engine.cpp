// GEN
#include "cl_GEN_Geometry_Engine.hpp"
#include "fn_GEN_create_geometries.hpp"
#include "cl_GEN_Level_Set.hpp"
#include "fn_GEN_create_properties.hpp"
#include "cl_GEN_Interpolation.hpp"
#include "cl_GEN_Child_Node.hpp"
#include "cl_GEN_Intersection_Node.hpp"

// MTK
#include "cl_MTK_Integration_Mesh.hpp"
#include "cl_MTK_Interpolation_Mesh.hpp"

// MRS
#include "fn_Parsing_Tools.hpp"

namespace moris
{
    namespace ge
    {

        //--------------------------------------------------------------------------------------------------------------
        // PUBLIC
        //--------------------------------------------------------------------------------------------------------------

        Geometry_Engine::Geometry_Engine(
                Cell<Cell<ParameterList>> aParameterLists,
                std::shared_ptr<Library_IO> aLibrary):

                // Level-set options
                mIsocontourThreshold(aParameterLists(0)(0).get<real>("isocontour_threshold")),
                mErrorFactor(aParameterLists(0)(0).get<real>("isocontour_error_factor")),
                mLevelSetFile(aParameterLists(0)(0).get<std::string>("level_set_file")),

                // ADVs/IQIs
                mADVs(aParameterLists(0)(0).get<sint>("advs_size")
                        ? Matrix<DDRMat>((uint)aParameterLists(0)(0).get<sint>("advs_size"), 1, aParameterLists(0)(0).get<real>("initial_advs_fill"))
                        : string_to_mat<DDRMat>(aParameterLists(0)(0).get<std::string>("initial_advs"))),
                mLowerBounds(aParameterLists(0)(0).get<sint>("advs_size")
                        ? Matrix<DDRMat>((uint)aParameterLists(0)(0).get<sint>("advs_size"), 1, aParameterLists(0)(0).get<real>("lower_bounds_fill"))
                        : string_to_mat<DDRMat>(aParameterLists(0)(0).get<std::string>("lower_bounds"))),
                mUpperBounds(aParameterLists(0)(0).get<sint>("advs_size")
                        ? Matrix<DDRMat>((uint)aParameterLists(0)(0).get<sint>("advs_size"), 1, aParameterLists(0)(0).get<real>("upper_bounds_fill"))
                        : string_to_mat<DDRMat>(aParameterLists(0)(0).get<std::string>("upper_bounds"))),
                mRequestedIQIs(string_to_cell<std::string>(aParameterLists(0)(0).get<std::string>("IQI_types"))),

                // Library
                mLibrary(aLibrary),

                // Geometries and properties
                mGeometries(create_geometries(aParameterLists(1), mADVs, mLibrary)),
                mGeometryParameterLists(aParameterLists(1)),
                mProperties(create_properties(aParameterLists(2), mADVs, mLibrary)),
                mPropertyParameterLists(aParameterLists(2)),

                // Phase table
                mPhaseTable(string_to_mat<IndexMat>(aParameterLists(0)(0).get<std::string>("phase_table")).numel()
                      ? Phase_Table(string_to_mat<IndexMat>(aParameterLists(0)(0).get<std::string>("phase_table")), aParameterLists(0)(0).get<std::string>("phase_table_structure"))
                      : Phase_Table(mGeometries.size(), aParameterLists(0)(0).get<std::string>("phase_table_structure")))
        {
            // Set requested PDVs
            Cell<std::string> tRequestedPdvNames = string_to_cell<std::string>(aParameterLists(0)(0).get<std::string>("PDV_types"));
            Cell<PDV_Type> tRequestedPdvTypes(tRequestedPdvNames.size());
            map<std::string, PDV_Type> tPdvTypeMap = get_pdv_type_map();
            for (uint tPdvTypeIndex = 0; tPdvTypeIndex < tRequestedPdvTypes.size(); tPdvTypeIndex++)
            {
                tRequestedPdvTypes(tPdvTypeIndex) = tPdvTypeMap[tRequestedPdvNames(tPdvTypeIndex)];
            }
            mPdvHostManager.set_ip_requested_pdv_types(tRequestedPdvTypes);
        }

        //--------------------------------------------------------------------------------------------------------------

        Geometry_Engine::Geometry_Engine(
                Cell< std::shared_ptr<Geometry> >  aGeometry,
                Phase_Table                        aPhaseTable,
                mtk::Interpolation_Mesh*           aMesh,
                Matrix<DDRMat>                     aADVs,
                real                               aIsocontourThreshold,
                real                               aErrorFactor)
                : mIsocontourThreshold(aIsocontourThreshold),
                  mErrorFactor(aErrorFactor),
                  mADVs(aADVs),
                  mActiveGeometryIndex(0),
                  mGeometries(aGeometry),
                  mPhaseTable(aPhaseTable)
        {
            for (uint tGeometryIndex = 0; tGeometryIndex < mGeometries.size(); tGeometryIndex++)
            {
                mShapeSensitivities = (mShapeSensitivities or mGeometries(tGeometryIndex)->depends_on_advs());
            }
            this->compute_level_set_data(aMesh);
        }

        //--------------------------------------------------------------------------------------------------------------

        Geometry_Engine::~Geometry_Engine()
        {
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::set_advs(Matrix<DDRMat> aNewADVs)
        {
            // Set new ADVs
            mADVs = aNewADVs;

            // Reset info related to the mesh
            mPdvHostManager.reset();
            mIntersectionNodes.resize(0);
            mInterfaceParentNodes.resize(0);
            mInterfaceNodeIndices.resize(0, 0);
            mActiveGeometryIndex = 0;
        }

        //--------------------------------------------------------------------------------------------------------------

        Matrix<DDRMat>& Geometry_Engine::get_advs()
        {
            return mADVs;
        }

        //--------------------------------------------------------------------------------------------------------------

        Matrix<DDRMat>& Geometry_Engine::get_lower_bounds()
        {
            return mLowerBounds;
        }

        //--------------------------------------------------------------------------------------------------------------

        Matrix<DDRMat>& Geometry_Engine::get_upper_bounds()
        {
            return mUpperBounds;
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::communicate_requested_IQIs()
        {
            mPdvHostManager.set_requested_IQIs(mRequestedIQIs);
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::communicate_requested_IQIs(Cell<std::string> aIQINames)
        {
            mPdvHostManager.set_requested_IQIs(aIQINames);
        }

        //--------------------------------------------------------------------------------------------------------------

        Matrix<DDRMat> Geometry_Engine::get_dcriteria_dadv()
        {
            return mPdvHostManager.compute_diqi_dadv();
        }

        //--------------------------------------------------------------------------------------------------------------

        MSI::Design_Variable_Interface* Geometry_Engine::get_design_variable_interface()
        {
            return &mPdvHostManager;
        }

        //--------------------------------------------------------------------------------------------------------------

        real Geometry_Engine::get_geometry_field_value(
                uint                   aNodeIndex,
                const Matrix<DDRMat> & aCoordinates,
                uint                   aGeometryIndex)
        {
            return mGeometries(aGeometryIndex)->evaluate_field_value(aNodeIndex, aCoordinates);
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::create_new_child_nodes(
                const Cell<moris_index>&    aNewNodeIndices,
                const Cell<xtk::Topology*>& aParentTopo,
                const Cell<Matrix<DDRMat>>& aParamCoordRelativeToParent,
                const Matrix<DDRMat>&       aGlobalNodeCoord )
        {
            for (uint tNode = 0; tNode < aNewNodeIndices.size(); tNode++ )
            {
                // Create child node
                Matrix<DDUMat> tParentNodeIndices(aParentTopo(tNode)->get_node_indices().length(), 1);
                Cell<Matrix<DDRMat>> tParentNodeCoordinates(tParentNodeIndices.length());
                for (uint tParentNode = 0; tParentNode < tParentNodeIndices.length(); tParentNode++)
                {
                    tParentNodeIndices(tParentNode) = aParentTopo(tNode)->get_node_indices()(tParentNode);
                    tParentNodeCoordinates(tParentNode) = aGlobalNodeCoord.get_row(tParentNodeIndices(tParentNode));
                }
                std::shared_ptr<Child_Node> tChildNode = std::make_shared<Child_Node>(
                        tParentNodeIndices, tParentNodeCoordinates, aParentTopo(tNode)->get_basis_function(), aParamCoordRelativeToParent(tNode));

                // Assign to geometries
                for (uint tGeometryIndex = 0; tGeometryIndex < this->get_num_geometries(); tGeometryIndex++)
                {
                    mGeometries(tGeometryIndex)->add_child_node(aNewNodeIndices(tNode), tChildNode);
                }
            }
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::is_intersected(
                const Matrix<DDRMat>&      aNodeCoords,
                const Matrix<IndexMat>&    aNodetoEntityConn,
                size_t                     aCheckType,
                Cell<GEN_Geometry_Object>& aGeometryObjects)
        {
            //Get information for loops
            size_t tNumEntities = aNodetoEntityConn.n_rows(); // Number of entities provided to the geometry engine

            //Initialize
            size_t tIntersectedCount = 0;    // Intersected element counter
            aGeometryObjects.clear();
            aGeometryObjects.resize(tNumEntities,GEN_Geometry_Object());

            //Loop over elements and determine if the element has an intersection
            for(moris_index i = 0; i < (moris_index)tNumEntities; i++)
            {

                //Populate the intersection flag of this element with a bool
                Matrix< IndexMat > tRow = aNodetoEntityConn.get_row(i);
                bool tIsIntersected = compute_intersection_info(
                        i,
                        tRow,
                        aNodeCoords,
                        aCheckType,
                        aGeometryObjects(tIntersectedCount) );

                if (tIsIntersected)
                {
                    mInterfaceParentNodes.push_back(tRow);
                    tIntersectedCount++;
                }
            }

            // resize
            aGeometryObjects.resize( tIntersectedCount, GEN_Geometry_Object() );
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::set_interface_nodes(const Matrix<IndexMat>& aInterfaceNodeIndices)
        {
            mInterfaceNodeIndices = aInterfaceNodeIndices;
        }

        //--------------------------------------------------------------------------------------------------------------

        size_t Geometry_Engine::get_num_phases()
        {
            return mPhaseTable.get_num_phases();
        }

        //--------------------------------------------------------------------------------------------------------------


        moris_index Geometry_Engine::get_phase_sign_of_given_phase_and_geometry(
                moris_index aPhaseIndex,
                moris_index aGeometryIndex )
        {
            return mPhaseTable.get_phase_sign_of_given_phase_and_geometry( aPhaseIndex,aGeometryIndex );
        }

        //--------------------------------------------------------------------------------------------------------------

        size_t Geometry_Engine::get_phase_index(
                moris_index            aNodeIndex,
                const Matrix<DDRMat> & aCoordinates)
        {
            // 0 for neg 1 for pos
            real tNodePhaseValue = 0;
            Matrix< IndexMat > tPhaseOnOff(1, this->get_num_geometries());

            for (uint tGeometryIndex = 0; tGeometryIndex < mGeometries.size(); tGeometryIndex++)
            {
                tNodePhaseValue = this->get_geometry_field_value(aNodeIndex, aCoordinates, tGeometryIndex);

                // Negative
                if (tNodePhaseValue < mIsocontourThreshold)
                {
                    tPhaseOnOff(0, tGeometryIndex) = 0;
                }
                else
                {
                    tPhaseOnOff(0, tGeometryIndex) = 1;
                }
            }

            return mPhaseTable.get_phase_index(tPhaseOnOff);
        }

        //--------------------------------------------------------------------------------------------------------------

        moris_index Geometry_Engine::get_elem_phase_index(Matrix< IndexMat > const & aElemOnOff)
        {
            return mPhaseTable.get_phase_index(aElemOnOff);
        }

        //--------------------------------------------------------------------------------------------------------------

        size_t Geometry_Engine::get_node_phase_index_wrt_a_geometry(
                uint                   aNodeIndex,
                const Matrix<DDRMat> & aCoordinates,
                uint                   aGeometryIndex)
        {
            real tNodePhaseValue = this->get_geometry_field_value(
                    aNodeIndex,
                    aCoordinates,
                    aGeometryIndex);

            size_t tPhaseOnOff = 1;

            if (tNodePhaseValue < mIsocontourThreshold)
            {
                tPhaseOnOff = 0;
            }

            return tPhaseOnOff;
        }

        //--------------------------------------------------------------------------------------------------------------

        size_t Geometry_Engine::get_num_geometries()
        {
            return mGeometries.size();
        }

        //--------------------------------------------------------------------------------------------------------------

        size_t Geometry_Engine::get_num_bulk_phase()
        {
            return mPhaseTable.get_num_phases();
        }

        //--------------------------------------------------------------------------------------------------------------

        size_t Geometry_Engine::get_active_geometry_index()
        {
            return mActiveGeometryIndex;
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::advance_geometry_index()
        {
            MORIS_ASSERT(mActiveGeometryIndex < mGeometries.size(),
                    "Trying to advance past the number of geometries in the geometry engine");
            mActiveGeometryIndex += 1;
        }

        //--------------------------------------------------------------------------------------------------------------

        uint Geometry_Engine::get_num_refinement_fields()
        {
            return mGeometries.size();
        }

        //--------------------------------------------------------------------------------------------------------------

        bool Geometry_Engine::refinement_needed(
                uint aFieldIndex,
                uint aRefinementIndex)
        {
            return ((sint)aRefinementIndex < mGeometries(aFieldIndex)->get_num_refinements());
        }

        //--------------------------------------------------------------------------------------------------------------

        real Geometry_Engine::get_field_value(
                uint                  aFieldIndex,
                uint                  aNodeIndex,
                const Matrix<DDRMat>& aCoordinates)
        {
            // TODO can return property field too
            return mGeometries(aFieldIndex)->evaluate_field_value(aNodeIndex, aCoordinates);
        }

        //--------------------------------------------------------------------------------------------------------------

        sint Geometry_Engine::get_refinement_function_index(
                uint aFieldIndex,
                uint aRefinementIndex)
        {
            return mGeometries(aFieldIndex)->get_refinement_function_index();
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::create_pdvs(std::shared_ptr<mtk::Mesh_Manager> aMeshManager)
        {
            // Initialize
            mtk::Integration_Mesh* tIntegrationMesh = aMeshManager->get_integration_mesh(0);

            Cell<Cell<Cell<PDV_Type>>> tPdvTypes(tIntegrationMesh->get_num_sets());
            Cell<PDV_Type> tPdvTypeGroup(1);
            Cell<std::string> tMeshSetNames(0);

            Matrix<DDUMat> tMeshSetIndices(0, 0);

            // PDV type map
            map< std::string, PDV_Type > tPdvTypeMap = get_pdv_type_map();

            // Loop over properties to create PDVs
            for (uint tPropertyIndex = 0; tPropertyIndex < mPropertyParameterLists.size(); tPropertyIndex++)
            {
                // PDV type and mesh set names/indices from parameter list
                tPdvTypeGroup(0) = tPdvTypeMap[mPropertyParameterLists(tPropertyIndex).get<std::string>("pdv_type")];

                string_to_cell(mPropertyParameterLists(tPropertyIndex).get<std::string>("pdv_mesh_set_names"), tMeshSetNames);
                string_to_mat(mPropertyParameterLists(tPropertyIndex).get<std::string>("pdv_mesh_set_indices"), tMeshSetIndices);

                // Convert mesh set names to indices
                uint tNumSetIndices = tMeshSetIndices.length();
                tMeshSetIndices.resize(tNumSetIndices + tMeshSetNames.size(), 1);

                for (uint tIndex = tNumSetIndices; tIndex < tMeshSetIndices.length(); tIndex++)
                {
                    tMeshSetIndices(tIndex) = tIntegrationMesh->get_set_index_by_name(tMeshSetNames(tIndex - tNumSetIndices));
                }

                // Assign PDV types
                for (uint tIndex = 0; tIndex < tMeshSetIndices.length(); tIndex++)
                {
                    tPdvTypes(tMeshSetIndices(tIndex)).push_back(tPdvTypeGroup);
                }
            }

            // Create PDV hosts
            this->create_ip_pdv_hosts(
                    aMeshManager->get_interpolation_mesh(0),
                    tIntegrationMesh,
                    tPdvTypes);

            if (mShapeSensitivities)
            {
                this->create_ig_pdv_hosts(tIntegrationMesh);
            }

            // Loop over properties to assign PDVs
            for (uint tPropertyIndex = 0; tPropertyIndex < mPropertyParameterLists.size(); tPropertyIndex++)
            {
                // PDV type and mesh set names/indices from parameter list
                tPdvTypeGroup(0) = tPdvTypeMap[mPropertyParameterLists(tPropertyIndex).get<std::string>("pdv_type")];
                string_to_cell(mPropertyParameterLists(tPropertyIndex).get<std::string>("pdv_mesh_set_names"), tMeshSetNames);
                string_to_mat(mPropertyParameterLists(tPropertyIndex).get<std::string>("pdv_mesh_set_indices"), tMeshSetIndices);

                // Assign PDVs
                if (mPropertyParameterLists(tPropertyIndex).get<std::string>("pdv_mesh_type") == "interpolation")
                {
                    this->assign_property_to_pdv_hosts(mProperties(tPropertyIndex), tPdvTypeGroup(0), tIntegrationMesh, tMeshSetIndices);
                }
                else
                {
                    MORIS_ERROR(false, "Assignment of PDVs is only supported with an interpolation mesh right now.");
                }
            }

            // Get rid of parameter lists
            mPropertyParameterLists.resize(0);
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::compute_level_set_data(mtk::Interpolation_Mesh* aMesh)
        {
            // Register spatial dimension
            mSpatialDim = aMesh->get_spatial_dim();

            // Number of filled ADVs
            uint tNumFilledADVs = mADVs.length();

            // Loop over all geometries and properties to resize ADVs (TODO)
            for (uint tGeometryIndex = 0; tGeometryIndex < mGeometryParameterLists.size(); tGeometryIndex++)
            {
                // Determine if level set will be created
                sint tBSplineMeshIndex = mGeometryParameterLists(tGeometryIndex).get<sint>("bspline_mesh_index");
                if (tBSplineMeshIndex >= 0)
                {
                    // Resize
                    mADVs.resize(mADVs.length() + aMesh->get_num_coeffs(tBSplineMeshIndex), 1);
                }
            }

            // Check all input geometries for ADVs and level set conversion (if not from parameter list) for more resizing
            bool tDependOnADVs = false;
            bool tBSplineConversion = false;
            for (uint tGeometryIndex = 0; tGeometryIndex < mGeometries.size(); tGeometryIndex++)
            {
                tDependOnADVs = (tDependOnADVs or mGeometries(tGeometryIndex)->depends_on_advs());
                tBSplineConversion = (tBSplineConversion or mGeometries(tGeometryIndex)->conversion_to_bsplines());

                // If level set will be created
                if (mGeometries(tGeometryIndex)->conversion_to_bsplines())
                {
                    // Resize
                    mADVs.resize(mADVs.length() + aMesh->get_num_coeffs(mGeometries(tGeometryIndex)->get_bspline_mesh_index()), 1);
                }
            }
            MORIS_ERROR((not tDependOnADVs) or (not tBSplineConversion),
                        "If the geometry engine is given geometries which have already been created, they cannot both depend "
                        "on ADVs and be converted into a level set. Instead, please create the level set beforehand.");

            // Set number of ADVs after level set creation
            mLowerBounds.resize(mADVs.length(), 1);
            mUpperBounds.resize(mADVs.length(), 1);
            mPdvHostManager.set_num_advs(mADVs.length());

            // Build geometries and properties
            if (mGeometryParameterLists.size() > 0)
            {
                mGeometries = create_geometries(mGeometryParameterLists, mADVs, mLibrary);
                mProperties = create_properties(mPropertyParameterLists, mADVs, mLibrary);
                mGeometryParameterLists.resize(0);
                // TODO have properties store all data so parameter lists can be deleted too
            }

            // Determine if conversion to level sets are needed and if shape sensitivities are needed
            for (uint tGeometryIndex = 0; tGeometryIndex < mGeometries.size(); tGeometryIndex++)
            {
                // Shape sensitivities logic in case of no level sets
                mShapeSensitivities = (mShapeSensitivities or mGeometries(tGeometryIndex)->depends_on_advs());

                // Convert to level set if needed
                if (mGeometries(tGeometryIndex)->conversion_to_bsplines())
                {
                    // Always have shape sensitivities if level set
                    mShapeSensitivities = true;

                    // Create level set
                    mGeometries(tGeometryIndex) = std::make_shared<Level_Set>(mADVs,
                                                                              tNumFilledADVs,
                                                                              aMesh,
                                                                              mGeometries(tGeometryIndex));

                    // Assign bounds
                    uint tNumCoeffs = aMesh->get_num_coeffs(mGeometries(tGeometryIndex)->get_bspline_mesh_index());
                    real tBSplineLowerBound = mGeometries(tGeometryIndex)->get_bspline_lower_bound();
                    real tBSplineUpperBound = mGeometries(tGeometryIndex)->get_bspline_upper_bound();
                    for (uint tADVIndex = tNumFilledADVs; tADVIndex < tNumFilledADVs + tNumCoeffs; tADVIndex++)
                    {
                        mLowerBounds(tADVIndex) = tBSplineLowerBound;
                        mUpperBounds(tADVIndex) = tBSplineUpperBound;
                    }

                    // Update filled ADVs
                    tNumFilledADVs = tNumFilledADVs + tNumCoeffs;
                }
            }

            // Save level set data
            if (mLevelSetFile != "")
            {
                // Get all node coordinates
                Cell<Matrix<DDRMat>> tNodeCoordinates(aMesh->get_num_nodes());
                for (uint tNodeIndex = 0; tNodeIndex < aMesh->get_num_nodes(); tNodeIndex++)
                {
                    tNodeCoordinates(tNodeIndex) = aMesh->get_node_coordinate(tNodeIndex);
                }

                // Loop over geometries
                for (uint tGeometryIndex = 0; tGeometryIndex < mGeometries.size(); tGeometryIndex++)
                {
                    // Create file
                    std::ofstream tOutFile(mLevelSetFile + "_" + std::to_string(tGeometryIndex) + ".txt");

                    // Write to file
                    for (uint tNodeIndex = 0; tNodeIndex < aMesh->get_num_nodes(); tNodeIndex++)
                    {
                        // Coordinates
                        for (uint tDimension = 0; tDimension < mSpatialDim; tDimension++)
                        {
                            tOutFile << tNodeCoordinates(tNodeIndex)(tDimension) << ", ";
                        }

                        // Fill unused dimensions with zeros
                        for (uint tDimension = mSpatialDim; tDimension < 3; tDimension++)
                        {
                            tOutFile << 0.0 << ", ";
                        }

                        // Level-set field
                        tOutFile << mGeometries(tGeometryIndex)->evaluate_field_value(tNodeIndex, tNodeCoordinates(tNodeIndex)) << std::endl;
                    }

                    // Close file
                    tOutFile.close();
                }
            }
        }

        //--------------------------------------------------------------------------------------------------------------
        // PRIVATE
        //--------------------------------------------------------------------------------------------------------------

        bool Geometry_Engine::on_interface(real aFieldValue)
        {
            return (std::abs(aFieldValue - mIsocontourThreshold) < mErrorFactor);
        }

        //--------------------------------------------------------------------------------------------------------------

        bool Geometry_Engine::compute_intersection_info(
                moris_index             aEntityIndex,
                const Matrix<IndexMat>& aEntityNodeIndices,
                const Matrix<DDRMat>&   aNodeCoords,
                size_t                  aCheckType,
                GEN_Geometry_Object&    aGeometryObject)
        {
            //Initialize
            bool tIsIntersected = false;

            real tMax = 0;
            real tMin = 0;
            uint tMaxLocRow = 0;
            uint tMaxLocCol = 0;
            uint tMinLocRow = 0;
            uint tMinLocCol = 0;

            size_t tNodeInd  = 0;
            size_t tNumNodes = aEntityNodeIndices.numel();
            Matrix< DDRMat > tEntityNodeVars(tNumNodes, 1);

            // Loop through nodes and get level set values from pre-computed values in aNodeVars or in the level set mesh
            for(size_t n = 0; n < tNumNodes; n++)
            {
                tNodeInd = aEntityNodeIndices(n);

                tEntityNodeVars(n) = this->get_geometry_field_value(
                        tNodeInd,
                        aNodeCoords.get_row(tNodeInd),
                        mActiveGeometryIndex);
            }

            //get the max and minimum level set value for the entity
            tMax = tEntityNodeVars.max(tMaxLocRow,tMaxLocCol);
            tMin = tEntityNodeVars.min(tMinLocRow,tMinLocCol);

            // All nodes are on interface
            if (this->on_interface(tMin) and this->on_interface(tMax))
            {
                aGeometryObject.set_parent_entity_index(aEntityIndex);
                aGeometryObject.mark_all_nodes_as_on_interface();
                tIsIntersected = true;
            }

            // Max node is on interface
            else if (this->on_interface(tMax))
            {
                aGeometryObject.set_parent_entity_index(aEntityIndex);
                aGeometryObject.mark_node_as_on_interface(tMaxLocRow);
                tIsIntersected = true;
            }

            // Min node is on interface
            else if (this->on_interface(tMin))
            {
                aGeometryObject.set_parent_entity_index(aEntityIndex);
                aGeometryObject.mark_node_as_on_interface(tMinLocRow);
                tIsIntersected = true;
            }

            // Interface is somewhere inside of parent
            else if ((tMax > mIsocontourThreshold) and (tMin < mIsocontourThreshold))
            {
                aGeometryObject.set_parent_entity_index(aEntityIndex);
                tIsIntersected = true;

                // Determine if new node
                bool tNewNode = true;
                if (aEntityNodeIndices.n_cols() == 2)
                {
                    for (uint tParentIndex = 0; tParentIndex < mInterfaceParentNodes.size(); tParentIndex++)
                    {
                        tNewNode = tNewNode and (mInterfaceParentNodes(tParentIndex).min() != aEntityNodeIndices.min()
                                or mInterfaceParentNodes(tParentIndex).max() != aEntityNodeIndices.max());
                    }
                }

                if (tNewNode)
                {
                    if(aCheckType == 1)
                    {
                        Matrix< DDRMat > tIntersectLocalCoordinate(1,1);
                        Matrix< DDRMat > tIntersectGlobalCoordinate(1,mSpatialDim);

                        get_intersection_location(aNodeCoords,
                                                  tEntityNodeVars,
                                                  aEntityNodeIndices,
                                                  tIntersectLocalCoordinate,
                                                  tIntersectGlobalCoordinate);

                        aGeometryObject.set_interface_loc_coord(tIntersectLocalCoordinate(0));
                        aGeometryObject.set_interface_glb_coord(tIntersectGlobalCoordinate);
                    }
                }
            }

            return tIsIntersected;
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::get_intersection_location(
                const Matrix<DDRMat>&   aGlobalNodeCoordinates,
                const Matrix<DDRMat>&   aEntityNodeVars,
                const Matrix<IndexMat>& aEntityNodeIndices,
                Matrix<DDRMat>&         aIntersectionLocalCoordinates,
                Matrix<DDRMat>&         aIntersectionGlobalCoordinates)
        {
            // Intersection node
            Cell <Matrix<DDRMat>> tParentNodeCoordinates(2, Matrix<DDRMat>(1, mSpatialDim));

            aGlobalNodeCoordinates.get_row(aEntityNodeIndices(0), tParentNodeCoordinates(0));
            aGlobalNodeCoordinates.get_row(aEntityNodeIndices(1), tParentNodeCoordinates(1));

            Matrix <DDUMat> tParentNodeIndices(2, 1);

            tParentNodeIndices(0) = aEntityNodeIndices(0);
            tParentNodeIndices(1) = aEntityNodeIndices(1);

            mIntersectionNodes.push_back(
                    std::make_shared<Intersection_Node>(
                             tParentNodeIndices,
                             tParentNodeCoordinates,
                             mGeometries(mActiveGeometryIndex),
                             mIsocontourThreshold));

            // Return local and global coordinates
            aIntersectionLocalCoordinates = mIntersectionNodes(mIntersectionNodes.size() - 1)->get_local_coordinates();
            aIntersectionGlobalCoordinates = mIntersectionNodes(mIntersectionNodes.size() - 1)->get_global_coordinates();
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::create_ip_pdv_hosts(
                mtk::Interpolation_Mesh     * aInterpolationMesh,
                mtk::Integration_Mesh       * aIntegrationMesh,
                Cell<Cell<Cell<PDV_Type>>>    aPdvTypes)
        {
            // Get information from integration mesh
            //uint tNumSets = tInterpolationMesh->get_num_sets(); FIXME
            uint tNumSets  = aPdvTypes.size();
            uint tNumNodes = aInterpolationMesh->get_num_nodes();

            Cell<Matrix<DDSMat>> tNodeIndicesPerSet(tNumSets);
            Cell<Matrix<DDRMat>> tNodeCoordinates(tNumNodes);

            // Loop through sets
            for (uint tMeshSetIndex = 0; tMeshSetIndex < tNumSets; tMeshSetIndex++)
            {
                uint tCurrentNode = 0;
                mtk::Set* tSet = aIntegrationMesh->get_set_by_index(tMeshSetIndex);

                // Clusters per set
                for (uint tClusterIndex = 0; tClusterIndex < tSet->get_num_clusters_on_set(); tClusterIndex++)
                {
                    const mtk::Cluster* tCluster = tSet->get_clusters_by_index(tClusterIndex);

                    // Indices on cluster
                    Matrix<IndexMat> tNodeIndicesInCluster = tCluster->get_interpolation_cell().get_vertex_inds();
                    tNodeIndicesPerSet(tMeshSetIndex).resize(tNodeIndicesPerSet(tMeshSetIndex).length() + tNodeIndicesInCluster.length(), 1);

                    for (uint tNodeInCluster = 0; tNodeInCluster < tNodeIndicesInCluster.length(); tNodeInCluster++)
                    {
                        tNodeIndicesPerSet(tMeshSetIndex)(tCurrentNode++) = tNodeIndicesInCluster(tNodeInCluster);
                    }
                }
            }

            // Get node coordinates
            for (uint tNodeIndex = 0; tNodeIndex < tNumNodes; tNodeIndex++)
            {
                tNodeCoordinates(tNodeIndex) = aInterpolationMesh->get_node_coordinate(tNodeIndex);
            }

            // Create hosts
            mPdvHostManager.create_ip_pdv_hosts(tNodeIndicesPerSet, tNodeCoordinates, aPdvTypes);
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::create_ig_pdv_hosts(mtk::Integration_Mesh* aIntegrationMesh)
        {
            // Check interface nodes
            MORIS_ERROR(mInterfaceNodeIndices.length() == mIntersectionNodes.size(),
                        ("Number of interface nodes in XTK (" + std::to_string(mInterfaceNodeIndices.length()) +
                        ") must match number of intersection nodes in the geometry engine (" +
                        std::to_string(mIntersectionNodes.size()) + ").").c_str());

            // Get information from integration mesh
            uint tNumSets = aIntegrationMesh->get_num_sets();

            // Cell of IG PDV_Type types
            Cell<PDV_Type> tCoordinatePdvs(mSpatialDim);

            switch(mSpatialDim)
            {
                case 2:
                {
                    tCoordinatePdvs(0) = PDV_Type::X_COORDINATE;
                    tCoordinatePdvs(1) = PDV_Type::Y_COORDINATE;
                    break;
                }
                case 3:
                {
                    tCoordinatePdvs(0) = PDV_Type::X_COORDINATE;
                    tCoordinatePdvs(1) = PDV_Type::Y_COORDINATE;
                    tCoordinatePdvs(2) = PDV_Type::Z_COORDINATE;
                    break;
                }
                default:
                {
                    MORIS_ERROR( false, "Geometry Engine only works for 2D and 3D models." );
                }
            }

            // Loop through sets
            Cell<Cell<Cell<PDV_Type>>> tPdvTypes(tNumSets);
            for (uint tMeshSetIndex = 0; tMeshSetIndex < tNumSets; tMeshSetIndex++)
            {
                // PDV_Type types per set
                tPdvTypes(tMeshSetIndex).resize(1);
                tPdvTypes(tMeshSetIndex)(0) = tCoordinatePdvs;
            }

            // Create hosts
            if (mInterfaceNodeIndices.length() > 0)
            {
                Cell<std::shared_ptr<Intersection_Node>> tIntersectionNodes(mInterfaceNodeIndices(mInterfaceNodeIndices.length() - 1) + 1);

                for (uint tInterfaceNode = 0; tInterfaceNode < mInterfaceNodeIndices.length(); tInterfaceNode++)
                {
                    tIntersectionNodes(mInterfaceNodeIndices(tInterfaceNode)) = mIntersectionNodes(tInterfaceNode);
                }

                mPdvHostManager.create_ig_pdv_hosts(tPdvTypes, tIntersectionNodes);
                mPdvHostManager.set_ig_requested_pdv_types(tCoordinatePdvs);
            }
        }

        //--------------------------------------------------------------------------------------------------------------

        void Geometry_Engine::assign_property_to_pdv_hosts(
                std::shared_ptr<Property> aPropertyPointer,
                PDV_Type                  aPdvType,
                mtk::Integration_Mesh*    aIntegrationMesh,
                Matrix<DDUMat>            aSetIndices)
        {
            for (uint tSet = 0; tSet < aSetIndices.length(); tSet++)
            {
                // get the mesh set from index
                mtk::Set* tSetPointer = aIntegrationMesh->get_set_by_index( aSetIndices(tSet) );

                // get the list of cluster on mesh set
                Cell< mtk::Cluster const * > tClusterPointers = tSetPointer->get_clusters_on_set();

                // get number of clusters on mesh set
                uint tNumClusters = tClusterPointers.size();

                // loop over the clusters on mesh set
                for(uint iClust=0; iClust<tNumClusters; iClust++)
                {
                    // get the IP cell from cluster
                    mtk::Cell const & tIPCell = tClusterPointers(iClust)->get_interpolation_cell();

                    // get the vertices from IP cell
                    Cell< mtk::Vertex * > tVertices = tIPCell.get_vertex_pointers();

                    // get the number of vertices on IP cell
                    uint tNumVerts = tVertices.size();

                    // loop over vertices on IP cell
                    for(uint iVert = 0; iVert < tNumVerts; iVert++)
                    {
                        // get the vertex index
                        moris_index tVertIndex = tVertices(iVert)->get_index();

                        // ask pdv host manager to assign to vertex a pdv type and a property
                        mPdvHostManager.create_ip_pdv( uint(tVertIndex), aPdvType, aPropertyPointer );
                    }
                }
            }
        }

        //--------------------------------------------------------------------------------------------------------------

    }
}
