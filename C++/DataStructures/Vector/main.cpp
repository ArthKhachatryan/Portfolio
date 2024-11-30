#include <iostream>
#include "Vector.h"

int main(){
    Vector v;
    Vector v2;
    Vector v3;
    v.push_back(10);
    v.push_back(11);
    v.push_back(12);
    v.push_back(13);
    v.push_back(40);
    v.push_back(15);
    v.push_front(17);
    v.push_front(18);
    v.push_front(19);
    v.push_front(20);
    v.push_front(21);

    v2.push_back(10);
    v2.push_back(78);
    std::cout << "Vector v:\n";
    v.print();
    Vector v1(v);
    std::cout << "Vector v after Vector v1(v):\n";
    v.print();
    std::cout << "Vector v1 after Vector v1(v):\n";
    v1.print();
    v3 = v1 = v2;
    std::cout << "Vector v1 after v3 = v1 = v2:\n";
    v1.print();
    std::cout << "Vector v2 after v3 = v1 = v2:\n";
    v2.print();
    std::cout << "Vector v2 after v3 = v1 = v2:\n";
    v3.print();

    return 0;
}