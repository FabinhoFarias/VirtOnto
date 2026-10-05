/** Formata um número com 2 casas decimais para mostrar as coordenadas. */
const fmt = (value) => value.toFixed(2);

/** Tabela com todos os nós: cor, rótulo, tipo, id e posição (x, y, z). */
export default function NodeTable({ nodes }) {
  return (
    <section className="panel">
      <h2>Nós</h2>
      <div className="table-scroll">
        <table>
          <thead>
            <tr>
              <th scope="col">Rótulo</th>
              <th scope="col">Tipo</th>
              <th scope="col">Id</th>
              <th scope="col" className="num">x</th>
              <th scope="col" className="num">y</th>
              <th scope="col" className="num">z</th>
            </tr>
          </thead>
          <tbody>
            {nodes.map((node) => (
              <tr key={node.id}>
                <td>
                  <span className="swatch" style={{ background: node.color }} aria-hidden="true" />
                  {node.label}
                </td>
                <td>{node.typeInfo.label}</td>
                <td className="muted">{node.id}</td>
                <td className="num">{fmt(node.position.x)}</td>
                <td className="num">{fmt(node.position.y)}</td>
                <td className="num">{fmt(node.position.z)}</td>
              </tr>
            ))}
          </tbody>
        </table>
      </div>
    </section>
  );
}