/*
 * cl_HMR_Database.hpp
 *
 *  Created on: Oct 1, 2018
 *      Author: messe
 */

#ifndef PROJECTS_HMR_SRC_CL_HMR_DATABASE_HPP_
#define PROJECTS_HMR_SRC_CL_HMR_DATABASE_HPP_

#include <memory> // <-- database is always a shared pointer, so we need std::memory
#include "cl_Cell.hpp"             //CON/src
#include "cl_MTK_Field.hpp"        //HMR/src
#include "cl_HMR_Factory.hpp"        //HMR/src
#include "cl_HMR_Lagrange_Mesh.hpp"  //HMR/src
#include "cl_HMR_Parameters.hpp"     //HMR/src
#include "cl_HMR_T_Matrix.hpp"       //HMR/src

namespace moris
{
    namespace hmr
    {
// -----------------------------------------------------------------------------

        class Field;

// -----------------------------------------------------------------------------
        class Database  : public std::enable_shared_from_this< Database >
        {
            //! object containing user settings
            Parameters *                mParameters;

            //! pointer to background mesh
            Background_Mesh_Base*       mBackgroundMesh;

            //! cell of pointers to B-Spline meshes
            Cell< BSpline_Mesh_Base* >  mBSplineMeshes;

            //! cell of pointers to Lagrange meshes
            Cell< Lagrange_Mesh_Base* > mLagrangeMeshes;

            //! calculation object that calculates the T-Matrices
            Cell< T_Matrix* >           mTMatrix;

            //! communication table for this mesh. Created during finalize.
            Matrix< IdMat >             mCommunicationTable;


            //! flag telling if parameter pointer is suppposed to be deleted on destruction
            bool                        mDeleteParametersOnDestruction = false;

// -----------------------------------------------------------------------------
        public:
// -----------------------------------------------------------------------------

            /**
             * Database constructor
             */
            Database( Parameters * aParameters );

// -----------------------------------------------------------------------------

            /**
             * alternative constructor which loads a mesh from a h5 file
             */
            Database( const std::string & aPath );

// -----------------------------------------------------------------------------

            /**
             * destructor
             */
            ~Database();

// -----------------------------------------------------------------------------

            void
            load_pattern_from_hdf5_file(
                    const uint        & aPattern,
                    const std::string & aPath );

// -----------------------------------------------------------------------------

            /**
             * sets the flag that the parameter object must be deleted
             * by the destructor
             */
            void
            set_parameter_owning_flag();

// -----------------------------------------------------------------------------

            /**
             * creates a union of two patterns
             */
            void
            unite_patterns(
                    const uint & aSourceA,
                    const uint & aSourceB,
                    const uint & aTarget );

// -----------------------------------------------------------------------------

            /**
             * copies a source pattern to a target pattern
             */
            void
            copy_pattern(
                    const uint & aSource,
                    const uint & aTarget );
// -----------------------------------------------------------------------------

            /**
             * runs the refinement scheme
             */
            void
            perform_refinement( const bool aResetPattern = true );

// -----------------------------------------------------------------------------

            /**
             * aTarget must be a refined variant of aSource
             */
            void
            interpolate_field(
                    const uint                   & aSourcePattern,
                    const std::shared_ptr<Field>   aSource,
                    const uint                   & aTargetPattern,
                    std::shared_ptr<Field>         aTarget );

// -----------------------------------------------------------------------------

            /**
             * Returns the pointer to a T-Matrix object.
             * Needed by Field constructor.
             */
            T_Matrix *
            get_t_matrix( const uint & aLagrangeMeshIndex );

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

            /**
             * returns the pointer to a Bspline mesh, needed by interface
             * constructor
             */
            BSpline_Mesh_Base*
            get_bspline_mesh_by_index( const uint& aIndex )
            {
                return mBSplineMeshes( aIndex );
            }

// -----------------------------------------------------------------------------

            Background_Mesh_Base *
            get_background_mesh();

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
            get_number_of_lagrange_meshes() const
            {
                return mLagrangeMeshes.size();
            }

// -----------------------------------------------------------------------------

            /**
             * returns the number of Bsploine meshes
             */
            uint
            get_number_of_bspline_meshes() const
            {
                return mBSplineMeshes.size();
            }

// -----------------------------------------------------------------------------

            /**
             * set active pattern of background mesh
             */
            void
            set_activation_pattern( const uint & aPattern )
            {
                mBackgroundMesh->set_activation_pattern( aPattern );
            }

// -----------------------------------------------------------------------------

            /**
             * returns the active pattern
             */
            auto
            get_activation_pattern() const
                -> decltype( mBackgroundMesh->get_activation_pattern() )
            {
                return  mBackgroundMesh->get_activation_pattern();
            }

// -----------------------------------------------------------------------------

            /**
             * function needed for tests etc
             */
            void
            flag_element( const uint & aIndex )
            {
                mBackgroundMesh->get_element( aIndex )->put_on_refinement_queue();
            }

// -----------------------------------------------------------------------------

            /**
             * returns the communication table that is needed by FEM
             */
            const Matrix< IdMat > &
            get_communication_table() const
            {
                return mCommunicationTable;
            }

// -----------------------------------------------------------------------------

            /**
             * return pointer to parameter object ( const version )
             */
            Parameters *
            get_parameters()
            {
                return mParameters;
            }

// -----------------------------------------------------------------------------

            /**
             * return pointer to parameter object ( const version )
             */
            const Parameters *
            get_parameters() const
            {
                return mParameters;
            }

// -----------------------------------------------------------------------------

            /**
             * populates the member variables of the relevant nodes
             * with their T-Matrices
             */
            void
            finalize();

// -----------------------------------------------------------------------------

            /**
             * needed for exodus output of cubic meshes, called by finalize
             */
            void
            add_extra_refinement_step_for_exodus();

// -----------------------------------------------------------------------------

            /**
             *  this function updates the meshes after an refinement step
             */
            void
            update_meshes();

// -----------------------------------------------------------------------------

            /**
             *  test that all relevant entitiy IDs are set
             */
            void
            check_entity_ids();

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
             * creates the communication table and writes it into
             * mCommunicationTable. Must be called after mesh has been finalized.
             */
            void
            create_communication_table();

// -----------------------------------------------------------------------------

            /**
             * creates a union mesh of the input and the output patterns
             */
            void
            create_union_pattern()
            {
                this->unite_patterns(
                        mParameters->get_input_pattern(),
                        mParameters->get_output_pattern(),
                        mParameters->get_union_pattern() );
            }

        };
    } /* namespace hmr */
} /* namespace moris */


#endif /* PROJECTS_HMR_SRC_CL_HMR_DATABASE_HPP_ */