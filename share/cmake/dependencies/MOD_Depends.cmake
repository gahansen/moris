# Model Dependencies ------------------------------------------------------
# -------------------------------------------------------------------------

# Check if MOD has already been included
if(DEFINED MOD_CONFIGURED_ONCE)
    return()
endif()

set(MOD_CONFIGURED_ONCE "YES")

# Add MOD to the source directory list
list(APPEND MORIS_SOURCE_DIRS ${MOD})

# Include libraries needed by MOD
set(MOD_TPL_DEPENDENCIES
    ""
    )
