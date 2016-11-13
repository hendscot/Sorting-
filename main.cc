#include <iostream>
#include "MyArray.h"

int main (int argc, char* argv[]) {
	int size = 10;
	MyArray* arr = new MyArray();

	arr->randomize(size, 100);

	arr->output();

	// SelectionSort(array);
	arr->QuickSort (0, (size - 1));

	arr->output();

	getchar();
	return 0;
}
