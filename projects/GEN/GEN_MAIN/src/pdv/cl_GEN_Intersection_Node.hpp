#ifndef MORIS_CL_GEN_INTERSECTION_NODE_HPP
#define MORIS_CL_GEN_INTERSECTION_NODE_HPP

#include "cl_GEN_Child_Node.hpp"

namespace moris
{
    namespace ge
    {
        class Intersection_Node : public Child_Node
        {

        private:
            std::shared_ptr<Geometry> mInterfaceGeometry;
            Cell<std::shared_ptr<Intersection_Node>> mNodeDependencies;
            Matrix<DDRMat> mCoordinates;
            uint mStartingPdvIndex;
            bool mPdvIndexSet = false;

        public:
            /**
             * Constructor
             *
             * @param aParentNodeIndices Node indices of the parent of this node
             * @param aParentNodeCoordinates Coordinates of the parent of this node
             * @param aInterfaceGeometry Geometry that intersects the parent to create this child
             * @param aIsocontourThreshold Threshold for determining the intersection location of the child node
             */
            Intersection_Node(Matrix<DDUMat>            aParentNodeIndices,
                              Cell<Matrix<DDRMat>>      aParentNodeCoordinates,
                              std::shared_ptr<Geometry> aInterfaceGeometry,
                              real                      aIsocontourThreshold);

            /**
             * Sets the starting index to be able to use the intersection coordinates of this node as PDVs
             *
             * @param aStartingPdvIndex The global index of the first PDV on the host
             */
            void set_starting_pdv_index(uint aStartingPdvIndex);

            /**
             * Get the starting global index for the intersection coordinate PDVs
             *
             * @return The global index of the first PDV on the host
             */
            uint get_starting_pdv_index();

            /**
             * Get the value of a coordinate of this node
             *
             * @param aCoordinateIndex index of the coordinate, obtained from casting the related PDV coordinate type
             * @return Coordinate value
             */
            real get_coordinate_value(uint aCoordinateIndex);

            /**
             * Gets all of the sensitivity vectors for each coordinate
             *
             * @param aSensitivities Sensitivity matrix to be filled
             */
            void get_all_sensitivities(Matrix<DDRMat>& aSensitivities);

        };
    }
}

#endif //MORIS_CL_GEN_INTERSECTION_NODE_HPP
