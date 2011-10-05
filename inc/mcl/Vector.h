#ifndef _MCL_Vector_h_
#define _MCL_Vector_h_
// Copyright (c) 2007-2011, Jeffrey Hunter
// See the LICENSE file distributed with this work for restrictions.

#include <mcl/OutofMemoryException.h>
#include <mcl/OutofBoundsException.h>
#include <mcl/IntegerWrapException.h>

#include <string.h>

namespace mcl {

/**
 * Vector
 *
 * A simple vector template implementation.  A vector is an
 * array-backed list.  Insertions and deletions are only optimal at
 * the end of the list, but it is fast to access list elements by
 * their index.
 */
template <class T> class Vector {

public:

    inline Vector(int capacity = 16);
    inline Vector(const Vector<T>& list);
    inline ~Vector();

    // accessors
    inline T& item(size_t idx);
    inline T  item(size_t idx) const;
    T& operator[](size_t idx)       { return item(idx); }
    T  operator[](size_t idx) const { return item(idx); }
    size_t size() const { return count; }

    // insertion
    inline void append(const T& item);
    inline void prepend(const T& item);
    inline void insert(size_t before, const T& item);
    inline void push(const T& item)    { append(item); }
    inline void unshift(const T& item) { prepend(item); }

    // deletion
    inline T remove(size_t idx);
    inline T removeLast() { return remove(count - 1); }
    inline T pop() { return remove(count - 1 ); }
    inline T shift() { return remove(0); }
    inline void clear();

    // other operators
    inline Vector<T>& operator=(const Vector<T>& list);
    inline bool operator==(const Vector<T>& list) const;
    inline bool operator!=(const Vector<T>& list) const
        { return (! (*this == list)); }

protected:
    inline void checkBounds(size_t pos) const;
    inline void grow();

    T**    elems;
    size_t count;
    size_t capacity;
};

#include "Vector.cpp"

} // namespace

#endif // _MCL_Vector_h_

// Local Variables:
// mode:C++
// End:
