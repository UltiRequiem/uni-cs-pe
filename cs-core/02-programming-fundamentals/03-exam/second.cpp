#include <iostream>
using std::cout, std::endl;

// o(n^2)
int firstUniqueNumber(int numbers[], int size){
    for (int i = 0; i < size; i++){
        bool isUnique = true;
        int currentNumber = numbers[i];
        
        for (int j = 0; j < size; j++){
            int iterationNumber = numbers[j];

            // diferentes indices, mismos valores
            if (i != j && currentNumber == iterationNumber){
                isUnique = false;
                break;
            }
        }

        if (isUnique){
            return currentNumber;
            
        }
    }

    // si no encontro nada
    return -1;
}

int main(){
    int numbers[] = {4,5,1,2,1,4,2};
    int size = sizeof(numbers) / sizeof(numbers[0]);

    int numbers2[] = {4,5,1,2,1,4,2,5};
    int size2 = sizeof(numbers2) / sizeof(numbers2[0]);

    cout << "Primer resultado: " << firstUniqueNumber(numbers, size) << endl;
    cout << "Segundo resultado: " << firstUniqueNumber(numbers2, size2) << endl; 

    return 0;
}