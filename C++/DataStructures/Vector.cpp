#include <iostream>
#include <vector>
#include <exception>
class Vector{
    public:
    Vector() : m_capacity{4},m_size{0},m_arr{new int[m_capacity]} {}
    Vector(const Vector& other) {
        m_capacity = other.m_capacity;
        m_size = other.m_size;
        m_arr = new int[m_capacity];
        for(int i = 0; i < m_size; i ++)
            m_arr[i] = other.m_arr[i];
    }
    ~Vector(){
        delete [] m_arr;
    }
    void push_back(int elem){
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

    void push_front(int elem){
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

int & operator[](int subscript){
    if(subscript < 0 || subscript >= m_size)
     throw std::out_of_range("Subscript out of range");
    return m_arr[subscript];
}   

Vector& operator=(const Vector& v){
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

int size(){
    return m_size;
}

void print(){
    for(int i = 0; i < m_size; i ++)
     std::cout << m_arr[i] << " ";
     std::cout <<"\n";
}

   private:
    int m_capacity;
    int m_size;
    int* m_arr;
};

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
