#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
// The size of our RNG'd array.
#define arr_size 10

/**
 * A more simple/readable implemenation of Bogosort
 * that doesn't have any print statements or timing.
 */

int arr[arr_size];

/*
 * Swaps array values at indices a and b
 */
void swap(int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}

/**
 * Creates a random array, runs bogosort and times the process.
 */
int main(int argc, char **argv) {

	// Seed the RNG
	srand(time(NULL));
	
	// Randomly generate an array.
	for (int i = 0; i < arr_size; i++) {
		arr[i] = -1;
	}
	for (int i = 0; i < arr_size; i++) {
		bool assigned = false;
		while (!assigned) {
			int index = rand() % arr_size;
			if (arr[index] == -1) {
				arr[index] = i;
				assigned = true;
			}
		}
	}

	// True if array is sorted.
	bool sorted = false;
	
	// Actual bogosort	
	while (!sorted) {
		sorted = true;
		
		// Check if array is sorted
		for (int i = 0; i < arr_size - 1; i++) {

			if (arr[i] > arr[i+1]) {
				sorted = false;
			}
		}
		
		// Shuffle the array.
		// Using the Fisher-Yates shuffle.
		for (int i = 0; i < arr_size-2; i++) {
			int range = arr_size - i;
			int random = (rand() % range) + i;
			swap(i, random);
		}
		
	}
	return 0;
}
