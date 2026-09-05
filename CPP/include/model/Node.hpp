#pragma once

#include "model/OntologyElement.hpp"
#include "model/Vector3D.hpp"

namespace virtonto::model {

enum class NodeType {
    CLASS,
    INDIVIDUAL,
    PROPERTY
};

class Node final : public OntologyElement {
public:
    Node(std::string id, std::string label, NodeType type);

    NodeType getType() const noexcept;
    Vector3D getPosition() const noexcept;
    void setPosition(const Vector3D& position) noexcept;
    Vector3D getVelocity() const noexcept;
    void setVelocity(const Vector3D& velocity) noexcept;
    float getMass() const noexcept;
    std::string getDisplayColor() const override;

private:
    NodeType type_;
    Vector3D position_{};
    Vector3D velocity_{};
    float mass_{1.0F};
};

} // namespace virtonto::model
