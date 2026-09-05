#pragma once

#include "algorithm/ILayoutStrategy.hpp"
#include "model/Graph.hpp"

#include <memory>
#include <string>

namespace virtonto::service {

class SpatialEngineFacade {
public:
    SpatialEngineFacade();

    void loadOntologyGraph(const std::string& jsonInput);
    void setLayoutStrategy(std::unique_ptr<algorithm::ILayoutStrategy> strategy);
    void processLayout(int iterations);
    std::string getRenderableJSON() const;

private:
    model::Graph currentGraph_;
    std::unique_ptr<algorithm::ILayoutStrategy> layoutStrategy_;
};

} // namespace virtonto::service
