#include <stdio.h>
#include <string.h>
#include <stdlib.h>


enum {
    up_arrow,
    left_arrow,
    diag_arrow
};

inline int max( int x, int y ) {
    return ( x <= y )? y : x;
}


void lsc( char* x, char* y ) {
    int m = strlen(x);
    int n = strlen(y);
    int b[m+1][n+1], c[m+1][n+1];
    int i,j,k=0;    
    char *buf = malloc(sizeof(char) * max(n,m));

#if DEBUG    
    printf("m: %d\n",m);
    printf("n: %d\n",n);
#endif
    
    for( i = 1; i <= m; i++ )
        c[i][0] = 0;
    for( j = 0; j <= n; j++ )
        c[0][j] = 0;
    for( i = 1; i <= m; i++ ) {
        for ( j = 1; j <= n; j++ ) {
            if (x[i-1] == y[j-1] ) {
                c[i][j] = (c[i-1][j-1]) + 1;
                b[i][j] = diag_arrow; 
            } else if ( c[i-1][j] >= c[i][j-1] ) {
                c[i][j] = c[i-1][j];
                b[i][j] = up_arrow;
            } else {
                c[i][j] = c[i][j-1];
                b[i][j] = left_arrow;
            }
        }
    }
    i--;j--;

#if DEBUG
    printf("length: %d\n",c[i][j]);
    printf("i: %d\n",i);
    printf("j: %d\n",j);
    printf("x[0]: %c\n",x[0]);
    printf("y[0]: %c\n",y[0]);
    int s,q;
    
    for( s = 1; s <= m; s++ ) {
        for( q = 1; q <= n; q++ ) {
            printf("[%d]",b[s][q]);
        }
        printf("\n"); 
    }
#endif

    while(1) {
        if ( i == 0 || j == 0 ) {
            break;
        } else if ( b[i][j] == diag_arrow ) {
            buf[k] = (char)x[i-1];
            k++;
            i--; j--;
        } else if ( b[i][j] == up_arrow ) {
            i--;
        } else {
            j--;
        }
    }
    k--;
    for( ; k>=0; k-- ) {
        putchar(buf[k]);
    }
    putchar('\n');
    free(buf);
}


int main( int argc, char * argv[] ) 
{
    if( argc != 3 ){
        printf("Usage: %s string1 string2\n",argv[0]);
        exit(EXIT_FAILURE);
    } 

    lsc(argv[1],argv[2]);
}
