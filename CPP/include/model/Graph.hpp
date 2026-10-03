#pragma once

#include "model/Edge.hpp"
#include "model/Node.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace virtonto::model {

class Graph {
public:
    Graph() = default;
    ~Graph() = default;

    // --- CREATE ---
    void addNode(std::shared_ptr<Node> node);
    void addEdge(std::shared_ptr<Edge> edge);

    // --- READ ---
    std::shared_ptr<Node> getNode(const std::string& id) const;
    const std::unordered_map<std::string, std::shared_ptr<Node>>& getNodes() const noexcept;
    const std::vector<std::shared_ptr<Edge>>& getEdges() const noexcept;
    std::size_t getNodeCount() const noexcept;
    std::size_t getEdgeCount() const noexcept;

    // --- UPDATE ---
    bool updateNode(const std::string& id, const Node& updatedNodeData);

    // --- DELETE ---
    bool deleteNode(const std::string& id);
    bool deleteEdge(const std::string& sourceId, const std::string& targetId);

    // Clean
    void clear() noexcept;

private:
    std::unordered_map<std::string, std::shared_ptr<Node>> nodes_;
    std::vector<std::shared_ptr<Edge>> edges_;
};

} // namespace virtonto::model