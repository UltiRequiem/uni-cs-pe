public class Compra {
  private int p1, p2, compra;

  public Compra (int p1, int p2, int compra){
    this.p1 = p1;
    this.p2 = p2;
    this.compra = compra;
  }

  public void printResults(){
    System.out.println("C1 - C2 - Compra");

    for (int c1 = 1; c1* this.p1 <= this.compra; c1++){
      for (int c2 = 1; c2*this.p2 + c1* this.p1 <= this.compra; c2++){
        System.out.println(
            c1 + " " + c2 + " " + (c1*p1+c2*p2)
            );

      }
    }
  }

  public static void main (String[] args){
    var compra = new Compra(10,20,60);
    compra.printResults();
  } 
}
