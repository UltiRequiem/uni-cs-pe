#include <iostream>
#include <string>

using std::cout;
using std::cout;
using std::cin;
using std::endl;
using std::string;

class Point {
    public:
    int x, y;
};

class Conjunto {
    public:
    Point *points;
    int size;

    Conjunto() { 
        this->points = nullptr;
        this->size = 0;
    }

    void addPoint(int x, int y) {
        Point *newPoints = new Point[size + 1];

        if (this->points == nullptr) {
            this->points = newPoints;
            
            newPoints[0].x = x;
            newPoints[0].y = y;
            
            size = 1;
            return;
        }

        for (int i = 0; i < size; i++) {
            newPoints[i] = points[i];
        }
        
        newPoints[size].x = x;
        newPoints[size].y = y;
        
        delete[] this->points;
        
        this->points = newPoints;
        
        size++;
    }

    int getSize() const {
        return size;
    }

    void displayar(){
        cout << "Puntos del conjunto:" << endl;
        
        for (int i = 0; i < this->getSize(); i++) {
            cout << "(" << this->points[i].x << ", " << this->points[i].y << ") ";
        }
        
        cout << endl;
    }


    ~Conjunto() {
        delete[] points;
    }



};

Conjunto unionDeConjunto(Conjunto &c1, Conjunto &c2) {
    Conjunto result;

    for (int i = 0; i < c1.getSize(); i++) {
        result.addPoint(c1.points[i].x, c1.points[i].y);
    }

    for (int i = 0; i < c2.getSize(); i++) {
        bool found = false;
        Point current = c2.points[i];

        for (int j = 0; j < result.getSize(); j++) {
            Point comparingTo = result.points[j];

            if (current.x == comparingTo.x && current.y == comparingTo.y) {
                found = true;

                break;
            }
        }

        if (!found) {
            result.addPoint(current.x, current.y);
        }
    }

    return result;
}

Conjunto leerConjunto(string name) {
    cout << "Conjunto " << name << "." << endl;

    int n;

    cout << "Ingrese la cantidad de puntos: ";
    cin >> n;

    Conjunto conjunto;

    for (int i = 0; i < n; i++) {
        int x, y;
        cout << "Ingrese las coordenadas del punto " << i + 1 << " (x y): ";
        cin >> x >> y;
        conjunto.addPoint(x, y);
    }

    return conjunto;
}


int main() {
 
    Conjunto conjuntoA = leerConjunto("A");
    Conjunto conjuntoB = leerConjunto("B");
    Conjunto conjuntoUnion = unionDeConjunto(conjuntoA, conjuntoB);
   
    cout << "Union de A y B: " << endl;
    conjuntoUnion.displayar();

    delete [] conjuntoA.points;
    delete [] conjuntoB.points;
    delete [] conjuntoUnion.points;
  
    return 0;
}