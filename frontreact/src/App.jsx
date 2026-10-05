import { getNodeType } from './constants/nodeTypes.js';

export default function App() {
  return (
    <div>
      <h1>VirtOnto funcionando</h1>
      <p>Tipo 0: {getNodeType(0).label}</p>
      <p>Tipo 1: {getNodeType(1).label}</p>
      <p>Tipo 2: {getNodeType(2).label}</p>
      <p>Tipo 7: {getNodeType(7).label}</p>
    </div>
  );
}