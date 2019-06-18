// ConsoleApplication1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

void calculator() {
	calc a;
	std::string in;
	std::cout << "Insert your expression:\n";
	std::cin >> in;
	std::cout << "Reverse Polish Notation: " << a.getRPN(in) << std::endl;
	std::cout << "Result: " << a.count(in).value << "\nPress any key to continue or 0 to exit" << std::endl;
	std::cin >> in;
	if (in == "0") {
		return;
	}
	else {
		calculator();
	}
}

int main()
{
	calculator();
	system("pause");
	return 0;
}

