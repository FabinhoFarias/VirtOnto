import { loadGraph } from './services/graphLoader.js';

// Teste provisório: carrega o grafo e mostra o resultado no console (F12).
loadGraph('/data/sample-graph.json')
  .then((graph) => console.log('Grafo carregado:', graph))
  .catch((error) => console.error('Erro:', error.message));

export default function App() {
  return <h1>VirtOnto funcionando. Abra o console (F12).</h1>;
}