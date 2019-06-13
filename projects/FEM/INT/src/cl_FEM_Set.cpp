/*
 * cl_FEM_Set.cpp
 *
 *  Created on: Apr 11, 2019
 *      Author: schmidt
 */
#include <iostream>

#include "cl_MSI_Model_Solver_Interface.hpp" //FEM/MSI/src
#include "cl_FEM_Set.hpp"                    //FEM/INT/src
#include "cl_FEM_Element_Factory.hpp"        //FEM/INT/src
#include "cl_FEM_Integrator.hpp"             //FEM/INT/src

namespace moris
{
    namespace fem
    {
//------------------------------------------------------------------------------

    Set::Set( moris::Cell< mtk::Cell_Cluster const * > & aMeshClusterList,
              enum fem::Element_Type                     aElementType,
              moris::Cell< IWG* >                      & aIWGs,
              moris::Cell< Node_Base* >                & aIPNodes) : mMeshCellClusterList( aMeshClusterList ),
                                                                     mNodes(aIPNodes),
                                                                     mIWGs( aIWGs ),
                                                                     mElementType( aElementType )
    {
        // create a unique dof type list
        this->create_unique_dof_type_lists();

        // create a dof type list for field interpolators
        this->create_dof_type_lists();

        // create a unique property type list for field interpolators
        this->create_unique_property_type_list();

        // init the equation object list
        mEquationObjList.resize( mMeshCellClusterList.size(), nullptr);

        // create a factory to create fem cluster
        fem::Element_Factory tClusterFactory;

        for( luint k = 0; k < mMeshCellClusterList.size(); ++k )
        {
            // create a cluster
            mEquationObjList( k ) = tClusterFactory.create_cluster( mElementType,
                                                                    mMeshCellClusterList( k ),
                                                                    mNodes,
                                                                    this );
        }
    }

    Set::Set( moris::Cell< mtk::Side_Cluster const * > & aMeshClusterList,
              enum fem::Element_Type                     aElementType,
              moris::Cell< IWG* >                      & aIWGs,
              moris::Cell< Node_Base* >                & aIPNodes) : mMeshSideClusterList( aMeshClusterList ),
                                                                     mNodes(aIPNodes),
                                                                     mIWGs( aIWGs ),
                                                                     mElementType( aElementType )
    {
        // create a unique dof type list
        this->create_unique_dof_type_lists();

        // create a dof type list for field interpolators
        this->create_dof_type_lists();

        // create a unique property type list for field interpolators
        this->create_unique_property_type_list();

        // init the equation object list
        mEquationObjList.resize( mMeshSideClusterList.size(), nullptr);

        // create a factory to create fem cluster
        fem::Element_Factory tClusterFactory;

        for( luint k = 0; k < mMeshSideClusterList.size(); ++k )
        {
            // create a side cluster
            mEquationObjList( k ) = tClusterFactory.create_cluster( mElementType,
                                                                    mMeshSideClusterList( k ),
                                                                    mNodes,
                                                                    this );
        }
    }


    Set::Set( moris::Cell< mtk::Double_Side_Cluster > const & aMeshClusterList,
              enum fem::Element_Type                          aElementType,
              moris::Cell< IWG* >                           & aIWGs,
              moris::Cell< Node_Base* >                     & aIPNodes) : mMeshDoubleSideClusterList( aMeshClusterList ),
                                                                          mNodes(aIPNodes),
                                                                          mIWGs( aIWGs ),
                                                                          mElementType( aElementType )
        {
            // create a unique dof type list
            this->create_unique_dof_type_lists();

            // create a dof type list for field interpolators
            this->create_dof_type_lists();

            // create a unique property type list for field interpolators
            this->create_unique_property_type_list();

            // init the equation object list
            mEquationObjList.resize( mMeshDoubleSideClusterList.size(), nullptr);

            // create a factory to create fem cluster
            fem::Element_Factory tClusterFactory;

            for( luint k = 0; k < mMeshDoubleSideClusterList.size(); ++k )
            {
                // create a side cluster
                mEquationObjList( k ) = tClusterFactory.create_cluster( mElementType,
                                                                        mMeshDoubleSideClusterList( k ),
                                                                        mNodes,
                                                                        this );
            }
        }

//------------------------------------------------------------------------------

    Set::~Set()
    {
        this->delete_pointers();

        for( auto tEquationObj : mEquationObjList )
        {
            delete tEquationObj;
        }
    }

//------------------------------------------------------------------------------

    void Set::delete_pointers()
    {
        // delete the interpolation geometry interpolator pointer
        if ( mIPGeometryInterpolator != nullptr )
        {
            delete mIPGeometryInterpolator;
        }

        if ( mLeftIPGeometryInterpolator != nullptr )
        {
            delete mLeftIPGeometryInterpolator;
        }
        if ( mRightIPGeometryInterpolator != nullptr )
        {
            delete mRightIPGeometryInterpolator;
        }

        // delete the integration geometry interpolator pointer
        if ( mIGGeometryInterpolator != nullptr )
        {
            delete mIGGeometryInterpolator;
        }

        if ( mLeftIGGeometryInterpolator != nullptr )
        {
            delete mLeftIGGeometryInterpolator;
        }
        if ( mRightIGGeometryInterpolator != nullptr )
        {
            delete mRightIGGeometryInterpolator;
        }

        // delete the list of field interpolator pointers
        mFieldInterpolators.clear();
        mLeftFieldInterpolators.clear();
        mRightFieldInterpolators.clear();

//        mEquationObjList.clear();        // FIXME memory leak
    }

//------------------------------------------------------------------------------

    void Set::finalize( MSI::Model_Solver_Interface * aModelSolverInterface )
    {
        this->delete_pointers();

        // if block-set
        if( mMeshCellClusterList.size() > 0 )
        {
                // set the integration geometry type
                mIPGeometryType = mMeshCellClusterList( 0 )->get_interpolation_cell().get_geometry_type();

                // set the integration geometry type
                mIGGeometryType = mMeshCellClusterList( 0 )->get_primary_cells_in_cluster()( 0 )->get_geometry_type();

                // space interpolation order for IP cells fixme
                mIPSpaceInterpolationOrder = this->get_auto_interpolation_order( mMeshCellClusterList( 0 )->get_interpolation_cell().get_number_of_vertices(),
                                                                                 mIPGeometryType );
                // space interpolation order for IG cells fixme
                mIGSpaceInterpolationOrder = this->get_auto_interpolation_order( mMeshCellClusterList( 0 )->get_primary_cells_in_cluster()( 0 )->get_number_of_vertices(),
                                                                                 mIGGeometryType );

                // time interpolation order for IP cells fixme not linear
                mIPTimeInterpolationOrder = mtk::Interpolation_Order::LINEAR;

                // time interpolation order for IG cells fixme not linear
                mIGTimeInterpolationOrder = mtk::Interpolation_Order::LINEAR;

                // geometry interpolation rule for interpolation cells
                Interpolation_Rule tIPGeometryInterpolationRule( mIPGeometryType,
                                                                 Interpolation_Type::LAGRANGE,
                                                                 mIPSpaceInterpolationOrder,
                                                                 Interpolation_Type::LAGRANGE,
                                                                 mIPTimeInterpolationOrder );

                // geometry interpolation rule for integration cells
                Interpolation_Rule tIGGeometryInterpolationRule( mIGGeometryType,
                                                                 Interpolation_Type::LAGRANGE,
                                                                 mIGSpaceInterpolationOrder,
                                                                 Interpolation_Type::LAGRANGE,
                                                                 mIGTimeInterpolationOrder );

                // create an interpolation geometry intepolator
                mIPGeometryInterpolator = new Geometry_Interpolator( tIPGeometryInterpolationRule, false );

                // create an integration geometry intepolator
                mIGGeometryInterpolator = new Geometry_Interpolator( tIGGeometryInterpolationRule, false );

                // create the element field interpolators
                this->create_field_interpolators( aModelSolverInterface );

                // create the element dof assembly map
                this->create_dof_assembly_map();

                // create an interpolation rule for the cell
                Integration_Rule tIntegrationRule = Integration_Rule( mIGGeometryType,
                                                                      Integration_Type::GAUSS,
                                                                      this->get_auto_integration_order( mIGGeometryType ),
                                                                      Integration_Type::GAUSS,
                                                                      Integration_Order::BAR_1 ); // fixme time integration

                // create an integrator
                Integrator tIntegrator( tIntegrationRule );

                //get number of integration points
                mNumOfIntegPoints = tIntegrator.get_number_of_points();

                // get integration points
                mIntegPoints = tIntegrator.get_points();

                // get integration weights
                mIntegWeights = tIntegrator.get_weights();
            }

            // if side-set
            else if( mMeshSideClusterList.size() > 0 )
            {
                // set the integration geometry type
                mIPGeometryType = mMeshSideClusterList( 0 )->get_interpolation_cell().get_geometry_type();

                // set the integration geometry type
                mIGGeometryType = get_auto_side_geometry_type( mMeshSideClusterList( 0 )->get_cells_in_side_cluster()( 0 )->get_geometry_type() );

                // interpolation order for IP cells fixme
                mIPSpaceInterpolationOrder = this->get_auto_interpolation_order( mMeshSideClusterList( 0 )->get_interpolation_cell().get_number_of_vertices(),
                                                                                 mIPGeometryType );

                // interpolation order for IG cells fixme
                mIGSpaceInterpolationOrder = this->get_auto_interpolation_order( mMeshSideClusterList( 0 )->get_cells_in_side_cluster()( 0 )->get_number_of_vertices(),
                                                                                 mMeshSideClusterList( 0 )->get_cells_in_side_cluster()( 0 )->get_geometry_type() );

                // time interpolation order for IP cells fixme not linear
                mIPTimeInterpolationOrder = mtk::Interpolation_Order::LINEAR;

                // time interpolation order for IG cells fixme not linear
                mIGTimeInterpolationOrder = mtk::Interpolation_Order::LINEAR;

                // geometry interpolation rule for interpolation cells
                Interpolation_Rule tIPGeometryInterpolationRule( mIPGeometryType,
                                                                 Interpolation_Type::LAGRANGE,
                                                                 mIPSpaceInterpolationOrder,
                                                                 Interpolation_Type::LAGRANGE,
                                                                 mIPTimeInterpolationOrder );

                // geometry interpolation rule for integration cells
                Interpolation_Rule tIGGeometryInterpolationRule( mIGGeometryType,
                                                                 Interpolation_Type::LAGRANGE,
                                                                 mIGSpaceInterpolationOrder,
                                                                 Interpolation_Type::LAGRANGE,
                                                                 mIGTimeInterpolationOrder );

                // create an interpolation geometry intepolator
                mIPGeometryInterpolator = new Geometry_Interpolator( tIPGeometryInterpolationRule, true );

                // create an integration geometry intepolator
                mIGGeometryInterpolator = new Geometry_Interpolator( tIGGeometryInterpolationRule, true );

                // create the element field interpolators
                this->create_field_interpolators( aModelSolverInterface );

                // create the element dof assembly map
                this->create_dof_assembly_map();

                // create an interpolation rule for the side
                Integration_Rule tIntegrationRule = Integration_Rule( mIGGeometryType,
                                                                      Integration_Type::GAUSS,
                                                                      this->get_auto_integration_order( mIGGeometryType ),
                                                                      Integration_Type::GAUSS,
                                                                      Integration_Order::BAR_1 ); // fixme time order

                // create an integrator
                Integrator tIntegrator( tIntegrationRule );

                //get number of integration points
                mNumOfIntegPoints = tIntegrator.get_number_of_points();

                // get integration points
                mIntegPoints = tIntegrator.get_points();

                // get integration weights
                mIntegWeights = tIntegrator.get_weights();
            }

            // if double side-set
            else if( mMeshDoubleSideClusterList.size() > 0 )
            {
                // set the integration geometry type
                mIPGeometryType = mMeshDoubleSideClusterList( 0 ).get_left_interpolation_cell().get_geometry_type();

                // set the integration geometry type
                mIGGeometryType = get_auto_side_geometry_type( mMeshDoubleSideClusterList( 0 ).get_left_integration_cells()( 0 )->get_geometry_type() );

                // interpolation order for IP cells fixme
                mIPSpaceInterpolationOrder = this->get_auto_interpolation_order( mMeshDoubleSideClusterList( 0 ).get_left_interpolation_cell().get_number_of_vertices(),
                                                                                 mIPGeometryType );

                // interpolation order for IG cells fixme
                mIGSpaceInterpolationOrder = this->get_auto_interpolation_order( mMeshDoubleSideClusterList( 0 ).get_left_integration_cells()( 0 )->get_number_of_vertices(),
                                                                                 mMeshDoubleSideClusterList( 0 ).get_left_integration_cells()( 0 )->get_geometry_type() );

                // time interpolation order for IP cells fixme not linear
                mIPTimeInterpolationOrder = mtk::Interpolation_Order::LINEAR;

                // time interpolation order for IG cells fixme not linear
                mIGTimeInterpolationOrder = mtk::Interpolation_Order::LINEAR;

                // geometry interpolation rule for interpolation cells
                Interpolation_Rule tIPGeometryInterpolationRule( mIPGeometryType,
                                                                 Interpolation_Type::LAGRANGE,
                                                                 mIPSpaceInterpolationOrder,
                                                                 Interpolation_Type::LAGRANGE,
                                                                 mIPTimeInterpolationOrder );

                // geometry interpolation rule for integration cells
                Interpolation_Rule tIGGeometryInterpolationRule( mIGGeometryType,
                                                                 Interpolation_Type::LAGRANGE,
                                                                 mIGSpaceInterpolationOrder,
                                                                 Interpolation_Type::LAGRANGE,
                                                                 mIGTimeInterpolationOrder );

                // create an interpolation geometry intepolator
                mLeftIPGeometryInterpolator  = new Geometry_Interpolator( tIPGeometryInterpolationRule, true );
                mRightIPGeometryInterpolator = new Geometry_Interpolator( tIPGeometryInterpolationRule, true );

                // create an integration geometry intepolator
                mLeftIGGeometryInterpolator  = new Geometry_Interpolator( tIGGeometryInterpolationRule, true );
                mRightIGGeometryInterpolator = new Geometry_Interpolator( tIGGeometryInterpolationRule, true );

                // create the element field interpolators
                this->create_field_interpolators_double( aModelSolverInterface );

                // create the element dof assembly map
                this->create_dof_assembly_map_double();

                // create an interpolation rule for the side
                Integration_Rule tIntegrationRule = Integration_Rule( mIGGeometryType,
                                                                      Integration_Type::GAUSS,
                                                                      this->get_auto_integration_order( mIGGeometryType ),
                                                                      Integration_Type::GAUSS,
                                                                      Integration_Order::BAR_1 ); // fixme time order

                // create an integrator
                Integrator tIntegrator( tIntegrationRule );

                //get number of integration points
                mNumOfIntegPoints = tIntegrator.get_number_of_points();

                // get integration points
                mIntegPoints = tIntegrator.get_points();

                // get integration weights
                mIntegWeights = tIntegrator.get_weights();
            }
    }

//------------------------------------------------------------------------------

