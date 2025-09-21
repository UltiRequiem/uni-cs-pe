#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* merge(int* left, int leftSize, int* right, int rightSize) {
    int* result = (int*)malloc((leftSize + rightSize) * sizeof(int));

    int leftIndex = 0;
    int rightIndex = 0;
    int resultIndex = 0;

    while (leftIndex < leftSize && rightIndex < rightSize) {
        int currentLeft = left[leftIndex];
        int currentRight = right[rightIndex];

        if (currentLeft <= currentRight) {
            result[resultIndex++] = currentLeft;
            leftIndex++;
            continue;
        }

        result[resultIndex++] = currentRight;
        rightIndex++;
    }

    while (leftIndex < leftSize) {
        result[resultIndex++] = left[leftIndex++];
    }

    while (rightIndex < rightSize) {
        result[resultIndex++] = right[rightIndex++];
    }

    return result;
}


int* mergeSort(int* nums, int size) {
    if (size <= 1) {
        int* result = (int*)malloc(size * sizeof(int));
        
        int i;
        
        for (i = 0; i < size; i++) {
            result[i] = nums[i];
        }

        return result;
    }

    int pivot = floor(size / 2);

    int* left = (int*)malloc(pivot * sizeof(int));
    int* right = (int*)malloc((size - pivot) * sizeof(int));

    int i;

    for (i = 0; i < pivot; i++) {
        left[i] = nums[i];
    }

    for (i = pivot; i < size; i++) {
        right[i - pivot] = nums[i];
    }

    int* sortedLeft = mergeSort(left, pivot);
    int* sortedRight = mergeSort(right, size - pivot);

    free(left);
    free(right);

    int* result = merge(sortedLeft, pivot, sortedRight, size - pivot);

    free(sortedLeft);
    free(sortedRight);

    return result;
}

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    int* sorted = mergeSort(arr, size);

    printf("Sorted array: ");
    int i;

    for (i = 0; i < size; i++) {
        printf("%d ", sorted[i]);
    }
    
    printf("\n");

    free(sorted);

    return 0;
}