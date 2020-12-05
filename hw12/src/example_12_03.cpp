#include <iostream>

template <typename T>
void func(const T& x) {
	static int count = 0;
	std::cout << "x = " << x << ", count = " << count << std::endl;
	++count;
}

int main() {
	func<int>(1);
	// 	x = 1, count = 0
	
	func<int>(1);
	// x = 1, count = 1
	
	func<double>(1.1);
	// x = 1.1, count = 0

	func<int>(1);
	// x = 1, count = 2

	// Why? Because compiler create func(int x) and func(double x) at the compile-time.
	// So there is two static count.
	//		one in the (int x)
	//		the other in the (double x)
	return 0;
}
