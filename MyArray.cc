/********************************************************************
  Author:        Scott Henderson Dana Vrajitoru, IUSB, CS
  Class:         C243, Fall 2016
  File name:     MyArray.cc
  Last updated:  August 29, 2016.
  Description:   Implementation of a class that implements a safe array.
  Note:          See MyArray.h notes for more details of additional
                 functionality provided by Scott Henderson.
*********************************************************************/

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "MyArray.h"
using namespace std;

// Constructor with given size, can be used as default constructor.
MyArray::MyArray(int theSize)
{
    // initialize the object as empty
    array = NULL;
    size = 0;
	// seed the rand function using time
	srand(time(NULL));
    // then use the resize function to allocate the memory
    resize(theSize);
} // MyArray::MyArray()

// Destructor. If the array is not empty, it must be deallocated.
MyArray::~MyArray()
{
    // call the function empty instead, so we only need to modify in
    // one place if anything changes
    empty();
} // MyArray::~MyArray()

// Copy constructor: initializes the target object with the size of
// the object data and copies the content of the object data into the
// target object.
MyArray::MyArray(const MyArray& data)
    : size(data.size) // initialize the size
{
    // allocate the array
    array = new int[size];

    // copy all the values from data
    for (int i = 0; i < size; i++)
        array[i] = data.array[i];
} // MyArray::MyArray()

// Assignment operator: if the object data is different from the
// target object, initializes the target object with the size of the
// object data and copies the content of the object data.
MyArray& MyArray::operator=(const MyArray &data)
{
    // check that we're not trying to copy an object onto itself
    if (this != &data) // different address in the memory
    {
        resize(data.size);
        for (int i=0; i<size; i++)
            array[i] = data.array[i];
    }
    else
        cout << "Attempt to copy an object on itself. "
             << "Operation ignored." << endl;
    return *this;
} // MyArray::operator=()

// Overloads the == operator. Returns false if the arrays
// are not equal or if any elements in a corresponding index
// are not equal. Returns true if every value in each
// corresponding array index is equal.
bool MyArray::operator==(const MyArray &data) const
{
    // if array sizes are not equal
    if (this->size != data.size)
    {
        // just return false because sizes not equal
        return false;
    }
    else // otherwise arrays must be equal
    {
        // iterate while less than common size
        for (int i = 0; i < data.size; i++)
        {
            // if any corresponding elements are ever unequal
            // return false
            if (this->array[i] != data.array[i]) return false;
        }
    }
    // every element must be equal so return true
    return true;
} // MyArray::operator==()

// Overloads the != operator. Simply returns the opposite of
// the value returned by the == operator. (ex. True if false)
bool MyArray::operator!=(const MyArray &data) const
{
    return !(*this == data);
} // MyArray::operator!=()

// Deallocate the array and reset the size to 0
void MyArray::empty()
{
    // make sure we have an array to delete
    if (size != 0 && array != NULL)
    {
        size = 0;
        delete [] array;
        array = NULL; // make the pointer NULL after deallocating
    }
} // MyArray::empty()

// Resize the array with the new size. If the object contains an
// array, it is deallocated first.
void MyArray::resize(int theSize)
{
    if (theSize >= 0)     // check that the new size is valid
    {
        if (size > 0)     // if the array is not empty, deallocate first
            empty();
        if (theSize != 0) // allocate again if the size is not 0
        {
            size = theSize;
            array = new int[size];
        }
    }
    else                  // negative size, give an error message
        cout << "Resize attempted with a negative size. "
             << "Operation ignored." << endl;
} // MyArray::resize()

// Resizes the array based on the "theSize" parameter,
// then instantiates the array by storing a a random integer
// between 0 and limit exclusive in each index.
// Note that limit defaults to 100 if not specified.
void MyArray::randomize(int theSize, int limit)
{
    if (size != theSize) // if desired size is different than current size
        resize(theSize);   // then resize

    for(int i = 0; i < size; i++) //store random ints in each index
    {
        // generate number between 0 and limit exclusive
        array[i] = rand() % (limit - 1) + 1;
    }
} //MyArray::randomize()

void MyArray::QuickSort(int low, int hi) {
	int i = low, j = hi;
	int pivot = array[((hi + low) / 2)];

	while (i <= j) {
		while (array[i] < pivot) i++;
		while (array[j] > pivot) j--;
		if (i <= j) {
			Swap(i++, j--);
		}
	}
	if (low < j) QuickSort(low, j);
	if (i < hi) QuickSort(i, hi);
} // QuickSort

void MyArray::Swap(int in1, int in2) {
	int temp = array[in1];
	array[in1] = array[in2];
	array[in2] = temp;
} // Swap

// Access an element of the array. If the index (subscript) is out
// of the array, it prints an error message and exits the program.
int& MyArray::operator[](int index) const
{
    // check that the index is in the right range
    if (index >= 0 && index < size)
        return array[index];
    else // error
    {
        cerr << "Illegal access to an element of the array." << endl
             << "The size of the array was " << size
             << " and the index was " << index << endl;
        exit(1);
    }
} // MyArray::operator[]()

// Returns the size of the array.
int MyArray::getSize() const
{
    return size;
} // MyArray::getSize()

// Resizes array based on input from user and then instantiates
// each element of the array with user-provided data.
void MyArray::input()
{
    // theSize stores desired array size, iValue stores desired index value
    int theSize(0), iValue(0);
    // prompt user for array size
    cout << "Enter the desired size for new array: ";
    cin >> theSize;
    // resize the current array with user's desired size
    resize(theSize);
    // prompt to begin filling array
    cout << "\nFill in your newly allocated array:" << endl;
    for (int i = 0; i < size; i++)
    {
        // prompt for value of current index
        cout << "\nEnter value for index " << i << ": ";
        cin >> iValue;     // retrieve user value
        array[i] = iValue; // store value in current index
    }
}// MyArray::input()

// Output the elements of the array.
void MyArray::output() const
{
    // output the size
    cout << "The array of size " << size
         << " contains the elements:" << endl;
    // then all the elements
    for (int i = 0; i < size; i++)
        cout << array[i] << ' ';
    cout << endl;
} // MyArray::output()

// ScalarProduct() multiplies two arrays together or, rather,
// each corresponding index, and returns the sum of each product.
// If the arrays are not equal, the length becomes that of the
// smallest of the two arrays.
int MyArray::scalarProduct(const MyArray& data) const
{
    // sum stores the total sum of the products
    int sum = 0;
    // length is either common length if equal or the smallest common length
    // if unequal
    int length = (this->size > data.size) ? data.size : this->size;
    // begin iterating through the arrays
    for (int i = 0; i < length; i++)
    {
        // sum is the current sum plus the product of the two indices
        sum += (this->array[i] * data.array[i]);
    }
    return sum;
}// MyArray::scalarProduct()

// We define this so that we can write "cout << a;" if a is an object
// of this class. This is not a class method.
ostream& operator<<(ostream& out, const MyArray& data)
{
    // output the size
    out << "The array of size " << data.size
        << " contains the elements:" << endl;
    // then all the elements
    for (int i = 0; i < data.size; i++)
        out << data.array[i] << ' ';
    out << endl;
    return out;
} // operator<<()

// Overload extraction operator from istream to allow for
// std::cin input from user (ex. "std::cin >> a" )
// Rather than use "in" object to assign every element,
// we call defined input method which handles such a task
istream& operator>>(istream& in, MyArray& data)
{
    // note that simply calling data.input() would perform
    // the same as the below implementation
    // data.input();

    // prompt for desired size
    cout << "Enter desired size for array: ";
    in >> data.size;
    // resize based on value stored in data.size
    data.resize(data.size);
    for (int i = 0; i < data.size; i++)
    {
        // prompt for value to be stored in current index
        cout << "\nEnter value for index " << i << ": ";
        // store entered value in current index
        in >> data.array[i];
    }
    return in;
} // operator>>()
