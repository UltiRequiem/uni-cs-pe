#include <iostream>
using namespace std;

bool canDivide(int A[], int size, int n, int maxDistance) {
    int currentSum = 0;
    int groups = 1;

    for (int i = 0; i < size; i++) {
        if (currentSum + A[i] > maxDistance) {
            groups++;
            currentSum = A[i];
            if (groups > n) {
                return false; 
            }
        } else {
            currentSum += A[i];
        }
    }

    return true;
}

int busquedaBinaria(int A[], int size, int n) {
    int left = A[0]; 
    int right = 0;   

    for (int i = 0; i < size; i++) {
        if (A[i] > left) left = A[i]; 
        right += A[i];                
    }

    int result = right;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (canDivide(A, size, n, mid)) {
            result = mid; 
            right = mid - 1;
        } else {
            left = mid + 1; 
        }
    }

    return result;
}

void formGroups(int A[], int size, int n, int maxDistance) {
    int currentSum = 0;
    int groups = 1;

    cout << "Los grupos formados son:" << endl;
    for (int i = 0; i < size; i++) {
        if (currentSum + A[i] > maxDistance) {
            cout << "]" << endl; 
            groups++;
            currentSum = A[i];
            cout << "[" << A[i]; 
        } else {
            if (currentSum == 0) {
                cout << "[" << A[i];
            } else {
                cout << ", " << A[i];
            }
            currentSum += A[i];
        }
    }
    cout << "]" << endl; 
}

int main() {
    int n = 2; 
    int A[] = {7, 2, 5, 10, 8};
    int size = sizeof(A) / sizeof(A[0]);

    int maxDistance = busquedaBinaria(A, size, n);

    cout << "La mínima distancia máxima es: " << maxDistance << endl;

    formGroups(A, size, n, maxDistance);

    return 0;
}