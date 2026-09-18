# Arquitetura e Especificação de Classes — VirtOnto 3D Engine

Este documento descreve a responsabilidade de cada classe, interface e método da engine espacial 3D em C++.

---

## 1. Camada de Modelo (`virtonto::model`)

### **`Vector3D`** (`struct`)
Estrutura matemática para representação de posições e vetores no espaço tridimensional.
* **`distanceTo(const Vector3D& other) const noexcept`**: Calcula a distância euclidiana em 3D até outro ponto.
* **`operator+(const Vector3D& other) const noexcept`**: Gera um novo vetor resultante da soma elemento a elemento.
* **`operator-(const Vector3D& other) const noexcept`**: Gera um novo vetor resultante da subtração elemento a elemento.
* **`operator*(float scalar) const noexcept`**: Multiplica o vetor por um valor escalar.
* **`operator+=(const Vector3D& other) noexcept`**: Soma as coordenadas de outro vetor diretamente na instância atual.
* **`operator*=(float scalar) noexcept`**: Escala as coordenadas do vetor atual por um fator numérico.
* **`operator*=(const Vector3D& other) noexcept`**: Aplica o produto de Hadamard (multiplicação componente a componente).

---

### **`OntologyElement`** (`class` abstrata base)
Classe base abstrata para todos os elementos gerenciados pelo grafo ontológico.
* **`OntologyElement(std::string id, std::string label)`**: Construtor base que inicializa o identificador único e o rótulo.
* **`virtual ~OntologyElement()`**: Destrutor virtual para garantir desalocação polimórfica correta nas derivadas.
* **`getId() const noexcept`**: Retorna o ID único do elemento.
* **`getLabel() const noexcept`**: Retorna o rótulo textual do elemento.
* **`virtual std::string getDisplayColor() const = 0`**: Método abstrato puro para consulta da cor de exibição visual em formato Hexadecimal.

---

### **`NodeType`** (`enum class`)
Enumerador forte (*Scoped Enum*) que define os papéis ontológicos dos nós:
* `CLASS`: Representa conceitos/classes na ontologia.
* `INDIVIDUAL`: Representa instâncias de classes.
* `PROPERTY`: Representa atributos ou predicados.

---

### **`Node`** (`class final` : `public OntologyElement`)
Representa um vértice/nó dentro do espaço 3D.
* **`Node(std::string id, std::string label, NodeType type)`**: Inicializa o nó passando `id` e `label` à classe base `OntologyElement` e definindo o tipo.
* **`getType() const noexcept`**: Retorna o `NodeType` do nó.
* **`getPosition() const noexcept` / `setPosition(const Vector3D& position) noexcept`**: Consulta e atualiza as coordenadas 3D no espaço.
* **`getVelocity() const noexcept` / `setVelocity(const Vector3D& velocity) noexcept`**: Consulta e atualiza o vetor de velocidade (utilizado por algoritmos de simulação física).
* **`getMass() const noexcept`**: Retorna a massa do nó.
* **`getDisplayColor() const override`**: Sobrescreve o método base, mapeando cores específicas para cada tipo de nó (`#FFA500` para `CLASS`, `#00FF00` para `INDIVIDUAL`, `#0000FF` para `PROPERTY`).

---

### **`Edge`** (`class` : `public OntologyElement`)
Representa as conexões/arestas entre dois nós no espaço.
* **`Edge(std::string id, std::string label, std::string sourceId, std::string targetId, float weight)`**: Inicializa a aresta com seus nós de origem, destino e peso numérico.
* **`getSourceId() const noexcept`**: Retorna o ID do nó de origem.
* **`getTargetId() const noexcept`**: Retorna o ID do nó de destino.
* **`getWeight() const noexcept`**: Retorna o peso/intensidade da relação.
* **`getDisplayColor() const override`**: Sobrescreve o método base com a cor padrão da conexão (`#888888`).

---

### **`Graph`** (`class`)
Contêiner de dados do modelo espacial que armazena os vértices e conexões.
* **`addNode(Node node)`**: Insere um nó na coleção do grafo.
* **`addEdge(Edge edge)`**: Insere uma aresta na coleção do grafo.
* **`getNodes() const noexcept` / `getNodes() noexcept`**: Retornam referências para a lista de nós (leitura contínua ou modificação).
* **`getEdges() const noexcept`**: Retorna a lista de arestas para consulta.

---

## 2. Camada de Algoritmos (`virtonto::algorithm`)

### **`ILayoutStrategy`** (`interface`)
Interface que define o contrato para algoritmos de cálculo de posicionamento (Padrão Strategy).
* **`virtual void applyLayout(model::Graph& graph) = 0`**: Executa a reorganização das posições dos nós do grafo recebido.

---

### **`ForceDirectedLayout3D`** (`class` : `public ILayoutStrategy`)
* **`applyLayout(model::Graph& graph) override`**: Aplica simulação física de repulsão entre os nós com base na distância, ajustando velocidades e amortecimento.

---

### **`SphericalLayout3D`** (`class` : `public ILayoutStrategy`)
* **`applyLayout(model::Graph& graph) override`**: Distribui os nós de maneira uniforme na superfície de uma esfera 3D utilizando a espiral de Fibonacci.

---

### **`HierarchicalLayout3D`** (`class` : `public ILayoutStrategy`)
* **`applyLayout(model::Graph& graph) override`**: Distribui os nós em planos horizontais paralelos (camadas $Y$) agrupados pelo seu tipo `NodeType`.

---

## 3. Camada de Serviços (`virtonto::service`)

### **`GraphBuilder`** (`class`)
Implementa o padrão *Builder* para construção fluente de grafos complexos.
* **`addNode(...)`**: Adiciona um nó ao grafo interno e retorna a referência `*this` para encadeamento.
* **`addEdge(...)`**: Adiciona uma aresta ao grafo interno e retorna a referência `*this`.
* **`build()`**: Retorna a instância completa do `Graph` construído por movimentação (*move semantics*).

---

### **`GraphSerializer`** (`class`)
Responsável pela conversão do modelo para formatos de persistência/rede.
* **`static std::string serializeToJson(const model::Graph& graph)`**: Varre o grafo e exporta os nós, cores e coordenadas 3D em uma string formatada em JSON.

---

### **`SpatialEngineFacade`** (`class`)
Interface simplificada para o cliente controlar o motor espacial (Padrão Facade).
* **`SpatialEngineFacade(std::unique_ptr<algorithm::ILayoutStrategy> layoutStrategy)`**: Constrói o serviço definindo o algoritmo de posicionamento inicial.
* **`setLayoutStrategy(...)`**: Permite alternar dinamicamente o algoritmo de posicionamento em tempo de execução.
* **`updateLayout(model::Graph& graph)`**: Dispara a atualização das posições dos nós usando a estratégia configurada no momento.
* **`exportGraphState(const model::Graph& graph)`**: Delega a serialização do grafo para o `GraphSerializer` e retorna a string resultante.