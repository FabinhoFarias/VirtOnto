import { Line } from '@react-three/drei';

/**
 * Desenha uma linha reta entre a origem e o destino de cada aresta.
 * Arestas quebradas (que apontam para um nó inexistente) são ignoradas,
 * porque não há posição para onde desenhar.
 */
export default function EdgeLines({ edges, nodesById }) {
  return (
    <group>
      {edges
        .filter((edge) => !edge.isBroken)
        .map((edge) => {
          const from = nodesById.get(edge.source).position;
          const to = nodesById.get(edge.target).position;
          return (
            <Line
              key={edge.id}
              points={[
                [from.x, from.y, from.z],
                [to.x, to.y, to.z],
              ]}
              color="#8b99ae"
              lineWidth={1.5}
              transparent
              opacity={0.6}
            />
          );
        })}
    </group>
  );
}