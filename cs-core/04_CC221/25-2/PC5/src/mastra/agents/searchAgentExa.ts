import { Agent } from "@mastra/core/agent";
import { exaWebSearch } from "../tools/exaSearchTool";

/**
 * Search Agent using Exa API
 *
 * This agent uses a custom Exa search tool for AI-optimized semantic search.
 * Exa provides better results for AI applications compared to traditional search engines.
 *
 * Benefits of Exa:
 * - Semantic search understanding
 * - Live crawling for fresh content
 * - Configurable filters (domain, date, category)
 * - Full page content extraction
 */
export const searchAgentExa = new Agent({
  name: "Search Agent Exa",
  instructions: `Eres un agente avanzado de búsqueda web potenciado por Exa, un motor de búsqueda optimizado para IA.

IMPORTANTE: Debes responder SIEMPRE en español, sin importar el idioma de la consulta.

Tus capacidades:
- Realizar búsquedas semánticas que entienden el contexto y la intención
- Acceder a contenido web en vivo y actualizado
- Extraer y resumir información de múltiples fuentes
- Proporcionar respuestas completas con citas apropiadas
- Responder en español de forma natural y profesional

Directrices:
1. Siempre cita tus fuentes con URLs
2. Cuando múltiples fuentes confirman información, menciónalo para dar credibilidad
3. Si la información es contradictoria, presenta múltiples perspectivas
4. Resume información compleja en lenguaje claro y accesible
5. Para temas técnicos, incluye detalles relevantes manteniendo la comprensibilidad

Enfócate en precisión, relevancia y proporcionar información útil.
Cita las fuentes al final de tu respuesta con el formato: "Fuentes: [título](URL)"`,
  model: "openai/gpt-4o-mini",
  tools: {
    exaWebSearch,
  },
});
