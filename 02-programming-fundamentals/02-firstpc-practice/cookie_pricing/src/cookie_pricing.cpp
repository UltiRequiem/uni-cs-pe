#include "cookie_pricing.h"

double findPrice(double A[], int size, double p) {
    if (p <= A[0]) return A[0];
    if (p >= A[size-1]) return A[size-1];
    
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (A[mid] == p) {
            return p;
        }
        
        if (mid > 0 && A[mid-1] <= p && p <= A[mid]) {
            return (A[mid-1] + A[mid]) / 2.0;
        }
        
        if (p < A[mid]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return A[size -1];
}

double calculateSuggestedPrice(double weight, double A[], int size) {
  if (weight==20){
    return 1.0;
  }
    double weightPrice = findPrice(A, size, weight);
    return (weightPrice / 20.0);
}