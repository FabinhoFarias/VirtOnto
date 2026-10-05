/** Tabela com as arestas no formato "origem — relação — destino". */
export default function EdgeTable({ edges, nodesById }) {
  // Usa o mapa para trocar o id pelo rótulo legível do nó.
  const labelOf = (id) => nodesById.get(id)?.label ?? `${id} (não encontrado)`;

  return (
    <section className="panel">
      <h2>Arestas</h2>
      <div className="table-scroll">
        <table>
          <thead>
            <tr>
              <th scope="col">Origem</th>
              <th scope="col">Relação</th>
              <th scope="col">Destino</th>
            </tr>
          </thead>
          <tbody>
            {edges.map((edge) => (
              <tr key={edge.id} className={edge.isBroken ? 'broken' : undefined}>
                <td>{labelOf(edge.source)}</td>
                <td className="relation">{edge.label}</td>
                <td>{labelOf(edge.target)}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </section>
  );
}