    void Set::create_unique_dof_type_lists()
    {
        // set the size of the element active dof type list
        uint tCounter = 0;
        for ( IWG * tIWG : mIWGs )
        {
            tCounter = tCounter + tIWG->get_residual_dof_type().size();
        }
        mEqnObjDofTypeList.reserve( tCounter );

        // loop over the IWGs
        tCounter = 0;
        for ( IWG * tIWG : mIWGs )
        {
            mEqnObjDofTypeList.append( tIWG->get_residual_dof_type() );
        }

        auto last = std::unique( ( mEqnObjDofTypeList.data() ).data(),
                                 ( mEqnObjDofTypeList.data() ).data() + mEqnObjDofTypeList.size() );
        auto pos  = std::distance( ( mEqnObjDofTypeList.data() ).data(), last );
        mEqnObjDofTypeList.resize( pos );
    }

//------------------------------------------------------------------------------

    void Set::create_dof_type_lists()
    {
        // get the number of IWGs
        uint tNumOfIWGs = this->get_num_IWG();

        // create a list of the groups of dof types provided by the IWGs----------------
        // FIXME works as long as the dof type are always grouped in the same way
        moris::Cell< MSI::Dof_Type > tInterpDofTypeListBuild( tNumOfIWGs );

        // loop over the IWGs
        for ( uint i = 0; i < tNumOfIWGs; i++ )
        {
            // get the first dof type of each group
            tInterpDofTypeListBuild( i ) = mIWGs( i )->get_residual_dof_type()( 0 );
        }

        // get a unique list of the first dof type of each group
        Cell< moris::moris_index > tUniqueDofTypeGroupsIndices = unique_index( tInterpDofTypeListBuild );

        // get the number of unique dof type groups
        uint tNumOfUniqueDofTypeGroupsIndices = tUniqueDofTypeGroupsIndices.size();

        // set the size of the list of unique dof type groups
        mInterpDofTypeList.resize( tNumOfUniqueDofTypeGroupsIndices );

        // loop over the list of unique dof type groups
        for ( uint i = 0; i < tNumOfUniqueDofTypeGroupsIndices; i++ )
        {
            // get the unique residual dof type groups
            mInterpDofTypeList( i ) = mIWGs( tUniqueDofTypeGroupsIndices( i ) )->get_residual_dof_type();
        }

        // create a map of the element active dof type list------------------------
        // set number of unique pdof type of the element
        mNumOfInterp = tNumOfUniqueDofTypeGroupsIndices;

        // get maximal dof type enum number
        sint tMaxDofTypeEnumNumber = 0;

        // loop over all pdof types to get the highest enum index
        for ( uint i = 0; i < mNumOfInterp; i++ )
        {
            tMaxDofTypeEnumNumber = std::max( tMaxDofTypeEnumNumber, static_cast< int >( mInterpDofTypeList( i )( 0 ) ) );
        }

        // +1 because c++ is 0 based
        tMaxDofTypeEnumNumber = tMaxDofTypeEnumNumber + 1;

        // set size of mapping matrix
        mInterpDofTypeMap.set_size( tMaxDofTypeEnumNumber, 1, -1 );

        // loop over all dof types to create the mapping matrix
        for ( uint i = 0; i < mNumOfInterp; i++ )
        {
            mInterpDofTypeMap( static_cast< int >( mInterpDofTypeList( i )( 0 ) ), 0 ) = i;
        }
    }

//------------------------------------------------------------------------------

