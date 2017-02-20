#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// The size of our RNG'd array.
#define arr_size 10

/**
 * Implements Bogosort by swapping whole array.
 * Array is also randomly generated
 */
int arr[arr_size];

// Whether to print iterations.
bool doPrint = true;
// Will print every __th iteration.
// Anything less than 10000 messes up the timing
// (I think.)
int printEvery = 10000;

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
	// Number of times we've checked the array
	unsigned long iterations = 0;
	
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
	
	// Copy the array to another array so I can
	// reference the original later
	int oArr[arr_size];
	for (int i = 0; i < arr_size; i++) {
		oArr[i] = arr[i];
	}
	
	// Start the timer
	clock_t stCycles = clock();
	
	// True if array is sorted.
	bool sorted = false;
	
	// Actual bogosort	
	while (!sorted) {
		iterations++;
		sorted = true;
		
		// Check if array is sorted
		for (int i = 0; i < arr_size - 1; i++) {
			if (doPrint && iterations % printEvery == 0) printf("%d ", arr[i]);
			if (arr[i] > arr[i+1]) {
				sorted = false;
			}
		}
		if (doPrint && iterations % printEvery == 0) printf("%d Iteration: %ld\n", arr[arr_size-1], iterations);
		
		// Shuffle the array.
		// Using the Fisher-Yates shuffle.
		for (int i = 0; i < arr_size-2; i++) {
			int range = arr_size - i;
			int random = (rand() % range) + i;
			swap(i, random);
		}
		
	}
	
	// Stop the timer
	clock_t endCycles = clock();
	// Calculate time in seconds
	double timeDif = 1.0 * (endCycles - stCycles)/CLOCKS_PER_SEC;

	// Print Results
	printf("Sort completed in %ld shuffles and %.2lf s\n", iterations, timeDif);
	printf("Initial Array: ");
	for (int i = 0; i < arr_size; i++) {
		printf("%d, ", oArr[i]);
	}
	printf("\n");
	
	return 0;
}
