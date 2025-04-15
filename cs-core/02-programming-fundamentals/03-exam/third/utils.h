#ifndef UTILS_H

#define UTILS_H
void QuickSort(int pArray[], int n);

void Merge(int vect1[], int tam1, // vector de entrada #1, ordenado de forma ascendente
    int vect2[], int tam2, // vector de entrada #2, ordenado de forma ascendente
    int resultado[], int &tamresultado // vector de salida, ordenado de forma ascendente
    );
    
void PrintArray(int pArray[], int n);

#endif