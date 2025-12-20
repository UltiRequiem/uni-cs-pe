# Resumen del Proyecto: Agente de Búsqueda Web IA

## Información General

**Título:** Agente de búsqueda web mediante inteligencia artificial

**Institución:** Universidad Nacional de Ingeniería (UNI)

**Curso:** Arquitectura de Computadoras - Grupo 2

**Periodo:** 2025-II

**Integrantes:**

- Bobadilla Camarena Eliaz Sebastian
- Cabello Quevedo Yaimar Alexis
- Flores Bautista Alexandra Noemi
- Vitor Quispe Emmanuelle Ethan

**Profesor:** Cesar Cruz

---

## Descripción del Proyecto

Sistema inteligente de búsqueda web que utiliza inteligencia artificial para:

- Comprender consultas en lenguaje natural
- Buscar información relevante en internet
- Procesar y sintetizar resultados
- Generar respuestas contextualizadas

### Tecnologías Principales

- **Framework:** Mastra AI
- **Modelos de IA:** OpenAI GPT-4o-mini, Google Gemini 2.5 Flash
- **API de Búsqueda:** Exa (optimizada para IA)
- **Lenguaje:** TypeScript + Node.js
- **Validación:** Zod

---

## Arquitectura Implementada

### 1. Tres Estrategias de Búsqueda

#### Estrategia 1: OpenAI Nativa

- Modelo: GPT-4o-mini
- Búsqueda: Herramienta nativa de OpenAI
- Ventaja: Integración directa, rápida

#### Estrategia 2: Google Gemini Nativa

- Modelo: Gemini 2.5 Flash
- Búsqueda: Google Search integrado
- Ventaja: Infraestructura de Google, muy rápida

#### Estrategia 3: Exa Personalizada

- Modelo: GPT-4o-mini
- Búsqueda: API de Exa (herramienta custom)
- Ventaja: Búsqueda semántica, control total, contenido completo

### 2. Componentes del Sistema

```
Usuario
   ↓
Mastra Framework
   ↓
Agentes (3 tipos)
   ↓
Herramientas de Búsqueda
   ↓
Web / APIs
```

---

## Estructura del Código

```
web-search-agent-ai-uni-pe/
│
├── src/
│   ├── mastra/
│   │   ├── agents/
│   │   │   ├── searchAgentOpenAI.ts    # Agente OpenAI
│   │   │   ├── searchAgentGemini.ts    # Agente Gemini
│   │   │   └── searchAgentExa.ts       # Agente Exa
│   │   ├── tools/
│   │   │   └── exaSearchTool.ts        # Herramienta Exa
│   │   └── index.ts                    # Config Mastra
│   ├── examples/
│   │   ├── simple-search.ts            # Ejemplo básico
│   │   └── compare-agents.ts           # Comparación
│   └── index.ts                        # Entrada principal
│
├── Documentación/
│   ├── README.md                       # Guía principal
│   ├── QUICKSTART.md                   # Inicio rápido
│   ├── ARCHITECTURE.md                 # Arquitectura detallada
│   ├── CONTRIBUTING.md                 # Guía de contribución
│   ├── PROJECT_SUMMARY.md              # Este archivo
│   └── informe.pdf                     # Documento de investigación
│
└── Configuración/
    ├── package.json                    # Dependencias
    ├── tsconfig.json                   # Config TypeScript
    ├── .env.example                    # Plantilla env vars
    └── .gitignore                      # Archivos ignorados
```

---

## Características Implementadas

### ✅ Funcionalidades Principales

1. **Búsqueda Web Inteligente**
   - Comprensión de lenguaje natural
   - Búsqueda semántica
   - Procesamiento contextual

2. **Múltiples Motores**
   - OpenAI con búsqueda nativa
   - Google Gemini con Google Search
   - Exa con búsqueda personalizada

3. **Herramienta Personalizada**
   - API de Exa integrada
   - Validación con Zod
   - Extracción de contenido completo
   - Configuración de número de resultados

4. **Ejemplos y Testing**
   - Ejemplo de búsqueda simple
   - Comparación de agentes
   - Interfaz visual (Mastra Studio)

5. **Documentación Completa**
   - README detallado en español
   - Guía de inicio rápido
   - Documentación de arquitectura
   - Guía de contribución para el equipo

### 🎯 Casos de Uso

1. **Investigación Académica**
   ```
   "¿Cuáles son los últimos avances en computación cuántica?"
   ```

2. **Noticias Actuales**
   ```
   "¿Qué pasó esta semana en el mundo de la IA?"
   ```

3. **Información Técnica**
   ```
   "Explica la arquitectura de un procesador moderno"
   ```

4. **Comparación**
   ```
   "Compara diferentes algoritmos de búsqueda"
   ```

---

## Comandos Disponibles

| Comando                   | Función                    |
| ------------------------- | -------------------------- |
| `npm install`             | Instalar dependencias      |
| `npm run dev`             | Ejecutar ejemplo principal |
| `npm run mastra:dev`      | Abrir interfaz visual      |
| `npm run example:simple`  | Ejemplo de búsqueda simple |
| `npm run example:compare` | Comparar los 3 agentes     |
| `npm run build`           | Compilar proyecto          |
| `npm start`               | Ejecutar versión compilada |

---

## Conceptos de Arquitectura de Computadoras

### 1. Niveles de Abstracción

```
Alto Nivel:    Aplicación TypeScript/Mastra
              ↓
Medio:        Node.js Runtime (V8)
              ↓
Sistema:      Sistema Operativo
              ↓
Hardware:     CPU + Memoria + Red
```

### 2. Procesamiento Distribuido

- **Cliente:** Máquina local ejecutando Node.js
- **Servidor:** APIs en la nube (OpenAI, Google, Exa)
- **Comunicación:** HTTP/HTTPS (REST)

### 3. Paralelismo

```typescript
// Procesamiento concurrente de consultas
await Promise.all([
  agentOpenAI.search(query),
  agentGemini.search(query),
  agentExa.search(query),
]);
```

### 4. Optimización

- **Cache:** Resultados frecuentes en memoria
- **Truncamiento:** Contenido limitado para eficiencia
- **Async/Await:** I/O no bloqueante
- **Lazy Loading:** Carga bajo demanda

---

## Métricas del Proyecto

### Código

- **Archivos TypeScript:** 8
- **Agentes:** 3
- **Herramientas Custom:** 1
- **Ejemplos:** 2
- **Líneas de Código:** ~500

### Documentación

- **Archivos Markdown:** 5
- **Páginas totales:** ~25
- **Ejemplos de código:** 20+

### Dependencias

- **Principales:** 6
- **Desarrollo:** 3
- **Total:** 450+ paquetes (con sub-dependencias)

---

## Roadmap Futuro

### Fase 1: Mejoras Básicas ✅

- [x] Implementar 3 agentes
- [x] Crear herramienta Exa
- [x] Documentación completa
- [x] Ejemplos funcionales

### Fase 2: Extensiones 🔄

- [ ] Agregar más proveedores (Bing, Brave)
- [ ] Implementar cache de resultados
- [ ] Agregar filtros avanzados
- [ ] Búsqueda en PDFs académicos

### Fase 3: Optimización 📋

- [ ] Testing automatizado
- [ ] Métricas de rendimiento
- [ ] Logging estructurado
- [ ] Manejo de errores mejorado

### Fase 4: Interfaz 📋

- [ ] CLI interactivo
- [ ] Dashboard web personalizado
- [ ] Visualización de resultados
- [ ] Historial de búsquedas

---

## Comparación de Agentes

| Aspecto           | OpenAI | Gemini   | Exa      |
| ----------------- | ------ | -------- | -------- |
| **Velocidad**     | ⚡⚡⚡ | ⚡⚡⚡⚡ | ⚡⚡     |
| **Control**       | ⭐⭐   | ⭐⭐     | ⭐⭐⭐⭐ |
| **Contenido**     | ⭐⭐⭐ | ⭐⭐⭐   | ⭐⭐⭐⭐ |
| **Precisión**     | ⭐⭐⭐ | ⭐⭐⭐⭐ | ⭐⭐⭐⭐ |
| **Configuración** | Fácil  | Fácil    | Media    |
| **Costo**         | $      | $        | $$       |

---

## Aspectos Técnicos Destacados

### 1. Type Safety

- TypeScript para prevención de errores
- Zod para validación en runtime
- Esquemas explícitos para entrada/salida

### 2. Modularidad

- Agentes independientes
- Herramientas reutilizables
- Fácil extensión

### 3. Async/Await

- Código no bloqueante
- Mejor performance
- Manejo de errores limpio

### 4. Validación

```typescript
inputSchema: z.object({
  query: z.string().min(1).max(200),
  numResults: z.number().min(1).max(10),
});
```

---

## Conclusiones

### Logros

✅ Sistema funcional de búsqueda web con IA ✅ Tres estrategias diferentes
implementadas ✅ Documentación completa en español ✅ Código modular y
extensible ✅ Ejemplos prácticos funcionando

### Aprendizajes

- Integración de APIs de IA
- Arquitectura de agentes inteligentes
- Procesamiento de lenguaje natural
- Desarrollo con TypeScript moderno
- Trabajo con frameworks de IA (Mastra)

### Aplicaciones Prácticas

- Investigación académica automatizada
- Asistentes virtuales inteligentes
- Sistemas de recomendación
- Análisis de información en tiempo real

---

## Enlaces Rápidos

- **GitHub:** https://github.com/UltiRequiem/web-search-agent-ai-uni-pe
- **README Principal:** [README.md](README.md)
- **Guía Rápida:** [QUICKSTART.md](QUICKSTART.md)
- **Arquitectura:** [ARCHITECTURE.md](ARCHITECTURE.md)
- **Contribución:** [CONTRIBUTING.md](CONTRIBUTING.md)

---

**Proyecto desarrollado para:** Universidad Nacional de Ingeniería Arquitectura
de Computadoras - 2025-II
