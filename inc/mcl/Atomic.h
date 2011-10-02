#ifndef _MCL_Atomic_h_
#define _MCL_Atomic_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

/**
 * Macros for atomic operations
 */

#include <mcl/config.h>

#if _MCL_ARCH == _MCL_ARCH_X86

#ifdef _MCL_MASM_SYNTAX
#include <mcl/arch/Atomic_i486_masm.h>
#else
#include <mcl/arch/Atomic_i486_att.h>
#endif

#else

#error "Unknown architecture"

#endif

#endif // _MCL_Atomic_h_

// Local Variables:
// mode:C++
// End:
