-- ================================================
-- BASE DE DATOS: billetera_digital
-- Fase III – Proyecto Formativo de Base de Datos
-- Universidad Nacional de Ingeniería
-- ================================================
-- PRERREQUISITO: BD billetera_digital creada con el
-- DDL e INSERTs de la Fase II ya ejecutados.

\c billetera_digital

-- ============================================================
-- I. DOMINIOS
-- ============================================================

-- dom_email: dirección de correo electrónico válida
CREATE DOMAIN dom_email
    AS VARCHAR(100)
    CHECK (VALUE ~* '^[^@\s]+@[^@\s]+\.[^@\s]{2,}$');

-- dom_monto_pos: valor monetario estrictamente positivo
CREATE DOMAIN dom_monto_pos
    AS NUMERIC(12,2)
    CHECK (VALUE > 0);

-- dom_dni_pe: DNI peruano de exactamente 8 dígitos numéricos
CREATE DOMAIN dom_dni_pe
    AS CHAR(8)
    CHECK (VALUE ~ '^\d{8}$');

-- dom_celular_pe: celular peruano de exactamente 9 dígitos
CREATE DOMAIN dom_celular_pe
    AS CHAR(9)
    CHECK (VALUE ~ '^\d{9}$');

-- dom_moneda_iso: código ISO 4217 de tres letras mayúsculas
CREATE DOMAIN dom_moneda_iso
    AS CHAR(3)
    CHECK (VALUE ~ '^[A-Z]{3}$');

-- dom_estado_gen: campo de estado no nulo de hasta 20 caracteres
CREATE DOMAIN dom_estado_gen
    AS VARCHAR(20)
    NOT NULL;

-- Ejemplo de tabla que utilizaría los dominios definidos:
--   CREATE TABLE EjemploDominios (
--       email   dom_email,
--       monto   dom_monto_pos,
--       dni     dom_dni_pe,
--       celular dom_celular_pe,
--       moneda  dom_moneda_iso,
--       estado  dom_estado_gen
--   );

-- Demo: inserción aceptada sobre dom_email
SELECT CAST('usuario@ejemplo.pe' AS dom_email)   AS email_valido;
-- Demo: inserción rechazada sobre dom_email (sin @)
-- SELECT CAST('usuarioejemplo.pe'  AS dom_email);
-- ERROR: value for domain dom_email violates check constraint "dom_email_check"


-- ============================================================
-- II. DEMOS DE RESTRICCIONES
--
-- Para cada restricción:
--   - Ejecutar el INSERT "ACEPTADO" y hacer captura.
--   - Ejecutar el INSERT "RECHAZADO" (comentado abajo) y
--     hacer captura del mensaje de error en pgAdmin.
--   Los RECHAZADOs están en bloques DO para que el script
--   pueda ejecutarse de inicio a fin sin interrupciones.
-- ============================================================

-- -------------------------------------------------------
-- II.a NOT NULL – 10 restricciones
-- -------------------------------------------------------

-- 1. Usuario.nombre NOT NULL
-- ACEPTADO
INSERT INTO Usuario(dni,nombre,apellido,celular,email)
    VALUES ('91000001','Ana','Demo','910000001','ana.demo@ewallet.pe');
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Usuario(dni,nombre,apellido,celular,email)
        VALUES ('91000002',NULL,'Demo','910000002','ana2.demo@ewallet.pe');
EXCEPTION WHEN not_null_violation THEN
    RAISE NOTICE '[RECHAZADO] NOT NULL Usuario.nombre: %', SQLERRM;
END $$;

-- 2. Usuario.apellido NOT NULL
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Usuario(dni,nombre,apellido,celular,email)
        VALUES ('91000003','Luis',NULL,'910000003','luis.demo@ewallet.pe');
EXCEPTION WHEN not_null_violation THEN
    RAISE NOTICE '[RECHAZADO] NOT NULL Usuario.apellido: %', SQLERRM;
END $$;

-- 3. Usuario.dni NOT NULL
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Usuario(dni,nombre,apellido,celular,email)
        VALUES (NULL,'Pedro','Demo','910000004','pedro.demo@ewallet.pe');
EXCEPTION WHEN not_null_violation THEN
    RAISE NOTICE '[RECHAZADO] NOT NULL Usuario.dni: %', SQLERRM;
END $$;

-- 4. Usuario.celular NOT NULL
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Usuario(dni,nombre,apellido,celular,email)
        VALUES ('91000005','Sara','Demo',NULL,'sara.demo@ewallet.pe');
EXCEPTION WHEN not_null_violation THEN
    RAISE NOTICE '[RECHAZADO] NOT NULL Usuario.celular: %', SQLERRM;
END $$;

-- 5. Usuario.email NOT NULL
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Usuario(dni,nombre,apellido,celular,email)
        VALUES ('91000006','Juan','Demo','910000006',NULL);
EXCEPTION WHEN not_null_violation THEN
    RAISE NOTICE '[RECHAZADO] NOT NULL Usuario.email: %', SQLERRM;
END $$;

-- 6. Billetera.saldo NOT NULL
-- ACEPTADO (crear billetera para el usuario de demo)
INSERT INTO Billetera(id_usuario,saldo,moneda,fecha_creacion,estado)
    SELECT id_usuario,0.00,'PEN',CURRENT_DATE,'Activa'
    FROM Usuario WHERE dni='91000001';
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Billetera(id_usuario,saldo,moneda,fecha_creacion,estado)
        VALUES (1,NULL,'PEN',CURRENT_DATE,'Activa');
EXCEPTION WHEN not_null_violation THEN
    RAISE NOTICE '[RECHAZADO] NOT NULL Billetera.saldo: %', SQLERRM;
END $$;

-- 7. Transaccion.monto NOT NULL
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Transaccion(id_billetera_emisor,id_billetera_receptor,monto,estado)
        VALUES (1,2,NULL,'Pendiente');
EXCEPTION WHEN not_null_violation THEN
    RAISE NOTICE '[RECHAZADO] NOT NULL Transaccion.monto: %', SQLERRM;
END $$;

-- 8. Notificacion.mensaje NOT NULL
-- ACEPTADO
INSERT INTO Notificacion(id_usuario,tipo,mensaje)
    VALUES (1,'Sistema','Bienvenido al sistema de prueba.');
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Notificacion(id_usuario,tipo,mensaje)
        VALUES (1,'Sistema',NULL);
EXCEPTION WHEN not_null_violation THEN
    RAISE NOTICE '[RECHAZADO] NOT NULL Notificacion.mensaje: %', SQLERRM;
END $$;

-- 9. Banco.nombre NOT NULL
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Banco(nombre,pais) VALUES (NULL,'Peru');
EXCEPTION WHEN not_null_violation THEN
    RAISE NOTICE '[RECHAZADO] NOT NULL Banco.nombre: %', SQLERRM;
END $$;

-- 10. Recarga.monto NOT NULL
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Recarga(id_billetera,id_cuenta,monto,estado)
        VALUES (1,1,NULL,'Pendiente');
EXCEPTION WHEN not_null_violation THEN
    RAISE NOTICE '[RECHAZADO] NOT NULL Recarga.monto: %', SQLERRM;
END $$;


-- -------------------------------------------------------
-- II.b PRIMARY KEY y UNIQUE – 4 restricciones
-- -------------------------------------------------------

-- 1. Usuario.dni UNIQUE – DNI duplicado
-- ACEPTADO
INSERT INTO Usuario(dni,nombre,apellido,celular,email)
    VALUES ('92000001','Marco','Rios','920000001','marco.rios@ewallet.pe');
-- RECHAZADO (mismo DNI)
DO $$ BEGIN
    INSERT INTO Usuario(dni,nombre,apellido,celular,email)
        VALUES ('92000001','Pedro','Rios','920000002','pedro.rios@ewallet.pe');
EXCEPTION WHEN unique_violation THEN
    RAISE NOTICE '[RECHAZADO] UNIQUE Usuario.dni: %', SQLERRM;
END $$;

-- 2. Usuario.celular UNIQUE – celular duplicado
-- RECHAZADO (celular '920000001' ya existe)
DO $$ BEGIN
    INSERT INTO Usuario(dni,nombre,apellido,celular,email)
        VALUES ('92000003','Rosa','Rios','920000001','rosa.rios@ewallet.pe');
EXCEPTION WHEN unique_violation THEN
    RAISE NOTICE '[RECHAZADO] UNIQUE Usuario.celular: %', SQLERRM;
END $$;

-- 3. Banco.nombre UNIQUE – nombre de banco duplicado
-- RECHAZADO (BCP ya existe)
DO $$ BEGIN
    INSERT INTO Banco(nombre,pais) VALUES ('BCP','Peru');
EXCEPTION WHEN unique_violation THEN
    RAISE NOTICE '[RECHAZADO] UNIQUE Banco.nombre: %', SQLERRM;
END $$;

-- 4. CuentaBancaria.numero_cuenta UNIQUE – número de cuenta duplicado
-- RECHAZADO (número '19101234567890' ya existe)
DO $$ BEGIN
    INSERT INTO CuentaBancaria(id_billetera,id_banco,numero_cuenta,tipo_cuenta)
        VALUES (2,2,'19101234567890','Ahorros');
EXCEPTION WHEN unique_violation THEN
    RAISE NOTICE '[RECHAZADO] UNIQUE CuentaBancaria.numero_cuenta: %', SQLERRM;
END $$;


-- -------------------------------------------------------
-- II.c CHECK – 8 restricciones
-- -------------------------------------------------------

-- 1. Usuario.estado CHECK IN ('Activo','Bloqueado','Inactivo')
-- ACEPTADO
INSERT INTO Usuario(dni,nombre,apellido,celular,email,estado)
    VALUES ('93000001','Test','Estado','930000001','test.estado@ewallet.pe','Bloqueado');
-- RECHAZADO (valor fuera del dominio)
DO $$ BEGIN
    INSERT INTO Usuario(dni,nombre,apellido,celular,email,estado)
        VALUES ('93000002','Test','Estado2','930000002','test2.estado@ewallet.pe','Suspendido');
EXCEPTION WHEN check_violation THEN
    RAISE NOTICE '[RECHAZADO] CHECK Usuario.estado: %', SQLERRM;
END $$;

-- 2. Billetera.estado CHECK IN ('Activa','Bloqueada','Cerrada')
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Billetera(id_usuario,saldo,estado)
        VALUES (1,0.00,'Eliminada');
EXCEPTION WHEN check_violation THEN
    RAISE NOTICE '[RECHAZADO] CHECK Billetera.estado: %', SQLERRM;
END $$;

-- 3. Billetera.saldo CHECK >= 0
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Billetera(id_usuario,saldo)
        VALUES (1,-50.00);
EXCEPTION WHEN check_violation THEN
    RAISE NOTICE '[RECHAZADO] CHECK Billetera.saldo >= 0: %', SQLERRM;
END $$;

-- 4. CuentaBancaria.tipo_cuenta CHECK IN ('Ahorros','Corriente')
-- ACEPTADO
INSERT INTO CuentaBancaria(id_billetera,id_banco,numero_cuenta,tipo_cuenta)
    VALUES (1,1,'99901234567890','Ahorros');
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO CuentaBancaria(id_billetera,id_banco,numero_cuenta,tipo_cuenta)
        VALUES (1,1,'99999999999999','Plazo Fijo');
EXCEPTION WHEN check_violation THEN
    RAISE NOTICE '[RECHAZADO] CHECK CuentaBancaria.tipo_cuenta: %', SQLERRM;
END $$;

-- 5. Tarjeta.tipo CHECK IN ('Debito','Credito')
-- ACEPTADO
INSERT INTO Tarjeta(id_billetera,id_banco,ultimos_4_digitos,tipo,fecha_vencimiento)
    VALUES (1,1,'0001','Debito','2029-01-31');
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Tarjeta(id_billetera,id_banco,ultimos_4_digitos,tipo,fecha_vencimiento)
        VALUES (1,1,'0002','Prepago','2029-01-31');
EXCEPTION WHEN check_violation THEN
    RAISE NOTICE '[RECHAZADO] CHECK Tarjeta.tipo: %', SQLERRM;
END $$;

-- 6. Recarga.monto CHECK > 0
-- ACEPTADO
INSERT INTO Recarga(id_billetera,id_cuenta,id_tarjeta,monto,estado)
    VALUES (1,1,NULL,50.00,'Pendiente');
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Recarga(id_billetera,id_cuenta,id_tarjeta,monto,estado)
        VALUES (1,1,NULL,-50.00,'Pendiente');
EXCEPTION WHEN check_violation THEN
    RAISE NOTICE '[RECHAZADO] CHECK Recarga.monto > 0: %', SQLERRM;
END $$;

-- 7. Transaccion.monto CHECK > 0
-- ACEPTADO (transacción de prueba entre billeteras 1 y 2)
INSERT INTO Transaccion(id_billetera_emisor,id_billetera_receptor,monto,mensaje,estado)
    VALUES (1,2,10.00,'Prueba check','Pendiente');
-- RECHAZADO (monto = 0)
DO $$ BEGIN
    INSERT INTO Transaccion(id_billetera_emisor,id_billetera_receptor,monto,estado)
        VALUES (1,2,0.00,'Pendiente');
EXCEPTION WHEN check_violation THEN
    RAISE NOTICE '[RECHAZADO] CHECK Transaccion.monto > 0: %', SQLERRM;
END $$;

-- 8. Notificacion.tipo CHECK IN ('Transaccion','Recarga','Sistema')
-- RECHAZADO
DO $$ BEGIN
    INSERT INTO Notificacion(id_usuario,tipo,mensaje)
        VALUES (1,'Alerta','Mensaje no válido');
EXCEPTION WHEN check_violation THEN
    RAISE NOTICE '[RECHAZADO] CHECK Notificacion.tipo: %', SQLERRM;
END $$;


-- -------------------------------------------------------
-- II.d FK INTEGRIDAD – inserción, exclusión, actualización
-- -------------------------------------------------------

-- FK 1: Billetera.id_usuario → Usuario

-- INCLUSIÓN: billetera con usuario inexistente
DO $$ BEGIN
    INSERT INTO Billetera(id_usuario,saldo) VALUES (9999,0.00);
EXCEPTION WHEN foreign_key_violation THEN
    RAISE NOTICE '[RECHAZADO] FK Billetera→Usuario (INSERT): %', SQLERRM;
END $$;

-- EXCLUSIÓN: eliminar usuario 1 (tiene billetera referenciando)
DO $$ BEGIN
    DELETE FROM Usuario WHERE id_usuario = 1;
EXCEPTION WHEN foreign_key_violation THEN
    RAISE NOTICE '[RECHAZADO] FK Billetera→Usuario (DELETE): %', SQLERRM;
END $$;

-- ACTUALIZACIÓN: cambiar id_usuario en Billetera a uno inexistente
DO $$ BEGIN
    UPDATE Billetera SET id_usuario = 9999 WHERE id_billetera = 1;
EXCEPTION WHEN foreign_key_violation THEN
    RAISE NOTICE '[RECHAZADO] FK Billetera→Usuario (UPDATE): %', SQLERRM;
END $$;

-- FK 2: CuentaBancaria.id_billetera → Billetera

-- INCLUSIÓN
DO $$ BEGIN
    INSERT INTO CuentaBancaria(id_billetera,id_banco,numero_cuenta,tipo_cuenta)
        VALUES (9999,1,'88888888888888','Ahorros');
EXCEPTION WHEN foreign_key_violation THEN
    RAISE NOTICE '[RECHAZADO] FK CuentaBancaria→Billetera (INSERT): %', SQLERRM;
END $$;

-- EXCLUSIÓN: eliminar billetera 1 (referenciada por cuentas)
DO $$ BEGIN
    DELETE FROM Billetera WHERE id_billetera = 1;
EXCEPTION WHEN foreign_key_violation THEN
    RAISE NOTICE '[RECHAZADO] FK CuentaBancaria→Billetera (DELETE): %', SQLERRM;
END $$;

-- ACTUALIZACIÓN
DO $$ BEGIN
    UPDATE CuentaBancaria SET id_billetera = 9999 WHERE id_cuenta = 1;
EXCEPTION WHEN foreign_key_violation THEN
    RAISE NOTICE '[RECHAZADO] FK CuentaBancaria→Billetera (UPDATE): %', SQLERRM;
END $$;

-- FK 3: Transaccion.id_billetera_emisor → Billetera

-- INCLUSIÓN
DO $$ BEGIN
    INSERT INTO Transaccion(id_billetera_emisor,id_billetera_receptor,monto,estado)
        VALUES (9999,2,100.00,'Pendiente');
EXCEPTION WHEN foreign_key_violation THEN
    RAISE NOTICE '[RECHAZADO] FK Transaccion→Billetera_emisor (INSERT): %', SQLERRM;
END $$;

-- EXCLUSIÓN: billetera 2 es emisora en transacciones
DO $$ BEGIN
    DELETE FROM Billetera WHERE id_billetera = 2;
EXCEPTION WHEN foreign_key_violation THEN
    RAISE NOTICE '[RECHAZADO] FK Transaccion→Billetera_emisor (DELETE): %', SQLERRM;
END $$;

-- ACTUALIZACIÓN
DO $$ BEGIN
    UPDATE Transaccion SET id_billetera_emisor = 9999 WHERE id_transaccion = 1;
EXCEPTION WHEN foreign_key_violation THEN
    RAISE NOTICE '[RECHAZADO] FK Transaccion→Billetera_emisor (UPDATE): %', SQLERRM;
END $$;

-- FK 4: Notificacion.id_usuario → Usuario

-- INCLUSIÓN
DO $$ BEGIN
    INSERT INTO Notificacion(id_usuario,tipo,mensaje)
        VALUES (9999,'Sistema','Prueba FK');
EXCEPTION WHEN foreign_key_violation THEN
    RAISE NOTICE '[RECHAZADO] FK Notificacion→Usuario (INSERT): %', SQLERRM;
END $$;

-- EXCLUSIÓN: usuario 2 tiene notificaciones
DO $$ BEGIN
    DELETE FROM Usuario WHERE id_usuario = 2;
EXCEPTION WHEN foreign_key_violation THEN
    RAISE NOTICE '[RECHAZADO] FK Notificacion→Usuario (DELETE): %', SQLERRM;
END $$;

-- ACTUALIZACIÓN
DO $$ BEGIN
    UPDATE Notificacion SET id_usuario = 9999 WHERE id_notificacion = 1;
EXCEPTION WHEN foreign_key_violation THEN
    RAISE NOTICE '[RECHAZADO] FK Notificacion→Usuario (UPDATE): %', SQLERRM;
END $$;


-- -------------------------------------------------------
-- II.e RESTRICCIONES A NIVEL DE TUPLA – 2
-- -------------------------------------------------------

-- 1. Contacto.chk_no_autocontacto (id_usuario <> id_usuario_contacto)
-- ACEPTADO
INSERT INTO Contacto(id_usuario,id_usuario_contacto,alias)
    VALUES (5,9,'Sofia G - prueba');
-- RECHAZADO: usuario se agrega a sí mismo
DO $$ BEGIN
    INSERT INTO Contacto(id_usuario,id_usuario_contacto,alias)
        VALUES (5,5,'Yo mismo');
EXCEPTION WHEN check_violation THEN
    RAISE NOTICE '[RECHAZADO] TUPLE CHECK chk_no_autocontacto: %', SQLERRM;
END $$;

-- 2. Recarga.chk_origen_recarga (exactamente un origen: cuenta O tarjeta)
-- ACEPTADO (solo cuenta bancaria)
INSERT INTO Recarga(id_billetera,id_cuenta,id_tarjeta,monto,estado)
    VALUES (2,3,NULL,100.00,'Pendiente');
-- RECHAZADO: ambos nulos (ningún origen)
DO $$ BEGIN
    INSERT INTO Recarga(id_billetera,id_cuenta,id_tarjeta,monto,estado)
        VALUES (2,NULL,NULL,100.00,'Pendiente');
EXCEPTION WHEN check_violation THEN
    RAISE NOTICE '[RECHAZADO] TUPLE CHECK chk_origen_recarga (ambos NULL): %', SQLERRM;
END $$;
-- RECHAZADO: ambos presentes
DO $$ BEGIN
    INSERT INTO Recarga(id_billetera,id_cuenta,id_tarjeta,monto,estado)
        VALUES (2,3,2,100.00,'Pendiente');
EXCEPTION WHEN check_violation THEN
    RAISE NOTICE '[RECHAZADO] TUPLE CHECK chk_origen_recarga (ambos NOT NULL): %', SQLERRM;
END $$;


-- ============================================================
-- III. ÍNDICES
-- ============================================================

-- 1. B-tree en Usuario.celular
--    Razón: el login y la búsqueda de destinatario se hacen por número
--    de celular; sin índice, cada búsqueda hace un sequential scan de
--    la tabla Usuario.
CREATE INDEX idx_usuario_celular
    ON Usuario(celular);

-- 2. B-tree en Transaccion.estado
--    Razón: la mayoría de consultas operacionales filtran por
--    estado = 'Completada'. Sin índice, el motor escanea toda la tabla.
CREATE INDEX idx_transaccion_estado
    ON Transaccion(estado);

-- 3. Índice compuesto B-tree en Notificacion(id_usuario, leida)
--    Razón: la bandeja de entrada de un usuario filtra por id_usuario
--    Y leida = FALSE; el índice compuesto cubre ambas columnas de
--    la condición sin acceder a la tabla.
CREATE INDEX idx_notif_usuario_leida
    ON Notificacion(id_usuario, leida);

-- 4. B-tree descendente en Transaccion.fecha
--    Razón: el historial de movimientos se muestra en orden cronológico
--    inverso (más reciente primero). El índice DESC evita un sort en
--    memoria para la cláusula ORDER BY fecha DESC.
CREATE INDEX idx_transaccion_fecha_desc
    ON Transaccion(fecha DESC);

-- 5. Índice parcial en Billetera (solo billeteras activas)
--    Razón: prácticamente todas las consultas de saldo y transacciones
--    operan sobre billeteras con estado = 'Activa'. El índice parcial
--    es más pequeño y por tanto más rápido que uno total.
CREATE INDEX idx_billetera_activa
    ON Billetera(id_billetera)
    WHERE estado = 'Activa';


-- ============================================================
-- IV. CONSULTAS
-- ============================================================

-- -------------------------------------------------------
-- IV.a Funciones de agregación
-- -------------------------------------------------------

-- Q1: SUM y COUNT – total enviado y número de envíos por usuario
SELECT b.id_billetera,
       u.nombre || ' ' || u.apellido AS usuario,
       COUNT(*)                       AS num_envios,
       SUM(t.monto)                   AS total_enviado
FROM Transaccion t
JOIN Billetera b ON t.id_billetera_emisor = b.id_billetera
JOIN Usuario   u ON b.id_usuario          = u.id_usuario
GROUP BY b.id_billetera, u.nombre, u.apellido
ORDER BY total_enviado DESC;

-- Q2: AVG, MIN, MAX, SUM, COUNT – estadísticas de recargas exitosas
SELECT COUNT(*)               AS total_recargas,
       ROUND(AVG(monto), 2)   AS promedio_monto,
       MIN(monto)             AS monto_minimo,
       MAX(monto)             AS monto_maximo,
       SUM(monto)             AS monto_total
FROM Recarga
WHERE estado = 'Exitosa';


-- -------------------------------------------------------
-- IV.b WHERE, GROUP BY, HAVING, ORDER BY
-- -------------------------------------------------------

-- Q3: billeteras con más de un envío total, ordenadas por monto acumulado
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

-- Q4: usuarios con dos o más notificaciones recibidas
SELECT u.nombre || ' ' || u.apellido AS usuario,
       COUNT(*)                       AS total_notificaciones
FROM Notificacion n
JOIN Usuario u ON n.id_usuario = u.id_usuario
GROUP BY u.id_usuario, u.nombre, u.apellido
HAVING COUNT(*) >= 2
ORDER BY total_notificaciones DESC;


-- -------------------------------------------------------
-- IV.c Subconsultas
-- -------------------------------------------------------

-- Q5 (IN): usuarios que han enviado al menos una transacción
SELECT nombre, apellido
FROM Usuario
WHERE id_usuario IN (
    SELECT b.id_usuario
    FROM Transaccion t
    JOIN Billetera b ON t.id_billetera_emisor = b.id_billetera
)
ORDER BY apellido, nombre;

-- Q6 (EXISTS): usuarios con al menos una cuenta bancaria vinculada
SELECT u.nombre, u.apellido, b.saldo
FROM Usuario u
JOIN Billetera b ON u.id_usuario = b.id_usuario
WHERE EXISTS (
    SELECT 1
    FROM CuentaBancaria c
    WHERE c.id_billetera = b.id_billetera
)
ORDER BY u.apellido;

-- Q7 (ALL): transacciones cuyo monto supera TODAS las recargas de la billetera 1
SELECT id_transaccion, monto, estado
FROM Transaccion
WHERE monto > ALL (
    SELECT monto
    FROM Recarga
    WHERE id_billetera = 1
)
ORDER BY monto DESC;

-- Q8 (ANY): usuarios cuyo saldo es menor que ALGUNA transacción completada
SELECT u.nombre, u.apellido, b.saldo
FROM Usuario u
JOIN Billetera b ON u.id_usuario = b.id_usuario
WHERE b.saldo < ANY (
    SELECT monto
    FROM Transaccion
    WHERE estado = 'Completada'
)
ORDER BY b.saldo;


-- ============================================================
-- V. VISTAS
-- ============================================================

-- -------------------------------------------------------
-- V.a Operaciones de conjuntos
-- -------------------------------------------------------

-- V1 (UNION ALL): todos los movimientos financieros (transacciones + recargas)
CREATE VIEW v_movimientos AS
    SELECT 'Transaccion'::TEXT AS tipo, monto, fecha, estado
      FROM Transaccion
  UNION ALL
    SELECT 'Recarga', monto, fecha, estado
      FROM Recarga;

-- V2 (EXCEPT): usuarios que enviaron transacciones pero nunca recargaron
CREATE VIEW v_emisores_sin_recarga AS
    SELECT b.id_usuario
      FROM Billetera b
      JOIN Transaccion t ON b.id_billetera = t.id_billetera_emisor
  EXCEPT
    SELECT b2.id_usuario
      FROM Billetera b2
      JOIN Recarga r ON b2.id_billetera = r.id_billetera;

-- -------------------------------------------------------
-- V.b JOINs con WHERE
-- -------------------------------------------------------

-- V3 (INNER JOIN): detalle de transacciones completadas con nombres de partes
CREATE VIEW v_transacciones_detalle AS
SELECT t.id_transaccion,
       ue.nombre || ' ' || ue.apellido AS emisor,
       ur.nombre || ' ' || ur.apellido AS receptor,
       t.monto,
       t.fecha,
       t.estado
FROM Transaccion t
JOIN Billetera be ON t.id_billetera_emisor   = be.id_billetera
JOIN Billetera br ON t.id_billetera_receptor = br.id_billetera
JOIN Usuario   ue ON be.id_usuario = ue.id_usuario
JOIN Usuario   ur ON br.id_usuario = ur.id_usuario
WHERE t.estado = 'Completada';

