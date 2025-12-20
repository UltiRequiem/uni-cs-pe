import java.util.ArrayList;

public class ConjeturaCollatz {

  private static int nextCollatz(int number) {
    if (number % 2 == 0) {
      return number / 2;
    }

    return 3 * number + 1;
  }

  public static void collatz(int baseCase) {
    var results = new ArrayList<Integer>();

    while (baseCase != 1){
      var nextItem = nextCollatz(baseCase);
      results.add(baseCase);
      baseCase = nextItem;
    }

    results.add(1);

    System.out.println(results);
  }

  public static void main(String[] args) {
    collatz(13);
  }
}
