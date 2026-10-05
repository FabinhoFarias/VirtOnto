import { defineConfig } from 'vite';
import react from '@vitejs/plugin-react';

// Configuração do Vite: o plugin do React habilita JSX e recarregamento rápido.
export default defineConfig({
  plugins: [react()],
});