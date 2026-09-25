#include "algorithms/ForceDirectedLayout3D.hpp"
#include "model/Edge.hpp"
#include "model/Node.hpp"
#include <cmath>
#include <vector>

namespace virtonto::algorithm {

ForceDirectedLayout3D::ForceDirectedLayout3D(float repulsion, float attraction, float damping)
    : repulsionStrength_(repulsion), attractionStrength_(attraction), dampingFactor_(damping) {}

void ForceDirectedLayout3D::applyLayout(model::Graph& graph, int iterations) {
    // Transforma o map em vector pra fazer par-a-par
    std::vector<std::shared_ptr<model::Node>> nodes;
    nodes.reserve(graph.getNodeCount());
    for (auto& [id, node] : graph.getNodes()) {
        nodes.push_back(node);
        node->setVelocity({0,0,0}); // reseta quando puxa grafo novo
    }

    for (int iter = 0; iter < iterations; ++iter) {

        // 1. REPULSÃO: todo nó repele todo nó
        for (size_t i = 0; i < nodes.size(); ++i) {
            for (size_t j = i + 1; j < nodes.size(); ++j) {
                auto posA = nodes[i]->getPosition();
                auto posB = nodes[j]->getPosition();

                model::Vector3D dir{posA.x - posB.x, posA.y - posB.y, posA.z - posB.z};
                float distSq = dir.x*dir.x + dir.y*dir.y + dir.z*dir.z;
                float dist = std::sqrt(distSq);
                if (dist < 0.1f) dist = 0.1f;

                float forceMag = repulsionStrength_ / (dist * dist);
                model::Vector3D force{
                    (dir.x / dist) * forceMag,
                    (dir.y / dist) * forceMag,
                    (dir.z / dist) * forceMag
                };

                auto velA = nodes[i]->getVelocity();
                auto velB = nodes[j]->getVelocity();
                nodes[i]->setVelocity({velA.x + force.x, velA.y + force.y, velA.z + force.z});
                nodes[j]->setVelocity({velB.x - force.x, velB.y - force.y, velB.z - force.z});
            }
        }

        // 2. ATRAÇÃO: arestas puxam
        for (auto& edge : graph.getEdges()) {
            auto source = graph.getNode(edge->getSourceId());
            auto target = graph.getNode(edge->getTargetId());
            if (!source ||!target) continue;

            auto posS = source->getPosition();
            auto posT = target->getPosition();
            model::Vector3D dir{posT.x - posS.x, posT.y - posS.y, posT.z - posS.z};
            float dist = std::sqrt(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
            if (dist < 0.01f) continue;

            float forceMag = dist * attractionStrength_;
            model::Vector3D force{
                (dir.x / dist) * forceMag,
                (dir.y / dist) * forceMag,
                (dir.z / dist) * forceMag
            };

            auto velS = source->getVelocity();
            auto velT = target->getVelocity();
            source->setVelocity({velS.x + force.x, velS.y + force.y, velS.z + force.z});
            target->setVelocity({velT.x - force.x, velT.y - force.y, velT.z - force.z});
        }

        // 3. APLICA com amortecimento
        for (auto& node : nodes) {
            auto vel = node->getVelocity();
            vel = {vel.x * dampingFactor_, vel.y * dampingFactor_, vel.z * dampingFactor_};
            node->setVelocity(vel);

            auto pos = node->getPosition();
            node->setPosition({pos.x + vel.x * 0.01f, pos.y + vel.y * 0.01f, pos.z + vel.z * 0.01f});
        }
    }
}

} // namespace virtonto::algorithm

//implementado
