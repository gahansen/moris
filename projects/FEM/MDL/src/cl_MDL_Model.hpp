/*
 * cl_MDL_Model.hpp
 *
 *  Created on: Aug 22, 2018
 *      Author: messe
 */

#ifndef PROJECTS_FEM_MDL_SRC_CL_MDL_MODEL_HPP_
#define PROJECTS_FEM_MDL_SRC_CL_MDL_MODEL_HPP_

#include "typedefs.hpp"                       //MRS/COR/src
#include "cl_Cell.hpp"                        //MRS/CON/src

#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_MTK_Enums.hpp"

namespace moris
{

//------------------------------------------------------------------------------
    namespace mtk
    {
       class Mesh_Manager;
    }

    namespace vis
    {
       class Output_Manager;
    }

    namespace fem
    {
        class IWG;
        class Node_Base;
        class Cell;
        class Set;
        class Field_Interpolator;
        class Set_User_Info;
    }

    namespace dla
    {
        class Linear_Solver;
        class Linear_Solver_Algorithm;
    }

    namespace MSI
    {
        class Model_Solver_Interface;
        class MSI_Solver_Interface;
        class Equation_Set;
        class Equation_Object;
        class Equation_Model;
        class Design_Variable_Interface;
        enum class Dof_Type;
    }
    namespace tsa
    {
        class Time_Solver;
        class Time_Solver_Algorithm;
    }
    namespace mdl
    {
//------------------------------------------------------------------------------

        class Model
        {
            // pointer to reference mesh
            mtk::Mesh_Manager* mMeshManager = nullptr;
            moris_index        mMeshPairIndex;

            std::shared_ptr< MSI::Equation_Model >    mEquationModel = nullptr;

            // list of FEM sets
            moris::Cell< MSI::Equation_Set * > mEquationSets;

            // list of FEM clusters
            moris::Cell< MSI::Equation_Object* > mEquationObjects;

            // by default, this value is set to the order of the
            // Lagrange modes
            moris::uint                       mBSplineIndex = 0;

            // model solver interface pointer
            MSI::Model_Solver_Interface * mModelSolverInterface = nullptr;

            // solver interface pointer
            MSI::MSI_Solver_Interface   * mSolverInterface = nullptr;

            // fixme: maybe introduce a cell of maps for different orders?
            map< moris_id, moris_index >      mCoefficientsMap;
            Matrix< DDUMat >                  mAdofMap;

            Matrix< DDRMat> mSolHMR;

            tsa::Time_Solver * mTimeSolver = nullptr;

            vis::Output_Manager * mOutputManager = nullptr;

            bool mUseMultigrid = false;

//------------------------------------------------------------------------------
        public:
//------------------------------------------------------------------------------
            /**
             * constructor
             * @param[ in ] aMesh          mesh for this problem
             * @param[ in ] aBSplineOrder  ???
             * @param[ in ] aSetInfo       cell of set user info
             * @param[ in ] aMeshPairIndex ???
             * @param[ in ] aUseMultigrid  bool for multigrid use
             */
            Model(       mtk::Mesh_Manager*                  aMeshManager,
                   const uint                                aBSplineIndex,
                         moris::Cell< fem::Set_User_Info > & aSetInfo,
                   const moris_index                         aMeshPairIndex = 0,
                   const bool                                aUseMultigrid  = false );

            Model(       mtk::Mesh_Manager*                  aMeshManager,
                   const uint                                aBSplineIndex,
                         moris::Cell< fem::Set_User_Info > & aSetInfo,
                         MSI::Design_Variable_Interface * aDesignVariableInterface,
                   const moris_index                         aMeshPairIndex = 0,
                   const bool                                aUseMultigrid  = false );

//------------------------------------------------------------------------------
            /**
             * destructor
             */
            ~Model();

//------------------------------------------------------------------------------
            /**
             * FIXME
             * gets HMR solution vector
             */
            Matrix< DDRMat> & get_mSolHMR( )
            {
                return mSolHMR;
            };

//------------------------------------------------------------------------------
            /**
             * sets dof order
             * @param[ in ] aOrder an order
             */
            void set_dof_order( const uint aOrder );

//------------------------------------------------------------------------------
            /**
             * get equation sets for test
             */
            moris::Cell< MSI::Equation_Set * > & get_equation_sets( )
            {
                return mEquationSets;
            };

//------------------------------------------------------------------------------

            map< moris_index, moris_index > & get_mesh_set_to_fem_set_index_map( );

//------------------------------------------------------------------------------
            /**
             * gets the solver interface
             */
            MSI::MSI_Solver_Interface * get_solver_interface()
            {
                return mSolverInterface;
            }

//------------------------------------------------------------------------------
            /**
             * gets the adof map
             */
            Matrix< DDUMat > & get_adof_map()
            {
                return mAdofMap;
            }

//------------------------------------------------------------------------------
            /**
             * gets the lagrange interpolation order from the mesh
             */
            uint get_lagrange_order_from_mesh();

//------------------------------------------------------------------------------
            /**
             * FIXME
             * sets the weak BCs
             * @param[ in ] aWeakBCs matrix with weak BCs value
             */
            void set_weak_bcs( const Matrix< DDRMat > & aWeakBCs );

//------------------------------------------------------------------------------
            /**
             * FIXME
             * sets the weak BCs from a nodal field
             * @param[ in ] aFieldIndex an index for the field
             */
            void set_weak_bcs_from_nodal_field( moris_index aFieldIndex );

//------------------------------------------------------------------------------
            /**
             * FIXME
             * computes the integration error
             * @param[ in ] aFunction a function pointer to compute the integration error
             */
            real compute_integration_error( real (*aFunction)( const Matrix< DDRMat > & aPoint ) );

//------------------------------------------------------------------------------
            /**
             * FIXME
             * computes an element average
             * @param[ in ] aElementIndex an element index
             */
           real compute_element_average( const uint aElementIndex );

//------------------------------------------------------------------------------
           /**
            * outputs the solution in a file
            * @param[ in ] aFilePath a file path
            */
           void output_solution( const std::string & aFilePath );

//------------------------------------------------------------------------------
           /*
            * Returns matrix for integration mesh outputting
            * @param[ in ] aDofType a dof type for outputting
            */
           Matrix<DDRMat> get_solution_for_integration_mesh_output( enum MSI::Dof_Type aDofType );

//------------------------------------------------------------------------------

           void set_output_manager( vis::Output_Manager * aOutputManager )
           {
               mOutputManager = aOutputManager;
           }

//------------------------------------------------------------------------------

           void output_solution( const uint aVisMeshIndex,
                                 const real aTime );

//------------------------------------------------------------------------------
           /*!
            * Provided a list of dofs, returns a bool saying whether the desired dof is
            * contained in the cell of dof types
            * @param[ in ] aDofTypeToFind a dof type for search for
            * @param[ in ] aDofList       a list of dof types to serach through
            */
           bool dof_type_is_in_list( enum MSI::Dof_Type                  aDofTypeToFind,
                                     moris::Cell< enum MSI::Dof_Type > & aDofList );

//------------------------------------------------------------------------------
        };
//------------------------------------------------------------------------------
    } /* namespace mdl */
} /* namespace moris */


#endif /* PROJECTS_FEM_MDL_SRC_CL_MDL_MODEL_HPP_ */
