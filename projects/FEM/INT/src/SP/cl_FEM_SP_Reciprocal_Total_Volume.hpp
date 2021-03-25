/*
 * cl_FEM_SP_Reciprocal_Total_Volume.hpp
 *
 *  Created on: Feb 28, 2020
 *      Author: schmidt
 */

#ifndef PROJECTS_FEM_INT_SRC_CL_FEM_SP_RECIPROCAL_TOTAL_VOLUME_HPP_
#define PROJECTS_FEM_INT_SRC_CL_FEM_SP_RECIPROCAL_TOTAL_VOLUME_HPP_

#include <map>

#include "typedefs.hpp"                     //MRS/COR/src
#include "cl_Cell.hpp"                      //MRS/CON/src

#include "cl_Matrix.hpp"                    //LINALG/src
#include "linalg_typedefs.hpp"              //LINALG/src

#include "cl_FEM_Field_Interpolator.hpp"    //FEM/INT/src
#include "cl_FEM_Constitutive_Model.hpp"    //FEM/INT/src
#include "cl_FEM_Stabilization_Parameter.hpp"     //FEM/INT/src
#include "cl_FEM_Cluster.hpp"     //FEM/INT/src

namespace moris
{
    namespace fem
    {
        //------------------------------------------------------------------------------

        class SP_Reciprocal_Total_Volume : public Stabilization_Parameter
        {

                //------------------------------------------------------------------------------
            private:

                // default tuple for master volume size to define cluster measure
                std::tuple< fem::Measure_Type, mtk::Primary_Void, mtk::Master_Slave > mMasterVolumeTuple =
                        std::make_tuple(
                                fem::Measure_Type::CELL_MEASURE,
                                mtk::Primary_Void::PRIMARY,
                                mtk::Master_Slave::MASTER );

                // default tuple for slave volume size to define cluster measure
                std::tuple< fem::Measure_Type, mtk::Primary_Void, mtk::Master_Slave > mSlaveVolumeTuple =
                        std::make_tuple(
                                fem::Measure_Type::CELL_MEASURE,
                                mtk::Primary_Void::VOID,
                                mtk::Master_Slave::SLAVE );

            public:

                //------------------------------------------------------------------------------
                /*
                 * constructor
                 */
                SP_Reciprocal_Total_Volume(){};

                //------------------------------------------------------------------------------
                /**
                 * trivial destructor
                 */
                ~SP_Reciprocal_Total_Volume(){};

                //------------------------------------------------------------------------------
                /**
                 * set dof types
                 * @param[ in ] aDofTypes a cell of cell of dof types
                 * @param[ in ] aDofStrings list of strings describing the dof types
                 * @param[ in ] aIsMaster enum for master or slave
                 */
                void set_dof_type_list(
                        moris::Cell< moris::Cell< MSI::Dof_Type > > & aDofTypes,
                        moris::Cell< std::string >                  & aDofStrings,
                        mtk::Master_Slave                             aIsMaster = mtk::Master_Slave::MASTER )
                {
                    Stabilization_Parameter::set_dof_type_list( aDofTypes, aIsMaster );
                }

                //------------------------------------------------------------------------------
                /**
                 * set dv types
                 * @param[ in ] aDvTypes   a cell of group of dv types
                 * @param[ in ] aDvStrings list of strings describing the dv types
                 * @param[ in ] aIsMaster enum for master or slave
                 */
                void set_dv_type_list(
                        moris::Cell< moris::Cell< PDV_Type > > & aDvTypes,
                        moris::Cell< std::string >             & aDvStrings,
                        mtk::Master_Slave                        aIsMaster = mtk::Master_Slave::MASTER )
                {
                    Stabilization_Parameter::set_dv_type_list( aDvTypes, aIsMaster );
                }

                //------------------------------------------------------------------------------
                /**
                 * get cluster measure tuples
                 * @param[ in ] aClusterMeasureTuples list of tuples describing the cluster measure types
                 */
                moris::Cell< std::tuple<
                fem::Measure_Type,
                mtk::Primary_Void,
                mtk::Master_Slave > > get_cluster_measure_tuple_list();

                //------------------------------------------------------------------------------
                /**
                 * evaluate the penalty parameter value
                 */
                void eval_SP();

                //------------------------------------------------------------------------------
                /**
                 * evaluate the stabilization parameter derivative wrt to a master dof type
                 * @param[ in ] aDofTypes a dof type wrt which the derivative is evaluated
                 * dSPdMasterDOF ( 1 x numDerDof )
                 */
                void eval_dSPdMasterDOF( const moris::Cell< MSI::Dof_Type > & aDofTypes );

                //------------------------------------------------------------------------------
                /**
                 * evaluate the stabilization parameter derivative wrt to a slave dof type
                 * @param[ in ] aDofTypes a dof type wrt which the derivative is evaluated
                 * dSPdSlaveDOF ( 1 x numDerDof )
                 */
                void eval_dSPdSlaveDOF( const moris::Cell< MSI::Dof_Type > & aDofTypes );

                //------------------------------------------------------------------------------
                /**
                 * evaluate the penalty parameter derivative wrt to a master dv type
                 * @param[ in ] aDvTypes a dv type wrt which the derivative is evaluated
                 * dPPdMasterDV ( 1 x numDerDv )
                 */
                void eval_dSPdMasterDV( const moris::Cell< PDV_Type > & aDvTypes )
                {
                    MORIS_ERROR( false, "SP_Reciprocal_Total_Volume::eval_dSPdMasterDV: not implemented." );
                }

                //------------------------------------------------------------------------------
                /**
                 * evaluate the penalty parameter derivative wrt to a slave dv type
                 * @param[ in ] aDvTypes a dv type wrt which the derivative is evaluated
                 * dSPdSlaveDV ( 1 x numDerDv )
                 */
                void eval_dSPdSlaveDV( const moris::Cell< PDV_Type > & aDvTypes )
                {
                    MORIS_ERROR( false, "SP_Reciprocal_Total_Volume::eval_dSPdSlaveDV: not implemented." );
                }
                //------------------------------------------------------------------------------
        };
        //------------------------------------------------------------------------------
    } /* namespace fem */
} /* namespace moris */

#endif /* PROJECTS_FEM_INT_SRC_CL_FEM_SP_RECIPROCAL_TOTAL_VOLUME_HPP_ */
