class Carrito {
  public int mangos=0, naranjas=0, melones=0, total=0;

  public Carrito(int mangos) {
    this.mangos = mangos;
    this.updateTotal();
  }

  public void comprarNaranjas(int narajas) {
    this.naranjas = narajas;
    this.updateTotal();
  }

  public void comprarMelones(int melones) {
    this.melones = melones;
    this.updateTotal();
  }

  private void updateTotal() {
    this.total = melones + naranjas + mangos;
  }

  public void reportar() {
    System.out.println("Se compraron: ");
    System.out.println(this.mangos + " mangos");
    System.out.println(this.naranjas + " naranjas");
    System.out.println(this.melones + " mangos");
    System.out.println("En total: " + this.total + " frutas.");

  }
}

public class Compra {
  public static void main(String[] args) {
    Carrito carrito = new Carrito(1); // asigna: mangos = 1
    carrito.comprarNaranjas(2); // compra 2 naranjas
    carrito.comprarMelones(3); // compra 3 melones
    carrito.reportar(); // reporta la compra de 6 frutas
  }
}
