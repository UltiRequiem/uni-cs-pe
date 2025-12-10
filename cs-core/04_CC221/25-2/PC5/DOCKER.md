# Guía de Docker

Esta guía explica cómo usar Docker para ejecutar el proyecto en un contenedor.

## Archivos Docker

- **`Dockerfile`** - Imagen de producción (optimizada)
- **`Dockerfile.dev`** - Imagen de desarrollo (con hot reload)
- **`docker-compose.yml`** - Orquestación de servicios
- **`.dockerignore`** - Archivos excluidos del build

---

## Prerrequisitos

### Instalar Docker

**macOS:**
```bash
brew install --cask docker
```

**Linux:**
```bash
sudo apt-get update
sudo apt-get install docker.io docker-compose
```

**Windows:**
Descarga Docker Desktop desde https://www.docker.com/products/docker-desktop

### Verificar instalación

```bash
docker --version
docker-compose --version
```

---

## Configuración

### 1. Crear archivo .env

```bash
cp .env.example .env
```

Edita `.env` con tus API keys:
```env
OPENAI_API_KEY=sk-your-key-here
EXA_API_KEY=your-exa-key-here
GOOGLE_GENERATIVE_AI_API_KEY=your-google-key-here
```

---

## Uso Básico

### Modo Desarrollo (con hot reload)

```bash
# Iniciar en modo desarrollo
docker-compose up web-search-agent-dev

# O en segundo plano
docker-compose up -d web-search-agent-dev

# Ver logs
docker-compose logs -f web-search-agent-dev

# Detener
docker-compose down
```

### Modo Producción

```bash
# Iniciar en modo producción
docker-compose up web-search-agent

# O en segundo plano
docker-compose up -d web-search-agent

# Ver logs
docker-compose logs -f web-search-agent

# Detener
docker-compose down
```

---

## Comandos Docker Avanzados

### Construir imagen manualmente

```bash
# Producción
docker build -t web-search-agent:latest .

# Desarrollo
docker build -f Dockerfile.dev -t web-search-agent:dev .
```

### Ejecutar contenedor manualmente

```bash
# Producción
docker run -d \
  --name web-search-agent \
  -p 3000:3000 \
  -e OPENAI_API_KEY=$OPENAI_API_KEY \
  -e EXA_API_KEY=$EXA_API_KEY \
  web-search-agent:latest

# Desarrollo con volúmenes
docker run -d \
  --name web-search-agent-dev \
  -p 3000:3000 \
  -v $(pwd)/src:/app/src \
  -e OPENAI_API_KEY=$OPENAI_API_KEY \
  -e EXA_API_KEY=$EXA_API_KEY \
  web-search-agent:dev
```

### Ejecutar comandos dentro del contenedor

```bash
# Abrir shell
docker exec -it web-search-agent-dev sh

# Ejecutar ejemplo simple
docker exec web-search-agent-dev npm run example:simple

# Ejecutar comparación
docker exec web-search-agent-dev npm run example:compare
```

### Ver logs

```bash
# Ver logs en tiempo real
docker logs -f web-search-agent-dev

# Ver últimas 100 líneas
docker logs --tail 100 web-search-agent-dev
```

### Limpiar recursos

```bash
# Detener y eliminar contenedores
docker-compose down

# Eliminar contenedores y volúmenes
docker-compose down -v

# Eliminar imágenes
docker rmi web-search-agent:latest web-search-agent:dev

# Limpiar todo (cuidado!)
docker system prune -a
```

---

## Estructura de las Imágenes

### Dockerfile (Producción)

```dockerfile
FROM node:20-alpine          # Imagen base ligera
WORKDIR /app                  # Directorio de trabajo
COPY package*.json ./         # Copiar dependencias
RUN npm ci --only=production  # Instalar solo producción
COPY . .                      # Copiar código
RUN npm run build            # Compilar TypeScript
CMD ["node", "dist/index.js"] # Ejecutar
```

**Tamaño:** ~150-200 MB

### Dockerfile.dev (Desarrollo)

```dockerfile
FROM node:20-alpine           # Imagen base ligera
WORKDIR /app                   # Directorio de trabajo
COPY package*.json ./          # Copiar dependencias
RUN npm install               # Instalar todas (incluyendo dev)
COPY . .                       # Copiar código
CMD ["npm", "run", "dev"]     # Ejecutar con tsx (hot reload)
```

