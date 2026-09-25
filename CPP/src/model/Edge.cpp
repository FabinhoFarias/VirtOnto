#include "model/Edge.hpp"
#include <iostream>
#include <cassert>
#include <utility>

namespace virtonto::model {

// Repassa 'id' e 'relation' (como rótulo) para a classe pai OntologyElement
Edge::Edge(std::string id, std::string source, std::string target, std::string relation)
    : OntologyElement(std::move(id), relation),
      sourceId_(std::move(source)),
      targetId_(std::move(target)),
      relationType_(std::move(relation)) {}

const std::string& Edge::getSourceId() const noexcept {
    return sourceId_;
}

const std::string& Edge::getTargetId() const noexcept {
    return targetId_;
}

const std::string& Edge::getRelationType() const noexcept {
    return relationType_;
}

float Edge::getWeight() const noexcept {
    return weight_;
}

std::string Edge::getDisplayColor() const {
    return "#888888"; // Cor cinza padrão para conexões
}

} // namespace virtonto::model


// --- BLOCO DE TESTE TEMPORÁRIO ---
// int main() {
//     using namespace virtonto::model;

//     Edge edge("e1", "node_class_person", "node_ind_john", "isA");

//     // Teste de métodos herados de OntologyElement
//     assert(edge.getId() == "e1");
//     assert(edge.getLabel() == "isA");
//     assert(edge.getDisplayColor() == "#888888");

//     // Teste de métodos específicos de Edge
//     assert(edge.getSourceId() == "node_class_person");
//     assert(edge.getTargetId() == "node_ind_john");
//     assert(edge.getRelationType() == "isA");
//     assert(edge.getWeight() == 1.0f);

//     std::cout << "✅ Todos os testes da Edge passaram!" << std::endl;
//     return 0;
// }


// g++ -std=c++17 CPP/src/model/Edge.cpp CPP/src/model/OntologyElement.cpp -ICPP/include -o test_edge && ./test_edge

//concluído
