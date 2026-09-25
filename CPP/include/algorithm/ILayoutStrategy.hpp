#pragma once

#include "model/Graph.hpp"

namespace virtonto::algorithm {

class ILayoutStrategy {
public:
    virtual ~ILayoutStrategy() = default;
    virtual void applyLayout(model::Graph& graph, int iterations) = 0;
};

} // namespace virtonto::algorithm

//concluído
