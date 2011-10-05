#ifndef _MCL_error_messages_h_
#define _MCL_error_messages_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

namespace mcl {
extern const char* ERROR_MESSAGES[];
}

#define _MCL_ERR_INTEGER_WRAP_                mcl::ERROR_MESSAGES[0]
#define _MCL_ERR_INVALID_REF_COUNT_           mcl::ERROR_MESSAGES[1]
#define _MCL_ERR_OUT_OF_MEMORY_               mcl::ERROR_MESSAGES[2]
#define _MCL_ERR_OUT_OF_BOUNDS_               mcl::ERROR_MESSAGES[3]

#endif // _MCL_error_messages_h_

// Local Variables:
// mode:C++
// End:
