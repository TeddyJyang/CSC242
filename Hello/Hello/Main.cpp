#include <iostream>

using namespace std;

int a = 1;

void add() {
	int a = a + 1;
}

int main() {
	cout << "Hello World" << endl;
	cout << a;
	add();
	cout << a;
	return 0;
}
