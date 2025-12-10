# Guía de Inicio Rápido

Esta guía te ayudará a poner en marcha el proyecto en menos de 5 minutos.

## Paso 1: Verificar Requisitos

Asegúrate de tener Node.js v20 o superior instalado:

```bash
node --version
```

## Paso 2: Instalar Dependencias

```bash
npm install
```

## Paso 3: Configurar API Keys

1. Copia el archivo de ejemplo:
```bash
cp .env.example .env
```

2. Edita `.env` y agrega al menos una clave API:

```env
OPENAI_API_KEY=sk-...
```

**Obtener claves API:**
- OpenAI: https://platform.openai.com/api-keys
- Google AI: https://aistudio.google.com/app/apikey
- Exa: https://exa.ai/

## Paso 4: Iniciar Mastra Studio (Playground)

```bash
npm run dev
```

Esto abrirá **Mastra Studio** en http://localhost:3000

### Usar el Playground:

1. Abre tu navegador en http://localhost:3000
2. Verás 3 agentes disponibles:
   - **Search Agent OpenAI** (funciona con tu API key de OpenAI)
   - **Search Agent Gemini** (requiere Google API key)
   - **Search Agent Exa** (funciona con tu API key de Exa)
3. Selecciona un agente
4. ¡Empieza a hacer preguntas!

### Ejemplos de Consultas:

- "¿Cuáles son las últimas noticias sobre IA?"
- "¿Qué es la computación cuántica?"
- "Explica la arquitectura de un procesador moderno"

---

## Comandos Disponibles

| Comando | Descripción |
|---------|-------------|
| `npm run dev` | **Inicia Mastra Studio (Recomendado)** |
| `npm start` | Alias para `npm run dev` |
| `npm run example:simple` | Ejemplo de búsqueda por código |
| `npm run example:compare` | Compara los 3 agentes por código |
| `npm run build` | Compila el proyecto TypeScript |

## Estructura de Archivos Importantes

```
src/
├── mastra/
│   ├── agents/          # Definición de agentes
│   ├── tools/           # Herramientas personalizadas
│   └── index.ts         # Configuración Mastra
├── examples/            # Ejemplos de uso
└── index.ts             # Punto de entrada principal
```

## Solución de Problemas Comunes

### Error: "Missing API key"
➜ Verifica que el archivo `.env` existe y contiene las claves correctas

### Error: "Cannot find module"
➜ Ejecuta `npm install` nuevamente

### El agente no responde
➜ Verifica tu conexión a internet y que las claves API sean válidas

## Siguiente Paso

Consulta el [README.md](README.md) completo para documentación detallada.
