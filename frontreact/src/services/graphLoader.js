import { getNodeType } from '../constants/nodeTypes.js';

/**
 * Responsável por buscar o JSON do grafo e prepará-lo para a interface.
 *
 * Hoje ele lê um arquivo estático (public/data/sample-graph.json).
 * Na etapa 5 este será o único arquivo que muda: em vez de `fetch`,
 * vamos chamar o motor C++ compilado para WebAssembly.
 */

export async function loadGraph(url) {
  const response = await fetch(url);
  if (!response.ok) {
    throw new Error(`Não foi possível carregar ${url} (HTTP ${response.status}).`);
  }
  const raw = await response.json();
  return normalizeGraph(raw);
}

/**
 * Confere o formato do JSON e cria estruturas auxiliares.
 * Formato esperado (o mesmo do GraphSerializer::toJSON3D):
 *   nodes: [{ id, label, type, color, x, y, z }]
 *   edges: [{ id, source, target, label }]
 */
export function normalizeGraph(raw) {
  if (!raw || !Array.isArray(raw.nodes) || !Array.isArray(raw.edges)) {
    throw new Error('JSON inválido: era esperado um objeto com as listas "nodes" e "edges".');
  }

  const nodes = raw.nodes.map((node) => ({
    id: String(node.id),
    label: node.label || String(node.id),
    type: Number(node.type),
    typeInfo: getNodeType(Number(node.type)),
    color: node.color || getNodeType(Number(node.type)).color,
    position: { x: Number(node.x) || 0, y: Number(node.y) || 0, z: Number(node.z) || 0 },
  }));

  // Mapa id -> nó, parecido com o std::unordered_map do Graph em C++.
  const nodesById = new Map(nodes.map((node) => [node.id, node]));

  const edges = raw.edges.map((edge) => ({
    id: String(edge.id),
    source: String(edge.source),
    target: String(edge.target),
    label: edge.label || '',
    // Marca arestas que apontam para nós que não existem (útil para achar bugs no backend).
    isBroken: !nodesById.has(String(edge.source)) || !nodesById.has(String(edge.target)),
  }));

  return { nodes, edges, nodesById };
}