-- V4 (LEFT JOIN): todos los usuarios activos con su resumen de recargas
CREATE VIEW v_usuarios_recargas AS
SELECT u.id_usuario,
       u.nombre || ' ' || u.apellido       AS usuario,
       COUNT(r.id_recarga)                  AS total_recargas,
       COALESCE(SUM(r.monto), 0::NUMERIC)  AS monto_total
FROM Usuario u
LEFT JOIN Billetera b ON u.id_usuario   = b.id_usuario
LEFT JOIN Recarga   r ON b.id_billetera = r.id_billetera
WHERE u.estado = 'Activo'
GROUP BY u.id_usuario, u.nombre, u.apellido;

-- V5 (RIGHT JOIN): todos los bancos con la cantidad de cuentas vinculadas
CREATE VIEW v_bancos_cuentas AS
SELECT bn.nombre                AS banco,
       COUNT(c.id_cuenta)       AS num_cuentas
FROM CuentaBancaria c
RIGHT JOIN Banco bn ON c.id_banco = bn.id_banco
WHERE bn.pais = 'Peru'
GROUP BY bn.nombre
ORDER BY num_cuentas DESC;

-- -------------------------------------------------------
-- V.c Vistas cuyo origen es otra vista
-- -------------------------------------------------------

-- V6 (sobre v_movimientos): resumen mensual por tipo de movimiento
CREATE VIEW v_resumen_mensual AS
SELECT tipo,
       DATE_TRUNC('month', fecha)::DATE AS mes,
       COUNT(*)                          AS operaciones,
       SUM(monto)                        AS volumen
FROM v_movimientos
GROUP BY tipo, DATE_TRUNC('month', fecha)
ORDER BY mes, tipo;

-- V7 (sobre v_transacciones_detalle): transacciones de alto valor (>= S/ 200)
CREATE VIEW v_transacciones_grandes AS
SELECT *
FROM v_transacciones_detalle
WHERE monto >= 200
ORDER BY monto DESC;

-- Consultas de prueba sobre las vistas
SELECT * FROM v_movimientos         ORDER BY fecha DESC LIMIT 10;
SELECT * FROM v_emisores_sin_recarga;
SELECT * FROM v_transacciones_detalle;
SELECT * FROM v_usuarios_recargas   ORDER BY monto_total DESC;
SELECT * FROM v_bancos_cuentas;
SELECT * FROM v_resumen_mensual;
SELECT * FROM v_transacciones_grandes;


-- ============================================================
-- VI. FUNCIONES
-- ============================================================

-- -------------------------------------------------------
-- VI.a Funciones con JOIN
-- -------------------------------------------------------

-- Natural Join: Usuario y Billetera (comparten id_usuario)
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

-- Theta Join: transacciones donde monto enviado < saldo actual del emisor
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

-- Left Join: todos los usuarios con total enviado (0 si nunca enviaron)
CREATE OR REPLACE FUNCTION fn_left_usuarios_total_enviado()
RETURNS TABLE(
    usuario       TEXT,
    total_enviado NUMERIC
) AS $$
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

-- Right Join: todos los bancos con número de cuentas vinculadas
CREATE OR REPLACE FUNCTION fn_right_bancos_num_cuentas()
RETURNS TABLE(
    banco      VARCHAR,
    num_cuentas BIGINT
) AS $$
BEGIN
    RETURN QUERY
    SELECT bn.nombre, COUNT(c.id_cuenta)
    FROM CuentaBancaria c
    RIGHT JOIN Banco bn ON c.id_banco = bn.id_banco
    GROUP BY bn.nombre
    ORDER BY COUNT(c.id_cuenta) DESC;
END;
$$ LANGUAGE plpgsql;

-- Llamadas de prueba
SELECT * FROM fn_natural_join_usuarios_billeteras();
SELECT * FROM fn_theta_transacciones_bajo_saldo();
SELECT * FROM fn_left_usuarios_total_enviado();
SELECT * FROM fn_right_bancos_num_cuentas();


-- -------------------------------------------------------
-- VI.b Inserción con parámetros
-- -------------------------------------------------------

CREATE OR REPLACE FUNCTION fn_registrar_usuario(
    p_dni      TEXT,
    p_nombre   TEXT,
    p_apellido TEXT,
    p_celular  TEXT,
    p_email    TEXT
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

-- Prueba: registrar usuario con billetera inicial
SELECT fn_registrar_usuario(
    '95000001', 'Roberto', 'Sanchez', '950000001', 'roberto.sanchez@ewallet.pe'
) AS nuevo_id_usuario;


-- -------------------------------------------------------
-- VI.c Actualización con condición
-- -------------------------------------------------------

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
        RAISE EXCEPTION 'Billetera % no existe o no está activa', p_id_billetera;
    END IF;

    RETURN 'Saldo de billetera ' || p_id_billetera || ' actualizado a S/ ' || p_nuevo_saldo;
END;
$$ LANGUAGE plpgsql;

-- Prueba aceptada
SELECT fn_actualizar_saldo(1, 500.00);
-- Prueba rechazada (descomentar para ver el error)
-- SELECT fn_actualizar_saldo(1, -100.00);


-- -------------------------------------------------------
-- VI.d Eliminación con condición
-- -------------------------------------------------------

-- Desactiva un dispositivo (soft delete)
CREATE OR REPLACE FUNCTION fn_desactivar_dispositivo(
    p_id INT
) RETURNS TEXT AS $$
BEGIN
    UPDATE Dispositivo SET activo = FALSE
    WHERE id_dispositivo = p_id AND activo = TRUE;

    IF NOT FOUND THEN
        RAISE EXCEPTION 'Dispositivo % no existe o ya estaba inactivo', p_id;
    END IF;

    RETURN 'Dispositivo ' || p_id || ' desactivado';
END;
$$ LANGUAGE plpgsql;

-- Elimina un contacto de la agenda de un usuario
CREATE OR REPLACE FUNCTION fn_eliminar_contacto(
    p_id_usuario          INT,
    p_id_usuario_contacto INT
) RETURNS TEXT AS $$
DECLARE
    n INT;
BEGIN
    DELETE FROM Contacto
    WHERE id_usuario           = p_id_usuario
      AND id_usuario_contacto  = p_id_usuario_contacto;

    GET DIAGNOSTICS n = ROW_COUNT;

    IF n = 0 THEN
        RETURN 'Contacto no encontrado';
    END IF;
    RETURN 'Contacto eliminado correctamente';
END;
$$ LANGUAGE plpgsql;

-- Pruebas
SELECT fn_desactivar_dispositivo(1);
SELECT fn_eliminar_contacto(1, 2);


-- -------------------------------------------------------
-- VI.e TRIGGER y STORED PROCEDURE
-- -------------------------------------------------------

-- Función trigger: genera notificación automática al receptor
-- cuando se inserta una transacción con estado 'Completada'
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

-- Prueba del trigger (verificar notificación creada automáticamente)
INSERT INTO Transaccion(id_billetera_emisor,id_billetera_receptor,monto,mensaje,estado)
    VALUES (3, 5, 75.00, 'Prueba trigger', 'Completada');

SELECT * FROM Notificacion ORDER BY id_notificacion DESC LIMIT 1;


-- Stored procedure: transferencia P2P con control de saldo
CREATE OR REPLACE PROCEDURE sp_transferencia(
    p_emisor   INT,
    p_receptor INT,
    p_monto    NUMERIC,
    p_mensaje  TEXT DEFAULT NULL
) AS $$
DECLARE
    v_saldo NUMERIC;
BEGIN
    SELECT saldo INTO v_saldo
      FROM Billetera
     WHERE id_billetera = p_emisor AND estado = 'Activa'
       FOR UPDATE;

    IF v_saldo IS NULL THEN
        RAISE EXCEPTION 'Billetera % no existe o no está activa', p_emisor;
    END IF;

    IF v_saldo < p_monto THEN
        RAISE EXCEPTION 'Saldo insuficiente: disponible S/ %, requerido S/ %',
            v_saldo, p_monto;
    END IF;

    UPDATE Billetera SET saldo = saldo - p_monto WHERE id_billetera = p_emisor;
    UPDATE Billetera SET saldo = saldo + p_monto WHERE id_billetera = p_receptor;

    INSERT INTO Transaccion(
        id_billetera_emisor, id_billetera_receptor, monto, mensaje, estado
    ) VALUES (p_emisor, p_receptor, p_monto, p_mensaje, 'Completada');
END;
$$ LANGUAGE plpgsql;

-- Prueba aceptada: billetera 2 (Eliaz, saldo 580) envía 50 a billetera 3
CALL sp_transferencia(2, 3, 50.00, 'Prueba stored procedure');

-- Verificar saldos actualizados
SELECT id_billetera, saldo FROM Billetera WHERE id_billetera IN (2, 3);

-- Prueba rechazada: monto mayor al saldo disponible (descomentar)
-- CALL sp_transferencia(2, 3, 99999.00, 'Fallo por saldo insuficiente');

-- ============================================================
-- FIN DEL SCRIPT FASE III
-- ============================================================
