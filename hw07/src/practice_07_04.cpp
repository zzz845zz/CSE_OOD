#include <iostream>
#include <vector>

using std::vector;
int main() {
    vector<int> vec;

    int a, b;
    std::cout << "Input 2 integer: ";
    std::cin >> a >> b;

    try {
        if (b == 0 ) throw b;
        std::cout << a << "/" << b << " = " << a/b << std::endl;
    }
    catch (int exception) {
        std::cout << "exeception: " << exception << std::endl;
    }

}
