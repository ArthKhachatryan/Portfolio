#include <iostream>
#include <exception>
#include "Vector.h"
    Vector::Vector() : m_capacity{4},m_size{0},m_arr{new int[m_capacity]} {}
    Vector::Vector(const Vector& other) {
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_arr = new int[m_capacity];
        for(int i = 0; i < m_size; i ++)
            m_arr[i] = other.m_arr[i];
    }
    Vector::Vector(Vector&& rhs){
        m_capacity = rhs.m_capacity;
        m_size = rhs.m_size;
        m_arr = rhs.m_arr;
        rhs.m_arr = nullptr;
        rhs.m_size = 0;
        rhs.m_capacity = 0;
    }

    Vector::~Vector(){
        delete [] m_arr;
    }
    void Vector::push_back(int elem){
        if(m_size == m_capacity){
            m_capacity *= 2;
            int* tmp = new int[m_capacity];
            for (int i = 0; i < m_size; i ++)
                tmp[i] = m_arr[i];
                tmp[m_size] = elem;
            delete [] m_arr;
            m_arr = tmp;
            tmp = nullptr;
        }
    m_arr[m_size++] = elem;        
    }

    void Vector::push_front(int elem){
        if(m_size == m_capacity){
            m_capacity *= 2;
            int* tmp = new int[m_capacity];
            tmp[0] = elem;
            for (int i = 0; i < m_size; i ++)
                tmp[i + 1] = m_arr[i];
            delete [] m_arr;
            m_arr = tmp;
            tmp = nullptr;
        }
        else {
        for(int i = m_size; i > 0; i --)
        m_arr[i] = m_arr[i - 1];
        m_arr[0] = elem;
        }
        m_size ++;
    }

int& Vector::operator[](int subscript){
    if(subscript < 0 || subscript >= m_size)
     throw std::out_of_range("Subscript out of range");
    return m_arr[subscript];
}   

Vector& Vector::operator=(const Vector& v){
    if(this == &v)
    return *this;
    delete [] m_arr;
     m_capacity = v.m_capacity;
        m_size = v.m_size;
        m_arr = new int[m_capacity];
        for(int i = 0; i < m_size; i ++)
            m_arr[i] = v.m_arr[i];
    return *this;
}

Vector& Vector::operator=(Vector&& r){
        delete [] m_arr;
        m_capacity = r.m_capacity;
        m_size = r.m_size;
        m_arr = r.m_arr;
        r.m_arr = nullptr;
        r.m_size = 0;
        r.m_capacity = 0;
        return *this;
}


int Vector::size(){
    return m_size;
}

void Vector::print(){
    for(int i = 0; i < m_size; i ++)
     std::cout << m_arr[i] << " ";
     std::cout <<"\n";
}
