# Padrão Strategy

## 1. Conceito Teórico

O padrão Strategy encapsula algoritmos intercambiáveis atrás de uma mesma interface. O cliente depende de `ILayoutStrategy`, não de uma implementação concreta.

Em Python, isso pode ser feito com um protocolo ou uma classe base. Em Java, é comum usar uma interface. Em C++, a interface usa métodos virtuais puros e polimorfismo por ponteiro ou referência.

## 2. Sintaxe Essencial

~~~cpp
class Strategy {
public:
    virtual ~Strategy() = 0;
    virtual void execute() = 0;
};

class ConcreteStrategy final : public Strategy {
public:
    void execute() override;
};
~~~

A implementação concreta pode ser escolhida em tempo de execução sem alterar o código do cliente.

## 3. Aplicação no Projeto Spatial Engine

Os contratos estão em `CPP/include/algorithm/ILayoutStrategy.hpp` e `Layouts.hpp`.

~~~cpp
class ILayoutStrategy {
public:
    virtual ~ILayoutStrategy() = 0;
    virtual void applyLayout(model::Graph& graph, int iterations) = 0;
};

class ForceDirectedLayout3D final : public ILayoutStrategy {
public:
    void applyLayout(model::Graph& graph, int iterations) override;
};
~~~

As estratégias previstas são `ForceDirectedLayout3D`, `SphericalLayout3D` e `HierarchicalLayout3D`. A `SpatialEngineFacade` recebe qualquer uma delas por `std::unique_ptr`.

## 4. Cuidados e Erros Comuns

- A assinatura sobrescrita precisa coincidir exatamente com a interface.
- Use `override` para detectar erros de assinatura.
- A interface deve possuir destrutor virtual.
- Não acople a fachada a uma estratégia concreta.
- Defina uma política para `iterations` inválido, como zero ou valor negativo.
