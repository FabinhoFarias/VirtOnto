import { Canvas } from '@react-three/fiber';
import { OrbitControls } from '@react-three/drei';
import NodeSphere from './NodeSphere.jsx';

/** A cena 3D: câmera, luzes, controles de órbita e uma esfera por nó. */
export default function GraphScene({ nodes }) {
  return (
    <Canvas camera={{ position: [0, 0, 28], fov: 50 }}>
      <color attach="background" args={['#17212f']} />
      <ambientLight intensity={0.6} />
      <directionalLight position={[10, 15, 10]} intensity={1.2} />

      {nodes.map((node) => (
        <NodeSphere key={node.id} node={node} />
      ))}

      <axesHelper args={[3]} />
      <OrbitControls enableDamping />
    </Canvas>
  );
}