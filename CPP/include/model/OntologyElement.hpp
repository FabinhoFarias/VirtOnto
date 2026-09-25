#pragma once
#include <string>

namespace virtonto::model {

class OntologyElement {
public:
    OntologyElement(std::string id, std::string label);
    virtual ~OntologyElement(); // Destrutor virtual obrigatório para classes base

    virtual std::string getDisplayColor() const = 0; // Método abstrato (puro)

    std::string getId() const noexcept;
    std::string getLabel() const noexcept;

protected:
    std::string id_;
    std::string label_;
};

} // namespace virtonto::model
//concluído
