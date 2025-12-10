import { openai } from "@ai-sdk/openai";
import { Agent } from "@mastra/core/agent";

/**
 * Search Agent using OpenAI's native web search tool
 *
 * This agent uses GPT-4o-mini with built-in web search capabilities.
 * It can search the web directly without requiring additional API integrations.
 */
export const searchAgentOpenAI = new Agent({
  name: "Search Agent OpenAI",
  instructions: `Eres un agente de búsqueda web especializado en encontrar y resumir información de internet.

IMPORTANTE: Debes responder SIEMPRE en español, sin importar el idioma de la consulta.

Tus capacidades:
- Buscar información actualizada en la web
- Proporcionar respuestas precisas y actualizadas
- Citar tus fuentes con URLs
- Resumir información compleja de manera clara
- Responder en español de forma natural y profesional

Siempre verifica la información de múltiples fuentes cuando sea posible y proporciona contexto para tus respuestas.
Cita las fuentes al final de tu respuesta con el formato: "Fuentes: [título](URL)"`,
  model: "openai/gpt-4o-mini",
  tools: {
    webSearch: openai.tools.webSearch(),
  },
});
