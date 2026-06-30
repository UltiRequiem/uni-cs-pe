#set page(paper: "a4", margin: (x: 2.5cm, y: 2.5cm), numbering: "1")
#set text(font: "Arial", size: 12pt, lang: "es")
#set par(leading: 0.65em, justify: true)
#set heading(numbering: "1.")
#show raw: set text(font: "Courier New", size: 10pt)
#show raw.where(block: true): block.with(
  fill: rgb("#f4f4f4"), inset: 8pt, radius: 3pt, width: 100%,
)
#set table(stroke: 0.5pt + black, inset: 5pt)
#show table: set text(size: 9pt)

// ============================================================
// CARÁTULA
// ============================================================
#set page(numbering: none)
#align(center + horizon)[
  #image("escudo.jpg", width: 8cm)
  #v(0.8cm)
  #text(size: 14pt, weight: "bold")[UNIVERSIDAD NACIONAL DE INGENIERÍA]
  #v(0.2cm)
  #text(size: 12pt)[
    Facultad de Ciencias \
    Escuela Profesional de Ciencia de la Computación
  ]
  #v(0.8cm)
  #text(size: 16pt, weight: "bold")[
    PROYECTO FORMATIVO DEL CURSO \
    BASE DE DATOS
  ]
  #v(0.3cm)
  #text(size: 14pt, weight: "bold")[Fase III — Objetos Avanzados de la Base de Datos]
  #v(0.3cm)
  #text(size: 13pt)[Caso de Estudio: Billetera Digital (e-wallet)]
  #v(0.8cm)
  #text(weight: "bold")[Docente:] M.Sc. Víctor Melchor Espinoza \
  #v(0.3cm)
  #text(weight: "bold")[Integrantes:] \
  #v(0.1cm)
  Carlos Bonifacio — 20244684K \
  Eliaz Bobadilla — 20244697E \
  Leonardo Estacio — 20241548I
  #v(1fr)
  Lima, Perú — 2026
]

#pagebreak()

// ============================================================
// ÍNDICE
// ============================================================
#align(center)[#text(size: 16pt, weight: "bold")[ÍNDICE]]
#v(0.5cm)
#outline(title: none, indent: 2em, depth: 3)

#pagebreak()

// ============================================================
// CONTENIDO PRINCIPAL
// ============================================================
#set page(numbering: "1")
#counter(page).update(1)

= Resumen Ejecutivo

El presente informe corresponde a la *Fase III* del Proyecto Formativo del curso de Base de Datos, cuya aplicación de caso es la *billetera digital (e-wallet)*. Partiendo del esquema relacional implementado en la Fase II (diez tablas normalizadas hasta 3FN con 15 registros cada una), esta fase extiende la base de datos con los siguientes objetos avanzados:

- *Sección I:* Seis dominios de usuario que encapsulan reglas de validación comunes.
- *Sección II:* Demostración de todas las restricciones de integridad (NOT NULL, PRIMARY KEY / UNIQUE, CHECK, clave foránea y a nivel de tupla), mostrando casos aceptados y rechazados en pgAdmin.
- *Sección III:* Cinco índices de distintos tipos analizando la carga de consultas.
- *Sección IV:* Ocho consultas SQL avanzadas (funciones de agregación, GROUP BY / HAVING y subconsultas correlacionadas).
- *Sección V:* Siete vistas que cubren operaciones de conjuntos, los tres tipos de JOIN y vistas anidadas.
- *Sección VI:* Ocho funciones PL/pgSQL con los cuatro tipos de JOIN, funciones de inserción, actualización y eliminación, un trigger automático de notificaciones, un stored procedure de transferencia P2P, y una aplicación de escritorio en Python con tkinter para las operaciones CRUD.

= Creación de Dominios, Relaciones y Llaves

== Definición de Dominios

Un *dominio* es un tipo de dato con nombre que incorpora restricciones CHECK propias, permitiendo reutilizar validaciones en múltiples columnas sin duplicar código. Se definen seis dominios para la base de datos `billetera_digital`.

```sql
-- Dirección de correo electrónico válida (contiene @ y dominio con punto)
CREATE DOMAIN dom_email
    AS VARCHAR(100)
    CHECK (VALUE ~* '^[^@\s]+@[^@\s]+\.[^@\s]{2,}$');

-- Valor monetario estrictamente positivo
CREATE DOMAIN dom_monto_pos
    AS NUMERIC(12,2)
    CHECK (VALUE > 0);

-- DNI peruano: exactamente 8 dígitos numéricos
CREATE DOMAIN dom_dni_pe
    AS CHAR(8)
    CHECK (VALUE ~ '^\d{8}$');

-- Celular peruano: exactamente 9 dígitos numéricos
CREATE DOMAIN dom_celular_pe
    AS CHAR(9)
    CHECK (VALUE ~ '^\d{9}$');

-- Código de moneda ISO 4217: tres letras mayúsculas
CREATE DOMAIN dom_moneda_iso
    AS CHAR(3)
    CHECK (VALUE ~ '^[A-Z]{3}$');

-- Campo de estado no nulo de hasta 20 caracteres
CREATE DOMAIN dom_estado_gen
    AS VARCHAR(20)
    NOT NULL;
```

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Dominio*], [*Tipo base*], [*Restricción*],
    [`dom_email`],       [`VARCHAR(100)`],  [Patrón `^[^@\s]+@[^@\s]+\.[^@\s]{2,}$` (case-insensitive)],
    [`dom_monto_pos`],   [`NUMERIC(12,2)`], [VALUE > 0],
    [`dom_dni_pe`],      [`CHAR(8)`],       [Patrón `^\d{8}$` — solo dígitos, longitud exacta 8],
    [`dom_celular_pe`],  [`CHAR(9)`],       [Patrón `^\d{9}$` — solo dígitos, longitud exacta 9],
    [`dom_moneda_iso`],  [`CHAR(3)`],       [Patrón `^[A-Z]{3}$` — tres letras mayúsculas],
    [`dom_estado_gen`],  [`VARCHAR(20)`],   [NOT NULL implícito en el dominio],
  )
  *Tabla 1.* Resumen de los seis dominios definidos.
]

Uso de dominios en una tabla:

```sql
CREATE TABLE EjemploDominios (
    email   dom_email,        -- rechaza 'usuario.sin.arroba'
    monto   dom_monto_pos,    -- rechaza 0 y negativos
    dni     dom_dni_pe,       -- rechaza '1234567' (7 dígitos)
    celular dom_celular_pe,   -- rechaza '98765432' (8 dígitos)
    moneda  dom_moneda_iso,   -- rechaza 'pen' (minúsculas)
    estado  dom_estado_gen    -- rechaza NULL
);
```



== Claves Primarias

Las claves primarias identifican de forma única cada tupla en la relación. Las siguientes cuatro son representativas del esquema:

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Tabla*], [*Clave Primaria*], [*Descripción*],
    [`Banco`],       [`id_banco SERIAL`],       [Identificador único del banco; generado automáticamente],
    [`Usuario`],     [`id_usuario SERIAL`],     [Identificador único del usuario registrado],
    [`Billetera`],   [`id_billetera SERIAL`],   [Identificador único de la billetera digital],
    [`Transaccion`], [`id_transaccion SERIAL`], [Identificador único de cada operación P2P],
  )
  *Tabla 2.* Claves primarias representativas del esquema.
]

```sql
-- Ejemplos de PK en el DDL de Fase II
CREATE TABLE Banco (
    id_banco SERIAL PRIMARY KEY, ...
);
CREATE TABLE Usuario (
    id_usuario SERIAL PRIMARY KEY, ...
);
CREATE TABLE Billetera (
    id_billetera SERIAL PRIMARY KEY, ...
);
CREATE TABLE Transaccion (
    id_transaccion SERIAL PRIMARY KEY, ...
);
```

== Claves Únicas

Las restricciones UNIQUE garantizan que no existan dos tuplas con el mismo valor en la columna indicada, sin necesidad de que sea la clave primaria.

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Tabla*], [*Columna UNIQUE*], [*Justificación*],
    [`Usuario`],         [`dni`],            [Cada persona tiene un DNI irrepetible en Perú],
    [`Usuario`],         [`celular`],        [El celular es el identificador de cuenta en Yape/Plin],
    [`Usuario`],         [`email`],          [Correo electrónico único por cuenta registrada],
    [`CuentaBancaria`],  [`numero_cuenta`],  [Número de cuenta bancaria globalmente único],
  )
  *Tabla 3.* Claves únicas representativas del esquema.
]

```sql
CREATE TABLE Usuario (
    dni    CHAR(8)      NOT NULL UNIQUE,
    celular CHAR(9)     NOT NULL UNIQUE,
    email  VARCHAR(100) NOT NULL UNIQUE, ...
);
CREATE TABLE CuentaBancaria (
    numero_cuenta VARCHAR(20) NOT NULL UNIQUE, ...
);
```

== Claves Foráneas

Las claves foráneas mantienen la integridad referencial entre tablas.

#align(center)[
  #table(
    columns: (auto, auto, auto),
    [*Tabla hijo*], [*Columna FK*], [*Tabla padre → columna PK*],
    [`Billetera`],    [`id_usuario`],            [`Usuario(id_usuario)` — relación 1:1],
    [`CuentaBancaria`],[`id_billetera`],          [`Billetera(id_billetera)`],
    [`Transaccion`],  [`id_billetera_emisor`],   [`Billetera(id_billetera)`],
    [`Notificacion`], [`id_usuario`],            [`Usuario(id_usuario)`],
  )
  *Tabla 4.* Claves foráneas representativas del esquema.
]

