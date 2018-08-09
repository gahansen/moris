# Distributed Linear Algebra Dependencies ---------------------------------
# -------------------------------------------------------------------------

# Check if MAIN has already been included
if(DEFINED MAIN_CONFIGURED_ONCE)
    return()
endif()

set(MAIN_CONFIGURED_ONCE "YES")

# Add MAIN to the source directory list
list(APPEND MORIS_SRC_DIRS ${MAIN})

# Include all libraries for MAIN
set(MAIN_TPL_DEPENDENCIES
    "")

include(${MORIS_DEPENDS_DIR}/ALG_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/COM_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/DLA_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/GEN_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/HMR_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/INT_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/IOS_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/LNA_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/MOD_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/MSI_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/MTK_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/OPT_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/STK_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/TOL_Depends.cmake)
# include(${MORIS_DEPENDS_DIR}/XTK_Depends.cmake)

list(APPEND MAIN_TPL_DEPENDENCIES
    ${LNA_TPL_DEPENDENCIES} )
