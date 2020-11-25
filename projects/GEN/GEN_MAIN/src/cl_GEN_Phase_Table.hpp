#ifndef MORIS_CL_GEN_PHASE_TABLE_HPP_
#define MORIS_CL_GEN_PHASE_TABLE_HPP_

#include "cl_Matrix.hpp"

namespace moris
{
    namespace ge
    {
        class Phase_Table
        {

        private:
            uint mNumGeometries;           // Total number of geometries
            uint mNumPhases = 0;           // Number of bulk phases
            Matrix<DDUMat> mBulkPhases;    // Geometric sign to bulk phase
            Cell<std::string> mPhaseNames; // Phase names
            
        public:

            /**
             * Constructor for using a given phase table with the standard 2^n structure.
             * 
             * @param aNumGeometries Number of geometries
             * @param aBulkPhases Geometric index to bulk phase map
             * @param aPhaseNames (optional) Phase names
             */
            Phase_Table(
                    uint              aNumGeometries,
                    Matrix<DDUMat>    aBulkPhases,
                    Cell<std::string> aPhaseNames = {});

            /**
             * Create a phase table with 2^n structure using a number of bulk phases. Delegating constructor.
             *
             * @param aNumGeometries Number of geometries
             * @param aPhaseNames (optional) Phase names
             */
            Phase_Table(
                    uint              aNumGeometries,
                    Cell<std::string> aPhaseNames = {});

            /**
             * Get the number of phases
             *
             * @return Number of phases
             */
            uint get_num_phases();

            /**
             * Get phase index based on entity phase info
             *
             * @param aEntityPhaseInfo Phase info
             * @return Phase index
             */
            moris_index get_phase_index(Matrix<IndexMat> const &aEntityPhaseInfo);

            /**
             * Gets the name of a requested phase
             *
             * @param aPhaseIndex The index of the requested phase
             * @return Phase name
             */
            std::string get_phase_name(uint aPhaseIndex);

            /*!
            * Print information for setting up phase table
            */
            void print();

        private:

            /**
             * Set all of the phases to have default names (p_i)
             */
            void set_default_phase_names();

        };
    }
}

#endif /* MORIS_CL_GEN_PHASE_TABLE_HPP_ */
