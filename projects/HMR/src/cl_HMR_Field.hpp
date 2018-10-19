/*
 * cl_HMR_Field.hpp
 *
 *  Created on: Sep 13, 2018
 *      Author: messe
 */

#ifndef PROJECTS_HMR_SRC_CL_HMR_FIELD_HPP_
#define PROJECTS_HMR_SRC_CL_HMR_FIELD_HPP_

#include <memory>

#include "typedefs.hpp"
#include "cl_MTK_Field.hpp"
#include "cl_HMR_Database.hpp"
#include "cl_HMR_Lagrange_Mesh_Base.hpp"

namespace moris
{
    namespace hmr
    {
//------------------------------------------------------------------------------

        class Field : public mtk::Field
        {
            //! pointer to database
            std::shared_ptr< Database > mDatabase;

            //! mesh that holds data
            Lagrange_Mesh_Base * mLagrangeMesh;

            // index of field in mesh
            uint mFieldIndex;

            // parameter for minumum volume refinement
            uint mMinVolumeLevel = 0;

            // parameter for minimun surface refinement
            uint mMinSurfaceLevel = 0;

            // parameter for maximum volume refinement
            uint mMaxVolumeLevel = gMaxNumberOfLevels;

            // parameter for maximum surface refinement
            uint mMaxSurfaceLevel = gMaxNumberOfLevels;

//------------------------------------------------------------------------------
        public :
//------------------------------------------------------------------------------

            Field(  const std::string             & aLabel,
                    std::shared_ptr< mtk::Mesh >    aMesh,
                    std::shared_ptr< Database >     aDatabase,
                    Lagrange_Mesh_Base *            aLagrangeMesh );

//------------------------------------------------------------------------------

            ~Field();

//------------------------------------------------------------------------------

            // parameter copied from input settings
            void
            set_min_surface_level( const uint & aLevel );

//------------------------------------------------------------------------------

            // parameter copied from input settings
            void
            set_min_volume_level( const uint & aLevel );

//------------------------------------------------------------------------------

            // parameter copied from input settings
            void
            set_max_surface_level( const uint & aLevel );

//------------------------------------------------------------------------------

            // parameter copied from input settings
            void
            set_max_volume_level( const uint & aLevel );

//------------------------------------------------------------------------------

            uint
            get_min_surface_level() const;

//------------------------------------------------------------------------------

            // parameter copied from input settings
            uint
            get_min_volume_level() const;

//------------------------------------------------------------------------------

            // parameter copied from input settings
            uint
            get_max_surface_level() const;

//------------------------------------------------------------------------------

            // parameter copied from input settings
            uint
            get_max_volume_level() const;

//------------------------------------------------------------------------------

            const std::string &
            get_label() const;

//------------------------------------------------------------------------------

            void
            set_label( const std::string & aLabel );

//------------------------------------------------------------------------------

            Matrix< DDRMat > &
            get_node_values();

//------------------------------------------------------------------------------

            const Matrix< DDRMat > &
            get_node_values() const;

//------------------------------------------------------------------------------

            Matrix< DDRMat > &
            get_coefficients();
//------------------------------------------------------------------------------

            const Matrix< DDRMat > &
            get_coefficients() const;

//------------------------------------------------------------------------------

            /**
             * sets the pointer of the mesh to another mesh
             * this is needed by the mapper
             */
            void
            change_mesh( Lagrange_Mesh_Base * aMesh, const uint aFieldIndex );

//------------------------------------------------------------------------------

            /**
             * returns the pointer of the underlying mesh
             */
            const Lagrange_Mesh_Base *
            get_mesh() const
            {
                return mLagrangeMesh;
            }

//------------------------------------------------------------------------------

            /**
             * return the field index on the linked mesh
             */
            uint
            get_field_index() const
            {
                return mFieldIndex;
            }

//------------------------------------------------------------------------------

            void
            save_field_to_hdf5( const std::string & aFilePath );

//------------------------------------------------------------------------------

            void
            load_field_from_hdf5( const std::string & aFilePath );

//------------------------------------------------------------------------------

            void
            save_bspline_coeffs_to_binary( const std::string & aFilePath );

//------------------------------------------------------------------------------

            void
            save_node_values_to_binary( const std::string & aFilePath );

//------------------------------------------------------------------------------
        };

//------------------------------------------------------------------------------
    } /* namespace hmr */
} /* namespace moris */



#endif /* PROJECTS_HMR_SRC_CL_HMR_FIELD_HPP_ */
