#ifndef _MCL_Exception_h_
#define _MCL_Exception_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

/**
 * Exception
 *
 * An abstract base class for exceptions.
 */

namespace mcl {
  
/**
 * A simple, abstract base class for exceptions. It returns a message
 * describing the error that occurred.
 */
class Exception {

public:
  
  /** Destructor */
  virtual ~Exception() { }
  
  /** Return the message associated with this exception */
  virtual const char* message() const = 0;
};

} // namespace


#endif // _MCL_Exception_h_


// Local Variables:
// mode:C++
// End:
