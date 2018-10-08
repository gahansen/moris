/*
 * cl_Model_Solver_Interface.hpp
 *
 *  Created on: Jul 22, 2018
 *      Author: schmidt
 */
#ifndef SRC_FEM_CL_EQUATION_MANAGER_HPP_
#define SRC_FEM_CL_EQUATION_MANAGER_HPP_

#include "typedefs.hpp"
#include "cl_Cell.hpp"
#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_Map.hpp"

#include "cl_MSI_Dof_Manager.hpp"

namespace moris
{
class Dist_Vector;
    namespace MSI
    {
    class MSI_Solver_Interface;
    class Model_Solver_Interface
    {
    private:
        moris::Cell< Equation_Object* > mEquationObjectList;
        Dof_Manager                     mDofMgn;

    public:
        /**
         * @brief Model solver interface constructor. This function is tested by the test [MSI_Test][MSI_Test_parallel]
         *
         * @param[in] aListEqnObj   List containing all the equation objects.
         * @param[in] aCommTable    Communication table for adofs.
         *
         */
//        Model_Solver_Interface(       moris::Cell < Equation_Object* >                  & aListEqnObj,
//                                const moris::Mat< moris::uint >                         & aCommTable,
//                                const moris::map< moris::moris_id, moris::moris_index > & tAdofLocaltoGlobalMap = moris::map< moris::moris_id, moris::moris_index >(),
//                                const moris::sint                                       & tMaxNumAdofs          = -1) : mEquationObjectList( aListEqnObj ),
//                                                                                                                        mDofMgn( aCommTable, tAdofLocaltoGlobalMap, tMaxNumAdofs)

        Model_Solver_Interface(       moris::Cell < Equation_Object* >                  & aListEqnObj,
                                const Matrix< IdMat >                         & aCommTable,
                                const moris::map< moris::moris_id, moris::moris_index > & tAdofLocaltoGlobalMap,
                                const moris::sint                                       & tMaxNumAdofs ) : mEquationObjectList( aListEqnObj ),
                                                                                                           mDofMgn( aCommTable, tAdofLocaltoGlobalMap, tMaxNumAdofs )
        {
            mDofMgn.initialize_pdof_type_list( aListEqnObj );

            mDofMgn.initialize_pdof_host_list( aListEqnObj );

            mDofMgn.create_adofs();

            mDofMgn.set_pdof_t_matrix();

            for ( moris::uint Ii=0; Ii < aListEqnObj.size(); Ii++ )
            {
                aListEqnObj( Ii )->create_my_pdof_list();
                aListEqnObj( Ii )->create_my_list_of_adof_ids();

                aListEqnObj( Ii )->set_unique_adof_map();
            }
        };

        Model_Solver_Interface(       moris::Cell < Equation_Object* >                  & aListEqnObj,
                                const Matrix< IdMat >                         & aCommTable ) : mEquationObjectList( aListEqnObj ),
                                                                                                         mDofMgn( aCommTable )
        {
            mDofMgn.initialize_pdof_type_list( aListEqnObj );

            mDofMgn.initialize_pdof_host_list( aListEqnObj );

            mDofMgn.create_adofs();

            mDofMgn.set_pdof_t_matrix();

            for ( moris::uint Ii=0; Ii < aListEqnObj.size(); Ii++ )
            {
                aListEqnObj( Ii )->create_my_pdof_list();
                aListEqnObj( Ii )->create_my_list_of_adof_ids();

                aListEqnObj( Ii )->set_unique_adof_map();
            }
        };

        ~Model_Solver_Interface()
        {};

//        void assemble_residual_and_jacobian ( moris::Linear_Solver * aLin,
//                                              moris::Solver_Interface  * aInput,
//                                                     Sparse_Matrix * aMat,
//                                              moris::Dist_Vector   * aVectorRHS );

        moris::uint get_num_eqn_objs()
        {
            return mEquationObjectList.size();
        };

        Dof_Manager * get_dof_manager(){ return &mDofMgn; };

        void get_equation_obj_jacobian( const moris::uint      & aEqnObjInd,
                                              Matrix< DDRMat > & aEqnObjMatrix)
        {
            mEquationObjectList( aEqnObjInd )->get_egn_obj_jacobian( aEqnObjMatrix );
        };

        void get_equation_obj_residual ( const moris::uint      & aEqnObjInd,
                                               Matrix< DDRMat > & aEqnObjRHS,
                                               Dist_Vector * aSolutionVector )
        {
            mEquationObjectList( aEqnObjInd )->get_equation_obj_residual( aEqnObjRHS, aSolutionVector  );
        };

        void get_equation_obj_dof_ids( const moris::uint      & aEqnObjInd,
                                             Matrix< DDSMat > & aElementTopology )
        {
            mEquationObjectList( aEqnObjInd )->get_equation_obj_dof_ids( aElementTopology );
        };
    };
    }
}

#endif /* SRC_FEM_CL_EQUATION_MANAGER_HPP_ */
