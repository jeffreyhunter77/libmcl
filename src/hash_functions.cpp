// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

/**
 * Hash functions for use with HashMap
 */

#include <mcl/hash_functions.h>

using namespace mcl;

#define _MCL_STR_HASH_INIT 5381

/**
 * Hash the null-terminated string str.
 *
 * See hash_string(const char*, size_t) for an explanation of
 * the algorigthm.
 *
 * @param str  The string to hash
 *
 * @return The hash value of str
 */
size_t hash_string(const char* str) {
  // Times 33 hash
  register size_t h = _MCL_STR_HASH_INIT;
  while (*str) {
    h = ((h << 5) + h) + *(str++);
  }

  return h;
}

/**
 * Hash the string str.
 *
 * This hash algorithm is attributed to Daniel J. Bernstein and in
 * essence is:
 *
 * <code>
 *  for (i = 0; i < strSize; i++) {
 *    hash = (hash*33) + str[i];
 *  }
 * </code>
 *
 * The implementation below includes two optimizations: the
 * mulitplication is performed as a left shift 5 (equivalent to
 * multiplication by 32) plus a single addition.  The loop is unrolled
 * to work on groups of eight bytes for increased speed.
 *
 * @param str  The string to hash
 * @param len  The length of the string
 *
 * @return The hash value of str
 */
size_t hash_string(const char* str, size_t len) {
  // Times 33 hash
  register size_t h = _MCL_STR_HASH_INIT;
  while (len >= 8) {
    h = ((h << 5) + h) + *(str++);
    h = ((h << 5) + h) + *(str++);
    h = ((h << 5) + h) + *(str++);
    h = ((h << 5) + h) + *(str++);
    h = ((h << 5) + h) + *(str++);
    h = ((h << 5) + h) + *(str++);
    h = ((h << 5) + h) + *(str++);
    h = ((h << 5) + h) + *(str++);
    len -= 8;
  }

  switch (len) {
  case 7:
    h = ((h << 5) + h) + *(str++); // fall through
  case 6:
    h = ((h << 5) + h) + *(str++); // fall through
  case 5:
    h = ((h << 5) + h) + *(str++); // fall through
  case 4:
    h = ((h << 5) + h) + *(str++); // fall through
  case 3:
    h = ((h << 5) + h) + *(str++); // fall through
  case 2:
    h = ((h << 5) + h) + *(str++); // fall through
  case 1:
    h = ((h << 5) + h) + *(str++);
    break;
  default:
    break;
  }

  return h;
}

/**
 * Hash the given integer.
 *
 * @param i    The integer to hash
 *
 * @return The hash value of i
 */
size_t hash_int(const int& i) {
  return (size_t)i;
}

/**
 * Hash the given unsigned integer.
 *
 * @param i    The unsigned integer to hash
 *
 * @return The hash value of i
 */
size_t hash_uint(const unsigned int& i) {
  return (size_t)i;
}


// Local Variables:
// mode:C++
// End:
