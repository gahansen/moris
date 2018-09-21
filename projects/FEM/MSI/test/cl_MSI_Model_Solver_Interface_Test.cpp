/*
 * cl_Dof_Manager_Test.cpp
 *
 *  Created on: Jul 14, 2018
 *      Author: schmidt
 */
#ifdef MORIS_HAVE_PARALLEL
 #include "Epetra_MpiComm.h"
 #include <mpi.h>
#endif

#include "catch.hpp"
#include "fn_equal_to.hpp"
#include "typedefs.hpp"
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_Communication_Tools.hpp"


#include "cl_Solver_Factory.hpp"
#include "cl_Solver_Input.hpp"

#define protected public
#define private   public
#include "cl_MSI_Solver_Interface.hpp"
#include "cl_MSI_Equation_Object.hpp"
#include "cl_MSI_Node_Obj.hpp"
#include "cl_MSI_Model_Solver_Interface.hpp"
#include "cl_MSI_Dof_Manager.hpp"
#include "cl_MSI_Pdof_Host.hpp"
#undef protected
#undef private

namespace moris
{
    namespace MSI
    {

    TEST_CASE("MSI_Test","[MSI],[MSI_Test]")
    {
        if ( par_size() == 1 )
        {
            /*!
             * <h1>User Tutorial: Usage of the MSI based on a two dof problem"</h1>
             * This example creates a pdof and adofs for a simple 2 dop problem
             */
            SECTION( "MSI_Test" )
            {
            /*!
             * <b> Step 1: Preperation: Create node objects </b>
             */

            /*!
             * Create pointer to two FEM node objects
             *
             * \code{.cpp}
             * fem::Node_Base * Node1;
             * fem::Node_Base * Node2;
             * \endcode
             */
            fem::Node_Base * Node1;
            fem::Node_Base * Node2;

            /*!
             * Create matrix with adof Ids for each FEM node
             *
             * \code{.cpp}
             * Matrix< IdMat > tAdofsId1( 2, 1 );
             * Matrix< IdMat > tAdofsId2( 2, 1 );
             *
             * tAdofsId1( 0, 0 ) = 0;         tAdofsId1( 1, 0 ) = 1;
             * tAdofsId2( 0, 0 ) = 1;         tAdofsId2( 1, 0 ) = 0;
             * \endcode
             */
            Matrix< IdMat > tAdofsId1( 2, 1 );
            Matrix< IdMat > tAdofsId2( 2, 1 );

            tAdofsId1( 0, 0 ) = 0;         tAdofsId1( 1, 0 ) = 1;
            tAdofsId2( 0, 0 ) = 1;         tAdofsId2( 1, 0 ) = 0;

            /*!
             * Create matrix with adof Indices for each FEM node
             *
             * \code{.cpp}
             * Matrix< IdMat > tAdofsInd1( 2, 1 );
             * Matrix< IdMat > tAdofsInd2( 2, 1 );
             *
             * tAdofsInd1( 0, 0 ) = 0;        tAdofsInd1( 1, 0 ) = 1;
             * tAdofsInd2( 0, 0 ) = 1;        tAdofsInd2( 1, 0 ) = 0;
             * \endcode
             */
            Matrix< IdMat > tAdofsInd1( 2, 1 );
            Matrix< IdMat > tAdofsInd2( 2, 1 );

            tAdofsInd1( 0, 0 ) = 0;        tAdofsInd1( 1, 0 ) = 1;
            tAdofsInd2( 0, 0 ) = 1;        tAdofsInd2( 1, 0 ) = 0;

            /*!
             * Create matrix with adof T-matrix values for each FEM node
             *
             * \code{.cpp}
             * Matrix< DDRMat > tMatrix1( 2, 1 );
             * Matrix< IdMat > tAdofsInd2( 2, 1 );
             *
             * tMatrix1( 0, 0 ) = 1.0;           tMatrix1( 1, 0 ) = 1.0;
             * tMatrix2( 0, 0 ) = 1.0;           tMatrix2( 1, 0 ) = 2.0;
             * \endcode
             */
            Matrix< DDRMat > tMatrix1( 2, 1 );
            Matrix< DDRMat > tMatrix2( 2, 1 );

            tMatrix1( 0, 0 ) = 1.0;           tMatrix1( 1, 0 ) = 1.0;
            tMatrix2( 0, 0 ) = 1.0;           tMatrix2( 1, 0 ) = 2.0;

            /*!
             * Create matrix with information about adof ownership for each FEM node
             *
             * \code{.cpp}
             * Matrix< IdMat > tAdofOwningProcessor1( 2, 1 );
             * Matrix< IdMat > tAdofOwningProcessor2( 2, 1 );
             *
             * tAdofOwningProcessor1( 0, 0 ) = 0;         tAdofOwningProcessor1( 1, 0 ) = 0;
             * tAdofOwningProcessor2( 0, 0 ) = 0;         tAdofOwningProcessor2( 1, 0 ) = 0;
             * \endcode
             */
            Matrix< IdMat > tAdofOwningProcessor1( 2, 1 );
            Matrix< IdMat > tAdofOwningProcessor2( 2, 1 );

            tAdofOwningProcessor1( 0, 0 ) = 0;         tAdofOwningProcessor1( 1, 0 ) = 0;
            tAdofOwningProcessor2( 0, 0 ) = 0;         tAdofOwningProcessor2( 1, 0 ) = 0;

            /*!
             * Call constructor of node objects. First argument stands for the node Id, argument 1...5 were specified earlier.
             *
             * \code{.cpp}
             * Node1 = new Node_Obj( 0, tAdofsId1, tAdofsInd1, tMatrix1, tAdofOwningProcessor1 );
             * Node2 = new Node_Obj( 1, tAdofsId2, tAdofsInd2, tMatrix2, tAdofOwningProcessor2 );
             * \endcode
             */
            Node1 = new Node_Obj( 0, tAdofsId1, tAdofsInd1, tMatrix1, tAdofOwningProcessor1 );
            Node2 = new Node_Obj( 1, tAdofsId2, tAdofsInd2, tMatrix2, tAdofOwningProcessor2 );

            /*!
             * Create list with node pointers which will be assigned to a equation object
             *
             * \code{.cpp}
             * moris::Cell< fem::Node_Base* > tNodeIds_1( 2 );
             * tNodeIds_1( 0 ) = Node1;       tNodeIds_1( 1 ) = Node2;
             * \endcode
             */
            moris::Cell< fem::Node_Base* > tNodeIds_1( 2 );
            tNodeIds_1( 0 ) = Node1;       tNodeIds_1( 1 ) = Node2;

            moris::Cell< fem::Node_Base* > tNodeIds_2( 2 );
            tNodeIds_2( 0 ) = Node1;       tNodeIds_2( 1 ) = Node2;

            /*!
             * Create  equation objects. Equation objects have a list with nodes assigned
             *
             * \code{.cpp}
             * moris::Cell < Equation_Object* > tListEqnObj( 2, nullptr );
             * Equation_Object EquObj_1( tNodeIds_1 );    Equation_Object EquObj_2( tNodeIds_2 );
             * \endcode
             */
            Equation_Object EquObj_1( tNodeIds_1 );    Equation_Object EquObj_2( tNodeIds_2 );

            /*!
             * Set the equation object dof types. Jacobians and residuals
             *
             * \code{.cpp}
             * EquObj_1.mEqnObjDofTypeList.resize( 1, Dof_Type::TEMP);
             * EquObj_1.mJacobian.set_size( 2, 2, 0.0 );       EquObj_2.mJacobian.set_size( 2, 2, 0.0 );
             * EquObj_1.mResidual.set_size( 2, 1, 0.0 );       EquObj_2.mResidual.set_size( 2, 1, 0.0 );
             *
             * EquObj_1.mJacobian.set_size( 2, 2, 0.0 );            EquObj_2.mJacobian.set_size( 2, 2, 0.0 );
             * EquObj_1.mResidual.set_size( 2, 1, 0.0 );            EquObj_2.mResidual.set_size( 2, 1, 0.0 );
             *
             * EquObj_1.mJacobian( 0, 0 ) = 1;            EquObj_1.mJacobian( 0, 1 ) = 2;
             * EquObj_2.mJacobian( 1, 0 ) = 1;            EquObj_2.mJacobian( 1, 1 ) = -3;
             *
             * EquObj_1.mResidual( 0, 0 ) = 5;
             * \endcode
             */
            EquObj_1.mEqnObjDofTypeList.resize( 1, Dof_Type::TEMP);
            EquObj_2.mEqnObjDofTypeList.resize( 1, Dof_Type::TEMP);

            EquObj_1.mJacobian.set_size( 2, 2, 0.0 );            EquObj_2.mJacobian.set_size( 2, 2, 0.0 );
            EquObj_1.mResidual.set_size( 2, 1, 0.0 );            EquObj_2.mResidual.set_size( 2, 1, 0.0 );

            EquObj_1.mJacobian( 0, 0 ) = 1;            EquObj_1.mJacobian( 0, 1 ) = 2;
            EquObj_2.mJacobian( 1, 0 ) = 1;            EquObj_2.mJacobian( 1, 1 ) = -3;

            EquObj_1.mResidual( 0, 0 ) = 5;

            /*!
             * Set a list with equation object pointers. This particular list has a size of 2 and 2 equation objects assigned
             *
             * \code{.cpp}
             * moris::Cell < Equation_Object* > tListEqnObj( 2, nullptr );
             * tListEqnObj( 0 ) = & EquObj_1;      tListEqnObj( 1 ) = & EquObj_2;
             * \endcode
             */
            moris::Cell < Equation_Object* > tListEqnObj( 2, nullptr );
            tListEqnObj( 0 ) = & EquObj_1;      tListEqnObj( 1 ) = & EquObj_2;

            /*!
             * Creating cammunication table
             *
             * \code{.cpp}
             * Matrix< IdMat > tCommTable( 1, 1, 0 );
             * \endcode
             */
            Matrix< IdMat > tCommTable( 1, 1, 0 );

            /*!
             * <b> Step 2: Creating the Model Solver Interface and solve the problem </b>
             */

            /*!
             * Create MSI. Input argument are the list of equation object pointers and the communication table
             *
             * \code{.cpp}
             * Model_Solver_Interface tMSI( tListEqnObj, tCommTable );
             * \endcode
             */
            Model_Solver_Interface tMSI( tListEqnObj, tCommTable );

            /*!
             * Create solver Interface
             *
             * \code{.cpp}
             * moris::Solver_Input *  tSolverInput = new moris::MSI::MSI_Solver_Interface( &tMSI, tMSI.get_dof_manager() );
             * \endcode
             */
            moris::Solver_Input *  tSolverInput = new moris::MSI::MSI_Solver_Interface( &tMSI, tMSI.get_dof_manager() );

            /*!
             * Create solver
             *
             * \code{.cpp}
             * moris::Solver_Factory  tSolFactory;
             *
             * std::shared_ptr< Linear_Solver > tLin = tSolFactory.create_solver( tSolverInput );
             * \endcode
             */
            moris::Solver_Factory  tSolFactory;

            std::shared_ptr< Linear_Solver > tLin = tSolFactory.create_solver( tSolverInput );

            /*!
             * Solve linear system
             *
             * \code{.cpp}
             * tLin->solve_linear_system();
             * \endcode
             */
            tLin->solve_linear_system();

            Matrix< DDRMat > tSolution;
            tLin->get_solution( tSolution );

            CHECK( equal_to( tSolution( 0, 0 ), -2 ) );
            CHECK( equal_to( tSolution( 1, 0 ), 5 ) );

            delete Node1;
            delete Node2;
            delete tSolverInput;
            }
        }
    }

