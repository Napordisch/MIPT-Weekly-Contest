#include <iostream>

int main() {
	int h, m, s, h1, m1, s1;

	std::cin >> h >> m >> s >> h1 >> m1 >> s1;

	std::cout << (h1*3600 + m1*60 + s1) - (h*3600 + m*60 + s);
}