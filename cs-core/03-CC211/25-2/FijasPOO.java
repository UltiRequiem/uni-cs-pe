/**
 * MATERIAL DIDÁCTICO: PROGRAMACIÓN ORIENTADA A OBJETOS EN JAVA
 * DIRIGIDO A PROGRAMADORES CON EXPERIENCIA EN C++
 *
 * PRÁCTICA CALIFICADA 1 (PC1) - SEMANA 3
 *
 * Temas cubiertos:
 * 1. Diferencias entre clases y objetos en C++ vs Java
 * 2. Visibilidad y modificadores de acceso
 * 3. Relaciones entre clases (has-a, is-a)
 * 4. Ejemplos prácticos comparados
 * 5. Ejercicio tipo PC1: Sistema Académico
 *
 * @author Profesor Java
 * @version 1.0
 */
public class FijasPOO {

    /**
     * =========================================================================
     * SECCIÓN 1: EXPLICACIÓN TEÓRICA - DIFERENCIAS C++ vs JAVA
     * =========================================================================
     */

    /*
     * DIFERENCIAS CLAVE ENTRE C++ Y JAVA:
     *
     * 1. GESTIÓN DE MEMORIA:
     *    C++: Manual (new/delete, stack/heap explícito)
     *    Java: Automática (Garbage Collector, solo referencias)
     *
     * 2. PUNTEROS:
     *    C++: Punteros explícitos (*ptr, &ref)
     *    Java: Solo referencias (sin aritmética de punteros)
     *
     * 3. CONSTRUCTORES/DESTRUCTORES:
     *    C++: Constructor + Destructor obligatorio para recursos
     *    Java: Constructor + finalize() (rara vez usado)
     *
     * 4. HERENCIA:
     *    C++: Herencia múltiple permitida
     *    Java: Solo herencia simple + interfaces múltiples
     *
     * 5. MODIFICADORES DE ACCESO:
     *    C++: public, private, protected
     *    Java: public, private, protected + package-private (default)
     */

    /**
     * =========================================================================
     * SECCIÓN 2: EJEMPLO COMPARATIVO C++ vs JAVA
     * =========================================================================
     */

    /*
     * EJEMPLO EN C++:
     *
     * class Persona {
     * private:
     *     string nombre;
     *     int edad;
     *
     * public:
     *     // Constructor
     *     Persona(string n, int e) : nombre(n), edad(e) {}
     *
     *     // Destructor
     *     ~Persona() { cout << "Destruyendo persona" << endl; }
     *
     *     // Métodos
     *     void setEdad(int e) { edad = e; }
     *     int getEdad() const { return edad; }
     *
     *     void mostrarInfo() const {
     *         cout << "Nombre: " << nombre << ", Edad: " << edad << endl;
     *     }
     * };
     *
     * // Uso:
     * Persona* p1 = new Persona("Juan", 25);  // Heap
     * Persona p2("Ana", 30);                  // Stack
     * delete p1;  // ¡Obligatorio!
     */

    // EQUIVALENTE EN JAVA:

    /**
     * Clase Persona - Ejemplo básico en Java
     * Nota para programadores C++: No hay destructores explícitos
     */
    static class Persona {
        // Atributos privados (equivalente a private en C++)
        private String nombre;  // String, no char* ni std::string
        private int edad;

        // Constructor (similar a C++, pero sin inicialización en lista)
        public Persona(String nombre, int edad) {
            this.nombre = nombre;  // 'this' equivale a 'this->' en C++
            this.edad = edad;
        }

        // No hay destructor en Java - el Garbage Collector se encarga
        // Raramente se usa finalize() y está deprecated desde Java 9

        // Métodos getter/setter (buena práctica en Java)
        public void setEdad(int edad) {
            this.edad = edad;
        }

        public int getEdad() {
            return edad;  // No necesita 'this.edad' si no hay ambigüedad
        }

        public String getNombre() {
            return nombre;
        }

        // Método para mostrar información
        public void mostrarInfo() {
            System.out.println("Nombre: " + nombre + ", Edad: " + edad);
        }

        // toString() - equivalente al operator<< en C++
        @Override
        public String toString() {
            return "Persona{nombre='" + nombre + "', edad=" + edad + "}";
        }
    }

    /**
     * =========================================================================
     * SECCIÓN 3: RELACIONES ENTRE CLASES Y UML
     * =========================================================================
     */

    /*
     * UML BÁSICO PARA LAS RELACIONES:
     *
     * 1. RELACIÓN "HAS-A" (COMPOSICIÓN):
     *
     *    +----------------+        +----------------+
     *    |   Automovil    |◆-------|     Motor      |
     *    +----------------+        +----------------+
     *    | -marca: String |        | -potencia: int |
     *    | -motor: Motor  |        | -tipo: String  |
     *    +----------------+        +----------------+
     *    | +acelerar()    |        | +encender()    |
     *    | +frenar()      |        | +apagar()      |
     *    +----------------+        +----------------+
     *
     * El diamante relleno (◆) indica composición fuerte
     *
     * 2. RELACIÓN "IS-A" (HERENCIA):
     *
     *    +----------------+
     *    |    Vehiculo    |
     *    +----------------+
     *    | -marca: String |
     *    | -modelo: String|
     *    +----------------+
     *    | +acelerar()    |
     *    +----------------+
     *            △
     *            |
     *    +----------------+
     *    |   Automovil    |
     *    +----------------+
     *    | -numPuertas:int|
     *    +----------------+
     *    | +abrirPuertas()|
     *    +----------------+
     *
     * El triángulo vacío (△) indica herencia
     */

    // EJEMPLO DE COMPOSICIÓN (HAS-A)

    /**
     * Clase Motor - Componente para demostrar composición
     */
    static class Motor {
        private int potencia;
        private String tipo;
        private boolean encendido;

        public Motor(int potencia, String tipo) {
            this.potencia = potencia;
            this.tipo = tipo;
            this.encendido = false;
        }

        public void encender() {
            encendido = true;
            System.out.println("Motor " + tipo + " encendido (" + potencia + " HP)");
        }

        public void apagar() {
            encendido = false;
            System.out.println("Motor apagado");
        }

        public boolean isEncendido() { return encendido; }
        public int getPotencia() { return potencia; }
        public String getTipo() { return tipo; }
    }

    /**
     * Clase Automovil - Demuestra composición con Motor
     * Nota C++: En Java no necesitamos preocuparnos por liberar memoria del Motor
     */
    static class Automovil {
        private String marca;
        private String modelo;
        private Motor motor;  // Relación HAS-A (composición)

        // Constructor que crea el motor (composición fuerte)
        public Automovil(String marca, String modelo, int potenciaMotor, String tipoMotor) {
            this.marca = marca;
            this.modelo = modelo;
            this.motor = new Motor(potenciaMotor, tipoMotor);  // Composición
        }

        public void acelerar() {
            if (motor.isEncendido()) {
                System.out.println(marca + " " + modelo + " acelerando...");
            } else {
                System.out.println("Debe encender el motor primero");
            }
        }

        public void encenderMotor() {
            motor.encender();
        }

        public void apagarMotor() {
            motor.apagar();
        }

        // Getters
        public String getMarca() { return marca; }
        public String getModelo() { return modelo; }
        public Motor getMotor() { return motor; }
    }

    // EJEMPLO DE HERENCIA (IS-A)

    /**
     * Clase base Vehiculo - Para demostrar herencia
     */
    static class Vehiculo {
        protected String marca;    // protected: accesible en subclases
        protected String modelo;
        protected int velocidad;

        public Vehiculo(String marca, String modelo) {
            this.marca = marca;
            this.modelo = modelo;
            this.velocidad = 0;
        }

        public void acelerar() {
            velocidad += 10;
            System.out.println("Velocidad: " + velocidad + " km/h");
        }

        public void frenar() {
            velocidad = Math.max(0, velocidad - 10);
            System.out.println("Velocidad: " + velocidad + " km/h");
        }

        // Método que puede ser sobrescrito
        public void mostrarInfo() {
            System.out.println("Vehículo: " + marca + " " + modelo);
        }

        // Getters
        public String getMarca() { return marca; }
        public String getModelo() { return modelo; }
        public int getVelocidad() { return velocidad; }
    }

    /**
     * Clase AutomovilHerencia - Demuestra herencia de Vehiculo
     * Nota C++: 'extends' es equivalente a ':' en C++
     */
    static class AutomovilHerencia extends Vehiculo {
        private int numPuertas;

        public AutomovilHerencia(String marca, String modelo, int numPuertas) {
            super(marca, modelo);  // Llamada al constructor padre (equivale a lista de inicialización)
            this.numPuertas = numPuertas;
        }

        // Método específico de la subclase
        public void abrirPuertas() {
            System.out.println("Abriendo " + numPuertas + " puertas");
        }

        // Sobrescribir método de la clase padre
        @Override  // Anotación para verificar sobrescritura (buena práctica)
        public void mostrarInfo() {
            super.mostrarInfo();  // Llamar al método padre
            System.out.println("Número de puertas: " + numPuertas);
        }

        // Getter específico
        public int getNumPuertas() { return numPuertas; }
    }

    /**
     * =========================================================================
     * SECCIÓN 4: EJERCICIO TIPO PC1 - SISTEMA ACADÉMICO
     * =========================================================================
     */

    /*
     * UML DEL SISTEMA ACADÉMICO:
     *
     *    +------------------+     +------------------+     +------------------+
     *    |     Alumno       |     |      Curso       |     |    Profesor      |
     *    +------------------+     +------------------+     +------------------+
     *    | -codigo: String  |     | -codigo: String  |     | -codigo: String  |
     *    | -nombre: String  |     | -nombre: String  |     | -nombre: String  |
     *    | -edad: int       |     | -creditos: int   |     | -especialidad: String |
     *    | -notas: double[] |     | -alumnos: Alumno[]|     | -cursos: Curso[] |
     *    +------------------+     +------------------+     +------------------+
     *    | +matricular()    |     | +matricularAlumno() |  | +asignarCurso()  |
     *    | +calcularPromedio() |  | +calificarAlumno()  |  | +calificarAlumno() |
     *    | +mostrarInfo()   |     | +mostrarAlumnos()   |  | +mostrarInfo()   |
     *    +------------------+     +------------------+     +------------------+
     *                |                       |                       |
     *                |                       |                       |
     *                +----------- agregación/composición ------------+
     *
     * RELACIONES:
     * - Alumno se matricula en Curso (muchos a muchos)
     * - Profesor dicta Curso (uno a muchos)
     * - Curso tiene Alumnos matriculados (uno a muchos)
     */

    /**
     * Clase Alumno - Entidad del sistema académico
     */
    static class Alumno {
        private String codigo;
        private String nombre;
        private int edad;
        private double[] notas;
        private int numNotas;

        public Alumno(String codigo, String nombre, int edad) {
            this.codigo = codigo;
            this.nombre = nombre;
            this.edad = edad;
            this.notas = new double[10];  // Máximo 10 notas
            this.numNotas = 0;
        }

        public void agregarNota(double nota) {
            if (numNotas < notas.length && nota >= 0 && nota <= 20) {
                notas[numNotas] = nota;
                numNotas++;
                System.out.println("Nota " + nota + " agregada a " + nombre);
            } else {
                System.out.println("No se puede agregar la nota (límite alcanzado o nota inválida)");
            }
        }

        public double calcularPromedio() {
            if (numNotas == 0) return 0.0;

            double suma = 0;
            for (int i = 0; i < numNotas; i++) {
                suma += notas[i];
            }
            return suma / numNotas;
        }

        public void mostrarInfo() {
            System.out.println("=== INFORMACIÓN DEL ALUMNO ===");
            System.out.println("Código: " + codigo);
            System.out.println("Nombre: " + nombre);
            System.out.println("Edad: " + edad);
            System.out.printf("Promedio: %.2f%n", calcularPromedio());

            if (numNotas > 0) {
                System.out.print("Notas: ");
                for (int i = 0; i < numNotas; i++) {
                    System.out.print(notas[i]);
                    if (i < numNotas - 1) System.out.print(", ");
                }
                System.out.println();
            }
        }

        // Getters
        public String getCodigo() { return codigo; }
        public String getNombre() { return nombre; }
        public int getEdad() { return edad; }
        public double[] getNotas() { return notas.clone(); }  // Defensive copy
        public int getNumNotas() { return numNotas; }
    }

    /**
     * Clase Curso - Entidad del sistema académico
     */
    static class Curso {
        private String codigo;
        private String nombre;
        private int creditos;
        private Alumno[] alumnos;
        private int numAlumnos;
        private Profesor profesor;

        public Curso(String codigo, String nombre, int creditos) {
            this.codigo = codigo;
            this.nombre = nombre;
            this.creditos = creditos;
            this.alumnos = new Alumno[30];  // Máximo 30 alumnos
            this.numAlumnos = 0;
        }

        public boolean matricularAlumno(Alumno alumno) {
            if (numAlumnos < alumnos.length) {
                // Verificar que el alumno no esté ya matriculado
                for (int i = 0; i < numAlumnos; i++) {
                    if (alumnos[i].getCodigo().equals(alumno.getCodigo())) {
                        System.out.println("El alumno ya está matriculado en este curso");
                        return false;
                    }
                }

                alumnos[numAlumnos] = alumno;
                numAlumnos++;
                System.out.println("Alumno " + alumno.getNombre() + " matriculado en " + nombre);
                return true;
            } else {
                System.out.println("Curso lleno, no se puede matricular más alumnos");
                return false;
            }
        }

        public void calificarAlumno(String codigoAlumno, double nota) {
            for (int i = 0; i < numAlumnos; i++) {
                if (alumnos[i].getCodigo().equals(codigoAlumno)) {
                    alumnos[i].agregarNota(nota);
                    return;
                }
            }
            System.out.println("Alumno no encontrado en este curso");
        }

        public void mostrarAlumnos() {
            System.out.println("=== ALUMNOS DEL CURSO " + nombre + " ===");
            if (numAlumnos == 0) {
                System.out.println("No hay alumnos matriculados");
                return;
            }

            for (int i = 0; i < numAlumnos; i++) {
                System.out.printf("%d. %s (%s) - Promedio: %.2f%n",
                    i + 1,
                    alumnos[i].getNombre(),
                    alumnos[i].getCodigo(),
                    alumnos[i].calcularPromedio());
            }
        }

        public void asignarProfesor(Profesor profesor) {
            this.profesor = profesor;
            System.out.println("Profesor " + profesor.getNombre() + " asignado al curso " + nombre);
        }

        // Getters
        public String getCodigo() { return codigo; }
        public String getNombre() { return nombre; }
        public int getCreditos() { return creditos; }
        public int getNumAlumnos() { return numAlumnos; }
        public Profesor getProfesor() { return profesor; }
    }

    /**
     * Clase Profesor - Entidad del sistema académico
     */
    static class Profesor {
        private String codigo;
        private String nombre;
        private String especialidad;
        private Curso[] cursos;
        private int numCursos;

        public Profesor(String codigo, String nombre, String especialidad) {
            this.codigo = codigo;
            this.nombre = nombre;
            this.especialidad = especialidad;
            this.cursos = new Curso[5];  // Máximo 5 cursos
            this.numCursos = 0;
        }

        public boolean asignarCurso(Curso curso) {
            if (numCursos < cursos.length) {
                cursos[numCursos] = curso;
                numCursos++;
                curso.asignarProfesor(this);  // Relación bidireccional
                return true;
            } else {
                System.out.println("Profesor tiene el máximo de cursos asignados");
                return false;
            }
        }

        public void calificarAlumno(String codigoCurso, String codigoAlumno, double nota) {
            for (int i = 0; i < numCursos; i++) {
                if (cursos[i].getCodigo().equals(codigoCurso)) {
                    cursos[i].calificarAlumno(codigoAlumno, nota);
                    return;
                }
            }
            System.out.println("El profesor no dicta ese curso");
        }

        public void mostrarInfo() {
            System.out.println("=== INFORMACIÓN DEL PROFESOR ===");
            System.out.println("Código: " + codigo);
            System.out.println("Nombre: " + nombre);
            System.out.println("Especialidad: " + especialidad);
            System.out.println("Cursos a cargo:");

            if (numCursos == 0) {
                System.out.println("  No tiene cursos asignados");
            } else {
                for (int i = 0; i < numCursos; i++) {
                    System.out.println("  - " + cursos[i].getNombre() +
                                     " (" + cursos[i].getCodigo() + ")");
                }
            }
        }

        // Getters
        public String getCodigo() { return codigo; }
        public String getNombre() { return nombre; }
        public String getEspecialidad() { return especialidad; }
        public int getNumCursos() { return numCursos; }
    }

    /**
     * =========================================================================
     * SECCIÓN 5: PROGRAMA PRINCIPAL Y EJEMPLOS
     * =========================================================================
     */

    /**
     * Método principal para ejecutar ejemplos y demostraciones
     */
    public static void main(String[] args) {
        System.out.println("╔══════════════════════════════════════════════════════════════╗");
        System.out.println("║           PRÁCTICA CALIFICADA 1 - POO EN JAVA               ║");
        System.out.println("║              Para programadores con experiencia en C++      ║");
        System.out.println("╚══════════════════════════════════════════════════════════════╝");

        // Demostración 1: Diferencias básicas
        demostrarDiferenciasBasicas();

        // Demostración 2: Composición (HAS-A)
        demostrarComposicion();

        // Demostración 3: Herencia (IS-A)
        demostrarHerencia();

        // Demostración 4: Sistema Académico Completo
        demostrarSistemaAcademico();

        System.out.println("\n╔══════════════════════════════════════════════════════════════╗");
        System.out.println("║                    FIN DE LA DEMOSTRACIÓN                   ║");
        System.out.println("╚══════════════════════════════════════════════════════════════╝");
    }

    /**
     * Demuestra las diferencias básicas entre C++ y Java
     */
    private static void demostrarDiferenciasBasicas() {
        System.out.println("\n1. DIFERENCIAS BÁSICAS C++ vs JAVA");
        System.out.println("═══════════════════════════════════");

        // En Java, todo son referencias (no hay punteros explícitos)
        Persona persona1 = new Persona("Juan Pérez", 25);
        Persona persona2 = persona1;  // Copia de referencia, no del objeto

        System.out.println("Objeto original:");
        persona1.mostrarInfo();

        // Modificar a través de la segunda referencia
        persona2.setEdad(30);

        System.out.println("Después de modificar edad via persona2:");
        persona1.mostrarInfo();  // También cambió porque apunta al mismo objeto

        System.out.println("\nNota para programadores C++:");
        System.out.println("- No hay delete explícito (Garbage Collector automático)");
        System.out.println("- persona2 = persona1 copia la referencia, no el objeto");
        System.out.println("- Equivale a: Persona* persona2 = persona1; en C++");
    }

    /**
     * Demuestra el concepto de composición (HAS-A)
     */
    private static void demostrarComposicion() {
        System.out.println("\n2. COMPOSICIÓN (HAS-A)");
        System.out.println("══════════════════════");

        Automovil auto = new Automovil("Toyota", "Corolla", 120, "Gasolina");

        System.out.println("Creado automóvil: " + auto.getMarca() + " " + auto.getModelo());

        auto.acelerar();  // No debería funcionar sin encender
        auto.encenderMotor();
        auto.acelerar();  // Ahora sí funciona
        auto.apagarMotor();

        System.out.println("\nNota para programadores C++:");
        System.out.println("- El Motor se crea automáticamente en el constructor");
        System.out.println("- No necesitamos preocuparnos por liberar memoria del Motor");
        System.out.println("- La composición se maneja con referencias, no punteros");
    }

    /**
     * Demuestra el concepto de herencia (IS-A)
     */
    private static void demostrarHerencia() {
        System.out.println("\n3. HERENCIA (IS-A)");
        System.out.println("══════════════════");

        AutomovilHerencia auto = new AutomovilHerencia("Honda", "Civic", 4);

        // Métodos heredados
        auto.acelerar();
        auto.acelerar();

        // Método específico de la subclase
        auto.abrirPuertas();

        // Método sobrescrito
        auto.mostrarInfo();

        auto.frenar();

        System.out.println("\nNota para programadores C++:");
        System.out.println("- 'extends' equivale a ':' en C++");
        System.out.println("- 'super()' equivale a la lista de inicialización");
        System.out.println("- '@Override' verifica que realmente sobrescribimos");
        System.out.println("- Solo herencia simple (no múltiple como C++)");
    }

    /**
     * Demuestra el sistema académico completo
     */
    private static void demostrarSistemaAcademico() {
        System.out.println("\n4. SISTEMA ACADÉMICO COMPLETO");
        System.out.println("═══════════════════════════════");

        // Crear alumnos
        Alumno alumno1 = new Alumno("A001", "María García", 20);
        Alumno alumno2 = new Alumno("A002", "Carlos López", 21);
        Alumno alumno3 = new Alumno("A003", "Ana Rodríguez", 19);

        // Crear cursos
        Curso poo = new Curso("CS101", "Programación Orientada a Objetos", 4);
        Curso bd = new Curso("CS201", "Base de Datos", 3);

        // Crear profesor
        Profesor profesor1 = new Profesor("P001", "Dr. Roberto Martínez", "Ingeniería de Software");

        // Asignar cursos al profesor
        profesor1.asignarCurso(poo);
        profesor1.asignarCurso(bd);

        // Matricular alumnos
        poo.matricularAlumno(alumno1);
        poo.matricularAlumno(alumno2);
        bd.matricularAlumno(alumno1);
        bd.matricularAlumno(alumno3);

        // Calificar alumnos
        profesor1.calificarAlumno("CS101", "A001", 18.5);
        profesor1.calificarAlumno("CS101", "A001", 16.0);
        profesor1.calificarAlumno("CS101", "A002", 19.0);

        poo.calificarAlumno("A002", 17.5);
        bd.calificarAlumno("A001", 15.5);
        bd.calificarAlumno("A003", 20.0);

        // Mostrar información
        System.out.println();
        profesor1.mostrarInfo();

        System.out.println();
        poo.mostrarAlumnos();

        System.out.println();
        bd.mostrarAlumnos();

        System.out.println();
        alumno1.mostrarInfo();

        System.out.println("\nEJERCICIO PARA ESTUDIANTES:");
        System.out.println("1. Agregar método para buscar alumno por código");
        System.out.println("2. Implementar validación de notas (0-20)");
        System.out.println("3. Crear método para dar de baja a un alumno");
        System.out.println("4. Agregar atributo 'semestre' a la clase Curso");
        System.out.println("5. Implementar sistema de prerrequisitos entre cursos");
    }

    /**
     * =========================================================================
     * SECCIÓN 6: GUÍA DEL IDE Y COMPILACIÓN
     * =========================================================================
     */

    /*
     * GUÍA PASO A PASO PARA COMPILAR Y EJECUTAR:
     *
     * 1. EN INTELLIJ IDEA:
     *    - File → New → Project
     *    - Seleccionar Java
     *    - Crear proyecto con JDK 8 o superior
     *    - Crear package: functions
     *    - Crear clase: FijasPOO
     *    - Copiar este código
     *    - Click derecho en main() → Run 'FijasPOO.main()'
     *
     * 2. EN NETBEANS:
     *    - File → New Project → Java → Java Application
     *    - Crear package: functions
     *    - New → Java Class → FijasPOO
     *    - Copiar este código
     *    - F6 para ejecutar
     *
     * 3. LÍNEA DE COMANDOS:
     *    $ javac -d . FijasPOO.java
     *    $ java functions.FijasPOO
     *
     * 4. ESTRUCTURA DE DIRECTORIOS RECOMENDADA:
     *    MiProyecto/
     *    ├── src/
     *    │   └── functions/
     *    │       └── FijasPOO.java
     *    ├── bin/    (archivos .class)
     *    └── docs/   (documentación)
     */

    /**
     * =========================================================================
     * SECCIÓN 7: DOCUMENTACIÓN Y BUENAS PRÁCTICAS
     * =========================================================================
     */

    /*
     * DOCUMENTACIÓN JAVADOC:
     *
     * Generar documentación HTML:
     * $ javadoc -d docs -sourcepath src functions
     *
     * CONVENCIONES DE NOMENCLATURA EN JAVA:
     * - Clases: PascalCase (ej: MiClase)
     * - Métodos y variables: camelCase (ej: miMetodo, miVariable)
     * - Constantes: UPPER_SNAKE_CASE (ej: MAX_SIZE)
     * - Packages: lowercase (ej: com.empresa.proyecto)
     *
     * DIFERENCIAS CON C++:
     * - No hay archivos .h (header files)
     * - Un archivo .java por clase pública
     * - Package define el namespace
     * - Import en lugar de #include
     */
}
