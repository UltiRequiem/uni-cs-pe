import java.util.LinkedList;
import java.util.Random;

public class Bus {
    Random ran = new Random();
    int paradas;
    float[] precios;
    int nprecios;
    int[] suben;
    int[] bajan;
    int pasajeros;
    int totalPasajeros;
    float totalDinero;
    Pasajero p = new Pasajero();
    LinkedList<Pasajero> list = new LinkedList<>();

    public Bus(int paradas, float[] precios) {
        this.paradas = paradas;
        this.precios = precios;
        nprecios = precios.length;
        suben = new int[paradas];
        bajan = new int[paradas];
    }

    public void viajar() {
        // Inicio: primera parada, solo suben pasajeros
        suben[0] = 5 + ran.nextInt(11);
        pasajeros = suben[0];
        totalPasajeros = suben[0];
        for (int j = 0; j < suben[0]; j++) {
            totalDinero += precios[ran.nextInt(nprecios)];
            list.addFirst(p); // Entran por la puerta delantera
        }

        // Repetición: paradas intermedias
        for (int i = 1; i < paradas - 1; i++) {
            bajar(i);
            subir(i);
        }

        // Fin: última parada, solo bajan pasajeros
        bajan[paradas - 1] = pasajeros;
        for (int j = 0; j < bajan[paradas - 1]; j++) {
            list.removeLast(); // Bajan por la puerta trasera
        }
        pasajeros = 0;
    }

    void subir(int i) {
        suben[i] = ran.nextInt(11);
        pasajeros += suben[i];
        totalPasajeros += suben[i];
        for (int j = 0; j < suben[i]; j++) {
            totalDinero += precios[ran.nextInt(nprecios)];
            list.addFirst(p); // Pasajeros entran por la puerta delantera
        }
    }

    void bajar(int i) {
        bajan[i] = Math.min(pasajeros, ran.nextInt(11));
        pasajeros -= bajan[i];
        for (int j = 0; j < bajan[i]; j++) {
            list.removeLast(); // Bajan por la puerta trasera
        }
    }
}
