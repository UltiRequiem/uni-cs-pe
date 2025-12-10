# Agente de Búsqueda Web mediante Inteligencia Artificial

**Universidad Nacional de Ingeniería**
**Curso:** Arquitectura de Computadoras
**Grupo:** 2

## Integrantes

- Bobadilla Camarena Eliaz Sebastian
- Cabello Quevedo Yaimar Alexis
- Flores Bautista Alexandra Noemi
- Vitor Quispe Emmanuelle Ethan

**Profesor:** Cesar Cruz
**Periodo Académico:** 2025-II

---

## Descripción del Proyecto

Este proyecto implementa un **agente de búsqueda web inteligente** basado en inteligencia artificial, capaz de buscar información en internet, procesarla y presentar resultados relevantes de manera coherente y contextualizada.

El sistema utiliza el framework **Mastra** junto con modelos de lenguaje avanzados (OpenAI GPT-4o-mini y Google Gemini) para proporcionar capacidades de búsqueda semántica y generación de respuestas naturales.

### Características Principales

- **Búsqueda Semántica:** Comprende el contexto y la intención detrás de las consultas
- **Múltiples Motores de Búsqueda:** Integración con herramientas nativas de OpenAI, Google y la API de Exa
- **Resultados en Tiempo Real:** Acceso a información actualizada de la web
- **Procesamiento de Lenguaje Natural:** Genera respuestas coherentes y contextualizadas
- **Arquitectura Modular:** Fácil de extender y mantener

---

## Arquitectura del Sistema

El proyecto implementa tres agentes diferentes, cada uno con distintas estrategias de búsqueda:

### 1. Search Agent OpenAI

Utiliza las herramientas nativas de búsqueda web de GPT-4o-mini.

**Ubicación:** [src/mastra/agents/searchAgentOpenAI.ts](src/mastra/agents/searchAgentOpenAI.ts)

### 2. Search Agent Gemini

Aprovecha las capacidades de búsqueda integradas de Google Gemini 2.5 Flash.

**Ubicación:** [src/mastra/agents/searchAgentGemini.ts](src/mastra/agents/searchAgentGemini.ts)

### 3. Search Agent Exa

Usa una integración personalizada con la API de Exa, un motor de búsqueda optimizado para aplicaciones de IA.

**Ubicación:** [src/mastra/agents/searchAgentExa.ts](src/mastra/agents/searchAgentExa.ts)

**Herramienta personalizada:** [src/mastra/tools/exaSearchTool.ts](src/mastra/tools/exaSearchTool.ts)

---

## Requisitos Previos

- **Node.js:** v20.0 o superior
- **npm** o **yarn**
- **Docker** (opcional, para ejecución en contenedores)
- Claves API de al menos uno de los siguientes proveedores:
  - OpenAI (para GPT-4o-mini)
  - Google AI (para Gemini)
  - Exa (para búsqueda personalizada)

---

## Instalación

### Opción 1: Instalación Local (Recomendado para desarrollo)

### 1. Clonar el repositorio

```bash
git clone https://github.com/UltiRequiem/web-search-agent-ai-uni-pe.git
cd web-search-agent-ai-uni-pe
```

### 2. Instalar dependencias

```bash
npm install
```

### 3. Configurar variables de entorno

Copia el archivo `.env.example` a `.env`:

```bash
cp .env.example .env
```

Luego edita el archivo `.env` y agrega tus claves API:

```env
# OpenAI API Key
OPENAI_API_KEY=tu_clave_openai

# Google AI API Key (para Gemini)
GOOGLE_GENERATIVE_AI_API_KEY=tu_clave_google

# Exa API Key
EXA_API_KEY=tu_clave_exa
```

#### Obtener las claves API:

- **OpenAI:** https://platform.openai.com/api-keys
- **Google AI:** https://aistudio.google.com/app/apikey
- **Exa:** https://exa.ai/

### Opción 2: Instalación con Docker (Recomendado para producción)

Si prefieres usar Docker, consulta la [Guía de Docker](DOCKER.md) para instrucciones detalladas.

```bash
# Desarrollo con Docker
docker-compose up web-search-agent-dev

# Producción con Docker
docker-compose up web-search-agent
```

---

## Uso

### Modo 1: Ejecutar un ejemplo rápido

El archivo [src/index.ts](src/index.ts) contiene un ejemplo de uso que puedes ejecutar directamente:

```bash
npm run dev
```

Por defecto, usa el agente de OpenAI. Puedes cambiar al agente de Gemini o Exa editando el archivo y descomentando la opción deseada.

### Modo 2: Usar Mastra Studio (Interfaz Visual)

Mastra incluye una interfaz web para probar los agentes interactivamente:

```bash
npm run mastra:dev
```

Esto abrirá una interfaz web en `http://localhost:3000` donde podrás:

- Seleccionar entre los diferentes agentes
- Hacer consultas en tiempo real
- Ver los resultados de manera interactiva

### Modo 3: Compilar y ejecutar en producción

```bash
npm run build
npm start
```

---

## Estructura del Proyecto

