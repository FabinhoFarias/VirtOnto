cmake_minimum_required(VERSION 3.20)
project(VirtOntoSpatialEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(virton_to_spatial_engine
    src/model/Vector3D.cpp
    src/model/OntologyElement.cpp
    src/model/Node.cpp
    src/model/Edge.cpp
    src/model/Graph.cpp
    src/algorithm/ForceDirectedLayout3D.cpp
    src/algorithm/SphericalLayout3D.cpp
    src/algorithm/HierarchicalLayout3D.cpp
    src/service/GraphBuilder.cpp
    src/service/GraphSerializer.cpp
    src/service/SpatialEngineFacade.cpp
)

target_include_directories(virton_to_spatial_engine PUBLIC include)
target_compile_features(virton_to_spatial_engine PUBLIC cxx_std_17)

if (MSVC)
    target_compile_options(virton_to_spatial_engine PRIVATE /W4)
else()
    target_compile_options(virton_to_spatial_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()
