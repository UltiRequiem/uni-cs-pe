#include <iostream>
#include <string>

using namespace std;

string classifyTriangle(int a1, int a2, int a3){
	if (a1 < 90 && a2 < 90 && a3 < 90) return "ACUTANGULO";
	if (a1 == 90 || a2 == 90 || a3 == 90) return "RECTANGULO";

	return "OBTUSANGULO";
}