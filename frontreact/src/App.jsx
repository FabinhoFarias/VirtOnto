import { useEffect, useState } from 'react';
import { loadGraph } from './services/graphLoader.js';
import GraphSummary from './components/GraphSummary.jsx';
import NodeTable from './components/NodeTable.jsx';
import EdgeTable from './components/EdgeTable.jsx';

// import.meta.env.BASE_URL garante que o caminho funcione também depois do deploy.
const SAMPLE_GRAPH_URL = `${import.meta.env.BASE_URL}data/sample-graph.json`;

export default function App() {
  // Três estados possíveis da tela: carregando, erro, ou com o grafo pronto.
  const [graph, setGraph] = useState(null);
  const [error, setError] = useState(null);

  // Roda uma vez quando o componente aparece na tela.
  useEffect(() => {
    loadGraph(SAMPLE_GRAPH_URL)
      .then(setGraph)
      .catch((err) => setError(err.message));
  }, []);

  return (
    <div className="app">
      <header className="app-header">
        <h1>VirtOnto</h1>
        <p className="subtitle">Dados do grafo de ontologia, antes da visualização 3D</p>
      </header>

      {error && (
        <p className="status error" role="alert">
          {error} Confira se o arquivo existe em public/data/.
        </p>
      )}
      {!error && !graph && <p className="status">Carregando grafo…</p>}

      {graph && (
        <main>
          <GraphSummary nodes={graph.nodes} edges={graph.edges} />
          <div className="panels">
            <NodeTable nodes={graph.nodes} />
            <EdgeTable edges={graph.edges} nodesById={graph.nodesById} />
          </div>
        </main>
      )}
    </div>
  );
}