/*
 * cl_HMR.hpp
 *
 *  Created on: May 5, 2018
 *      Author: messe
 */

#ifndef SRC_HMR_CL_HMR_HPP_
#define SRC_HMR_CL_HMR_HPP_

#include "cl_Cell.hpp" //CON/src

#include "cl_HMR_Factory.hpp" //HMR/src
#include "cl_HMR_Lagrange_Mesh.hpp" //HMR/src
#include "cl_HMR_Interface.hpp" //HMR/src
#include "cl_HMR_Parameters.hpp" //HMR/src
#include "cl_HMR_T_Matrix.hpp" //HMR/src
#include "cl_HMR_Field.hpp" //HMR/src
namespace moris
{
    namespace hmr
    {
// -----------------------------------------------------------------------------

        /**
         * \brief the main class of HMR
         */
        class HMR
        {
        public :
            //! object containing user settings
            const Parameters *          mParameters;

            //! pointer to background mesh
            Background_Mesh_Base*       mBackgroundMesh;

            //! cell of pointers to B-Spline meshes
            Cell< BSpline_Mesh_Base* >  mBSplineMeshes;

            //! cell of pointers to Lagrange meshes
            Cell< Lagrange_Mesh_Base* > mLagrangeMeshes;

            //! calculation object that calculates the T-Matrices
            Cell< T_Matrix* >           mTMatrix;

            //! communication table for this mesh. Created during finalize.
            Mat< uint >                 mCommunicationTable;

            //! cointainer with field objects
            Cell<  Field* >             mFields;
// -----------------------------------------------------------------------------
        public :
// -----------------------------------------------------------------------------

            /**
             * the  HMR constructor
             *
             * @param[in] aParameters  ref to container of user defined settings
             */
            HMR ( const Parameters * aParameters ) ;

// -----------------------------------------------------------------------------

            /**
             * default destructor of HMR
             */
            ~HMR ( ) ;


// -----------------------------------------------------------------------------

            /**
             *  this function updates the meshes after an refinement step
             */
            void
            update_meshes();

// -----------------------------------------------------------------------------

            /**
             * returns the number of ( active ) elements on this proc
             */
            auto
            get_number_of_elements_on_proc()
                -> decltype( mBackgroundMesh->get_number_of_active_elements_on_proc() )
            {
                return mBackgroundMesh->get_number_of_active_elements_on_proc();
            }

// -----------------------------------------------------------------------------

             /**
              * returns the number of dimensions in space
              */
             auto
             get_number_of_dimensions() const
                 -> decltype( mParameters->get_number_of_dimensions() )
             {
                 return mParameters->get_number_of_dimensions();
             }

// -----------------------------------------------------------------------------

             /**
              * returns the number of Lagrange meshes
              */
             uint
             get_number_of_lagrange_meshes()
             {
                 return mLagrangeMeshes.size();
             }

// -----------------------------------------------------------------------------

             /**
              * returns the pointer to a Lagrange mesh, needed by interface
              * constructor
              */
             Lagrange_Mesh_Base*
             get_lagrange_mesh_by_index( const uint& aIndex )
             {
                 return mLagrangeMeshes( aIndex );
             }

// -----------------------------------------------------------------------------

             Interface
             create_interface();

//-----------------------------------------------------------------------------

             /**
              * popules the member variables of the relevant nodes
              * with their T-Matrices
              */
             void
             finalize();

//------------------------------------------------------------------------------
             /**
              * provides a moris::Mat<uint> containing the IDs this mesh has
              * to communicate with
              */
             Mat< uint >
             get_communication_table() const
             {
                 return mCommunicationTable;
             }

// -----------------------------------------------------------------------------

             /**
              * Temporary function to add field data to the mesh object.
              * Needed for testing.
              */
             void
             add_field(
                     const std::string & aLabel,
                     const uint        & aOrder,
                     const Mat<real>   & aValues );

// -----------------------------------------------------------------------------

             /**
              * experimental funciton
              */
             void
             flag_element( const uint & aIndex )
             {
                 mBackgroundMesh->get_element( aIndex )->put_on_queue();
             }

// -----------------------------------------------------------------------------

             /**
              * experimental funciton
              */

             void
             perform_refinement()
             {
                 mBackgroundMesh->perform_refinement();
                 this->update_meshes();
             }

// -----------------------------------------------------------------------------
             void
             save_to_exodus( const uint & aOrder, const std::string & aPath );

// -----------------------------------------------------------------------------
        private:
// -----------------------------------------------------------------------------

            /**
             * this function initializes the Lagrange and B-Spline Meshes
             * is complete
             *
             * @return void
             */
            void
            create_meshes();
// -----------------------------------------------------------------------------
            /**
             * this function deletes the Lagrange and B-Spline meshes
             * the function is called before create_meshes
             */
            void
            delete_meshes();
// -----------------------------------------------------------------------------

            /**
             * initializes the T-Matrix objects
             */
            void
            init_t_matrices();

// -----------------------------------------------------------------------------

            /**
             * deletes the T-Matrix objects
             */
            void
            delete_t_matrices();

// -----------------------------------------------------------------------------

            /**
             * This function checks if t-matrix flags on the neighbor procs
             * have been set. If so, it makes sure that basis owned by current
             * proc are created
             */
            void
            synchronize_t_matrix_flags();

// -----------------------------------------------------------------------------

            /**
             * creates the communication table and writes it into
             * mCommunicationTable. Must be called after mesh has been finalized.
             */
            void
            create_communication_table();

// -----------------------------------------------------------------------------
        }; /* HMR */

    } /* namespace hmr */
} /* namespace moris */

#endif /* SRC_HMR_CL_HMR_HPP_ */
