# Arquitectura del Sistema

## Diagrama de Arquitectura General

```
┌─────────────────────────────────────────────────────────────┐
│                         Usuario                              │
└─────────────────────┬───────────────────────────────────────┘
                      │ Consulta
                      ▼
┌─────────────────────────────────────────────────────────────┐
│                    Mastra Framework                          │
│  ┌───────────────────────────────────────────────────────┐  │
│  │              Capa de Agentes                          │  │
│  └───────────────────────────────────────────────────────┘  │
└─────────────────────┬───────────────────────────────────────┘
                      │
        ┌─────────────┼─────────────┐
        ▼             ▼             ▼
┌──────────────┐ ┌──────────────┐ ┌──────────────┐
│   OpenAI     │ │   Gemini     │ │   Exa API    │
│  GPT-4o-mini │ │ 2.5 Flash    │ │   Custom     │
│  (Native)    │ │  (Native)    │ │   Tool       │
└──────┬───────┘ └──────┬───────┘ └──────┬───────┘
       │                │                │
       └────────────────┼────────────────┘
                        ▼
                ┌──────────────┐
                │  Internet    │
                │  Web Search  │
                └──────────────┘
```

## Flujo de Datos

### 1. Flujo con Herramientas Nativas (OpenAI/Gemini)

```
Usuario → Consulta → Agente → Modelo LLM → Tool Nativa → Web
                                    ↓
Usuario ← Respuesta ← Agente ← Resultados procesados ←─┘
```

### 2. Flujo con Herramienta Personalizada (Exa)

```
Usuario → Consulta → Agente → Decisión de usar tool
                                    ↓
                           exaWebSearch Tool
                                    ↓
                              Exa API → Web
                                    ↓
                           Resultados extraídos
                                    ↓
Usuario ← Respuesta ← Modelo LLM procesa resultados
```

## Componentes del Sistema

### 1. **Capa de Presentación**
- CLI (src/index.ts)
- Mastra Studio (interfaz web)
- Ejemplos (src/examples/)

### 2. **Capa de Agentes** (src/mastra/agents/)

#### SearchAgentOpenAI
```typescript
Input: Consulta de usuario
Process: GPT-4o-mini + webSearch tool
Output: Respuesta contextualizada con información web
```

#### SearchAgentGemini
```typescript
Input: Consulta de usuario
Process: Gemini 2.5 Flash + googleSearch tool
Output: Respuesta usando infraestructura de Google
```

#### SearchAgentExa
```typescript
Input: Consulta de usuario
Process: GPT-4o-mini + exaWebSearch custom tool
Output: Respuesta con búsqueda semántica optimizada
```

### 3. **Capa de Herramientas** (src/mastra/tools/)

#### exaWebSearch Tool
```typescript
Input Schema:
  - query: string (1-200 caracteres)
  - numResults: number (1-10, default: 3)

Output Schema:
  - title: string
  - url: string
  - content: string (truncado a 1000 chars)
  - publishedDate: string (opcional)

Proceso:
  1. Recibe consulta del agente
  2. Llama a Exa API con livecrawl="always"
  3. Extrae contenido de páginas web
  4. Trunca contenido para eficiencia
  5. Retorna array de resultados
```

### 4. **Capa de Integración**
- Mastra Core (orquestación)
- AI SDK (abstracciones de modelos)
- APIs externas (OpenAI, Google, Exa)

## Arquitectura de Computadoras: Perspectiva de Hardware

### Stack Completo

```
┌────────────────────────────────────────┐
│     Aplicación (Node.js/TypeScript)    │ ← Software de alto nivel
├────────────────────────────────────────┤
│     Runtime de JavaScript (V8)         │ ← Máquina virtual
├────────────────────────────────────────┤
│     Sistema Operativo (macOS/Linux)    │ ← Gestión de recursos
├────────────────────────────────────────┤
│     CPU + Memoria + Red                │ ← Hardware físico
└────────────────────────────────────────┘
```

### Procesamiento de una Consulta

```
1. CPU: Ejecuta código JavaScript/TypeScript
   ↓
2. Memoria RAM: Almacena estado del agente
   ↓
3. Interfaz de Red: Envía request HTTP a API
   ↓
4. GPU (en servidores remotos): Procesa modelo LLM
   ↓
5. Memoria: Cache de resultados
   ↓
6. CPU: Procesa respuesta y genera output
```

## Patrones de Diseño Utilizados

### 1. **Strategy Pattern** (Agentes)
Diferentes estrategias de búsqueda encapsuladas en agentes intercambiables.

### 2. **Factory Pattern** (createTool)
Creación de herramientas con configuración estandarizada.

### 3. **Proxy Pattern** (AI SDK)
Abstracción sobre diferentes proveedores de LLM.

### 4. **Adapter Pattern** (Exa Tool)
Adaptación de API externa a interfaz de Mastra.

## Consideraciones de Rendimiento

### Latencia
```
OpenAI Native:  ~2-5 segundos
Gemini Native:  ~1-3 segundos
Exa Custom:     ~3-7 segundos (incluye crawling)
```

### Escalabilidad
- **Horizontal:** Múltiples instancias con balanceo de carga
- **Vertical:** Más memoria/CPU para procesamiento paralelo
- **Cache:** Almacenar resultados frecuentes

### Optimizaciones
1. **Truncamiento de contenido:** Reduce payload y tiempo de procesamiento
2. **Limit de resultados:** Configurable (1-10 results)
3. **Async/Await:** I/O no bloqueante
4. **Streaming:** Posible con Mastra para respuestas incrementales

## Seguridad

### Protección de Claves API
- Variables de entorno (no hardcoded)
- .env en .gitignore
- Validación de entrada con Zod

### Validación de Datos
```typescript
inputSchema: z.object({
  query: z.string().min(1).max(200),
  numResults: z.number().min(1).max(10)
})
```

## Extensibilidad

### Agregar un Nuevo Proveedor de Búsqueda

```typescript
// 1. Crear herramienta
export const newSearchTool = createTool({
  id: "new-search",
  description: "...",
  inputSchema: z.object({ ... }),
  outputSchema: z.object({ ... }),
  execute: async ({ context }) => { ... }
});

// 2. Crear agente
export const searchAgentNew = new Agent({
  name: "New Search Agent",
  instructions: "...",
  model: "openai/gpt-4o-mini",
  tools: { newSearchTool }
});

// 3. Registrar en Mastra
export const mastra = new Mastra({
  agents: {
    searchAgentOpenAI,
    searchAgentGemini,
    searchAgentExa,
    searchAgentNew  // ← Nuevo agente
  }
});
```

## Referencias de Arquitectura

- **Mastra Framework:** Orquestación de agentes
- **AI SDK:** Abstracción de modelos
- **Zod:** Validación en tiempo de ejecución
- **TypeScript:** Type safety en tiempo de compilación
