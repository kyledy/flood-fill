/*
* File:        testStackQueue.cpp
* Description: Basic test cases for CPSC 221 2021W2 PA2 - Stack and Queue
*              Add your own code to this!
*
* Date:        2022-02-11 00:37
*
*/

#define CATCH_CONFIG_MAIN
#include <iostream>
#include <cassert>
#include "cs221util/catch.hpp"

#include "stack.h"
#include "queue.h"

using namespace std;

TEST_CASE("Stack::basic functions", "[weight=1][part=stack]") {
  cout << "Testing Stack..." << endl;
  Stack<int> intStack;
  vector<int> result;
  vector<int> expected;
  
  for (int i = 10; i > 0; i--) {
    expected.push_back(i);
  }
  for (int i = 1; i <= 10; i++) {
    intStack.Push(i);
  }
  cout << intStack.Peek() << endl;

  while (!intStack.IsEmpty()) {
    result.push_back(intStack.Pop());
  }
  REQUIRE(result == expected);
}

TEST_CASE("Stack::testing pop limits", "[weight=1][part=stack]") {
  cout << "Testing Stack..." << endl;
  // Stack<int> intStack;
  // vector<int> result;
  // vector<int> expected;
  
  // for (int i = 50; i > 0; i--) {
  //   expected.push_back(i);
  // }
  // for (int i = 1; i <= 50; i++) {
  //   intStack.Push(i);
  // }
  // cout << intStack.Peek() << endl;

  // while (!intStack.IsEmpty()) {
  //    result.push_back(intStack.Pop());
  //    // cout << intStack.Pop() << endl;
  // }
  // REQUIRE(result == expected);
}



TEST_CASE("Queue::basic functions", "[weight=1][part=queue]") {
  cout << "Testing Queue..." << endl;
  Queue<int> intQueue;
  vector<int> expected;
  vector<int> result;
  for (int i = 1; i <= 10; i++) {
    expected.push_back(i);
  }

  // push onto queue
  for (int i = 1; i <= 10; i++) {
     intQueue.Enqueue(i);
  }

  while (!intQueue.IsEmpty()) {
    result.push_back(intQueue.Dequeue());
    // cout << intQueue.Dequeue() << endl;
  }  
  REQUIRE(result == expected);
}

TEST_CASE("Stack::resizing", "[weight=1][part=queue]") {
  cout << "Testing Stack..." << endl;
  Stack<int> intStack;
  vector<int> expected;
  vector<int> result;

  // fills the stack with numbers from 1-10
  for (int i = 1; i <= 10; i++) {
    intStack.Push(i);
  }
  REQUIRE(intStack.Capacity() == 16);

  // fills the stack to its capacity 
  for (int i = 11; i <= 16; i++) {
    intStack.Push(i);
  }
  REQUIRE(intStack.Peek() == 16);
  REQUIRE(intStack.Size() == intStack.Capacity());
  
  // array should have 4 elements at this point, but still has capacity 16
  for (int i = 1; i <= 12; i++) {
    intStack.Pop();
  }
  cout << intStack.Size() << " " << intStack.Capacity() << endl;

  intStack.Pop();
  // size should be 3 and capacity should be 8
  cout << intStack.Size() << " " << intStack.Capacity() << endl;
  // peek should be 3
  cout << intStack.Peek() << endl;
}

TEST_CASE("Queue::peek tests", "[weight=1][part=queue]") {
  cout << "Testing Queue..." << endl;
  Queue<int> intQueue;

  // push onto queue
  for (int i = 1; i <= 10; i++) {
     intQueue.Enqueue(i);
  }

  while (!intQueue.IsEmpty()) {
    intQueue.Dequeue();
  }
}
 