    TEST_CASE("MSI_Test_parallel","[MSI],[MSI_Test_parallel][MSI_parallel]")
    {
        size_t tSize = par_size();

        if ( tSize == 2 )
        {
            // Create node obj
            moris::uint tNodeId1 = 0;
            moris::uint tNodeId2 = 1;
            moris::uint tNodeId3 = 2;
            moris::uint tNodeId4 = 3;

            fem::Node_Base * Node1;
            fem::Node_Base * Node2;

            // Create generic adofs to this nodes pdof
            Matrix< IdMat > tAdofsId1( 2, 1 );
            Matrix< IdMat > tAdofsId2( 2, 1 );

            // Create generic adofs to this nodes pdof
            Matrix< IdMat > tAdofsInd1( 2, 1 );
            Matrix< IdMat > tAdofsInd2( 2, 1 );

            // Create generic T-matrices
            Matrix< DDRMat > tMatrix1( 2, 1 );
            Matrix< DDRMat > tMatrix2( 2, 1 );

            // Create generic adof owning processor
            Matrix< IdMat > tAdofOwningProcessor1( 2, 1 );
            Matrix< IdMat > tAdofOwningProcessor2( 2, 1 );

            // Determine process rank
            size_t tRank = par_rank();
            size_t tSize = par_size();

            Matrix< IdMat > tCommTable( 2, 1 );
            moris::uint tNumEquationObjects;
            moris::uint tNumNodes;
            moris::Cell < Equation_Object* >tListEqnObj;
            moris::Cell< fem::Node_Base* > tNodeIds_1;
            moris::Cell< fem::Node_Base* > tNodeIds_2;

            moris::map< moris::sint, moris::sint >  tAdofGlobaltoLocalMap;

            // Hardcode input test values
            switch( tRank )
            {
            case 0:
                tAdofsId1( 0, 0 ) = 0;
                tAdofsId1( 1, 0 ) = 1;
                tAdofsId2( 0, 0 ) = 1;
                tAdofsId2( 1, 0 ) = 2;

                tAdofsInd1( 0, 0 ) = 0;
                tAdofsInd1( 1, 0 ) = 1;
                tAdofsInd2( 0, 0 ) = 1;
                tAdofsInd2( 1, 0 ) = 2;

                tMatrix1( 0, 0 ) = 1.0;
                tMatrix1( 1, 0 ) = 1.0;
                tMatrix2( 0, 0 ) = 1.0;
                tMatrix2( 1, 0 ) = 2.0;

                tAdofOwningProcessor1( 0, 0 ) = 0;
                tAdofOwningProcessor1( 1, 0 ) = 0;
                tAdofOwningProcessor2( 0, 0 ) = 0;
                tAdofOwningProcessor2( 1, 0 ) = 1;

                // Create generic Node Object
                Node1 = new Node_Obj( tNodeId1, tAdofsId1, tAdofsInd1, tMatrix1, tAdofOwningProcessor1 );
                Node2 = new Node_Obj( tNodeId2, tAdofsId2, tAdofsInd2, tMatrix2, tAdofOwningProcessor2 );

                tCommTable( 0, 0 ) = 0;
                tCommTable( 1, 0 ) = 1;

                tNumEquationObjects = 2;
                tNumNodes = 2;
                tListEqnObj.resize( tNumEquationObjects, nullptr );

                // Create List with node pointern correponding to generic equation object
                tNodeIds_1.resize( tNumNodes );
                tNodeIds_1( 0 ) = Node1;
                tNodeIds_1( 1 ) = Node2;

                tNodeIds_2.resize( tNumNodes );
                tNodeIds_2( 0 ) = Node1;
                tNodeIds_2( 1 ) = Node2;

                tAdofGlobaltoLocalMap[ 0 ] = 0;
                tAdofGlobaltoLocalMap[ 1 ] = 1;
                tAdofGlobaltoLocalMap[ 2 ] = 2;

              break;
            case 1:
                tAdofsId1( 0, 0 ) = 3;
                tAdofsId1( 1, 0 ) = 1;
                tAdofsId2( 0, 0 ) = 3;
                tAdofsId2( 1, 0 ) = 0;

                tAdofsInd1( 0, 0 ) = 0;
                tAdofsInd1( 1, 0 ) = 1;
                tAdofsInd2( 0, 0 ) = 0;
                tAdofsInd2( 1, 0 ) = 3;

                tMatrix1( 0, 0 ) = 1.0;
                tMatrix1( 1, 0 ) = 1.0;
                tMatrix2( 0, 0 ) = 1.0;
                tMatrix2( 1, 0 ) = 2.0;

                tAdofOwningProcessor1( 0, 0 ) = 1;
                tAdofOwningProcessor1( 1, 0 ) = 0;
                tAdofOwningProcessor2( 0, 0 ) = 1;
                tAdofOwningProcessor2( 1, 0 ) = 0;

                // Create generic Node Object
                Node1 = new Node_Obj( tNodeId3, tAdofsId1, tAdofsInd1, tMatrix1, tAdofOwningProcessor1 );
                Node2 = new Node_Obj( tNodeId4, tAdofsId2, tAdofsInd2, tMatrix2, tAdofOwningProcessor2 );

                tCommTable( 0, 0 ) = 1;
                tCommTable( 1, 0 ) = 0;

                tNumEquationObjects = 2;
                tNumNodes = 2;
                tListEqnObj.resize( tNumEquationObjects, nullptr );

                // Create List with node pointern correponding to generic equation object
                tNodeIds_1.resize( tNumNodes );
                tNodeIds_1( 0 ) = Node1;
                tNodeIds_1( 1 ) = Node2;

                tNodeIds_2.resize( tNumNodes );
                tNodeIds_2( 0 ) = Node1;
                tNodeIds_2( 1 ) = Node2;

                tAdofGlobaltoLocalMap[ 0 ] = 3;
                tAdofGlobaltoLocalMap[ 1 ] = 1;
                tAdofGlobaltoLocalMap[ 2 ] = 2;
                tAdofGlobaltoLocalMap[ 3 ] = 0;
              break;
            default:
                Node1 = new Node_Obj( tNodeId1, tAdofsId1, tAdofsInd1, tMatrix1, tAdofOwningProcessor1 );
                Node2 = new Node_Obj( tNodeId1, tAdofsId1, tAdofsInd1, tMatrix1, tAdofOwningProcessor1 );
                break;
            }

            // Create generic equation objects
            Equation_Object EquObj_1( tNodeIds_1 );
            Equation_Object EquObj_2( tNodeIds_2 );

            EquObj_1.mEqnObjDofTypeList.resize( 1, Dof_Type::TEMP );
            EquObj_2.mEqnObjDofTypeList.resize( 1, Dof_Type::TEMP );

            EquObj_1.mJacobian.set_size( 2, 2, 0.0);
            EquObj_2.mJacobian.set_size( 2, 2, 0.0);
            EquObj_1.mResidual.set_size( 2, 1, 0.0);
            EquObj_2.mResidual.set_size( 2, 1, 0.0);

            EquObj_1.mJacobian( 0, 0 ) = 1;
            EquObj_1.mJacobian( 0, 1 ) = 2;
            EquObj_2.mJacobian( 1, 0 ) = 1;
            EquObj_2.mJacobian( 1, 1 ) = -3;

            EquObj_1.mResidual( 0, 0 ) = 2;

            EquObj_2.mResidual( 1, 0 ) = 2;

            // Create List with equation objects
            tListEqnObj( 0 ) = & EquObj_1;
            tListEqnObj( 1 ) = & EquObj_2;

            Model_Solver_Interface tMSI( tListEqnObj, tCommTable, tAdofGlobaltoLocalMap, 4 );

            // create solver input object
            moris::MSI::MSI_Solver_Interface * tSolverInput;
            tSolverInput = new moris::MSI::MSI_Solver_Interface( &tMSI, tMSI.get_dof_manager() );

            // create solver factory
            moris::Solver_Factory  tSolFactory;

            // create solver object
            std::shared_ptr< Linear_Solver > tLin = tSolFactory.create_solver( tSolverInput );

            tLin->solve_linear_system();

            Matrix< DDRMat > tSolution;
            tLin->get_solution( tSolution );

            if ( par_rank() == 0 )
            {
                CHECK( equal_to( tSolution( 0, 0 ), 0 ) );
                CHECK( equal_to( tSolution( 1, 0 ), 2 ) );
            }
            else if ( par_rank() == 1 )
            {
                CHECK( equal_to( tSolution( 0, 0 ), 0 ) );
                CHECK( equal_to( tSolution( 1, 0 ), -1 ) );
            }
            delete Node1;
            delete Node2;
        }
    }
    }
}