```sql
CREATE TABLE Billetera (
    id_usuario INT NOT NULL UNIQUE
        REFERENCES Usuario(id_usuario), ...
);
CREATE TABLE CuentaBancaria (
    id_billetera INT NOT NULL
        REFERENCES Billetera(id_billetera), ...
);
CREATE TABLE Transaccion (
    id_billetera_emisor INT NOT NULL
        REFERENCES Billetera(id_billetera), ...
);
CREATE TABLE Notificacion (
    id_usuario INT NOT NULL
        REFERENCES Usuario(id_usuario), ...
);
```

= Restricciones

Para cada restricción se describe la tupla que se intenta insertar, se muestra el caso *aceptado* (la operación procede) y el caso *rechazado* (la restricción se activa), junto con el mensaje de error de PostgreSQL.

== Restricciones NOT NULL

=== 1. `Usuario.nombre` NOT NULL

*Enunciado:* Se intenta insertar un usuario sin nombre.

*Caso aceptado:*
```sql
INSERT INTO Usuario(dni,nombre,apellido,celular,email)
    VALUES ('91000001','Ana','Demo','910000001','ana.demo@ewallet.pe');
-- Resultado: INSERT 0 1
```

*Caso rechazado:*
```sql
INSERT INTO Usuario(dni,nombre,apellido,celular,email)
    VALUES ('91000002',NULL,'Demo','910000002','ana2.demo@ewallet.pe');
```
*Error:* `ERROR: null value in column "nombre" of relation "usuario" violates not-null constraint`


=== 2. `Usuario.apellido` NOT NULL

*Enunciado:* Se intenta insertar un usuario sin apellido.

*Caso aceptado:* (ídem al anterior, campo `apellido = 'Demo'` presente)

*Caso rechazado:*
```sql
INSERT INTO Usuario(dni,nombre,apellido,celular,email)
    VALUES ('91000003','Luis',NULL,'910000003','luis.demo@ewallet.pe');
```
*Error:* `ERROR: null value in column "apellido" of relation "usuario" violates not-null constraint`


=== 3. `Usuario.dni` NOT NULL

*Enunciado:* Se intenta insertar un usuario sin DNI.

*Caso rechazado:*
```sql
INSERT INTO Usuario(dni,nombre,apellido,celular,email)
    VALUES (NULL,'Pedro','Demo','910000004','pedro.demo@ewallet.pe');
```
*Error:* `ERROR: null value in column "dni" of relation "usuario" violates not-null constraint`


=== 4. `Usuario.celular` NOT NULL

*Enunciado:* Se intenta insertar un usuario sin número de celular.

*Caso rechazado:*
```sql
INSERT INTO Usuario(dni,nombre,apellido,celular,email)
    VALUES ('91000005','Sara','Demo',NULL,'sara.demo@ewallet.pe');
```
*Error:* `ERROR: null value in column "celular" of relation "usuario" violates not-null constraint`


=== 5. `Usuario.email` NOT NULL

*Enunciado:* Se intenta insertar un usuario sin correo electrónico.

*Caso rechazado:*
```sql
INSERT INTO Usuario(dni,nombre,apellido,celular,email)
    VALUES ('91000006','Juan','Demo','910000006',NULL);
```
*Error:* `ERROR: null value in column "email" of relation "usuario" violates not-null constraint`


=== 6. `Billetera.saldo` NOT NULL

*Enunciado:* Se intenta insertar una billetera con saldo explícitamente NULL.

*Caso aceptado:*
```sql
INSERT INTO Billetera(id_usuario,saldo,moneda,fecha_creacion,estado)
    VALUES (1,0.00,'PEN',CURRENT_DATE,'Activa');
-- Resultado: INSERT 0 1
```

*Caso rechazado:*
```sql
INSERT INTO Billetera(id_usuario,saldo,moneda,fecha_creacion,estado)
    VALUES (1,NULL,'PEN',CURRENT_DATE,'Activa');
```
*Error:* `ERROR: null value in column "saldo" of relation "billetera" violates not-null constraint`


=== 7. `Transaccion.monto` NOT NULL

*Enunciado:* Se intenta insertar una transacción sin especificar el monto.

*Caso rechazado:*
```sql
INSERT INTO Transaccion(id_billetera_emisor,id_billetera_receptor,monto,estado)
    VALUES (1,2,NULL,'Pendiente');
```
*Error:* `ERROR: null value in column "monto" of relation "transaccion" violates not-null constraint`


=== 8. `Notificacion.mensaje` NOT NULL

*Enunciado:* Se intenta insertar una notificación sin texto de mensaje.

*Caso aceptado:*
```sql
INSERT INTO Notificacion(id_usuario,tipo,mensaje)
    VALUES (1,'Sistema','Bienvenido al sistema de prueba.');
-- Resultado: INSERT 0 1
```

*Caso rechazado:*
```sql
INSERT INTO Notificacion(id_usuario,tipo,mensaje)
    VALUES (1,'Sistema',NULL);
```
*Error:* `ERROR: null value in column "mensaje" of relation "notificacion" violates not-null constraint`


=== 9. `Banco.nombre` NOT NULL

*Enunciado:* Se intenta registrar un banco sin nombre.

*Caso rechazado:*
```sql
INSERT INTO Banco(nombre,pais) VALUES (NULL,'Peru');
```
*Error:* `ERROR: null value in column "nombre" of relation "banco" violates not-null constraint`


=== 10. `Recarga.monto` NOT NULL

*Enunciado:* Se intenta insertar una recarga sin especificar el monto.

*Caso rechazado:*
```sql
INSERT INTO Recarga(id_billetera,id_cuenta,monto,estado)
    VALUES (1,1,NULL,'Pendiente');
```
*Error:* `ERROR: null value in column "monto" of relation "recarga" violates not-null constraint`


== Restricciones PRIMARY KEY y UNIQUE

=== 1. `Usuario.dni` UNIQUE

*Enunciado:* Se intenta registrar dos usuarios con el mismo DNI `'92000001'`.

*Caso aceptado:*
```sql
INSERT INTO Usuario(dni,nombre,apellido,celular,email)
    VALUES ('92000001','Marco','Rios','920000001','marco.rios@ewallet.pe');
-- Resultado: INSERT 0 1
```

*Caso rechazado:* (mismo DNI, distinto nombre)
```sql
INSERT INTO Usuario(dni,nombre,apellido,celular,email)
    VALUES ('92000001','Pedro','Rios','920000002','pedro.rios@ewallet.pe');
```
*Restricción activada:* `usuario_dni_key` \
*Error:* `ERROR: duplicate key value violates unique constraint "usuario_dni_key"` \
`DETAIL: Key (dni)=(92000001) already exists.`


=== 2. `Usuario.celular` UNIQUE

*Enunciado:* Se intenta registrar un usuario con el celular `'920000001'` que ya pertenece a Marco Rios.

*Caso rechazado:*
```sql
INSERT INTO Usuario(dni,nombre,apellido,celular,email)
    VALUES ('92000003','Rosa','Rios','920000001','rosa.rios@ewallet.pe');
```
*Restricción activada:* `usuario_celular_key` \
*Error:* `ERROR: duplicate key value violates unique constraint "usuario_celular_key"` \
`DETAIL: Key (celular)=(920000001) already exists.`


=== 3. `Banco.nombre` UNIQUE

*Enunciado:* Se intenta insertar el banco 'BCP', que ya existe en la tabla.

*Caso rechazado:*
```sql
INSERT INTO Banco(nombre,pais) VALUES ('BCP','Peru');
```
*Restricción activada:* `banco_nombre_key` \
*Error:* `ERROR: duplicate key value violates unique constraint "banco_nombre_key"` \
`DETAIL: Key (nombre)=(BCP) already exists.`


=== 4. `CuentaBancaria.numero_cuenta` UNIQUE

*Enunciado:* Se intenta vincular el número de cuenta `'19101234567890'` que ya está registrado.

*Caso rechazado:*
```sql
INSERT INTO CuentaBancaria(id_billetera,id_banco,numero_cuenta,tipo_cuenta)
    VALUES (2,2,'19101234567890','Ahorros');
```
*Restricción activada:* `cuentabancaria_numero_cuenta_key` \
*Error:* `ERROR: duplicate key value violates unique constraint "cuentabancaria_numero_cuenta_key"` \
`DETAIL: Key (numero_cuenta)=(19101234567890) already exists.`


== Restricciones CHECK

=== 1. `Usuario.estado` CHECK

*Enunciado:* El estado del usuario solo admite los valores `'Activo'`, `'Bloqueado'` o `'Inactivo'`. Se intenta insertar un usuario con estado `'Suspendido'`.

*Caso aceptado:*
```sql
INSERT INTO Usuario(dni,nombre,apellido,celular,email,estado)
    VALUES ('93000001','Test','Estado','930000001',
            'test.estado@ewallet.pe','Bloqueado');
-- Resultado: INSERT 0 1
```

*Caso rechazado:*
```sql
INSERT INTO Usuario(dni,nombre,apellido,celular,email,estado)
    VALUES ('93000002','Test','Estado2','930000002',
            'test2.estado@ewallet.pe','Suspendido');
```
*Restricción activada:* `usuario_estado_check` \
*Error:* `ERROR: new row for relation "usuario" violates check constraint "usuario_estado_check"`


=== 2. `Billetera.estado` CHECK

*Enunciado:* El estado de la billetera solo admite `'Activa'`, `'Bloqueada'` o `'Cerrada'`. Se intenta insertar una billetera con estado `'Eliminada'`.

*Caso rechazado:*
```sql
INSERT INTO Billetera(id_usuario,saldo,estado)
    VALUES (1,0.00,'Eliminada');
```
*Restricción activada:* `billetera_estado_check` \
*Error:* `ERROR: new row for relation "billetera" violates check constraint "billetera_estado_check"`


=== 3. `Billetera.saldo >= 0` CHECK

*Enunciado:* El saldo de una billetera no puede ser negativo. Se intenta insertar una billetera con saldo de −S/ 50.

*Caso rechazado:*
```sql
INSERT INTO Billetera(id_usuario,saldo)
    VALUES (1,-50.00);
```
*Restricción activada:* `billetera_saldo_check` \
*Error:* `ERROR: new row for relation "billetera" violates check constraint "billetera_saldo_check"`


=== 4. `CuentaBancaria.tipo_cuenta` CHECK

*Enunciado:* El tipo de cuenta solo admite `'Ahorros'` o `'Corriente'`. Se intenta registrar un tipo `'Plazo Fijo'`.

*Caso aceptado:*
```sql
INSERT INTO CuentaBancaria(id_billetera,id_banco,numero_cuenta,tipo_cuenta)
    VALUES (1,1,'99901234567890','Ahorros');
-- Resultado: INSERT 0 1
```

*Caso rechazado:*
```sql
INSERT INTO CuentaBancaria(id_billetera,id_banco,numero_cuenta,tipo_cuenta)
    VALUES (1,1,'99999999999999','Plazo Fijo');
```
*Restricción activada:* `cuentabancaria_tipo_cuenta_check` \
*Error:* `ERROR: new row for relation "cuentabancaria" violates check constraint "cuentabancaria_tipo_cuenta_check"`


=== 5. `Tarjeta.tipo` CHECK

*Enunciado:* El tipo de tarjeta solo admite `'Debito'` o `'Credito'`. Se intenta registrar una tarjeta `'Prepago'`.

*Caso aceptado:*
```sql
INSERT INTO Tarjeta(id_billetera,id_banco,ultimos_4_digitos,tipo,fecha_vencimiento)
    VALUES (1,1,'0001','Debito','2029-01-31');
-- Resultado: INSERT 0 1
```

*Caso rechazado:*
```sql
INSERT INTO Tarjeta(id_billetera,id_banco,ultimos_4_digitos,tipo,fecha_vencimiento)
    VALUES (1,1,'0002','Prepago','2029-01-31');
```
*Restricción activada:* `tarjeta_tipo_check` \
*Error:* `ERROR: new row for relation "tarjeta" violates check constraint "tarjeta_tipo_check"`


=== 6. `Recarga.monto > 0` CHECK

*Enunciado:* El monto de recarga debe ser estrictamente positivo. Se intenta ingresar una recarga de −S/ 50.

*Caso aceptado:*
```sql
INSERT INTO Recarga(id_billetera,id_cuenta,id_tarjeta,monto,estado)
    VALUES (1,1,NULL,50.00,'Pendiente');
-- Resultado: INSERT 0 1
```

*Caso rechazado:*
```sql
INSERT INTO Recarga(id_billetera,id_cuenta,id_tarjeta,monto,estado)
    VALUES (1,1,NULL,-50.00,'Pendiente');
```
*Restricción activada:* `recarga_monto_check` \
*Error:* `ERROR: new row for relation "recarga" violates check constraint "recarga_monto_check"`


=== 7. `Transaccion.monto > 0` CHECK

*Enunciado:* El monto de una transacción debe ser mayor a cero. Se intenta registrar una transferencia de S/ 0.

*Caso aceptado:*
```sql
INSERT INTO Transaccion(id_billetera_emisor,id_billetera_receptor,
                         monto,mensaje,estado)
    VALUES (1,2,10.00,'Prueba check monto','Pendiente');
-- Resultado: INSERT 0 1
```

*Caso rechazado:*
```sql
INSERT INTO Transaccion(id_billetera_emisor,id_billetera_receptor,
                         monto,estado)
    VALUES (1,2,0.00,'Pendiente');
```
*Restricción activada:* `transaccion_monto_check` \
*Error:* `ERROR: new row for relation "transaccion" violates check constraint "transaccion_monto_check"`


=== 8. `Notificacion.tipo` CHECK

*Enunciado:* El tipo de notificación solo admite `'Transaccion'`, `'Recarga'` o `'Sistema'`. Se intenta insertar un tipo `'Alerta'`.

*Caso rechazado:*
```sql
INSERT INTO Notificacion(id_usuario,tipo,mensaje)
    VALUES (1,'Alerta','Mensaje no válido');
```
*Restricción activada:* `notificacion_tipo_check` \
*Error:* `ERROR: new row for relation "notificacion" violates check constraint "notificacion_tipo_check"`


== Restricción de Integridad de Clave Foránea

Para cada FK se prueba la restricción en tres operaciones: *inclusión* (INSERT que viola la FK), *exclusión* (DELETE del padre bloqueado por la FK) y *actualización* (UPDATE que viola la FK).

=== FK 1: `Billetera.id_usuario → Usuario`

==== Inclusión (INSERT)

*Enunciado:* Se intenta crear una billetera referenciando al usuario con `id_usuario = 9999`, que no existe.

```sql
INSERT INTO Billetera(id_usuario,saldo) VALUES (9999,0.00);
```
*Error:* `ERROR: insert or update on table "billetera" violates foreign key constraint "billetera_id_usuario_fkey"` \
`DETAIL: Key (id_usuario)=(9999) is not present in table "usuario".`


==== Exclusión (DELETE)

*Enunciado:* Se intenta eliminar al usuario con `id_usuario = 1` (Carlos Bonifacio), que tiene una billetera activa que lo referencia.

```sql
DELETE FROM Usuario WHERE id_usuario = 1;
```
*Error:* `ERROR: update or delete on table "usuario" violates foreign key constraint "billetera_id_usuario_fkey" on table "billetera"` \
`DETAIL: Key (id_usuario)=(1) is still referenced from table "billetera".`


==== Actualización (UPDATE)

*Enunciado:* Se intenta reasignar la billetera 1 al usuario inexistente `id_usuario = 9999`.

```sql
UPDATE Billetera SET id_usuario = 9999 WHERE id_billetera = 1;
```
*Error:* `ERROR: insert or update on table "billetera" violates foreign key constraint "billetera_id_usuario_fkey"` \
`DETAIL: Key (id_usuario)=(9999) is not present in table "usuario".`


=== FK 2: `CuentaBancaria.id_billetera → Billetera`

==== Inclusión (INSERT)

```sql
INSERT INTO CuentaBancaria(id_billetera,id_banco,numero_cuenta,tipo_cuenta)
    VALUES (9999,1,'88888888888888','Ahorros');
```
*Error:* `ERROR: insert or update on table "cuentabancaria" violates foreign key constraint "cuentabancaria_id_billetera_fkey"` \
`DETAIL: Key (id_billetera)=(9999) is not present in table "billetera".`


==== Exclusión (DELETE)

```sql
DELETE FROM Billetera WHERE id_billetera = 1;
```
*Error:* `ERROR: update or delete on table "billetera" violates foreign key constraint "cuentabancaria_id_billetera_fkey" on table "cuentabancaria"`


==== Actualización (UPDATE)

```sql
UPDATE CuentaBancaria SET id_billetera = 9999 WHERE id_cuenta = 1;
```
*Error:* `ERROR: insert or update on table "cuentabancaria" violates foreign key constraint "cuentabancaria_id_billetera_fkey"`


=== FK 3: `Transaccion.id_billetera_emisor → Billetera`

==== Inclusión (INSERT)

```sql
INSERT INTO Transaccion(id_billetera_emisor,id_billetera_receptor,monto,estado)
    VALUES (9999,2,100.00,'Pendiente');
```
*Error:* `ERROR: insert or update on table "transaccion" violates foreign key constraint "transaccion_id_billetera_emisor_fkey"` \
`DETAIL: Key (id_billetera_emisor)=(9999) is not present in table "billetera".`


==== Exclusión (DELETE)

```sql
DELETE FROM Billetera WHERE id_billetera = 2;
```
*Error:* `ERROR: update or delete on table "billetera" violates foreign key constraint "transaccion_id_billetera_emisor_fkey" on table "transaccion"`


==== Actualización (UPDATE)

```sql
UPDATE Transaccion SET id_billetera_emisor = 9999 WHERE id_transaccion = 1;
```
*Error:* `ERROR: insert or update on table "transaccion" violates foreign key constraint "transaccion_id_billetera_emisor_fkey"`


=== FK 4: `Notificacion.id_usuario → Usuario`

==== Inclusión (INSERT)

```sql
INSERT INTO Notificacion(id_usuario,tipo,mensaje)
    VALUES (9999,'Sistema','Prueba FK usuario');
```
*Error:* `ERROR: insert or update on table "notificacion" violates foreign key constraint "notificacion_id_usuario_fkey"` \
`DETAIL: Key (id_usuario)=(9999) is not present in table "usuario".`