**Tamaño:** ~200-250 MB

---

## Variables de Entorno

El proyecto usa las siguientes variables:

| Variable | Requerida | Descripción |
|----------|-----------|-------------|
| `OPENAI_API_KEY` | Sí* | Clave API de OpenAI |
| `EXA_API_KEY` | Sí* | Clave API de Exa |
| `GOOGLE_GENERATIVE_AI_API_KEY` | No | Clave API de Google (opcional) |
| `NODE_ENV` | No | Entorno (development/production) |

*Al menos una de OpenAI o Exa es requerida

---

## Puertos

- **3000** - Mastra Studio (interfaz web)

Para cambiar el puerto:
```yaml
# En docker-compose.yml
ports:
  - "8080:3000"  # Mapea puerto 8080 local al 3000 del contenedor
```

---

## Volúmenes (Desarrollo)

En modo desarrollo, los siguientes directorios están montados:

```yaml
volumes:
  - ./src:/app/src                    # Código fuente
  - ./package.json:/app/package.json  # Dependencias
  - ./tsconfig.json:/app/tsconfig.json # Config TS
  - /app/node_modules                 # Excluir node_modules
```

Esto permite **hot reload**: los cambios en tu código local se reflejan inmediatamente en el contenedor.

---

## Troubleshooting

### Error: "Cannot connect to Docker daemon"

```bash
# Iniciar Docker Desktop (macOS/Windows)
# O iniciar servicio (Linux)
sudo systemctl start docker
```

### Error: "Port 3000 already in use"

```bash
# Encontrar proceso usando el puerto
lsof -i :3000

# Matar proceso
kill -9 <PID>

# O cambiar puerto en docker-compose.yml
```

### Error: "Missing API key"

```bash
# Verificar que .env existe y contiene las claves
cat .env

# Reconstruir contenedor con nuevas variables
docker-compose down
docker-compose up --build web-search-agent-dev
```

### Los cambios no se reflejan

```bash
# Reconstruir imagen
docker-compose up --build web-search-agent-dev

# O forzar recreación
docker-compose up --force-recreate web-search-agent-dev
```

### Contenedor se detiene inmediatamente

```bash
# Ver logs de error
docker logs web-search-agent-dev

# Ejecutar en primer plano para debugging
docker-compose up web-search-agent-dev
```

---

## Mejores Prácticas

### 1. Desarrollo Local
```bash
# Usa docker-compose para desarrollo
docker-compose up web-search-agent-dev
```

### 2. Producción
```bash
# Construye imagen optimizada
docker-compose build web-search-agent

# Ejecuta en segundo plano
docker-compose up -d web-search-agent
```

### 3. Multi-stage builds (futuro)

Para imágenes aún más pequeñas:
```dockerfile
# Build stage
FROM node:20-alpine AS builder
WORKDIR /app
COPY package*.json ./
RUN npm ci
COPY . .
RUN npm run build

# Production stage
FROM node:20-alpine
WORKDIR /app
COPY --from=builder /app/dist ./dist
COPY --from=builder /app/node_modules ./node_modules
CMD ["node", "dist/index.js"]
```

---

## Integración con CI/CD

### GitHub Actions

```yaml
# .github/workflows/docker.yml
name: Docker Build

on:
  push:
    branches: [ main ]

jobs:
  build:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Build Docker image
        run: docker build -t web-search-agent .
```

---

## Comandos Rápidos

```bash
# Desarrollo
docker-compose up -d web-search-agent-dev

# Producción
docker-compose up -d web-search-agent

# Ver logs
docker-compose logs -f

# Detener
docker-compose down

# Reconstruir
docker-compose up --build

# Limpiar todo
docker-compose down -v && docker system prune -a
```

---

## Recursos Adicionales

- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose Documentation](https://docs.docker.com/compose/)
- [Node.js Docker Best Practices](https://github.com/nodejs/docker-node/blob/main/docs/BestPractices.md)

---

**Proyecto:** Web Search Agent AI - UNI
**Arquitectura de Computadoras 2025-II**
