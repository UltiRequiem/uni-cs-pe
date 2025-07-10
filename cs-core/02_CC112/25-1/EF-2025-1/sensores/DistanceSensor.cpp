#include "./Sensor.cpp"

class DistanceSensor: public Sensor{
    public:

    float distance;

    DistanceSensor(string id, float frequency, string description) {
        this->id = id;
        this->frequency= frequency;
        this->description = description;
        this->type = "Sensor de Distancia";
    }

     void simularLectura (){
       // cout << "Leyendo datos desde el " << this->type << endl;
        this->distance = 5.34;
    }

    void mostrarDatos (){
        if (!this->distance || this->distance == 0){
            cout << "Aun no se han leido los datos!" << endl;
            return; 
        }

        cout << "[" << this->type <<  "] ID: " << this->id << " / Frecuencia: " << this->frequency <<"Hz / Lectura: " << this->distance << "m (ruido: +-0.25m)" << endl;
    }

};