import java.util.HashMap;

public class ConjeturaCoolGoldbatch {
  private static void displayGoldbatchResults(HashMap<Integer, Integer> memory, int baseCase) {
    for (var entry : memory.entrySet()) {
      var key = entry.getKey();
      var value = entry.getValue();

      System.out.printf("%d + %d = %d\n", key, value, baseCase);
    }
  }

  public static void goldbach(int baseCase) {

    var memory = new HashMap<Integer, Integer>();

    for (int i = 1; i < baseCase; i++) {
      if (memory.containsKey(i)) {
        break;
      }

      if (esPrimo(i) && esPrimo(baseCase - i)) {
        memory.put(baseCase - i, i);
      }
    }

    displayGoldbatchResults(memory, baseCase);
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
