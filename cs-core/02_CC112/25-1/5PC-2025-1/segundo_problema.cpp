#include <iostream>
#include "rectangulo.cpp"

using std::cout;
using std::endl;

int main()
{
    Coordenada v1(1, 4), v2(1, 2), v3(4, 2), v4(4, 4);

    Rectangulo rectangulo(&v1, &v2, &v3, &v4);

    cout << "Rectangulo 1" << endl;
    cout << "Ancho: " << rectangulo.getAncho() << endl;
    cout << "Largo: " << rectangulo.getLargo() << endl;
    cout << "Area: " << rectangulo.getArea() << endl;
    cout << "Perimetro: " << rectangulo.getPerimetro() << endl;
    cout << "Es cuadrado: " << (rectangulo.esCuadrado() ? "Si" : "No") << endl;
    

    cout << endl;

    Coordenada vv1(1, 2), vv2(1, 1), vv3(2, 1), vv4(2, 2);

    Rectangulo rectangulo2(&vv1, &vv2, &vv3, &vv4);

    cout << "Rectangulo 2" << endl;
    cout << "Ancho: " << rectangulo2.getAncho() << endl;
    cout << "Largo: " << rectangulo2.getLargo() << endl;
    cout << "Area: " << rectangulo2.getArea() << endl;
    cout << "Perimetro: " << rectangulo2.getPerimetro() << endl;
    cout << "Es cuadrado: " << (rectangulo2.esCuadrado() ? "Si" : "No") << endl;

    return 0;
}