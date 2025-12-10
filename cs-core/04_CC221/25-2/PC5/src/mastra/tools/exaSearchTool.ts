import { createTool } from "@mastra/core/tools";
import z from "zod";
import Exa from "exa-js";

/**
 * Initialize Exa search client
 * Exa is a search engine built specifically for AI applications
 */
export const exa = new Exa(process.env.EXA_API_KEY);

/**
 * Web Search Tool using Exa API
 *
 * This tool provides semantic search capabilities with configurable filters
 * and the ability to retrieve full page contents.
 *
 * Features:
 * - Semantic search optimized for AI
 * - Live crawling for up-to-date results
 * - Configurable result count
 * - Full content extraction
 */
export const exaWebSearch = createTool({
  id: "exa-web-search",
  description: `Search the web using Exa's AI-optimized search engine.
  This tool performs semantic search and returns relevant results with full content.
  Use this when you need to find current information from the internet.`,
  inputSchema: z.object({
    query: z
      .string()
      .min(1)
      .max(200)
      .describe("The search query to find information about"),
    numResults: z
      .number()
      .min(1)
      .max(10)
      .optional()
      .default(3)
      .describe("Number of results to return (1-10)"),
  }),
  outputSchema: z.array(
    z.object({
      title: z.string().nullable().describe("The title of the web page"),
      url: z.string().describe("The URL of the web page"),
      content: z
        .string()
        .describe("The extracted text content from the page (truncated)"),
      publishedDate: z
        .string()
        .optional()
        .describe("The published date of the content"),
    })
  ),
  execute: async ({ context }) => {
    try {
      const response = await exa.search(context.query, {
        numResults: context.numResults || 3,
        useAutoprompt: true,
        contents: {
          text: true,
        },
      });

      return response.results.map((result) => {
        // Handle the result properly with type safety
        const resultWithText = result as typeof result & { text?: string };
        return {
          title: result.title ?? null,
          url: result.url,
          // Truncate content to first 1000 characters for efficiency
          content: (resultWithText.text || "No content available").slice(0, 1000),
          publishedDate: result.publishedDate,
        };
      });
    } catch (error) {
      console.error("Error in Exa search:", error);
      throw new Error(
        `Failed to search: ${error instanceof Error ? error.message : "Unknown error"}`
      );
    }
  },
});
