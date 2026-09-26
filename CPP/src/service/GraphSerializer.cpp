#include "service/GraphSerializer.hpp"
#include <sstream>

namespace virtonto::service {

std::string GraphSerializer::toJSON3D(const model::Graph& graph) {
    std::ostringstream oss;
    oss << "{\n \"nodes\": [\n";
    bool first = true;
    for (auto& [key, node] : graph.getNodes()) {
        if (!first) oss << ",\n";
        auto p = node->getPosition();
        oss << " {\"id\":\"" << node->getId() << "\","
            << "\"label\":\"" << node->getLabel() << "\","
            << "\"type\":" << static_cast<int>(node->getType()) << ","
            << "\"color\":\"" << node->getDisplayColor() << "\","
            << "\"x\":" << p.x << ",\"y\":" << p.y << ",\"z\":" << p.z << "}";
        first = false;
    }
    oss << "\n ],\n \"edges\": [\n";
    first = true;
    for (auto& edge : graph.getEdges()) {
        if (!first) oss << ",\n";
        oss << " {\"id\":\"" << edge->getId() << "\","
            << "\"source\":\"" << edge->getSourceId() << "\","
            << "\"target\":\"" << edge->getTargetId() << "\","
            << "\"label\":\"" << edge->getLabel() << "\"}";
        first = false;
    }
    oss << "\n ]\n}";
    return oss.str();
}

} // namespace virtonto::service
