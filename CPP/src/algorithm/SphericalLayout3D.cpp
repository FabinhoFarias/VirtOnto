#include "algorithms/SphericalLayout3D.hpp"
#include "model/Node.hpp"
#include <vector>

namespace virtonto::algorithm {

SphericalLayout3D::SphericalLayout3D(float radius) : radius_(radius) {}

void SphericalLayout3D::applyLayout(model::Graph& graph, int iterations) {
    (void)iterations;

    std::vector<std::shared_ptr<model::Node>> nodes;
    nodes.reserve(graph.getNodeCount());
    for (auto& [id, node] : graph.getNodes()) nodes.push_back(node);

    size_t n = nodes.size();
    if (n == 0) return;

    for (size_t i = 0; i < n; ++i) {
        float y = 1.0f - (2.0f * i) / (n - 1);
        float r = std::sqrt(1.0f - y*y);
        float theta = GOLDEN_ANGLE * i; // <-- só referencia do contrato

        nodes[i]->setPosition({
            std::cos(theta) * r * radius_,
            y * radius_,
            std::sin(theta) * r * radius_
        });
        nodes[i]->setVelocity({0,0,0});
    }
}

} // namespace virtonto::algorithm
