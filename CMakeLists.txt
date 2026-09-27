cmake_minimum_required(VERSION 3.20)
project(VirtOntoSpatialEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1. Compilação da Biblioteca Estática do Motor Espacial
add_library(virton_to_spatial_engine
    CPP/src/model/Vector3D.cpp
    CPP/src/model/OntologyElement.cpp
    CPP/src/model/Node.cpp
    CPP/src/model/Edge.cpp
    CPP/src/model/Graph.cpp
    CPP/src/algorithm/ForceDirectedLayout3D.cpp
    CPP/src/algorithm/SphericalLayout3D.cpp
    CPP/src/algorithm/HierarchicalLayout3D.cpp
    CPP/src/service/GraphBuilder.cpp
    CPP/src/service/GraphSerializer.cpp
    CPP/src/service/SpatialEngineFacade.cpp
)

target_include_directories(virton_to_spatial_engine PUBLIC CPP/include)
target_compile_features(virton_to_spatial_engine PUBLIC cxx_std_17)

if (MSVC)
    target_compile_options(virton_to_spatial_engine PRIVATE /W4)
else()
    target_compile_options(virton_to_spatial_engine PRIVATE -Wall -Wextra -Wpedantic)
endif()

# 2. Compilação do Executável de Teste
add_executable(ontology_mock_test "ontology mock test.cpp")
target_link_libraries(ontology_mock_test PRIVATE virton_to_spatial_engine)

# 3. PUXAR RECURSOS AUTOMATICAMENTE PARA A PASTA BUILD
# Copia o index.html e o mock_ontology.json da raiz para o diretório de saída
configure_file(
    "${CMAKE_SOURCE_DIR}/index.html"
    "${CMAKE_BINARY_DIR}/index.html"
    COPYONLY
)

configure_file(
    "${CMAKE_SOURCE_DIR}/mock_ontology.json"
    "${CMAKE_BINARY_DIR}/mock_ontology.json"
    COPYONLY
)