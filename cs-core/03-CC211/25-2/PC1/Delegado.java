import java.util.Random;

class Estudiante {
	public static int numEstudiantes;
	public static String delegado;
	public static String subDelegado;

	public int codigo;
	public String nombre;
	public int tel;

	Estudiante(int codigo, String nombre, int tel) {
		this.codigo = codigo;
		this.nombre = nombre;
		this.tel = tel;

		// Incrementar el contador de estudiantes (estado estatico)
		numEstudiantes++;
	}
}

public class Delegado {

	private static void displayVotes(int[] votos) {
		System.out.print("  Votos         :");

		for (int voto : votos) {
			System.out.printf("%6d", voto);
		}

		System.out.println();
	}

	private static void displayCandidates(int[] candidatos, Estudiante[] estudiantes) {
		System.out.print("  Candidatos:");

		for (int c : candidatos) {
			System.out.printf("%6s", estudiantes[c].nombre);

		}

		System.out.println();
	}

	public static void main(String[] args) {
		Random ran = new Random();

		int numEst = 21 + ran.nextInt(10); // De 21 a 30 estudiantes

		Estudiante[] estudiantes = new Estudiante[numEst];

		int i;
		System.out.println("código nombre teléfono");

		for (i = 0; i < numEst; i++) {
			String nombre = "A" + i;
			int telefono = 10 + i;
			estudiantes[i] = new Estudiante(i, nombre, telefono);
			System.out.printf("%6d %8s %4d\n", i, nombre, telefono);
		}

		int numCan = 2 + ran.nextInt(4); // De 2 a 5 candidatos
		int[] candidatos = new int[numCan];

		int can = 0;
		int codigo = 0;
		boolean duplicado = false;

		while (can < numCan) {
			for (i = 0; i < numEst; i++) {
				if (ran.nextInt(10) > 7) { // 20% de estudiantes propone un candidato
					codigo = ran.nextInt(numEst); // codigo de estudiante propuesto
					duplicado = false; // se verifica si candidato propuesto se duplica
					for (int j = 0; j < can; j++)
						if (candidatos[j] == codigo) {
							duplicado = true;
							break;
						}

					if (!duplicado) {
						candidatos[can++] = codigo; // se acepta candidato
					}
				}

				if (can == numCan) {
					break; // se alcanzó el número de candidatos
				}

			}
		}

		displayCandidates(candidatos, estudiantes);

		int[] votos = new int[numCan];

		for (i = 0; i < numEst; i++) {
			int candidatoElegido = ran.nextInt(numCan);
			votos[candidatoElegido]++;
		}

		displayVotes(votos);

		int[] votosOrdenados = votos.clone();
		int[] candidatosOrdenados = candidatos.clone();

		// Ordenamiento descendente por burbuja manteniendo sincronia
		for (i = 0; i < numCan - 1; i++) {
			for (int j = 0; j < numCan - 1 - i; j++) {
				if (votosOrdenados[j] < votosOrdenados[j + 1]) {
					// Intercambiar votos
					int tempVoto = votosOrdenados[j];
					votosOrdenados[j] = votosOrdenados[j + 1];
					votosOrdenados[j + 1] = tempVoto;

					// Intercambiar candidatos correspondientes
					int tempCandidato = candidatosOrdenados[j];
					candidatosOrdenados[j] = candidatosOrdenados[j + 1];
					candidatosOrdenados[j + 1] = tempCandidato;
				}
			}
		}

		// Seleccionar delegado tomando en cuenta: votos por candidato; en caso de
		// empate se sortea
		String delegadoNombre = estudiantes[candidatosOrdenados[0]].nombre;
		boolean empate = false;

		// Verificar si hay empate en el primer lugar
		for (i = 1; i < numCan; i++) {
			if (votosOrdenados[i] == votosOrdenados[0]) {
				empate = true;
				break;
			}
		}

		if (empate) {
			System.out.println("   El Delegado       es: " + delegadoNombre + ": por sorteo");
		} else {
			System.out.println("   El Delegado       es: " + delegadoNombre);
		}

		// Seleccionar subdelegado tomando en cuenta: votos por candidato
		if (numCan > 1) {
			String subdelegadoNombre = estudiantes[candidatosOrdenados[1]].nombre;
			System.out.println("   El Subdelegado es: " + subdelegadoNombre);
		}
	}
}
