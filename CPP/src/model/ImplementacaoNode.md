### Roteiro de Implementação: `NodeType`

* **Arquivo:** `CPP/include/model/NodeType.hpp`
* **Tipo:** `enum class` contendo as opções: `CLASS`, `INDIVIDUAL`, `PROPERTY`.
* **Uso no Projeto:** 
  * Armazenado como um atributo privado dentro da classe `Node`.
  * Utilizado dentro do método `Node::getDisplayColor()` para mapear cores distintas (ex: Laranja para `CLASS`, Verde para `INDIVIDUAL`, Azul para `PROPERTY`).
  * Impede erros de atribuição inválida via verificação rigorosa em tempo de compilação (*Type Safety*).