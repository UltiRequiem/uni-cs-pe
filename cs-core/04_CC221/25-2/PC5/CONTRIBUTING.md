# Guía de Contribución

Esta guía está diseñada para los miembros del equipo del proyecto.

## Equipo

- **Bobadilla Camarena Eliaz Sebastian**
- **Cabello Quevedo Yaimar Alexis**
- **Flores Bautista Alexandra Noemi**
- **Vitor Quispe Emmanuelle Ethan**

## Flujo de Trabajo con Git

### 1. Antes de Empezar a Trabajar

```bash
# Actualizar tu copia local
git pull origin main

# Crear una rama para tu feature
git checkout -b feature/nombre-descriptivo
```

### 2. Durante el Desarrollo

```bash
# Ver archivos modificados
git status

# Agregar cambios específicos
git add archivo1.ts archivo2.ts

# O agregar todos los cambios
git add .

# Hacer commit con mensaje descriptivo
git commit -m "feat: descripción breve del cambio"
```

### 3. Compartir tus Cambios

```bash
# Subir tu rama al repositorio
git push origin feature/nombre-descriptivo

# Crear un Pull Request en GitHub para revisión
```

## Convención de Mensajes de Commit

Usa prefijos descriptivos en tus commits:

- `feat:` - Nueva funcionalidad
- `fix:` - Corrección de bugs
- `docs:` - Cambios en documentación
- `refactor:` - Refactorización de código
- `test:` - Agregar o modificar tests
- `style:` - Cambios de formato (no afectan funcionalidad)

**Ejemplos:**

```bash
git commit -m "feat: agregar agente de búsqueda con Gemini"
git commit -m "fix: corregir error en exaSearchTool"
git commit -m "docs: actualizar README con ejemplos"
```

## Estructura del Proyecto

### Dónde Agregar Código

```
src/
├── mastra/
│   ├── agents/          ← Agregar nuevos agentes aquí
│   ├── tools/           ← Agregar nuevas herramientas aquí
│   └── index.ts         ← Registrar agentes y herramientas
├── examples/            ← Agregar ejemplos de uso
└── index.ts             ← Punto de entrada principal
```

## Tareas Sugeridas para el Equipo

### Tarea 1: Mejorar los Agentes

**Responsable sugerido:** [Nombre]

- Mejorar las instrucciones de los agentes
- Agregar más contexto específico para consultas académicas
- Optimizar prompts para mejores respuestas

**Archivo:** [src/mastra/agents/](src/mastra/agents/)

### Tarea 2: Documentación y Ejemplos

**Responsable sugerido:** [Nombre]

- Crear más ejemplos de uso en español
- Agregar casos de uso para investigación académica
- Documentar casos de prueba

**Archivos:** [src/examples/](src/examples/), README.md

### Tarea 3: Herramientas Adicionales

**Responsable sugerido:** [Nombre]

- Investigar otras APIs de búsqueda (Bing, Brave, etc.)
- Implementar filtros avanzados
- Agregar capacidad de búsqueda en PDFs académicos

**Archivos:** [src/mastra/tools/](src/mastra/tools/)

### Tarea 4: Interfaz y Testing

**Responsable sugerido:** [Nombre]

- Mejorar la experiencia en Mastra Studio
- Crear scripts de testing
- Documentar casos de error

**Archivos:** [src/examples/](src/examples/), tests/

## Estándares de Código

### TypeScript

```typescript
// ✅ BIEN: Usar tipos explícitos
export async function search(query: string): Promise<SearchResult> {
  // código
}

// ❌ MAL: Sin tipos
export async function search(query) {
  // código
}
```

### Comentarios

```typescript
// ✅ BIEN: Comentarios descriptivos
/**
 * Busca información en la web usando Exa API
 * @param query - La consulta de búsqueda
 * @param numResults - Número de resultados (1-10)
 */

// ❌ MAL: Sin comentarios o muy básicos
// función de búsqueda
```

### Nombres de Variables

```typescript
// ✅ BIEN: Nombres descriptivos en español o inglés consistente
const searchResults = await fetchResults(query);
const resultadosBusqueda = await obtenerResultados(consulta);

// ❌ MAL: Nombres ambiguos o mixtos
const res = await fetch(q);
const resultados_search = await get(query);
```

## Testing Local

Antes de hacer commit, prueba tu código:

```bash
# Compilar TypeScript
npm run build

# Ejecutar ejemplo simple
npm run example:simple

# Ejecutar comparación
npm run example:compare

# Probar con Mastra Studio
npm run mastra:dev
```

## Solución de Problemas Comunes

### Error: "Cannot find module"

```bash
rm -rf node_modules package-lock.json
npm install
```

### Error de TypeScript

```bash
npm run build
# Lee los errores y corrígelos antes de commit
```

### Conflictos en Git

```bash
# Actualizar tu rama con cambios de main
git checkout main
git pull
git checkout tu-rama
git merge main
# Resolver conflictos manualmente
git commit
```

## Recursos Útiles

### Documentación

- [TypeScript](https://www.typescriptlang.org/docs/)
- [Mastra](https://mastra.ai/docs)
- [Zod](https://zod.dev/)
- [Git](https://git-scm.com/doc)

### APIs

- [OpenAI](https://platform.openai.com/docs)
- [Google Gemini](https://ai.google.dev/docs)
- [Exa](https://docs.exa.ai/)

## Comunicación del Equipo

### Antes de Implementar

1. Discutir el enfoque con el equipo
2. Revisar si alguien más está trabajando en algo similar
3. Actualizar esta guía si es necesario

### Durante el Desarrollo

1. Hacer commits frecuentes con mensajes claros
2. Documentar decisiones importantes
3. Pedir ayuda si te bloqueas

### Después de Implementar

1. Probar exhaustivamente
2. Actualizar documentación
3. Crear Pull Request para revisión

## Checklist Antes de Commit

- [ ] El código compila sin errores (`npm run build`)
- [ ] Los ejemplos funcionan correctamente
- [ ] Agregué comentarios donde era necesario
- [ ] Actualicé la documentación relevante
- [ ] El mensaje de commit es descriptivo
- [ ] No incluí credenciales o API keys

## Preguntas Frecuentes

**P: ¿Puedo trabajar directamente en main?** R: Para cambios pequeños sí, pero
para features nuevos es mejor usar ramas.

**P: ¿Qué hago si rompí algo?** R: No te preocupes, usa `git revert` o pide
ayuda al equipo.

**P: ¿Cómo pruebo sin gastar créditos de API?** R: Usa console.log() para
simular respuestas o crea un mock.

**P: ¿Puedo cambiar la estructura del proyecto?** R: Discútelo con el equipo
primero para mantener consistencia.

---

¡Gracias por contribuir al proyecto! 🚀
