// Eliaz Sebastian Bobadilla Camarena 20244697E

#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

using std::string;
using std::to_string;
using std::pow;
using std::cout;
using std::endl;
using std::invalid_argument;

class Figura3D{
    public:
    virtual double volumen() const = 0;
    virtual string descripcion() const = 0;
};

class Cubo: public Figura3D{
    public:
    double lado;
 
    Cubo(double lado) {
        if (lado <= 0){
            throw invalid_argument("Este programa solo acepta dimensiones positivas.");
        }

        this->lado = lado;
    }

    string descripcion() const override {
        return "Cubo con lado " + to_string(lado) + ".";
    }

    double volumen() const override {
        return pow(lado, 3);
    }
};

class Esfera: public Figura3D{
    public:
    double radio;
    Esfera(double radio) {
        if (radio <= 0){
            throw invalid_argument("Este programa solo acepta dimensiones positivas.");
        }

        this->radio = radio;
    }

    string descripcion() const override {
        return "Esfera con radio " + to_string(radio)+ ".";
    }

    double volumen() const override {
        return (4.0 / 3.0) * M_PI * pow(radio, 3);
    }
};

class Cilindro: public Figura3D{
    public:
    double radio;
    double altura;

    Cilindro(double radio, double altura){
        if (radio <=0 || altura <=0){
            throw invalid_argument("Este programa solo acepta dimensiones positivas.");
        }

        this->radio = radio;
        this->altura = altura;
    }

    string descripcion() const override {
        return "Cilindro con radio " + to_string(radio) + " y altura " + to_string(altura);
    }

    double volumen() const override {
        return M_PI * pow(radio, 2) * altura;
    }
};

class PiramidaCuadrada: public Figura3D{
    public:
    double base;
    double altura;
    
    PiramidaCuadrada(double base, double altura){
        if (base <=0 || altura <=0){
            throw invalid_argument("Este programa solo acepta dimensiones positivas.");
        }

        this->base = base;
        this->altura = altura;
    }

    string descripcion() const override {
        return "Piramide Cuadrada con base " + to_string(base) + " y altura " + to_string(altura);
    }

    double volumen() const override {
        return (1.0 / 3.0) * pow(base, 2) * altura;
    }
};

int main(){
    // Casos de prueba del papel

    Figura3D* cubo1 = new Cubo(4);
    cout << cubo1->descripcion() << " -> " << "Volumen: " << cubo1->volumen() << endl;

    Figura3D* esfera1 = new Esfera(3);
    cout << esfera1->descripcion() << " -> " << "Volumen: " << esfera1->volumen() << endl;

    Figura3D* clindro1 = new Cilindro(2,5);
    cout << clindro1->descripcion() << " -> " << "Volumen: " << clindro1->volumen() << endl;

    Figura3D* piramide1 = new PiramidaCuadrada(6,10);
    cout << piramide1->descripcion() << " -> " << "Volumen: " << piramide1->volumen() << endl;

    Figura3D* esfera2 = new Esfera(1.5);
    cout << esfera2->descripcion() << " -> " << "Volumen: " << esfera2->volumen() << endl;

    Figura3D* cubo2 = new Cubo(2);
    cout << cubo2->descripcion() << " -> " << "Volumen: " << cubo2->volumen() << endl;

    return 0;
}