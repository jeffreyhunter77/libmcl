#ifndef _MCL_config_h_
#define _MCL_config_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

/**
 * Top-level configuration file
 */

/**
 * Values used in configuration
 */
#define _MCL_ARCH_X86       1

/**
 * Windows configuration
 */
#ifdef WIN32
#define _MCL_MASM_SYNTAX
#endif

/**
 * Optional constants not used under Windows
 */
// _MCL_HAS_GMTIME_R
// _MCL_HAS_TIMEGM

/**
 * General configurable parameters
 */
#define _MCL_ARCH       _MCL_ARCH_X86
#define _MCL_LINE_LIMIT 4096
#define _MCL_EOL        '\n'

#endif // _MCL_config_h_

// Local Variables:
// mode:C++
// End:
