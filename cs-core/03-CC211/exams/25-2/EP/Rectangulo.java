/**
  Clase Rectangulo
  @author Eliaz Bobadilla
*/

public class Rectangulo implements Cloneable {
    private int largo;
    private int ancho;

    /**
    En caso no se tengan parametros, sera un cuadrado por defecto.
    */
    public Rectangulo() {
        this.largo = 1;
        this.ancho = 1;
    }

    public Rectangulo(int largo, int ancho) {
        this.largo = largo;
        this.ancho = ancho;
    }

    // INICIO de getters y setters

    public int getLargo() {
        return largo;
    }

    public void setLargo(int largo) {
        this.largo = largo;
    }

    public int getAncho() {
        return ancho;
    }

    public void setAncho(int ancho) {
        this.ancho = ancho;

    }

    // FIN de getters y setters

    @Override
    public Object clone() {
      return new Rectangulo(largo, ancho);
    }

    @Override
    public String toString() {
        return String.format("%7d %10d", largo, ancho);
    }
}
