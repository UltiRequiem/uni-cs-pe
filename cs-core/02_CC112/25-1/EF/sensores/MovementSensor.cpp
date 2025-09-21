#include "./Sensor.cpp"

class MovementSensor: public Sensor{
    public:

    float x;
    float y;
    float z;

    MovementSensor(string id, float frequency, string description) {
        this->id = id;
        this->frequency= frequency;
        this->description = description;
        this->type = "Sensor de Distancia";
    }

     void simularLectura (){
       // cout << "Leyendo datos desde el " << this->type << endl;
        this->x = 0.12;
        this->y = 0.02;
        this->z = 0.0;
    }

    void mostrarDatos (){
        if (!this->x || !this->y || !this->z){
            cout << "Aun no se han leido los datos!" << endl;
            return; 
        }

        cout << "[" << this->type <<  "] ID: " << this->id <<
         " / Frecuencia: " << this->frequency <<"Hz / Aceleracion (x,y,z): " << 
         this->x << "m/s^2" <<  
         this->y << "m/s^2"  <<  
         this->z << "m/s^2" <<endl;
    }

};