// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include <mcl/Vector.h>

using namespace mcl;

typedef Vector<int> IntVector;

/**
 * Constructor tests
 */
void testConstructor() {
  
  IntVector empty;
  assert(empty.size() == 0);
  
  IntVector copy1;
  copy1.push(0);
  copy1.push(1);
  copy1.push(2);
  IntVector copy2(copy1);
  assert(copy2.size() == 3);
  assert(copy2[0] == 0);
  assert(copy2[1] == 1);
  assert(copy2[2] == 2);
  
  IntVector copy3(empty);
  assert(copy3.size() == 0);
}

/**
 * item() and operator[] tests
 */
void testItem() {
  IntVector numbers;
  numbers.push(5);
  numbers.push(4);
  numbers.push(3);
  numbers.push(2);
  numbers.push(1);

  IntVector numbersCopy = numbers;
  assert(numbersCopy.item(1) == 4);
  numbersCopy.item(1) = 40;
  assert(numbersCopy.item(1) == 40);
  
  try {
    numbersCopy.item(5);
    fprintf(stderr, "Did not generate OutOfBoundsException on invalid item() access.\n");
    exit(1);
  } catch (OutOfBoundsException&) {
    // expected
  }

  numbersCopy = numbers;
  assert(numbersCopy[1] == 4);
  numbersCopy[1] = 40;
  assert(numbersCopy[1] == 40);

  try {
    numbersCopy[5];
    fprintf(stderr, "Did not generate OutOfBoundsException on invalid [] access.\n");
    exit(1);
  } catch (OutOfBoundsException&) {
    // expected
  }

  numbersCopy = numbers;
  const IntVector& numbersRef = numbersCopy;
  assert(numbersRef.item(1) == 4);
  
  try {
    numbersRef.item(5);
    fprintf(stderr, "Did not generate OutOfBoundsException on invalid item() const access.\n");
    exit(1);
  } catch (OutOfBoundsException&) {
    // expected
  }

  assert(numbersRef[1] == 4);

  try {
    numbersRef[5];
    fprintf(stderr, "Did not generate OutOfBoundsException on invalid [] const access.\n");
    exit(1);
  } catch (OutOfBoundsException&) {
    // expected
  }
}

/**
 * append() tests
 */
void testAppend() {
  IntVector v;
  v.push(0);
  v.append(5);
  
  assert(v.size() == 2);
  assert(v[0] == 0);
  assert(v[1] == 5);
}

/**
 * prepend() tests
 */
void testPrepend() {
  IntVector v;
  v.push(0);
  v.prepend(5);
  
  assert(v.size() == 2);
  assert(v[0] == 5);
  assert(v[1] == 0);
}

/**
 * insert() tests
 */
void testInsert() {
  // insert middle
  IntVector v;
  v.push(2);
  v.push(6);
  v.insert(1, 4);
  
  assert(v.size() == 3);
  assert(v[0] == 2);
  assert(v[1] == 4);
  assert(v[2] == 6);

  // insert beginning
  v.insert(0, 0);
  assert(v.size() == 4);
  assert(v[0] == 0);
  assert(v[1] == 2);
  assert(v[2] == 4);
  assert(v[3] == 6);
  
  // insert end
  v.insert(4, 8);
  assert(v.size() == 5);
  assert(v[0] == 0);
  assert(v[1] == 2);
  assert(v[2] == 4);
  assert(v[3] == 6);
  assert(v[4] == 8);
  
  // invalid index
  try {
    v.insert(10, 100);
    fprintf(stderr, "Allowed insertion at invalid index\n");
    exit(1);
  } catch (OutOfBoundsException&) {
    // expected
  }
}

/**
 * push() tests
 */
void testPush() {
  IntVector v;
  v.insert(0, 0);
  v.push(5);
  
  assert(v.size() == 2);
  assert(v[0] == 0);
  assert(v[1] == 5);
}

/**
 * unshift() tests
 */
void testUnshift() {
  IntVector v;
  v.push(0);
  v.unshift(5);
  
  assert(v.size() == 2);
  assert(v[0] == 5);
  assert(v[1] == 0);
}

/**
 * remove() tests
 */
void testRemove() {
  IntVector v;
  v.push(1);
  v.push(2);
  v.push(3);
  v.push(4);
  v.push(5);

  // middle
  int i = v.remove(2);
  assert(i == 3);
  assert(v.size() == 4);
  assert(v[0] == 1);
  assert(v[1] == 2);
  assert(v[2] == 4);
  assert(v[3] == 5);
  
  // beginning
  i = v.remove(0);
  assert(i == 1);
  assert(v.size() == 3);
  assert(v[0] == 2);
  assert(v[1] == 4);
  assert(v[2] == 5);
  
  // end
  i = v.remove(2);
  assert(i == 5);
  assert(v.size() == 2);
  assert(v[0] == 2);
  assert(v[1] == 4);
  
  // bad index
  try {
    i = v.remove(10);
    fprintf(stderr, "Allowed removal of non-existent index.\n");
    exit(1);
  } catch (OutOfBoundsException&) {
    // expected
  }
}

/**
 * removeLast() tests
 */
void testRemoveLast() {
  IntVector v;
  v.push(1);
  v.push(2);
  v.push(3);
  
  assert(v.removeLast() == 3);
  assert(v.removeLast() == 2);
  assert(v.removeLast() == 1);
  
  try {
    v.removeLast();
    fprintf(stderr, "Allowed removeLast on empty list.\n");
  } catch (OutOfBoundsException&) {
    // expected
  }
}

/**
 * pop() tests
 */
void testPop() {
  IntVector v;
  v.push(1);
  v.push(2);
  v.push(3);
  
  assert(v.pop() == 3);
  assert(v.pop() == 2);
  assert(v.pop() == 1);
  
  try {
    v.pop();
    fprintf(stderr, "Allowed pop on empty list.\n");
  } catch (OutOfBoundsException&) {
    // expected
  }
}

/**
 * shift() tests
 */
void testShift() {
  IntVector v;
  v.push(1);
  v.push(2);
  v.push(3);
  
  assert(v.shift() == 1);
  assert(v.shift() == 2);
  assert(v.shift() == 3);
  
  try {
    v.shift();
    fprintf(stderr, "Allowed shift on empty list.\n");
  } catch (OutOfBoundsException&) {
    // expected
  }
}

/**
 * clear() tests
 */
void testClear() {
  IntVector v;
  v.push(0);
  v.push(1);
  v.push(2);
  
  v.clear();
  
  assert(v.size() == 0);
  
  // test empty
  v.clear();
  assert(v.size() == 0);
}

/**
 * operator=() tests
 */
void testAssignment() {
  IntVector orig;
  orig.push(1);
  orig.push(2);
  orig.push(3);
  
  IntVector copy;
  copy = orig;
  
  assert(copy.size() == 3);
  assert(copy[0] == 1);
  assert(copy[1] == 2);
  assert(copy[2] == 3);
}

/**
 * operator== tests
 */
void testEquality() {
  IntVector orig;
  orig.push(1);
  orig.push(2);
  orig.push(3);
  
  IntVector copy;
  copy.push(1);
  copy.push(2);
  copy.push(3);
  
  assert(orig == copy);
  
  IntVector tooShort;
  tooShort.push(1);
  tooShort.push(2);
  
  assert(! (tooShort == orig));
  
  IntVector differentValues;
  differentValues.push(1);
  differentValues.push(2);
  differentValues.push(4);
  
  assert(! (differentValues == orig));
}

/**
 * operator!= tests
 */
void testInequality() {
  IntVector orig;
  orig.push(1);
  orig.push(2);
  orig.push(3);
  
  IntVector copy;
  copy.push(1);
  copy.push(2);
  copy.push(3);
  
  assert(! (orig != copy));
  
  IntVector tooShort;
  tooShort.push(1);
  tooShort.push(2);
  
  assert(tooShort != orig);
  
  IntVector differentValues;
  differentValues.push(1);
  differentValues.push(2);
  differentValues.push(4);
  
  assert(differentValues != orig);
}

/**
 * grow() tests
 */
void testGrow() {
  IntVector longList(16);
  
  longList.push(1);
  longList.push(2);
  longList.push(3);
  longList.push(4);
  longList.push(5);
  longList.push(6);
  longList.push(7);
  longList.push(8);
  longList.push(9);
  longList.push(10);
  longList.push(11);
  longList.push(12);
  longList.push(13);
  longList.push(14);
  longList.push(15);
  longList.push(16);
  longList.push(17); // automatically grown here
  longList.push(18);
  longList.push(19);
  longList.push(20);
  longList.push(21);
  longList.push(22);
  longList.push(23);
  longList.push(24);

  assert(longList.size() == 24);
  assert(longList[0] == 1);
  assert(longList[1] == 2);
  assert(longList[2] == 3);
  assert(longList[3] == 4);
  assert(longList[4] == 5);
  assert(longList[5] == 6);
  assert(longList[6] == 7);
  assert(longList[7] == 8);
  assert(longList[8] == 9);
  assert(longList[9] == 10);
  assert(longList[10] == 11);
  assert(longList[11] == 12);
  assert(longList[12] == 13);
  assert(longList[13] == 14);
  assert(longList[14] == 15);
  assert(longList[15] == 16);
  assert(longList[16] == 17);
  assert(longList[17] == 18);
  assert(longList[18] == 19);
  assert(longList[19] == 20);
  assert(longList[20] == 21);
  assert(longList[21] == 22);
  assert(longList[22] == 23);
  assert(longList[23] == 24);
}

int main(int argc, char** argv) {
  
  testConstructor();
  testItem();
  testAppend();
  testPrepend();
  testInsert();
  testPush();
  testUnshift();
  testRemove();
  testRemoveLast();
  testPop();
  testShift();
  testClear();
  testAssignment();
  testEquality();
  testInequality();
  testGrow();
  
  return 0;
}
