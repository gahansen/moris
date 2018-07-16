# -------------------------------------------------------------------------
# Armadillo libraries -----------------------------------------------------
# -------------------------------------------------------------------------

set(ARMADILLO_ENV_VARS
    $ENV{ARMADILLODIR}
    $ENV{ARMADILLO_DIR}
    $ENV{Armadillo_DIR}
    $ENV{ARMADILLO_ROOT}
    $ENV{Armadillo_ROOT}
    $ENV{ARMADILLO_PATH}
    $ENV{Armadillo_PATH} )

find_package(Armadillo REQUIRED HINTS ${ARMADILLO_ENV_VARS})

message(STATUS "ARMADILLO_LIBRARIES: ${ARMADILLO_LIBRARIES}")

list(APPEND MORIS_DEFINITIONS "-DMORIS_USE_ARMA")
list(APPEND MORIS_INCDIRS "${ARMADILLO_INCLUDE_DIRS}")
list(APPEND MORIS_LDFLAGS "${ARMADILLO_LIBRARY_DIRS}")
list(APPEND MORIS_LDLIBS "-larmadillo")

mark_as_advanced(Armadillo_DIR)