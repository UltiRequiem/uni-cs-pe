// Buggy Code from buggy girl

import java.util.Random;

class Alumno {
  int codigo;
  String nombre;
  int[] pr = new int[5];
  int[] ex = new int[3];
  int notaFinal;

  public Alumno(int codigo, String nombre) {
    this.codigo = codigo;
    this.nombre = nombre;
  }

  public void setPractica(int i, int n) {
    pr[i] = n;
  }

  public void setExamen(int i, int n) {
    ex[i] = n;
  }

  public void setNotaFinal() {
    int suma = 0;
    int min = pr[0];
    for (int i = 0; i < 5; i++) {
      suma += pr[i];
      if (pr[i] < min) {
        min = pr[i];
      }
    }

    
    int notaPracticas = (suma - min) / 4;

    if (ex[2] > Math.min(ex[0], ex[1])) {
      if (ex[0] > ex[1]) {
        notaFinal = (notaPracticas + ex[0] + ex[2]) / 3;
      } else {
        notaFinal = (notaPracticas + ex[1] + ex[2]) / 3;
      }
    }

  }

  public void print() {
    System.out.printf("%-3d %-5s ", codigo, nombre);

    for (int i = 0; i < 5; i++) {
      System.out.printf("%2d ", pr[i]);
    }

    for (int i = 0; i < 3; i++) {
      System.out.printf("%2d ", ex[i]);
    }

    System.out.printf("%2d\n", notaFinal);
  }

}

public class CC211 {
  public static void main(String[] args) {
    Random ran = new Random();
    int numAlumnos = ran.nextInt(10) + 1;
    Alumno[] als = new Alumno[numAlumnos];

    for (int i = 0; i < numAlumnos; i++) {
      als[i] = new Alumno(i, ("Al" + i));

      for (int j = 0; j < 5; j++) {
        als[i].setPractica(j, ran.nextInt(10) + 6);
      }

      for (int j = 0; j < 3; j++) {
        als[i].setExamen(j, ran.nextInt(10) + 7);
      }

      als[i].setNotaFinal();
    }

    System.out.println("Código Nombre Pr1 Pr2 Pr3 Pr4 Pr5 Ep Ef Es Nota");

    for (Alumno al : als) {
      al.print();
    }
  }
}
