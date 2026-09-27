#pragma once
#include "algorithm/ILayoutStrategy.hpp"
#include <cmath>

namespace virtonto::algorithm {

class HierarchicalLayout3D : public ILayoutStrategy {
public:
    static constexpr float M_PI_F = 3.14159265358979323846f;
    static constexpr float LAYER_HEIGHT = 30.0f;
    static constexpr float RADIUS_CLASS = 40.0f;
    static constexpr float RADIUS_INDIVIDUAL = 50.0f;
    static constexpr float RADIUS_PROPERTY = 25.0f;

    explicit HierarchicalLayout3D(float layerHeight = LAYER_HEIGHT);
    void applyLayout(model::Graph& graph, int iterations) override;

private:
    float layerHeight_;
};

} // namespace virtonto::algorithm