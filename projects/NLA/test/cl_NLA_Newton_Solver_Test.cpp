/*
 * cl_NLA_Newton_Solver.cpp
 *
 *  Created on: Sep 21, 2018
 *      Author: schmidt
 */
#ifdef MORIS_HAVE_PARALLEL
 #include <mpi.h>
#endif

#include "catch.hpp"
#include "fn_equal_to.hpp"
#include "typedefs.hpp"
#include "cl_Matrix.hpp"
#include "fn_reshape.hpp"
#include "fn_print.hpp"

#include "linalg_typedefs.hpp"
#include "cl_Communication_Tools.hpp"

#include "cl_DLA_Solver_Factory.hpp"
#include "cl_DLA_Linear_Solver_Aztec.hpp"
#include "cl_DLA_Linear_Solver_Manager.hpp"
#include "cl_Vector.hpp"

#define protected public
#define private   public
#include "cl_NLA_Nonlinear_Solver_Factory.hpp"
#include "cl_NLA_Newton_Solver.hpp"
#include "cl_NLA_Nonlinear_Problem.hpp"
#include "cl_NLA_Solver_Interface_Proxy.hpp"
#undef protected
#undef private

namespace moris
{
    Matrix< DDRMat > test_residual1( const moris::sint aNX,
                                     const moris::sint aNY,
                                           Matrix< DDRMat > tMyValues,
                                     const moris::uint      aEquationObjectInd )
    {
        Matrix< DDRMat > tResidual( 2, 1, 0.0);
        tResidual( 0, 0 ) = (0.4 - 10*tMyValues( 0, 0 ) - 0.4*std::pow(tMyValues( 1, 0 ),3) + 5*std::pow(tMyValues( 1, 0 ),2));
        tResidual( 1, 0 ) = (0.15 - 0.4*std::pow(tMyValues( 0, 0 ),3) + 3*std::pow(tMyValues( 0, 0 ),2) - 10*tMyValues( 1, 0 ));

        return tResidual;
    }

    Matrix< DDRMat > test_jacobian1( const moris::sint aNX,
                                     const moris::sint aNY,
                                           Matrix< DDRMat > tMyValues,
                                     const moris::uint      aEquationObjectInd )
    {
        Matrix< DDRMat > tJacobian( 2, 2, 0.0);

        tJacobian( 0, 0 ) = -10;
        tJacobian( 0, 1 ) = -1.2*std::pow(tMyValues( 0, 0 ),2)+6*tMyValues( 0, 0 );
        tJacobian( 1, 0 ) = -1.2*std::pow(tMyValues( 1, 0 ),2)+10*tMyValues( 1, 0 );
        tJacobian( 1, 1 ) = -10;

        return tJacobian;
    }

    Matrix< DDSMat > test_topo1( const moris::sint aNX,
                                 const moris::sint aNY,
                                 const moris::uint aEquationObjectInd )
    {
    moris::Matrix< moris::DDSMat > tTopo( 2, 1, -1 );

    for ( moris::sint Ik = 0; Ik < 2; Ik++ )
    {
        tTopo( Ik, 0 ) = Ik;
    }

    return tTopo;
    }

    Matrix< DDRMat > test_residual_bratu( const moris::sint aNX,
                                     const moris::sint aNY,
                                           Matrix< DDRMat > tMyValues,
                                     const moris::uint      aEquationObjectInd )
    {
    moris::sint j = std::floor( (aEquationObjectInd ) / aNX );
    moris::sint i = aEquationObjectInd - ( j * aNX );
    moris::real lambda = 2;
    moris::sint tN = aNX;

    Matrix< DDRMat > tF( 1, 1, 0.0);

    moris::real hx     = 1.0/(tN-1);
    moris::real hy     = 1.0/(tN-1);
    moris::real sc     = hx*hy*lambda;
    moris::real hxdhy  = hx/hy;
    moris::real hydhx  = hy/hx;

    if (i == 0 || j == 0 || i == tN-1 || j == tN-1)
    {
         tF( 0, 0 ) = tMyValues((j*tN) + i, 0 );
    }
    else
    {
        moris::real u    = tMyValues((j*tN) + i, 0 );
        moris::real uxx  = (2.0*u - tMyValues((j*tN) + i-1, 0 ) - tMyValues((j*tN)+i+1, 0 ) )*hydhx;
        moris::real uyy  = (2.0*u - tMyValues(((j-1)*tN)+i, 0 ) - tMyValues(((j+1)*tN)+i, 0 ))*hxdhy;
        tF(0, 0 ) = uxx + uyy - sc*std::exp(u);
    }

    Matrix< DDRMat > tResidual( 5, 1, 0.0);

    tResidual( 2, 0 ) = tF( 0, 0 );

    return tResidual;
    }

