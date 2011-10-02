#ifndef _MCL_hash_functions_h_
#define _MCL_hash_functions_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

/**
 * Hash functions for use with HashMap
 */

#include <stddef.h>

namespace mcl {
  
size_t hash_string(const char* str);
size_t hash_string(const char* str, size_t len);
size_t hash_int(const int& i);
size_t hash_uint(const unsigned int& i);

} // namespace

#endif // _MCL_hash_functions_h_

// Local Variables:
// mode:C++
// End:
