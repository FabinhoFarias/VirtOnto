import { Canvas } from '@react-three/fiber';
import { OrbitControls } from '@react-three/drei';
import NodeSphere from './NodeSphere.jsx';
import EdgeLines from './EdgeLines.jsx';

/** A cena 3D: câmera, luzes, controles de órbita, esferas e arestas. */
export default function GraphScene({ graph }) {
  return (
    <Canvas camera={{ position: [0, 0, 28], fov: 50 }}>
      <color attach="background" args={['#17212f']} />
      <ambientLight intensity={0.6} />
      <directionalLight position={[10, 15, 10]} intensity={1.2} />

      {graph.nodes.map((node) => (
        <NodeSphere key={node.id} node={node} />
      ))}
      <EdgeLines edges={graph.edges} nodesById={graph.nodesById} />

      <axesHelper args={[3]} />
      <OrbitControls enableDamping />
    </Canvas>
  );
}