#include <vector>
#include <iostream>
using namespace std;

template <typename Comparable>
void insertionSort( vector<Comparable> & a, int left, int right )
{
    int j;

    for( int p = left; p <= right; p++ )
    {
        Comparable tmp = a[ p ];
        for( j = p; j > 0 && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}

template <typename Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right )
{
    int center = ( left + right ) / 2;
    if( a[ center ] < a[ left ] )
        swap( a[ left ], a[ center ] );
    if( a[ right ] < a[ left ] )
        swap( a[ left ], a[ right ] );
    if( a[ right ] < a[ center ] )
        swap( a[ center ], a[ right ] );

        // Place pivot at position right - 1
    swap( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}
template <typename Comparable>
void quicksort( vector<Comparable> & a, int left, int right )
{
    while( left + 10 <= right )
    {
        Comparable pivot = median3( a, left, right );

            // Begin partitioning
        int i = left, j = right - 1;
        for( ; ; )
        {
            while( a[ ++i ] < pivot ) { }
            while( pivot < a[ --j ] ) { }
            if( i < j )
                swap( a[ i ], a[ j ] );
            else
                break;
        }

        swap( a[ i ], a[ right - 1 ] );  // Restore pivot
        if ( (i -left) < (right - i) ) {
            quicksort( a, left, i - 1 );     // Sort small elements
            left = i + 1;
        } else { 
            quicksort( a, i + 1, right );     // Sort small elements
            right = i - 1;
        }
    }
    insertionSort( a, left, right );
}
template <typename Comparable>
void quicksort( vector<Comparable> & a )
{
    quicksort( a, 0, a.size( ) - 1 );
}

int main() 
{
    vector<int> a{10,34,5,7,8,2,45,86,1235,67,231,999999,23};

    quicksort(a);
    
    for( int b : a ) cout << b << " ";
    cout << endl;
    

}
