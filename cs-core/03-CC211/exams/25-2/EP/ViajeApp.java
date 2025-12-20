import java.util.Random;

public class ViajeApp {
    private static final Random ran = new Random();

    public static void main(String[] args) {
        float[] precios = {1, 1.5f, 2, 2.5f, 3};

        System.out.println("Viaje virtual en bus virtual");
        System.out.println("Parada  Suben  Bajan  En el bus");

        Bus bus = new Bus(3 + ran.nextInt(4), precios);
        bus.viajar();
        
        int enBus = 0;
        for (int i = 0; i < bus.paradas; i++) {
            enBus += bus.suben[i] - bus.bajan[i];
            System.out.printf("%6d %6d %6d %6d\n", i + 1, bus.suben[i], bus.bajan[i], enBus);
        }

        System.out.printf("Total  %6d %6d\n", bus.totalPasajeros, bus.totalPasajeros);
        System.out.printf("Total dinero: %.2f\n", bus.totalDinero);
    }
}
