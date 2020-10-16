#include <stdio.h>

class Animal {
    public:
    
    protected:
        int age;
};

class Cat : public Animal {};
class Dog : public Animal {};



//  | Animal |      | Animal |
//      ^                ^
//  |  Cat   |      |   Dog  |
//          ^        ^
//          | DogCat |
class DogCat : public Cat, public Dog {
    public:
        void setAge() {
            // age = 10;            -----   It doesn't know whose `age` it is  (Cat? or Dog?)
            Cat::age = 10;
        }
};

int main() {
    DogCat* dat = new DogCat();
    Animal* animal;
    // animal = dat;            -----   It doesn't know that where `DogCat` comes from? (Animal->Cat->DogCat?   or   Animal->Dog->DogCat?)
    animal = static_cast <Cat*>(dat);   // Type casting `DogCat` to `Cat`
    animal = (Cat*)dat;                 // Type casting `DogCat` to `Cat`
}