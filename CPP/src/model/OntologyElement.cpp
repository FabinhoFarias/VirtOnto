#include "model/OntologyElement.hpp"
#include <utility>

namespace virtonto::model {

// Construtor base exigido pelo Node
OntologyElement::OntologyElement(std::string id, std::string label)
    : id_(std::move(id)), label_(std::move(label)) {}

// O destrutor precisa ter corpo no .cpp, mesmo usando '= default;'
OntologyElement::~OntologyElement() = default;

std::string OntologyElement::getId() const noexcept {
    return id_;
}

std::string OntologyElement::getLabel() const noexcept {
    return label_;
}

} // namespace virtonto::model