# NonLinear Algebra Dependencies ---------------------------------
# -------------------------------------------------------------------------

# Check if NLA has already been included
if(DEFINED NLA_CONFIGURED_ONCE)
    return()
endif()

set(NLA_CONFIGURED_ONCE "YES")

# Add NLA to the source directory list
list(APPEND MORIS_SOURCE_DIRS ${SOL}/${NLA})

# Include libraries needed by NLA
set(NLA_TPL_DEPENDENCIES
    ""
    )

# Make sure needed moris libraries are built
include(${MORIS_DEPENDS_DIR}/SOL_CORE_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/LINALG_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/DLA_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/COM_Depends.cmake)
include(${MORIS_DEPENDS_DIR}/MSI_Depends.cmake)

# Includes needed for tests
include(${MORIS_DEPENDS_DIR}/ALG_Depends.cmake)