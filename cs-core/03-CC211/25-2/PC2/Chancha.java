import java.util.Random;

class Estudiante {
    static int estudiantes = 0;
    static int totalAportes = 0;

    int codigo;
    String nombre;

    int totalAporte;

    Estudiante(int codigo, String nombre) {
        this.codigo = codigo;
        this.nombre = nombre;
        this.totalAporte = 0;

        estudiantes++;
    }

    void aportar(int aporte) {
        totalAporte += aporte;
        totalAportes += aporte;
    }
}

public class Chancha {
    public static void displayStudentsNames(Estudiante[] students){
        for (int i = 0; i < students.length; i++) {
            System.out.printf("   %s", students[i].nombre);
        }
    }

    public static Estudiante[] generateStudents(int quantity){
      Estudiante[] estudiantes = new Estudiante[quantity];

      for (int i = 0; i < quantity; i++) {
          estudiantes[i] = new Estudiante(i, "E" + i);
      }

      return estudiantes;
    }

    public static void main(String[] _args) {
        Random ran = new Random();

        int monto = 2000;
        int nEst = 2 + ran.nextInt(5);

        Estudiante[] estudiantes = generateStudents(nEst);

        System.out.print("Cuota");

        displayStudentsNames(estudiantes);
          
        System.out.println("    Total   Mayores aportadores (de dinero)");

        int aporte, aporteFila, aporteMax, aporteTotal = 0;
        int[] aportes = new int[nEst];
        int nFila = 1;

        do {
            System.out.printf("  %2d ", nFila);
            nFila++;
            aporteFila = 0;
            aporteMax = 0;

            for (int i = 0; i < nEst; i++) {
                aporte = 60 + ran.nextInt(11);

                System.out.printf("   %2d", aporte);

                aporteFila += aporte;

                if (aporte > aporteMax) {
                    aporteMax = aporte;
                }

                aportes[i] = aporte;
                estudiantes[i].aportar(aporte);
            }

            System.out.printf(" %7d ", aporteFila);

            aporteTotal += aporteFila;

            System.out.print("  ");

            for (int i = 0; i < nEst; i++) {
                if (aportes[i] == aporteMax) {
                    System.out.print(" " + estudiantes[i].nombre);
                }
            }

            System.out.println();

        } while (aporteTotal < monto);

        System.out.print("Total");
        aporteMax = 0;

        for (int i = 0; i < nEst; i++) {
            aportes[i] = estudiantes[i].totalAporte;

            System.out.printf(" %4d", aportes[i]);

            if (aportes[i] > aporteMax) {
                aporteMax = aportes[i];
            }
        }

        System.out.printf(" %7d  ", Estudiante.totalAportes);

        for (int i = 0; i < nEst; i++) {
            if (aportes[i] == aporteMax) {
                System.out.print("  " + estudiantes[i].nombre);
            }
        }

        System.out.println();
    }

}
