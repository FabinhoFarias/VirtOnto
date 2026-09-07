# Facade e Métodos Estáticos

## 1. Conceito Teórico

Facade oferece uma interface simples para um subsistema complexo. No projeto, `SpatialEngineFacade` coordena carregamento, escolha da estratégia, processamento e serialização.

Métodos estáticos pertencem à classe e podem ser chamados sem instanciar um objeto. Eles são adequados para operações sem estado próprio, como construir um `Graph` a partir de texto ou serializá-lo.

Em Python, funções de módulo ou `@staticmethod` cumprem papel semelhante. Em Java, usa-se um método `static`.

## 2. Sintaxe Essencial

~~~cpp
class Converter {
public:
    static int parse(const std::string& value);
};

int result = Converter::parse("42");
~~~

Uma Facade normalmente mantém os detalhes dos componentes internos privados e expõe operações de alto nível.

## 3. Aplicação no Projeto Spatial Engine

Os contratos estão em `CPP/include/service/SpatialEngineFacade.hpp`, `GraphBuilder.hpp` e `GraphSerializer.hpp`.

~~~cpp
class SpatialEngineFacade {
public:
    SpatialEngineFacade();
    void loadOntologyGraph(const std::string& jsonInput);
    void setLayoutStrategy(std::unique_ptr<algorithm::ILayoutStrategy> strategy);
    void processLayout(int iterations);
    std::string getRenderableJSON() const;
};

class GraphBuilder {
public:
    static model::Graph buildFromJSON(const std::string& rawJson);
};
~~~

O fluxo esperado é: receber JSON do Java, construir o grafo, selecionar o layout, processar as posições e devolver JSON 3D.

## 4. Cuidados e Erros Comuns

- A Facade não deve expor detalhes internos desnecessários.
- Métodos estáticos não acessam estado de instância sem recebê-lo como argumento.
- Documente quem é responsável pela propriedade da estratégia.
- Valide entradas antes de encaminhá-las aos componentes internos.
- Evite transformar a Facade em uma classe que concentre toda a lógica do domínio.
