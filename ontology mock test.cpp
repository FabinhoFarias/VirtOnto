#include "service/SpatialEngineFacade.hpp"
#include "algorithm/HierarchicalLayout3D.hpp" // Cabeçalho do Hierárquico
#include <fstream>
#include <iostream>

int main() {
    std::ifstream f("mock_ontology.json");
    if (!f.is_open()) {
        std::cerr << "Erro ao abrir mock_ontology.json!" << std::endl;
        return 1;
    }
    std::string json((std::istreambuf_iterator<char>(f)), {});
    
    virtonto::service::SpatialEngineFacade engine;
    engine.loadOntologyGraph(json);

    // Aqui é onde o filho chora e a mãe não vê! 
    engine.setLayoutStrategy(std::make_unique<virtonto::algorithm::HierarchicalLayout3D>());

    // O layout hierárquico é determinístico, não precisa de iterações de simulação física
    engine.processLayout(0); 

    auto out = engine.getRenderableJSON();
    std::cout << out << std::endl;
    std::ofstream o("renderable.json");
    o << out;
}