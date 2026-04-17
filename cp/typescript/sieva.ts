export function sieva(target: number) {
	const primes = new Array(target).fill(true);

	if (target > 0) primes[0] = false;
	if (target > 1) primes[1] = false;

	for (let i = 4; i < target; i += 2) primes[i] = false;

	for (let i = 3; i * i < target; i += 2) {
		if (!primes[i]) continue;

		for (let j = i * i; j < target; j += 2 * i) {
			primes[j] = false;
		}
	}

	return primes;
}
