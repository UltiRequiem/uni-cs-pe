import java.util.Random;

class Abuelo {
    String nombre;
    int ahorro;

    public Abuelo(String nombre) {
        this.nombre = nombre;
        this.ahorro = 0;
    }
}

class Papa {
    String nombre;
    int ahorro;
    Abuelo ab;

    public Papa(String nombre, Abuelo ab) {
        this.nombre = nombre;
        this.ab = ab;
        this.ahorro = 0;
    }
}

class Hijo {
    String nombre;
    int ahorro;
    Papa pa;

    public Hijo(String nombre, Papa pa) {
        this.nombre = nombre;
        this.pa = pa;
        this.ahorro = 0;
    }

    public void ahorrar(int cantidad) {
        this.ahorro += cantidad;
    }

    public void ahorrarPapa(int cantidad) {
        this.pa.ahorro += cantidad;
    }

    public void ahorrarAbuelo(int cantidad) {
        this.pa.ab.ahorro += cantidad;
    }
}

public class FamiliaApp {
    public static void main(String[] args) {
        Random ran = new Random();

        Abuelo ab = new Abuelo("Abuelo");
        Papa pa = new Papa("Papá", ab);
        Hijo hijo1 = new Hijo("Hijo1", pa);
        Hijo hijo2 = new Hijo("Hijo2", pa);

        System.out.println("Contribuciones en miles de soles");
        System.out.printf("%-6s %-8s %-8s %-8s %-8s %-8s%n", "Cuota", "Abuelo", "Papá", "Hijo1", "Hijo2", "Total");

        int totalAbuelo = 0, totalPapa = 0, totalHijo1 = 0, totalHijo2 = 0;
        int cuota = 1;
        int totalAcumulado = 0;

        while (totalAcumulado < 300) {
            int ahorroHijo1 = ran.nextInt(11) + 30;
            int ahorroHijo2 = ran.nextInt(11) + 20;
            int ahorroPapa = ran.nextInt(11) + 10;
            int ahorroAbuelo = ran.nextInt(10) + 1;

            hijo1.ahorrar(ahorroHijo1);
            hijo2.ahorrar(ahorroHijo2);
            hijo1.ahorrarPapa(ahorroPapa);
            hijo2.ahorrarAbuelo(ahorroAbuelo);

            totalHijo1 += ahorroHijo1;
            totalHijo2 += ahorroHijo2;
            totalPapa += ahorroPapa;
            totalAbuelo += ahorroAbuelo;

            int totalCuota = ahorroAbuelo + ahorroPapa + ahorroHijo1 + ahorroHijo2;
            totalAcumulado += totalCuota;

            System.out.printf("%-6d %-8d %-8d %-8d %-8d %-8d%n",
                cuota, ahorroAbuelo, ahorroPapa, ahorroHijo1, ahorroHijo2, totalCuota);

            cuota++;

            if (totalAcumulado >= 300) break;
        }

        int totalGeneral = totalAbuelo + totalPapa + totalHijo1 + totalHijo2;
        System.out.printf("%-6s %-8d %-8d %-8d %-8d %-8d%n",
            "Total", totalAbuelo, totalPapa, totalHijo1, totalHijo2, totalGeneral);

        int saldoRemanente = totalGeneral - 300;
        System.out.println("Saldo remanente en hijo1: " + saldoRemanente + ".");
        System.out.println("Felicidades por la nueva casa.");
        System.out.println("Se lo merecen.");
    }
}