    void Set::create_unique_property_type_list()
       {
           // set the size of the active mp type list
           uint tCounter = 0;
           for ( IWG * tIWG : mIWGs )
           {
               tCounter = tCounter + tIWG->get_active_property_types().size();
           }
           mPropertyTypeList.reserve( tCounter );

           // loop over the IWGs
           tCounter = 0;
           for ( IWG * tIWG : mIWGs )
           {
               mPropertyTypeList.append( tIWG->get_active_property_types() );
           }

           auto last = std::unique( ( mPropertyTypeList.data() ).data(), ( mPropertyTypeList.data() ).data() + mPropertyTypeList.size() );
           auto pos  = std::distance( ( mPropertyTypeList.data() ).data(), last );
           mPropertyTypeList.resize( pos );
       }

//------------------------------------------------------------------------------

    void Set::create_dof_assembly_map( )
    {
        // set size of assembly mapping matrix
        mInterpDofAssemblyMap.set_size( mNumOfInterp, 2, -1 );

        // init dof counter
        uint tDofCounter = 0;

        // loop on the dof type groups and create a field interpolator for each
        for( uint i = 0; i < mNumOfInterp; i++ )
        {
            // fill the assembly map with starting dof counter
            mInterpDofAssemblyMap( i, 0 ) = tDofCounter;

            // update dof counter
            tDofCounter = tDofCounter + mFieldInterpolators( i )->get_number_of_space_time_coefficients()-1;

            // fill the assembly map with starting dof counter
            mInterpDofAssemblyMap( i, 1 ) = tDofCounter;

            // update dof counter
            tDofCounter = tDofCounter + 1;
        }

        // set mTotalDof
        mTotalDof = tDofCounter;
    }

    void Set::create_dof_assembly_map_double( )
    {
        // set size of assembly mapping matrix
        mInterpDofAssemblyMap.set_size( mNumOfInterp, 2, -1 );

        // init dof counter
        uint tDofCounter = 0;

        // loop on the dof type groups and create a field interpolator for each
        for( uint i = 0; i < mNumOfInterp; i++ )
        {
            // fill the assembly map with starting dof counter
            mInterpDofAssemblyMap( i, 0 ) = tDofCounter;

            // update dof counter
            //FIXME works if left and right field interpolators are the same
            tDofCounter = tDofCounter + 2 * mLeftFieldInterpolators( i )->get_number_of_space_time_coefficients()-1;

            // fill the assembly map with starting dof counter
            mInterpDofAssemblyMap( i, 1 ) = tDofCounter;

            // update dof counter
            tDofCounter = tDofCounter + 1;
        }

        // set mTotalDof (two times what we have on the left side)
        mTotalDof = tDofCounter;
    }


//------------------------------------------------------------------------------

    mtk::Interpolation_Order Set::get_auto_interpolation_order( const moris::uint        aNumVertices,
                                                                const mtk::Geometry_Type aGeometryType )
    {
        switch( aGeometryType )
        {
            case( mtk::Geometry_Type::LINE ) :
                switch( aNumVertices )
                {
                   case( 1 ) :
                       return mtk::Interpolation_Order::UNDEFINED;
                       break;
                   case( 2 ) :
                       return mtk::Interpolation_Order::LINEAR;
                       break;

                   case( 3 ) :
                       return mtk::Interpolation_Order::QUADRATIC;
                       break;

                   default :
                       MORIS_ERROR( false, " Element::get_auto_interpolation_order - not defined for LINE and number of vertices. ");
                       return mtk::Interpolation_Order::UNDEFINED;
                       break;
                }

            case( mtk::Geometry_Type::QUAD ) :
                switch( aNumVertices )
                {
                    case( 4 ) :
                        return mtk::Interpolation_Order::LINEAR;
                        break;

                    case( 8 ) :
                        return mtk::Interpolation_Order::SERENDIPITY;
                        break;

                    case( 9 ) :
                        return mtk::Interpolation_Order::QUADRATIC;
                        break;

                    case( 16 ) :
                        return mtk::Interpolation_Order::CUBIC;
                        break;

                    default :
                        MORIS_ERROR( false, " Element::get_auto_interpolation_order - not defined for QUAD and number of vertices. ");
                        return mtk::Interpolation_Order::UNDEFINED;
                        break;
                }

            case( mtk::Geometry_Type::HEX ) :
                switch( aNumVertices )
                {
                    case( 8 ) :
                        return mtk::Interpolation_Order::LINEAR;
                        break;

                    case( 20 ) :
                        return mtk::Interpolation_Order::SERENDIPITY;
                        break;

                    case( 27 ) :
                        return mtk::Interpolation_Order::QUADRATIC;
                        break;

                    case( 64 ) :
                        return mtk::Interpolation_Order::CUBIC;
                        break;

                    default :
                        MORIS_ERROR( false, " Element::get_auto_interpolation_order - not defined for HEX and number of vertices. ");
                        return mtk::Interpolation_Order::UNDEFINED;
                        break;
                }

                case( mtk::Geometry_Type::TET ) :
                switch( aNumVertices )
                {
                    case( 4 ) :
                        return mtk::Interpolation_Order::LINEAR;
                        break;

                    case( 10 ) :
                        return mtk::Interpolation_Order::QUADRATIC;
                        break;

                    case( 20 ) :
                        return mtk::Interpolation_Order::CUBIC;
                        break;

                    default :
                        MORIS_ERROR( false, " Element::get_auto_interpolation_order - not defined for TET and number of vertices. ");
                        return mtk::Interpolation_Order::UNDEFINED;
                        break;
                }


            default :
                MORIS_ERROR( false, " Element::get_auto_interpolation_order - not defined for this geometry type. ");
                return mtk::Interpolation_Order::UNDEFINED;
                break;
        }
    }

//------------------------------------------------------------------------------

    fem::Interpolation_Type Set::get_auto_time_interpolation_type( const moris::uint aNumVertices )
    {
        switch( aNumVertices )
        {
          case( 1 ) :
              return Interpolation_Type::CONSTANT;
              break;
          case( 2 ) :
          case( 3 ) :
          case( 4 ) :
              return Interpolation_Type::LAGRANGE;
              break;
          default :
              MORIS_ERROR( false, " Element::get_auto_time_interpolation_type - not defined this number of time vertices. ");
              return Interpolation_Type::UNDEFINED;
              break;
        }
    }

//------------------------------------------------------------------------------

    void Set::create_field_interpolators( MSI::Model_Solver_Interface * aModelSolverInterface )
    {
        // cell of field interpolators
        mFieldInterpolators.resize( mInterpDofTypeList.size() + mPropertyTypeList.size(), nullptr );

        // create a field interpolator for each dof type
        for( uint i = 0; i < mInterpDofTypeList.size(); i++ )
        {
            // get the ith dof type group
            Cell< MSI::Dof_Type > tDofTypeGroup = mInterpDofTypeList( i );

            moris::uint tNumTimeNodes = aModelSolverInterface->get_time_levels_for_type( tDofTypeGroup( 0 ) );

            // create the field interpolation rule for the ith dof type group
            Interpolation_Rule tFieldInterpolationRule( mIPGeometryType,
                                                        Interpolation_Type::LAGRANGE,
                                                        mIPSpaceInterpolationOrder,
                                                        this->get_auto_time_interpolation_type( tNumTimeNodes ), // fixme
                                                        // If interpolation type CONSTANT, iInterpolation order is not used
                                                        this->get_auto_interpolation_order( tNumTimeNodes, mtk::Geometry_Type::LINE ) ); //fixme

            // get number of field interpolated by the ith field interpolator
            uint tNumOfFields = tDofTypeGroup.size();

            // create an interpolator for the ith dof type group
            mFieldInterpolators( i ) = new Field_Interpolator( tNumOfFields,
                                                               tFieldInterpolationRule,
                                                               mIPGeometryInterpolator );
        }

        // create a field interpolator for each property type
        for( uint i = 0; i < mPropertyTypeList.size(); i++ )
        {
            // get the ith property type
            // fem::Property_Type tPropertyType = mPropertyTypeList( i );

            //moris::uint tNumTimeNodes = aModelSolverInterface->get_time_levels_for_type( tPropertyType );

            // create the field interpolation rule for the ith dof type group
            Interpolation_Rule tFieldInterpolationRule( mIPGeometryType,
                                                        Interpolation_Type::LAGRANGE,
                                                        mIPSpaceInterpolationOrder,
                                                        this->get_auto_time_interpolation_type( 2 ), // fixme
                                                        // If interpolation type CONSTANT, iInterpolation order is not used
                                                        this->get_auto_interpolation_order( 2, mtk::Geometry_Type::LINE ) ); //fixme

            // get number of field interpolated by the ith field interpolator
            uint tNumOfFields = 1; // fixme

            // create an interpolator for the ith dof type group
            mFieldInterpolators( mInterpDofTypeList.size() + i ) = new Field_Interpolator( tNumOfFields,
                                                                                           tFieldInterpolationRule,
                                                                                           mIPGeometryInterpolator );
        }
    }

    void Set::create_field_interpolators_double( MSI::Model_Solver_Interface * aModelSolverInterface )
    {
        // init the lists of field interpolators for left and right IP cells
        mLeftFieldInterpolators.resize( mNumOfInterp, nullptr );
        mRightFieldInterpolators.resize( mNumOfInterp, nullptr );

        // loop on the dof type groups and create a field interpolator for each
        for( uint i = 0; i < mNumOfInterp; i++ )
        {
            // get the ith dof type group
            Cell< MSI::Dof_Type > tDofTypeGroup = mInterpDofTypeList( i );

            moris::uint tNumTimeNodes = aModelSolverInterface->get_time_levels_for_type( tDofTypeGroup( 0 ) );

            // create the field interpolation rule for the ith dof type group
            Interpolation_Rule tFieldInterpolationRule( mIPGeometryType,
                                                        Interpolation_Type::LAGRANGE,
                                                        mIPSpaceInterpolationOrder,
                                                        this->get_auto_time_interpolation_type( tNumTimeNodes ), // fixme
                                                        // If interpolation type CONSTANT, iInterpolation order is not used
                                                        this->get_auto_interpolation_order( tNumTimeNodes, mtk::Geometry_Type::LINE ) ); //fixme

            // get number of field interpolated by the ith field interpolator
            uint tNumOfFields = tDofTypeGroup.size();

            // create an interpolator for the ith dof type group
            mLeftFieldInterpolators( i )  = new Field_Interpolator( tNumOfFields,
                                                                    tFieldInterpolationRule,
                                                                    mLeftIPGeometryInterpolator );
            mRightFieldInterpolators( i ) = new Field_Interpolator( tNumOfFields,
                                                                    tFieldInterpolationRule,
                                                                    mRightIPGeometryInterpolator );
        }
    }

//------------------------------------------------------------------------------

