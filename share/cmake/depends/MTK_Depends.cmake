# MTK Dependencies --------------------------------------------------------
# -------------------------------------------------------------------------

# Check if MTK has already been included
if(DEFINED MTK_CONFIGURED_ONCE)
    return()
endif()

set(MTK_CONFIGURED_ONCE "YES")

# Add MTK to the header directory list
list(APPEND MORIS_SOURCE_DIRS ${MTK})

# Include libraries needed by MTK
set(MTK_TPL_DEPENDENCIES
    ${ARMADILLO_EIGEN}
    )
# Make sure needed moris libraries are built
include(${MORIS_DEPENDS_DIR}/LNA_Depends.cmake)

# Include third party libraries indirectly needed by MTK
list(APPEND MTK_TPL_DEPENDENCIES
    )
