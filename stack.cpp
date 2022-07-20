/*
*  File:        stack.cpp
*  Description: Implementation of the Stack class.
*
*               Complete your implementation in this file
*/

/*
*  Default constructor. Remember to initialize any variables you need
*  and allocate any required memory. The initial size of `items` should
*  be DEFAULTCAPACITY defined in stack.h.
*
*/
#include <iostream>
#include <cassert>

using namespace std;

template <class T>
Stack<T>::Stack()
{  
  // setting private variables 
  max_items = DEFAULTCAPACITY; 
  num_items = -1; // pointer to the top of the stack 

  // allocating the dynamic array
  items = (T*) malloc(sizeof(T) * DEFAULTCAPACITY);
}

/*
*  Destructor. Remember to free any memory allocated.
*/
template <class T>
Stack<T>::~Stack()
{  
  items = NULL;
  delete[] items;
}

/*
*  Adds the parameter object to the top of the Stack. That is, the
*  element should go at the end of the array. If the dynamic array
*  holding the stack elements is full the array should be resized. Resize should be
*  called by multiplying current capacity EXPANSIONFACTOR defined in stack.h.
*  To be clear resize should happen before adding the element to the stack and only
*  when the stack is completely full.
*
*  PARAM: item - the object to be added to the Stack.
*/
template <class T>
void Stack<T>::Push(const T& item) 
{
  // Resizing scheme 
  if (Size() + 1 > max_items) {
    int newSize = max_items * EXPANSIONFACTOR;
    Resize(newSize); 
  }
   
  num_items++; 
  items[num_items] = item;
};

/*
*  Removes the object on top of the Stack, and returns it. That is, remove
*  the element at the end of the array. You may assume this function
*  is only called when the Stack is not empty. If the size of the stack changes
*  to strictly less than a ratio of 1.0 / SHRINKRATE (where SHRINKRATE is defined in stack.h)
*  after the item is removed the Stack should be resized to the larger of max_items / EXPANSIONFACTOR,
*  or DEFAULTCAPACITY.
*
*  RETURN: the element that used to be at the top of the Stack.
*/
template <class T>
T Stack<T>::Pop() 
{
  double shrinkRatio = (double) 1.0 / (double) SHRINKRATE;
  double sizeAfterPop =  (double) (Size() - 1) / (double) max_items;
  T itemToReturn = items[num_items]; // holds the top element of the stack
  num_items--;

  // downsizing scheme
  if (sizeAfterPop < shrinkRatio) {
    int newSize = fmax((max_items / EXPANSIONFACTOR), DEFAULTCAPACITY);
    Resize(newSize);
  }

  return itemToReturn;
};

/*
*  Adds the given element to the ordering structure.
*  See OrderingStructure::Add()
*/
template <class T>
void Stack<T>::Add(const T& item)
{
  // complete your implementation below
  // Hint: this should call another Stack function
  //   to add the element to the Stack.
  Push(item); 
}

/*
*  Removes an element from the ordering structure. You may assume
*  that this function is only called when the ordering structure is
*  not empty.
*  See OrderingStructure::Remove()
*/
template <class T>
T Stack<T>::Remove()
{
  // complete your implementation below
  // Hint: this should call another Stack function
  //   to remove an element from the Stack and return it.
  return Pop();
}

/*
*  Finds the object on top of the Stack, and returns it to the caller.
*  Unlike Pop(), this operation does not alter the Stack itself.
*  It should look at the end of the array. You may assume this function
*  is only called when the Stack is not empty.
* 
*  RETURN: the element at the top of the Stack.
*/
template <class T>
T Stack<T>::Peek() {
  T itemToReturn = items[num_items]; 
  return itemToReturn;
};

/*
*  Determines if the Stack is empty.
*  RETURN: true if the stack is empty,
*          false otherwise.
*/
template <class T>
bool Stack<T>::IsEmpty() const {
  return Size() == 0;
};

/*
*  Return the maximum number of items the stack can hold.
*
*  Note: This is an implementation detail we would normally hide.
*  We include it here for testing purposes.
* 
*  RETURN: maximum number of items the stack can hold (int)
*/
template <class T>
size_t Stack<T>::Capacity() const {
  return max_items;
};

/*
*  Return the number of items on the stack.
*  RETURN: number of items on the stack (int)
*/
template <class T>
size_t Stack<T>::Size() const {
  return num_items + 1;
};

/*
*  Resize the the member variable `items`.
*  The minimum size is the number of items in the Stack.
*  Don't forget to free up any memory that is no longer used.
*  PRE: n >= num_items, i.e. the new size has room for all items in the structure
*  PARAM: n - the capacity of the stack after resizing
*/
template <class T>
void Stack<T>::Resize(size_t n) {
  
  // copying array values to the new array, runs in O(n) time
  T* newArray = (T*) malloc(sizeof(T) * n);
  for (unsigned int i = 0; i < Size(); i++) {
    newArray[i] = items[i];
  }

  delete[] items; 

  // reallocating items to house the new, bigger array 
  items = newArray;
  max_items = n; 
};