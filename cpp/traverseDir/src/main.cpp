#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include "dirtrav.h"

using namespace std;

int do_args( int argc, char * argv[] ) {
    int c = 1;
 //   while()
    return 0; 
}

int main( int argc, char * argv[] )
{
    printf("size: %d\n", depth_first_apply(argv[1], &sizepathfun));
    return 0;
}
