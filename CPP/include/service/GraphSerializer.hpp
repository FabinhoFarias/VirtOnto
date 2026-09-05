#pragma once

#include "model/Graph.hpp"

#include <string>

namespace virtonto::service {

class GraphSerializer {
public:
    static std::string toJSON3D(const model::Graph& graph);
};

} // namespace virtonto::service
