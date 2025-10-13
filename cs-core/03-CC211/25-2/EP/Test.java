import java.util.Random;
import java.util.Arrays;

public class Test {
    private static final String[] COLORES = {"blanco", "azul", "rojo"};
    private static final Random random = new Random();

    public static void main(String[] _args) {
        // A: Crear un círculo c y un arreglo cuyos elementos son un clone de c
        CR c = new CR();
        CR[] circulos = new CR[3];

        System.out.println("Círculos clonados");
        System.out.println("Radio Color              Area  Largo  Ancho");
        for (int i = 0; i < circulos.length; i++) {
            circulos[i] = (CR) c.clone();
            System.out.println(circulos[i]);
        }
        System.out.println();

        // B: Cambiar al azar radio, color, largo y ancho
        System.out.println("Cambios de radio, color, largo y ancho");
        System.out.println("Radio  Color             Area  Largo  Ancho");
        for (CR circulo : circulos) {
            circulo.setRadio(random.nextInt(3) + 1); // 1, 2 o 3
            circulo.setColor(COLORES[random.nextInt(COLORES.length)]);
            circulo.getRectangulo().setLargo(random.nextInt(3) + 1);
            circulo.getRectangulo().setAncho(random.nextInt(3) + 1);
            System.out.println(circulo);
        }
        System.out.println();

        // C: Ordenar descendentemente por área
        System.out.println("Circulos ordenados descendentemente por área");
        System.out.println("Radio  Color             Area  Largo  Ancho");
        Arrays.sort(circulos, CR.porAreaDescendente());
        for (CR circulo : circulos) {
            System.out.println(circulo);
        }
        System.out.println();

        // D: Ordenar ascendentemente por color
        System.out.println("Círculos ordenados ascendentemente por color");
        System.out.println("Radio  Color              Area  Largo  Ancho");
        Arrays.sort(circulos);
        for (CR circulo : circulos) {
            System.out.println(circulo);
        }

        // E: Buscar un círculo de color blanco
        CR claveBusqueda = new CR();
        claveBusqueda.setColor("blanco");
        int posicion = Arrays.binarySearch(circulos, claveBusqueda);
        if (posicion >= 0) {
            System.out.println("Un círculo de color blanco está en la posición: " + posicion);
        } else {
            System.out.println("No se encontró un círculo de color blanco");
        }
        System.out.println();

        // F: Ordenar descendentemente por color
        System.out.println("Círculos ordenados descendentemente por color");
        System.out.println("Radio  Color        Area  Largo  Ancho");
        Arrays.sort(circulos, CR.porColorDescendente());
        for (CR circulo : circulos) {
            System.out.println(circulo);
        }

        // G: Buscar un círculo de color blanco (con orden descendente)
        posicion = Arrays.binarySearch(circulos, claveBusqueda, CR.porColorDescendente());
        if (posicion >= 0) {
            System.out.println("Un círculo de color blanco está en la posición: " + posicion);
        } else {
            System.out.println("No se encontró un círculo de color blanco");
        }
    }
}
