export function gcd(a: number, b: number): number {
  // a < b self-corrects in one extra iteration (a % b = a when a < b,
  // then a and b swap), so caller order doesn't matter.
  while (b !== 0) {
    const remainder = a % b;
    a = b;
    b = remainder;
  }

  // gcd(0, 0) falls through to here and returns 0 (convention, not defined math).
  // Negative inputs: JS % keeps dividend's sign, so result can end up negative.
  return a;
}