```
web-search-agent-ai-uni-pe/
├── src/
│   ├── mastra/
│   │   ├── agents/
│   │   │   ├── searchAgentOpenAI.ts    # Agente con búsqueda nativa OpenAI
│   │   │   ├── searchAgentGemini.ts    # Agente con búsqueda nativa Gemini
│   │   │   └── searchAgentExa.ts       # Agente con API personalizada Exa
│   │   ├── tools/
│   │   │   └── exaSearchTool.ts        # Herramienta personalizada Exa
│   │   └── index.ts                    # Configuración Mastra
│   └── index.ts                        # Punto de entrada principal
├── dist/                               # Código compilado (generado)
├── informe.pdf                         # Documento de investigación
├── .env.example                        # Plantilla de variables de entorno
├── .gitignore                          # Archivos ignorados por Git
├── package.json                        # Configuración del proyecto
├── tsconfig.json                       # Configuración TypeScript
└── README.md                           # Este archivo
```

---

## Fundamento Teórico

### Agente Inteligente

Un agente inteligente es un programa que percibe su entorno mediante sensores y actúa sobre él con el objetivo de maximizar su rendimiento. En este proyecto, el agente percibe consultas del usuario y actúa realizando búsquedas web y generando respuestas.

### Web Crawling e Indexación

El proceso de rastreo web (web crawling) implica navegar automáticamente por páginas web siguiendo enlaces. La indexación organiza esta información para que pueda ser buscada eficientemente.

### Procesamiento del Lenguaje Natural (NLP)

Los modelos de lenguaje utilizados en este proyecto son capaces de:

- Entender el contexto de las consultas
- Generar respuestas coherentes
- Resumir información compleja
- Mantener conversaciones naturales

### Arquitectura Cliente-Servidor

El sistema sigue un modelo cliente-servidor donde:

- **Cliente:** El usuario que hace consultas
- **Servidor:** El agente de IA que procesa las solicitudes
- **APIs externas:** Servicios de búsqueda (OpenAI, Google, Exa)

---

## Ejemplos de Uso

### Ejemplo 1: Consulta Técnica

```typescript
const result = await mastra.agents.searchAgentOpenAI.text({
  messages: [
    {
      role: "user",
      content: "¿Cuáles son los últimos avances en inteligencia artificial?",
    },
  ],
});

console.log(result.text);
```

### Ejemplo 2: Búsqueda con Exa (más control)

```typescript
const result = await mastra.agents.searchAgentExa.text({
  messages: [
    {
      role: "user",
      content: "Busca información sobre arquitectura de computadoras moderna",
    },
  ],
});
```

---

## Tecnologías Utilizadas

- **[Mastra](https://mastra.ai/):** Framework para construcción de agentes de IA
- **[OpenAI GPT-4o-mini](https://platform.openai.com/):** Modelo de lenguaje con búsqueda web integrada
- **[Google Gemini 2.5 Flash](https://ai.google.dev/):** Modelo de lenguaje de Google con capacidades de búsqueda
- **[Exa](https://exa.ai/):** Motor de búsqueda optimizado para aplicaciones de IA
- **TypeScript:** Lenguaje de programación con tipado estático
- **Node.js:** Runtime de JavaScript
- **Zod:** Validación de esquemas

---

## Desarrollo y Extensión

### Agregar un nuevo agente

1. Crea un archivo en `src/mastra/agents/`
2. Define el agente usando la clase `Agent`
3. Regístralo en `src/mastra/index.ts`

### Crear una herramienta personalizada

1. Crea un archivo en `src/mastra/tools/`
2. Usa `createTool` para definir la herramienta
3. Define el esquema de entrada/salida con Zod
4. Implementa la función `execute`
5. Importa y agrega la herramienta a un agente

---

## Comparación de Estrategias

| Característica     | OpenAI Native  | Gemini Native  | Exa Custom          |
| ------------------ | -------------- | -------------- | ------------------- |
| Configuración      | Simple         | Simple         | Requiere API key    |
| Control            | Limitado       | Limitado       | Alto                |
| Filtros            | No             | No             | Sí (dominio, fecha) |
| Contenido completo | Limitado       | Limitado       | Sí                  |
| Velocidad          | Rápida         | Rápida         | Configurable        |
| Costo              | Por uso OpenAI | Por uso Google | Por uso Exa         |

---

## Solución de Problemas

### Error: "Missing API key"

Asegúrate de haber configurado correctamente el archivo `.env` con las claves API necesarias.

### Error: "Module not found"

Ejecuta `npm install` para instalar todas las dependencias.

### El agente no responde

Verifica que tengas conexión a internet y que las claves API sean válidas.

---

## Referencias

- [Guía oficial de Mastra](https://mastra.ai/guides/guide/web-search)
- [Documentación de OpenAI](https://platform.openai.com/docs)
- [Documentación de Google AI](https://ai.google.dev/docs)
- [Documentación de Exa](https://docs.exa.ai/)

---

## Licencia

ISC License

---

## Contacto

Para preguntas o sugerencias sobre este proyecto, contacta a los integrantes del grupo o al profesor del curso.

**Universidad Nacional de Ingeniería**
Facultad de Ingeniería Eléctrica y Electrónica
Lima, Perú
