import { assertEquals } from "https://deno.land/std/assert/mod.ts";
import { gcd } from "./eucliedean.ts";

Deno.test("gcd of two positive numbers", () => {
  assertEquals(gcd(48, 18), 6);
});

Deno.test("gcd when one number is 0", () => {
  assertEquals(gcd(0, 5), 5);
});

Deno.test("gcd of equal numbers", () => {
  assertEquals(gcd(7, 7), 7);
});

Deno.test("gcd of coprime numbers", () => {
  assertEquals(gcd(17, 13), 1);
});

Deno.test("gcd with first number smaller than second", () => {
  assertEquals(gcd(4, 12), 4);
});

Deno.test("gcd of two zeros returns 0 (convention)", () => {
  assertEquals(gcd(0, 0), 0);
});

Deno.test("gcd with negative dividend can return negative (JS % sign quirk)", () => {
  assertEquals(gcd(48, -18), -6);
});
