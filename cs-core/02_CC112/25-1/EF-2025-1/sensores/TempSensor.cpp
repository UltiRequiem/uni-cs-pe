#include "./Sensor.cpp"

class TempSensor: public Sensor{
    public:

    float temp;

    TempSensor(string id, float frequency, string description) {
        this->id = id;
        this->frequency= frequency;
        this->description = description;
        this->type = "Sensor de Temperatura";
    }

     void simularLectura (){
        //cout << "Leyendo datos desde el " << this->type << endl;
        this->temp = 22.8;
    }

    void mostrarDatos (){
        if (!this->temp || this->temp == 0){
            cout << "Aun no se han leido los datos!" << endl;
            return; 
        }

        cout << "[" << this->type <<  "] ID: " << this->id << " / Frecuencia: " << this->frequency <<"Hz / Lectura: " << this->temp << " C" << endl;
    }

};
