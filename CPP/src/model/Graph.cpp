#include "model/Graph.hpp"
#include <cassert>
#include <iostream>
#include <utility>

namespace virtonto::model {

void Graph::addNode(std::shared_ptr<Node> node) {
    if (node) {
        nodes_[node->getId()] = std::move(node);
    }
}

void Graph::addEdge(std::shared_ptr<Edge> edge) {
    if (edge) {
        edges_.push_back(std::move(edge));
    }
}

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

void Graph::clear() noexcept {
    nodes_.clear();
    edges_.clear();
}

} // namespace virtonto::model


/* --- BLOCO DE TESTE TEMPORÁRIO ---
int main() {
    using namespace virtonto::model;

    Graph graph;

    auto nodeClass = std::make_shared<Node>("1", "Person", NodeType::CLASS);
    auto nodeInd = std::make_shared<Node>("2", "John", NodeType::INDIVIDUAL);
    auto edge1 = std::make_shared<Edge>("e1", "1", "2", "isA");

    // Testes de Adição e Contagem
    graph.addNode(nodeClass);
    graph.addNode(nodeInd);
    graph.addEdge(edge1);

    assert(graph.getNodeCount() == 2);
    assert(graph.getEdgeCount() == 1);

    // Teste de Busca por ID (O(1))
    auto buscaSucesso = graph.getNode("1");
    assert(buscaSucesso != nullptr);
    assert(buscaSucesso->getLabel() == "Person");

    auto buscaFalha = graph.getNode("id_inexistente");
    assert(buscaFalha == nullptr);

    // Teste de Limpeza de Dados
    graph.clear();
    assert(graph.getNodeCount() == 0);
    assert(graph.getEdgeCount() == 0);

    std::cout << "✅ Todos os testes da classe Graph passaram!" << std::endl;
    return 0;
}
*/

//concluído
