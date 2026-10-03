#include "model/Graph.hpp"
#include <algorithm>

namespace virtonto::model {

// --- CREATE ---
void Graph::addNode(std::shared_ptr<Node> node) {
    if (node && nodes_.find(node->getId()) == nodes_.end()) {
        nodes_[node->getId()] = std::move(node);
    }
}

void Graph::addEdge(std::shared_ptr<Edge> edge) {
    if (edge) {
        edges_.push_back(std::move(edge));
    }
}

// --- READ ---
std::shared_ptr<Node> Graph::getNode(const std::string& id) const {
    auto it = nodes_.find(id);
    if (it != nodes_.end()) {
        return it->second;
    }
    return nullptr;
}

const std::unordered_map<std::string, std::shared_ptr<Node>>& Graph::getNodes() const noexcept {
    return nodes_;
}

const std::vector<std::shared_ptr<Edge>>& Graph::getEdges() const noexcept {
    return edges_;
}

std::size_t Graph::getNodeCount() const noexcept {
    return nodes_.size();
}

std::size_t Graph::getEdgeCount() const noexcept {
    return edges_.size();
}

// --- UPDATE ---
bool Graph::updateNode(const std::string& id, const Node& updatedNodeData) {
    auto it = nodes_.find(id);
    if (it == nodes_.end()) {
        return false;
    }
    *(it->second) = updatedNodeData;
    return true;
}

// --- DELETE ---
bool Graph::deleteNode(const std::string& id) {
    auto it = nodes_.find(id);
    if (it == nodes_.end()) {
        return false;
    }

    // 1. Remove o nó do mapa de nós
    nodes_.erase(it);

    // 2. Remove todas as arestas associadas ao nó para evitar ponteiros pendurados
    edges_.erase(
        std::remove_if(edges_.begin(), edges_.end(),
            [&id](const std::shared_ptr<Edge>& edge) {
                return edge->getSourceId() == id || edge->getTargetId() == id;
            }),
        edges_.end()
    );

    return true;
}

bool Graph::deleteEdge(const std::string& sourceId, const std::string& targetId) {
    auto initialSize = edges_.size();
    edges_.erase(
        std::remove_if(edges_.begin(), edges_.end(),
            [&sourceId, &targetId](const std::shared_ptr<Edge>& edge) {
                return edge->getSourceId() == sourceId && edge->getTargetId() == targetId;
            }),
        edges_.end()
    );
    return edges_.size() < initialSize;
}

void Graph::clear() noexcept {
    nodes_.clear();
    edges_.clear();
}

} // namespace virtonto::model

// ============================================================================
// --- BLOCO DE TESTE TEMPORÁRIO (CRUD no Graph com cassert) ---
// ============================================================================
// #include <iostream>
// #include <cassert>

// int main() {
//     using namespace virtonto::model;

//     Graph graph;

//     // 1. TESTE CREATE (Nodes e Edges)
//     auto node1 = std::make_shared<Node>("1", "Person", NodeType::CLASS, Vector3D{0.0f, 0.0f, 0.0f});
//     auto node2 = std::make_shared<Node>("2", "John", NodeType::INDIVIDUAL, Vector3D{1.0f, 1.0f, 1.0f});
//     auto edge1 = std::make_shared<Edge>("e1", "1", "2", "hasInstance");

//     graph.addNode(node1);
//     graph.addNode(node2);
//     graph.addEdge(edge1);

//     assert(graph.getNodeCount() == 2);
//     assert(graph.getEdgeCount() == 1);

//     // 2. TESTE READ
//     auto fetchedNode = graph.getNode("1");
//     assert(fetchedNode != nullptr);
//     assert(fetchedNode->getLabel() == "Person");
//     assert(fetchedNode->getDisplayColor() == "#FFA500"); // Laranja para CLASS

//     // 3. TESTE UPDATE
//     Node updatedNodeData("1", "HumanBeing", NodeType::CLASS, Vector3D{10.0f, -5.0f, 2.5f});
//     bool updated = graph.updateNode("1", updatedNodeData);
//     assert(updated == true);

//     auto nodeAfterUpdate = graph.getNode("1");
//     assert(nodeAfterUpdate->getLabel() == "HumanBeing");
//     assert(nodeAfterUpdate->getPosition().x == 10.0f);

//     // 4. TESTE DELETE NODE (Verifica deleção do nó E limpeza de arestas em cascata)
//     bool nodeDeleted = graph.deleteNode("1");
//     assert(nodeDeleted == true);
//     assert(graph.getNode("1") == nullptr);
//     assert(graph.getNodeCount() == 1);
//     assert(graph.getEdgeCount() == 0); // A aresta 'e1' que conectava o nó '1' deve ter sido removida!

//     // 5. TESTE DELETE EDGE ISOLADO
//     auto node3 = std::make_shared<Node>("3", "Age", NodeType::PROPERTY);
//     auto edge2 = std::make_shared<Edge>("e2", "2", "3", "hasProperty");
//     graph.addNode(node3);
//     graph.addEdge(edge2);

//     assert(graph.getEdgeCount() == 1);
//     bool edgeDeleted = graph.deleteEdge("2", "3");
//     assert(edgeDeleted == true);
//     assert(graph.getEdgeCount() == 0);
//     assert(graph.getNodeCount() == 2); // Os nós permanecem no grafo

//     std::cout << "✅ Todos os testes CRUD da classe Graph passaram com sucesso!" << std::endl;
//     return 0;
// }
//
// Comando de compilação do teste isolado da classe Graph:
// g++ -std=c++17 CPP/src/model/Graph.cpp CPP/src/model/Node.cpp CPP/src/model/Edge.cpp CPP/src/model/Vector3D.cpp CPP/src/model/OntologyElement.cpp -ICPP/include -o test_graph && ./test_graph