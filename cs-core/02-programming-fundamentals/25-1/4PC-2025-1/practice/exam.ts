/**
  Considere formar un arreglo dinámico con valores enteros positivos ingresados por el
usuario, de manera que solo se inserte valores no repetidos. Cada valor positivo x es insertado al
final del arreglo si x es mayor que el máximo de los valores ya almacenados, de lo contrario es
insertado al inicio de arreglo. No suponga una longitud constante para el arreglo, sino que debe
variar en cada inserción de nuevos valores. Finalmente imprima el arreglo formado y el valor de
máximo.
  */

function main() {
	const input = [2, 3, 3, 4, 1, 5, 4, 2, 1, 3, 0];

	const result: number[] = [];

	const memory = {};

	for (let i = 0; i < input.length; i++) {
		const current = input[i];

		if (memory[current] || current <= 0) {
			continue;
		}

		const last = result[result.length - 1];

		if (current > last) {
			result.push(current);
		} else {
			result.unshift(current);
		}

		memory[input[i]] = true;
	}

	console.log("Arreglo formado:", result);
	console.log(result[result.length - 1]);
}

main();
