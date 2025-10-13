import java.util.Comparator;

/**
 * Circulo con rectangulo
 * @author Eliaz Bobadilla
 */
public class CR implements Comparable<CR>, Cloneable {
    private int radio;
    private String color;
    private Rectangulo rectangulo;

    // Populando con valores por defecto
    public CR() {
        this.radio = 1;
        this.color = "blanco";
        this.rectangulo = new Rectangulo();
    }

    public CR(int radio, String color, int largo, int ancho) {
        this.radio = radio;
        this.color = color;
        this.rectangulo = new Rectangulo(largo, ancho);
    }
    
    public CR(int radio, String color, Rectangulo rectangulo) {
        this.radio = radio;
        this.color = color;
        this.rectangulo = rectangulo;
    }

    // INICIO de setters y getters

    public int getRadio() {
        return radio;
    }

    public void setRadio(int radio) {
        this.radio = radio;
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public Rectangulo getRectangulo() {
        return rectangulo;
    }

    public void setRectangulo(Rectangulo rectangulo) {
        this.rectangulo = rectangulo;
    }

    // FIN de setters y getters

    public float getArea() {
        return (float) (Math.PI * radio * radio);
    }

    @Override
    public Object clone() {
      return new CR(radio, color, rectangulo.getLargo(), rectangulo.getAncho());
    }

    @Override
    public int compareTo(CR otro) {
        return this.color.compareTo(otro.color);
    }

    @Override
    public String toString() {
        return String.format("%7d   %-8s %10.6f %s",
            radio, color, getArea(), rectangulo.toString());
    }

    public static Comparator<CR> porAreaDescendente() {
        return new Comparator<CR>() {
            @Override
            public int compare(CR c1, CR c2) {
                return Float.compare(c2.getArea(), c1.getArea());
            }
        };
    }

    public static Comparator<CR> porColorDescendente() {
        return new Comparator<CR>() {
            @Override
            public int compare(CR c1, CR c2) {
                return c2.getColor().compareTo(c1.getColor());
            }
        };
    }
}
