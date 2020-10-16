#include <iostream>
#include <vector>

using std::vector;
int main() {
    vector<int> vec;
    vec.push_back(11);
    vec.push_back(22);
    vec.push_back(33);
    vec.push_back(44);

    for(vector<int>::iterator it= vec.begin(); it!= vec.end(); ++it) {
        if (*it == 33) {
            vec.erase(it);
        } 
    }

    for(vector<int>::iterator it= vec.begin(); it!= vec.end(); ++it) {
            std::cout << "Vector element: " << *it << std::endl;
    }
}
