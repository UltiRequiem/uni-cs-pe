#include <iostream>

using namespace std;

bool leapYear(int year) {
    return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
}

int howManyDaysIn(int mes, int year) {
    switch (mes) {
        case 1: return 31; 
        case 2: return leapYear(year) ? 29 : 28;
        case 3: return 31; 
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
}

void nextWeekDate(int day, int month, int year) {
    int daysLeft = howManyDaysIn(month, year) - day;
    
    if (daysLeft >= 7) {
        day += 7;
    } else {
        day = 7 - daysLeft;
        month++;

        if (month > 12) {
            month = 1;
            year++;
        }
    }

    cout << "La fecha una semana después es: " << day << " " << month << " " << year << endl;
}

int main() {
    int day, month, year;

    cout << "Ingrese una fecha (DD MM AAAA): ";
    cin >> day >> month >> year;

    nextWeekDate(day, month, year);

    return 0;
}

