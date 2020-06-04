#include "cl_GEN_Pdv_Host.hpp"
#include "cl_GEN_Pdv_Value.hpp"
#include "cl_GEN_Pdv_Property.hpp"
#include "cl_GEN_Pdv_Intersection.hpp"

namespace moris
{
    namespace ge
    {
        
        //--------------------------------------------------------------------------------------------------------------
        
        Pdv_Host::Pdv_Host(uint aNodeIndex, const Cell<PDV_Type>& aPdvTypes, uint aGlobalIndex)
        : mNodeIndex(aNodeIndex),
          mPdvs(aPdvTypes.size(), nullptr),
          mGlobalPdvIndices(aPdvTypes.size(), 1)
        {
            for (uint tPdvIndex = 0; tPdvIndex < aPdvTypes.size(); tPdvIndex++)
            {
                // Map from PDV type to local index
                mPdvTypeMap[aPdvTypes(tPdvIndex)] = tPdvIndex;

                // local index to global index
                mGlobalPdvIndices(tPdvIndex) = aGlobalIndex++;
            }
        }

        //--------------------------------------------------------------------------------------------------------------
        
        Pdv_Host::~Pdv_Host()
        {
        }

        //--------------------------------------------------------------------------------------------------------------
        
        uint Pdv_Host::add_pdv_types(const Cell<PDV_Type>& aPdvTypes, uint aGlobalIndex)
        {
            // Check for existing PDVs and add new ones to map
            uint tOriginalPdvs = mPdvTypeMap.size();
            uint tPdvIndex = tOriginalPdvs;
            for (uint tNewPdvIndex = 0; tNewPdvIndex < aPdvTypes.size(); tNewPdvIndex++)
            {
                if (!mPdvTypeMap.key_exists(aPdvTypes(tNewPdvIndex)))
                {
                    mPdvTypeMap[aPdvTypes(tNewPdvIndex)] = tPdvIndex;
                    tPdvIndex++;
                }
            }

            // Extend PDV list and indices
            mPdvs.resize(tPdvIndex);
            mGlobalPdvIndices.resize(tPdvIndex, 1);
            for (uint tNewPdvIndex = 0; tNewPdvIndex < tPdvIndex - tOriginalPdvs; tNewPdvIndex++)
            {
                mGlobalPdvIndices(tOriginalPdvs + tNewPdvIndex) = aGlobalIndex++;
            }

            // Return number of added PDV types
            return tPdvIndex - tOriginalPdvs;
        }

        //--------------------------------------------------------------------------------------------------------------

        void Pdv_Host::create_pdv(PDV_Type aPdvType, real aPdvVal)
        {
            // Check PDV type
            MORIS_ASSERT(mPdvTypeMap.key_exists(aPdvType),
                         "Tried to call Pdv_Host.create_pdv() using pdv value with a PDV type that doesn't exist on this host.");

            // Create a pdv with pdv value
            mPdvs(mPdvTypeMap[aPdvType]) = std::make_shared< Pdv_Value >(aPdvVal);
        }

        //--------------------------------------------------------------------------------------------------------------

        void Pdv_Host::create_pdv(PDV_Type aPdvType, std::shared_ptr<Property> aPropertyPointer)
        {
            // Check PDV type
            MORIS_ASSERT(mPdvTypeMap.key_exists(aPdvType),
                    "Tried to call Pdv_Host.create_pdv() using GEN property with a PDV type that doesn't exist on this host.");

            // Create a pdv with property pointer
            mPdvs(mPdvTypeMap[aPdvType]) = std::make_shared< Pdv_Property >(aPropertyPointer);
        }

        //--------------------------------------------------------------------------------------------------------------

        void Pdv_Host::create_pdv(PDV_Type aPdvType, GEN_Geometry_Object* aIntersection, uint aDimension)
        {
            // Check PDV type
            MORIS_ASSERT(mPdvTypeMap.key_exists(aPdvType),
                         "Tried to call Pdv_Host.create_pdv() using an intersection with a PDV type that doesn't exist on this host.");

            // Create a pdv with an intersection pointer
            mPdvs(mPdvTypeMap[aPdvType]) = std::make_shared<Pdv_Intersection>(aIntersection, aDimension);
        }

        //--------------------------------------------------------------------------------------------------------------

        bool Pdv_Host::is_active_type(PDV_Type aPdvType)
        {
            // Check PDV type
            MORIS_ASSERT(mPdvTypeMap.key_exists(aPdvType),
                    "Tried to call Pdv_Host.is_active_type() with PDV type that doesn't exist on this host.");

            // return if active PDV
            return mPdvs(mPdvTypeMap[aPdvType])->mIsActive;
        }

        //--------------------------------------------------------------------------------------------------------------

        uint Pdv_Host::get_global_index_for_pdv_type(PDV_Type aPdvType)
        {
            // Check PDV type
            MORIS_ASSERT(mPdvTypeMap.key_exists(aPdvType),
                         "Tried to call Pdv_Host.get_global_index_for_pdv_type() with a PDV type that doesn't exist on this host.");

            // Return id from map
            return mGlobalPdvIndices(mPdvTypeMap[aPdvType]);
        }

        //--------------------------------------------------------------------------------------------------------------

        const Matrix<DDUMat>& Pdv_Host::get_all_global_indices()
        {
            return mGlobalPdvIndices;
        }

        //--------------------------------------------------------------------------------------------------------------

        real Pdv_Host::get_pdv_value(PDV_Type aPdvType)
        {
            // Check PDV type
            MORIS_ASSERT(mPdvTypeMap.key_exists(aPdvType),
                         "Tried to call Pdv_Host.get_pdv_value() with a PDV type that doesn't exist on this host.");

            // Return value
            return mPdvs(mPdvTypeMap[aPdvType])->get_value(mNodeIndex, mCoordinates);
        }

        //--------------------------------------------------------------------------------------------------------------

        void Pdv_Host::get_all_sensitivities(Matrix<DDRMat>& aSensitivities)
        {
            aSensitivities.resize(0, aSensitivities.n_cols());
            if (mPdvs.size() > 0)
            {
                uint tActivePdvIndex = 0;
                Matrix<DDRMat> tSensitivities(0, 0);
                for (uint tPdvIndex = 0; tPdvIndex < mPdvs.size(); tPdvIndex++)
                {
                    if (mPdvs(tPdvIndex)->mIsActive)
                    {
                        mPdvs(tPdvIndex)->get_sensitivity(mNodeIndex, mCoordinates, tSensitivities);
                        aSensitivities.resize(tActivePdvIndex + 1, tSensitivities.length());
                        aSensitivities.set_row(tActivePdvIndex++, tSensitivities);
                    }
                }
            }
        }

        //--------------------------------------------------------------------------------------------------------------
        
    } // end ge namepsace
} // end moris namespace

