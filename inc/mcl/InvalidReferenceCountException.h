#ifndef _MCL_InvalidReferenceCountException_h_
#define _MCL_InvalidReferenceCountException_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

#include <mcl/Exception.h>
#include <mcl/error_messages.h>

namespace mcl {
  
/**
 * InvalidReferenceCountException is thrown if a reference is made to
 * data which has already gone out of scope. This exception should not
 * occur under ordinary circumstances (it indicates a serious
 * programming flaw).
 */
class InvalidReferenceCountException : public Exception {

public:
  
  /** Contructor */
  InvalidReferenceCountException() { }
  
  /** Return the message associated with this exception */
  const char* message() const { return _MCL_ERR_INVALID_REF_COUNT_; }

};

} // namespace


#endif // _MCL_InvalidReferenceCountException_h_


// Local Variables:
// mode:C++
// End:
