
/*
 * cl_MSI_Multigrid.cpp
 *
 *  Created on: Jul 14, 2018
 *      Author: schmidt
 */
#include "catch.hpp"

#include "typedefs.hpp"
#include "cl_Map.hpp"

#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"

#include "cl_Communication_Tools.hpp"
#include "cl_Communication_Manager.hpp"

#include "fn_equal_to.hpp"

#include "MSI_Adof_Order_Hack.hpp"

#define protected public
#define private   public
#include "cl_MSI_Adof.hpp"
#include "cl_MSI_Pdof_Host.hpp"
#include "cl_MSI_Equation_Object.hpp"
#include "cl_MSI_Dof_Manager.hpp"
#include "cl_MSI_Model_Solver_Interface.hpp"
#include "cl_MSI_Node_Proxy.hpp"
#undef protected
#undef private

#include "cl_HMR_Parameters.hpp"
#include "cl_HMR.hpp"
#include "cl_HMR_Field.hpp"

#include "cl_FEM_Node_Base.hpp"
#include "cl_FEM_Element.hpp"

#include "cl_MTK_Mapper.hpp"
#include "cl_FEM_IWG_L2.hpp"

#include "fn_r2.hpp"

moris::real
LevelSetFunction( const moris::Matrix< moris::DDRMat > & aPoint )
{
    return norm( aPoint ) - 1.2;
}

namespace moris
{
    namespace MSI
    {
    TEST_CASE("MSI_Multigrid","[MSI],[multigrid]")
    {
        if( moris::par_size() == 1 )
        {
             moris::hmr::Parameters tParameters;

             tParameters.set_number_of_elements_per_dimension( { { 2} , { 2 } } );
             tParameters.set_domain_offset( 0, 0 );

             uint tOrder = 1;
             moris::MSI::gAdofOrderHack = tOrder;

             tParameters.set_mesh_orders_simple( tOrder );
             tParameters.set_verbose( true );
             tParameters.set_multigrid( false );

             // create HMR object
             moris::hmr::HMR tHMR( tParameters );

             // flag first element
             tHMR.flag_element( 0 );

             // call internal refinement function
             tHMR.get_database()->get_background_mesh()->perform_refinement();

             // finish mesh
             tHMR.finalize();

             // grab pointer to output field
             std::shared_ptr< moris::hmr::Mesh > tMesh = tHMR.create_mesh( tOrder );

             tHMR.save_mesh_to_vtk("LagrangeMesh.vtk");
             tHMR.save_bsplines_to_vtk("BSplines.vtk");
             // create field
             std::shared_ptr< moris::hmr::Field > tField = tMesh->create_field( "Circle", tOrder );

             // evaluate node values
             tField->evaluate_scalar_function( LevelSetFunction );

             for( uint k=0; k<tHMR.get_database()->get_number_of_bspline_meshes(); ++k )
             {
            	 moris::hmr::BSpline_Mesh_Base * tMesh = tHMR.get_database()->get_bspline_mesh_by_index( k );

            	 std::cout << "BSpline-Mesh " << k << " pattern: " << tMesh->get_activation_pattern()
            			 << " order " << tMesh->get_order()
						 << " basis " << tMesh->get_number_of_active_basis_on_proc() << std::endl;

             }

             exit( 0 );
             //-------------------------------------------------------------------------------------------

             // create IWG object
             fem::IWG_L2 * tIWG = new moris::fem::IWG_L2( );

             map< moris_id, moris_index >   tCoefficientsMap;
             Cell< fem::Node_Base* >        tNodes;
             Cell< MSI::Equation_Object* >  tElements;

             // get map from mesh
             tMesh->get_adof_map( tOrder, tCoefficientsMap );

             // ask mesh about number of nodes on proc
             luint tNumberOfNodes = tMesh->get_num_nodes();

             // create node objects
             tNodes.resize( tNumberOfNodes, nullptr );

             for( luint k = 0; k < tNumberOfNodes; ++k )
             {
                 tNodes( k ) = new fem::Node( &tMesh->get_mtk_vertex( k ) );
             }

             // ask mesh about number of elements on proc
             luint tNumberOfElements = tMesh->get_num_elems();

             // create equation objects
             tElements.resize( tNumberOfElements, nullptr );

             for( luint k=0; k<tNumberOfElements; ++k )
             {
                 // create the element
                 tElements( k ) = new fem::Element( & tMesh->get_mtk_cell( k ),
                                                    tIWG,
                                                    tNodes );
             }

             MSI::Model_Solver_Interface * tMSI = new moris::MSI::Model_Solver_Interface( tElements,
                                                                                          tMesh->get_communication_table(),
                                                                                          tCoefficientsMap,
                                                                                          tMesh->get_num_coeffs( tOrder ),
                                                                                          tMesh.get() );
        }
    }

        TEST_CASE("MSI_Multigrid1","[MSI],[multigrid1]")
        {
            if( moris::par_size() == 1 )
            {
                 moris::hmr::Parameters tParameters;

                 tParameters.set_number_of_elements_per_dimension( { { 2} , { 2 } } );
                 tParameters.set_domain_offset( 0, 0 );

                 uint tOrder = 2;
                 tParameters.set_mesh_orders_simple( tOrder );
                 tParameters.set_verbose( true );
                 tParameters.set_multigrid( true );

                 // create HMR object
                 moris::hmr::HMR tHMR( tParameters );

                 // flag first element
                 tHMR.flag_element( 0 );
                 tHMR.perform_refinement( moris::hmr::gRefinementModeBSpline );

                 // finish mesh
                 tHMR.finalize();

                 // grab pointer to output field
                 std::shared_ptr< moris::hmr::Mesh > tMesh = tHMR.create_mesh( tOrder );

                 // create field
                 std::shared_ptr< moris::hmr::Field > tField = tMesh->create_field( "Circle", tOrder );
                 std::shared_ptr< moris::hmr::Field > tExact = tMesh->create_field( "Exact", tOrder );

                 // evaluate node values
                 tField->evaluate_scalar_function( LevelSetFunction );
                 tExact->get_node_values() = tField->get_node_values();

                 // create mapper
                 moris::mapper::Mapper tMapper( tMesh );

                 // call mapping function
                 tMapper.perform_mapping(
                         tField->get_label(),
                         EntityRank::NODE,
                         tField->get_label(),
                         tField->get_bspline_rank() );

                 tField->evaluate_node_values();

                 // save field to hdf5
                 tField->save_field_to_hdf5("Circle.hdf5");

                 // determine coefficient of determination
                 moris::real tR2 = moris::r2( tExact->get_node_values(),
                         tField->get_node_values() );

                 std::cout << "R2 " << tR2 << std::endl;
            }
    }
    }
}


