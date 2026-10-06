import { Html } from '@react-three/drei';

/**
 * Nome do nó flutuando logo acima da esfera, sempre virado para a tela.
 * zIndexRange limita a camada dos nomes, para o painel "Ver dados" poder ficar por cima.
 */
export default function NodeLabel({ node }) {
  const { x, y, z } = node.position;

  return (
    <Html position={[x, y + 1.1, z]} center zIndexRange={[10, 0]}>
      <span className="node-label">{node.label}</span>
    </Html>
  );
}