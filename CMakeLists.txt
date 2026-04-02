cmake_minimum_required(VERSION 3.16)

project(SpoutEngage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(SpoutEngage SHARED
  SpoutEngage_global.h
  spoutengage.cpp
  spoutengage.h
  spoutsender.h spoutsender.cpp
)

# Compile spout2 from source (avoids DLL ABI mismatch / buffer overruns in MinGW Plugin loading)
if (MINGW AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # GCC/Clang требуют явного флага для интринсиков SSE, в отличие от MSVC.
    add_compile_options(-mssse3 -msse4.1)
endif()

set(SPOUT_BUILD_SPOUTDX ON)
set(SPOUT_BUILD_LIBRARY OFF)
set(SKIP_INSTALL_ALL ON)
add_subdirectory("${CMAKE_SOURCE_DIR}/../spout2" spoutbuild)

target_include_directories(SpoutEngage PRIVATE
    "${CMAKE_SOURCE_DIR}/../spout2/SPOUTSDK"
    "${CMAKE_SOURCE_DIR}/../spout2/SPOUTSDK/SpoutDirectX"
)

# Use only DX (DX11) and GL, which are what SpoutSender actually uses in your code
target_compile_definitions(SpoutEngage PRIVATE
    USE_SPOUT_DX
    USE_SPOUT_GL
    SPOUTENGAGE_LIBRARY
)

# Link statically to avoid needing DLLs at runtime and side-effect crashes
target_link_libraries(SpoutEngage PRIVATE SpoutDX_static Spout_static d3d11)

set_target_properties(SpoutEngage PROPERTIES SUFFIX ".ofp")


