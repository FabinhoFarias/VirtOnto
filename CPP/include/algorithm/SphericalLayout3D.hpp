#pragma once
#include "algorithm/ILayoutStrategy.hpp"
#include <cmath>

namespace virtonto::algorithm {

class SphericalLayout3D : public ILayoutStrategy {
public:
    // Contrato bonito com a matemática exposta
    static constexpr float GOLDEN_RATIO_PHI = 1.6180339887f;
    // Substitui a linha 11 por:
    static constexpr float M_PI_F = 3.14159265358979323846f;
    static constexpr float GOLDEN_ANGLE = 2.0f * M_PI_F / (GOLDEN_RATIO_PHI * GOLDEN_RATIO_PHI);

    explicit SphericalLayout3D(float radius = 50.0f);
    void applyLayout(model::Graph& graph, int iterations) override;

private:
    float radius_;
};

} // namespace virtonto::algorithm
