 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#include "answer06.h"


int main(int argc, char * * argv)
{
	printf("Testing partitionDecreasing(3)\n");
	partitionDecreasing(3);
	printf("Testing partitionDecreasing(4)\n");
	partitionDecreasing(4);
	printf("Testing partitionDecreasing(5)\n");
	partitionDecreasing(5);
	printf("Testing partitionIncreasing(3)\n");
	partitionIncreasing(3);
	printf("Testing partitionIncreasing(4)\n");
	partitionIncreasing(4);
	printf("Testing partitionIncreasing(5)\n");
	partitionIncreasing(5);
    return 0;
}

