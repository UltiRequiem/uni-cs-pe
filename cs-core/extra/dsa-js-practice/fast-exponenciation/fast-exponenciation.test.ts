import { assertEquals } from "https://deno.land/std/assert/mod.ts";
import { modPow, power } from "./fast-exponenciation.ts";

Deno.test("power of positive exponent", () => {
  assertEquals(power(2, 10), 1024);
});

Deno.test("power of 0 exponent returns 1", () => {
  assertEquals(power(5, 0), 1);
});

Deno.test("power of 1 exponent returns base", () => {
  assertEquals(power(7, 1), 7);
});

Deno.test("power of odd exponent", () => {
  assertEquals(power(3, 5), 243);
});

Deno.test("power of base 0 with positive exponent", () => {
  assertEquals(power(0, 4), 0);
});

Deno.test("power of base 1 returns 1", () => {
  assertEquals(power(1, 999), 1);
});

Deno.test("modPow of positive exponent", () => {
  assertEquals(modPow(2, 10, 1000), 24);
});

Deno.test("modPow of 0 exponent returns 1 mod m", () => {
  assertEquals(modPow(7, 0, 5), 1);
});

Deno.test("modPow of odd exponent", () => {
  assertEquals(modPow(3, 5, 7), 5);
});

Deno.test("modPow with mod 1 always returns 0", () => {
  assertEquals(modPow(10, 5, 1), 0);
});

Deno.test("modPow with large exponent stays fast (no overflow)", () => {
  assertEquals(modPow(4, 13, 497), 445);
});
