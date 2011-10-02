#ifndef _MCL_Atomic_i486_att_h_
#define _MCL_Atomic_i486_att_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

/**
 * Macros for atomic operations
 *
 * Implementation for Intel 486 or better processors using AT&T syntax
 */

/*
 * The exchange and add instruction (AT&T/GAS syntax):
 *
 *  XADD src, dst
 *
 * works as follows: the two values are swapped and added, then the
 * result is stored in dst.  Because they are first swapped, src is
 * effectively updated to contain the value of dst prior to the
 * operation.  The dst operand may be a register or a memory location,
 * and src must be a register.  The lock prefix used below prevents
 * any other processor from accessing the bus while the instruction is
 * executing, resulting in an atomic operation.
 *
 * (this instruction requires a 486 or better processor)
 */

/*
 * Atomic add macro
 *
 *  incPtr  - dword pointer (int*) to the address to increment
 *  val     - value to add (int)
 *  prevVal - output variable (int) will contain the value of ptr prior to addition
 */
#define AtomicAdd(incPtr, val, prevVal) \
  __asm__ __volatile__ ( \
    "lock\n\t" \
    "xaddl %2, (%1)\n\t" \
    "movl %2, %0" \
    : "=m" (prevVal) \
    : "r" (incPtr), "r" (val) \
    : "memory" )


#endif // _MCL_Atomic_i486_att_h_

// Local Variables:
// mode:C++
// End:
