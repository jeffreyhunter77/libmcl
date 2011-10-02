#ifndef _MCL_Atomic_i486_masm_h_
#define _MCL_Atomic_i486_masm_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

/**
 * Macros for atomic operations
 *
 * Implementation for Intel 486 or better processors using MASM syntax
 */

/*
 * The exchange and add instruction (Intel/MASM syntax):
 *
 *  XADD dst, src
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
  __asm { \
    __asm mov eax, val \
    __asm mov ebx, incPtr \
    __asm lock xadd dword ptr [ebx], eax \
    __asm mov prevVal, eax \
  }


#endif // _MCL_Atomic_i486_masm_h_

// Local Variables:
// mode:C++
// End:
