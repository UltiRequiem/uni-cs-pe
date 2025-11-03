import java.io.*;
import java.util.*;

class Estudiante {
    private String codigo;
    private String nombre;
    private int[] notas;

    private Estudiante(String codigo, String nombre) {
        this.codigo = codigo;
        this.nombre = nombre;
        this.notas = new int[4];
    }

    public static Estudiante crear(String codigo, String nombre) {
        return new Estudiante(codigo, nombre);
    }

    public String getCodigo() {
        return codigo;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNota(int examen, int nota) {
        this.notas[examen] = nota;
    }

    public int getNota(int examen) {
        return notas[examen];
    }

    public int getPromedio() {
        var sum = Arrays.stream(notas).reduce(0, (a, b) -> a + b);

        return sum / 4;
    }

    public int[] getNotas() {
        return notas;
    }
}

public class CC211App {
    private List<Estudiante> estudiantes;
    private Random random;

    public CC211App() {
        estudiantes = new ArrayList<>();
        random = new Random();
    }

    public void leerEstudiantes(String archivo) {
        try (var br = new BufferedReader(new FileReader(archivo))) {
            String linea;
            while ((linea = br.readLine()) != null) {
                var partes = linea.trim().split("\\s+", 2);

                if (partes.length == 2) {
                    var est = Estudiante.crear(partes[0], partes[1]);
                    estudiantes.add(est);
                }
            }
        } catch (IOException e) {
            System.err.println("Error al leer el archivo: " + e.getMessage());
        }
    }

    public void mostrarInicioCurso() {
        System.out.println("Calificaciones: CC211");
        System.out.println("Inicio del curso");

        for (var est : estudiantes) {
            System.out.println(est.getCodigo() + " " + est.getNombre());
        }
    }

    public void realizarExamen(int numeroExamen) {
        System.out.println("Examen " + numeroExamen);

        for (var est : estudiantes) {
            var nota = generarNota(numeroExamen);
            est.setNota(numeroExamen - 1, nota);
            System.out.printf("%s %-15s %d%n", est.getCodigo(), est.getNombre(), nota);
        }
    }

    private int generarNota(int numeroExamen) {
        var base = 10 + (numeroExamen - 1) * 3;
        return base + random.nextInt(3);
    }

    public void mostrarPromedioFinal() {
        System.out.println("Promedio final");

        for (var est : estudiantes) {
            System.out.printf("%s %-15s %d%n", est.getCodigo(), est.getNombre(), est.getPromedio());
        }
        
        System.out.println("Buen ciclo jóvenes.");
    }

    public void guardarResultados(String archivo) {
        try (var pw = new PrintWriter(new FileWriter(archivo))) {
            for (var est : estudiantes) {
                pw.printf("%s %-10s", est.getCodigo(), est.getNombre());

                for (var nota : est.getNotas()) {
                    pw.printf("  %2d", nota);
                }

                pw.println();
            }
        } catch (IOException e) {
            System.err.println("Error al escribir el archivo: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        var app = new CC211App();

        app.leerEstudiantes("cc211In.txt");

        app.mostrarInicioCurso();

        for (int i = 1; i <= 4; i++) {
            app.realizarExamen(i);
        }

        app.mostrarPromedioFinal();

        app.guardarResultados("cc211Out.txt");
    }
}