    Matrix< DDRMat > test_jacobian_bratu( const moris::sint aNX,
                                     const moris::sint aNY,
                                           Matrix< DDRMat > tMyValues,
                                     const moris::uint      aEquationObjectInd )
    {
    moris::sint j = std::floor( (aEquationObjectInd ) / aNX );
    moris::sint i = aEquationObjectInd - ( j * aNX );
    moris::real lambda = 2;
    moris::sint tN = aNX;

    Matrix< DDRMat > tVal( 1, 5, 0.0);

    moris::real hx     = 1.0/(tN-1);
    moris::real hy     = 1.0/(tN-1);
    moris::real sc     = hx*hy*lambda;
    moris::real hxdhy  = hx/hy;
    moris::real hydhx  = hy/hx;

    if (i == 0 || j == 0 || i == tN-1 || j == tN-1)
    {
        tVal( 0, 0 ) = 0.0;
        tVal( 0, 1 ) = 0.0;
        tVal( 0, 2 ) = 1.0;
        tVal( 0, 3 ) = 0.0;
        tVal( 0, 4 ) = 0.0;
    }
    else
    {
        moris::real u    = tMyValues((j*tN) + i, 0 );

        tVal( 0, 0) = - hxdhy;
        tVal( 0, 1 ) = - hydhx;
        tVal( 0, 2 ) = 2.0 * (hxdhy + hydhx) - sc*std::exp(u) ;
        tVal( 0, 3 ) = - hydhx;
        tVal( 0, 4 ) = -hxdhy;
    }

    moris::Matrix< moris::DDRMat > tJacobian( 5, 5, 0.0 );

    for ( moris::sint Ik = 0; Ik < 5; Ik++ )
    {
        tJacobian( 2, Ik ) = tVal( 0, Ik );
    }

    return tJacobian;
    }

    Matrix< DDSMat > test_topo_bratu( const moris::sint aNX,
                                 const moris::sint aNY,
                                 const moris::uint      aEquationObjectInd )
    {
    moris::sint j = std::floor( (aEquationObjectInd ) / aNX );
    moris::sint i = aEquationObjectInd - ( j * aNX );
    moris::sint tN = aNX;

    Matrix< DDSMat > tCol( 1, 5, 0);

    tCol( 0, 0 ) = (((j-1)*tN) + i );
    tCol( 0, 1 ) = ((j*tN) + i -1 );
    tCol( 0, 2 ) = ((j*tN) + i );
    tCol( 0, 3 ) = ((j*tN) + i +1 );
    tCol( 0, 4 ) = (((j+1)*tN) + i );

    moris::Matrix< moris::DDSMat > tTopo( 5, 1, -1 );

    for ( moris::sint Ik = 0; Ik < 5; Ik++ )
    {
        tTopo( Ik, 0 ) = tCol( 0, Ik );
    }

    return tTopo;
    }


    namespace NLA
    {
    TEST_CASE("Newton Solver Test 1","[NLA],[NLA_Test1]")
    {
          if ( par_size() == 1 )
          {
        /*!
         * <b> Step 1: Create proxy interface and nonlinear solver </b>
         */

        /*!
         * Build linear solver interface. For testing we use the well known, non-convex "Rosenbrock" benchmark function. <br>
         * Rosenbrock, H.H. (1960). "An automatic method for finding the greatest or least value of a function". The Computer Journal. 3 (3): 175–184
         *
         * The nonlinear problem is stated as followed.
         * \f[ R = \begin{bmatrix} 0.4 -10x_1   -0.4x_2^3+5x_2^2 \\ 0.15-0.4x_1^3+3x_1^2  -10x_2 \\ \end{bmatrix} = 0 \f]
         *
         * Therfore the corresponding linearized system can be stated as followed.
         *
         *    \f[ \begin{bmatrix} 10 & 1.2x_1^2-6X_1 \\ 1.2x_2^2-10x_2 & 10 \\ \end{bmatrix}
         *    \begin{bmatrix} x_1 \\ x_2 \\ \end{bmatrix} =
         *    \begin{bmatrix} 0.4 -10x_1   -0.4x_2^3+5x_2^2 \\ 0.15-0.4x_1^3+3x_1^2  -10x_2 \\ \end{bmatrix} \f]
         *
         * \code{.cpp}
         * // Inputs are NLA_Solver_Interface_Proxy( Number of Dofs,
         * //                                        Number of elements,
         * //                                        Dummy,
         * //                                        Dummy,
         * //                                        Residual function pointer,
         * //                                        Jacobian function pointer,
         * //                                        Topology function pointer );
         * Solver_Interface * tSolverInput = new NLA_Solver_Interface_Proxy( 2, 1, 1, 1, test_residual1, test_jacobian1, test_topo1 );
         * \endcode
         */
        Solver_Interface * tSolverInput = new NLA_Solver_Interface_Proxy( 2, 1, 1, 1, test_residual1, test_jacobian1, test_topo1 );

        dla::Linear_Solver_Manager * tLinSolManager = new dla::Linear_Solver_Manager();
        /*!
         * Create nonlinear problem class
         *
         * \code{.cpp}
         * Nonlinear_Problem * tNonlinearProblem = new Nonlinear_Problem( tSolverInput );
         * \endcode
         */
        Nonlinear_Problem * tNonlinearProblem = new Nonlinear_Problem( tSolverInput );

        /*!
         * Create nonlinear solver factory. Build nonlinear solver.
         *
         * \code{.cpp}
         * Nonlinear_Solver_Factory tNonlinFactory;
         * std::shared_ptr< Nonlinear_Solver > tNonLinSolver = tNonlinFactory.create_nonlinear_solver( NonlinearSolverType::NEWTON_SOLVER );
         * \endcode
         */
        Nonlinear_Solver_Factory tNonlinFactory;
        std::shared_ptr< Nonlinear_Solver > tNonLinSolver = tNonlinFactory.create_nonlinear_solver( NonlinearSolverType::NEWTON_SOLVER );
        //std::shared_ptr< Nonlinear_Solver > tNonLinSolver = tNonlinFactory.create_nonlinear_solver( tSolverInput, NonlinearSolverType::NEWTON_SOLVER );
        //tNonLinSolver->set_nonlinear_problem( tNonlinearProblem );

        tNonLinSolver->set_linear_solvers( tLinSolManager );
        /*!
         * Set nonlinear solver parameters
         *
         * \code{.cpp}
         * tNonLinSolver->set_param("NLA_max_iter")   = 10;
         * tNonLinSolver->set_param("NLA_hard_break") = false;
         * tNonLinSolver->set_param("NLA_max_lin_solver_restarts") = 2;
         * \endcode
         */
        tNonLinSolver->set_param("NLA_max_iter")   = 10;
        tNonLinSolver->set_param("NLA_hard_break") = false;
        tNonLinSolver->set_param("NLA_max_lin_solver_restarts") = 2;
        tNonLinSolver->set_param("NLA_rebuild_jacobian") = true;

        /*!
         * Build linear solver factory and linear solvers.
         *
         * \code{.cpp}
         * dla::Solver_Factory  tSolFactory;
         * std::shared_ptr< dla::Linear_Solver > tLinSolver1 = tSolFactory.create_solver( SolverType::AZTEC_IMPL );
         * std::shared_ptr< dla::Linear_Solver > tLinSolver2 = tSolFactory.create_solver( SolverType::AZTEC_IMPL );
         * \endcode
         */
        dla::Solver_Factory  tSolFactory;
        std::shared_ptr< dla::Linear_Solver > tLinSolver1 = tSolFactory.create_solver( SolverType::AZTEC_IMPL );
        std::shared_ptr< dla::Linear_Solver > tLinSolver2 = tSolFactory.create_solver( SolverType::AZTEC_IMPL );

        /*!
         * Set linear solver options
         *
         * \code{.cpp}
         * tLinSolver2->set_param("AZ_solver") = AZ_gmres;
         * tLinSolver2->set_param("AZ_precond") = AZ_dom_decomp;
         * \endcode
         */
        tLinSolver1->set_param("AZ_diagnostics") = AZ_none;
        tLinSolver1->set_param("AZ_output") = AZ_none;
        tLinSolver2->set_param("AZ_solver") = AZ_gmres;
        tLinSolver2->set_param("AZ_precond") = AZ_dom_decomp;

        /*!
         * Set linear solver to linear solver manager
         *
         * \code{.cpp}
         * tNonLinSolver->set_linear_solver( 0, tLinSolver1 );
         * tNonLinSolver->set_linear_solver( 1, tLinSolver2 );
         * \endcode
         */
        tNonLinSolver->set_linear_solver( 0, tLinSolver1 );
        tNonLinSolver->set_linear_solver( 1, tLinSolver2 );

        /*!
         * <b> Step 2: Solve nonlinear system </b>
         */

        /*!
         * Solve nonlinear system, passing in the nonlinear problem
         *
         * \code{.cpp}
         * tNonLinSolver->solver_nonlinear_system( tNonlinearProblem );
         * \endcode
         */
        tNonLinSolver->solver_nonlinear_system( tNonlinearProblem );

        /*!
         * Get Solution
         *
         * \code{.cpp}
         * tNonLinSolver->extract_my_values( 2, tGlobalIndExtract, 0, tMyValues);
         * \endcode
         */
        Matrix< DDSMat > tGlobalIndExtract( 2, 1, 0);
        tGlobalIndExtract( 1, 0 ) = 1;
        Matrix< DDRMat > tMyValues;

        tNonLinSolver->extract_my_values( 2, tGlobalIndExtract, 0, tMyValues);

        CHECK( equal_to( tMyValues( 0, 0 ), 0.04011965, 1.0e+08 ) );
        CHECK( equal_to( tMyValues( 1, 0 ), 0.0154803, 1.0e+08 ) );
        }
    }

