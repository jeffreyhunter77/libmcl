// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <mcl/String.h>

using namespace mcl;


/**
 * Constructor tests
 */
void testConstructor() {
  String empty;
  assert(strcmp(empty, "") == 0);
  
  String example1("example");
  assert(strcmp(example1, "example") == 0);

  String example2(example1);
  assert(strcmp(example2, "example") == 0);

  String ample(example1, 2);
  assert(strcmp(ample, "ample") == 0);

  String ple(example1, -3);
  assert(strcmp(ple, "ple") == 0);

  String empty2(example1, 7);
  assert(strcmp(empty2, "") == 0);

  String empty3(example1, 100);
  assert(strcmp(empty3, "") == 0);

  String amp(example1, 2, 3);
  assert(strcmp(amp, "amp") == 0);

  String amp2(example1, 2, -2);
  assert(strcmp(amp2, "amp") == 0);

  String amp3(example1, -5, -2);
  assert(strcmp(amp3, "amp") == 0);

  String ample2(example1, 2, 100);
  assert(strcmp(ample2, "ample") == 0);

  String empty4(example1, 2, -50);
  assert(strcmp(empty4, "") == 0);

  String empty5(example1, 2, 0);
  assert(strcmp(empty5, "") == 0);
  
  String ex("example", 2);
  assert(strcmp(ex, "ex") == 0);
  
  String empty6("example", 0);
  assert(strcmp(empty6, "") == 0);
  
  String x('x');
  assert(strcmp(x, "x") == 0);

  String xxxx('x', 4);
  assert(strcmp(xxxx, "xxxx") == 0);

  String empty7('x', 0);
  assert(strcmp(empty7, "") == 0);
}

/**
 * data() tests
 */
void testData() {
  String foo("foo");
  assert(strcmp(foo.data(), "foo") == 0);
}

/**
 * operator const char*() tests
 */
void testConversionOperator() {
  String foo("foo");
  assert(strcmp(foo, "foo") == 0);
}

/**
 * size() tests
 */
void testSize() {
  String foo("foo");
  assert(foo.size() == 3);
  
  String empty;
  assert(empty.size() == 0);
}

/**
 * charAt() tests
 */
void testCharAt() {
  String foo("foo");
  assert(foo.charAt(0) == 'f');
  assert(foo.charAt(1) == 'o');
  assert(foo.charAt(2) == 'o');
  
  try {
    foo.charAt(3);
    fprintf(stderr, "Invalid string index accessed.\n");
    exit(1);
  } catch (OutOfBoundsException&) {
    // expected
  }
}

/**
 * substring() tests
 */
void testSubstring() {
  String letters = "abcdefg";
  
  assert(letters.substring(0)    == "abcdefg");
  assert(letters.substring(3)    == "defg");
  assert(letters.substring(-2)   == "fg");
  assert(letters.substring(7)    == "");
  assert(letters.substring(-100) == "abcdefg");
  
  assert(letters.substring(2, 2)   == "cd");
  assert(letters.substring(2, -1)  == "cdef");
  assert(letters.substring(3, 6)   == "defg");
  assert(letters.substring(1, 0)   == "");
  assert(letters.substring(1, -10) == "");
}

/**
 * operator=() tests
 */
void testAssignmentOperator() {
  String str1("one");
  String str2("two");
  
  str1 = str2;
  str2 = "three";
  
  assert(str1 == "two");
  assert(str2 == "three");
}

/**
 * assign() tests
 */
void testAssign() {
  String str;
  String example = "example";
  
  
  str.assign("example");
  assert(str == "example");

  str.assign(example);
  assert(str == "example");
  
  str.assign(example, 0);
  assert(str == "example");

  str.assign(example, 2);
  assert(str == "ample");

  str.assign(example, -3);
  assert(str == "ple");

  str.assign(example, 7);
  assert(str == "");
  
  str.assign(example, 100);
  assert(str == "");

  str.assign(example, 2, 3);
  assert(str == "amp");
  
  str.assign(example, 2, -2);
  assert(str == "amp");

  str.assign(example, -5, -2);
  assert(str == "amp");

  str.assign(example, 2, 100);
  assert(str == "ample");

  str.assign(example, 2, -50);
  assert(str == "");

  str.assign(example, 2, 0);
  assert(str == "");
  
  str.assign("example", 2);
  assert(str == "ex");
  
  str.assign("example", 0);
  assert(str == "");
  
  str.assign('x');
  assert(str == "x");
  
  str.assign('x', 4);
  assert(str == "xxxx");

  str.assign('x', 0);
  assert(str == "");
}

