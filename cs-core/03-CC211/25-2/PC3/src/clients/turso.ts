import { env } from "@/env";
import { createClient } from "@libsql/client";

export const turso = createClient({
  url: env.TURSO_DATABASE_URL,
  authToken: env.TURSO_AUTH_TOKEN,
});
