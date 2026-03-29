cmake_minimum_required(VERSION 3.16)

project(SpoutEngage LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(SpoutEngage SHARED
  SpoutEngage_global.h
  spoutengage.cpp
  spoutengage.h
  # spoutsender.h spoutsender.cpp
)
# Дохнет от Spout

# set(SPOUT_DIR "${CMAKE_SOURCE_DIR}/../spout2")
# set(SPOUT_LIB_DIR "${SPOUT_DIR}/INSTALL/lib")
# set(SPOUT_BIN_DIR "${SPOUT_DIR}/INSTALL/bin")

# target_include_directories(SpoutEngage PRIVATE
#     "${SPOUT_DIR}/INSTALL/include"
# )

# set(SPOUT_LIBS
#     "${SPOUT_LIB_DIR}/libSpoutDX.dll.a"
#     "${SPOUT_LIB_DIR}/libSpoutDX12.dll.a"
#     "${SPOUT_LIB_DIR}/libSpoutDX9.dll.a"
#     "${SPOUT_LIB_DIR}/libSpout.dll.a"
#     "${SPOUT_LIB_DIR}/libSpoutLibrary.dll.a"
# )
# target_compile_definitions(SpoutEngage PRIVATE
#     USE_SPOUT_DX
#     USE_SPOUT_DX12
#     USE_SPOUT_DX9
#     USE_SPOUT_GL
#     USE_SPOUT_LIBRARY
# )

# target_link_libraries(${PROJECT_NAME} PRIVATE ${SPOUT_LIBS})

target_compile_definitions(SpoutEngage PRIVATE SPOUTENGAGE_LIBRARY)

set_target_properties(SpoutEngage PROPERTIES SUFFIX ".ofp")


