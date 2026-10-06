import { NODE_TYPES } from '../constants/nodeTypes.js';

/** Legenda fixa no canto da cena explicando cores e linhas. */
export default function Legend() {
  return (
    <ul className="legend" aria-label="Legenda">
      {Object.values(NODE_TYPES).map((type) => (
        <li key={type.key}>
          <span className="legend-swatch" style={{ background: type.color }} aria-hidden="true" />
          {type.label}
        </li>
      ))}
      <li>
        <span className="legend-edge" aria-hidden="true" />
        Relação
      </li>
    </ul>
  );
}