/**
 * operator==() tests
 */
void testEqualityOperator() {
  String foo1 = "foo";
  String foo2 = "foo";
  String bar = "bar";
  
  assert(foo1 == foo2);
  assert(foo2 == foo1);
  assert(!(foo1 == bar));
  assert(!(foo2 == bar));
  assert(!(bar == foo1));
  assert(!(bar == foo2));
  
  assert(foo1 == foo1);
  assert(foo2 == foo2);
  assert(bar == bar);
  
  assert(foo1 == "foo");
  assert(foo2 == "foo");
  assert(!(foo1 == "bar"));
}

/**
 * operator!=() tests
 */
void testInequalityOperator() {
  String foo1 = "foo";
  String foo2 = "foo";
  String bar = "bar";
  
  assert(!(foo1 != foo2));
  assert(!(foo2 != foo1));
  assert(foo1 != bar);
  assert(foo2 != bar);
  assert(bar != foo1);
  assert(bar != foo2);

  assert(!(foo1 != foo1));
  assert(!(foo2 != foo2));
  assert(!(bar != bar));
  
  assert(foo1 != "bar");
  assert(foo2 != "bar");
  assert(!(foo1 != "foo"));
}

/**
 * operator<() tests
 */
void testLessThanOperator() {
  String foo1 = "foo";
  String foo2 = "foo";
  String bar = "bar";
  
  assert(bar < foo1);
  assert(!(foo1 < bar));
  assert(!(foo1 < foo2));
  assert(!(foo1 < foo1));
  
  assert(bar < "foo");
  assert(!(foo1 < "bar"));
  assert(!(foo1 < "foo"));
}

/**
 * operator>() tests
 */
void testGreaterThanOperator() {
  String foo1 = "foo";
  String foo2 = "foo";
  String bar = "bar";
  
  assert(foo1 > bar);
  assert(!(bar > foo1));
  assert(!(foo1 > foo2));
  assert(!(foo1 > foo1));

  assert(foo1 > "bar");
  assert(!(bar > "foo"));
  assert(!(foo1 > "foo"));
}

/**
 * operator<=() tests
 */
void testLessThanOrEqualToOperator() {
  String foo1 = "foo";
  String foo2 = "foo";
  String bar = "bar";
  
  assert(foo1 <= foo2);
  assert(foo2 <= foo1);
  assert(!(foo1 <= bar));
  assert(!(foo2 <= bar));
  assert(bar <= foo1);
  assert(bar <= foo2);
  
  assert(foo1 <= foo1);
  assert(foo2 <= foo2);
  assert(bar <= bar);
  
  assert(foo1 <= "foo");
  assert(foo2 <= "foo");
  assert(!(foo1 <= "bar"));
  assert(bar <= "foo");
}

/**
 * operator>=() tests
 */
void testGreaterThanOrEqualToOperator() {
  String foo1 = "foo";
  String foo2 = "foo";
  String bar = "bar";
  
  assert(foo1 >= foo2);
  assert(foo2 >= foo1);
  assert(foo1 >= bar);
  assert(foo2 >= bar);
  assert(!(bar >= foo1));
  assert(!(bar >= foo2));
  
  assert(foo1 >= foo1);
  assert(foo2 >= foo2);
  assert(bar >= bar);
  
  assert(foo1 >= "foo");
  assert(foo2 >= "foo");
  assert(foo1 >= "bar");
  assert(!(bar >= "foo"));
}

/**
 * compare() tests
 */
void testCompare() {
  String foo1 = "foo";
  String foo2 = "foo";
  String bar = "bar";
  
  assert(foo1.compare(foo2) == 0);
  assert(foo1.compare(bar) > 0);
  assert(bar.compare(foo1) < 0);
  assert(foo1.compare(foo1) == 0);

  assert(foo1.compare("foo") == 0);
  assert(foo1.compare("bar") > 0);
  assert(bar.compare("foo") < 0);
}

int main(int argc, char** argv) {

    // run string tests
    testConstructor();
    testData();
    testConversionOperator();
    testSize();
    testCharAt();
    testSubstring();
    testAssignmentOperator();
    testAssign();
    testEqualityOperator();
    testInequalityOperator();
    testLessThanOperator();
    testGreaterThanOperator();
    testLessThanOrEqualToOperator();
    testGreaterThanOrEqualToOperator();
    testCompare();

    return 0;
}

// Local Variables:
// mode:C++
// End:
