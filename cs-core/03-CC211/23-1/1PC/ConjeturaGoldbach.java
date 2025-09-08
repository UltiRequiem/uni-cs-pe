public class ConjeturaGoldbach {

  ConjeturaGoldbach(){
    
  }

  public static void main(String[] args) {

  }

  static boolean esPrimo(int n) {
    if (n < 2 || n == 4) {
      return false;

    }

    for (int i = 2; i < n / 2; i++) {
      if (n % i == 0) {
        return false;
      }
    }

    return true;
  }
}
