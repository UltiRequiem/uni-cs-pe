import java.util.ArrayList;

public class ConjeturaGoldbach {

  public static void goldbach(int baseCase) {
    var lowerPrimes = new ArrayList<Integer>();

    for (int i = 0; i < baseCase; i++) {
      if (esPrimo(i)){
        lowerPrimes.add(i);
      }
    }

    for (var p1 : lowerPrimes) {
      for (var p2 : lowerPrimes) {
        if (p1 + p2 == baseCase) {
          System.out.printf("%d + %d = %d", p1, p2, p1 + p2);
          System.out.println();
        }

        if (p1==p2) break;
      }
    }

  }

  public static void main(String[] args) {
    goldbach(22);
  }

  private static boolean esPrimo(int n) {
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
