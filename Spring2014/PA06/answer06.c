#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#include "answer06.h"

	/*def printPartition(nums):
    print ' =',
    for n in nums:
        if n != 0:
            print n,
    print*/
void printPartition(int* nums, int arrayLength)
{
	int i;
	printf("= ");
	for(i=0;i<arrayLength;i++)
	{
		//printf("Printed");
		if(nums[i] != 0)
		{
			printf("%d", nums[i]);
			if(i == arrayLength-1)
			{
				//Do nothing
			}
			else if(nums[i+1]!=0) //NOT WORKING
			{
				printf(" + ");
			}
			
		}
		
	}
	printf("\n");
	
}



/*def partition(nums, n, i):
    if n != 0:
        for k in xrange(n, 0, -1):
            tmp = nums[:]
            tmp[i] = k
            partition(tmp, n-k, i+1)

    else:
        printPartition(nums)*/
		
void partition(int nums[], int n, int i, int arrayLength)
{
	//printf("Partition %d %d %d\n",n,i,arrayLength);
    if (n!=0)
	{
		int k;
		for(k = n;k>0;k--)
		{		
			int* tmp = (int*)malloc(sizeof(int)*arrayLength);
			memcpy(tmp,nums,sizeof(int)*arrayLength);
			tmp[i] = k;
			partition(tmp,n-k,i+1,arrayLength);
			free(tmp);
		}
	}
	else
	{
		printPartition(nums, arrayLength);
	}
}
/*def partitionAll(value):
    partition([0]*value, value, 0)*/
	
void partitionAll(int value)
{
    int* stored_partition_values = (int*)malloc(sizeof(int)*value);
	int i;
	for (i=0;i<value;i++)
	{
		stored_partition_values[i] = 0;
	}
	partition(stored_partition_values, value, 0, value);
    free(stored_partition_values);
}

/**
 * Prints all partitions that have strictly increasing values.
 *
 * Example:
 * partitionIncreasing(5); // prints the following: (line order not important)
 * = 1 + 4
 * = 2 + 3
 * = 5
 * 
 * These partitions are excluded because they are not _strictly_ increasing
 * 1 + 1 + 3
 * 2 + 1 + 2
 * 3 + 2
 * 
 * Note:
 * The program should generate only valid partitions.  Do not
 * generates all partitions and then filter for validity. If you 
 * do this, you will almost certainly have trouble understanding the exam.
 *
 * Hint: look at file: expected/partitionIncreasing.output
 */
 void partition5(int nums[], int n, int i, int arrayLength)
{
	//printf("Partition %d %d %d\n",n,i,arrayLength);
    if (n!=0)
	{
		int k;
		for(k = n;k>0;k--)
		{	
			if(i == 0)
			{
				int* tmp = (int*)malloc(sizeof(int)*arrayLength);
				memcpy(tmp,nums,sizeof(int)*arrayLength);
				tmp[i] = k;
				partition5(tmp,n-k,i+1,arrayLength);
				free(tmp);
			}
			else if(k > nums[i-1])
			{
				int* tmp = (int*)malloc(sizeof(int)*arrayLength);
				memcpy(tmp,nums,sizeof(int)*arrayLength);
				tmp[i] = k;
				partition5(tmp,n-k,i+1,arrayLength);
				free(tmp);
			}
		}
	}
	else
	{
		printPartition(nums, arrayLength);
	}
}

void partitionIncreasing(int value)
{
	int* stored_partition_values = (int*)malloc(sizeof(int)*value);
	int i;
	for (i=0;i<value;i++)
	{
		stored_partition_values[i] = 0;
	}
	partition5(stored_partition_values, value, 0, value);
    free(stored_partition_values);
}


 void partition6(int nums[], int n, int i, int arrayLength)
{
	//printf("Partition %d %d %d\n",n,i,arrayLength);
    if (n!=0)
	{
		int k;
		for(k = n;k>0;k--)
		{	
			if(i == 0)
			{
				int* tmp = (int*)malloc(sizeof(int)*arrayLength);
				memcpy(tmp,nums,sizeof(int)*arrayLength);
				tmp[i] = k;
				partition6(tmp,n-k,i+1,arrayLength);
				free(tmp);
			}
			else if(k < nums[i-1] || nums[i-1] == 0)
			{
				int* tmp = (int*)malloc(sizeof(int)*arrayLength);
				memcpy(tmp,nums,sizeof(int)*arrayLength);
				tmp[i] = k;
				partition6(tmp,n-k,i+1,arrayLength);
				free(tmp);
			}
		}
	}
	else
	{
		printPartition(nums, arrayLength);
	}
}
void partitionDecreasing(int value)
{
	int* stored_partition_values = (int*)malloc(sizeof(int)*value);
	int i;
	for (i=0;i<value;i++)
	{
		stored_partition_values[i] = 0;
	}
	partition6(stored_partition_values, value, 0, value);
    free(stored_partition_values);
}
/**
 * Prints all partitions comprised solely of odd numbers.
 *
 * Example:
 * partitionOdd(5); // prints the following (line order not important)
 * = 1 + 1 + 1 + 1 + 1
 * = 1 + 1 + 3
 * = 1 + 3 + 1
 * = 3 + 1 + 1
 * = 5
 * 
 * See: note on partitionIncreasing(...)
 * Hint: for odd numbers, (value % 2 != 0)
 * Hint: look at file: expected/partitionOdd.output*/
 void partition2(int nums[], int n, int i, int arrayLength)
{
	//printf("Partition %d %d %d\n",n,i,arrayLength);
    if (n!=0)
	{
		int k;
		for(k = n;k>0;k--)
		{	
			if(k % 2 != 0)
			{
				int* tmp = (int*)malloc(sizeof(int)*arrayLength);
				memcpy(tmp,nums,sizeof(int)*arrayLength);
				tmp[i] = k;
				partition2(tmp,n-k,i+1,arrayLength);
				free(tmp);
			}
		}
	}
	else
	{
		printPartition(nums, arrayLength);
	}
}

void partitionOdd(int value)
{
	int* stored_partition_values = (int*)malloc(sizeof(int)*value);
	int i;
	for (i=0;i<value;i++)
	{
		stored_partition_values[i] = 0;
	}
	partition2(stored_partition_values, value, 0, value);
    free(stored_partition_values);
}

void partition3(int nums[], int n, int i, int arrayLength)
{
	//printf("Partition %d %d %d\n",n,i,arrayLength);
    if (n!=0)
	{
		int k;
		for(k = n;k>0;k--)
		{	
			if(k % 2 == 0)
			{
				int* tmp = (int*)malloc(sizeof(int)*arrayLength);
				memcpy(tmp,nums,sizeof(int)*arrayLength);
				tmp[i] = k;
				partition3(tmp,n-k,i+1,arrayLength);
				free(tmp);
			}
		}
	}
	else
	{
		printPartition(nums, arrayLength);
	}
}
void partitionEven(int value)
{
	int* stored_partition_values = (int*)malloc(sizeof(int)*value);
	int i;
	for (i=0;i<value;i++)
	{
		stored_partition_values[i] = 0;
	}
	partition3(stored_partition_values, value, 0, value);
    free(stored_partition_values);
}

int isPrime(int k)
{
	if(k==2 || k==3 || k==5 || k==7)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void partition4(int nums[], int n, int i, int arrayLength)
{
	//printf("Partition %d %d %d\n",n,i,arrayLength);
    if (n!=0)
	{
		int k;
		for(k = n;k>0;k--)
		{	
			if(isPrime(k) == 1)
			{
				int* tmp = (int*)malloc(sizeof(int)*arrayLength);
				memcpy(tmp,nums,sizeof(int)*arrayLength);
				tmp[i] = k;
				partition4(tmp,n-k,i+1,arrayLength);
				free(tmp);
			}
		}
	}
	else
	{
		printPartition(nums, arrayLength);
	}
}

void partitionPrime(int value)
{
	int* stored_partition_values = (int*)malloc(sizeof(int)*value);
	int i;
	for (i=0;i<value;i++)
	{
		stored_partition_values[i] = 0;
	}
	partition4(stored_partition_values, value, 0, value);
    free(stored_partition_values);
}

void partition7(int nums[], int n, int i, int arrayLength)
{
	//printf("Partition %d %d %d\n",n,i,arrayLength);
    if (n!=0)
	{
		int k;
		for(k = n;k>0;k--)
		{	
			if(i == 0)
			{
				int* tmp = (int*)malloc(sizeof(int)*arrayLength);
				memcpy(tmp,nums,sizeof(int)*arrayLength);
				tmp[i] = k;
				partition7(tmp,n-k,i+1,arrayLength);
				free(tmp);
			}
			else if((k % 2 == 0 && (nums[i-1] % 2 == 1 || nums[i-1] == 0)) || (k % 2 == 1 && (nums[i-1] % 2 == 0 || nums[i-1] == 0)))
			{
				int* tmp = (int*)malloc(sizeof(int)*arrayLength);
				memcpy(tmp,nums,sizeof(int)*arrayLength);
				tmp[i] = k;
				partition7(tmp,n-k,i+1,arrayLength);
				free(tmp);
			}
		}
	}
	else
	{
		printPartition(nums, arrayLength);
	}
}

void partitionOddAndEven(int value)
{
	int* stored_partition_values = (int*)malloc(sizeof(int)*value);
	int i;
	for (i=0;i<value;i++)
	{
		stored_partition_values[i] = 0;
	}
	partition7(stored_partition_values, value, 0, value);
    free(stored_partition_values);
}




/*
http://repl.it/languages/Python


def printPartition(nums):
    print ' =',
    for n in nums:
        if n != 0:
            print n,
    print

def partition(nums, n, i):
    if n != 0:
        for k in xrange(n, 0, -1):
            tmp = nums[:]
            tmp[i] = k
            partition(tmp, n-k, i+1)

    else:
        printPartition(nums)

def partitionAll(value):
    partition([0]*value, value, 0)


partitionAll(1)
partitionAll(2)
partitionAll(3)
partitionAll(4)
partitionAll(5)


*/