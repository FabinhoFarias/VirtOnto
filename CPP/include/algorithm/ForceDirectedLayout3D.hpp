#pragma once
#include "algorithms/ILayoutStrategy.hpp"

namespace virtonto::algorithm {

class ForceDirectedLayout3D : public ILayoutStrategy {
public:

    static constexpr float REPULSION_DEFAULT = 500.0f;
    static constexpr float ATTRACTION_DEFAULT = 0.05f;
    static constexpr float DAMPING_DEFAULT = 0.85f;
    static constexpr float MIN_DISTANCE = 0.1f;
    static constexpr float TIME_STEP = 0.01f;

    ForceDirectedLayout3D(
        float repulsion = REPULSION_DEFAULT,
        float attraction = ATTRACTION_DEFAULT,
        float damping = DAMPING_DEFAULT
    );

    void applyLayout(model::Graph& graph, int iterations) override;

private:
    float repulsionStrength_;
    float attractionStrength_;
    float dampingFactor_;
};

} // namespace virtonto::algorithm
