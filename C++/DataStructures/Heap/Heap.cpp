#include <iostream>
#include <vector>

class Heap{
public:

void insert(int elem){
    heap.push_back(elem);
    int i = heap.size() - 1;
    int parent = (i - 1) / 2;
    while(heap[i] > heap[parent] && i > 0){
        int temp = heap[i];
        heap[i] = heap[parent];
        heap[parent] = temp;
        
        i = parent;
        parent = (i - 1) / 2;
    }
}

void heapify(int i)
{
    int leftChild;
    int rightChild;
    int largestChild;

    for (; ; )
    {
        leftChild = 2 * i + 1;
        rightChild = 2 * i + 2;
        largestChild = i;

        if (leftChild < heap.size() && heap[leftChild] > heap[largestChild]) 
        {
            largestChild = leftChild;
        }

        if (rightChild < heap.size() && heap[rightChild] > heap[largestChild])
        {
            largestChild = rightChild;
        }

        if (largestChild == i) 
        {
            break;
        }

        int temp = heap[i];
        heap[i] = heap[largestChild];
        heap[largestChild] = temp;
        i = largestChild;
    }
}

void printHeap(){
for(int val : heap){
std::cout << val << " ";
}
}

void buildHeap(std::vector<int>& source){
    heap = source;
    for(int i = (heap.size()/2) - 1; i >= 0; i --)
    heapify(i);
}

int deleteMax(){
    if (heap.empty()) {
            throw std::out_of_range("Heap is empty");
        }

    int max = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapify(0); 
    return max;
}

private:
std::vector<int> heap;
};

int main(){
Heap heap1;
Heap heap2;
heap1.insert(17);
heap1.insert(18);
heap1.insert(10);
heap1.insert(21);
heap1.insert(23);
heap1.insert(7);
heap1.insert(77);
heap1.insert(101);
std::vector<int> vect = {1,8,7,5,66,4,2,8};
heap2.buildHeap(vect);
heap1.printHeap();
heap2.printHeap();
std::cout << "\n" << heap1.deleteMax() << "\n";
std::cout << heap1.deleteMax() << "\n";
heap1.printHeap();
heap2.printHeap();
}