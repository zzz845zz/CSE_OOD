#include <iostream>

template<typename T>
void swapXX(T& a, T& b) {
	T temp = a;
	a = b;
	b = temp;
}

// Template specialization for type <string>
template<>
void swapXX(std::string& a, std::string& b) {
	a = a;
	b = b;
}

int main() {
	int a = 1;
	int b = 2;
	float c = 3.3;
	float d = 4.4;
	std::string e = "world";
	std::string f = "hello";

	std::cout << "--- Before ---" << std::endl; 
	std::cout << "a:" << a << ",b:" << b << std::endl;
	std::cout << "c:" << c << ",d:" << d << std::endl;
	std::cout << "e:" << e << ",f:" << f << std::endl;
	// --- Before ---
	// a:1,b:2
	// c:3.3,d:4.4
	// e:world,f:hello

	swapXX<int>(a, b);
	swapXX<float>(c, d);
	swapXX < std::string>(e, f);

	std::cout << "\n--- After ---" << std::endl; 
	std::cout << "a:" << a << ",b:" << b << std::endl;
	std::cout << "c:" << c << ",d:" << d << std::endl;
	std::cout << "e:" << e << ",f:" << f << std::endl;
	// --- After ---
	// a:2,b:1
	// c:4.4,d:3.3
	// e:world,f:hello
	return 0;
}
