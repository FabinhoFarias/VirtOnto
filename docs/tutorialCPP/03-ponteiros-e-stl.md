# Ponteiros Inteligentes e STL

## 1. Conceito Teórico

A STL oferece containers e algoritmos prontos. `std::unordered_map` armazena nós indexados por ID; `std::vector` mantém a sequência de arestas.

`std::shared_ptr` representa propriedade compartilhada. No `Graph`, vários componentes podem manter uma referência ao mesmo nó. `std::unique_ptr` representa propriedade exclusiva e é adequado para a estratégia usada pela fachada.

Em Python, a memória é gerenciada pelo coletor de lixo. Em Java, ocorre algo semelhante. Em C++, RAII associa a liberação dos recursos ao tempo de vida dos objetos.

## 2. Sintaxe Essencial

~~~cpp
#include <memory>
#include <unordered_map>
#include <string>

struct Node { };

std::unordered_map<std::string, std::shared_ptr<Node>> nodes;
nodes["Person"] = std::make_shared<Node>();

std::unique_ptr<Node> owner = std::make_unique<Node>();
~~~

O uso de `std::make_shared` e `std::make_unique` evita chamadas explícitas a `new`.

## 3. Aplicação no Projeto Spatial Engine

O diagrama mapeia `Graph` para `CPP/include/model/Graph.hpp`.

~~~cpp
class Graph {
public:
    void addNode(std::shared_ptr<Node> node);
    void addEdge(std::shared_ptr<Edge> edge);
    const std::unordered_map<std::string, std::shared_ptr<Node>>& getNodes() const noexcept;
    const std::vector<std::shared_ptr<Edge>>& getEdges() const noexcept;

private:
    std::unordered_map<std::string, std::shared_ptr<Node>> nodes_;
    std::vector<std::shared_ptr<Edge>> edges_;
};
~~~

Os retornos por referência constante evitam cópias e impedem que o consumidor altere os containers internos.

## 4. Cuidados e Erros Comuns

- Não use `shared_ptr` quando existir um único proprietário claro.
- Verifique ponteiros recebidos antes de acessá-los.
- Evite ciclos de `shared_ptr`; use `weak_ptr` quando necessário.
- Não retorne referências para containers que serão destruídos.
- `unordered_map` não garante ordem de iteração.
