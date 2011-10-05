/**
 * Default constructor that accepts an optional capacity argument.
 *
 * @param capacity The initial capacity of the vector.
 */
template <class T> inline Vector<T>::Vector(int capacity) : elems(0), count(0), capacity(0) {
  elems = new T*[capacity];
  if (!elems)
    throw OutOfMemoryException();

  this->capacity = capacity;
}

/**
 * Copy constructor.  Performs a deep copy of list.
 *
 * @param list The vector to copy
 */
template <class T> inline Vector<T>::Vector(const Vector<T>& list) : elems(0), count(0), capacity(0) {
  // allocate memory
  elems = new T*[list.capacity];
  if (!elems)
    throw OutOfMemoryException();

  capacity = list.capacity;

  // copy elements
  for (size_t i = 0; i < list.count; i++) {
    elems[i] = new T( *(list.elems[i]) );
    if (!elems[i])
      throw OutOfMemoryException();

    count++;
  }
}

/**
 * Destructor
 */
template <class T> inline Vector<T>::~Vector() {
  clear();
  if (elems)
    delete [] elems;
}

/**
 * Return a reference to the item at index idx.
 *
 * @param idx The index (zero-based) of the item to return.
 *
 * @return The item at idx
 */
template <class T> inline T& Vector<T>::item(size_t idx) {
  checkBounds(idx);
  return *(elems[idx]);
}

/**
 * Return a copy of the item at index idx.
 *
 * @param idx The index (zero-based) of the item to return.
 *
 * @return The item at idx
 */
template <class T> inline T Vector<T>::item(size_t idx) const {
  checkBounds(idx);
  return *(elems[idx]);
}

/**
 * Add a copy of item to the end of the list.
 *
 * @param item The item to add.
 */
template <class T> inline void Vector<T>::append(const T& item) {
  // ensure capacity
  if (count >= capacity)
    grow();

  // create the item we'll hold on to
  T* t = new T(item);
  if (!t)
    throw OutOfMemoryException();

  // put it in the list
  elems[count++] = t;
}

/**
 * Add a copy of item at the beginning of the list.  (This performs a
 * memory move, and so for large lists it may not be an optimal
 * operation.)
 *
 * @param item The item to add.
 */
template <class T> inline void Vector<T>::prepend(const T& item) {
  // ensure capacity
  if (count >= capacity)
    grow();

  // create the item we'll hold on to
  T* t = new T(item);
  if (!t)
    throw OutOfMemoryException();

  // make a space for the item
  if (count)
    memmove(&elems[1], elems, count * sizeof(T*));

  // put it in the list
  elems[0] = t;
  count++;
}

/**
 * Insert a copy of item before the given index (zero-based indexing).
 * If the given index is equal to the size of the list, the item is
 * appended to the end of the list.
 *
 * @param before The position before which the item should be added.
 * @param item   The item to add.
 */
template <class T> inline void Vector<T>::insert(size_t before, const T& item) {
  // check the validity of the index
  if ((before < 0) || (before > count))
      throw OutOfBoundsException(0, count, before);

  // ensure capacity
  if (count >= capacity)
    grow();

  // create the item we'll hold on to
  T* t = new T(item);
  if (!t)
    throw OutOfMemoryException();

  // make a space for the item
  if (before < count)
    memmove(&elems[before + 1], &elems[before], (count - before) * sizeof(T*));

  // put it in the list
  elems[before] = t;
  count++;
}


/**
 * Remove the item at index idx (zero is the index of the first item)
 * from the list.
 *
 * @param idx The index of the item to remove.
 *
 * @return A copy of the removed item.
 */
template <class T> inline T Vector<T>::remove(size_t idx) {
  // validate idx
  checkBounds(idx);

  // save a copy of what we're about to delete
  T t( *(elems[idx]) );

  // delete it
  delete elems[idx];

  // close the hole
  if (idx < (count - 1))
    memmove(&elems[idx], &elems[idx + 1], (count - idx - 1) * sizeof(T*));
  count--;

  return t;
}

/**
 * Remove all items from the list.
 */
template <class T> inline void Vector<T>::clear() {
  while (count)
    delete elems[--count];
}

/**
 * Assignment operator.  Performs a deep copy of list into this list.
 *
 * @param list  The list to copy
 *
 * @return A reference to this list
 */
template <class T> inline Vector<T>& Vector<T>::operator=(const Vector<T>& list) {
  // clear the list
  clear();

  // increase the capacity to hold the new list
  if (capacity < list.count) {
    capacity = 0;
    delete [] elems;
    elems = new T*[list.capacity];
    if (!elems)
      throw OutOfMemoryException();
    capacity = list.capacity;
  }

  // copy elements
  for (size_t i = 0; i < list.count; i++) {
    elems[i] = new T( *(list.elems[i]) );
    if (!elems[i])
      throw OutOfMemoryException();

    count++;
  }

  return *this;
}

/**
 * Equality operator.  Test all values of list to see if list is
 * equal to this list.
 */
template <class T> inline bool Vector<T>::operator==(const Vector<T>& list) const {
  // don't bother if sizes aren't the same
  if (count != list.count)
    return false;

  for (size_t i = 0; i < count; i++) {
    if ( *(elems[i]) != *(list.elems[i]) )
      return false;
  }

  return true;
}

/**
 * Increases the capacity of the vector
 */
template <class T> inline void Vector<T>::grow() {
  // pick a new capacity
  size_t newSize = capacity;
  if (newSize < 16)
    newSize = 16;
  newSize <<= 2;
  if (newSize <= capacity)
    throw IntegerWrapException();

  // allocate the memory
  T** newElems = new T*[newSize];
  if (!newElems)
      throw OutOfMemoryException();

  // copy everything over
  if (elems) {
    memcpy(newElems, elems, count * sizeof(T*));

    // get rid of the old array
    delete [] elems;
  }

  // put it all in place
  elems = newElems;
  capacity = newSize;
}

/**
 * Ensures that pos is within the bounds of this vector.  An
 * OutOfBoundsEx exception is thrown otherwise.
 */
template <class T> inline void Vector<T>::checkBounds(size_t pos) const {
  if ((pos < 0) || (pos >= count))
    throw OutOfBoundsException(0, count - 1, pos);
}

// Local Variables:
// mode:C++
// End:
