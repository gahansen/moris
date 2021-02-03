#include <iostream>
#include <cstdio>

// HD5 c-interface
#include "hdf5.h"

#include "fn_save_matrix_to_binary_file.hpp"

#include "cl_Map.hpp"
#include "cl_Matrix.hpp"
#include "cl_MTK_Field.hpp"
#include "linalg_typedefs.hpp"

#include "HDF5_Tools.hpp"

#include "cl_MTK_Mesh.hpp"
#include "cl_MTK_Mesh_Manager.hpp"
#include "cl_MTK_Interpolation_Mesh.hpp"
#include "cl_MTK_Integration_Mesh.hpp"

#include "fn_dot.hpp"

namespace moris
{
    namespace mtk
    {

        //------------------------------------------------------------------------------

        Field::~Field()
        {

        }

        void Field::evaluate_node_values()
        {
            Interpolation_Mesh* tInterpolationMesh =
                    mMeshManager->get_interpolation_mesh( mMeshIndex );

            // get number of nodes on block
            uint tNumberOfNodes= tInterpolationMesh->get_num_nodes();

            // set size of node values
            mNodalValues.set_size( tNumberOfNodes, 1 );

            for( uint Ik = 0; Ik < tNumberOfNodes; ++Ik )
            {
                // get pointer to node
                auto tNode = &tInterpolationMesh->get_mtk_vertex( Ik );

                // get PDOFs from node
                auto tBSplines = tNode->
                        get_interpolation( mDiscretizationMeshIndex )->
                        get_coefficients();

                // get T-Matrix
                const Matrix< DDRMat > & tTMatrix = *tNode->
                        get_interpolation( mDiscretizationMeshIndex )->
                        get_weights();

                // get number of coefficients
                uint tNumberOfCoeffs = tTMatrix.length();

                MORIS_ASSERT( tNumberOfCoeffs > 0, "No coefficients defined for node" ) ;

                // fill coeffs vector
                Matrix< DDRMat > tCoeffs( tNumberOfCoeffs, 1 );
                for( uint Ii = 0; Ii < tNumberOfCoeffs; ++Ii )
                {
                    tCoeffs( Ii ) = mCoefficients( tBSplines( Ii )->get_index() );
                }

                // write value into solution
                mNodalValues( Ik ) = moris::dot( tTMatrix, tCoeffs );
            }
        }

        //------------------------------------------------------------------------------

        void Field::save_field_to_hdf5(
                const std::string & aFilePath,
                const bool          aCreateNewFile )
        {
            // test if file exists
            std::string tFilePath = make_path_parallel( aFilePath );

            // test if file exists
            std::ifstream tFile( tFilePath );
            bool tFileExists;
            if( tFile )
            {
                tFileExists = true;
            }
            else
            {
                tFileExists = false;
            }

            tFile.close();

            // delete file if it exists and user does not want to keep it
            if( aCreateNewFile && tFileExists )
            {
                std::remove( tFilePath.c_str() );
                tFileExists = false;
            }

            hid_t tFileID;

            if( tFileExists )
            {
                tFileID = open_hdf5_file( aFilePath );
            }
            else
            {
                tFileID = create_hdf5_file( aFilePath );
            }

            herr_t tStatus;

            save_matrix_to_hdf5_file( tFileID,
                    this->get_label(),
                    this->get_coefficients(),
                    tStatus );

            // close file
            tStatus = close_hdf5_file( tFileID );
        }

        //------------------------------------------------------------------------------

        void Field::save_node_values_to_hdf5(
                const std::string & aFilePath,
                const bool          aCreateNewFile )
        {
            // test if file exists
            std::string tFilePath = make_path_parallel( aFilePath );

            // test if file exists
            std::ifstream tFile( tFilePath );
            bool tFileExists;
            if( tFile )
            {
                tFileExists = true;
            }
            else
            {
                tFileExists = false;
            }

            tFile.close();

            // delete file if it exists and user does not want to keep it
            if( aCreateNewFile && tFileExists )
            {
                std::remove( tFilePath.c_str() );
                tFileExists = false;
            }

            hid_t tFileID;

            if( tFileExists )
            {
                tFileID = open_hdf5_file( aFilePath );
            }
            else
            {
                tFileID = create_hdf5_file( aFilePath );
            }

            herr_t tStatus;

            save_matrix_to_hdf5_file( tFileID,
                    this->get_label(),
                    this->get_node_values(),
                    tStatus );

            // close file
            tStatus = close_hdf5_file( tFileID );
        }

        //------------------------------------------------------------------------------

        void Field::load_field_from_hdf5(
                const std::string & aFilePath,
                const uint          aBSplineOrder )
        {
            hid_t tFile    = open_hdf5_file( aFilePath );
            herr_t tStatus = 0;
            load_matrix_from_hdf5_file( tFile,
                    this->get_label(),
                    this->get_coefficients(),
                    tStatus );

            tStatus = close_hdf5_file( tFile );
        }

        //------------------------------------------------------------------------------

        void Field::save_node_values_to_binary( const std::string & aFilePath )
        {
            // make path parallel
            std::string tFilePath = parallelize_path( aFilePath );

            save_matrix_to_binary_file( this->get_node_values(), tFilePath );
        }

        //------------------------------------------------------------------------------

        void Field::save_bspline_coeffs_to_binary( const std::string & aFilePath )
        {
            // make path parallel
            std::string tFilePath = parallelize_path( aFilePath );

            save_matrix_to_binary_file( this->get_coefficients(), tFilePath );
        }

        //------------------------------------------------------------------------------
    } /* namespace hmr */
} /* namespace moris */
