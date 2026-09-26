#include "algorithms/ForceDirectedLayout3D.hpp"
#include "model/Edge.hpp"
#include "model/Node.hpp"
#include <cmath>
#include <vector>

namespace virtonto::algorithm {

ForceDirectedLayout3D::ForceDirectedLayout3D(float repulsion, float attraction, float damping)
    : repulsionStrength_(repulsion), attractionStrength_(attraction), dampingFactor_(damping) {}

void ForceDirectedLayout3D::applyLayout(model::Graph& graph, int iterations) {
    std::vector<std::shared_ptr<model::Node>> nodes;
    nodes.reserve(graph.getNodeCount());
    for (auto& [id, node] : graph.getNodes()) {
        nodes.push_back(node);
        node->setVelocity({0,0,0});
    }

    for (int iter = 0; iter < iterations; ++iter) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            for (size_t j = i + 1; j < nodes.size(); ++j) {
                auto posA = nodes[i]->getPosition();
                auto posB = nodes[j]->getPosition();
                model::Vector3D dir{posA.x - posB.x, posA.y - posB.y, posA.z - posB.z};
                float dist = std::sqrt(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
                if (dist < MIN_DISTANCE) dist = MIN_DISTANCE;

                float forceMag = repulsionStrength_ / (dist * dist);
                model::Vector3D force{ (dir.x/dist)*forceMag, (dir.y/dist)*forceMag, (dir.z/dist)*forceMag };

                auto va = nodes[i]->getVelocity();
                auto vb = nodes[j]->getVelocity();
                nodes[i]->setVelocity({va.x+force.x, va.y+force.y, va.z+force.z});
                nodes[j]->setVelocity({vb.x-force.x, vb.y-force.y, vb.z-force.z});
            }
        }

        for (auto& edge : graph.getEdges()) {
            auto s = graph.getNode(edge->getSourceId());
            auto t = graph.getNode(edge->getTargetId());
            if (!s ||!t) continue;
            auto posS = s->getPosition(); auto posT = t->getPosition();
            model::Vector3D dir{posT.x-posS.x, posT.y-posS.y, posT.z-posS.z};
            float dist = std::sqrt(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
            if (dist < 0.01f) continue;
            float forceMag = dist * attractionStrength_;
            model::Vector3D force{ (dir.x/dist)*forceMag, (dir.y/dist)*forceMag, (dir.z/dist)*forceMag };
            auto vs = s->getVelocity(); auto vt = t->getVelocity();
            s->setVelocity({vs.x+force.x, vs.y+force.y, vs.z+force.z});
            t->setVelocity({vt.x-force.x, vt.y-force.y, vt.z-force.z});
        }

        for (auto& node : nodes) {
            auto vel = node->getVelocity();
            vel = {vel.x * dampingFactor_, vel.y * dampingFactor_, vel.z * dampingFactor_};
            node->setVelocity(vel);
            auto pos = node->getPosition();
            node->setPosition({pos.x + vel.x * TIME_STEP, pos.y + vel.y * TIME_STEP, pos.z + vel.z * TIME_STEP});
        }
    }
}

} // namespace virtonto::algorithm
