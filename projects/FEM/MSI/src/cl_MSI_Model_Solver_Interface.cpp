/*
 * cl_MSI_Model_Solver_Interface.cpp
 *
 *  Created on: Jul 14, 2018
 *      Author: schmidt
 */
#include "cl_MSI_Model_Solver_Interface.hpp"

#include "cl_MTK_Mesh.hpp"
#include "cl_HMR_Database.hpp"

namespace moris
{
    namespace MSI
    {

    void Model_Solver_Interface::set_solver_parameters()
    {
        mMSIParameterList.insert( "UX"    ,  1 );
        mMSIParameterList.insert( "UY"    ,  1 );
        mMSIParameterList.insert( "UZ"    ,  1 );
        mMSIParameterList.insert( "TEMP"  ,  1 );
        mMSIParameterList.insert( "L2"    ,  1 );
        mMSIParameterList.insert( "MAPPING_DOF"    ,  1 );
        mMSIParameterList.insert( "LS1",     1 );
        mMSIParameterList.insert( "LS2",     1 );
        mMSIParameterList.insert( "NLSX",    1 );
        mMSIParameterList.insert( "NLSY",    1 );
        mMSIParameterList.insert( "NLSZ",    1 );
        mMSIParameterList.insert( "VX",      1 );
        mMSIParameterList.insert( "VY",      1 );
        mMSIParameterList.insert( "VZ",      1 );
    }

//------------------------------------------------------------------------------

    moris::sint Model_Solver_Interface::get_adof_order_for_type( moris::uint aDofType )
    {
       // Get dof type enum
       enum Dof_Type tDofType = mDofMgn.get_dof_type_enum( aDofType );

       if      ( tDofType == Dof_Type::UX )          { return mMSIParameterList.get< moris::sint >( "UX" ); }
       else if ( tDofType == Dof_Type::UY )          { return mMSIParameterList.get< moris::sint >( "UY" ); }
       else if ( tDofType == Dof_Type::UZ )          { return mMSIParameterList.get< moris::sint >( "UZ" ); }
       else if ( tDofType == Dof_Type::TEMP )        { return mMSIParameterList.get< moris::sint >( "TEMP" ); }
       else if ( tDofType == Dof_Type::L2 )          { return mMSIParameterList.get< moris::sint >( "L2" ); }
       else if ( tDofType == Dof_Type::MAPPING_DOF ) { return mMSIParameterList.get< moris::sint >( "MAPPING_DOF" ); }
       else if ( tDofType == Dof_Type::LS1 )         { return mMSIParameterList.get< moris::sint >( "LS1" ); }
       else if ( tDofType == Dof_Type::LS2 )         { return mMSIParameterList.get< moris::sint >( "LS2" ); }
       else if ( tDofType == Dof_Type::NLSX )        { return mMSIParameterList.get< moris::sint >( "NLSX" ); }
       else if ( tDofType == Dof_Type::NLSY )        { return mMSIParameterList.get< moris::sint >( "NLSY" ); }
       else if ( tDofType == Dof_Type::NLSZ )        { return mMSIParameterList.get< moris::sint >( "NLSZ" ); }
       else if ( tDofType == Dof_Type::VX )          { return mMSIParameterList.get< moris::sint >( "VX" ); }
       else if ( tDofType == Dof_Type::VY )          { return mMSIParameterList.get< moris::sint >( "VY" ); }
       else if ( tDofType == Dof_Type::VZ )          { return mMSIParameterList.get< moris::sint >( "VZ" ); }

       else
       {
           MORIS_ERROR( false, "Model_Solver_Interface::get_adof_order_for_type(): Dof type does not exist. Check dof type enums");
           return 0;
       }
    }

    }
}
