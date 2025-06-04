function recursiveFibo(n, memo = {}) {
	if (n < 3) return 1;
	if (n in memo) return memo[n];

	return (memo[n] = recursiveFibo(n - 1, memo) + recursiveFibo(n - 2, memo));
}

console.time("recursiveFibo");
console.log(recursiveFibo(700));
console.timeEnd("recursiveFibo");
console.log(calls);