    moris::Cell< Field_Interpolator* > Set::get_IWG_field_interpolators ( IWG*                               & aIWG,
                                                                          moris::Cell< Field_Interpolator* > & aFieldInterpolators )
    {
        // ask the IWG for its active dof types
    	moris::Cell< moris::Cell< MSI::Dof_Type > > tIWGActiveDof = aIWG->get_active_dof_types();

        // number of active dof type for the IWG
        uint tNumOfIWGActiveDof = tIWGActiveDof.size();

        // select associated active interpolators
        moris::Cell< Field_Interpolator* > tIWGFieldInterpolators( tNumOfIWGActiveDof, nullptr );
        for( uint i = 0; i < tNumOfIWGActiveDof; i++ )
        {
            // find the index of active dof type in the list of element dof type
            uint tIWGDofIndex = mInterpDofTypeMap( static_cast< int >( tIWGActiveDof( i )( 0 ) ) );

            // select the corresponding interpolator
            tIWGFieldInterpolators( i ) = aFieldInterpolators( tIWGDofIndex );
        }
        return tIWGFieldInterpolators;
    }

//------------------------------------------------------------------------------

    fem::Integration_Order Set::get_auto_integration_order( const mtk::Geometry_Type aGeometryType )
    {
        switch( aGeometryType )
        {
            case( mtk::Geometry_Type::LINE ) :
                return fem::Integration_Order::BAR_3;
                break;

            case( mtk::Geometry_Type::QUAD ) :
                 return fem::Integration_Order::QUAD_3x3;
                 break;

            case( mtk::Geometry_Type::HEX ) :
                return fem::Integration_Order::HEX_3x3x3;
                break;

            case( mtk::Geometry_Type::TRI ) :
                return fem::Integration_Order::TRI_6;
                break;

            case( mtk::Geometry_Type::TET ) :
                return fem::Integration_Order::TET_5;
                break;

            default :
                MORIS_ERROR( false, " Element::get_auto_integration_order - not defined for this geometry type. ");
                return Integration_Order::UNDEFINED;
                break;
        }
    }

//------------------------------------------------------------------------------

    mtk::Geometry_Type Set::get_auto_side_geometry_type( const mtk::Geometry_Type aGeometryType )
    {
        mtk::Geometry_Type tSideGeometryType;

        // depending on the parent geometry type
        switch ( aGeometryType )
        {
            case ( mtk::Geometry_Type::LINE ):
            {
                tSideGeometryType = mtk::Geometry_Type::POINT;
                break;
            }
            case ( mtk::Geometry_Type::QUAD ):
            {
                tSideGeometryType = mtk::Geometry_Type::LINE;
                break;
            }
            case ( mtk::Geometry_Type::HEX ):
            {
                tSideGeometryType = mtk::Geometry_Type::QUAD;
                break;
            }
            case ( mtk::Geometry_Type::TRI ):
                {
                    tSideGeometryType = mtk::Geometry_Type::LINE;
                    break;
                }
            case ( mtk::Geometry_Type::TET ):
                {
                    tSideGeometryType = mtk::Geometry_Type::TRI;
                    break;
                }
            default:
            {
                MORIS_ERROR( false, " Geometry_Interpolator::get_auto_side_geometry_type - undefined geometry type. " );
                tSideGeometryType = mtk::Geometry_Type::UNDEFINED;
            }
        }
        return tSideGeometryType;
    }
//------------------------------------------------------------------------------

    void Set::initialize_mJacobian()
    {
        if ( !mJacobianExist )
        {
            uint tTotalDof = this->get_total_number_of_dofs();
            mJacobian.set_size( tTotalDof, tTotalDof, 0.0 );

            mJacobianExist = true;
        }
        else
        {
            MORIS_ASSERT( mJacobian.numel() > 0, "Set::initialize_mJacobian() - Jacobian not properly initialized.");

            mJacobian.fill( 0.0 );
        }
    }

//------------------------------------------------------------------------------

    void Set::initialize_mResidual()
    {
        if ( !mResidualExist )
        {
            mResidual.set_size( this->get_total_number_of_dofs(), 1, 0.0 );

            mResidualExist = true;
        }
        else
        {
            MORIS_ASSERT( mResidual.numel() > 0, "Set::initialize_mResidual() - Residual not properly initialized.");

            mResidual.fill( 0.0 );
        }
    }

//------------------------------------------------------------------------------


    } /* namespace fem */
} /* namespace moris */
