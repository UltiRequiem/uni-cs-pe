// Eliaz bobadilla, 20244697E

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>

using namespace std;

int main(){
    srand (time(NULL));
    
    int highestTemperature;
    int minTemperature;
    int totalTemp = 0;

    
    for (int day = 1; day < 31; day++){
        int todayTemperature = rand() % 35 + 1 - 10;
        cout << "Día " << day << ": " << todayTemperature << "°C" << endl;
        
        if (todayTemperature > highestTemperature){
            highestTemperature = todayTemperature;
        }
        
        if (todayTemperature < minTemperature){
            minTemperature = todayTemperature;
        }
        totalTemp += todayTemperature;
        
        }
    
    cout << endl << "Resumen del mes: " << endl << endl;
    
    cout << "Temperatura máxima: " << highestTemperature << "°C" << endl;
    
    cout << "Temperatura minima: " << minTemperature << "°C" << endl;
    
    cout << "Temperatura promedio: " << totalTemp / 30 << endl;

    return 0;
}
