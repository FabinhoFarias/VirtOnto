### Roteiro de Implementação: `Vector3D`

Para garantir o funcionamento inicial da engine sem sobrecarregar a etapa de fundamentos, divida a implementação dos membros em duas fases:

#### Foco Atual (Mínimo Essencial)
* **Atributos públicos:** `float x{0.0f}`, `float y{0.0f}`, `float z{0.0f}`.
* **Construtores:** Padrão (`= default`) e parametrizado `(float x, float y, float z)`.
* **`operator+`:** Soma vetorial componente a componente para aplicar deslocamentos ($P_{\text{novo}} = P_{\text{atual}} + \vec{v}$).
* **`operator-`:** Subtração vetorial para determinar a direção/afastamento entre dois nós no espaço.
* **`operator*`:** Multiplicação por escalar (`float`) para ajustar o peso ou a velocidade de movimento.
* **`distanceTo`:** Cálculo de distância euclidiana entre dois pontos ($\sqrt{\Delta x^2 + \Delta y^2 + \Delta z^2}$).

#### Fases Futuras (Física Avançada & Shaders)
* **`magnitude`:** Comprimento do vetor a partir da origem.
* **`normalized`:** Vetor unitário direcional (incluindo tratamento para divisão por zero).
* **`dot`:** Produto escalar para verificação de alinhamento e orientação espacial.