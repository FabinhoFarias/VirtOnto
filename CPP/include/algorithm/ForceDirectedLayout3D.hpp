#pragma once
#include "algorithms/ILayoutStrategy.hpp"

namespace virtonto::algorithm {

class ForceDirectedLayout3D : public ILayoutStrategy {
public:
    ForceDirectedLayout3D(float repulsion = 500.0f, float attraction = 0.05f, float damping = 0.85f);
    void applyLayout(model::Graph& graph, int iterations) override;

private:
    float repulsionStrength_;
    float attractionStrength_;
    float dampingFactor_;
};

} // namespace virtonto::algorithm
