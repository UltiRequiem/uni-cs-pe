import { Mastra } from "@mastra/core";
import { searchAgentOpenAI } from "./agents/searchAgentOpenAI";
import { searchAgentGemini } from "./agents/searchAgentGemini";
import { searchAgentExa } from "./agents/searchAgentExa";

/**
 * Main Mastra instance
 *
 * This configures the Mastra framework with all available search agents:
 * - searchAgentOpenAI: Uses OpenAI's native web search
 * - searchAgentGemini: Uses Google Gemini's native search
 * - searchAgentExa: Uses custom Exa API integration
 */
export const mastra = new Mastra({
  agents: {
    searchAgentOpenAI,
    searchAgentGemini,
    searchAgentExa,
  },
});
