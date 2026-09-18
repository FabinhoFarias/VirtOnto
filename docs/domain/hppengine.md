# Documentação Arquitetural: C++ Spatial Engine

---

## 1. Módulo Model (Estruturas de Dados e Entidades)

### `Vector3D` (`Vector3D.hpp`)
* **O que é:** Uma `struct` maatemática de baixo nível para representação de coordenadas e forças no espaço tridimensional.
* **Por que é uma `struct`:** Em C++, dados puros sem regras complexas de estado são definidos como `struct`. Seus membros `x`, `y` e `z` são públicos por padrão.
* **Responsabilidade:**
  * Armazenar a posição tridimensional $(x, y, z)$ e os vetores de velocidade/força dos nós.
  * Executar operações algébricas vetoriais via sobrecarga de operadores (`+`, `-`, `*`).
  * Calcular distâncias euclidianas (`distanceTo`) e magnitudes físicas (`magnitude` e `normalized`) necessárias para os algoritmos de disposição espacial. 

### `NodeType` (`Node.hpp`)
* **O que é:** Um `enum class` (enumeração fortemente tipada).
* **Responsabilidade:**
  * Categorizar a natureza semântica de um elemento no grafo semântico em três tipos: `CLASS` (Classes ontológicas), `INDIVIDUAL` (Instâncias/Pacientes) ou `PROPERTY` (Propriedades/Atributos).
  * Garantir *Type Safety*: impede conversões implícitas para números inteiros ou comparações acidentais com outros tipos numéricos.

### `OntologyElement` (`OntologyElement.hpp`)
* **O que é:** Uma classe abstrata base (*Interface/Abstract Base Class*).
* **Responsabilidade:**
  * Definir o contrato genérico para qualquer elemento visualizável na ontologia (seja um nó ou uma aresta/conexão).
  * Encapsular os atributos comuns de identificação: `id` e `label`.
  * Forçar as classes filhas a implementarem o método virtual puro `getDisplayColor() = 0`, estabelecendo uma interface polimórfica para personalização gráfica.

### `Node` (`Node.hpp`)
* **O que é:** Uma classe concreta que herda de `OntologyElement`.
* **Responsabilidade:**
  * Representar uma entidade do grafo no espaço 3D (um conceito, sintoma, doença ou paciente).
  * Encapsular o estado físico do nó: posição atual (`Vector3D position`), velocidade acumulada (`Vector3D velocity`) e massa física (`float mass`).
  * Sobrescrever `getDisplayColor()` para atribuir cores dinâmicas com base no seu `NodeType` (ex: Laranja para `CLASS`, Verde para `INDIVIDUAL`).

### `Edge` (`Edge.hpp`)
* **O que é:** Uma classe concreta que herda de `OntologyElement`.
* **Responsabilidade:**
  * Representar a conexão semântica/relacionamento entre dois nós no grafo.
  * Armazenar a origem (`sourceId`), o destino (`targetId`), o tipo de relação (`relationType`) e o peso escalar da conexão (`weight`).
  * Determinar a cor padrão de renderização da linha/conexão 3D.

### `Graph` (`Graph.hpp`)
* **O que é:** A classe container principal de dados.
* **Responsabilidade:**
  * Agrupar e gerenciar a coleção de nós e arestas que formam a ontologia.
  * Utilizar `std::unordered_map<std::string, std::shared_ptr<Node>>` para busca e inserção de nós em tempo constante $\mathcal{O}(1)$.
  * Utilizar `std::vector<std::shared_ptr<Edge>>` para armazenar as conexões do grafo.
  * Gerenciar a memória dos elementos através de ponteiros inteligentes (`std::shared_ptr`), garantindo desalocação automática e prevenindo vazamentos de memória (*memory leaks*).

---

## 2. Módulo Algorithm (Padrão Strategy)

### `ILayoutStrategy` (`ILayoutStrategy.hpp`)
* **O que é:** Uma interface pura que implementa o **Padrão de Projeto Strategy**.
* **Responsabilidade:**
  * Desacoplar a representação do Grafo do algoritmo que calcula as posições geométricas.
  * Declarar o método virtual puro `applyLayout(Graph& graph, int iterations) = 0`.
  * Permitir a troca de algoritmos de posicionamento 3D em tempo de execução (*runtime*) sem alterar a estrutura da classe `Graph` ou da fachada.

### `SphericalLayout3D` (`SphericalLayout3D.hpp`)
* **O que é:** Uma estratégia concreta de disposição geométrica que implementa `ILayoutStrategy`.
* **Responsabilidade:**
  * Distribuir os nós do grafo uniformemente sobre a superfície de uma esfera 3D.
  * Utilizar a espiral de Fibonacci esférica (Ângulo de Ouro) para calcular as posições $(x, y, z)$ sem sobreposição, ideal para visualização esférica estática rápida.

### `ForceDirectedLayout3D` (`ForceDirectedLayout3D.hpp`)
* **O que é:** Uma estratégia concreta baseada em simulação física (Algoritmo de Fruchterman-Reingold 3D).
* **Responsabilidade:**
  * Calcular forças de repulsão eletrostática entre todos os pares de nós para mantê-los afastados.
  * Calcular forças de atração elástica (mola) ao longo das arestas conexas para aproximar elementos relacionados semântica ou clinicamente.
  * Atualizar iterativamente os vetores de posição e velocidade de cada nó até atingir o equilíbrio físico do sistema visual.

### `HierarchicalLayout3D` (`HierarchicalLayout3D.hpp`)
* **O que é:** Uma estratégia concreta de disposição em camadas/árvore.
* **Responsabilidade:**
  * Posicionar os nós em planos paralelos ou em cones hierárquicos ao longo do eixo Y ou Z.
  * Destacar relações de taxonomia e herança (ex: sub-classes de doenças degenerativas).

---

## 3. Módulo Service (Padrões Facade, Factory e Serialização)

### `GraphBuilder` (`GraphBuilder.hpp`)
* **O que é:** Uma classe utilitária estática baseada no **Padrão Factory / Parser**.
* **Responsabilidade:**
  * Receber a *string* em formato JSON bruto vinda da API Web local/nuvem.
  * Parsear os nós e conexões e instanciar os objetos `Node` e `Edge` com seus respetivos ponteiros `std::shared_ptr`.
  * Montar e retornar o objeto `Graph` populado e pronto para processamento espacial.

### `GraphSerializer` (`GraphSerializer.hpp`)
* **O que é:** Uma classe utilitária estática de transformação de dados.
* **Responsabilidade:**
  * Extrair as coordenadas $(x, y, z)$ finais, cores e rótulos de todos os elementos armazenados na instância do `Graph`.
  * Serializar o estado do grafo processado em uma *string* JSON estruturada no formato esperado pelos clientes de renderização (Unity VR / Web Three.js).

### `SpatialEngineFacade` (`SpatialEngineFacade.hpp`)
* **O que é:** O ponto de entrada unificado da biblioteca, implementando o **Padrão de Projeto Facade (Fachada)**.
* **Responsabilidade:**
  * Ocultar a complexidade interna do motor (Criação de Grafo, Parseamento de JSON, Seleção de Estratégias e Serialização) atrás de uma interface simples de 4 métodos:
    1. `loadOntologyGraph(jsonInput)`: invoca o `GraphBuilder`.
    2. `setLayoutStrategy(strategy)`: altera a estratégia de layout em uso.
    3. `processLayout(iterations)`: executa o algoritmo de disposição física/matemática.
    4. `getRenderableJSON()`: invoca o `GraphSerializer` e devolve a resposta final.

---

## 4. Visão Geral do Fluxo de Execução

```text
 [JSON Bruto da API]
         │
         ▼
 1. GraphBuilder::buildFromJSON()          ──► Cria instâncias de Node, Edge e Graph
         │
         ▼
 2. SpatialEngineFacade                    ──► Armazena o Graph ativo
         │
         ▼
 3. ILayoutStrategy::applyLayout()         ──► Calcula as posições 3D (X, Y, Z) via Vector3D
         │
         ▼
 4. GraphSerializer::toJSON3D()            ──► Converte o Graph com posições em JSON
         │
         ▼
 [JSON 3D Final para Renderização no VR]