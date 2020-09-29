#include <iostream>
using namespace std;
int i;
class A{
    public:
        ~A(){
            i= 10;
        }
};

int foo(){
    i= 3;
    A ob;
    // <-- when calling `foo` defined as `&foo()`, `A` is destructed before return `i`
    return i;
    // <-- when calling `foo` defined as `foo()`, `A` is destructed after return `i`
}

int main(){
    cout << foo() <<endl;

    cout << i <<endl;

    return 0;
}