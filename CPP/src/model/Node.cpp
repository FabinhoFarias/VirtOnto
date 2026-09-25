#include "model/Node.hpp"
#include <iostream>
#include <cassert>
#include <utility>

namespace virtonto::model {

// ✅ Repassa 'id' e 'label' para a classe pai OntologyElement
Node::Node(std::string id, std::string label, NodeType type)
    : OntologyElement(std::move(id), std::move(label)), type_(type) {}

NodeType Node::getType() const noexcept {
    return type_;
}

Vector3D Node::getPosition() const noexcept {
    return position_;
}

void Node::setPosition(const Vector3D& position) noexcept {
    position_ = position;
}

Vector3D Node::getVelocity() const noexcept {
    return velocity_;
}

void Node::setVelocity(const Vector3D& velocity) noexcept {
    velocity_ = velocity;
}

float Node::getMass() const noexcept {
    return mass_;
}

std::string Node::getDisplayColor() const {
    switch (type_) {
        case NodeType::CLASS:
            return "#FFA500"; // Laranja
        case NodeType::INDIVIDUAL:
            return "#00FF00"; // Verde
        case NodeType::PROPERTY:
            return "#0000FF"; // Azul
    }
    return "#FFFFFF";
}

} // namespace virtonto::model


// --- BLOCO DE TESTE TEMPORÁRIO ---
// int main() {
//     using namespace virtonto::model;

//     Node nodeClass("1", "Person", NodeType::CLASS);
//     Node nodeInd("2", "John", NodeType::INDIVIDUAL);
//     Node nodeProp("3", "hasAge", NodeType::PROPERTY);

//     // Teste das cores
//     assert(nodeClass.getDisplayColor() == "#FFA500");
//     assert(nodeInd.getDisplayColor() == "#00FF00");
//     assert(nodeProp.getDisplayColor() == "#0000FF");

//     // Teste de posição
//     Vector3D novaPos{10.0f, -5.0f, 2.5f};
//     nodeClass.setPosition(novaPos);
//     assert(nodeClass.getPosition().x == 10.0f);
//     assert(nodeClass.getPosition().y == -5.0f);

//     std::cout << "✅ Todos os testes do Node passaram!" << std::endl;
//     return 0;
// }

// g++ -std=c++17 CPP/src/model/Node.cpp CPP/src/model/Vector3D.cpp CPP/src/model/OntologyElement.cpp -ICPP/include -o test_node && ./test_node

//concluído
