#set page(margin: 2.5cm)
#set text(font: "New Computer Modern", size: 11pt)
#set par(justify: true)

#align(center)[
  #text(size: 14pt, weight: "bold")[Caso Práctico — Modelo Relacional de Base de Datos Bancaria]
]

#v(0.4em)
#align(center)[
  #text(size: 11pt)[Eliaz Bobadilla — 20244697E]
]

#v(1em)

== i. Relaciones que requieren claves primarias

Toda relación en el modelo relacional debe contar con una clave primaria que identifique de forma unívoca cada tupla. En este esquema bancario, las relaciones y sus claves primarias son las siguientes:

#table(
  columns: (auto, 1fr),
  stroke: 0.5pt,
  inset: 8pt,
  align: (left, left),
  [*Relación*], [*Clave Primaria*],
  [Sucursal],    [#text(style: "italic")[nombre\_sucursal] — identificador único de cada agencia],
  [Cliente],     [#text(style: "italic")[nombre\_cliente] — se asume que identifica a cada cliente de forma unívoca],
  [Cuenta],      [#text(style: "italic")[número\_cuenta] — único para cada cuenta del banco],
  [Préstamo],    [#text(style: "italic")[número\_préstamo] — único para cada operación de crédito],
  [Impositor],   [#text(style: "italic")[(nombre\_cliente, número\_cuenta)] — clave primaria compuesta],
  [Prestatario], [#text(style: "italic")[(nombre\_cliente, número\_préstamo)] — clave primaria compuesta],
)

#v(0.5em)
Las relaciones *Impositor* y *Prestatario* actúan como tablas de asociación entre clientes y sus productos financieros. Al estar formadas exclusivamente por claves foráneas, su clave primaria resulta de la combinación de ambos atributos, garantizando que no existan filas duplicadas para el mismo par cliente-producto.

#v(1.5em)

== ii. Relaciones que requieren claves foráneas

Las claves foráneas establecen las referencias de integridad referencial entre relaciones. A continuación se detallan todos los atributos que actúan como FK en el esquema:

#table(
  columns: (auto, auto, 1fr),
  stroke: 0.5pt,
  inset: 8pt,
  align: (left, left, left),
  [*Relación*],    [*Atributo FK*],          [*Referencia*],
  [Cuenta],        [nombre\_sucursal],        [→ Sucursal(nombre\_sucursal)],
  [Préstamo],      [nombre\_sucursal],        [→ Sucursal(nombre\_sucursal)],
  [Impositor],     [nombre\_cliente],         [→ Cliente(nombre\_cliente)],
  [Impositor],     [número\_cuenta],          [→ Cuenta(número\_cuenta)],
  [Prestatario],   [nombre\_cliente],         [→ Cliente(nombre\_cliente)],
  [Prestatario],   [número\_préstamo],        [→ Préstamo(número\_préstamo)],
)

#v(0.5em)
Las relaciones *Sucursal* y *Cliente* no poseen claves foráneas, ya que son entidades base independientes dentro del esquema. *Sucursal* funciona como punto de referencia central: tanto *Cuenta* como *Préstamo* la referencian para registrar en qué agencia se originó cada operación. *Impositor* y *Prestatario* conectan a los clientes con sus respectivos productos, completando el modelo de asociación.

== iii. Diagrama relacional entre entidades

El siguiente diagrama muestra cómo se vinculan las seis relaciones del esquema. Las líneas con notación ERmandOne–ERzeroToMany expresan cardinalidad: una sucursal puede gestionar múltiples cuentas y préstamos; un cliente puede ser titular de múltiples cuentas (vía Impositor) y puede haber solicitado múltiples préstamos (vía Prestatario).

#align(center)[
  #block(inset: 16pt)[
    #v(8pt)
    #image("diagram.svg", width: 120%)
  ]
]

