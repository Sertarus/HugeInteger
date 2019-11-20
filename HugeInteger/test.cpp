#include "HugeInteger.hpp"
#include <iostream>

using namespace std;

int main() {
	string s;
	cout << "a: ";
	cin >> s;
	HugeInteger a(s);
	cout << endl << "b: ";
	cin >> s;
	HugeInteger b(s);
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "a < b: " << ((a < b) ? "true" : "false") << endl;
	cout << "a <= b: " << ((a <= b) ? "true" : "false") << endl;
	cout << "a != b: " << ((a != b) ? "true" : "false") << endl;
	cout << "a == b: " << ((a == b) ? "true" : "false") << endl;
	cout << "a >= b: " << ((a >= b) ? "true" : "false") << endl;
	cout << "a > b: " << ((a > b) ? "true" : "false") << endl;
	cout << "a + b: " << a + b << endl;
	cout << "a - b: " << a - b << endl;
	cout << "a * b: " << a * b << endl;
	cout << "a / b: " << a / b << endl;
}