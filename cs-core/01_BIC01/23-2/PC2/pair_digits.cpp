#include <iostream>

using namespace std;

int main(){
    int input = 0;

    cout << "Enter a positive integer: ";
    cin >> input;

    int evenCounter = 0;

    while (input > 0){
        int digit = input % 10;

        if (digit % 2 == 0){
            cout << digit << " found!" << endl;
            evenCounter++;
        }

        input /= 10;
    }

    cout << "In total: " << evenCounter << " even numbers were found." << endl;

    return 0;
}
