// learning tail recursion
int fibHelper(int n, int previous1, int previous2) {
  if (n == 0) {
    return 1;
  }

  if (n == 2) {
    return previous1;
  }

  return fibHelper(n - 1, previous1 + previous2, previous1);
}

int fib(int n) { return fibHelper(n, 1, 1); }
