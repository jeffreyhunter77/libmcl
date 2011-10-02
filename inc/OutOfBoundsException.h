#ifndef _MCL_OutOfBoundsException_h_
#define _MCL_OutOfBoundsException_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

#include <stddef.h>

#include <Exception.h>
#include <error_messages.h>

namespace mcl {
  
/**
 * OutOfBoundsException indicates an attempt to access an item outside
 * of a collection's boundaries (such as attempting to access the
 * 5th element of an array with four elements).
 */
class OutOfBoundsException : public Exception {

public:
  
  /** Contructor */
  OutOfBoundsException(size_t lowerLimit, size_t upperLimit, size_t accessed)
    : lLimit(lowerLimit), uLimit (upperLimit), accessedIdx(accessed) { }
  
  /** Return the message associated with this exception */
  const char* message() const { return _MCL_ERR_OUT_OF_BOUNDS_; }

  /** Return the minimum accessible index */
  size_t lowerLimit() const { return lLimit; }
  /** Return the maximum accessible index */
  size_t upperLimit() const { return uLimit; }
  /** Return the index that was accessed (attempted) */
  size_t accessedIndex() const { return accessedIdx; }

protected:
  size_t lLimit;
  size_t uLimit;
  size_t accessedIdx;
  
};

} // namespace


#endif // _MCL_OutOfBoundsException_h_


// Local Variables:
// mode:C++
// End:
