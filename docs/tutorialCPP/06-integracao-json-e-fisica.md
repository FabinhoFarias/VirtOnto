# Integração JSON e Física 3D

## 1. Conceito Teórico

O motor recebe um grafo lógico do Java e produz um grafo com coordenadas `x`, `y` e `z` para Web e VR.

A estratégia force-directed usa duas ideias: repulsão entre nós e atração entre nós ligados por arestas. A velocidade é amortecida a cada iteração antes de atualizar a posição.

Para JSON, `nlohmann/json` fornece conversão entre texto e estruturas C++. A biblioteca deve ser adicionada ao projeto antes da implementação do parser.

## 2. Sintaxe Essencial

~~~cpp
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json data = json::parse(R"({"id":"Person","x":1.0})");
const auto id = data.at("id").get<std::string>();
const auto x = data.at("x").get<float>();
~~~

Para dois pontos 3D, a distância é:

$$d = \sqrt{(x_2-x_1)^2 + (y_2-y_1)^2 + (z_2-z_1)^2}$$

## 3. Aplicação no Projeto Spatial Engine

O contrato do algoritmo está em `CPP/include/algorithm/Layouts.hpp`; os serviços estão em `CPP/include/service/GraphBuilder.hpp` e `GraphSerializer.hpp`.

~~~cpp
class ForceDirectedLayout3D final : public ILayoutStrategy {
private:
    void calculateRepulsion(model::Graph& graph);
    void calculateAttraction(model::Graph& graph);

public:
    void applyLayout(model::Graph& graph, int iterations) override;
};
~~~

Uma implementação futura deverá:

1. calcular a repulsão entre pares de nós;
2. calcular a atração seguindo as arestas;
3. aplicar `damping` à velocidade;
4. atualizar as posições;
5. serializar as coordenadas para o frontend.

## 4. Cuidados e Erros Comuns

- Não acesse campos JSON sem validar sua existência e tipo.
- Escape aspas e caracteres especiais ao serializar texto.
- Evite divisão por zero quando dois nós ocuparem a mesma posição.
- Limite a força máxima para evitar instabilidade numérica.
- O parsing e a serialização devem usar o mesmo contrato de campos.
- Adicione `nlohmann/json` ao CMake antes de incluir o header em código compilado.
