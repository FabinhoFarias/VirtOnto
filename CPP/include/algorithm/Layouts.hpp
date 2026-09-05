#pragma once

#include "algorithm/ILayoutStrategy.hpp"

namespace virtonto::algorithm {

class ForceDirectedLayout3D final : public ILayoutStrategy {
public:
    ForceDirectedLayout3D(float attractionConstant = 0.01F, float repulsionConstant = 100.0F);
    void applyLayout(model::Graph& graph, int iterations) override;

private:
    void calculateRepulsion(model::Graph& graph);
    void calculateAttraction(model::Graph& graph);

    float attractionConstant_;
    float repulsionConstant_;
    float damping_{0.85F};
};

class SphericalLayout3D final : public ILayoutStrategy {
public:
    explicit SphericalLayout3D(float radius = 10.0F);
    void applyLayout(model::Graph& graph, int iterations) override;

private:
    float radius_;
};

class HierarchicalLayout3D final : public ILayoutStrategy {
public:
    explicit HierarchicalLayout3D(float layerDistance = 5.0F);
    void applyLayout(model::Graph& graph, int iterations) override;

private:
    float layerDistance_;
};

} // namespace virtonto::algorithm