==== Exclusión (DELETE)

```sql
DELETE FROM Usuario WHERE id_usuario = 2;
```
*Error:* `ERROR: update or delete on table "usuario" violates foreign key constraint "notificacion_id_usuario_fkey" on table "notificacion"`


==== Actualización (UPDATE)

```sql
UPDATE Notificacion SET id_usuario = 9999 WHERE id_notificacion = 1;
```
*Error:* `ERROR: insert or update on table "notificacion" violates foreign key constraint "notificacion_id_usuario_fkey"`


== Restricciones a Nivel de Tupla

Las restricciones a nivel de tupla se definen con `CONSTRAINT ... CHECK` sobre múltiples columnas dentro de la misma fila.

=== 1. `Contacto.chk_no_autocontacto`

*Definición:* `CONSTRAINT chk_no_autocontacto CHECK (id_usuario <> id_usuario_contacto)`

*Enunciado:* Un usuario no puede agregarse a sí mismo como contacto. Se intenta insertar el contacto `(id_usuario=5, id_usuario_contacto=5)`.

*Caso aceptado:*
```sql
INSERT INTO Contacto(id_usuario,id_usuario_contacto,alias)
    VALUES (5,9,'Sofia G - prueba');
-- Resultado: INSERT 0 1  (Jose agrega a Sofia)
```

*Caso rechazado:*
```sql
INSERT INTO Contacto(id_usuario,id_usuario_contacto,alias)
    VALUES (5,5,'Yo mismo');
```
*Restricción activada:* `chk_no_autocontacto` \
*Error:* `ERROR: new row for relation "contacto" violates check constraint "chk_no_autocontacto"` \
*Motivo:* Ambas columnas contienen el mismo valor (5 = 5), violando la restricción `id_usuario <> id_usuario_contacto`.


=== 2. `Recarga.chk_origen_recarga`

*Definición:*
```sql
CONSTRAINT chk_origen_recarga CHECK (
    (id_cuenta IS NOT NULL AND id_tarjeta IS NULL) OR
    (id_cuenta IS NULL     AND id_tarjeta IS NOT NULL)
)
```

*Enunciado:* Una recarga debe provenir exactamente de una fuente: cuenta bancaria O tarjeta, nunca ambas ni ninguna.

*Caso aceptado:* (origen = cuenta bancaria solamente)
```sql
INSERT INTO Recarga(id_billetera,id_cuenta,id_tarjeta,monto,estado)
    VALUES (2,3,NULL,100.00,'Pendiente');
-- Resultado: INSERT 0 1
```

*Caso rechazado 1:* (ningún origen)
```sql
INSERT INTO Recarga(id_billetera,id_cuenta,id_tarjeta,monto,estado)
    VALUES (2,NULL,NULL,100.00,'Pendiente');
```
*Restricción activada:* `chk_origen_recarga` — ambas fuentes son NULL.


*Caso rechazado 2:* (dos orígenes simultáneos)
```sql
INSERT INTO Recarga(id_billetera,id_cuenta,id_tarjeta,monto,estado)
    VALUES (2,3,2,100.00,'Pendiente');
```
*Restricción activada:* `chk_origen_recarga` — ambas columnas tienen valor.


= Índices

Se recomienda crear índices en columnas que sean consultadas frecuentemente en condiciones `WHERE`, `JOIN ON` u `ORDER BY`, especialmente cuando la tabla supera los miles de filas. A continuación se crean cinco índices con distintas características.

#table(
  columns: (2fr, 1.2fr, 2fr, 3.5fr),
  [*Índice*], [*Tipo*], [*Tabla / Columna(s)*], [*Justificación*],
  [`idx_usuario_celular`],
  [B-tree],
  [`Usuario(celular)`],
  [Login y búsqueda de destinatario se realizan por celular; sin índice, cada búsqueda hace un sequential scan.],

  [`idx_transaccion_estado`],
  [B-tree],
  [`Transaccion(estado)`],
  [La mayoría de consultas filtran `WHERE estado = 'Completada'`; el índice evita el scan completo de la tabla.],

  [`idx_notif_usuario_leida`],
  [B-tree compuesto],
  [`Notificacion(id_usuario, leida)`],
  [La bandeja de entrada filtra por `id_usuario AND leida = FALSE`; el índice compuesto cubre ambas columnas sin acceder a la tabla.],

  [`idx_transaccion_fecha_desc`],
  [B-tree DESC],
  [`Transaccion(fecha DESC)`],
  [El historial de movimientos se muestra en orden cronológico inverso; el índice DESC evita la operación de ordenamiento en memoria.],

  [`idx_billetera_activa`],
  [B-tree parcial],
  [`Billetera(id_billetera) WHERE estado = 'Activa'`],
  [Casi todas las consultas operacionales ignoran billeteras cerradas o bloqueadas; el índice parcial es más pequeño y eficiente.],
)
*Tabla 5.* Índices creados en la Fase III.

```sql
-- 1. B-tree en celular del usuario
CREATE INDEX idx_usuario_celular
    ON Usuario(celular);

-- 2. B-tree en estado de transacción
CREATE INDEX idx_transaccion_estado
    ON Transaccion(estado);

-- 3. B-tree compuesto: bandeja de notificaciones
CREATE INDEX idx_notif_usuario_leida
    ON Notificacion(id_usuario, leida);

-- 4. B-tree descendente: historial reciente
CREATE INDEX idx_transaccion_fecha_desc
    ON Transaccion(fecha DESC);

-- 5. Índice parcial: solo billeteras activas
CREATE INDEX idx_billetera_activa
    ON Billetera(id_billetera)
    WHERE estado = 'Activa';
```


= Consultas

== Consultas con Funciones de Agregación

=== Q1: Total enviado y número de envíos por usuario

*Enunciado:* Obtener, para cada emisor, la cantidad de transacciones realizadas y el monto total enviado, ordenados de mayor a menor monto.

```sql
SELECT b.id_billetera,
       u.nombre || ' ' || u.apellido AS usuario,
       COUNT(*)                       AS num_envios,
       SUM(t.monto)                   AS total_enviado
FROM Transaccion t
JOIN Billetera b ON t.id_billetera_emisor = b.id_billetera
JOIN Usuario   u ON b.id_usuario          = u.id_usuario
GROUP BY b.id_billetera, u.nombre, u.apellido
ORDER BY total_enviado DESC;
```

*Resultado (13 filas — billeteras 9 y 10 nunca enviaron):*

#align(center)[
  #table(
    columns: 4,
    [*id_billetera*],[*usuario*],[*num_envios*],[*total_enviado*],
    [8],[Diego Rojas],   [1],[500.00],
    [4],[Maria Quispe],  [2],[325.00],
    [14],[Miguel Torres],[1],[320.00],
    [7],[Ana Flores],    [1],[300.00],
    [5],[Jose Mamani],   [1],[200.00],
    [11],[Carmen Soto],  [1],[150.00],
    [3],[Leonardo Estacio],[1],[120.00],
    [13],[Valentina Cruz],[1],[90.00],
    [1],[Carlos Bonifacio],[2],[90.00],
    [2],[Eliaz Bobadilla],[1],[80.00],
    [12],[Roberto Luna], [1],[60.00],
    [15],[Daniela Paredes],[1],[45.00],
    [6],[Lucia Huaman],  [1],[35.50],
  )
]


=== Q2: Estadísticas de recargas exitosas

*Enunciado:* Calcular el número total, promedio, mínimo, máximo y suma de montos de las recargas con estado `'Exitosa'`.

```sql
SELECT COUNT(*)               AS total_recargas,
       ROUND(AVG(monto), 2)   AS promedio_monto,
       MIN(monto)             AS monto_minimo,
       MAX(monto)             AS monto_maximo,
       SUM(monto)             AS monto_total
FROM Recarga
WHERE estado = 'Exitosa';
```

*Resultado (1 fila — 13 recargas exitosas sobre 15 totales):*

#align(center)[
  #table(
    columns: 5,
    [*total_recargas*],[*promedio_monto*],[*monto_minimo*],[*monto_maximo*],[*monto_total*],
    [13],[378.85],[120.00],[900.00],[4925.00],
  )
]


== Consultas con WHERE, GROUP BY, HAVING y ORDER BY

=== Q3: Billeteras con más de un envío, ordenadas por monto acumulado

*Enunciado:* Listar las billeteras cuyos emisores realizaron más de una transacción (de cualquier estado), indicando el total acumulado enviado, ordenado descendentemente.

```sql
SELECT b.id_billetera,
       u.nombre || ' ' || u.apellido AS usuario,
       COUNT(*)                       AS num_transacciones,
       SUM(t.monto)                   AS total_enviado
FROM Transaccion t
JOIN Billetera b ON t.id_billetera_emisor = b.id_billetera
JOIN Usuario   u ON b.id_usuario          = u.id_usuario
GROUP BY b.id_billetera, u.nombre, u.apellido
HAVING COUNT(*) > 1
ORDER BY total_enviado DESC;
```

*Resultado (2 filas — solo Carlos y Maria enviaron más de una vez):*

#align(center)[
  #table(
    columns: 4,
    [*id_billetera*],[*usuario*],[*num_transacciones*],[*total_enviado*],
    [4],[Maria Quispe],    [2],[325.00],
    [1],[Carlos Bonifacio],[2],[90.00],
  )
]


=== Q4: Usuarios con dos o más notificaciones recibidas

*Enunciado:* Listar los usuarios que han recibido dos o más notificaciones, ordenados por cantidad descendente.

```sql
SELECT u.nombre || ' ' || u.apellido AS usuario,
       COUNT(*)                       AS total_notificaciones
FROM Notificacion n
JOIN Usuario u ON n.id_usuario = u.id_usuario
GROUP BY u.id_usuario, u.nombre, u.apellido
HAVING COUNT(*) >= 2
ORDER BY total_notificaciones DESC;
```

*Resultado (2 filas — Carlos tiene 3, Eliaz tiene 2):*

#align(center)[
  #table(
    columns: 2,
    [*usuario*],[*total_notificaciones*],
    [Carlos Bonifacio],[3],
    [Eliaz Bobadilla], [2],
  )
]


== Subconsultas

=== Q5: Operador `IN` — usuarios que enviaron al menos una transacción

*Enunciado:* Obtener el nombre y apellido de los usuarios cuya billetera figura como emisora en al menos una transacción.

```sql
SELECT nombre, apellido
FROM Usuario
WHERE id_usuario IN (
    SELECT b.id_usuario
    FROM Transaccion t
    JOIN Billetera b ON t.id_billetera_emisor = b.id_billetera
)
ORDER BY apellido, nombre;
```

*Resultado (13 filas — excluidos Sofia Gutierrez y Pedro Vargas):*

#align(center)[
  #table(
    columns: 2,
    [*nombre*],[*apellido*],
    [Eliaz],[Bobadilla],[Carlos],[Bonifacio],[Valentina],[Cruz],
    [Leonardo],[Estacio],[Ana],[Flores],[Lucia],[Huaman],
    [Roberto],[Luna],[Jose],[Mamani],[Daniela],[Paredes],
    [Maria],[Quispe],[Diego],[Rojas],[Carmen],[Soto],
    [Miguel],[Torres],[],[],
  )
]


=== Q6: Operador `EXISTS` — usuarios con cuenta bancaria vinculada

*Enunciado:* Listar los usuarios que tienen al menos una cuenta bancaria vinculada a su billetera.

```sql
SELECT u.nombre, u.apellido, b.saldo
FROM Usuario u
JOIN Billetera b ON u.id_usuario = b.id_usuario
WHERE EXISTS (
    SELECT 1
    FROM CuentaBancaria c
    WHERE c.id_billetera = b.id_billetera
)
ORDER BY u.apellido;
```

*Resultado (13 filas — excluidos Lucia Huaman y Pedro Vargas que no tienen cuentas):*

#align(center)[
  #table(
    columns: 3,
    [*nombre*],[*apellido*],[*saldo*],
    [Eliaz],[Bobadilla],[580.00],
    [Carlos],[Bonifacio],[320.00],
    [Valentina],[Cruz],[130.00],
    [Leonardo],[Estacio],[450.00],
    [Ana],[Flores],[620.00],
    [Sofia],[Gutierrez],[340.00],
    [Roberto],[Luna],[490.00],
    [Jose],[Mamani],[780.00],
    [Daniela],[Paredes],[215.00],
    [Maria],[Quispe],[220.00],
    [Diego],[Rojas],[1100.00],
    [Carmen],[Soto],[270.00],
    [Miguel],[Torres],[860.00],
  )
]


=== Q7: Operador `ALL` — transacciones que superan todas las recargas de la billetera 1

*Enunciado:* Obtener las transacciones cuyo monto es mayor que el monto de *todas* las recargas realizadas a la billetera 1 (recargas: S/ 200 y S/ 150). La condición `> ALL` equivale a `> MAX(200, 150) = 200`.

```sql
SELECT id_transaccion, monto, estado
FROM Transaccion
WHERE monto > ALL (
    SELECT monto
    FROM Recarga
    WHERE id_billetera = 1
)
ORDER BY monto DESC;
```

*Resultado (4 filas — montos estrictamente mayores a S/ 200):*

#align(center)[
  #table(
    columns: 3,
    [*id_transaccion*],[*monto*],[*estado*],
    [9],[500.00],[Completada],
    [13],[320.00],[Completada],
    [8],[300.00],[Pendiente],
    [3],[250.00],[Fallida],
  )
]


=== Q8: Operador `ANY` — usuarios con saldo menor que alguna transacción completada

*Enunciado:* Listar los usuarios cuyo saldo actual es menor que el monto de *alguna* transacción completada (indica que alguna operación movió más dinero del que tienen ahora). La condición `< ANY` es verdadera si el saldo es menor al máximo de los montos comparados (S/ 500).

```sql
SELECT u.nombre, u.apellido, b.saldo
FROM Usuario u
JOIN Billetera b ON u.id_usuario = b.id_usuario
WHERE b.saldo < ANY (
    SELECT monto
    FROM Transaccion
    WHERE estado = 'Completada'
)
ORDER BY b.saldo;
```

*Resultado (10 filas — saldo < S/ 500):*

#align(center)[
  #table(
    columns: 3,
    [*nombre*],[*apellido*],[*saldo*],
    [Pedro],[Vargas],[80.00],
    [Valentina],[Cruz],[130.00],
    [Lucia],[Huaman],[150.00],
    [Daniela],[Paredes],[215.00],
    [Maria],[Quispe],[220.00],
    [Carmen],[Soto],[270.00],
    [Carlos],[Bonifacio],[320.00],
    [Sofia],[Gutierrez],[340.00],
    [Leonardo],[Estacio],[450.00],
    [Roberto],[Luna],[490.00],
  )
]


= Vistas

== Vistas con Operaciones de Conjuntos

=== V1: UNION ALL — todos los movimientos financieros

*Enunciado:* Consolidar en una sola vista todos los movimientos financieros del sistema (transacciones P2P y recargas) con su tipo, monto, fecha y estado.

```sql
CREATE VIEW v_movimientos AS
    SELECT 'Transaccion'::TEXT AS tipo, monto, fecha, estado
      FROM Transaccion
  UNION ALL
    SELECT 'Recarga', monto, fecha, estado
      FROM Recarga;
```

*Consulta y resultado parcial:*
```sql
SELECT * FROM v_movimientos ORDER BY fecha DESC LIMIT 6;
```

#align(center)[
  #table(
    columns: 4,
    [*tipo*],[*monto*],[*fecha*],[*estado*],
    [Transaccion],[90.00],[2025-06-05 16:45:00],[Pendiente],
    [Transaccion],[45.00],[2025-06-03 09:30:00],[Completada],
    [Recarga],[175.00],[2025-06-02 08:30:00],[Exitosa],
    [Transaccion],[320.00],[2025-05-26 14:00:00],[Completada],
    [Transaccion],[60.00],[2025-05-23 11:30:00],[Completada],
    [Transaccion],[150.00],[2025-05-21 10:00:00],[Completada],
  )
  _(30 filas en total — 15 transacciones + 15 recargas)_
]


=== V2: EXCEPT — emisores sin ninguna recarga

*Enunciado:* Obtener los IDs de usuarios que han enviado transacciones pero nunca han recargado su billetera.

```sql
CREATE VIEW v_emisores_sin_recarga AS
    SELECT b.id_usuario
      FROM Billetera b
      JOIN Transaccion t ON b.id_billetera = t.id_billetera_emisor
  EXCEPT
    SELECT b2.id_usuario
      FROM Billetera b2
      JOIN Recarga r ON b2.id_billetera = r.id_billetera;
```

*Consulta:*
```sql
SELECT u.nombre, u.apellido
FROM Usuario u
WHERE u.id_usuario IN (SELECT id_usuario FROM v_emisores_sin_recarga)
ORDER BY u.apellido;
```

#align(center)[
  #table(
    columns: 2,
    [*nombre*],[*apellido*],
    [Lucia],[Huaman],
    [Diego],[Rojas],
  )
  _(2 filas — enviaron transacciones pero nunca recargaron)_
]


== Vistas con JOIN y condición WHERE

=== V3: INNER JOIN — detalle de transacciones completadas

*Enunciado:* Mostrar las transacciones completadas con los nombres reales de emisor y receptor, filtrando únicamente las de estado `'Completada'`.

```sql
CREATE VIEW v_transacciones_detalle AS
SELECT t.id_transaccion,
       ue.nombre || ' ' || ue.apellido AS emisor,
       ur.nombre || ' ' || ur.apellido AS receptor,
       t.monto, t.fecha, t.estado
FROM Transaccion t
JOIN Billetera be ON t.id_billetera_emisor   = be.id_billetera
JOIN Billetera br ON t.id_billetera_receptor = br.id_billetera
JOIN Usuario   ue ON be.id_usuario = ue.id_usuario
JOIN Usuario   ur ON br.id_usuario = ur.id_usuario
WHERE t.estado = 'Completada';
```

```sql
SELECT * FROM v_transacciones_detalle;
```

#align(center)[
  #table(
    columns: (auto, 1fr, 1fr, auto, auto),
    [*id*],[*emisor*],[*receptor*],[*monto*],[*estado*],
    [1],[Carlos Bonifacio],[Eliaz Bobadilla],[50.00],[Completada],
    [2],[Leonardo Estacio],[Maria Quispe],[120.00],[Completada],
    [4],[Eliaz Bobadilla],[Jose Mamani],[80.00],[Completada],
    [5],[Jose Mamani],[Carlos Bonifacio],[200.00],[Completada],
    [7],[Lucia Huaman],[Ana Flores],[35.50],[Completada],
    [9],[Diego Rojas],[Leonardo Estacio],[500.00],[Completada],
    [10],[Maria Quispe],[Sofia Gutierrez],[75.00],[Completada],
    [11],[Carmen Soto],[Roberto Luna],[150.00],[Completada],
    [12],[Roberto Luna],[Valentina Cruz],[60.00],[Completada],
    [13],[Miguel Torres],[Carmen Soto],[320.00],[Completada],
    [14],[Daniela Paredes],[Miguel Torres],[45.00],[Completada],
  )
  _(11 filas — excluidas 4 transacciones no completadas)_
]


=== V4: LEFT JOIN — todos los usuarios activos con resumen de recargas

*Enunciado:* Mostrar todos los usuarios activos con el número y monto total de sus recargas. Los usuarios sin recargas aparecen con `0`.

```sql
CREATE VIEW v_usuarios_recargas AS
SELECT u.id_usuario,
       u.nombre || ' ' || u.apellido      AS usuario,
       COUNT(r.id_recarga)                 AS total_recargas,
       COALESCE(SUM(r.monto), 0::NUMERIC) AS monto_total
FROM Usuario u
LEFT JOIN Billetera b ON u.id_usuario   = b.id_usuario
LEFT JOIN Recarga   r ON b.id_billetera = r.id_billetera
WHERE u.estado = 'Activo'
GROUP BY u.id_usuario, u.nombre, u.apellido;
```

```sql
SELECT * FROM v_usuarios_recargas ORDER BY monto_total DESC;
```

#align(center)[
  #table(
    columns: 4,
    [*id*],[*usuario*],[*total_recargas*],[*monto_total*],
    [14],[Miguel Torres],   [1],[900.00],
    [8],[Diego Rojas],     [1],[800.00],
    [12],[Roberto Luna],   [1],[600.00],
    [3],[Leonardo Estacio],[2],[720.00],
    [5],[Jose Mamani],     [1],[400.00],
    [11],[Carmen Soto],    [1],[350.00],
    [1],[Carlos Bonifacio],[2],[350.00],
    [2],[Eliaz Bobadilla], [1],[300.00],
    [7],[Ana Flores],      [1],[250.00],
    [9],[Sofia Gutierrez], [1],[180.00],
    [15],[Daniela Paredes],[1],[175.00],
    [13],[Valentina Cruz], [1],[120.00],
    [4],[Maria Quispe],    [1],[100.00],
    [6],[Lucia Huaman],    [0],[0.00],
    [10],[Pedro Vargas],   [0],[0.00],
  )
  _(15 filas — Lucia y Pedro aparecen con 0 recargas gracias al LEFT JOIN)_
]


=== V5: RIGHT JOIN — todos los bancos con cuentas vinculadas

*Enunciado:* Mostrar todos los bancos del sistema (incluyendo los que no tienen cuentas vinculadas) con el número de cuentas de ahorro/corriente asociadas.

```sql
CREATE VIEW v_bancos_cuentas AS
SELECT bn.nombre                AS banco,
       COUNT(c.id_cuenta)       AS num_cuentas
FROM CuentaBancaria c
RIGHT JOIN Banco bn ON c.id_banco = bn.id_banco
WHERE bn.pais = 'Peru'
GROUP BY bn.nombre
ORDER BY num_cuentas DESC;
```

```sql
SELECT * FROM v_bancos_cuentas;
```

#align(center)[
  #table(
    columns: 2,
    [*banco*],[*num_cuentas*],
    [BCP],[5],[Interbank],[3],[BBVA],[2],[Scotiabank],[2],
    [Banco de la Nacion],[1],[BanBif],[1],[MiBanco],[1],
    [Banco Falabella],[0],[Banco GNB],[0],[Banco Pichincha],[0],
    [Banco Ripley],[0],[Alfin Banco],[0],[Caja Arequipa],[0],
    [Caja Huancayo],[0],[Caja Piura],[0],
  )
  _(15 filas — RIGHT JOIN muestra también los 8 bancos sin cuentas vinculadas)_
]


== Vistas Anidadas

=== V6: Resumen mensual (basada en `v_movimientos`)

*Enunciado:* A partir de la vista `v_movimientos`, calcular el volumen y número de operaciones agrupados por tipo y mes.

```sql
CREATE VIEW v_resumen_mensual AS
SELECT tipo,
       DATE_TRUNC('month', fecha)::DATE AS mes,
       COUNT(*)                          AS operaciones,
       SUM(monto)                        AS volumen
FROM v_movimientos
GROUP BY tipo, DATE_TRUNC('month', fecha)
ORDER BY mes, tipo;
```

```sql
SELECT * FROM v_resumen_mensual LIMIT 8;
```

#align(center)[
  #table(
    columns: 4,
    [*tipo*],[*mes*],[*operaciones*],[*volumen*],
    [Recarga],[2024-12-01],[1],[200.00],
    [Recarga],[2025-01-01],[2],[600.00],
    [Transaccion],[2025-01-01],[1],[50.00],
    [Recarga],[2025-02-01],[2],[500.00],
    [Transaccion],[2025-02-01],[2],[330.00],
    [Recarga],[2025-03-01],[1],[150.00],
    [Transaccion],[2025-03-01],[1],[80.00],
    [Transaccion],[2025-04-01],[2],[240.00],
  )
]


=== V7: Transacciones de alto valor (basada en `v_transacciones_detalle`)

*Enunciado:* A partir de la vista `v_transacciones_detalle`, filtrar únicamente las transacciones completadas por un monto mayor o igual a S/ 200.

```sql
CREATE VIEW v_transacciones_grandes AS
SELECT *
FROM v_transacciones_detalle
WHERE monto >= 200
ORDER BY monto DESC;
```

```sql
SELECT * FROM v_transacciones_grandes;
```

#align(center)[
  #table(
    columns: (auto, 1fr, 1fr, auto),
    [*id*],[*emisor*],[*receptor*],[*monto*],
    [9],[Diego Rojas],[Leonardo Estacio],[500.00],
    [13],[Miguel Torres],[Carmen Soto],[320.00],
    [5],[Jose Mamani],[Carlos Bonifacio],[200.00],
  )
  _(3 filas — transacciones completadas de S/ 200 o más)_
]


= Funciones

== Funciones con JOIN

=== Natural Join: `fn_natural_join_usuarios_billeteras`

*Enunciado:* Obtener el nombre, apellido, saldo y estado de billetera de todos los usuarios usando NATURAL JOIN (columna compartida: `id_usuario`).

```sql
CREATE OR REPLACE FUNCTION fn_natural_join_usuarios_billeteras()
RETURNS TABLE(
    nombre           VARCHAR,
    apellido         VARCHAR,
    saldo            NUMERIC,
    estado_billetera VARCHAR
) AS $$
BEGIN
    RETURN QUERY
    SELECT u.nombre, u.apellido, b.saldo, b.estado
    FROM Usuario u
    NATURAL JOIN Billetera b
    ORDER BY u.apellido, u.nombre;
END;
$$ LANGUAGE plpgsql;
```

```sql
SELECT * FROM fn_natural_join_usuarios_billeteras();
```

#align(center)[
  #table(
    columns: 4,
    [*nombre*],[*apellido*],[*saldo*],[*estado_billetera*],
    [Eliaz],[Bobadilla],[580.00],[Activa],
    [Carlos],[Bonifacio],[320.00],[Activa],
    [Valentina],[Cruz],[130.00],[Activa],
    [Leonardo],[Estacio],[450.00],[Activa],
    [...],[...],[...],[...],
  )
  _(15 filas)_
]


=== Theta Join: `fn_theta_transacciones_bajo_saldo`

*Enunciado:* Listar las transacciones donde el monto enviado fue *estrictamente menor* al saldo actual de la billetera emisora (condición theta con operador `<`).

```sql
CREATE OR REPLACE FUNCTION fn_theta_transacciones_bajo_saldo()
RETURNS TABLE(
    id_transaccion INT,
    emisor         TEXT,
    monto          NUMERIC,
    saldo_actual   NUMERIC
) AS $$
BEGIN
    RETURN QUERY
    SELECT t.id_transaccion,
           u.nombre || ' ' || u.apellido,
           t.monto,
           b.saldo
    FROM Transaccion t
    JOIN Billetera b ON t.id_billetera_emisor = b.id_billetera
                     AND t.monto < b.saldo
    JOIN Usuario u ON b.id_usuario = u.id_usuario
    ORDER BY t.id_transaccion;
END;
$$ LANGUAGE plpgsql;
```

```sql
SELECT * FROM fn_theta_transacciones_bajo_saldo();
```

#align(center)[
  #table(
    columns: 4,
    [*id_transaccion*],[*emisor*],[*monto*],[*saldo_actual*],
    [1],[Carlos Bonifacio],[50.00],[320.00],
    [2],[Leonardo Estacio],[120.00],[450.00],
    [4],[Eliaz Bobadilla],[80.00],[580.00],
    [5],[Jose Mamani],[200.00],[780.00],
    [6],[Carlos Bonifacio],[40.00],[320.00],
    [7],[Lucia Huaman],[35.50],[150.00],
    [8],[Ana Flores],[300.00],[620.00],
    [9],[Diego Rojas],[500.00],[1100.00],
    [10],[Maria Quispe],[75.00],[220.00],
    [11],[Carmen Soto],[150.00],[270.00],
    [12],[Roberto Luna],[60.00],[490.00],
    [13],[Miguel Torres],[320.00],[860.00],
    [14],[Daniela Paredes],[45.00],[215.00],
    [15],[Valentina Cruz],[90.00],[130.00],
  )
  _(14 filas — excluida transacción 3: monto 250 > saldo 220)_
]


=== Left Join: `fn_left_usuarios_total_enviado`

*Enunciado:* Mostrar todos los usuarios con el total acumulado enviado en transacciones. Los usuarios que nunca enviaron aparecen con S/ 0.

```sql
CREATE OR REPLACE FUNCTION fn_left_usuarios_total_enviado()
RETURNS TABLE(usuario TEXT, total_enviado NUMERIC) AS $$
BEGIN
    RETURN QUERY
    SELECT u.nombre || ' ' || u.apellido,
           COALESCE(SUM(t.monto), 0::NUMERIC)
    FROM Usuario u
    LEFT JOIN Billetera b   ON u.id_usuario   = b.id_usuario
    LEFT JOIN Transaccion t ON b.id_billetera = t.id_billetera_emisor
    GROUP BY u.id_usuario, u.nombre, u.apellido
    ORDER BY COALESCE(SUM(t.monto), 0) DESC;
END;
$$ LANGUAGE plpgsql;
```

#align(center)[
  #table(
    columns: 2,
    [*usuario*],[*total_enviado*],
    [Diego Rojas],[500.00],
    [Maria Quispe],[325.00],
    [Miguel Torres],[320.00],
    [Ana Flores],[300.00],
    [Jose Mamani],[200.00],
    [Carmen Soto],[150.00],
    [Leonardo Estacio],[120.00],
    [Carlos Bonifacio],[90.00],
    [Valentina Cruz],[90.00],
    [Eliaz Bobadilla],[80.00],
    [Roberto Luna],[60.00],
    [Daniela Paredes],[45.00],
    [Lucia Huaman],[35.50],
    [Sofia Gutierrez],[0.00],
    [Pedro Vargas],[0.00],
  )
  _(15 filas — Sofia y Pedro con total = 0 gracias al LEFT JOIN)_
]


=== Right Join: `fn_right_bancos_num_cuentas`

*Enunciado:* Listar todos los bancos del sistema con el número de cuentas vinculadas. Los bancos sin cuentas aparecen con conteo 0.

```sql
CREATE OR REPLACE FUNCTION fn_right_bancos_num_cuentas()
RETURNS TABLE(banco VARCHAR, num_cuentas BIGINT) AS $$
BEGIN
    RETURN QUERY
    SELECT bn.nombre, COUNT(c.id_cuenta)
    FROM CuentaBancaria c
    RIGHT JOIN Banco bn ON c.id_banco = bn.id_banco
    GROUP BY bn.nombre
    ORDER BY COUNT(c.id_cuenta) DESC;
END;
$$ LANGUAGE plpgsql;
```


== Función de Inserción: `fn_registrar_usuario`

*Enunciado:* Registrar un nuevo usuario en el sistema creando automáticamente su billetera con saldo S/ 0.00. Retorna el `id_usuario` asignado.

```sql
CREATE OR REPLACE FUNCTION fn_registrar_usuario(
    p_dni TEXT, p_nombre TEXT, p_apellido TEXT,
    p_celular TEXT, p_email TEXT
) RETURNS INT AS $$
DECLARE
    v_id INT;
BEGIN
    INSERT INTO Usuario(dni, nombre, apellido, celular, email)
    VALUES (p_dni, p_nombre, p_apellido, p_celular, p_email)
    RETURNING id_usuario INTO v_id;

    INSERT INTO Billetera(id_usuario, saldo, moneda, fecha_creacion, estado)
    VALUES (v_id, 0.00, 'PEN', CURRENT_DATE, 'Activa');

    RETURN v_id;
END;
$$ LANGUAGE plpgsql;
```

*Prueba (aceptada):*
```sql
SELECT fn_registrar_usuario(
    '95000001','Roberto','Sanchez',
    '950000001','roberto.sanchez@ewallet.pe'
) AS nuevo_id_usuario;
-- Resultado: nuevo_id_usuario = 16
```


*Prueba (rechazada — DNI duplicado):*
```sql
SELECT fn_registrar_usuario(
    '73829142','Roberto','Sanchez',
    '950000002','roberto2@ewallet.pe'
);
-- ERROR: duplicate key value violates unique constraint "usuario_dni_key"
```


== Función de Actualización: `fn_actualizar_saldo`

*Enunciado:* Actualizar el saldo de una billetera activa. Valida que el nuevo saldo sea no negativo y que la billetera exista y esté activa.

```sql
CREATE OR REPLACE FUNCTION fn_actualizar_saldo(
    p_id_billetera INT,
    p_nuevo_saldo  NUMERIC
) RETURNS TEXT AS $$
BEGIN
    IF p_nuevo_saldo < 0 THEN
        RAISE EXCEPTION 'Saldo no puede ser negativo: %', p_nuevo_saldo;
    END IF;

    UPDATE Billetera
    SET saldo = p_nuevo_saldo
    WHERE id_billetera = p_id_billetera AND estado = 'Activa';

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Billetera % no existe o no está activa',
            p_id_billetera;
    END IF;

    RETURN 'Saldo de billetera ' || p_id_billetera
        || ' actualizado a S/ ' || p_nuevo_saldo;
END;
$$ LANGUAGE plpgsql;
```

*Prueba aceptada:*
```sql
SELECT fn_actualizar_saldo(1, 500.00);
-- Resultado: 'Saldo de billetera 1 actualizado a S/ 500.00'
```

*Prueba rechazada:*
```sql
SELECT fn_actualizar_saldo(1, -100.00);
-- ERROR: Saldo no puede ser negativo: -100.00
```

== Funciones de Eliminación

=== `fn_desactivar_dispositivo` (eliminación lógica)

*Enunciado:* Marcar un dispositivo como inactivo (soft delete). Si el dispositivo no existe o ya está inactivo, lanza excepción.

```sql
CREATE OR REPLACE FUNCTION fn_desactivar_dispositivo(p_id INT)
RETURNS TEXT AS $$
BEGIN
    UPDATE Dispositivo SET activo = FALSE
    WHERE id_dispositivo = p_id AND activo = TRUE;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Dispositivo % no existe o ya estaba inactivo', p_id;
    END IF;

    RETURN 'Dispositivo ' || p_id || ' desactivado';
END;
$$ LANGUAGE plpgsql;
```

```sql
SELECT fn_desactivar_dispositivo(1);
-- Resultado: 'Dispositivo 1 desactivado'
```

=== `fn_eliminar_contacto` (eliminación física)

*Enunciado:* Eliminar un contacto de la agenda de un usuario dado el ID del usuario propietario y el ID del usuario contacto.

```sql
CREATE OR REPLACE FUNCTION fn_eliminar_contacto(
    p_id_usuario INT, p_id_usuario_contacto INT
) RETURNS TEXT AS $$
DECLARE n INT;
BEGIN
    DELETE FROM Contacto
    WHERE id_usuario           = p_id_usuario
      AND id_usuario_contacto  = p_id_usuario_contacto;

    GET DIAGNOSTICS n = ROW_COUNT;
    IF n = 0 THEN RETURN 'Contacto no encontrado'; END IF;
    RETURN 'Contacto eliminado correctamente';
END;
$$ LANGUAGE plpgsql;
```

```sql
SELECT fn_eliminar_contacto(1, 2);
-- Resultado: 'Contacto eliminado correctamente'
```

== Trigger: Notificación Automática de Transacciones

*Enunciado:* Al insertar una transacción con estado `'Completada'`, el trigger genera automáticamente una notificación para el usuario receptor indicando el monto recibido y el nombre del emisor.

```sql
CREATE OR REPLACE FUNCTION trg_fn_notificar_transaccion()
RETURNS TRIGGER AS $$
DECLARE
    v_id_receptor   INT;
    v_nombre_emisor TEXT;
BEGIN
    IF NEW.estado = 'Completada' THEN
        SELECT b.id_usuario INTO v_id_receptor
          FROM Billetera b
         WHERE b.id_billetera = NEW.id_billetera_receptor;

        SELECT u.nombre INTO v_nombre_emisor
          FROM Billetera b
          JOIN Usuario u ON b.id_usuario = u.id_usuario
         WHERE b.id_billetera = NEW.id_billetera_emisor;

        INSERT INTO Notificacion(id_usuario, id_transaccion, tipo, mensaje)
        VALUES (
            v_id_receptor,
            NEW.id_transaccion,
            'Transaccion',
            'Recibiste S/ ' || NEW.monto || ' de ' || v_nombre_emisor
        );
    END IF;
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER trg_notificar_transaccion
AFTER INSERT ON Transaccion
FOR EACH ROW EXECUTE FUNCTION trg_fn_notificar_transaccion();
```

*Prueba:*
```sql
INSERT INTO Transaccion(id_billetera_emisor,id_billetera_receptor,
                         monto,mensaje,estado)
    VALUES (3, 5, 75.00, 'Prueba trigger', 'Completada');

SELECT * FROM Notificacion ORDER BY id_notificacion DESC LIMIT 1;
```

