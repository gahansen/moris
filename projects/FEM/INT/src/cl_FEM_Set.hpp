/*
 * cl_FEM_Set.hpp
 *
 *  Created on: Mar 10, 2019
 *      Author: schmidt/noel
 */

#ifndef SRC_FEM_CL_FEM_SET_HPP_
#define SRC_FEM_CL_FEM_SET_HPP_

#include "assert.h"
#include "cl_Communication_Tools.hpp"

//MTK
#include "cl_MTK_Enums.hpp"
#include "cl_MTK_Cell_Cluster.hpp"
#include "cl_MTK_Side_Cluster.hpp"
#include "cl_MTK_Double_Side_Cluster.hpp"
//FEM/INT/src
#include "cl_FEM_Enums.hpp"
#include "cl_FEM_Node_Base.hpp"
#include "cl_FEM_Property.hpp"
#include "cl_FEM_Constitutive_Model.hpp"
#include "cl_FEM_Stabilization_Parameter.hpp"
#include "cl_FEM_Set_User_Info.hpp"
#include "cl_FEM_IQI.hpp"
//FEM/MSI/src
#include "cl_MSI_Equation_Set.hpp"
#include "cl_MSI_Design_Variable_Interface.hpp"
//FEM/VIS/src
#include "cl_VIS_Output_Enums.hpp"

namespace moris
{
namespace mtk
{
   class Cell;
   class Set;
}
namespace MSI
{
   class Model_Solver_Interface;
}
    namespace fem
    {
    class FEM_Model;
    class IWG;
    class IQI;
    class Field_Interpolator;
    class Geometry_Interpolator;
    class Field_Interpolator_Manager;

//------------------------------------------------------------------------------
    /**
     * FEM set
     */
    class Set : public MSI::Equation_Set
    {
    private:

        // FEM model
        fem::FEM_Model * mFemModel = nullptr;

        // pointer to the corresponding mesh set
        moris::mtk::Set * mMeshSet = nullptr;

        // list of mesh cluster pointers
        moris::Cell< mtk::Cluster const* > mMeshClusterList;

        // interpolation mesh geometry type
        mtk::Geometry_Type mIPGeometryType = mtk::Geometry_Type::UNDEFINED;

        // integration mesh geometry type
        mtk::Geometry_Type mIGGeometryType = mtk::Geometry_Type::UNDEFINED;

        // space interpolation order for IP cells
        mtk::Interpolation_Order mIPSpaceInterpolationOrder = mtk::Interpolation_Order::UNDEFINED;

        // space interpolation order for IG cells
        mtk::Interpolation_Order mIGSpaceInterpolationOrder = mtk::Interpolation_Order::UNDEFINED;

        // time interpolation order for IP cells
        mtk::Interpolation_Order mIPTimeInterpolationOrder = mtk::Interpolation_Order::UNDEFINED;

        // space interpolation order for IG cells
        mtk::Interpolation_Order mIGTimeInterpolationOrder = mtk::Interpolation_Order::UNDEFINED;

        // list of fem node pointers for IP nodes
        moris::Cell< Node_Base* > mNodes;

        // field interpolator manager pointers
        Field_Interpolator_Manager * mMasterFIManager = nullptr;
        Field_Interpolator_Manager * mSlaveFIManager  = nullptr;
        Field_Interpolator_Manager * mMasterPreviousFIManager = nullptr;

        // cell of pointers to IWG objects
        moris::Cell< std::shared_ptr< IWG > > mIWGs;
        moris::Cell< std::shared_ptr< IWG > > mRequestedIWGs;

        // cell of pointer to IQI objects
        moris::Cell< std::shared_ptr< IQI > > mIQIs;
        moris::Cell< std::shared_ptr< IQI > > mRequestedIQIs;

        moris::map< std::string, moris_index > mIQINameToIndexMap;

        // enum for element type
        enum fem::Element_Type mElementType;

        // integration points
        Matrix< DDRMat > mIntegPoints;

        // integration weights
        Matrix< DDRMat > mIntegWeights;

