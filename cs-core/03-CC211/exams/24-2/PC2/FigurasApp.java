abstract class Figuras {
    public abstract double area();
    public abstract double perimetro();
}

class Circulo extends Figuras {
    double radio;

    public Circulo(double radio) {
        this.radio = radio;
    }

    @Override
    public double area() {
        return Math.PI * radio * radio;
    }

    @Override
    public double perimetro() {
        return 2 * Math.PI * radio;
    }
}

class Rectangulo extends Figuras {
    double largo;
    double ancho;

    public Rectangulo(double largo, double ancho) {
        this.largo = largo;
        this.ancho = ancho;
    }

    @Override
    public double area() {
        return largo * ancho;
    }

    @Override
    public double perimetro() {
        return 2 * (largo + ancho);
    }
}

public class FigurasApp {
    public static void main(String[] args) {
        Circulo c = new Circulo(2);
        Rectangulo r = new Rectangulo(4, 2);

        System.out.println("Breve muestra de dos figuras:");
        System.out.printf("Círculo   : radio = %6.3f; área = %6.3f,  perímetro = %6.3f%n",
            c.radio, c.area(), c.perimetro());
        System.out.printf("Rectángulo: largo = %6.3f, ancho = %6.3f;  área = %6.3f, perímetro = %6.3f%n",
            r.largo, r.ancho, r.area(), r.perimetro());
    }
}