# Proyecto BD – Fase 1: Billetera Digital (e-wallet)

## Contexto del curso

- **Curso:** Base de Datos – Universidad Nacional de Ingeniería (UNI), Facultad de Ciencias
- **Docente:** M.Sc. Víctor Melchor Espinoza
- **Fase:** 1 – Modelamiento de la Base de Datos
- **Fecha de entrega:** 25 de mayo de 2026
- **Fecha de exposición:** 26 de mayo de 2026

## Integrantes

- Carlos Bonifacio (20244684K)
- Eliaz Bobadilla (20244697E)
- Leonardo Estacio (20241548I)

## Tema del proyecto

Modelar una base de datos para una aplicación de **billetera digital (e-wallet)** que permita:

- Almacenar valor (saldo)
- Realizar transacciones (envío/recepción de dinero entre usuarios)
- Gestionar contactos

Referencias del dominio: Yape (yape.com.pe) y Plin (plin.pe) — aplicaciones peruanas de pago móvil.

## Formato del informe

- **Archivo de salida:** Typst (.typ) para flexibilidad tipográfica
- **Fuente texto:** Arial 12
- **Fuente código SQL/álgebra:** Courier New 10
- **Espaciado:** Simple
- El informe debe incluir: índice, introducción, resumen ejecutivo, modelado ER, modelo relacional, consultas álgebra relacional, consultas cálculo relacional, conclusión y apéndice (dataset Relax)

## Estructura requerida del informe (Fase 1)

1. Índice
2. Introducción
3. Resumen Ejecutivo y Presentación del Caso de Estudio
4. Modelado de la Base de Datos
   - Diagrama Entidad-Relación (ER)
   - Diagrama Relacional
5. Consultas del Álgebra Relacional
   - 5.1 Operadores Fundamentales (Selección, Proyección, Unión, Intersección, Diferencia, Producto Cartesiano, Renombramiento)
   - 5.2 Operadores de Join (Theta Join, Equijoin, Natural Join, Left/Right/Full Outer Join)
   - 5.3 Operaciones Extendidas (División, Asignación, Funciones de Agregación)
6. Consultas del Cálculo Relacional
   - 4 consultas a nivel de tuplas
   - 4 consultas a nivel de dominio
7. Conclusión
8. Anexo: Dataset completo en Relax (mínimo 8 tuplas por relación)

## Entidades del sistema (por definir/validar)

Propuesta inicial de 8+ entidades para e-wallet:

| Entidad          | Tipo   | Descripción                                      |
|------------------|--------|--------------------------------------------------|
| Usuario          | Fuerte | Persona registrada en la app                     |
| Billetera        | Débil  | Saldo digital vinculado 1:1 al Usuario           |
| Transaccion      | Fuerte | Envío/recepción de dinero entre billeteras       |
| Contacto         | Débil  | Contactos guardados por un usuario               |
| CuentaBancaria   | Fuerte | Cuenta bancaria vinculada a una Billetera        |
| Tarjeta          | Fuerte | Tarjeta de débito/crédito vinculada a Billetera  |
| Recarga          | Débil  | Operación de carga de saldo (desde banco/tarjeta)|
| Notificacion     | Débil  | Alertas generadas por transacciones              |

## Relaciones y cardinalidades (propuesta)

- Usuario **1:1** Billetera (cada usuario tiene exactamente una billetera)
- Usuario **1:N** Contacto (un usuario tiene muchos contactos)
- Billetera **1:N** Transaccion como emisor (una billetera envía muchas transacciones)
- Billetera **1:N** Transaccion como receptor (una billetera recibe muchas transacciones)
- Billetera **1:N** CuentaBancaria (una billetera puede tener varias cuentas enlazadas)
- Billetera **1:N** Tarjeta (una billetera puede tener varias tarjetas)
- Billetera **1:N** Recarga (una billetera puede recargarse múltiples veces)
- Transaccion **1:N** Notificacion (una transacción genera notificaciones al emisor y receptor)

## Referencia de estructura (borrador del compañero)

El borrador de un compañero sobre e-commerce sirve como guía de estilo y nivel de detalle esperado. Su estructura incluye dataset con 8+ relaciones y sus tuplas, consultas de álgebra relacional con enunciado + resultado, y consultas de cálculo relacional.

## Herramientas a usar

- **Diagramas ER:** Día o draw.io (fondo blanco obligatorio)
- **Modelo Relacional:** Herramienta online vista en clase (fondo blanco obligatorio)
- **Dataset y consultas relacionales:** RelaX (relax.informatik.uni-freiburg.de)
- **Documento:** Typst (.typ)

## Estado actual del proyecto

- [ ] Definir y validar entidades finales
- [ ] Diseñar diagrama ER (draw.io)
- [ ] Diseñar modelo relacional
- [ ] Crear dataset en RelaX (mínimo 8 tuplas por tabla)
- [ ] Escribir consultas de álgebra relacional (15 operadores)
- [ ] Escribir consultas de cálculo relacional (4 tuplas + 4 dominio)
- [ ] Redactar informe completo en Typst
- [ ] Agregar capturas de pantalla de resultados en RelaX

## Notas importantes

- Todas las consultas deben retornar al menos una tupla (si el resultado está vacío no se califica)
- El dataset debe tener mínimo 8 tuplas por cada relación
- Identificar claramente entidades fuertes vs débiles, atributos compuestos y derivados
- Indicar cardinalidades en el diagrama ER
- Justificar la creación de nuevas relaciones en el modelo relacional
- Identificar PK y FK claramente (con subrayado o etiquetas)
