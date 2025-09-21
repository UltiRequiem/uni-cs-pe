#include <string>
#include <iostream>

#include "./Sensor.cpp"
#include "./DistanceSensor.cpp"
#include "./TempSensor.cpp"
#include "./MovementSensor.cpp"


/* Como se moledaria un dro que utilice los tres sensores implementados?
Al ser solo 3 podriamos usarlos como propiedades consicsas de la clase/structura.
En caso fueran mas sensores podriamos hacer uso d un Hasmap o un array (utilizando un patron estratgia por cada sensor)
para uso mas sencillo.
*/

int main(){
    Sensor* temp =  new TempSensor("T-001", 1.0, "Su lectura base se ajusta con una pequenia fluctuacion aleatoria.");
    Sensor* dist =  new DistanceSensor("T-102", 0.5, "Simula una medicion con ruido proporcional al cuadrado de la distancia.");
    Sensor* move =  new MovementSensor("M-500", 2, "SUn vector de 3 valores represntando aceleraciones en x,y,z.");

    
    temp->simularLectura();
    temp->mostrarDatos();

    dist->simularLectura();
    dist->mostrarDatos();

    move->simularLectura();
    move->mostrarDatos();

    delete dist;
    delete move;
    delete temp;

    return 0;
}