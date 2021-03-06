#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(int a, int b) {
	return a - b;
}
int compar(const void *a, const void *b) {
	return *(int*)a - *(int*)b;
}

void nqsort(void *data, int elements, int size, int compare(int a, int b)) {
	char *vals;
	char *low;
	char *high;
	char *hole;
	char partition;
	bool count = 0;
	vals = (char*)data;

	if (elements == 2) {
		if (compare(vals[0], vals[1])>0) {
			partition = vals[0];
			vals[0] = vals[1];
			vals[1] = partition;

			memcpy(vals[0], vals[1], 4);
		}
		return;
	}
	else if(elements<2){
		return;
	}

	low = &(vals[0]);
	high = &(vals[elements - 1]);
	partition = *low;
	hole = low;
	while (high != low) {
		if  ( (count = !count)== 1){
			while (compare(*high, partition)>0 && high != low) {
				high = high - size;
			}
			*hole = *high;
			hole = high;
		}
		else {
			while (compare(*low, partition)<=0 && high != low) {
				low = low + size;
			}
			*hole = *low;
			hole = low;
		}
	}
	*hole = partition;

	nqsort(vals, hole - vals, size, compare);
	nqsort(hole + size, &(vals[elements - 1]) - hole, size, compare);
	
}

int main()
{
	int input;
	int val = 0;
	int *nums;
	int *rep;

	printf("Please enter number of values to be sorted:\n");
	while ((input = getchar()) != '\n') {
		val = val * 10 + (input - '0');
	}
	nums = (int*)malloc(sizeof(int)*val);
	rep = (int*)malloc(sizeof(int)*val);
	srand(time(0));
	for (int i = 0; i < val; i++) {
		nums[i] = rand() % 1000 + 1;
		rep[i] = nums[i];
	}

	nqsort(nums, val, sizeof(int), compare);

	for (int i = 0; i < val - 1; i++) {
		if (nums[i] > nums[i + 1]) {
			printf("FAILURE\n");
			exit(0);
		}
	}
	printf("SUCCESS\n");
}