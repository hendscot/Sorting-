/********************************************************************
  Author:        Scott Henderson and Dr. Dana Vrajitoru, IUSB, CS
  Class:         C243, Fall 2016
  File name:     MyArray.h
  Last updated:  August 29, 2016.
  Description:   Definition of a class that implements a safe array.
  Notes:         Notable changes made to Dr. Vrajitoru's files:

                 1. const correctness for reference variables and
                    methods when applicable. (not necessary but
                    preferred).

                 2. The addition of the input, randomize, and
                    scalarProduct methods, as well as overloaded
                    definitions for the equality ( == ), inequality
                    ( != ) and extraction ( >> ) operators.
*********************************************************************/

#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <iostream>
using namespace std;

class MyArray
{
protected:
    int  size;
    int* array;

public:
    // Constructor with given size, can be used as default constructor.
    MyArray(int theSize = 0);

    // Destructor. If the array is not empty, it must be deallocated.
    ~MyArray();

    // Copy constructor
    MyArray(const MyArray &data);

    // Assignment operator
    MyArray& operator=(const MyArray& data);

    // Equality ( == ) operator overload
    bool operator==(const MyArray& data) const;

    // Inequality ( != ) operator overload
    bool operator!=(const MyArray& data) const;

    // Deletes the array and sets the size to 0.
    void empty();

    // Resize the array.
    void resize(int theSize = 0);

	void QuickSort(int, int);
	
	void Swap(int, int);

    // Resize and initialize array with random elements
    // Random limit defaults to 100 if not specified
    void randomize(int theSize, int limit = 100);

    // Access an element of the array. If the index (subscript) is out
    // of the array, it prints an error message and exits the program.
    int& operator[](int index) const;

    // Returns the size of the array.
    int getSize() const;

    // Creates a new array of a user-defined size (prompts for input) and
    // initalizes the array with values from user input
    void input();

    // Output the elements of the array.
    void output() const;

    // Multiply corresponding array indices and return sum of all products
    int scalarProduct(const MyArray& data) const;

    // We define this so that we can write "cout << a;" if a is an
    // object of this class.
    friend ostream &operator<<(ostream &out, const MyArray &data);

    // Overload istream's >> extraction operator.
    friend istream &operator>>(istream &in, MyArray &data);
}; // class MyArray

#endif //MY_ARRAY_H
