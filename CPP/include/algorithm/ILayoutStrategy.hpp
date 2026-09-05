#pragma once

#include "model/Graph.hpp"

namespace virtonto::algorithm {

class ILayoutStrategy {
public:
    virtual ~ILayoutStrategy() = 0;
    virtual void applyLayout(model::Graph& graph, int iterations) = 0;
};

} // namespace virtonto::algorithm
