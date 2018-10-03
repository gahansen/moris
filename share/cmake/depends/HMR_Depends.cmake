# HMR Dependencies --------------------------------------------------------
# -------------------------------------------------------------------------

# Check if HMR has already been included
if(DEFINED HMR_CONFIGURED_ONCE)
    return()
endif()

set(HMR_CONFIGURED_ONCE "YES")

# Add HMR to the source directory list
list(APPEND MORIS_SOURCE_DIRS ${HMR})

# Include libraries needed by HMR
set(HMR_TPL_DEPENDENCIES
    "superlu"
    "boost"
    )

# Make sure needed moris libraries are built
include(${MORIS_DEPENDS_DIR}/LINALG_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/GEN_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/TOL_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/INT_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/MDL_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/NLA_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/DLA_Depends.cmake)

# Include third party libraries indirectly needed by HMR
list(APPEND HMR_TPL_DEPENDENCIES
    ${STK_TPL_DEPENDENCIES}
    ${TOL_TPL_DEPENDENCIES}
    )