*Resultado esperado:*

#align(center)[
  #table(
    columns: (auto, auto, auto, 1fr, auto, auto),
    [*id*],[*id_usuario*],[*id_trans*],[*mensaje*],[*tipo*],[*leida*],
    [16],[5],[16],[Recibiste S/ 75.00 de Leonardo],[Transaccion],[f],
  )
  _(El trigger creó la notificación automáticamente para Jose Mamani)_
]


== Stored Procedure: Transferencia P2P Completa

*Enunciado:* Ejecutar una transferencia P2P completa y atómica: debitar la billetera emisora, acreditar la receptora e insertar el registro de transacción. Verifica que el emisor tenga saldo suficiente.

```sql
CREATE OR REPLACE PROCEDURE sp_transferencia(
    p_emisor   INT,
    p_receptor INT,
    p_monto    NUMERIC,
    p_mensaje  TEXT DEFAULT NULL
) AS $$
DECLARE v_saldo NUMERIC;
BEGIN
    SELECT saldo INTO v_saldo
      FROM Billetera
     WHERE id_billetera = p_emisor AND estado = 'Activa'
       FOR UPDATE;

    IF v_saldo IS NULL THEN
        RAISE EXCEPTION 'Billetera % no existe o no está activa', p_emisor;
    END IF;

    IF v_saldo < p_monto THEN
        RAISE EXCEPTION
            'Saldo insuficiente: disponible S/ %, requerido S/ %',
            v_saldo, p_monto;
    END IF;

    UPDATE Billetera SET saldo = saldo - p_monto WHERE id_billetera = p_emisor;
    UPDATE Billetera SET saldo = saldo + p_monto WHERE id_billetera = p_receptor;

    INSERT INTO Transaccion(id_billetera_emisor, id_billetera_receptor,
                             monto, mensaje, estado)
    VALUES (p_emisor, p_receptor, p_monto, p_mensaje, 'Completada');
END;
$$ LANGUAGE plpgsql;
```

*Prueba aceptada:* (billetera 2 envía S/ 50 a billetera 3)
```sql
CALL sp_transferencia(2, 3, 50.00, 'Prueba stored procedure');
SELECT id_billetera, saldo FROM Billetera WHERE id_billetera IN (2, 3);
-- Billetera 2: 580 - 50 = 530.00
-- Billetera 3: 450 + 50 = 500.00
```

#align(center)[
  #table(
    columns: 2,
    [*id_billetera*],[*saldo*],
    [2],[530.00],
    [3],[500.00],
  )
]


*Prueba rechazada:* (monto mayor al saldo disponible)
```sql
CALL sp_transferencia(2, 3, 99999.00, 'Fallo esperado');
-- ERROR: Saldo insuficiente: disponible S/ 530.00, requerido S/ 99999.00
```


== Aplicación CRUD con tkinter y psycopg2

*Enunciado:* Desarrollar una aplicación de escritorio en Python que se conecte a la base de datos `billetera_digital` mediante la biblioteca `psycopg2` y permita realizar las cuatro operaciones CRUD sobre la tabla `Usuario` usando cursores parametrizados.

=== Arquitectura

#align(center)[
  #table(
    columns: (auto, 1fr),
    [*Componente*],[*Descripción*],
    [Interfaz],        [tkinter — ventana principal con formulario, Treeview y barra de estado],
    [Conexión],        [`psycopg2.connect(**DB_CONFIG)` — conexión directa a PostgreSQL],
    [Cursores],        [`conn.cursor()` — cursor estándar de psycopg2 para todas las operaciones],
    [Parámetros],      [Consultas parametrizadas con `%s` (previenen SQL injection)],
    [CRUD],            [Consulta (`SELECT`), Inserción (`INSERT`), Actualización (`UPDATE`), Eliminación (`DELETE`)],
  )
]

=== Operaciones CRUD implementadas

*C — Inserción:* Al pulsar "Insertar", se ejecutan dos INSERTs en la misma conexión:
```python
cur.execute("""
    INSERT INTO Usuario(dni, nombre, apellido, celular, email)
    VALUES (%s, %s, %s, %s, %s)
    RETURNING id_usuario
""", (dni, nombre, apellido, celular, email))
nuevo_id = cur.fetchone()[0]

cur.execute("""
    INSERT INTO Billetera(id_usuario, saldo, moneda, fecha_creacion, estado)
    VALUES (%s, 0.00, 'PEN', CURRENT_DATE, 'Activa')
""", (nuevo_id,))
conn.commit()
```

*R — Consulta:* Al pulsar "Actualizar lista", se ejecuta:
```python
cur.execute("""
    SELECT id_usuario, dni, nombre, apellido,
           celular, email, fecha_registro, estado
    FROM Usuario ORDER BY id_usuario
""")
rows = cur.fetchall()
```

*U — Actualización:* Al pulsar "Actualizar" con un usuario seleccionado:
```python
cur.execute("""
    UPDATE Usuario
    SET nombre=%s, apellido=%s, celular=%s, email=%s
    WHERE id_usuario=%s
""", (nombre, apellido, celular, email, user_id))
conn.commit()
```

*D — Eliminación:* Al pulsar "Eliminar" tras confirmar el diálogo:
```python
cur.execute("DELETE FROM Usuario WHERE id_usuario=%s", (user_id,))
conn.commit()
```


= Conclusiones

La Fase III consolidó la implementación de objetos avanzados sobre la base de datos de la billetera digital, con las siguientes conclusiones principales:

- *Dominios:* La definición de seis dominios (`dom_email`, `dom_monto_pos`, `dom_dni_pe`, `dom_celular_pe`, `dom_moneda_iso`, `dom_estado_gen`) permite encapsular las reglas de validación en un único punto, reduciendo la duplicación de restricciones CHECK en múltiples tablas y facilitando el mantenimiento.

- *Integridad referencial probada:* Las demostraciones de restricciones NOT NULL, UNIQUE, CHECK, clave foránea y a nivel de tupla confirman que el motor de PostgreSQL intercepta correctamente los intentos de inserción, eliminación y actualización que violan la integridad. Ningún caso rechazado requirió código en la capa de aplicación.

- *Índices estratégicos:* Los cinco índices creados responden a patrones de consulta reales del dominio (login por celular, filtros por estado, bandeja de notificaciones, historial reciente, operaciones sobre billeteras activas). El índice parcial sobre `Billetera WHERE estado = 'Activa'` ilustra cómo reducir el tamaño del índice cuando la mayoría de consultas operacionales solo acceden a un subconjunto de filas.

- *Vistas anidadas y operaciones de conjuntos:* La cadena `v_movimientos` → `v_resumen_mensual` y `v_transacciones_detalle` → `v_transacciones_grandes` demuestra que las vistas pueden actuar como capas de abstracción sobre las que se construyen análisis más específicos, sin reescribir la lógica base.

- *PL/pgSQL y triggers:* El trigger `trg_notificar_transaccion` automatiza la generación de notificaciones, eliminando la necesidad de que la capa de aplicación lo gestione. El stored procedure `sp_transferencia` encapsula la atomicidad de una transferencia P2P (débito, crédito y registro) en una sola llamada, protegida con `FOR UPDATE` para entornos concurrentes.

- *Aplicación CRUD:* La aplicación tkinter con psycopg2 verifica que la base de datos puede ser consumida desde una aplicación externa utilizando cursores y consultas parametrizadas, previniendo inyección SQL y manteniendo la integridad de los datos.

= Referencias Bibliográficas

+ Ramakrishnan, R., & Gehrke, J. (2003). _Database Management Systems_ (3rd ed.). McGraw-Hill.

+ Elmasri, R., & Navathe, S. B. (2016). _Fundamentals of Database Systems_ (7th ed.). Pearson.

+ Date, C. J. (2004). _An Introduction to Database Systems_ (8th ed.). Addison-Wesley.

+ PostgreSQL Global Development Group. (2024). _PostgreSQL 17 Documentation — Chapter 43: PL/pgSQL_. Recuperado de #link("https://www.postgresql.org/docs/17/plpgsql.html")

+ PostgreSQL Global Development Group. (2024). _PostgreSQL 17 Documentation — CREATE DOMAIN_. Recuperado de #link("https://www.postgresql.org/docs/17/sql-createdomain.html")

+ Gregoriadis, L. (2022). _Mastering PostgreSQL 15_ (5th ed.). Packt Publishing.

= Anexos

== Anexo A: Archivo SQL — `fase3.sql`

El archivo `fase3.sql` contiene todos los objetos SQL creados en esta Fase III, organizados en las secciones correspondientes a cada punto del enunciado. Se adjunta junto al presente informe como entregable independiente.

== Anexo B: Aplicación CRUD — `crud_app.py`

El archivo `crud_app.py` contiene la aplicación de escritorio desarrollada en Python con las bibliotecas `tkinter` (GUI) y `psycopg2` (conexión a PostgreSQL). Requisito de instalación: `pip install psycopg2-binary`. Ejecución: `python crud_app.py`.

== Anexo C: Diagrama Relacional — Fase II (referencia)

#align(center)[
  #image("diagrama_3.svg", width: 100%)
  *Figura C.1.* Diagrama relacional de la Fase II — esquema base de la Fase III (10 tablas, 3FN).
]
