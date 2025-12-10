# 🧾 SISTEMA DE INVENTARIO DE PRODUCTOS

**Curso: Programación Orientada a Objetos**

**Año: 2025**

**Equipo: Buena Onda Maravilla (BOM)**

## 🧠 Descripción general

El presente proyecto consiste en el desarrollo de un **sistema de inventario de productos** que permite **registrar, almacenar y gestionar información** sobre los productos disponibles, las cantidades máximas, las unidades vendidas y los precios.
El sistema fue diseñado con el objetivo de **poner en práctica los principios de la Programación Orientada a Objetos (POO)**, integrando además tecnologías modernas para el desarrollo web.

## 🎯 Objetivo del proyecto

Diseñar e implementar una aplicación que gestione de manera eficiente un inventario de productos, aplicando los **principios fundamentales de la POO** (encapsulamiento, abstracción, herencia y polimorfismo) dentro de un entorno de desarrollo moderno basado en **Next.js y TypeScript**.

## ⚙️ Funcionalidades principales

-📦 Registro de productos con nombre, cantidad máxima, cantidad vendida y precio.

-🔍 Consulta de productos almacenados.

-✏️ Actualización de datos del producto.

-❌ Eliminación de productos del inventario.

-📈 Validaciones automáticas (no se permite cantidad negativa ni ventas mayores al stock máximo).

-🗄️ Persistencia de datos mediante base de datos SQLite.
## 🧩 Tecnologías utilizadas

| Tecnología | Función principal| 
|----------|----------|
| **Next.js**  | Framework de React para construir interfaces y manejar rutas | 
| **React**    | Biblioteca para la creación de componentes dinámicos   | 
| **TailwindCSS** | Framework de estilos para diseño responsivo y moderno.   |
|**TypeScript**| Lenguaje tipado que permite aplicar POO en el desarrollo web |
|**Turso**| Base de datos liviana para almacenar la información del inventario |
|**BiomeJS**| Linter y formateador de código |

## 🧱 Estructura del proyecto

El proyecto se compone de varios archivos de configuración y código que garantizan su correcto funcionamiento:
| Archivo             | Descripción                                                       |
| ------------------- | ----------------------------------------------------------------- |
| `.gitignore`        | Lista de archivos y carpetas que no deben subirse al repositorio. |
| `schema.sql`        | Define la estructura de la base de datos (tabla `products`).      |
| `biome.json`        | Configuración del linter y formateador Biome.                     |
| `postcss.config.js` | Configura los plugins CSS, incluyendo TailwindCSS.                |
| `tsconfig.json`     | Configura TypeScript (tipado, módulos, rutas).                    |
| `next.config.ts`    | Configuración general de Next.js.                                 |
| `package.json`      | Lista de dependencias, scripts y metadatos del proyecto.          |

## 🧮 Base de datos

La base de datos fue creada con Turso y contiene la tabla principal products, estructurada de la siguiente manera:
| Campo           | Tipo                                                    | Descripción                 |
| --------------- | ------------------------------------------------------- | --------------------------- |
| `id`            | INTEGER PRIMARY KEY AUTOINCREMENT                       | Identificador único.        |
| `name`          | TEXT NOT NULL                                           | Nombre del producto.        |
| `quantity_max`  | INTEGER NOT NULL CHECK (quantity_max >= 0)              | Cantidad máxima disponible. |
| `quantity_sold` | INTEGER DEFAULT 0 CHECK (quantity_sold <= quantity_max) | Cantidad vendida.           |
| `price`         | REAL NOT NULL                                           | Precio del producto.        |
| `created_at`    | DATETIME DEFAULT CURRENT_TIMESTAMP                      | Fecha de registro.          |
| `updated_at`    | DATETIME DEFAULT CURRENT_TIMESTAMP                      | Última modificación.        |



## 🧠 Conceptos de POO aplicados

-**Encapsulamiento**: Cada producto maneja sus propios datos mediante propiedades y validaciones.

-**Abstracción**: Se modela un producto con solo los atributos necesarios.

-**Herencia y polimorfismo**: (Si el sistema lo extiende en el futuro) podría aplicarse para diferentes tipos de productos.

-**Modularidad**: El código se organiza en módulos reutilizables dentro del proyecto Next.js.

## 🚀 Ejecución del proyecto

Para ejecutar el sistema en un entorno local:

```bash
# Instalar dependencias
npm install

# Ejecutar el servidor en modo desarrollo
npm run dev
```

## 📜 Licencia

El proyecto se distribuye bajo la Licencia MIT, lo que permite su uso, modificación y redistribución libre, siempre que se conserve el aviso de derechos de autor:

Copyright (c) 2025
Equipo Buena Onda Maravilla (BOM)
