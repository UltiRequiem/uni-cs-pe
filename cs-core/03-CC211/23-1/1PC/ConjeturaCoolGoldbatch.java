import java.util.HashMap;

public class ConjeturaCoolGoldbatch {

  public static void goldbach(int baseCase) {
    var memory = new HashMap<Integer, Integer>();

    for (int i = 1; i < baseCase; i++) {
      if (esPrimo(i) && esPrimo(baseCase - i) && !memory.containsKey(i)) {
        memory.put(baseCase - i, i);
      }
    }

    System.out.println(memory);
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
