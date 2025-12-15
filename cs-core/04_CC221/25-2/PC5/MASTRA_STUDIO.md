# Guía de Mastra Studio

Mastra Studio es la interfaz visual (playground) para interactuar con tus
agentes de búsqueda de forma interactiva.

## Iniciar Mastra Studio

```bash
npm run dev
```

Esto iniciará el servidor en **http://localhost:3000**

## Interfaz de Mastra Studio

### 1. Página Principal

Cuando abres Mastra Studio verás:

```
┌─────────────────────────────────────────┐
│         MASTRA STUDIO                   │
├─────────────────────────────────────────┤
│                                         │
│  Agents Available:                      │
│                                         │
│  📡 Search Agent OpenAI                 │
│     Uses OpenAI GPT-4o-mini             │
│                                         │
│  📡 Search Agent Gemini                 │
│     Uses Google Gemini 2.5 Flash        │
│                                         │
│  📡 Search Agent Exa                    │
│     Uses Exa custom search              │
│                                         │
└─────────────────────────────────────────┘
```

### 2. Seleccionar un Agente

Haz clic en cualquiera de los agentes disponibles:

- **Search Agent OpenAI** ← Funciona con tu OPENAI_API_KEY
- **Search Agent Gemini** ← Requiere GOOGLE_GENERATIVE_AI_API_KEY
- **Search Agent Exa** ← Funciona con tu EXA_API_KEY

### 3. Chat Interactivo

Una vez seleccionado el agente, verás una interfaz de chat:

```
┌─────────────────────────────────────────┐
│  Search Agent OpenAI              [×]   │
├─────────────────────────────────────────┤
│                                         │
│  [Chat history appears here]            │
│                                         │
│  You: ¿Qué es la IA?                    │
│                                         │
│  Agent: La inteligencia artificial...   │
│                                         │
├─────────────────────────────────────────┤
│  Type your message here...        [→]   │
└─────────────────────────────────────────┘
```

## Ejemplos de Consultas

### Para Investigación Académica

```
¿Cuáles son los últimos avances en inteligencia artificial?
```

```
Explica la arquitectura de un procesador moderno
```

```
¿Qué es la computación cuántica y cómo funciona?
```

### Para Noticias

```
¿Qué pasó esta semana en el mundo de la tecnología?
```

```
Últimas noticias sobre machine learning
```

### Para Búsqueda Específica

```
Busca información sobre arquitectura de computadoras 2025
```

```
Encuentra papers recientes sobre redes neuronales
```

## Características de Mastra Studio

### ✨ Ventajas

- **Interfaz Visual:** No necesitas escribir código
- **Interactivo:** Conversación natural con el agente
- **Historial:** Mantiene el contexto de la conversación
- **Multi-agente:** Cambia entre agentes fácilmente
- **En tiempo real:** Respuestas en vivo

### 🔄 Cambiar de Agente

1. Haz clic en el botón "Back" o "Home"
2. Selecciona otro agente
3. Comienza una nueva conversación

### 💾 Historial de Conversación

Mastra Studio mantiene el historial de tu conversación, permitiendo:

- Hacer preguntas de seguimiento
- Contextualizar nuevas consultas
- Referencias a respuestas anteriores

## Solución de Problemas

### Error: "Port 3000 already in use"

Otro proceso está usando el puerto 3000.

**Solución:**

```bash
# Encontrar el proceso
lsof -i :3000

# Matar el proceso
kill -9 <PID>

# O iniciar en otro puerto
PORT=3001 npm run dev
```

### Error: "Missing API key"

El agente seleccionado no tiene API key configurada.

**Solución:**

1. Verifica tu archivo `.env`
2. Asegúrate de tener la clave correcta:
   - `OPENAI_API_KEY` para Search Agent OpenAI
   - `GOOGLE_GENERATIVE_AI_API_KEY` para Search Agent Gemini
   - `EXA_API_KEY` para Search Agent Exa
3. Reinicia Mastra Studio

### El agente no responde

**Posibles causas:**

- Sin conexión a internet
- API key inválida o expirada
- Límite de uso alcanzado

**Solución:**

1. Verifica tu conexión a internet
2. Verifica que tu API key sea válida
3. Revisa el consumo en la plataforma del proveedor

### La página no carga

**Solución:**

```bash
# Detener el servidor
Ctrl + C

# Limpiar node_modules
rm -rf node_modules package-lock.json

# Reinstalar
npm install

# Reiniciar
npm run dev
```

## Atajos de Teclado

- **Enter:** Enviar mensaje
- **Shift + Enter:** Nueva línea en el mensaje
- **Esc:** Cerrar modales
- **Ctrl + C:** Detener el servidor (en terminal)

## Consejos de Uso

### 1. Sé Específico

❌ Mal: "Dame información" ✅ Bien: "¿Cuáles son los 3 principales desafíos de
la computación cuántica?"

### 2. Usa Contexto

El agente recuerda la conversación:

```
Tú: ¿Qué es la IA?
Agent: [Respuesta sobre IA]

Tú: ¿Cuáles son sus aplicaciones? ← El agente sabe que te refieres a IA
```

### 3. Pide Fuentes

```
"Busca información sobre [tema] y cita las fuentes"
```

### 4. Solicita Formato Específico

```
"Dame un resumen en 3 puntos sobre [tema]"
"Crea una tabla comparativa entre [A] y [B]"
"Lista los 5 principales [concepto]"
```

## Integración con tu Investigación

### Para el Informe UNI

1. **Investigación de temas:**
   ```
   "Busca información actualizada sobre arquitectura de computadoras"
   ```

2. **Verificación de datos:**
   ```
   "¿Es cierto que [afirmación]? Busca fuentes"
   ```

3. **Comparaciones:**
   ```
   "Compara arquitectura Von Neumann vs Harvard"
   ```

4. **Ejemplos prácticos:**
   ```
   "Dame ejemplos reales de aplicaciones de IA en arquitectura de computadoras"
   ```

## Modo Desarrollo vs Producción

### Desarrollo (Actual)

```bash
npm run dev
```

- Hot reload automático
- Logs detallados
- Puerto 3000 por defecto

### Producción (Futuro)

```bash
npm run build
npm start
```

- Optimizado para rendimiento
- Sin logs de debug
- Listo para deploy

## Recursos Adicionales

- **Documentación oficial:** https://mastra.ai/docs
- **Ejemplos:** Ver carpeta `src/examples/`
- **Guía completa:** [README.md](README.md)

---

**Proyecto:** Web Search Agent AI - UNI **Arquitectura de Computadoras 2025-II**

¡Disfruta usando Mastra Studio! 🚀
