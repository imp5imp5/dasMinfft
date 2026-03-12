cmake_minimum_required(VERSION 3.16)
project(dasModuleMinfft C CXX)

# DASLANG_DIR must point to the daslang SDK root
if(NOT DEFINED DASLANG_DIR)
    message(FATAL_ERROR "DASLANG_DIR must be set to the daslang SDK root")
endif()

add_library(dasModuleMinfft SHARED
    src/dasMinfft.cpp
    src/dasMinfft.h
    minfft/minfft.c
    minfft/minfft.h
)

target_compile_features(dasModuleMinfft PRIVATE cxx_std_17)
target_compile_definitions(dasModuleMinfft PRIVATE
    MINFFT_SINGLE
    DAS_MOD_EXPORTS
    DAS_ENABLE_DLL=1
    $<$<CONFIG:Release>:DAS_NO_ASSERTIONS>
    $<$<CONFIG:MinSizeRel>:DAS_NO_ASSERTIONS>
    $<$<CONFIG:RelWithDebInfo>:DAS_NO_ASSERTIONS>
)

target_include_directories(dasModuleMinfft PRIVATE
    ${DASLANG_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/minfft
)

if(WIN32)
    target_link_libraries(dasModuleMinfft PRIVATE
        ${DASLANG_DIR}/lib/Release/libDaScriptDyn.lib
    )
else()
    target_link_libraries(dasModuleMinfft PRIVATE
        ${DASLANG_DIR}/lib/libDaScriptDyn.so
    )
endif()

if(MSVC)
    target_compile_options(dasModuleMinfft PRIVATE /wd4005)
endif()

set_target_properties(dasModuleMinfft PROPERTIES
    SUFFIX ".shared_module"
    PREFIX ""
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)
