#include <iostream>
#include <vector>
#include "Heap.h"

using namespace std;

int main() 
{
    vector<int> vec = {1,4,3,6,43,78,32,12,76,21,345,5,90};
    BinaryHeap<int> * heap = new BinaryHeap<int>(vec);
    vector<int> sorted = heap->heapSort();
    
    for( int a : sorted ) {
        cout << a << ' ';
    } 
    cout << endl;
    
        
    return 0;
}
