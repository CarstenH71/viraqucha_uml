//---------------------------------------------------------------------------------------------------------------------
// IntrusivePtr.h
//
// Copyright (C) 2017 Carsten Huber (Dipl.-Ing.)
//
// Description  : Declaration of template class IntrusivePtr.
// Compiles with: MSVC 15.2 (2017) or newer, GNU GCC 5.1 or newer
//
// *******************************************************************************************************************
// *                                                                                                                 *
// * This file is part of ViraquchaUML.                                                                              *
// *                                                                                                                 *
// * ViraquchaUML is free software; you can redistribute it and/or modify it under the terms of the GNU General      *
// * Public License as published by the Free Software Foundation; either version 3.0 of the License, or (at your     *
// * option) any later version.                                                                                      *
// *                                                                                                                 *
// * ViraquchaUML is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the      *
// * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License     *
// * for more details.                                                                                               *
// *                                                                                                                 *
// * You should have received a copy of the GNU General Public License along with ViraquchaUML; if not, see          *
// * http://www.gnu.org/licenses/gpl                                                                                 *
// *                                                                                                                 *
// *******************************************************************************************************************
//
// See https://github.com/CarstenH71/viraqucha_uml for the latest version of this software.
//---------------------------------------------------------------------------------------------------------------------
#pragma once

/**
 * @class IntrusivePtr
 * @brief Provides an implementation of an intrusive pointer using reference counting.
 * @since 1.0
 * @ingroup UmlCommon
 *
 * An intrusive pointer requires the object to be pointed to to have methods for increasing and decreasing a reference
 * count. To make increasing and decreasing thread safe, a QAtomicInteger should be used for the reference counter.
 */
template<class T> class IntrusivePtr
{
public: // Constructors
   /** Initializes a new instance of the IntrusivePtr class. */
   IntrusivePtr()
   : _pointee(nullptr)
   {}

   /** Initializes a new instance of the IntrusivePtr class. */
   explicit IntrusivePtr(T* pointee)
   : _pointee(pointee)
   {
      acquire();
   }

   /** Initializes a new instance of the IntrusivePtr class. */
   IntrusivePtr(const IntrusivePtr& other)
   : _pointee(other.pointee())
   {
      acquire();
   }

   /** Finalizes an instance of the IntrusivePtr class and releases the object pointed to. */
   ~IntrusivePtr()
   {
      release();
   }

public: // Properties
   /** Gets the object pointed to. */
   T* pointee() const { return _pointee; }

   /** Gets a value indicating whether the intrusive pointer is nullptr. */
   bool isNull() const { return _pointee == nullptr; }

public: // Operators
   /** Overloaded arrow operator, implements pointer semantics. Gets a non-guarded pointer to the object. */
   T* operator->() const { return _pointee; }

   /** Overloaded dereferencing operator, implements pointer semantics. Gets a reference to the object. */
   T& operator*() const { return *_pointee; }

   /** Overloaded cast operator, implements pointer semantics. */
   operator T*() const { return _pointee; }

   /** Overloaded assignment operator. Assigns another shared object. */
   IntrusivePtr& operator=(const IntrusivePtr& other)
   {
      release();
      _pointee = other.pointee();
      acquire();
      return *this;
   }

   /** Overloaded assignment operator. Assigns a pointer. */
   IntrusivePtr& operator=(T* pointee)
   {
      release();
      _pointee = pointee;
      acquire();
      return *this;
   }

private:
   /** Aquires the object pointed to by increasing the reference count of the object. */
   void acquire()
   {
      if (_pointee != nullptr) _pointee->incRefCount();
   }

   /** Releases the object pointed to by decreasing the reference count of the object. */
   void release()
   {
      if (_pointee != nullptr) _pointee->decRefCount();
   }

private:
   T* _pointee;
};

template<class T> bool operator==(const IntrusivePtr<T>& lhs, const IntrusivePtr<T>& rhs)
{
   return lhs.pointee() == rhs.pointee();
}

template<class T> bool operator!=(const IntrusivePtr<T>& lhs, const IntrusivePtr<T>& rhs)
{
   return lhs.pointee() != rhs.pointee();
}

template<class T> bool operator<=(const IntrusivePtr<T>& lhs, const IntrusivePtr<T>& rhs)
{
   return lhs.pointee() <= rhs.pointee();
}

template<class T> bool operator>=(const IntrusivePtr<T>& lhs, const IntrusivePtr<T>& rhs)
{
   return lhs.pointee() >= rhs.pointee();
}

template<class T> bool operator<(const IntrusivePtr<T>& lhs, const IntrusivePtr<T>& rhs)
{
   return lhs.pointee() < rhs.pointee();
}

template<class T> bool operator>(const IntrusivePtr<T>& lhs, const IntrusivePtr<T>& rhs)
{
   return lhs.pointee() > rhs.pointee();
}
