/*******************************************************************************
 * Name        : sum.c
 * Author      : Maxwell Metzner and Savnick Patel
 * Date        : 5/7/2021
 * Description : Practice using dynamic libraries
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include "sum.h"

/**
 * TODO:
 * Takes in an array of integers and its length.
 * Returns the sum of integers in the array.
 */
int sum_array(int *array, const int length) {
	int count = 0;
	for (int i=0; i <= length; i++) {
		count += array[i];
	}
	return count;
}
