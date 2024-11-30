#ifndef VECTOR_H
#define VECTOR_H
class Vector{
    public:
    Vector();
    Vector(const Vector& other);
    Vector(Vector&& rhs);
    ~Vector();

    void push_back(int elem);
    void push_front(int elem);
    int& operator[](int subscript);
    Vector& operator=(const Vector& v);
    Vector& operator=(Vector&& r);
    int size();
    void print();

   private:
    int m_capacity;
    int m_size;
    int* m_arr;
};
#endif
