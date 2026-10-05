/** Uma esfera 3D representando um nó do grafo. */
export default function NodeSphere({ node }) {
  const { x, y, z } = node.position;

  return (
    <mesh position={[x, y, z]}>
      <sphereGeometry args={[0.6, 32, 32]} />
      <meshStandardMaterial color={node.color} />
    </mesh>
  );
}