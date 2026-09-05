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
    void addNode(std::shared_ptr<Node> node);
    void addEdge(std::shared_ptr<Edge> edge);
    std::shared_ptr<Node> getNode(const std::string& id) const;
    const std::unordered_map<std::string, std::shared_ptr<Node>>& getNodes() const noexcept;
    const std::vector<std::shared_ptr<Edge>>& getEdges() const noexcept;
    std::size_t getNodeCount() const noexcept;
    std::size_t getEdgeCount() const noexcept;
    void clear() noexcept;

private:
    std::unordered_map<std::string, std::shared_ptr<Node>> nodes_;
    std::vector<std::shared_ptr<Edge>> edges_;
};

} // namespace virtonto::model
