/*******************************************************************************
 * Name        : quicksort.c
 * Author      : Maxwell Metzner, Savnick Patel
 * Date        : 2/27/21
 * Description : Quicksort implementation. - "The corresponding source file with the implementation of those functions contained within the header"
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "quicksort.h"

/* Static (private to this file) function prototypes. */
static void swap(void *a, void *b, size_t size);
static int lomuto(void *array, int left, int right, size_t elem_sz,
		int (*comp) (const void*, const void*));
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
		int (*comp) (const void*, const void*));

/**
 * Compares two integers passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to int pointers.
 * Returns:
 * -- 0 if the integers are equal
 * -- a positive number if the first integer is greater
 * -- a negative if the second integer is greater
 */
int int_cmp(const void *a, const void *b) {
	// TODO
	int num1;
	int num2;
	num1 = atoi(*(const char **)a);
	num2 = atoi(*(const char **)b);
	if (num1 > num2) {
		return 1;
	}
	if (num1 == num2) {
		return 0;
	}
	return -1;
}

/**
 * Compares two doubles passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to double pointers.
 * Returns:
 * -- 0 if the doubles are equal
 * -- 1 if the first double is greater
 * -- -1 if the second double is greater
 */
int dbl_cmp(const void *a, const void *b) {
	// TODO
	double num1;
	double num2;
	num1 = atof(*(const char **)a);
	num2 = atof(*(const char **)b);
	if (num1 > num2) {
		return 1;
	}
	if (num1 == num2) {
		return 0;
	}
	return -1;
}

/**
 * Compares two char arrays passed in as void pointers and returns an integer
 * representing their ordering.
 * First casts the void pointers to char* pointers (i.e. char**).
 * Returns the result of calling strcmp on them.
 */

int str_cmp(const void *a, const void *b) {
	return strcmp(*(const char **)a, *(const char **)b);
}

/**
 * Swaps the values in two pointers.
 *
 * Casts the void pointers to character types and works with them as char
 * pointers for the remainder of the function.
 * Swaps one byte at a time, until all 'size' bytes have been swapped.
 * For example, if ints are passed in, size will be 4. Therefore, this function
 * swaps 4 bytes in a and b character pointers.
 */
static void swap(void *a, void *b, size_t size) {
	// TODO
	char* achar = (char*)a;
	char* bchar = (char*)b;

	//May need to implement pointer manipulation instead of []
	for (int i = 0; i < size; i++) {
		char temp = *achar;
		*achar = *bchar;
		*bchar = temp;
		achar++;
		bchar++;
	}
}

/**
 * Partitions array around a pivot, utilizing the swap function.
 * Each time the function runs, the pivot is placed into the correct index of
 * the array in sorted order. All elements less than the pivot should
 * be to its left, and all elements greater than or equal to the pivot should be
 * to its right.
 * The function pointer is dereferenced when it is used.
 * Indexing into void *array does not work. All work must be performed with
 * pointer arithmetic.
 */
static int lomuto(void *array, int left, int right, size_t elem_sz,
		int (*comp) (const void*, const void*)) {
	// TODO
	int i,j;
	switch(elem_sz)
	{
	case 0:
		//STRING
		i = left;
		for(j = left + 1; j <= right; ++j) {
			if(comp( ((char**) array + j), ((char**) array + left) ) < 0) {
				++i;
				swap(((char**) array + i), ((char**) array + j), sizeof(char *));
			}
		}
		swap(((char**) array + left), ((char**) array + i), sizeof(char *));
		break;

	case 1:
		//INT
		i = left;
		for(j = left + 1; j <= right; ++j) {
			if(comp( ((char**) array + j), ((char**) array + left) ) < 0) {
				++i;
				swap(((char**) array + i), ((char**) array + j), sizeof(int));
			}
		}
		swap(((char**) array + left), ((char**) array + i), sizeof(int));
		break;

	case 2:
		//DOUBLE
		i = left;
		for(j = left + 1; j <= right; ++j) {
			if(comp( ((char**) array + j), ((char**) array + left) ) < 0) {
				++i;
				swap(((char**) array + i), ((char**) array + j), sizeof(double));
			}
		}
		swap(((char**) array + left), ((char**) array + i), sizeof(double));
		break;

	}
	return i;
}

/**
 * Sorts with lomuto partitioning, with recursive calls on each side of the
 * pivot.
 * This is the function that does the work, since it takes in both left and
 * right index values.
 */
static void quicksort_helper(void *array, int left, int right, size_t elem_sz,
		int (*comp) (const void*, const void*)) {
	// TODO
	if (left < right) {
		int partition;
		partition = lomuto(array, left, right, elem_sz, comp);

		quicksort_helper(array, left, partition, elem_sz, comp);
		quicksort_helper(array, partition+1, right, elem_sz, comp);
	}
}

/**
 * Quicksort function exposed to the user.
 * Calls quicksort_helper with left = 0 and right = len - 1.
 */
void quicksort(void *array, size_t len, size_t elem_sz,
		int (*comp) (const void*, const void*)) {
	// TODO
	quicksort_helper(array, 0, len-1, elem_sz, comp);

}
