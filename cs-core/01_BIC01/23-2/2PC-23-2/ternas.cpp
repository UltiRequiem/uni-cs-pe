#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> pytagoricTriple(int top){
	vector<vector<int>> triplesFound;

	for (int i =0; i <= top; i++){
		int hypoSquare = i*i;

		for(int x = 0; x < i ; x++){

			int firstLegSquare = x*x;
			
			for (int y = 0; y < x; y++ ){
				if (firstLegSquare + y*y == hypoSquare){
					bool is_multiple= false;

					for (const auto& terna : triplesFound){
						if (x % terna[0] == 0 and y % terna[1] == 0){
							is_multiple = true;
						}
					}

					if (!is_multiple) triplesFound.push_back({x,y,i});

				}

			}
		}
	}

	return triplesFound;
}

int main(){
	int K;
	cout << "Ingrese la cota: ";
	cin >> K;

	vector<vector<int>> ternas = pytagoricTriple(K);


	if (!ternas.empty()) {
		cout << "Las ternas que verifican i), ii) y iii) son:" << endl;
		for (const auto& terna : ternas) {
			cout << terna[0] << " " << terna[1] << " " << terna[2] << endl;
		}
	} else {
		cout << "No hay ternas que cumplan con las condiciones." << endl;
	}

	return 0;
}