    TEST_CASE("Newton Solver Test 2","[NLA],[NLA_Test2]")
    {
        if ( par_size() == 1 )
        {
        moris::sint tNumDofsInXandY= 200;
        moris::uint tNumDofs = (moris::uint)(tNumDofsInXandY*tNumDofsInXandY);
        moris::uint tNumElements = tNumDofs;

        /*!
         * <b> Step 1: Create proxy interface and nonlinear solver </b>
         */

        /*!
         * Build linear solver interface. For testing we use the well known, Bratu problem. <br>
         * Bratu, G. (1914). "Sur les équations intégrales non linéaires". Bulletin de la S. M. F. tome 42: 113–142 <br>
         * Mohsen, A. (2014). "A simple solution of the Bratu problem". Computer and Mathematics with Applications. 67: 26–33
         *
         *
         *
         *  The Bratu problem is used as a solid fuel ignition (SFI) problem. This problem is modeled by the partial differential equation
         *
         *  \f[ \Delta u - \lambda e^u = 0 \qquad on \quad \Omega: 0< x,y < 1 \f]
         *
         *  with boundary conditions:
         *
         *  \f[ u = 0 \quad on \quad \delta \Omega\f]
         *
         * \code{.cpp}
         * // Inputs are NLA_Solver_Interface_Proxy( Number of Dofs,
         * //                                        Number of elements,
         * //                                        Number nodes in X,
         * //                                        Number nodes in Y,
         * //                                        Residual function pointer,
         * //                                        Jacobian function pointer,
         * //                                        Topology function pointer );
         * Solver_Interface * tSolverInput = new NLA_Solver_Interface_Proxy( tNumDofs, tNumElements, tNumDofsInXandY, tNumDofsInXandY, test_residual_bratu, test_jacobian_bratu, test_topo_bratu );
         * \endcode
         */
        Solver_Interface * tSolverInput = new NLA_Solver_Interface_Proxy( tNumDofs, tNumElements, tNumDofsInXandY, tNumDofsInXandY, test_residual_bratu, test_jacobian_bratu, test_topo_bratu );

        /*!
         * Build linear solver manager
         *
         * \code{.cpp}
         * dla::Linear_Solver_Manager * tLinSolManager = new dla::Linear_Solver_Manager();
         * \endcode
         */
        dla::Linear_Solver_Manager * tLinSolManager = new dla::Linear_Solver_Manager();

        /*!
         * Create nonlinear problem class
         *
         * \code{.cpp}
         * Nonlinear_Problem * tNonlinearProblem = new Nonlinear_Problem( tSolverInput );
         * \endcode
         */
        Nonlinear_Problem * tNonlinearProblem = new Nonlinear_Problem( tSolverInput );

//        moris::sint tN = 10;
//        moris::real lambda = 2;
//        moris::real hx     = 1.0/(tN-1);
//        moris::real hy     = 1.0/(tN-1);
//        moris::real temp1 = lambda/(lambda + 1.0);
//
//        for ( moris::sint j = 0; j < tN; j++ )
//        {
//            moris::real temp = (real)( std::min( j,tN-j-1 ) )*hy;
//
//            for ( moris::sint i = 0; i < tN; i++ )
//            {
//                if (i == 0 || j == 0 || i == tN-1 || j == tN-1)
//                {
//                    Matrix< DDSMat > tRow( 1, 1, (j*tN)+i );
//                    Matrix< DDRMat > tVal( 1, 1, 0.0 );
//
//                    tNonlinearProblem->mVectorFullSol->sum_into_global_values( 1, tRow, tVal );
//                }
//                else
//                {
//                    Matrix< DDSMat > tRow( 1, 1, (j*tN)+i );
//
//                    moris::real Value1 = temp1*std::sqrt(std::min( (real)(std::min( i,tN-i-1 ))*hx, temp) );
//                    Matrix< DDRMat > tVal( 1, 1, Value1 );
//
//                    tNonlinearProblem->mVectorFullSol->sum_into_global_values( 1, tRow, tVal );
//                }
//            }
//        }
//        tNonlinearProblem->mVectorFullSol->vector_global_asembly();
//
//

        /*!
         * Create nonlinear solver factory. Build nonlinear solver.
         *
         * \code{.cpp}
         * Nonlinear_Solver_Factory tNonlinFactory;
         * std::shared_ptr< Nonlinear_Solver > tNonLinSolver = tNonlinFactory.create_nonlinear_solver( NonlinearSolverType::NEWTON_SOLVER );
         * \endcode
         */
        Nonlinear_Solver_Factory tNonlinFactory;
        std::shared_ptr< Nonlinear_Solver > tNonLinSolver = tNonlinFactory.create_nonlinear_solver( NonlinearSolverType::NEWTON_SOLVER );

        /*!
         * Assign linear solver manager to nonlinear solver
         *
         * \code{.cpp}
         * NonLinSolver->set_linear_solvers( tLinSolManager );
         * \endcode
         */
        tNonLinSolver->set_linear_solvers( tLinSolManager );
        /*!
         * Set nonlinear solver parameters
         *
         * \code{.cpp}
         * tNonLinSolver->set_param("NLA_max_iter")   = 10;
         * tNonLinSolver->set_param("NLA_hard_break") = false;
         * tNonLinSolver->set_param("NLA_max_lin_solver_restarts") = 2;
         * tNonLinSolver->set_param("NLA_rebuild_jacobian") = false;
         * tNonLinSolver->set_param("NLA_restart")    = 2;
         * \endcode
         */
        tNonLinSolver->set_param("NLA_max_iter")   = 20;
        //tNonLinSolver->set_param("NLA_restart")    = 2;
        tNonLinSolver->set_param("NLA_hard_break") = false;
        tNonLinSolver->set_param("NLA_max_lin_solver_restarts") = 2;
        //tNonLinSolver->set_param("NLA_rebuild_jacobian") = false;

        /*!
         * Build linear solver factory and linear solvers.
         *
         * \code{.cpp}
         * dla::Solver_Factory  tSolFactory;
         * std::shared_ptr< dla::Linear_Solver > tLinSolver1 = tSolFactory.create_solver( SolverType::AZTEC_IMPL );
         * std::shared_ptr< dla::Linear_Solver > tLinSolver2 = tSolFactory.create_solver( SolverType::AZTEC_IMPL );
         * \endcode
         */
        dla::Solver_Factory  tSolFactory;
        std::shared_ptr< dla::Linear_Solver > tLinSolver1 = tSolFactory.create_solver( SolverType::AZTEC_IMPL );
        std::shared_ptr< dla::Linear_Solver > tLinSolver2 = tSolFactory.create_solver( SolverType::AZTEC_IMPL );

        /*!
         * Set linear solver options
         *
         * \code{.cpp}
         * tLinSolver2->set_param("AZ_solver") = AZ_gmres;
         * tLinSolver2->set_param("AZ_precond") = AZ_dom_decomp;
         * tLinSolver1->set_param("AZ_pre_calc") = AZ_reuse;
         * tLinSolver1->set_param("AZ_keep_info") = 1;
         * \endcode
         */
        tLinSolver1->set_param("AZ_diagnostics") = AZ_none;
        tLinSolver1->set_param("AZ_output") = AZ_none;
        tLinSolver1->set_param("AZ_keep_info") = 1;
        //tLinSolver1->set_param("AZ_pre_calc") = AZ_reuse;
        tLinSolver1->set_param("AZ_graph_fill") = 5;

        tLinSolver1->set_param("Use_ML_Prec") = true;
        //tLinSolver1->set_param("ML_reuse") = true;

        /*!
         * Set linear solver to linear solver manager
         *
         * \code{.cpp}
         * tNonLinSolver->set_linear_solver( 0, tLinSolver1 );
         * tNonLinSolver->set_linear_solver( 1, tLinSolver2 );
         * \endcode
         */
        tNonLinSolver->set_linear_solver( 0, tLinSolver1 );
        tNonLinSolver->set_linear_solver( 1, tLinSolver2 );

        /*!
         * Solve nonlinear system, passing in the nonlinear problem
         *
         * \code{.cpp}
         * tNonLinSolver->solver_nonlinear_system( tNonlinearProblem );
         * \endcode
         */

        tNonLinSolver->solver_nonlinear_system( tNonlinearProblem );

        Matrix< DDSMat > tGlobalIndExtract( 2, 1, 0);
        tGlobalIndExtract( 1, 0 ) = 1;
        Matrix< DDRMat > tMyValues;

        tNonlinearProblem->extract_my_values( 2, tGlobalIndExtract, 0, tMyValues);

        std::cout<<tMyValues(0,0)<<std::endl;
        std::cout<<tMyValues(1,0)<<std::endl;
//        CHECK( equal_to( tMyValues( 0, 0 ), 0.04011965, 1.0e+08 ) );
//        CHECK( equal_to( tMyValues( 1, 0 ), 0.0154803, 1.0e+08 ) );
        }
    }
}
}

