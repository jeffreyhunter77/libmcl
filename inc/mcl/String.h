#ifndef _MCL_String_h_
#define _MCL_String_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

/**
 * String
 *
 * An immutable string class implementation.
 */

#include <mcl/OutOfBoundsException.h>
#include <mcl/Atomic.h>

namespace mcl {

/**
 * StringRef is a sharable reference to a block of data. The String
 * class uses it to allow multiple instances to reference the same
 * string of data.  When StringRef goes out of scope, any data it
 * references is deleted also.
 */
class StringRef {

public:

  /** The reference count. */
  int refCount;

  /** The size of data. */
  size_t size;
  
  /** The referenced data. */
  char* data;

  /** When set, data will never be deleted (useful for constants) */
  bool dataFrozen;

  /** Constructor for a data block (automatcially deleted by destructor). */
  StringRef(size_t size, char* data, bool dataFrozen = false)
    : refCount(1), size(size), data(data), dataFrozen(dataFrozen) { }

  /** Destructor */
  ~StringRef() { if (data && !dataFrozen) delete [] data; }
};

/**
 * String is an immutable string.  String is intended as an
 * object-oriented version of a C null-terminated string.  It is
 * designed to be as interoperable as possible with ordinary C
 * strings.  The data in a String is always null-terminated, however
 * it also contains the size of the string, so it may be used to hold
 * "strings" (really any block of data) with embedded nulls.
 *
 * Multiple instances of a String may point to the same data.  This
 * allows for efficient copying and assigning of a String.  Because
 * the string is not mutable, use of a String in a multithreaded
 * environment is less complex than other string implementations such
 * as the string class in the STL.
 *
 * Although at first the internal implementation of the string may seem complex, and the need for immutability may not seem so clear, the real advantage of this approach is that strings can be treated like (and behave almost as efficiently as) a primitive data type. As a simple usage example:
 *
 * <code>
 * String maxString(String a, String b) {
 *   if (b > a)
 *     return b;
 *   else
 *     return a;
 * }
 *
 * void callingFunction() {
 *   char* a = new char[6];
 *   char* b = new char[6];
 *
 *   sranddev();
 *
 *   for (int i = 0; i < 5; i++) {
 *     a[i] = (rand() % 95) + 32;
 *     b[i] = (rand() % 95) + 32;
 *   }
 *   a[5] = '\0';
 *   b[5] = '\0';
 *
 *   cout << "a = \"" << a << "\"" << endl;
 *   cout << "b = \"" << b << "\"" << endl;
 *
 *   String max = maxString(a, b);
 *
 *   delete [] a;
 *   delete [] b;
 *
 *   cout << "max = \"" << max << "\"" << endl;
 * }
 * </code>
 *
 * There are a couple of points that this code illustrates, the first is
 * that the <tt>maxString</tt> function accepts as its parameters and
 * returns Strings, not String pointers or references. Using a string
 * reference is, of course, perfectly fine for an output parameter, but
 * it isn't needed otherwise. The other point intentionally being
 * illustrated here is that even though the value used to create a String
 * goes out of scope, the String still contains the original value and
 * can be used without concern. A String creates its own copy of the data
 * (which can be shared by many other string instances) and that data is
 * automatically freed when the last String instance that uses it goes
 * out of scope.
 */
class String {

public:

  // constructors
  String();
  String (const String& str);
  String (const String& str, long offset);
  String (const String& str, long offset, long len);
  String (const char* str);
  String (const char* str, size_t len);
  String (char c, size_t repeat = 1);

  // destructor
  ~String();

  // accessors
  const char* data() const     { return ref->data; }
  operator const char*() const { return ref->data; }
  size_t size() const          { return ref->size; }

  // hashing
  static size_t hash(const String& str);

  // character accessors
  char charAt(size_t pos) const
    { checkBounds(pos); return ref->data[pos]; }
  /* uses operator const char* -- dumb
  char operator[](size_t pos) const
    { checkBounds(pos); return m_ref->m_data[pos]; }
  */

  // substring
  String substring(long offset) const;
  String substring(long offset, long len) const;

  // assignment operations
  String& operator=(const String& str) { assign(str); return *this; }
  String& operator=(const char* str)    { assign(str); return *this; }
  void assign(const String& str);
  void assign(const char* str);
  void assign(const String& str, long offset)
    { assign(str, offset, (offset < 0 ? 0 - offset : str.size() + offset)); }
  void assign(const String& str, long offset, long len);
  void assign(const char* str, size_t len);
  void assign(char c, size_t repeat = 1);
  
  // comparison routines
  bool operator==(const String& str) const { return (compare(str) == 0); }
  bool operator<(const String& str)  const { return (compare(str) < 0); }
  bool operator>(const String& str)  const { return (compare(str) > 0); }
  int compare(const String& str) const;

  bool operator==(const char* str) const { return (compare(str) == 0); }
  bool operator<(const char* str)  const { return (compare(str) < 0); }
  bool operator>(const char* str)  const { return (compare(str) > 0); }
  int compare(const char* str) const;

 protected:
  inline void checkBounds(size_t pos) const;
  inline bool acquireReference(StringRef* ref);
  inline bool releaseReference(StringRef* ref);
  void release();

  StringRef* ref;
};

/**
 * Ensures that pos is within the bounds of this string.  An
 * OutOfBoundsException is thrown otherwise.
 */
inline void String::checkBounds(size_t pos) const {
  if (!ref)
    throw OutOfBoundsException(0, 0, pos);
  if ((pos < 0) || (pos >= ref->size))
    throw OutOfBoundsException(0, ref->size - 1, pos);
}

/**
 * Acquire a string reference by incrementing its count
 */
inline bool String::acquireReference(StringRef* ref) {
  int* countPtr = &(ref->refCount);
  int countWas = 0;

  AtomicAdd(countPtr, 1, countWas);

  return (countWas >= 1);
}

/**
 * Release a string reference by decrementing its count.  Returns true
 * if the reference has gone out of scope (should be deleted following
 * our release).
 */
inline bool String::releaseReference(StringRef* ref) {
  int* countPtr = &(ref->refCount);
  int countWas = 0;

  AtomicAdd(countPtr, -1, countWas);

  return (countWas <= 1);
}

} // namespace


#endif // _MCL_String_h_


// Local Variables:
// mode:C++
// End:
