#pragma once

#include "model/Graph.hpp"

#include <string>

namespace virtonto::service {

class GraphBuilder {
public:
    static model::Graph buildFromJSON(const std::string& rawJson);
};

} // namespace virtonto::service
