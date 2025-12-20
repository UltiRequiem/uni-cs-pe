import java.util.ArrayList;
import java.util.HashMap;

public class Conjeturas {
  private static int nextCollatz(int number) {
    if (number % 2 == 0) {
      return number / 2;
    }

    return 3 * number + 1;
  }

  public static void collatz(int baseCase) {
    var results = new ArrayList<Integer>();

    while (baseCase != 1) {
      var nextItem = nextCollatz(baseCase);
      results.add(baseCase);
      baseCase = nextItem;
    }

    results.add(1);

    System.out.println(results);
  }

  public static void goldbach(int baseCase) {
    var memory = new HashMap<Integer, Integer>();

    for (int i = 1; i < baseCase; i++) {
      if (esPrimo(i) && esPrimo(baseCase - i) && !memory.containsKey(i)) {
        memory.put(baseCase - i, i);
      }
    }

    System.out.println(memory);
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

  public static void main(String[] args) {
    goldbach(22);
    collatz(13);
  }

}
