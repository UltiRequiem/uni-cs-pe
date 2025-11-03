import java.util.ArrayList;
import java.util.Random;
import java.io.*;
import java.nio.file.*;

class Alumno {
    int codigo;
    String nombre;
    int[] notas = new int[4];

    public Alumno(int codigo, String nombre) {
        this.codigo = codigo;
        this.nombre = nombre;
    }
}

interface Ex {
    Random rand = new Random();
    void notas(int i, ArrayList<Alumno> alumnos);
}


class Ex1 implements Ex {
    @Override
    public void notas(int i, ArrayList<Alumno> alumnos) {
        for (var al : alumnos) {
            al.notas[i - 1] = 11 + rand.nextInt(2); 
        }
    }
}

class Ex2 implements Ex {
    @Override
    public void notas(int i, ArrayList<Alumno> alumnos) {
        for (var al : alumnos) {
            al.notas[i - 1] = 13 + rand.nextInt(2);
        }
    }
}

class Ex3 implements Ex {
    @Override
    public void notas(int i, ArrayList<Alumno> alumnos) {
        for (var al : alumnos) {
            al.notas[i - 1] = 15 + rand.nextInt(2);
        }
    }
}

class Ex4 implements Ex {
    @Override
    public void notas(int i, ArrayList<Alumno> alumnos) {
        for (var al : alumnos) {
            al.notas[i - 1] = 17 + rand.nextInt(2); 
        }
    }
}

class ExFactory {
    public Ex getEx(int i) {
        switch (i) {
            case 1: return new Ex1();
            case 2: return new Ex2();
            case 3: return new Ex3();
            case 4: return new Ex4();
            default: return null;
        }
    }
}

class AlumnoDB {
    var alumnos = new ArrayList<>();
    var inPath = null, outPath = null;
    var inFile = null, outFile = null;
    final var FIELD_SEP = "\t";

    AlumnoDB() {
        getAlumnos();
    }

    void getAlumnos() {
        try (var br = new BufferedReader(new FileReader("cc211In.txt"))) {
            String linea;
            while ((linea = br.readLine()) != null) {
                var partes = linea.trim().split("\\s+", 2);
                if (partes.length == 2) {
                    var codigo = Integer.parseInt(partes[0]);
                    var nombre = partes[1];
                    alumnos.add(new Alumno(codigo, nombre));
                }
            }
        } catch (IOException e) {
            System.err.println("Error al leer el archivo: " + e.getMessage());
        }
    }

    void saveAlumnos() {
        try (var pw = new PrintWriter(new FileWriter("cc211Out.txt"))) {
            for (var al : alumnos) {
                pw.printf("%d %-10s", al.codigo, al.nombre);
                for (var nota : al.notas) {
                    pw.printf("  %2d", nota);
                }
                pw.println();
            }
        } catch (IOException e) {
            System.err.println("Error al escribir el archivo: " + e.getMessage());
        }
    }
}

public class CC211App {
    AlumnoDB alDB = new AlumnoDB();
    Ex ex = null;

    public static void main(String[] args) {
        var app = new CC211App();

        app.listaAlumnos(0);

        for (var i = 1; i < 5; i++) {
            app.examen(i);
            app.listaAlumnos(i);
        }

        app.listaAlumnos(5);
    }

    void listaAlumnos(int i) {
        if (i == 0) {
            System.out.println("Calificaciones: CC211");
            System.out.println("Inicio del curso");
            for (var al : alDB.alumnos) {
                System.out.printf("%d %s%n", al.codigo, al.nombre);
            }
        } else if (i == 5) {
            System.out.println("Promedio final");
            for (var al : alDB.alumnos) {
                var suma = 0;
                for (var nota : al.notas) {
                    suma += nota;
                }
                var promedio = suma / 4;
                System.out.printf("%d %-15s %d%n", al.codigo, al.nombre, promedio);
            }
            System.out.println("Buen ciclo jóvenes.");
        } else {
            System.out.println("Examen " + i);
            for (var al : alDB.alumnos) {
                System.out.printf("%d %-15s %d%n", al.codigo, al.nombre, al.notas[i - 1]);
            }
        }
    }

    void examen(int i) {
        var factory = new ExFactory();
        ex = factory.getEx(i);
        ex.notas(i, alDB.alumnos);
        alDB.saveAlumnos();
    }
}
