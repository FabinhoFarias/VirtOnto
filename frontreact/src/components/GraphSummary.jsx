import { NODE_TYPES } from '../constants/nodeTypes.js';

/** Mostra quantos nós de cada tipo existem e quantas arestas o grafo tem. */
export default function GraphSummary({ nodes, edges }) {
  const countsByType = Object.entries(NODE_TYPES).map(([typeNumber, info]) => ({
    ...info,
    count: nodes.filter((node) => node.type === Number(typeNumber)).length,
  }));
  const brokenEdges = edges.filter((edge) => edge.isBroken).length;

  return (
    <section className="summary" aria-label="Resumo do grafo">
      <p className="summary-total">
        <strong>{nodes.length}</strong> nós e <strong>{edges.length}</strong> arestas
      </p>
      <ul className="summary-types">
        {countsByType.map((type) => (
          <li key={type.key}>
            <span className="swatch" style={{ background: type.color }} aria-hidden="true" />
            {type.count} {type.label.toLowerCase()}
            {type.count === 1 ? '' : 's'}
          </li>
        ))}
      </ul>
      {brokenEdges > 0 && (
        <p className="summary-warning">
          {brokenEdges} aresta(s) apontam para nós que não existem no JSON.
        </p>
      )}
    </section>
  );
}