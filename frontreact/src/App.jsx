import { useEffect, useState } from 'react';
import { loadGraph } from './services/graphLoader.js';
import DataPanel from './components/DataPanel.jsx';
import GraphScene from './components/scene/GraphScene.jsx';

// import.meta.env.BASE_URL garante que o caminho funcione também depois do deploy.
const SAMPLE_GRAPH_URL = `${import.meta.env.BASE_URL}data/sample-graph.json`;

export default function App() {
  const [graph, setGraph] = useState(null);
  const [error, setError] = useState(null);
  // Controla se o painel de tabelas está aberto ou fechado.
  const [showData, setShowData] = useState(false);

  useEffect(() => {
    loadGraph(SAMPLE_GRAPH_URL)
      .then(setGraph)
      .catch((err) => setError(err.message));
  }, []);

  return (
    <div className="app">
      <header className="app-header">
        <h1>VirtOnto</h1>
        {graph && (
          <button type="button" onClick={() => setShowData(!showData)}>
            {showData ? 'Fechar dados' : 'Ver dados'}
          </button>
        )}
      </header>

      <main className="scene-area">
        {error && (
          <p className="status error" role="alert">
            {error} Confira se o arquivo existe em public/data/.
          </p>
        )}
        {!error && !graph && <p className="status">Carregando grafo…</p>}
        {graph && <GraphScene graph={graph} />}
        {graph && showData && <DataPanel graph={graph} />}
      </main>
    </div>
  );
}