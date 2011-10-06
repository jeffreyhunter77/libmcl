What Is This?
=============

This is a set of old utility classes written in C++ that I had lying
around and decided to bring out and update a little in case anyone else
finds them interesting or useful.

Essentially these are utility classes that have a different philosophy
behind them than the STL. Mostly I just wanted to toss these out there so
that I had something to reference when talking about approaches that are
different from the STL. There's more code and more information to come at
some point, but for now, there are two classes here: String and Vector.

Classes
=======

String
------

The String class is designed to be as interoperable as possible with
C-style strings. You should treat instances of String largely the same as
a primitive data type (e.g. an `int`), and the mechanics of copying
around the `char*` pointers and deciding when to free up the associated
memory is handled automatically and in a thread-safe matter.

A simple usage example:

    #include <mcl/String.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    
    using namespace mcl;
    using namespace std;
    
    String minString(String a, String b) {
      if (a <= b)
        return a;
      else
        return b;
    }
    
    String boolToString(bool test) {
      return test ? "true" : "false";
    }
    
    int main (int argc, char** argv) {
      // passing and returning strings:
      String string1 = "alpha";
      String string2 = "beta";
      
      String result = minString(string1, string2);
      
      cout << "Between " << string1 << " and " << string2 << ", "
           << result << " is less." << endl;
           
      // outputs: "Between alpha and beta, alpha is less."
      
      
      // interoperability with C functions
      String value = "1234";
      
      int i = atoi(value);
      
      // i set to 1234
      
      
      // usage with printf style routines:
      bool flag = false;
      
      String flagString = boolToString(flag);
      
      printf("flag is set to %s.\n", flagString.data());
      
      // outputs: "flag is set to false."
      
      return 0;
    }

One point in particular that's illustrated here is that most calls which
accept `char*` as an input parameter, don't require any special
conversion of a String. The one exception, however, is functions which
take a variable argument list, such as printf. In that case, the string
has to be explicitly cast as a C-style string.

Another convenient use of the String class is how it can create a copy of
any data block and allow the associated memory to stay allocated until
the last reference to it goes out of scope. A simple example:

    #include <mcl/String.h>
    #include <stdlib.h>
    #include <time.h>
    #include <iostream>
    
    using namespace mcl;
    using namespace std;
    
    String randomString() {
      srand(time(0));
      
      int len = rand() % 50;
      char* str = new char[len];
      
      for (int i = 0; i < len; i++) {
        str[i] = (rand() % 95) + 32;
      }
      
      // This creates a single copy of our data, which will then be
      // shared accross String instances. Note that we're using a
      // specified length here instead of a null terminator:
      
      String result(str, len);
      
      delete[] str; // clean up the memory we allocated
      
      return result;
    }
    
    int main(int argc, char** argv) {
      String random = randomString();
      
      cout << "Our random string: \"" << random << "\"" << endl;
      
      return 0;
    }

For more info on the String class, the best place to look at the moment
is the file inc/mcl/String.h.

Vector
------

The Vector class is sort of like a dynamic version of an array, that is, an array that can grow and shrink as needed. Access to members of a vector by index is efficient, as is adding items to and removing them from the end of the vector (`push` and `pop` operations).

Unlike the String class (which has the benefit of being immutable), assignment and copy operations produce a deep copy. So, it may be more efficient to pass Vector instances by reference, except, of course, when you do want to actually produce a copy of a vector.

Example usage:

    #include <mcl/Vector.h>
    #include <mcl/String.h>
  
    #include <iostream>
  
    using namespace mcl;
    using namespace std;
    
    template <class T> Vector<T> twoWayMerge(Vector<T>& a, Vector<T>& b) {
      Vector<T> result;
      int aI = 0;
      int bI = 0;
      
      while (aI < a.size() || bI < b.size()) {
        if (aI < a.size() && bI < b.size()) {
          
          if (a[aI] <= b[bI]) {
            result.push(a[aI]);
            if (a[aI] == b[bI]) ++bI;
            ++aI;
          } else {
            result.push(b[bI++]);
          }
          
        } else if (aI < a.size()) {
          result.push(a[aI++]);
        } else {
          result.push(b[bI++]);
        }
      }
      
      return result;
    }
    
    int main (int argc, char** argv) {
      Vector<String> list1;
      list1.push("apple");
      list1.push("grapefruit");
      list1.push("orange");
      list1.push("pear");
      
      Vector<String> list2;
      list2.push("apple");
      list2.push("banana");
      list2.push("orange");
      
      Vector<String> merged = twoWayMerge(list1, list2);
      
      cout << "Merged list: ";
      
      for (int i = 0; i < merged.size(); i++) {
        cout << merged[i];
        if (i < merged.size() - 1) cout << ", ";
      }
      
      cout << endl;
      
      // outputs: "Merged list: apple, banana, grapefruit, orange, pear"
      
      return 0;
    }

For more info on the Vector class, the best place to look at the moment
is the file inc/mcl/Vector.h.
