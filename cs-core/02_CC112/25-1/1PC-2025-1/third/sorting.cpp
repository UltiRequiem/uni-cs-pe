#include <iostream>
using namespace std;

void QuickSort(int numbers[], int n)
{
    if (n <= 1)
        return;

    int pivot = numbers[n / 2]; // pivote arbitrario
    int i = 0, j = n - 1;

    while (i <= j)
    {
        while (numbers[i] < pivot)
            i++;
        while (numbers[j] > pivot)
            j--;
        if (i <= j)
        {
            // intercambiamos las posiciones
            int savedValue = numbers[i];
            numbers[i] = numbers[j];
            numbers[j] = savedValue;
            i++;
            j--;
        }
    }

    QuickSort(numbers, j + 1);      
    QuickSort(numbers + i, n - i);  
    
    int uniqueIndex = 0;
    
    for (int k = 1; k < n; k++)
    {
        if (numbers[k] != numbers[uniqueIndex])
        {
            uniqueIndex++;
            numbers[uniqueIndex] = numbers[k];
        }
    }
    
    n = uniqueIndex + 1;
}

void Merge(int vect1[], // vector de entrada #1, ordenado de forma ascendente
           int tam1,
           int vect2[], // vector de entrada #2, ordenado de forma ascendente
           int tam2,
           int resultado[], // vector de salida, ordenado de forma ascendente
           int &tamresultado)
{
    int i = 0, j = 0, k = 0;

    while (i < tam1 && j < tam2)
    {
        if (vect1[i] < vect2[j])
        {
            if (k == 0 || resultado[k - 1] != vect1[i]) // Evitar duplicados
                resultado[k++] = vect1[i];
            i++;
        }
        else
        {
            if (k == 0 || resultado[k - 1] != vect2[j]) // Evitar duplicados
                resultado[k++] = vect2[j];
            j++;
        }
    }

    while (i < tam1)
    {
        if (k == 0 || resultado[k - 1] != vect1[i]) // Evitar duplicados
            resultado[k++] = vect1[i];
        i++;
    }

    while (j < tam2)
    {
        if (k == 0 || resultado[k - 1] != vect2[j]) // Evitar duplicados
            resultado[k++] = vect2[j];
        j++;
    }

    tamresultado = k;
}
