#ifndef SRC_DISTLINALG_CL_MAP_EPETRA_HPP_
#define SRC_DISTLINALG_CL_MAP_EPETRA_HPP_

#include <cstddef>
#include <cassert>
#include <memory>

#include "cl_Matrix.hpp"
#include "linalg_typedefs.hpp"
#include "cl_Communicator_Epetra.hpp"
#include "cl_BoostBitset.hpp" // CON/src

#include "cl_Map_Class.hpp"

#include "Epetra_ConfigDefs.h"
#include "Epetra_Directory.h"
#include "Epetra_BlockMap.h"
#include "Epetra_Map.h"

namespace moris
{
class Map_Epetra : public Map_Class
{
private:
    Communicator_Epetra      mEpetraComm;

    void translator( const moris::uint      & aNumMaxDofs,
                     const moris::uint      & aNumMyDofs,
                     const moris::uint      & aNumGlobalDofs,
                     const Matrix< DDSMat > & aMyLocaltoGlobalMap,
                           Matrix< DDSMat > & aMyGlobalConstraintDofs,
                     const Matrix< DDUMat > & aMyConstraintDofs );

protected:

public:
    Map_Epetra( const moris::uint      & aNumMaxDofs,
                const Matrix< DDSMat > & aMyLocaltoGlobalMap,
                const Matrix< DDUMat > & aMyConstraintDofs,
                const Matrix< DDSMat > & aOverlappingLocaltoGlobalMap );

    Map_Epetra( const moris::uint      & aNumMaxDofs,
                const Matrix< DDSMat > & aMyLocaltoGlobalMap,
                const Matrix< DDUMat > & aMyConstraintDofs );

    Map_Epetra( const Matrix< DDSMat > & aOverlappingLocaltoGlobalMap );

//-------------------------------------------------------------------------------------------------------------
    /** Destructor */
    ~Map_Epetra();

//-------------------------------------------------------------------------------------------------------------
    moris::sint return_local_ind_of_global_Id( moris::uint aGlobalId ) const;
};
}

#endif /* SRC_DISTLINALG_CL_MAP_EPETRA_HPP_ */
