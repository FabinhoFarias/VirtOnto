#pragma once

#include "model/OntologyElement.hpp"

#include <string>

namespace virtonto::model {

class Edge final : public OntologyElement {
public:
    Edge(std::string id, std::string source, std::string target, std::string relation);

    const std::string& getSourceId() const noexcept;
    const std::string& getTargetId() const noexcept;
    const std::string& getRelationType() const noexcept;
    float getWeight() const noexcept;
    std::string getDisplayColor() const override;

private:
    std::string sourceId_;
    std::string targetId_;
    std::string relationType_;
    float weight_{1.0F};
};

} // namespace virtonto::model
