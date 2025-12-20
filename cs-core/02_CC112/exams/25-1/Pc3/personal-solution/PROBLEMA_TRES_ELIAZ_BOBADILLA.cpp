#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

struct TerminoPolinomio{
    float coeficiente;
    int exponente;
};



int main(){
    int firstPoliTerms;
    cout <<  "Ingrese el numero de terminos del primer polinomio: ";
    cin >> firstPoliTerms;
    cout << endl;

    auto *firstPoli = new TerminoPolinomio[firstPoliTerms];

    for (int j = 0; j < firstPoliTerms;j++){
        TerminoPolinomio politerm;

        cout << "Ingrese el coeficiente del termino " << j << ": ";
        cin >> politerm.coeficiente;

        cout << "Ingrese el exponente del termino " << j << ": ";
        cin >> politerm.exponente;

        firstPoli[j] = politerm;
    }

    int secondPoliTerms;
    cout <<  "Ingrese el numero de terminos del segundo polinomio: ";
    cin >> secondPoliTerms;
    cout << endl;

    auto *secondPoli = new TerminoPolinomio[secondPoliTerms];

    for (int j = 0; j < secondPoliTerms;j++){
        TerminoPolinomio politerm;

        cout << "Ingrese el coeficiente del termino " << j << ": ";
        cin >> politerm.coeficiente;

        cout << "Ingrese el exponente del termino " << j << ": ";
        cin >> politerm.exponente;

        secondPoli[j] = politerm;
    }

    cout << "Primer polinomio: ";

    for (int j = 0; j < firstPoliTerms;j++){
        auto currentTerm = firstPoli[j];

        if (currentTerm.coeficiente == 0){
            continue;
        }

        cout << currentTerm.coeficiente << "x*" << currentTerm.exponente;
        if (j < firstPoliTerms -1){
            cout << "+";
        }

    }

    cout << endl;

    cout << "Segundo polinomio: ";

    for (int j = 0; j < secondPoliTerms;j++){
        auto currentTerm = secondPoli[j];

        if (currentTerm.coeficiente == 0){
            continue;
        }

        cout << currentTerm.coeficiente << "x*" << currentTerm.exponente;
        if (j < firstPoliTerms -1){
            cout << "+";
        }

    }

    // FALTA SUMAR Y MULTIPLICAR

    cout << endl;

    return 0;
}