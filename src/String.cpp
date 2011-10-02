// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

/**
 * String
 *
 * An immutable string class implementation.
 */
#include <String.h>

#include <hash_functions.h>
#include <InvalidReferenceCountException.h>
#include <OutOfMemoryException.h>

#include <string.h>

using namespace mcl;

namespace mcl {
  // global empty string
  StringRef EMPTY_STRING(0, "", true);
}


/**
 * Construct an empty String.
 */
String::String() : ref(&EMPTY_STRING) {
  // the empty string never goes out of scope
  acquireReference(m_ref);
}

/**
 * Construct a String that is a copy of str.
 *
 * @param str The string to copy.
 */
String::String(const String& str) : ref(0) {
  assign(str);
}

/**
 * Construct a String from a null-terminated C string.
 *
 * @param str The null-terminated string to create a copy of.
 */
String::String(const char* str) : ref(0) {
  assign(str);
}

/**
 * Create a substring from str.
 *
 * See substring() for more information on the use of substring
 * parameters.
 *
 * @param str    The string to create the substring from. 
 * @param offset The position in str where the substring should begin (the
 *               first character is 0).
 */
String::String(const String& str, long offset) : ref(0) {
  assign(str, offset);
}

/**
 * Create a substring from str.
 *
 * See substring() for more information on the use of substring
 * parameters.
 *
 * @param str    The string to create the substring from. 
 * @param offset The position in str where the substring should begin (the
 *               first character is 0).
 * @param len    The length of the new substring.
 */
String::String(const String& str, long offset, long len) : ref(0) {
  assign(str, offset, len);
}

/**
 * Create a substring from the data in str.  The new substring extends
 * from the beginning of str for len characters (even if null bytes are
 * encountered).
 *
 * @param str    The string to create the substring from.
 * @param len    The length of the  new substring
 */
String::String(const char* str, size_t len) : ref(0) {
  assign(str, len);
}

/**
 * Construct a string from the character c.  If a repeat count is
 * specified, the character is repeated that number of times
 * (e.g. String('x', 3) creates the equivalent of "xxx").
 *
 * @param c      The character to create the string from.
 * @param repeat The optional parameter specifying the number of times
 *               to repeat c.
 */
String::String(char c, size_t repeat) : ref(0) {
  assign(c, repeat);
}

/**
 * Destructor
 */
String::~String() {
  if (m_ref)
    release();
}

/**
 * Return the hash value of the provided string
 */
size_t String::hash(const String& str) {
  return hash_string(str.ref->data, str.ref->size);
}

/**
 * Create a substring of this String from the given offset to the end of
 * the string. Returns a new String.
 *
 * The value for <tt>offset</tt> may be positive or negative. A positive
 * value begins the substring that many characters from the beginning. A
 * negative value begins the substring that many characters from the end.
 * Specifying an offset before the beginning of the string or after the
 * end will instead begin at the start or end of the string, respectively.
 *
 * Some examples:
 *
 * <code>
 * String letters = "abcdefg";
 *
 * letters.substring(0);    // returns "abcdefg"
 * letters.substring(3);    // returns "defg"
 * letters.substring(-2);   // returns "fg"
 * letters.substring(7);    // returns ""
 * letters.substring(-100); // returns "abcdefg"
 * </code>
 *
 * @param str    The string to create the substring from. 
 * @param offset The position in str where the substring should begin (the
 *               first character is 0).
 */
String String::substring(long offset) const {
  return String(this, offset);
}

/**
 * Create a substring of this String from the given offset up to the
 * specified length. Returns a new String.
 *
 * The value for <tt>offset</tt> may be positive or negative. A positive
 * value begins the substring that many characters from the beginning. A
 * negative value begins the substring that many characters from the end.
 * Specifying an offset before the beginning of the string or after the
 * end will instead begin at the start or end of the string, respectively.
 *
 * The value for <tt>length</tt> may also be positive or negative. A
 * positive value ends the string after that many characters. A negative
 * value omits that many characters from the end of the string. As with
 * offset, specifying a value that would go beyond the end of the string
 * or before the offset will result in a shorter string being returned.
 *
 * Some examples:
 *
 * <code>
 * String letters = "abcdefg";
 *
 * letters.substring(2, 2);   // returns "cd"
 * letters.substring(2, -1);  // returns "cdef"
 * letters.substring(3, 6);   // returns "defg"
 * letters.substring(1, 0);   // returns ""
 * letters.substring(1, -10); // returns ""
 * </code>
 *
 * @param str    The string to create the substring from. 
 * @param offset The position in str where the substring should begin (the
 *               first character is 0).
 */
