# Herança e Polimorfismo

## 1. Conceito Teórico

Uma classe abstrata define um contrato que as subclasses devem cumprir. Em C++, um método virtual puro é declarado com `= 0`.

`Node` e `Edge` são especializações de `OntologyElement`. O ponteiro para a classe base pode referenciar qualquer uma das subclasses, permitindo polimorfismo em tempo de execução.

Em Python, isso é obtido com herança e métodos sobrescritos, geralmente usando `abc`. Em Java, a ideia corresponde a uma classe abstrata com métodos `abstract`.

## 2. Sintaxe Essencial

~~~cpp
#include <string>

class Element {
public:
    virtual ~Element() = 0;
    virtual std::string color() const = 0;
};

inline Element::~Element() = default;

class Node final : public Element {
public:
    std::string color() const override { return "blue"; }
};
~~~

O destrutor virtual permite destruir corretamente um objeto derivado por meio de um ponteiro da classe base.

## 3. Aplicação no Projeto Spatial Engine

O diagrama mapeia `OntologyElement` para `CPP/include/model/OntologyElement.hpp`, com `Node` e `Edge` em seus respectivos headers.

~~~cpp
class OntologyElement {
public:
    OntologyElement(std::string id, std::string label);
    virtual ~OntologyElement() = 0;
    virtual std::string getDisplayColor() const = 0;
};

class Node final : public OntologyElement {
public:
    std::string getDisplayColor() const override;
};
~~~

`id_` e `label_` são protegidos na classe base; estado específico de nó e aresta permanece privado nas subclasses.

## 4. Cuidados e Erros Comuns

- Use `override` para que o compilador confira a sobrescrita.
- Uma classe com método virtual puro não pode ser instanciada.
- O destrutor da base polimórfica deve ser virtual.
- Uma declaração de destrutor puro ainda precisa de uma definição em algum `.cpp`.
- `final` impede uma herança adicional quando isso for uma decisão de projeto.
