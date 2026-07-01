/**

* Si b es PAR:
 *
 *      a^b = (a^(b/2))²
 *  * Si b es IMPAR:
 *
 *      a^b = a · (a^((b-1)/2))²
 */

export function power(base: number, exponente: number): number {
    // Acumula el resultado final.
    let resultado = 1;

    // Mientras aún queden bits del exponente por procesar.
    while (exponente > 0) {

        // Si el exponente es impar,
        // significa que existe un factor "base"
        // que debe formar parte de la respuesta.
        if (exponente % 2 === 1) {
            resultado *= base;
        }

        // Aplicamos:
        //
        // (a²)^(b/2) = a^b
        //
        // para la siguiente iteración.
        base *= base;

        // Eliminamos el bit menos significativo
        // dividiendo el exponente entre 2.
        exponente = Math.floor(exponente / 2);
    }

    return resultado;
}

/**
 * Calcula (base^exp) mod mod usando exponenciación rápida.
 *
 * Complejidad:
 * - Tiempo: O(log exp)
 * - Espacio: O(1)
 */
export function modPow(base: number, exp: number, mod: number): number {
  if (mod === 1) return 0;

  // Aseguramos que la base esté dentro del rango [0, mod-1]
  base %= mod;

  // Elemento neutro de la multiplicación.
  let resultado = 1;

  while (exp > 0) {
    // Si el bit menos significativo del exponente es 1,
    // incorporamos la base actual al resultado.
    if (exp % 2 === 1) {
      resultado = (resultado * base) % mod;
    }

    // La siguiente base representa:
    // (base²) mod mod
    base = (base * base) % mod;

    // Eliminamos el bit menos significativo del exponente.
    exp = Math.floor(exp / 2);
  }

  return resultado;
}