        // map for the dof type
        Matrix< DDSMat > mUniqueDofTypeMap;
        Matrix< DDSMat > mUniqueDvTypeMap;

        // map visualization cell id to position in vector
        moris::Cell< moris::Matrix< DDSMat > > mCellAssemblyMap;
        moris::Cell< uint >                    mMtkIgCellOnSet;

        bool mIsResidual = false;

        // bool for time continuity
        bool mTimeContinuity = false;

        // bool for time boundary integral
        bool mTimeBoundary   = false;

        friend class MSI::Equation_Object;
        friend class Cluster;
        friend class Element_Bulk;
        friend class Element_Sideset;
        friend class Element_Double_Sideset;
        friend class Element_Time_Continuity;
        friend class Element;
        friend class Field_Interpolator_Manager;
        friend class Interpolation_Element;

//------------------------------------------------------------------------------
    public:
//------------------------------------------------------------------------------
        /**
         * constructor
         * @param[ in ] aFemModel a FEM model pointer
         * @param[ in ] aMeshSet  a set from the mesh
         * @param[ in ] aSetInfo  user defined info for set
         * @param[ in ] aIPNodes  cell of node pointers
         */
        Set(       fem::FEM_Model            * aFemModel,
                   moris::mtk::Set           * aMeshSet,
             const fem::Set_User_Info        & aSetInfo,
             const moris::Cell< Node_Base* > & aIPNodes );

//------------------------------------------------------------------------------
        /**
         * trivial constructor
         */
        Set()
        {
            mIsEmptySet = true;    //FIXME this flag is a hack. find better solution
        };

//------------------------------------------------------------------------------
        /**
         * trivial destructor
         */
        ~Set();

//------------------------------------------------------------------------------
        /**
         * delete the pointers built on the set
         */
        void delete_pointers();

//------------------------------------------------------------------------------
        /**
         * initialize the set
         * @param[ in ] aIsResidual bool true if this was called for the computation of a residual
         */
        void initialize_set( const bool aIsResidual  );

//------------------------------------------------------------------------------
        /**
         * finalize the fem sets
         * create and set the field interpolators
         * param[ in ] aModelSolverInterface model solver interface pointer
         */
        void finalize( MSI::Model_Solver_Interface * aModelSolverInterface );

//------------------------------------------------------------------------------
        /**
         * free the memory on the set
         */
        void free_memory();

//------------------------------------------------------------------------------
        /**
         * set visualization mesh set
         * @param[ in ] aVisMeshSet a mesh set pointer for visualization
         */
        void set_visualization_set( const uint              aMeshIndex,
                                          moris::mtk::Set * aVisMeshSet,
                                    const bool              aOnlyPrimayCells);

//------------------------------------------------------------------------------
        /**
         * get the element on the set
         * param[ out ] aElementType element type for the set
         */
        enum fem::Element_Type get_element_type() const
        {
            return mElementType;
        }

//------------------------------------------------------------------------------
        /**
         * get the clusters on the set
         * param[ out ] aClusters cell of mesh cluster pointers
         */
        moris::Cell< mtk::Cluster const* > const & get_clusters_on_set() const
        {
            return mMeshClusterList;
        }

//------------------------------------------------------------------------------
        /**
         * get bool for time continuity
         * param[ out ] mTimeContinuity bool true if time continuity
         */
        bool get_time_continuity() const
        {
            return mTimeContinuity;
        }

//------------------------------------------------------------------------------
        /**
         * create a unique dof type list for the solver
         * Cell< MSI::Dof_Type >, no group of dof type
         * one for both master and slave
         */
        void create_unique_dof_and_dv_type_lists();

//------------------------------------------------------------------------------
        /**
         * create a unique group of dof type list for the set
         * Cell< Cell< MSI::Dof_Type > >, list of groups of dof type
         * one for the master, one for the slave
         */
        void create_dof_and_dv_type_lists();

//------------------------------------------------------------------------------
        /**
         * create a map of the dof type for the set
         * one for the master, one for the slave
         */
        void create_dof_and_dv_type_maps();

//------------------------------------------------------------------------------
         /**
          * create field interpolator managers for the set
          * @param[ in ] aModelSolverInterface model solver interface
          * ( only used to set the time levels )
          */
         void create_field_interpolator_managers( MSI::Model_Solver_Interface * aModelSolverInterface );

//------------------------------------------------------------------------------
        /**
         * get IWGs
         * param[ out ] aIWGs cell of IWG pointers
         */
        moris::Cell< std::shared_ptr< IWG > > & get_IWGs()
        {
            return mIWGs;
        }

//------------------------------------------------------------------------------
        /**
         * get number of IWGs
         */
        uint get_number_of_IWGs()
        {
            return mIWGs.size();
        }

//------------------------------------------------------------------------------
        /**
         * get requested IWGs
         * param[ out ] mRequestedIWGs cell of requested IWG pointers
         */
        moris::Cell< std::shared_ptr< IWG > > & get_requested_IWGs()
        {
            return mRequestedIWGs;
        }

//------------------------------------------------------------------------------
        /**
         * get number of requested IWGs
         */
        uint get_number_of_requested_IWGs()
        {
            return mRequestedIWGs.size();
        }

//------------------------------------------------------------------------------
        /**
         * get IQI from type output type for visualization
         * param[ out ] aIQI an IQI pointer
         */
        std::shared_ptr< IQI > get_IQI_for_vis( enum vis::Output_Type aOutputType );

//------------------------------------------------------------------------------
        /**
         * building an IQI name to set local index map
         */
        void create_IQI_map();

//------------------------------------------------------------------------------
        /**
         * create requested IQI list
         */
        void create_requested_IQI_list();

//------------------------------------------------------------------------------
        /**
         * get requested IQIs
         * param[ out ] mRequestedIQIs cell of IQIs pointers
         */
        moris::Cell< std::shared_ptr< IQI > > & get_requested_IQIs()
        {
            return mRequestedIQIs;
        }

//------------------------------------------------------------------------------
        /**
         * get number of requested IQIs
         */
        uint get_number_of_requested_IQIs()
        {
            return mRequestedIQIs.size();
        }

//------------------------------------------------------------------------------
        /**
         * set the field interpolator managers for the IWGs
         */
        void set_IWG_field_interpolator_managers();

//------------------------------------------------------------------------------
        /**
         * set the field interpolator managers for the IQIs
         */
        void set_IQI_field_interpolator_managers();

//------------------------------------------------------------------------------
        /*!
         * set the cluster for the IWG stabilization parameters
         * associated with this set
         */
        void set_IWG_cluster_for_stabilization_parameters( fem::Cluster * aCluster );

//------------------------------------------------------------------------------
        /*!
         * set the cluster for the IQI stabilization parameters
         * associated with this set
         */
        void set_IQI_cluster_for_stabilization_parameters( fem::Cluster * aCluster );

//------------------------------------------------------------------------------
        /**
         * create the dof assembly map for the residual/rows
         */
        void create_residual_dof_assembly_map();

//------------------------------------------------------------------------------
        /**
         * create the dof assembly map for the jacobian/cols
         */
        void create_dof_assembly_map( const bool aIsResidual );

//------------------------------------------------------------------------------
        /**
         * create the dof assembly map for the jacobian/cols
         */
        void create_jacobian_dof_assembly_map();

//------------------------------------------------------------------------------
        /**
         * create the dof assembly map
         * for the off-diagonal requested jacobian/cols
         * for R = R_0 - A_{01} x_{1}
         */
        void create_staggered_jacobian_dof_assembly_map();

//------------------------------------------------------------------------------
        /**
         * create the material pdv assembly map
         */
        void create_mat_pdv_assembly_map();

//------------------------------------------------------------------------------
        /**
         * create the geometry pdv assembly map
         * @param[ in ] aFemCluster a fem cluster pointer
         */
        void create_geo_pdv_assembly_map( std::shared_ptr< fem::Cluster > aFemCluster );

//------------------------------------------------------------------------------
        /**
         * create a list of IWGs requested by the solver
         */
        void create_requested_IWG_list();

//------------------------------------------------------------------------------
        /**
         * create a dof type list for the list of IWGs requested by the solver
         */
        void build_requested_IWG_dof_type_list( const bool aItResidual );

//------------------------------------------------------------------------------
        /**
         * get the IP geometry type
         * @param[ out ] aGeometryType
         */
        mtk::Geometry_Type get_IP_geometry_type()
        {
            return mIPGeometryType;
        }

//------------------------------------------------------------------------------
        /**
         * get the IG geometry type
         * @param[ out ] aGeometryType
         */
        mtk::Geometry_Type get_IG_geometry_type()
        {
            return mIGGeometryType;
        }

//------------------------------------------------------------------------------
        /**
         * FIXME we should not be able to ask this question
         * as the interpolator order is not unique on the set
         * get the IG space interpolation order
         */
        mtk::Interpolation_Order get_IG_space_interpolation_order()
        {
            return mIGSpaceInterpolationOrder;
        }

//------------------------------------------------------------------------------
        /**
         * get the number of integration points
         * @param[ out ] aNumIntegPoints number of integration points
         */
        uint get_number_of_integration_points()
        {
            return mIntegWeights.numel();
        }

//------------------------------------------------------------------------------
        /**
         * get the integration points
         * @param[ out ] aIntegPoints integration points
         */
        const Matrix< DDRMat > & get_integration_points()
        {
            return mIntegPoints;
        }

//------------------------------------------------------------------------------
        /**
         * get the integration weights
         * @param[ out ] aIntegWeights integration weights
         */
        const Matrix< DDRMat > & get_integration_weights()
        {
            return mIntegWeights;
        }

//------------------------------------------------------------------------------
        /**
         * get the field interpolator manager
         * @param[ in ]  aIsMaster an enum for master or slave
         * @param[ out ] mFIManger a field interpolator manager pointer
         */
        Field_Interpolator_Manager * get_field_interpolator_manager( mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER )
        {
            switch ( aIsMaster )
            {
                case ( mtk::Master_Slave::MASTER ) :
                    return mMasterFIManager;

                case ( mtk::Master_Slave::SLAVE ) :
                    return mSlaveFIManager;

                default :
                {
                    MORIS_ERROR( false, "Set::get_field_interpolator_manager - can only be master or slave.");
                    return mMasterFIManager;
                }
            }
        };

//------------------------------------------------------------------------------
        /**
         * get the field interpolator manager for previous time step
         * @param[ in ]  aIsMaster an enum for master or slave
         * @param[ out ] mFIManger a field interpolator manager pointer
         */
        Field_Interpolator_Manager * get_field_interpolator_manager_previous_time( mtk::Master_Slave aIsMaster = mtk::Master_Slave::MASTER )
        {
            switch ( aIsMaster )
            {
                case ( mtk::Master_Slave::MASTER ) :
                    return mMasterPreviousFIManager;

                default :
                {
                    MORIS_ERROR( false, "Set::get_field_interpolator_manager - can only be master.");
                    return mMasterPreviousFIManager;
                }
            }
        };

//------------------------------------------------------------------------------
        /**
         * auto detect full integration scheme
         * @param[ in ]  aGeometryType       a geometry type
         * @param[ in ]  aInterpolationOrder an interpolation order
         * @param[ out ] aIntegrationOrder   an integration order
         */
        fem::Integration_Order get_auto_integration_order
        ( const mtk::Geometry_Type       aGeometryType,
          const mtk::Interpolation_Order aInterpolationOrder );

//------------------------------------------------------------------------------
        /**
         * auto detect space interpolation scheme
         * @param[ in ] aNumVertices  number of vertices for the considered geometry type
         * @param[ in ] aGeometryType geometry type
         * FIXME: works for Lagrange only
         */
        mtk::Interpolation_Order get_auto_interpolation_order( const moris::uint        aNumVertices,
                                                               const mtk::Geometry_Type aGeometryType );

//------------------------------------------------------------------------------
        /**
          * auto detect time interpolation scheme
          * @param[ in ] aNumVertices number of vertices for a line
          */
        fem::Interpolation_Type get_auto_time_interpolation_type( const moris::uint aNumVertices );

//------------------------------------------------------------------------------
        /**
         * set size and reset values for Jacobian
         */
        void initialize_mJacobian();

//------------------------------------------------------------------------------
        /**
         * set size and reset values for residual
         */
        void initialize_mResidual();

//------------------------------------------------------------------------------
        /**
         * set size and reset values for QI
         */
        void initialize_mQI();

