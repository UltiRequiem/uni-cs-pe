#include <iostream>

using namespace std;

float* crearArreglo(int n){
    float *respuestas = new float[n];

    return respuestas;
}

void leerRespuestas(float *arr, int n){
    int counter = 0;

    while(counter < n){
        float input;
        cout << "Ingrese la respuesta " << counter +1 << " : ";
        cin >> input;

        if (input > 5){
            cout << "Respuesta no valida!!" << endl;
            continue;
        }
        if (input < 1){
            cout << "Respuesta no valida!!" << endl;
            continue;
        }

        arr[counter] = input;
        counter++;
    }
    cout << endl;
}

int obtenerCantidad(){
    int cantidad;
    cout << "Ingrese la cantidad de respuestas: ";
    cin >> cantidad;    
    cout << endl;

    return cantidad;
}

float calcularPromedio(float* arr,int n){
    float totalSum = 0;

    for (int j = 0; j < n; j++){
        totalSum += arr[j];
    }

    float average = totalSum / n;

    return average;
}

void imprimirPromedio(float* arr, int n){
    auto promedio = calcularPromedio(arr, n);
    cout << "Promedio de satisfaccion: " << promedio << endl;
}

void mostrarFrecuencias(float* arr, int n){
    int total1 = 0;
    int total2 = 0;
    int total3 = 0;
    int total4 = 0;
    int total5 = 0;

    for (int j = 0; j < n ; j++){
        // Esto estaria mucho mejor con un hashmap
        auto current = arr[j];

        if (current == 1) total1++;
        if (current == 2) total2++;
        if (current == 3) total3++;
        if (current == 4) total4++;
        if (current == 5) total5++;
    }

    cout << "Frecuencia de respuestas: " << endl;
    cout << "1: " << total1 << endl;
    cout << "2: " << total2 << endl;
    cout << "3: " << total3 << endl;
    cout << "4: " << total4 << endl;
    cout << "5: " << total5 << endl;
}

int calcularModa(float* arr, int n){
    int total1 = 0;
    int total2 = 0;
    int total3 = 0;
    int total4 = 0;
    int total5 = 0;

    for (int j = 0; j < n ; j++){
        auto current = arr[j];

        if (current == 1) total1++;
        if (current == 2) total2++;
        if (current == 3) total3++;
        if (current == 4) total4++;
        if (current == 5) total5++;
    }

    int *frecuencias = new int[5];

    frecuencias[0] = total1;
    frecuencias[1] = total2;
    frecuencias[2] = total3;
    frecuencias[3] = total4;
    frecuencias[4] = total5;

    int winner = -1;

    for (int y = 0; y < 5;y++){
        auto current = frecuencias[y];
        if (current>winner){
            winner = current;
        }
    }

    // En casos con misma frecuencia se preferira este orden.
    if (winner == total1){
        return 1;
    } else if (winner == total2){
        return 2;
    }else if (winner == total3){
        return 3;
    }else if (winner == total4){
        return 4;
    }else if (winner == total5){
        return 5;
    }

    // NO ENCONTRO LA MODA
    return -1;
}

void imprimirModa(float* arr, int n){
    auto moda = calcularModa(arr, n);
    cout << "Moda: " << moda << endl;
}

void destruirArreglo(float*& arr){
    delete[] arr;
}

int main(){
    auto cantidad = obtenerCantidad();
    auto respuestas = crearArreglo(cantidad);
    
    leerRespuestas(respuestas, cantidad);
    imprimirPromedio(respuestas, cantidad);
    mostrarFrecuencias(respuestas, cantidad);
    imprimirModa(respuestas, cantidad);
    destruirArreglo(respuestas);

    return 0;
}