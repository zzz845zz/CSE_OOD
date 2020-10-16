#include <stdio.h>

class Animal {
    public:
    
    protected:
        int age;
};

// Power of virtual
class Cat : public virtual Animal {};
class Dog : public virtual Animal {};

//          | Animal |      
//          ^        ^
//  |  Cat   |      |   Dog  |
//          ^        ^
//          | DogCat |
class DogCat : public Cat, public Dog {
    public:
        void setAge() {
            age = 10;
            Cat::age = 10;
        }
};

int main() {
    DogCat* dat = new DogCat();
    Animal* animal;
    animal = dat;          
    animal = static_cast <Cat*>(dat);   // Type casting `DogCat` to `Cat`
    animal = (Cat*)dat;                 // Type casting `DogCat` to `Cat`
}