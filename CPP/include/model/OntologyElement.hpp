#pragma once

#include <string>

namespace virtonto::model {

class OntologyElement {
public:
    OntologyElement(std::string id, std::string label);
    virtual ~OntologyElement() = 0;

    const std::string& getId() const noexcept;
    const std::string& getLabel() const noexcept;
    virtual std::string getDisplayColor() const = 0;

protected:
    std::string id_;
    std::string label_;
};

} // namespace virtonto::model
