#set page(paper: "a4", margin: (x: 2.5cm, y: 2.5cm), numbering: "1")
#set text(font: "Arial", size: 12pt, lang: "es")
#set par(leading: 0.65em, justify: true)
#set heading(numbering: "1.")

#show raw: set text(font: "Courier New", size: 10pt)
#show raw.where(block: true): block.with(
  fill: rgb("#f4f4f4"), inset: 8pt, radius: 3pt, width: 100%,
)
#set table(stroke: 0.5pt + black, inset: 4pt)
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
  #text(size: 14pt, weight: "bold")[Fase II — Desarrollo de la Base de Datos]
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

El presente informe corresponde a la *Fase II* del Proyecto Formativo del curso de Base de Datos, cuyo caso de estudio es el diseño e implementación de una *billetera digital (e-wallet)* inspirada en servicios peruanos como Yape y Plin. En esta fase se construye la base de datos relacional en *PostgreSQL*, partiendo del modelo conceptual elaborado en la Fase I.

Los entregables comprenden: (1) normalización del modelo relacional hasta la Tercera Forma Normal (3FN); (2) implementación de diez tablas con restricciones de integridad, tipos de datos y claves; (3) población de cada tabla con quince registros fidedignos al dominio; (4) nueve consultas SQL que cubren los operadores de selección, proyección, unión, intersección, diferencia, producto cartesiano, theta join, left join y right join; y (5) gestión de roles y usuarios con scripts de creación, asignación y revocación de permisos.

= Caso de Estudio

== Identificación del Problema

Las aplicaciones de pago móvil permiten a los usuarios gestionar dinero electrónico desde sus teléfonos. En el contexto peruano, servicios como Yape (BCP) y Plin (BBVA, Interbank, Scotiabank) han masificado este modelo. El reto es diseñar una base de datos que soporte de manera íntegra:

- La gestión de *saldos* y su consistencia ante operaciones simultáneas.
- El registro de *transacciones P2P* (persona a persona) con trazabilidad completa.
- La vinculación de *cuentas bancarias y tarjetas* de múltiples bancos como fuentes de recarga.
- La gestión de *contactos frecuentes* y *notificaciones* en tiempo real.
- El control de *dispositivos registrados* para seguridad y notificaciones push.

== Planteamiento de la Solución

La solución es una base de datos relacional en PostgreSQL compuesta por diez tablas normalizadas hasta 3FN. El modelo distingue entidades de negocio (Usuario, Billetera, Transaccion, CuentaBancaria, Tarjeta, Banco) de entidades de soporte (Contacto, Recarga, Notificacion, Dispositivo). Las restricciones de integridad referencial, los tipos de datos adecuados y las condiciones CHECK garantizan la consistencia de los datos.

= Implementación de la Solución

== Normalización del Modelo Inicial

=== Modelo Relacional de la Fase I

El modelo relacional de la Fase I contaba con ocho relaciones. El diagrama original se presenta a continuación:

#align(center)[
  #image("diagrama_2.svg", width: 90%)
  *Figura 1.* Diagrama relacional de la Fase I (8 tablas).
]

=== Análisis de Normalización

==== Primera Forma Normal (1FN)

Una relación está en 1FN si todos sus atributos son atómicos y no existen grupos repetitivos. El modelo de la Fase I ya cumple esta condición: cada atributo almacena un único valor por tupla.

*Resultado:* Sin cambios. El modelo ya estaba en 1FN.

==== Segunda Forma Normal (2FN)

Una relación está en 2FN si está en 1FN y todos los atributos no clave dependen completamente de la clave primaria (sin dependencias parciales). Las dependencias parciales solo ocurren con claves compuestas.

Todas las tablas de la Fase I usan claves primarias simples surrogadas (SERIAL), por lo que no existen dependencias parciales. Dependencias funcionales representativas:

- `id_usuario → {dni, nombre, apellido, celular, email, fecha_registro, estado}`
- `id_billetera → {id_usuario, saldo, moneda, fecha_creacion, estado}`
- `id_transaccion → {id_billetera_emisor, id_billetera_receptor, monto, fecha, mensaje, estado}`

*Resultado:* Sin cambios. El modelo ya estaba en 2FN.

==== Tercera Forma Normal (3FN)

Una relación está en 3FN si está en 2FN y no existen dependencias transitivas: ningún atributo no clave depende de otro atributo no clave.

*Anomalía detectada:* En la Fase I, el atributo `banco` (VARCHAR) aparecía como texto libre en las tablas `CuentaBancaria` y `Tarjeta`. Esto genera la siguiente dependencia transitiva:

#align(center)[`id_cuenta → banco → {codigo_bic, pais}`]

Donde el nombre del banco determina atributos propios de la institución bancaria. Esto genera anomalías:

- *Actualización:* Si un banco cambia de nombre, hay que actualizar múltiples filas en dos tablas.
- *Inserción:* No es posible registrar un banco sin asociarlo a una cuenta o tarjeta.
- *Eliminación:* Al eliminar todas las cuentas de un banco, se pierde la información del banco.
- *Redundancia:* El mismo nombre de banco se repite en múltiples filas sin garantía de consistencia.

*Solución (3FN):* Extraer la entidad `Banco(id_banco, nombre, codigo_bic, pais)`. Ambas tablas referencian a `Banco` mediante FK `id_banco`.

*Adición complementaria:* Se incorpora la tabla `Dispositivo` para registrar los dispositivos móviles de los usuarios, necesaria para notificaciones push y autenticación por dispositivo.

*Resumen de cambios:*

#align(center)[
  #table(
    columns: (auto, 1fr, 1fr),
    [*Tabla*], [*Atributo en Fase I*], [*Cambio en Fase II*],
    [CuentaBancaria], [`banco VARCHAR`], [`id_banco INT FK → Banco`],
    [Tarjeta], [`banco VARCHAR`], [`id_banco INT FK → Banco`],
    [Notificacion], [sin `leida`], [`leida BOOLEAN` agregado],
    [—], [sin tabla Banco], [Tabla `Banco` nueva (3FN)],
    [—], [sin tabla Dispositivo], [Tabla `Dispositivo` nueva],
  )
]

=== Modelo Relacional Actualizado

#align(center)[
  #image("diagrama_3.svg", width: 100%)
  *Figura 2.* Diagrama relacional actualizado — Fase II (10 tablas, 3FN).
]

== Base de Datos y Tablas Implementadas

Se implementaron diez tablas en PostgreSQL. A continuación se describe el propósito y estructura de cada una.

=== Tabla 1: Banco

*Propósito:* Catálogo de bancos disponibles en el sistema. Normaliza la referencia a instituciones bancarias desde CuentaBancaria y Tarjeta (mejora de 3FN).

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Columna*], [*Tipo*], [*Descripción*],
    [`id_banco`], [`SERIAL`], [Identificador único del banco (PK)],
    [`nombre`], [`VARCHAR(60)`], [Nombre oficial de la institución (UNIQUE)],
    [`codigo_bic`], [`VARCHAR(20)`], [Código BIC/SWIFT internacional (nullable)],
    [`pais`], [`VARCHAR(50)`], [País de operación (default 'Peru')],
  )
]

=== Tabla 2: Usuario

*Propósito:* Registra a las personas naturales que usan el sistema. Cada usuario tiene exactamente una billetera.

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Columna*], [*Tipo*], [*Descripción*],
    [`id_usuario`], [`SERIAL`], [Identificador único del usuario (PK)],
    [`dni`], [`CHAR(8)`], [DNI peruano de 8 dígitos (UNIQUE)],
    [`nombre`], [`VARCHAR(50)`], [Primer nombre del usuario],
    [`apellido`], [`VARCHAR(50)`], [Apellido paterno],
    [`celular`], [`CHAR(9)`], [Celular peruano a 9 dígitos (UNIQUE)],
    [`email`], [`VARCHAR(100)`], [Correo electrónico (UNIQUE)],
    [`fecha_registro`], [`DATE`], [Fecha de registro en la aplicación],
    [`estado`], [`VARCHAR(20)`], [Activo / Bloqueado / Inactivo (CHECK)],
  )
]

=== Tabla 3: Billetera

*Propósito:* Almacena el saldo electrónico de cada usuario. Relación 1:1 con Usuario (FK UNIQUE).

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Columna*], [*Tipo*], [*Descripción*],
    [`id_billetera`], [`SERIAL`], [Identificador único de la billetera (PK)],
    [`id_usuario`], [`INT`], [FK a Usuario — relación 1:1 (UNIQUE)],
    [`saldo`], [`NUMERIC(12,2)`], [Saldo actual (≥ 0, CHECK)],
    [`moneda`], [`CHAR(3)`], [Código ISO 4217 (default 'PEN')],
    [`fecha_creacion`], [`DATE`], [Fecha de apertura de la billetera],
    [`estado`], [`VARCHAR(20)`], [Activa / Bloqueada / Cerrada (CHECK)],
  )
]

=== Tabla 4: Dispositivo

*Propósito:* Registra los dispositivos móviles por usuario para notificaciones push y control de acceso.

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Columna*], [*Tipo*], [*Descripción*],
    [`id_dispositivo`], [`SERIAL`], [Identificador único del dispositivo (PK)],
    [`id_usuario`], [`INT`], [FK a Usuario (un usuario puede tener varios)],
    [`modelo`], [`VARCHAR(100)`], [Modelo del dispositivo],
    [`sistema_operativo`], [`VARCHAR(50)`], [Sistema operativo y versión],
    [`token_push`], [`VARCHAR(255)`], [Token FCM/APNs para notificaciones],
    [`fecha_registro`], [`TIMESTAMP`], [Fecha y hora de registro del dispositivo],
    [`activo`], [`BOOLEAN`], [TRUE si el dispositivo está habilitado],
  )
]

=== Tabla 5: CuentaBancaria

*Propósito:* Cuentas bancarias vinculadas a cada billetera, usadas como origen de recargas. Referencia a Banco mediante FK (mejora de 3FN).

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Columna*], [*Tipo*], [*Descripción*],
    [`id_cuenta`], [`SERIAL`], [Identificador único de la cuenta (PK)],
    [`id_billetera`], [`INT`], [FK a Billetera],
    [`id_banco`], [`INT`], [FK a Banco — reemplaza banco VARCHAR de Fase I],
    [`numero_cuenta`], [`VARCHAR(20)`], [Número de cuenta bancaria (UNIQUE)],
    [`tipo_cuenta`], [`VARCHAR(20)`], [Ahorros o Corriente (CHECK)],
    [`fecha_vinculacion`], [`DATE`], [Fecha de vinculación a la billetera],
  )
]

=== Tabla 6: Tarjeta

*Propósito:* Tarjetas de débito/crédito vinculadas a cada billetera como medio alternativo de recarga. Referencia a Banco mediante FK (mejora de 3FN).

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Columna*], [*Tipo*], [*Descripción*],
    [`id_tarjeta`], [`SERIAL`], [Identificador único de la tarjeta (PK)],
    [`id_billetera`], [`INT`], [FK a Billetera],
    [`id_banco`], [`INT`], [FK a Banco — reemplaza banco VARCHAR de Fase I],
    [`ultimos_4_digitos`], [`CHAR(4)`], [Últimos 4 dígitos del número de tarjeta],
    [`tipo`], [`VARCHAR(20)`], [Debito o Credito (CHECK)],
    [`fecha_vencimiento`], [`DATE`], [Fecha de vencimiento de la tarjeta],
  )
]

=== Tabla 7: Contacto

*Propósito:* Agenda de contactos de cada usuario. Permite guardar otros usuarios del sistema con un alias personalizado.

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Columna*], [*Tipo*], [*Descripción*],
    [`id_contacto`], [`SERIAL`], [Identificador único del contacto (PK)],
    [`id_usuario`], [`INT`], [FK a Usuario — dueño de la agenda],
    [`id_usuario_contacto`], [`INT`], [FK a Usuario — usuario guardado],
    [`alias`], [`VARCHAR(50)`], [Nombre personalizado del contacto (nullable)],
    [`fecha_agregado`], [`DATE`], [Fecha en que se agregó el contacto],
  )
]

=== Tabla 8: Recarga

*Propósito:* Registra operaciones de carga de saldo a una billetera desde cuenta bancaria o tarjeta. Un CHECK garantiza que solo uno de los dos orígenes esté presente.

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Columna*], [*Tipo*], [*Descripción*],
    [`id_recarga`], [`SERIAL`], [Identificador único de la recarga (PK)],
    [`id_billetera`], [`INT`], [FK a Billetera receptora],
    [`id_cuenta`], [`INT`], [FK a CuentaBancaria — origen (nullable)],
    [`id_tarjeta`], [`INT`], [FK a Tarjeta — origen alternativo (nullable)],
    [`monto`], [`NUMERIC(12,2)`], [Monto de recarga (> 0, CHECK)],
    [`fecha`], [`TIMESTAMP`], [Fecha y hora de la operación],
    [`estado`], [`VARCHAR(20)`], [Exitosa / Fallida / Pendiente (CHECK)],
  )
]

=== Tabla 9: Transaccion

*Propósito:* Registra cada transferencia P2P entre dos billeteras. Garantiza que emisor ≠ receptor mediante CHECK.

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Columna*], [*Tipo*], [*Descripción*],
    [`id_transaccion`], [`SERIAL`], [Identificador único de la transacción (PK)],
    [`id_billetera_emisor`], [`INT`], [FK a Billetera — origen del dinero],
    [`id_billetera_receptor`], [`INT`], [FK a Billetera — destino del dinero],
    [`monto`], [`NUMERIC(12,2)`], [Monto transferido (> 0, CHECK)],
    [`fecha`], [`TIMESTAMP`], [Fecha y hora de la transacción],
    [`mensaje`], [`VARCHAR(255)`], [Concepto de la transferencia (nullable)],
    [`estado`], [`VARCHAR(20)`], [Completada / Pendiente / Fallida (CHECK)],
  )
]

=== Tabla 10: Notificacion

*Propósito:* Alertas generadas por el sistema para los usuarios por transacciones, recargas o mensajes. El atributo `leida` es nuevo en Fase II.

#align(center)[
  #table(
    columns: (auto, auto, 1fr),
    [*Columna*], [*Tipo*], [*Descripción*],
    [`id_notificacion`], [`SERIAL`], [Identificador único de la notificación (PK)],
    [`id_usuario`], [`INT`], [FK a Usuario — destinatario],
    [`id_transaccion`], [`INT`], [FK a Transaccion (nullable)],
    [`tipo`], [`VARCHAR(30)`], [Transaccion / Recarga / Sistema (CHECK)],
    [`mensaje`], [`VARCHAR(255)`], [Texto de la notificación],
    [`fecha`], [`TIMESTAMP`], [Fecha y hora de generación],
    [`leida`], [`BOOLEAN`], [TRUE si el usuario ya leyó la notificación],
  )
]

=== Script DDL de Creación de Tablas

```sql
-- ================================================
-- BASE DE DATOS: billetera_digital
-- Fase 2 – Proyecto Formativo de Base de Datos
-- ================================================

CREATE DATABASE billetera_digital
    WITH ENCODING = 'UTF8' TEMPLATE = template0;

\c billetera_digital

CREATE TABLE Banco (
    id_banco     SERIAL        PRIMARY KEY,
    nombre       VARCHAR(60)   NOT NULL UNIQUE,
    codigo_bic   VARCHAR(20),
    pais         VARCHAR(50)   NOT NULL DEFAULT 'Peru'
);

CREATE TABLE Usuario (
    id_usuario      SERIAL       PRIMARY KEY,
    dni             CHAR(8)      NOT NULL UNIQUE,
    nombre          VARCHAR(50)  NOT NULL,
    apellido        VARCHAR(50)  NOT NULL,
    celular         CHAR(9)      NOT NULL UNIQUE,
    email           VARCHAR(100) NOT NULL UNIQUE,
    fecha_registro  DATE         NOT NULL DEFAULT CURRENT_DATE,
    estado          VARCHAR(20)  NOT NULL DEFAULT 'Activo'
                    CHECK (estado IN ('Activo', 'Bloqueado', 'Inactivo'))
);

CREATE TABLE Billetera (
    id_billetera    SERIAL        PRIMARY KEY,
    id_usuario      INT           NOT NULL UNIQUE REFERENCES Usuario(id_usuario),
    saldo           NUMERIC(12,2) NOT NULL DEFAULT 0.00 CHECK (saldo >= 0),
    moneda          CHAR(3)       NOT NULL DEFAULT 'PEN',
    fecha_creacion  DATE          NOT NULL DEFAULT CURRENT_DATE,
    estado          VARCHAR(20)   NOT NULL DEFAULT 'Activa'
                    CHECK (estado IN ('Activa', 'Bloqueada', 'Cerrada'))
);

CREATE TABLE Dispositivo (
    id_dispositivo    SERIAL        PRIMARY KEY,
    id_usuario        INT           NOT NULL REFERENCES Usuario(id_usuario),
    modelo            VARCHAR(100),
    sistema_operativo VARCHAR(50),
    token_push        VARCHAR(255),
    fecha_registro    TIMESTAMP     NOT NULL DEFAULT CURRENT_TIMESTAMP,
    activo            BOOLEAN       NOT NULL DEFAULT TRUE
);

CREATE TABLE CuentaBancaria (
    id_cuenta          SERIAL       PRIMARY KEY,
    id_billetera       INT          NOT NULL REFERENCES Billetera(id_billetera),
    id_banco           INT          NOT NULL REFERENCES Banco(id_banco),
    numero_cuenta      VARCHAR(20)  NOT NULL UNIQUE,
    tipo_cuenta        VARCHAR(20)  NOT NULL
                       CHECK (tipo_cuenta IN ('Ahorros', 'Corriente')),
    fecha_vinculacion  DATE         NOT NULL DEFAULT CURRENT_DATE
);

CREATE TABLE Tarjeta (
    id_tarjeta          SERIAL      PRIMARY KEY,
    id_billetera        INT         NOT NULL REFERENCES Billetera(id_billetera),
    id_banco            INT         NOT NULL REFERENCES Banco(id_banco),
    ultimos_4_digitos   CHAR(4)     NOT NULL,
    tipo                VARCHAR(20) NOT NULL CHECK (tipo IN ('Debito', 'Credito')),
    fecha_vencimiento   DATE        NOT NULL
);

CREATE TABLE Contacto (
    id_contacto          SERIAL      PRIMARY KEY,
    id_usuario           INT         NOT NULL REFERENCES Usuario(id_usuario),
    id_usuario_contacto  INT         NOT NULL REFERENCES Usuario(id_usuario),
    alias                VARCHAR(50),
    fecha_agregado       DATE        NOT NULL DEFAULT CURRENT_DATE,
    CONSTRAINT uq_par_contacto     UNIQUE (id_usuario, id_usuario_contacto),
    CONSTRAINT chk_no_autocontacto CHECK  (id_usuario <> id_usuario_contacto)
);

CREATE TABLE Recarga (
    id_recarga    SERIAL        PRIMARY KEY,
    id_billetera  INT           NOT NULL REFERENCES Billetera(id_billetera),
    id_cuenta     INT                    REFERENCES CuentaBancaria(id_cuenta),
    id_tarjeta    INT                    REFERENCES Tarjeta(id_tarjeta),
    monto         NUMERIC(12,2) NOT NULL CHECK (monto > 0),
    fecha         TIMESTAMP     NOT NULL DEFAULT CURRENT_TIMESTAMP,
    estado        VARCHAR(20)   NOT NULL DEFAULT 'Pendiente'
                  CHECK (estado IN ('Exitosa', 'Fallida', 'Pendiente')),
    CONSTRAINT chk_origen_recarga CHECK (
        (id_cuenta IS NOT NULL AND id_tarjeta IS NULL) OR
        (id_cuenta IS NULL     AND id_tarjeta IS NOT NULL)
    )
);

CREATE TABLE Transaccion (
    id_transaccion         SERIAL        PRIMARY KEY,
    id_billetera_emisor    INT           NOT NULL REFERENCES Billetera(id_billetera),
    id_billetera_receptor  INT           NOT NULL REFERENCES Billetera(id_billetera),
    monto                  NUMERIC(12,2) NOT NULL CHECK (monto > 0),
    fecha                  TIMESTAMP     NOT NULL DEFAULT CURRENT_TIMESTAMP,
    mensaje                VARCHAR(255),
    estado                 VARCHAR(20)   NOT NULL DEFAULT 'Pendiente'
                           CHECK (estado IN ('Completada', 'Pendiente', 'Fallida')),
    CONSTRAINT chk_billeteras_distintas CHECK (
        id_billetera_emisor <> id_billetera_receptor
    )
);

CREATE TABLE Notificacion (
    id_notificacion  SERIAL       PRIMARY KEY,
    id_usuario       INT          NOT NULL REFERENCES Usuario(id_usuario),
    id_transaccion   INT                   REFERENCES Transaccion(id_transaccion),
    tipo             VARCHAR(30)  NOT NULL
                     CHECK (tipo IN ('Transaccion', 'Recarga', 'Sistema')),
    mensaje          VARCHAR(255) NOT NULL,
    fecha            TIMESTAMP    NOT NULL DEFAULT CURRENT_TIMESTAMP,
    leida            BOOLEAN      NOT NULL DEFAULT FALSE
);
```

== Población de las Tablas

Se insertaron 15 registros por tabla con datos representativos del dominio peruano.

=== Script de Inserción de Datos

```sql
-- BANCO (15 registros)
INSERT INTO Banco (nombre, codigo_bic, pais) VALUES
('BCP',                'BCPLPEPL', 'Peru'),
('BBVA',               'BSCHPEPL', 'Peru'),
('Interbank',          'BINPPEPL', 'Peru'),
('Scotiabank',         'BSUDPEPL', 'Peru'),
('Banco de la Nacion', 'BNAAPEPL', 'Peru'),
('BanBif',             'BANBPEPL', 'Peru'),
('MiBanco',            'MIBAPEPL', 'Peru'),
('Banco Falabella',    'FALAPEPL', 'Peru'),
('Banco Pichincha',    'PICMPEPL', 'Peru'),
('Caja Arequipa',      NULL,        'Peru'),
('Caja Huancayo',      NULL,        'Peru'),
('Caja Piura',         NULL,        'Peru'),
('Banco GNB',          'GNBSPEPL', 'Peru'),
('Alfin Banco',        'ALFIPLEPL','Peru'),
('Banco Ripley',       'RIPLEPEPL','Peru');

-- USUARIO (15 registros)
INSERT INTO Usuario (dni,nombre,apellido,celular,email,fecha_registro,estado) VALUES
('73829142','Carlos',   'Bonifacio','987654321','carlos.bonifacio@gmail.com', '2023-05-10','Activo'),
('74928374','Eliaz',    'Bobadilla','956789012','eliaz.bobadilla@gmail.com',  '2023-07-22','Activo'),
('75839465','Leonardo', 'Estacio',  '945678901','leonardo.estacio@gmail.com', '2023-09-15','Activo'),
('76948576','Maria',    'Quispe',   '932456789','maria.quispe@gmail.com',     '2024-01-08','Activo'),
('77058687','Jose',     'Mamani',   '967891234','jose.mamani@gmail.com',      '2024-03-12','Activo'),
('78168798','Lucia',    'Huaman',   '978912345','lucia.huaman@gmail.com',     '2024-06-20','Activo'),
('79278809','Ana',      'Flores',   '989123456','ana.flores@gmail.com',       '2024-08-05','Activo'),
('80388910','Diego',    'Rojas',    '991234567','diego.rojas@gmail.com',      '2024-10-18','Activo'),
('81499021','Sofia',    'Gutierrez','912345678','sofia.gutierrez@gmail.com',  '2025-02-25','Activo'),
('82609132','Pedro',    'Vargas',   '923456789','pedro.vargas@gmail.com',     '2025-04-14','Activo'),
('83719243','Carmen',   'Soto',     '934567890','carmen.soto@gmail.com',      '2025-05-02','Activo'),
('84829354','Roberto',  'Luna',     '945678012','roberto.luna@gmail.com',     '2025-05-10','Activo'),
('85939465','Valentina','Cruz',     '956789123','valentina.cruz@gmail.com',   '2025-05-18','Activo'),
('87049576','Miguel',   'Torres',   '967890234','miguel.torres@gmail.com',    '2025-05-25','Activo'),
('88159687','Daniela',  'Paredes',  '978901345','daniela.paredes@gmail.com',  '2025-06-01','Activo');

-- BILLETERA (15 registros)
INSERT INTO Billetera (id_usuario,saldo,moneda,fecha_creacion,estado) VALUES
(1,  320.00,'PEN','2023-05-10','Activa'),
(2,  580.00,'PEN','2023-07-22','Activa'),
(3,  450.00,'PEN','2023-09-15','Activa'),
(4,  220.00,'PEN','2024-01-08','Activa'),
(5,  780.00,'PEN','2024-03-12','Activa'),
(6,  150.00,'PEN','2024-06-20','Activa'),
(7,  620.00,'PEN','2024-08-05','Activa'),
(8, 1100.00,'PEN','2024-10-18','Activa'),
(9,  340.00,'PEN','2025-02-25','Activa'),
(10,  80.00,'PEN','2025-04-14','Activa'),
(11, 270.00,'PEN','2025-05-02','Activa'),
(12, 490.00,'PEN','2025-05-10','Activa'),
(13, 130.00,'PEN','2025-05-18','Activa'),
(14, 860.00,'PEN','2025-05-25','Activa'),
(15, 215.00,'PEN','2025-06-01','Activa');

-- DISPOSITIVO (15 registros)
INSERT INTO Dispositivo
  (id_usuario,modelo,sistema_operativo,token_push,fecha_registro,activo) VALUES
(1, 'Samsung Galaxy A54',  'Android 14','tok_a1b2c3d4','2023-05-10 09:15:00',TRUE),
(2, 'iPhone 14',           'iOS 17',    'tok_b2c3d4e5','2023-07-22 14:30:00',TRUE),
(3, 'Xiaomi Redmi 12',     'Android 13','tok_c3d4e5f6','2023-09-15 11:00:00',TRUE),
(4, 'Samsung Galaxy S23',  'Android 14','tok_d4e5f6a1','2024-01-08 10:20:00',TRUE),
(5, 'iPhone 13',           'iOS 16',    'tok_e5f6a1b2','2024-03-12 08:45:00',TRUE),
(6, 'Motorola G73',        'Android 13','tok_f6a1b2c3','2024-06-20 16:00:00',TRUE),
(7, 'OPPO A78',            'Android 13','tok_a1b2c3d5','2024-08-05 12:10:00',TRUE),
(8, 'iPhone 15 Pro',       'iOS 17',    'tok_b2c3d4e6','2024-10-18 09:30:00',TRUE),
(9, 'Samsung Galaxy A34',  'Android 14','tok_c3d4e5f7','2025-02-25 13:50:00',TRUE),
(10,'Xiaomi POCO X5',      'Android 13','tok_d4e5f6a2','2025-04-14 17:05:00',TRUE),
(11,'Realme C55',          'Android 13','tok_e5f6a1b3','2025-05-02 10:00:00',TRUE),
(12,'Samsung Galaxy A14',  'Android 13','tok_f6a1b2c4','2025-05-10 15:30:00',TRUE),
(13,'iPhone 12',           'iOS 16',    'tok_a1b2c3d6','2025-05-18 09:20:00',TRUE),
(14,'Huawei Y9s',          'EMUI 9',    'tok_b2c3d4e7','2025-05-25 11:45:00',TRUE),
(15,'Motorola Edge 40 Neo','Android 13','tok_c3d4e5f8','2025-06-01 14:00:00',TRUE);

-- CUENTABANCARIA (15 registros)
-- id_banco: BCP=1, BBVA=2, Interbank=3, Scotiabank=4,
--           BancoNacion=5, BanBif=6, MiBanco=7
INSERT INTO CuentaBancaria
  (id_billetera,id_banco,numero_cuenta,tipo_cuenta,fecha_vinculacion) VALUES
(1,  1,'19101234567890','Ahorros',   '2023-05-15'),
(1,  3,'00310045678901','Corriente', '2023-06-01'),
(2,  2,'01112233445566','Ahorros',   '2023-08-10'),
(3,  1,'19198765432101','Ahorros',   '2023-09-20'),
(4,  4,'00908172635445','Corriente', '2024-02-05'),
(5,  1,'19156473829100','Ahorros',   '2024-03-20'),
(7,  3,'00345678123456','Ahorros',   '2024-08-15'),
(8,  1,'19198273645501','Corriente', '2024-11-01'),
(8,  2,'01156473829112','Ahorros',   '2024-12-10'),
(9,  4,'00945678234567','Ahorros',   '2025-03-05'),
(11, 6,'00112233445500','Ahorros',   '2025-05-05'),
(12, 7,'00223344556611','Corriente', '2025-05-12'),
(13, 3,'00334455667722','Ahorros',   '2025-05-20'),
(14, 5,'00445566778833','Ahorros',   '2025-05-27'),
(15, 1,'19156473829200','Corriente', '2025-06-03');

-- TARJETA (15 registros)
INSERT INTO Tarjeta
  (id_billetera,id_banco,ultimos_4_digitos,tipo,fecha_vencimiento) VALUES
(1,  1,'4521','Debito', '2027-08-31'),
(2,  2,'8843','Credito','2026-12-31'),
(3,  1,'1290','Debito', '2028-03-31'),
(3,  3,'5678','Credito','2027-11-30'),
(4,  4,'3412','Debito', '2027-05-31'),
(5,  1,'9087','Debito', '2028-09-30'),
(7,  3,'2244','Credito','2027-02-28'),
(8,  1,'6655','Debito', '2028-07-31'),
(8,  2,'7788','Credito','2027-04-30'),
(9,  4,'3399','Debito', '2028-06-30'),
(11, 6,'4411','Debito', '2028-01-31'),
(12, 7,'5522','Credito','2027-09-30'),
(13, 3,'6633','Debito', '2028-04-30'),
(14, 5,'7744','Credito','2027-12-31'),
(15, 1,'8855','Debito', '2028-11-30');

-- CONTACTO (15 registros)
INSERT INTO Contacto (id_usuario,id_usuario_contacto,alias,fecha_agregado) VALUES
(1,  2, 'Eliaz - U',   '2024-01-15'),
(1,  3, 'Leo',         '2024-02-20'),
(2,  1, 'Carlitos',    '2024-02-22'),
(2,  4, 'Maria Q',     '2024-04-10'),
(3,  1, 'Carlos B',    '2024-08-12'),
(4,  5, 'Jose M',      '2024-05-18'),
(5,  6, 'Lucia H',     '2024-07-25'),
(7,  8, 'Diego R',     '2024-09-30'),
(8,  7, 'Ana F',       '2024-11-05'),
(9, 10, 'Pedro V',     '2025-03-15'),
(4,  3, 'Leo Estacio', '2024-11-05'),
(10, 9, 'Sofia G',     '2025-04-20'),
(11,12, 'Roberto L',   '2025-05-05'),
(12,11, 'Carmen S',    '2025-05-12'),
(13,14, 'Miguel T',    '2025-05-22');

-- RECARGA (15 registros)
INSERT INTO Recarga
  (id_billetera,id_cuenta,id_tarjeta,monto,fecha,estado) VALUES
(1,  1,   NULL,200.00,'2024-12-10 10:00:00','Exitosa'),
(2,  3,   NULL,300.00,'2025-01-05 11:30:00','Exitosa'),
(3,  4,   NULL,500.00,'2025-01-20 09:15:00','Exitosa'),
(4,  NULL,5,   100.00,'2025-02-10 14:00:00','Fallida'),
(5,  6,   NULL,400.00,'2025-02-25 08:45:00','Exitosa'),
(1,  NULL,1,   150.00,'2025-03-15 16:20:00','Exitosa'),
(7,  7,   NULL,250.00,'2025-04-02 10:30:00','Exitosa'),
(8,  8,   NULL,800.00,'2025-04-18 13:10:00','Exitosa'),
(9,  10,  NULL,180.00,'2025-05-08 09:00:00','Exitosa'),
(3,  NULL,4,   220.00,'2025-05-15 15:45:00','Pendiente'),
(11, 11,  NULL,350.00,'2025-05-20 10:00:00','Exitosa'),
(12, 12,  NULL,600.00,'2025-05-22 11:30:00','Exitosa'),
(13, NULL,13,  120.00,'2025-05-25 09:45:00','Exitosa'),
(14, 14,  NULL,900.00,'2025-05-27 14:20:00','Exitosa'),
(15, 15,  NULL,175.00,'2025-06-02 08:30:00','Exitosa');

-- TRANSACCION (15 registros)
INSERT INTO Transaccion
  (id_billetera_emisor,id_billetera_receptor,monto,fecha,mensaje,estado) VALUES
(1,  2,   50.00,'2025-01-15 12:00:00','Almuerzo',       'Completada'),
(3,  4,  120.00,'2025-02-03 10:30:00','Pago alquiler',  'Completada'),
(4,  6,  250.00,'2025-02-18 09:00:00','Servicio',       'Fallida'),
(2,  5,   80.00,'2025-03-22 15:45:00','Cumpleanos',     'Completada'),
(5,  1,  200.00,'2025-04-10 11:20:00','Devolucion',     'Completada'),
(1,  3,   40.00,'2025-04-22 14:00:00','Cafe',           'Pendiente'),
(6,  7,   35.50,'2025-05-01 13:30:00','Cafe',           'Completada'),
(7,  9,  300.00,'2025-05-08 16:00:00','Prestamo',       'Pendiente'),
(8,  3,  500.00,'2025-05-12 09:15:00','Prestamo',       'Completada'),
(4,  9,   75.00,'2025-05-18 12:45:00','Taxi',           'Completada'),
(11,12,  150.00,'2025-05-21 10:00:00','Deuda amigo',    'Completada'),
(12,13,   60.00,'2025-05-23 11:30:00','Recarga celular','Completada'),
(14,11,  320.00,'2025-05-26 14:00:00','Pago servicios', 'Completada'),
(15,14,   45.00,'2025-06-03 09:30:00','Desayuno',       'Completada'),
(13,15,   90.00,'2025-06-05 16:45:00','Comida',         'Pendiente');

-- NOTIFICACION (15 registros)
INSERT INTO Notificacion
  (id_usuario,id_transaccion,tipo,mensaje,fecha,leida) VALUES
(2,  1,   'Transaccion','Recibiste S/ 50.00 de Carlos',          '2025-01-15 12:00:01',TRUE),
(4,  2,   'Transaccion','Enviaste S/ 120.00 a Maria',            '2025-02-03 10:30:01',TRUE),
(5,  4,   'Transaccion','Recibiste S/ 80.00 de Eliaz',           '2025-03-22 15:45:01',FALSE),
(1,  5,   'Transaccion','Recibiste S/ 200.00 de Jose',           '2025-04-10 11:20:01',TRUE),
(7,  7,   'Transaccion','Recibiste S/ 35.50 de Lucia',           '2025-05-01 13:30:01',TRUE),
(3,  9,   'Transaccion','Recibiste S/ 500.00 de Diego',          '2025-05-12 09:15:01',FALSE),
(10, NULL,'Sistema',    'Bienvenido a la billetera digital',      '2025-04-14 08:00:00',TRUE),
(1,  NULL,'Sistema',    'Actualizacion de terminos y condiciones','2025-03-01 08:00:00',TRUE),
(1,  NULL,'Recarga',    'Recarga exitosa por S/ 200.00',          '2024-12-10 10:00:01',TRUE),
(2,  NULL,'Recarga',    'Recarga exitosa por S/ 300.00',          '2025-01-05 11:30:01',TRUE),
(12, 11,  'Transaccion','Recibiste S/ 150.00 de Carmen',          '2025-05-21 10:00:01',FALSE),
(13, 12,  'Transaccion','Recibiste S/ 60.00 de Roberto',          '2025-05-23 11:30:01',FALSE),
(11, 13,  'Transaccion','Recibiste S/ 320.00 de Miguel',          '2025-05-26 14:00:01',FALSE),
(14, 14,  'Transaccion','Recibiste S/ 45.00 de Daniela',          '2025-06-03 09:30:01',FALSE),
(15, NULL,'Sistema',    'Tu cuenta fue verificada exitosamente',   '2025-06-01 14:01:00',TRUE);
```

== Consultas SQL

Se presenta una consulta por cada operador estudiado. Cada sección incluye el enunciado, la instrucción SELECT y el resultado obtenido en PostgreSQL. Las capturas de pantalla de PGAdmin deben adjuntarse en el espacio indicado.

=== Selección

*Enunciado:* Listar todas las transacciones con estado "Completada" y monto mayor a 100 soles.

```sql
SELECT id_transaccion,
       id_billetera_emisor   AS emisor,
       id_billetera_receptor AS receptor,
       monto, estado
FROM Transaccion
WHERE estado = 'Completada'
  AND monto  > 100
ORDER BY id_transaccion;
```

#align(center)[
  #table(
    columns: 5,
    [*id_transaccion*],[*emisor*],[*receptor*],[*monto*],[*estado*],
    [2],[3],[4],[120.00],[Completada],
    [5],[5],[1],[200.00],[Completada],
    [9],[8],[3],[500.00],[Completada],
    [11],[11],[12],[150.00],[Completada],
    [13],[14],[11],[320.00],[Completada],
  )
  _(5 filas)_
]

=== Proyección

*Enunciado:* Obtener el nombre, apellido y celular de todos los usuarios, ordenados alfabéticamente por apellido.

```sql
SELECT nombre, apellido, celular
FROM Usuario
ORDER BY apellido, nombre;
```

#align(center)[
  #table(
    columns: 3,
    [*nombre*],[*apellido*],[*celular*],
    [Eliaz],[Bobadilla],[956789012],
    [Carlos],[Bonifacio],[987654321],
    [Valentina],[Cruz],[956789123],
    [Leonardo],[Estacio],[945678901],
    [Ana],[Flores],[989123456],
    [Sofia],[Gutierrez],[912345678],
    [Lucia],[Huaman],[978912345],
    [Roberto],[Luna],[945678012],
    [Jose],[Mamani],[967891234],
    [Daniela],[Paredes],[978901345],
    [Maria],[Quispe],[932456789],
    [Diego],[Rojas],[991234567],
    [Carmen],[Soto],[934567890],
    [Miguel],[Torres],[967890234],
    [Pedro],[Vargas],[923456789],
  )
  _(15 filas)_
]

=== Unión

*Enunciado:* Obtener los IDs únicos de las billeteras que participaron en alguna transacción, ya sea como emisor o como receptor.

```sql
SELECT id_billetera_emisor   AS id_billetera FROM Transaccion
UNION
SELECT id_billetera_receptor AS id_billetera FROM Transaccion
ORDER BY id_billetera;
```

#align(center)[
  #table(
    columns: 7,
    [*id_billetera*],[*id_billetera*],[*id_billetera*],[*id_billetera*],
    [*id_billetera*],[*id_billetera*],[*id_billetera*],
    [1],[2],[3],[4],[5],[6],[7],
    [8],[9],[11],[12],[13],[14],[15],
  )
  _(14 filas — billetera 10 no tiene transacciones)_
]

=== Intersección

*Enunciado:* Listar los IDs de los usuarios que tienen tanto cuenta bancaria como tarjeta vinculada a su billetera.

```sql
SELECT b.id_usuario
FROM Billetera b
JOIN CuentaBancaria c ON b.id_billetera = c.id_billetera
INTERSECT
SELECT b2.id_usuario
FROM Billetera b2
JOIN Tarjeta t ON b2.id_billetera = t.id_billetera
ORDER BY id_usuario;
```

#align(center)[
  #table(
    columns: 7,
    [*id_usuario*],[*id_usuario*],[*id_usuario*],[*id_usuario*],
    [*id_usuario*],[*id_usuario*],[*id_usuario*],
    [1],[2],[3],[4],[5],[7],[8],
    [9],[11],[12],[13],[14],[15],[],
  )
  _(13 filas — usuarios 6 y 10 sin cuenta ni tarjeta)_
]

=== Diferencia

*Enunciado:* Listar los usuarios que nunca han enviado una transacción (su billetera no figura como emisor).

```sql
SELECT u.id_usuario, u.nombre, u.apellido
FROM Usuario u
JOIN Billetera b ON u.id_usuario = b.id_usuario
EXCEPT
SELECT u2.id_usuario, u2.nombre, u2.apellido
FROM Usuario u2
JOIN Billetera b2  ON u2.id_usuario   = b2.id_usuario
JOIN Transaccion t ON b2.id_billetera = t.id_billetera_emisor
ORDER BY id_usuario;
```

#align(center)[
  #table(
    columns: 3,
    [*id_usuario*],[*nombre*],[*apellido*],
    [9],[Sofia],[Gutierrez],
    [10],[Pedro],[Vargas],
  )
  _(2 filas)_
]

=== Producto Cartesiano

*Enunciado:* Generar todas las combinaciones posibles entre usuarios y bancos del sistema (225 combinaciones). Se muestran las primeras 10.

```sql
SELECT u.nombre AS usuario, bn.nombre AS banco
FROM Usuario u, Banco bn
ORDER BY u.nombre, bn.nombre
LIMIT 10;
```

#align(center)[
  #table(
    columns: 2,
    [*usuario*],[*banco*],
    [Ana],[Alfin Banco],
    [Ana],[BanBif],
    [Ana],[Banco de la Nacion],
    [Ana],[Banco Falabella],
    [Ana],[Banco GNB],
    [Ana],[Banco Pichincha],
    [Ana],[Banco Ripley],
    [Ana],[BBVA],
    [Ana],[BCP],
    [Ana],[Caja Arequipa],
  )
  _(10 de 225 filas — 15 usuarios × 15 bancos)_
]

=== Theta Join

*Enunciado:* Obtener las transacciones donde el monto enviado fue estrictamente menor al saldo de la billetera emisora (condición theta con operador `<`).

```sql
SELECT t.id_transaccion, t.monto, b.saldo, t.estado
FROM Transaccion t
JOIN Billetera b
  ON t.id_billetera_emisor = b.id_billetera
 AND t.monto < b.saldo
ORDER BY t.id_transaccion;
```

#align(center)[
  #table(
    columns: 4,
    [*id_transaccion*],[*monto*],[*saldo*],[*estado*],
    [1],[50.00],[320.00],[Completada],
    [2],[120.00],[450.00],[Completada],
    [4],[80.00],[580.00],[Completada],
    [5],[200.00],[780.00],[Completada],
    [6],[40.00],[320.00],[Pendiente],
    [7],[35.50],[150.00],[Completada],
    [8],[300.00],[620.00],[Pendiente],
    [9],[500.00],[1100.00],[Completada],
    [10],[75.00],[220.00],[Completada],
    [11],[150.00],[270.00],[Completada],
    [12],[60.00],[490.00],[Completada],
    [13],[320.00],[860.00],[Completada],
    [14],[45.00],[215.00],[Completada],
    [15],[90.00],[130.00],[Pendiente],
  )
  _(14 filas — transacción 3 excluida: monto 250 > saldo 220)_
]

=== Left Join

*Enunciado:* Mostrar todos los usuarios con sus recargas; los usuarios sin ninguna recarga aparecen con valores nulos.

```sql
SELECT u.nombre, u.apellido, r.monto, r.estado
FROM Usuario u
LEFT JOIN Billetera b ON u.id_usuario   = b.id_usuario
LEFT JOIN Recarga   r ON b.id_billetera = r.id_billetera
ORDER BY u.id_usuario, r.id_recarga;
```

#align(center)[
  #table(
    columns: 4,
    [*nombre*],[*apellido*],[*monto*],[*estado*],
    [Carlos],[Bonifacio],[200.00],[Exitosa],
    [Carlos],[Bonifacio],[150.00],[Exitosa],
    [Eliaz],[Bobadilla],[300.00],[Exitosa],
    [Leonardo],[Estacio],[500.00],[Exitosa],
    [Leonardo],[Estacio],[220.00],[Pendiente],
    [Maria],[Quispe],[100.00],[Fallida],
    [Jose],[Mamani],[400.00],[Exitosa],
    [Lucia],[Huaman],[NULL],[NULL],
    [Ana],[Flores],[250.00],[Exitosa],
    [Diego],[Rojas],[800.00],[Exitosa],
    [Sofia],[Gutierrez],[180.00],[Exitosa],
    [Pedro],[Vargas],[NULL],[NULL],
    [Carmen],[Soto],[350.00],[Exitosa],
    [Roberto],[Luna],[600.00],[Exitosa],
    [Valentina],[Cruz],[120.00],[Exitosa],
    [Miguel],[Torres],[900.00],[Exitosa],
    [Daniela],[Paredes],[175.00],[Exitosa],
  )
  _(17 filas — Lucia y Pedro sin recargas; Carlos y Leonardo con dos recargas cada uno)_
]

=== Right Join

*Enunciado:* Mostrar todas las notificaciones con el monto de su transacción asociada. Las notificaciones sin transacción (tipo Sistema o Recarga) muestran NULL en el monto.

```sql
SELECT n.id_notificacion, n.tipo, n.mensaje, t.monto
FROM Transaccion t
RIGHT JOIN Notificacion n ON t.id_transaccion = n.id_transaccion
ORDER BY n.id_notificacion;
```

#align(center)[
  #table(
    columns: (auto, auto, 1fr, auto),
    [*id_notif.*],[*tipo*],[*mensaje*],[*monto*],
    [1],[Transaccion],[Recibiste S/ 50.00 de Carlos],[50.00],
    [2],[Transaccion],[Enviaste S/ 120.00 a Maria],[120.00],
    [3],[Transaccion],[Recibiste S/ 80.00 de Eliaz],[80.00],
    [4],[Transaccion],[Recibiste S/ 200.00 de Jose],[200.00],
    [5],[Transaccion],[Recibiste S/ 35.50 de Lucia],[35.50],
    [6],[Transaccion],[Recibiste S/ 500.00 de Diego],[500.00],
    [7],[Sistema],[Bienvenido a la billetera digital],[NULL],
    [8],[Sistema],[Actualizacion de terminos y condiciones],[NULL],
    [9],[Recarga],[Recarga exitosa por S/ 200.00],[NULL],
    [10],[Recarga],[Recarga exitosa por S/ 300.00],[NULL],
    [11],[Transaccion],[Recibiste S/ 150.00 de Carmen],[150.00],
    [12],[Transaccion],[Recibiste S/ 60.00 de Roberto],[60.00],
    [13],[Transaccion],[Recibiste S/ 320.00 de Miguel],[320.00],
    [14],[Transaccion],[Recibiste S/ 45.00 de Daniela],[45.00],
    [15],[Sistema],[Tu cuenta fue verificada exitosamente],[NULL],
  )
  _(15 filas — 5 notificaciones sin transacción asociada muestran NULL en monto)_
]

== Creación de Roles y Usuarios

=== Roles y Permisos Definidos

Se definen tres roles con distintos niveles de acceso:

#align(center)[
  #table(
    columns: (auto, 1fr, auto),
    [*Rol*],[*Descripción*],[*Permisos*],
    [`rol_admin_ewallet`],
    [Administrador: acceso completo a todas las tablas y creación de BD.],
    [ALL + CREATE DB],
    [`rol_operador_ewallet`],
    [Operador: gestiona transacciones, recargas y notificaciones; lectura en el resto.],
    [SELECT (todas), INSERT+UPDATE (3 tablas)],
    [`rol_auditor_ewallet`],
    [Auditor: solo consulta de todas las tablas, sin modificar datos.],
    [SELECT (todas)],
  )
]

#align(center)[
  #table(
    columns: 3,
    [*Rol*],[*Usuario 1*],[*Usuario 2*],
    [`rol_admin_ewallet`],[`admin1`],[`admin2`],
    [`rol_operador_ewallet`],[`operador1`],[`operador2`],
    [`rol_auditor_ewallet`],[`auditor1`],[`auditor2`],
  )
]

=== Script de Creación de Roles y Usuarios

```sql
-- a) Creación de Roles
CREATE ROLE rol_admin_ewallet
    NOSUPERUSER NOCREATEDB NOCREATEROLE INHERIT NOLOGIN;

CREATE ROLE rol_operador_ewallet
    NOSUPERUSER NOCREATEDB NOCREATEROLE INHERIT NOLOGIN;

CREATE ROLE rol_auditor_ewallet
    NOSUPERUSER NOCREATEDB NOCREATEROLE INHERIT NOLOGIN;

-- Usuarios Administrador
CREATE USER admin1    WITH PASSWORD 'Admin1$Ewallet2026' LOGIN;
CREATE USER admin2    WITH PASSWORD 'Admin2$Ewallet2026' LOGIN;
GRANT rol_admin_ewallet TO admin1, admin2;

-- Usuarios Operador
CREATE USER operador1 WITH PASSWORD 'Op1$Ewallet2026'    LOGIN;
CREATE USER operador2 WITH PASSWORD 'Op2$Ewallet2026'    LOGIN;
GRANT rol_operador_ewallet TO operador1, operador2;

-- Usuarios Auditor
CREATE USER auditor1  WITH PASSWORD 'Audit1$Ewallet2026' LOGIN;
CREATE USER auditor2  WITH PASSWORD 'Audit2$Ewallet2026' LOGIN;
GRANT rol_auditor_ewallet TO auditor1, auditor2;
```

=== Script de Otorgamiento de Permisos (GRANT)

```sql
-- b) Otorgar permisos de solo lectura
GRANT SELECT ON ALL TABLES IN SCHEMA public TO rol_auditor_ewallet;

-- Permisos de lectura + inserción + actualización al operador
GRANT SELECT ON ALL TABLES IN SCHEMA public TO rol_operador_ewallet;
GRANT INSERT, UPDATE ON Transaccion  TO rol_operador_ewallet;
GRANT INSERT, UPDATE ON Recarga      TO rol_operador_ewallet;
GRANT INSERT, UPDATE ON Notificacion TO rol_operador_ewallet;

-- Permisos completos al administrador
GRANT ALL PRIVILEGES ON ALL TABLES    IN SCHEMA public TO rol_admin_ewallet;
GRANT ALL PRIVILEGES ON ALL SEQUENCES IN SCHEMA public TO rol_admin_ewallet;
GRANT CREATE ON DATABASE billetera_digital TO rol_admin_ewallet;
```

=== Script de Revocación de Permisos (REVOKE)

```sql
-- c) Revocar permiso de lectura al auditor
REVOKE SELECT ON ALL TABLES IN SCHEMA public FROM rol_auditor_ewallet;

-- Revocar permisos de inserción y actualización al operador
REVOKE INSERT, UPDATE ON Transaccion  FROM rol_operador_ewallet;
REVOKE INSERT, UPDATE ON Recarga      FROM rol_operador_ewallet;
REVOKE INSERT, UPDATE ON Notificacion FROM rol_operador_ewallet;

-- Revocar permiso de eliminación al administrador
REVOKE DELETE ON ALL TABLES IN SCHEMA public FROM rol_admin_ewallet;

-- Revocar permiso de creación de base de datos al administrador
REVOKE CREATE ON DATABASE billetera_digital FROM rol_admin_ewallet;
```

=== Eliminación de Usuarios y Roles

```sql
-- d) Revocar membresías
REVOKE rol_admin_ewallet    FROM admin1,    admin2;
REVOKE rol_operador_ewallet FROM operador1, operador2;
REVOKE rol_auditor_ewallet  FROM auditor1,  auditor2;

-- Eliminar usuarios
DROP USER IF EXISTS admin1;
DROP USER IF EXISTS admin2;
DROP USER IF EXISTS operador1;
DROP USER IF EXISTS operador2;
DROP USER IF EXISTS auditor1;
DROP USER IF EXISTS auditor2;

-- Eliminar roles
DROP ROLE IF EXISTS rol_admin_ewallet;
DROP ROLE IF EXISTS rol_operador_ewallet;
DROP ROLE IF EXISTS rol_auditor_ewallet;
```

= Conclusiones y Recomendaciones

La Fase II permitió implementar íntegramente la base de datos para la billetera digital. Las conclusiones principales son:

- *Normalización efectiva:* El proceso hasta 3FN evidenció que el modelo de la Fase I ya cumplía 1FN y 2FN de forma natural. La mejora central fue extraer la entidad `Banco`, eliminando redundancias y anomalías de actualización que afectarían la integridad a medida que el sistema crezca.

- *Integridad garantizada:* Las restricciones `CHECK`, `UNIQUE`, `NOT NULL` y `FOREIGN KEY` aseguran que el motor rechace datos inválidos antes de persistirlos, reduciendo la deuda técnica en la capa de aplicación.

- *Dataset representativo:* Los 15 registros por tabla, con datos fidedignos al contexto peruano (bancos reales, nombres plausibles), permiten validar los nueve operadores SQL con resultados no vacíos y variados.

- *Gestión de acceso por roles:* La separación en tres roles (administrador, operador, auditor) implementa el principio de mínimo privilegio, reduciendo el riesgo de modificaciones accidentales o maliciosas.

*Recomendaciones:*

- Implementar *triggers* que actualicen el saldo de la billetera automáticamente tras cada transacción o recarga exitosa.
- Crear *índices* en columnas de búsqueda frecuente: `Transaccion.estado`, `Notificacion.id_usuario`, `Usuario.celular`.
- Considerar *particionamiento* de `Transaccion` por fecha para gestionar el crecimiento histórico.

= Referencias Bibliográficas

+ Ramakrishnan, R., & Gehrke, J. (2003). *Database Management Systems* (3rd ed.). McGraw-Hill.

+ Elmasri, R., & Navathe, S. B. (2016). *Fundamentals of Database Systems* (7th ed.). Pearson.

+ Date, C. J. (2004). *An Introduction to Database Systems* (8th ed.). Addison-Wesley.

+ PostgreSQL Global Development Group. (2024). *PostgreSQL 17 Documentation*. Recuperado de #link("https://www.postgresql.org/docs/17/")

+ Coronel, C., Morris, S., & Rob, P. (2019). *Database Systems: Design, Implementation, and Management* (13th ed.). Cengage Learning.

= Anexos

== Anexo A: Diagrama Entidad-Relación (Fase I)

#align(center)[
  #image("diagrama_1.svg", width: 90%)
  *Figura A.1.* Diagrama Entidad-Relación original de la Fase I.
]

== Anexo B: Scripts SQL

Los scripts `schema.sql` e `inserts.sql` se adjuntan como archivos independientes al presente informe, de acuerdo con los requisitos de entrega de la Fase II.
