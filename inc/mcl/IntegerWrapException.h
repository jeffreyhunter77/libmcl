#ifndef _MCL_IntegerWrapException_h_
#define _MCL_IntegerWrapException_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

#include <mcl/Exception.h>
#include <mcl/error_messages.h>

namespace mcl {
  
/**
 * IntegerWrapException occurs when incrementing or decrementing an
 * integer causes it to wrap around to the other side of zero in a fatal
 * way (such as trying to increase list size beyond the maximum allowable
 * size).
 */
class IntegerWrapException : public Exception {

public:
  
  /** Contructor */
  IntegerWrapException() { }
  
  /** Return the message associated with this exception */
  const char* message() const { return _MCL_ERR_INTEGER_WRAP_; }

};

} // namespace


#endif // _MCL_IntegerWrapException_h_


// Local Variables:
// mode:C++
// End:
