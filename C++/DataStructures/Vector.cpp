#include <iostream>
#include <vector>
#include <exception>
class Vector{
    public:
    Vector() : m_capacity{4},m_size{0},m_arr{new int[m_capacity]} {}
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

int size(){
    return m_size;
}

   private:
    int m_capacity;
    int m_size;
    int* m_arr;
};

int main(){
    Vector v;

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
    
    for(int i = 0; i < v.size(); i++){
     std::cout << v[i] << std::endl;
    }

    return 0;
}