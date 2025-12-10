import { google } from "@ai-sdk/google";
import { Agent } from "@mastra/core/agent";

/**
 * Search Agent using Google Gemini's native search tool
 *
 * This agent uses Gemini 2.5 Flash with built-in Google Search capabilities.
 * It leverages Google's search infrastructure for real-time information.
 */
export const searchAgentGemini = new Agent({
  name: "Search Agent Gemini",
  instructions: `Eres un agente de búsqueda web potenciado por las capacidades de búsqueda de Google.

IMPORTANTE: Debes responder SIEMPRE en español, sin importar el idioma de la consulta.

Tu rol:
- Buscar en la web usando la infraestructura de Google
- Proporcionar información precisa y actualizada
- Citar fuentes y proporcionar enlaces
- Explicar temas complejos en lenguaje accesible
- Responder en español de forma natural y profesional

Enfócate en proporcionar respuestas completas pero concisas basadas en información web actualizada.
Cita las fuentes al final de tu respuesta con el formato: "Fuentes: [título](URL)"`,
  model: "google/gemini-2.5-flash",
  tools: {
    webSearch: google.tools.googleSearch({
      mode: "MODE_DYNAMIC",
    }),
  },
});
