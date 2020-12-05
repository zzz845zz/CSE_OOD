#include <iostream>

template<typename T>
T min(T x, T y) {
	return x < y ? x : y;
}
int main() {
	int x = 3;
	int y = 2;
	double d = 2.1;
	double e = 3.3;

	// std::cout << "min(x,y) : " << min(x, y) << ", min(d,e) : " << min(d, e) << ", min(d,x) : " << min(d, x) << std::endl;
	// Compile error. 
	// `min(d,x)` -> min(<double>, <int>) but there is no matched template

	std::cout << "min(x,y) : " << min(x, y) << ", min(d,e) : " << min(d, e) << ", min(d,x) : " << min((int)d, x) << std::endl;
	// min(x,y) : 2, min(d,e) : 2.1, min(d,x) : 2
	std::cout << "min(x,y) : " << min(x, y) << ", min(d,e) : " << min(d, e) << ", min(d,x) : " << min(d, (double)x) << std::endl;
	// min(x,y) : 2, min(d,e) : 2.1, min(d,x) : 2.1

	return 0;
}