        //----------------------------------------------------------------------
        /**
         * set size and reset values for dQIdp
         */
        void initialize_mdQIdpMat();

        //----------------------------------------------------------------------
        /**
         * set size and reset values for dQIdp
         */
        void initialize_mdQIdpGeo( std::shared_ptr< fem::Cluster > aFemCluster );

//------------------------------------------------------------------------------
        /**
         * set size and reset values for dRdp mat
         */
        void initialize_mdRdpMat();

//------------------------------------------------------------------------------
        /**
         * set size and reset values for dRdp geo
         */
        void initialize_mdRdpGeo( std::shared_ptr< fem::Cluster > aFemCluster );

//------------------------------------------------------------------------------
        /*
         * get index from unique dof type map
         *@param[ in ] aDofType a dof type enum
         */
        moris::sint get_index_from_unique_dof_type_map( enum MSI::Dof_Type aDofType )
        {
            return mUniqueDofTypeMap( static_cast< int >( aDofType ), 0 );
        }

//------------------------------------------------------------------------------
        /*
         * get index from unique dv type map
         *@param[ in ] aDofType a dof type enum
         */
        moris::sint get_index_from_unique_dv_type_map( enum PDV_Type aDvType )
        {
            return mUniqueDvTypeMap( static_cast< int >( aDvType ), 0 );
        }

//------------------------------------------------------------------------------
        /*
         * create requested dv assembly map
         */
        void create_requested_dv_assembly_map();

//------------------------------------------------------------------------------
        /*
         * create dof and dv type map unique
         */
        void create_unique_dof_and_dv_type_maps();

//------------------------------------------------------------------------------
        /**
         * compute a quantity of interest
         * @param[ in ] aElementFieldValues
         * @param[ in ] aNodelFieldValues
         * @param[ in ] aGlobalScalar
         * @param[ in ] aOutputType
         * @param[ in ] aFieldType
         */
        void compute_quantity_of_interest( const uint            aMeshIndex,
                                           Matrix< DDRMat >      * aElementFieldValues,
                                           Matrix< DDRMat >      * aNodalFieldValues,
                                           moris::real           * aGlobalScalar,
                                           enum vis::Output_Type   aOutputType,
                                           enum vis::Field_Type    aFieldType );

//------------------------------------------------------------------------------
        /**
         * determine set type from mtk set type
         */
        void determine_set_type();

//------------------------------------------------------------------------------
        /**
         * set dv interface
         * @param[ in ] aDesignVariableInterface a design varaible pointer
         */
        void set_dv_interface( MSI::Design_Variable_Interface * aDesignVariableInterface )
       {
           mDesignVariableInterface = aDesignVariableInterface;

//           moris::Cell< PDV_Type > tTypesUnique;
//           mDesignVariableInterface->get_unique_dv_types_for_set( 0, tTypesUnique );     //FIXME use fem::SEt to MTK::set map
//
//           mUniqueDvTypeMap.set_size( static_cast< int >( PDV_Type::UNDEFINED ), 1, -1 );
//           for( uint Ik = 0; Ik < tTypesUnique.size(); Ik++)
//           {
//               mUniqueDvTypeMap( static_cast< int >( tTypesUnique( Ik ) ) )= Ik;
//           }
       };

    };
//------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

#endif /* SRC_FEM_CL_FEM_SET_HPP_ */
