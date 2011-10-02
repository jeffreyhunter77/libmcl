#ifndef _MCL_OutOfMemoryException_h_
#define _MCL_OutOfMemoryException_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

#include <Exception.h>
#include <error_messages.h>

namespace mcl {
  
/**
 * OutOfMemoryException indicates an attempt to allocate memory failed.
 */
class OutOfMemoryException : public Exception {

public:
  
  /** Contructor */
  OutOfMemoryException() { }
  
  /** Return the message associated with this exception */
  const char* message() const { return _MCL_ERR_OUT_OF_MEMORY_; }

};

} // namespace


#endif // _MCL_OutOfMemoryException_h_


// Local Variables:
// mode:C++
// End:
