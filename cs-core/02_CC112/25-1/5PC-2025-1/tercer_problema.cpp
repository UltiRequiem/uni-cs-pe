// Eliaz Sebastian Bobadilla Camarena 20244697E

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

using std::string;
using std::to_string;
using std::pow;
using std::cout;
using std::cin;
using std::endl;
using std::invalid_argument;

class Figura{
    private:
    // numero de lados
    int tipo;
    // arreglo dinamico con la longitud de los lados
    double* lados;
    
    public:
    Figura(int tipo){
        if (tipo != 3 && tipo != 4){
            throw invalid_argument("Este programa solo acepta figuras con 3 o 4 lados.");
        }

        this->tipo = tipo;
        this->lados = new double[tipo];
    }

    int checkType() const {
        return tipo;
    }

    int checkLado(int index) const {
        if (index < 0 || index >= tipo) {
            throw invalid_argument("Indice fuera de rango.");
        }

        return lados[index];
    }

    void setLado(int index, double value) {
        if (index < 0 || index >= tipo) {
            throw invalid_argument("Indice fuera de rango.");
        }

        lados[index] = value;
    }

        
};

int main(){
    int numeroDeFiguras;
    cout << "Ingrese el numero de rectangulos o triangulos: ";
    cin >> numeroDeFiguras;

    if (numeroDeFiguras <= 0){
        cout << "El numero de figuras debe ser postitivo." << endl;
        return 1;
    }

    cout << "Procedamos a armar " << numeroDeFiguras << " figuras." << endl;

    Figura* figuras[numeroDeFiguras];

    // Llenado de datos
    for (int i = 0; i < numeroDeFiguras; i++){
        cout << "Ingrese el numero de lados (3 o 4) de la figura " << i + 1 << ": ";
        int ladosDeFiguraActual;
        cin >> ladosDeFiguraActual;

        if (ladosDeFiguraActual != 3 && ladosDeFiguraActual !=4){
            cout << "Por el momento este programa solo acepta figuras con 3 o 4 lados." << endl;
            return 1;
        }

        if (ladosDeFiguraActual == 3){
            figuras[i] = new Figura(3);
          
            cout << "Ingrese las longitudes de los lados del triangulo: ";

            for (int j = 0; j < 3; j++){
                int value;
                cin >> value;
                figuras[i]->setLado(j, value);

                if (value <= 0){
                    cout << "Las longitudes de los lados deben ser positivas." << endl;
                    return 1;
                }
            }

             // Verificacion de la desigualdad triangular
            if (figuras[i]->checkLado(0) + figuras[i]->checkLado(1)  <= figuras[i]->checkLado(2) ||
                figuras[i]->checkLado(0)  + figuras[i]->checkLado(2) <= figuras[i]->checkLado(1)  ||
                figuras[i]->checkLado(1)  + figuras[i]->checkLado(2)  <= figuras[i]->checkLado(0) ) {
                cout << "Las longitudes ingresadas no forman un triángulo válido." << endl;
                return 1;
            }

        } else if (ladosDeFiguraActual == 4){
            figuras[i] = new Figura(4);

            cout << "Ingrese las longitudes a, b  del rectangulo: ";
            
            for (int j = 0; j < 2; j++){
                // Un rectangulo tiene dos lados iguales, por lo que solo se ingresan dos lados
                int value ;
                cin >> value;

                figuras[i]->setLado(j,value);
                figuras[i]->setLado(j + 2, value);

                
                if (figuras[i]->checkLado(j) <= 0){
                    cout << "Las longitudes de los lados deben ser positivas." << endl;
                    return 1;
                }
                
            }
        }
    }



    // Display de datos
    for (int i = 0; i < numeroDeFiguras; i++){
        auto currentFigura = figuras[i];
        if (currentFigura->checkType() == 3){
            cout << "Figura " << i + 1 << ": Triangulo con lados ";

            for (int j = 0; j < 3; j++){
                cout << currentFigura->checkLado(j) << " ";
            }
            
            cout << endl;

            cout << "El area del triangulo es: ";
            double s = (currentFigura->checkLado(0) + currentFigura->checkLado(1)  + currentFigura->checkLado(2) ) / 2.0; // Semiperimetro
            double area = sqrt(s * (s - currentFigura->checkLado(0)) * (s - currentFigura->checkLado(1) ) * (s - currentFigura->checkLado(2)));
            cout << area;

            cout << endl;
        } else if (currentFigura->checkType() == 4){
            cout << "Figura " << i + 1 << ": Rectangulo con lados ";
            for (int j = 0; j < 4; j++){
                cout << currentFigura->checkLado(j) << " ";
            }
            cout << endl;
            cout << "El area del rectangulo es: ";
            double area = currentFigura->checkLado(0)  * currentFigura->checkLado(1) ; // Area = a * b
            cout << area;
            cout << endl;
        }
    }

    return 0;
}