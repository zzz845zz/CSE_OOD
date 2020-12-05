// Functor

#include<iostream>
#include<string>

struct MyFunctor {
	void operator()() {
		std::cout << "functor executed" << std::endl;
	}
};

int main() {
	MyFunctor funct;
	funct();
}