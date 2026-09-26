#include "algorithms/HierarchicalLayout3D.hpp"
#include "model/Node.hpp"
#include <vector>
#include <unordered_map>

namespace virtonto::algorithm {

HierarchicalLayout3D::HierarchicalLayout3D(float layerHeight) : layerHeight_(layerHeight) {}

void HierarchicalLayout3D::applyLayout(model::Graph& graph, int iterations) {
    (void)iterations;

    std::unordered_map<model::NodeType, std::vector<std::shared_ptr<model::Node>>> layers;

    for (auto& [id, node] : graph.getNodes()) {
        layers[node->getType()].push_back(node);
    }

    auto placeLayer = [&](const std::vector<std::shared_ptr<model::Node>>& nodes, float y, float radius) {
        if (nodes.empty()) return;
        if (nodes.size() == 1) {
            nodes[0]->setPosition({0, y, 0});
            nodes[0]->setVelocity({0,0,0});
            return;
        }
        for (size_t i = 0; i < nodes.size(); ++i) {
            float angle = (2.0f * M_PI * i) / nodes.size();
            nodes[i]->setPosition({
                std::cos(angle) * radius,
                y,
                std::sin(angle) * radius
            });
            nodes[i]->setVelocity({0,0,0});
        }
    };

    // Y alto = Classes (conceito), meio = Propriedades, baixo = Indivíduos
    // Fica intuitivo no VR
    placeLayer(layers[model::NodeType::CLASS], layerHeight_, RADIUS_CLASS);
    placeLayer(layers[model::NodeType::PROPERTY], 0.0f, RADIUS_PROPERTY);
    placeLayer(layers[model::NodeType::INDIVIDUAL], -layerHeight_, RADIUS_INDIVIDUAL);
}

} // namespace virtonto::algorithm
