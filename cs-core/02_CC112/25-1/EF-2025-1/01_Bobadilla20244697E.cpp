// Eliaz Sebastian Bobadilla Camarena
// 20244697E

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

// Matrix> NxM
class Matrix {
    public:
    int n;
    int m;
    int** rows;

    Matrix(int m, int n){
        this->m = m;
        this->n = n;

        this->rows = new int*[n];
        
        for (int e = 0; e < n; e++){
            this->rows[e] = new int[m];
        }
    }

    void fillMatrix(int* numbers){
        int l = 0;

        for (int e = 0; e < n; e++){
            for (int k = 0; k < m; k++){
                this->rows[e][k] = numbers[l];
                l++;
            }
        }
    }

    void dislpayMatrix(){
        cout << " --------- " << endl;

        for (int e = 0; e < n; e++){
            for (int k = 0; k < m; k++){
                cout << " " << this->rows[e][k];
            }

         //   if (e == n -1) continue; // skip double print
            cout << endl;
        }

        cout << " --------- " << endl;

    }

    // Algoritmo para la eliminacion de gauss
    void gaussElimination(){
        //Itero mis filas
        for (int e = 0; e < n; e++){
            // Itero los elementos de mi fila
            for (int k = 0; k < m; k++){
                int pivot = this->rows[e][k];

                if (pivot == 0){
                    // No puedo hacer operaciones con esto.
                    continue;
                }

                if (this->columnHasZeros(k)) continue;

                // Sabemos que M[e][k] es no nulo, aprovechemos
                // para eliminar todos los elementos debajo de el
                // osea los M[i][k], tal que n >= i >k

                for (int u = e + 1; u <n; u++){
                    int factor = this->rows[u][k] / pivot;

                    for (int g = 0;g < m; g++){
                        int eliminator = this->rows[e][g];


                        this->rows[u][g] = this->rows[u][g] -eliminator*factor;
                    }

                }

            }

            cout << endl;
        }
    }

    void displayRange(){
        cout << "El rango de la matriz: " << this->getRange() << endl;
    }

    ~Matrix(){
        for (int e = 0; e < n; e++){
            delete this->rows[e];
        }

        delete this->rows;

        cout << "Hasta luego!" << endl;
    }

    private:

    bool columnHasZeros(int j){

        for (int i = 0; i < n; i++){
            if (this->rows[i][j] == 0) return true;
        }

        return false;
    }

    int getRange(){
        int rang = 0;

        for (int e = 0; e < n; e++){
            bool differentThanZero = false;

            for (int k = 0; k < m; k++){
                if (differentThanZero) break;
                int current = this->rows[e][k];

                if (current !=0) differentThanZero = true;
            }

            if (differentThanZero) rang++;
        }

        return rang;

    }


};

int main(){
    int m;
    int n;

    cout << "Ingrese el numero de filas y columnas: ";
    cin >> m;
    cin >> n;

    cout << "Ingrese la matrix: " << endl;
    int *numbers = new int[m*n];

    for (int p = 0; p < m*n;p++){
        cin >> numbers[p];
    }

    Matrix myMatrix(n,m);
    myMatrix.fillMatrix(numbers);
    cout << endl << "Matriz original: "  << endl;

    myMatrix.dislpayMatrix();


    cout << endl << "Matriz en forma escalonada: " ;

    myMatrix.gaussElimination();
    
    myMatrix.dislpayMatrix();
    cout << endl;
    myMatrix.displayRange();


    return 0;
}