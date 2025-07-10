#ifndef SENSOR
#define SENSOR

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;


class Sensor{
    public:
    string id;
    string type;
    string description;
    float frequency;

    virtual void simularLectura()= 0;
    virtual void mostrarDatos()= 0;

    virtual ~Sensor(){
        cout << "Destruyendo sensor " << this->type << endl;

    }
};

#endif