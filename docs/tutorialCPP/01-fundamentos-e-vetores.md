# Fundamentos, Vetores e Sobrecarga

## 1. Conceito Teórico

Uma `struct` agrupa dados relacionados e, em C++, seus membros são públicos por padrão. Ela é adequada para `Vector3D`, pois `x`, `y` e `z` representam diretamente um valor matemático.

`enum class` cria um enum fortemente tipado. Diferentemente de um enum tradicional, seus valores não são convertidos implicitamente para `int`.

Em Python, operações como `a + b` normalmente dependem de `__add__`. Em C++, a mesma ideia pode ser expressa por `operator+`. Java não possui sobrecarga geral de operadores; normalmente usa métodos como `add`.

## 2. Sintaxe Essencial

~~~cpp
#include <cmath>

struct Vector3D {
    float x{0.0F};
    float y{0.0F};
    float z{0.0F};

    Vector3D operator+(const Vector3D& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    float distanceTo(const Vector3D& other) const {
        const float dx = other.x - x;
        const float dy = other.y - y;
        const float dz = other.z - z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }
};

enum class NodeType { CLASS, INDIVIDUAL, PROPERTY };
~~~

A passagem por `const&` evita uma cópia e impede a alteração do argumento.

## 3. Aplicação no Projeto Spatial Engine

O diagrama mapeia `Vector3D` para `CPP/include/model/Vector3D.hpp` e `NodeType` para `CPP/include/model/Node.hpp`.

~~~cpp
virtonto::model::Vector3D origin{0.0F, 0.0F, 0.0F};
virtonto::model::Vector3D point{1.0F, 2.0F, 3.0F};
const auto distance = origin.distanceTo(point);
const auto translated = origin + point;
~~~

Os operadores e `distanceTo` estão declarados no projeto para serem implementados durante o módulo prático.

## 4. Cuidados e Erros Comuns

- Não confunda `enum class NodeType::CLASS` com um `int`.
- Verifique unidades e precisão ao trabalhar com `float`.
- Use `const` em operações que não alteram o vetor.
- Inclua `<cmath>` no arquivo que implementar `std::sqrt`.
- Evite retornar referências para objetos locais.
