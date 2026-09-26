#include "service/SpatialEngineFacade.hpp"
#include "service/GraphBuilder.hpp"
#include "service/GraphSerializer.hpp"

namespace virtonto::service {

SpatialEngineFacade::SpatialEngineFacade() : currentGraph_(), layoutStrategy_(nullptr) {}

void SpatialEngineFacade::loadOntologyGraph(const std::string& jsonInput) {
    currentGraph_ = GraphBuilder::buildFromJSON(jsonInput);
}

void SpatialEngineFacade::setLayoutStrategy(std::unique_ptr<algorithm::ILayoutStrategy> strategy) {
    layoutStrategy_ = std::move(strategy);
}

void SpatialEngineFacade::processLayout(int iterations) {
    if (layoutStrategy_) {
        layoutStrategy_->applyLayout(currentGraph_, iterations);
    }
}

std::string SpatialEngineFacade::getRenderableJSON() const {
    return GraphSerializer::toJSON3D(currentGraph_);
}

} // namespace virtonto::service
