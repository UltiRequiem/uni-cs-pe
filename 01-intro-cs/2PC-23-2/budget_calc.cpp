#include <iostream>

using namespace std;

int main(){
    int basePrice, adults, kids, kidPrice, adultPrice = 0;
    string day;

    cout << "Enter the original price: ";
    cin >> basePrice;

    cout << "How many adults are going? ";
    cin >> adults;

    cout << "How many kids are going? ";
    cin >> kids;

    cout << "Which day of the week are they going? ";
    cin >> day;

    if (day == "Saturday" || day == "Sunday"){
        adultPrice = basePrice * (1 - 0.3);
        kidPrice = basePrice * (1 - 0.5);
    } else if (day == "Monday" || day == "Wednesday"){
        adultPrice = basePrice * (1 - 0.2);
        kidPrice = basePrice * ( 1 - 0.6);
    } else if (day == "Tuesday" || day == "Thursday"){
        adultPrice = basePrice * (1 - 0.1);
        kidPrice = basePrice * (1 - 0.7);
    } else if (day == "Friday"){
        kidPrice = basePrice * (1 - 0.7);
    }

    int kidsCost = kidPrice * kids;
    int adultCost = adultPrice * adults;
    int totalCost = kidsCost + adultCost;

    cout << endl;

    cout << "Kid's budget: " << kidsCost << endl;
    cout << "Adult's budget: " << adultCost << endl;

    cout << "Total needed budget: " << totalCost << endl;
}