String String::substring(long offset, long len) const {
  return String(this, offset, len);
}

/**
 * Assign the string str to this instance.
 *
 * @param str The string to assign.
 */
void String::assign(const String& str) {
  // release any current string
  if (ref)
    release();

  // add a reference to str's data
  if (acquireReference(str.ref))
    ref = str.ref;
  else
    throw InvalidReferenceCountException();
}

/**
 * Assign the null-terminated string str to this instance.
 *
 * @param str The string to assign.
 */
void String::assign(const char* str) {
  // release any current string
  if (ref)
    release();

  // create a new reference
  ref = new StringRef(0, 0);
  if (!ref)
    throw OutOfMemoryException();

  // allocate memory for the string
  size_t len = strlen(str);
  ref->data = new char[len + 1];
  if (! ref->data)
    throw OutOfMemoryException();

  // copy the string
  memcpy(ref->data, str, len + 1);
  ref->size = len;
}

/**
 * Assign a substring of str to this instance.  The substring begins
 * at offset and includes len characters.
 *
 * See substring() for more information on the use of substring
 * parameters.
 *
 * @param str    The string to assign.
 * @param offset The position in str where the substring begins (the
 *               first character is 0).
 * @param len    The number of characters from str to include.
 */
void String::assign(const String& str, long offset, long len) {
  // release any current string
  if (ref)
    release();
  
  // for negative parameters, calculate the real values
  if (offset < 0)
    offset += str.size();
  if (len < 0)
    len += str.size() - offset;
  
  // constrain to boundaries
  if (offset < 0)
    offset = 0;
  if (offset > str.size())
    offset = str.size();
  if (len > str.size() - offset)
    len = str.size() - offset;
  if (len < 0)
    len = 0;

  // zero-length strings are a special case
  if (len == 0) {
    ref = &EMPTY_STRING;
    acquireReference(ref);
    return;
  }

  // create a new reference
  ref = new StringRef(0, 0);
  if (!ref)
    throw OutOfMemoryException();

  // allocate memory for the string
  ref->data = new char[len + 1];
  if (! ref->data)
    throw OutOfMemoryException();

  // copy the string
  memcpy(ref->data, &(str.ref->data[offset]), len);
  ref->data[len] = 0; // terminate it
  ref->size = len;
}

/**
 * Assigns a substring from the data in str.  The new substring
 * extends from the beginning of str for len characters (even if null bytes
 * are encountered).
 *
 * @param str    The string to create the substring from.
 * @param len    The length of the  new substring
 */
void String::assign(const char* str, size_t len) {
  // release any current string
  if (ref)
    release();

  // create a new reference
  ref = new StringRef(0, 0);
  if (!ref)
    throw OutOfMemoryException();

  // allocate memory for the string
  ref->data = new char[len + 1];
  if (! ref->data)
    throw OutOfMemoryException();

  // copy the string
  memcpy(ref->data, str, len);
  ref->data[len] = 0; // terminate it
  ref->size = len;
}

/**
 * Assign a string from the character c.  If a repeat count is
 * specified, the character is repeated that number of times
 * (e.g. DString('x', 3) creates the equivalent of "xxx").
 *
 * @param c      The character to create the string from.
 * @param repeat The optional parameter specifying the number
 *               of times to repeat c.
 */
void String::assign(char c, size_t repeat) {
  // release any current string
  if (ref)
    release();

  // create a new reference
  ref = new DStringRef(0, 0);
  if (!ref)
    throw OutOfMemoryException();

  // allocate memory for the string
  ref->data = new char[repeat + 1];
  if (! ref->data)
      throw OutOfMemoryException();

  // copy the string
  memset(ref->data, c, repeat);
  ref->data[repeat] = 0; // terminate it
  ref->size = repeat;
}

/**
 * Compares this string to str.  This uses the standard C library
 * routines, so it does not work with embedded nulls.  The return
 * values are as follows:
 *
 *  - this <  str : a value less than 0
 *  - this == str : 0
 *  - this >  str : a value greater than 0
 *
 * @param str  The string to compare.
 */
int String::compare(const String& str) const {
  return strcmp(data(), str);
}

/**
 * Compares this string to str.  This uses the standard C library
 * routines, so it does not work with embedded nulls.  The return
 * values are as follows:
 *
 *  - this <  str : a value less than 0
 *  - this == str : 0
 *  - this >  str : a value greater than 0
 *
 * @param str  The string to compare.
 */
int String::compare(const char* str) const {
  return strcmp(data(), str);
}

/**
 * Release any reference to the current data.
 */
void String::release() {
  if (ref) {
    if (releaseReference(ref))
      delete ref;
    ref = 0;
  }
}
