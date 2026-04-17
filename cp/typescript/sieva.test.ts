import { describe, expect, test } from "bun:test";
import { sieva } from "./sieva";

describe("sieva", () => {
	test("handles small targets", () => {
		expect(sieva(0)).toEqual([]);
		expect(sieva(1)).toEqual([false]);
		expect(sieva(2)).toEqual([false, false]);
	});

	test("marks primes below 10", () => {
		expect(sieva(10)).toEqual([
			false,
			false,
			true,
			true,
			false,
			true,
			false,
			true,
			false,
			false,
		]);
	});

	test("marks composites correctly for a larger range", () => {
		const primes = sieva(20);

		expect(primes[11]).toBe(true);
		expect(primes[12]).toBe(false);
		expect(primes[17]).toBe(true);
		expect(primes[18]).toBe(false);
	});
});
