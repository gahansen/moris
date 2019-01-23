/*
 * cl_NLA_DofTypeStruc.hpp.hpp
 *
 *  Created on: Jan 18, 2018
 *      Author: schmidt
 */
#ifndef SRC_FEM_CL_DOFTYPESTRUC_HPP_
#define SRC_FEM_CL_DOFTYPESTRUC_HPP_

#include "typedefs.hpp"
#include "cl_Cell.hpp"
#include "cl_Matrix.hpp"
#include "cl_MSI_Dof_Type_Enums.hpp"

namespace moris
{
namespace NLA
{
    class DofTypeStruc
    {
    private:

        moris::Cell< moris::Cell< enum MSI::Dof_Type > > mStaggeredDofTypeList;
        moris::sint                                      mLevel = -1;

    public:
        DofTypeStruc( const moris::Cell< moris::Cell< enum MSI::Dof_Type > > aStaggeredDofTypeList,
                      const moris::sint                                      aLevel =  0 ) : mStaggeredDofTypeList( aStaggeredDofTypeList),
                                                                                             mLevel (aLevel)
        {};

        ~DofTypeStruc()
        {
        };

        moris::Cell< moris::Cell< enum MSI::Dof_Type > > & get_dof_type_list()
        {
            return mStaggeredDofTypeList;
        };

        moris::sint get_dof_type_list_level()
        {
            return mLevel;
        };

//        moris::Cell< enum MSI::Dof_Type > get_dof_type_union()
//        {
//            moris::sint tCounter = 0;
//
//            for ( moris::sint Ik = 0; Ik <= mStaggeredDofTypeList.size(); ++Ik )
//            {
//                tCounter =+ mStaggeredDofTypeList( Ik ).size();
//            }
//
//            tCounter = 0;
//            moris::Cell< enum MSI::Dof_Type > tUnionEnumList( tCounter );
//
//            for ( moris::sint Ik = 0; Ik < mStaggeredDofTypeList.size(); ++Ik )
//            {
//                for ( moris::sint Ii = 0; Ii < mStaggeredDofTypeList( Ik ).size(); ++Ii )
//                {
//                    tUnionEnumList( tCounter ) = mStaggeredDofTypeList( Ik )( Ii );
//
//                    tCounter++;;
//                }
//            }
//
//            return tUnionEnumList;
//        };
    };
}
}

#endif /* SRC_FEM_CL_DOFTYPESTRUC_HPP_ */
