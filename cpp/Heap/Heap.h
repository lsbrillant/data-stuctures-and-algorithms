#include <vector>
#include <exception>
#include <iostream>

using namespace std;

struct HeapException : public exception {
    const char *what() const throw() {
        return "Empty Heap";
    }
};

template <typename Comparable>
class BinaryHeap 
{
    public:
        explicit BinaryHeap( int capacity = 100 ) : array ( capacity + 1 ) {
            currentSize = 0; 
        }
        explicit BinaryHeap( const vector<Comparable> & items ) 
            : array( items.size() + 10 ), currentSize( items.size() ) {
            for( int i = 0; i < items.size(); ++i ){
                array[i+1] = items[i];
            }
            buildHeap();
        }

        bool isEmpty() const {
            return (currentSize == 0);
        }
        const Comparable & findMin() const {
            return array[1];
        }

        void insert( const Comparable & x ) {
            if( currentSize == array.size() - 1 )
                array.resize( array.size() * 2 );
            int hole = ++currentSize;
            Comparable copy = x;
            array[0] = move( copy );
            for( ; x < array[hole / 2]; hole /= 2 ) 
                array[hole] = move(array[hole/2]);
            array[hole] = move(array[0]);
        }
        void deletMin() {
            if ( isEmpty() ) {
                throw HeapException();
            }
            array [1] = move( array[currentSize--] );
            percolateDown( 1 );
        }
        void deleteMin( Comparable & minItem ) { 
            if ( isEmpty() ) {
                throw HeapException();
            }
            minItem = move( array[1] );
            array [1] = move( array[currentSize--] );
            percolateDown( 1 );
        }
        void makeEmpty() {
            while(!isEmpty) {
                deleteMin();
            }
        }
        vector<Comparable> heapSort() {
            vector<Comparable> ret;
            Comparable cMin;
            while( !isEmpty() ){
                deleteMin( cMin );
                ret.push_back(cMin);
            }
            return ret;
        }
    private:
        int currentSize;
        vector<Comparable> array;

        void buildHeap() {
            for( int i = currentSize / 2; i > 0 ; --i ){
                percolateDown( i );
            }
        }
        void percolateDown( int hole ) {
            int child;
            Comparable tmp = move(array[hole]);

            for ( ; hole * 2 <= currentSize; hole = child ) {
                child = hole * 2;
                if(child != currentSize && array[child+1] < array[child]) 
                    ++child;
                if(array[child] < tmp)
                    array[hole] = move(array[child]);
                else
                    break; 
            }
            array[hole] = move(tmp);
        }
   
};

