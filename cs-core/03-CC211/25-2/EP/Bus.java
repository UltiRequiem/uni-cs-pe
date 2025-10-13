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
        for (int i = 0; i < paradas; i++) {
            bajar(i);
            subir(i);
        }
    }

    private void subir(int i) {
        if (i == paradas - 1) {
            suben[i] = 0;
            return;
        }
        
        int min = i == 0 ? 5 : 0;

        suben[i] = min +ran.nextInt(11);

        pasajeros += suben[i];
        totalPasajeros += suben[i];
        
        for (int j = 0; j < suben[i]; j++) {
            totalDinero += precios[ran.nextInt(nprecios)];
            list.addFirst(p); 
        }
    }

    private void bajar(int i) {
        if (i == 0) {
            bajan[i] = 0;
            return;
        }

        boolean isFinal = i == paradas - 1;
        bajan[i] =  isFinal ? pasajeros: Math.min(pasajeros, ran.nextInt(11));

        pasajeros -= bajan[i];
        
        for (int j = 0; j < bajan[i]; j++) {
            list.removeLast(); 
        }

        if (isFinal) {
            pasajeros = 0;
        }
    }
}
