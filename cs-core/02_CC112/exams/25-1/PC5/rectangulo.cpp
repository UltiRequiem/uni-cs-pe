#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

using std::cout;
using std::endl;
using std::invalid_argument;
using std::pow;
using std::string;
using std::to_string;

class Coordenada
{
public:
    double x;
    double y;

    Coordenada() : x(0), y(0)
    {
        this->x = 0;
        this->y = 0;
    }

    Coordenada(double x, double y) : x(x), y(y)
    {
        this->x = x;
        this->y = y;
    }

    bool isFirstCuadrant() const
    {
        return  this->x > 0 &&  this->y > 0;
    }

    bool allMinorThan(int minorThan) const
    {
        return this->x < minorThan && this->y < minorThan;
    }
};

class Rectangulo
{
public:
    Rectangulo(Coordenada *v1, Coordenada *v2, Coordenada *v3, Coordenada *v4)
    {
        if (!v1->isFirstCuadrant() ||
            !v2->isFirstCuadrant() ||
            !v3->isFirstCuadrant() ||
            !v4->isFirstCuadrant())
        {
            throw invalid_argument("Las coordenadas deben estar en el primer cuadrante.");
        }

        if (!v1->allMinorThan(20) ||
            !v2->allMinorThan(20) ||
            !v3->allMinorThan(20) ||
            !v4->allMinorThan(20))
        {
            throw invalid_argument("Tanto la abscisa como la ordenada de cada coordenana ah de ser menor de 20.");
        }

        this->vertices[0] = v1;
        this->vertices[1] = v2;
        this->vertices[2] = v3;
        this->vertices[3] = v4;

        if (!isValid())
        {
            throw invalid_argument("Las coordenadas no forman un rectangulo valido.");
        }

        this->ancho = abs(v1->y - v2->y);
        this->largo = abs(v1->x - v4->x);
        this->area = ancho * largo;
        this->perimetro = 2 * (ancho + largo);
    }

    double getAncho() const
    {
        return ancho;
    }

    double getLargo() const
    {
        return largo;
    }

    double getArea() const
    {
        return area;
    }

    double getPerimetro() const
    {
        return perimetro;
    }

    bool esCuadrado() const
    {
        // Factor correccion al usar doubles, evitamos falsos negativos 
        // a comparacion de solo usar ancho == largo
        return std::abs(ancho - largo) < 1e-6;
    }

private:
    Coordenada *vertices[4];

    double ancho;
    double largo;
    double area;
    double perimetro;

    bool isValid() const
    {
        return (vertices[0]->x == vertices[1]->x && vertices[2]->x == vertices[3]->x) &&
               (vertices[0]->y == vertices[3]->y && vertices[1]->y == vertices[2]->y);
    }
};