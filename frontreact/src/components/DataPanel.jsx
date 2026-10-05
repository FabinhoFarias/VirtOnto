import GraphSummary from './GraphSummary.jsx';
import NodeTable from './NodeTable.jsx';
import EdgeTable from './EdgeTable.jsx';

/** Painel "Ver dados": as tabelas da etapa 1, abertas por cima da cena. */
export default function DataPanel({ graph }) {
  return (
    <aside className="data-panel" aria-label="Dados do grafo">
      <GraphSummary nodes={graph.nodes} edges={graph.edges} />
      <div className="panels">
        <NodeTable nodes={graph.nodes} />
        <EdgeTable edges={graph.edges} nodesById={graph.nodesById} />
      </div>
    </aside>
  );
}