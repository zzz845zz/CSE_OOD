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
    // <-- when calling `foo` defined as `foo()`, Is `A` destructed at this time ?
    return i;
}

int main(){
    cout << foo() <<endl;
    // <-- when calling `foo` defined as `&foo()`, Is `A` destructed at this time (after return) ?

    cout << i <<endl;

    return 0;
}