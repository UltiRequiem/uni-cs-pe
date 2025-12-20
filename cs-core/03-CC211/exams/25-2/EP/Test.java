import java.util.Random;
import java.util.Arrays;

public class Test {
    // Dejamos las variebls constante como estaticas para optimizar memoria
    private static final String[] COLORES = {"blanco", "azul", "rojo"};
    private static final Random random = new Random();

    public static void main(String[] _args) {
        var c = new CR(1, "blanco", new Rectangulo(2, 1));

        // 1ro: Creamos arreglos de clon de C
        var circulos = new CR[1+random.nextInt(8)];
        
        System.out.println("Círculos clonados (" + circulos.length + ") \n");
        System.out.println("      Radio Color    Area       Largo      Ancho");

        for (int i = 0; i < circulos.length; i++) {
            circulos[i] =  c.clone();
            System.out.println(circulos[i]);
        }

        System.out.println();

        // 2do: Cambiar al azar radio, color, largo y ancho
        System.out.println("Cambios de radio, color, largo y ancho\n");
        System.out.println("      Radio Color    Area       Largo      Ancho");
        
        for (CR circulo : circulos) {
            circulo.setRadio(random.nextInt(3) + 1);
            circulo.setColor(COLORES[random.nextInt(COLORES.length)]);

            circulo.getRectangulo().setLargo(random.nextInt(3) + 1);
            circulo.getRectangulo().setAncho(random.nextInt(3) + 1);

            System.out.println(circulo);
        }
        System.out.println();

        // 3ro: Ordenar descendentemente por área
        System.out.println("Circulos ordenados descendentemente por área\n");
        System.out.println("      Radio Color    Area       Largo      Ancho");
        Arrays.sort(circulos, CR.porAreaDescendente());
        
        for (CR circulo : circulos) {
            System.out.println(circulo);
        }
        
        System.out.println();

        // 4to: Ordenar ascendentemente por color
        System.out.println("Círculos ordenados ascendentemente por color (lexicograficamente)");
        System.out.println("      Radio Color    Area       Largo      Ancho");
        // Orden lexicografico por color
        Arrays.sort(circulos);

        for (CR circulo : circulos) {
            System.out.println(circulo);
        }

        // 5to: Buscar un círculo de color blanco
        CR claveBusqueda = new CR();

        claveBusqueda.setColor("blanco");
        int posicion = Arrays.binarySearch(circulos, claveBusqueda);
        
        if (posicion >= 0) {
            System.out.println("\nUn círculo de color blanco está en la posición: " + posicion + "\n");
        } else {
            System.out.println("\nNo se encontró un círculo de color blanco \n");
        }

        System.out.println();

        // 6to: Ordenar descendentemente por color
        System.out.println("Círculos ordenados descendentemente por color");
        System.out.println("      Radio Color    Area       Largo      Ancho");
        
        Arrays.sort(circulos, CR.porColorDescendente());
        
        for (CR circulo : circulos) {
            System.out.println(circulo);
        }

        // 7mo: Buscar un circulo de color blanco (con orden descendente)
        posicion = Arrays.binarySearch(circulos, claveBusqueda, CR.porColorDescendente());

        if (posicion >= 0) {
            System.out.println("\nUn círculo de color blanco está en la posición: " + posicion + "\n");
        } else {
            System.out.println("No se encontró un círculo de color blanco\n");
        }
    }
}
