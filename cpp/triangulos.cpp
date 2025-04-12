#include "triangulos.h"

int main() {
	int n;
	cin >> n;

	string results[n];

	for (int i = 0; i < n; i++){
		int a1, a2, a3;
		cin >> a1 >> a2 >> a3;
		results[i] = classifyTriangle(a1,a2,a3);
	}


    for (int i = 0; i < n; ++i) {
        cout << results[i] << endl;
    }


	return 0;
}
