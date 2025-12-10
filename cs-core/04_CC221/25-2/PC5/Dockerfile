# Use Node.js 20 LTS as base image
FROM node:20-alpine

# Set working directory
WORKDIR /app

# Copy package files
COPY package*.json ./

# Install ALL dependencies (including dev deps for Mastra)
RUN npm ci

# Copy source code
COPY . .

# Build TypeScript
RUN npm run build

# Expose port - Railway will set PORT env variable
EXPOSE ${PORT:-3000}

# Set PORT environment variable for Mastra to use
ENV PORT=${PORT:-3000}

# Run Mastra in production mode (uses PORT env variable automatically)
CMD ["npx", "mastra", "start"]
