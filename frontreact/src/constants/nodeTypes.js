/**
 * Espelho do enum `NodeType` do C++ (CPP/include/model/Node.hpp).
 *
 * No C++ o enum é:
 *   enum class NodeType { CLASS, INDIVIDUAL, PROPERTY };
 * e o GraphSerializer converte para número com static_cast<int>,
 * então no JSON chega 0, 1 ou 2. Este objeto traduz esse número
 * de volta para algo legível na tela.
 *
 * IMPORTANTE: se a ordem do enum mudar no C++, tem que mudar aqui também.
 */
export const NODE_TYPES = {
  0: { key: 'CLASS', label: 'Classe', color: '#FFA500' },
  1: { key: 'INDIVIDUAL', label: 'Indivíduo', color: '#00FF00' },
  2: { key: 'PROPERTY', label: 'Propriedade', color: '#0000FF' },
};

/** Devolve as informações do tipo, ou um tipo "desconhecido" se o número for inválido. */
export function getNodeType(typeNumber) {
  return NODE_TYPES[typeNumber] ?? { key: 'UNKNOWN', label: 'Desconhecido', color: '#FFFFFF' };
}