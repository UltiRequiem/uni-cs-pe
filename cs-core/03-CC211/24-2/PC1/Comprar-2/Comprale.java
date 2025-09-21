public class Comprale {
  private int p1,p2,dinero;
  public Comprale(int p1, int p2,int dinero){
    this.p1=p1;
    this.p2=p2;
    this.dinero=dinero;
  }
  public void resultado(){
    System.out.println("c1- c2 - dinero");

    for(int c1=1;c1*this.p1<=this.dinero;c1++){
      for(int c2=1;c1*this.p1+c2*this.p2<=this.dinero;c2++){
        System.out.println(c1 + " " + c2 + " " + (c1*this.p1 + c2*this.p2));
      }
    }
  }
  public static void main (String[] args){
    var compra= new Comprale(10,20,60);
    compra.resultado();
  }

}
