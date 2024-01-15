add_library(
    CRTlib
    "${CMAKE_CURRENT_SOURCE_DIR}/CRTlib/CRTlib.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/CRTlib/CRTlib.cxx"
)

target_include_directories(CRTlib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_definitions(CRTlib PRIVATE CRT_VERSION=1.0)
