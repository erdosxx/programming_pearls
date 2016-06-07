#ifndef ALGORITHM_ANALYSIS_VECTOR_H
#define ALGORITHM_ANALYSIS_VECTOR_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include "dsexceptions.h"

template <typename Object>
class Vector {
public:
    explicit Vector( int initSize = 0 )
            : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY } {
        objects = new Object[ theCapacity ];
    }

    explicit Vector( int initSize, Object initVal )
            : theSize{ initSize }, theCapacity{ initSize + SPARE_CAPACITY } {
        objects = new Object[ theCapacity ];

        for (int i=0; i< initSize; i++)
            objects[i] = initVal;
    }

    Vector( const Vector & rhs )
            : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr } {
        objects = new Object[ theCapacity ];

        for( int k = 0; k < theSize; ++k )
            objects[ k ] = rhs.objects[ k ];
    }

    // See C++ Programming Language p. 65
    Vector( std::initializer_list<Object> lst)
            : objects{new Object[lst.size()]}, theSize{static_cast<int>(lst.size())},
              theCapacity{ static_cast<int>(lst.size()) + SPARE_CAPACITY} {
        int i = 0;
        for( auto & v : lst )
            objects[ i++ ] = std::move( v );
    }

    Vector & operator= ( const Vector & rhs ) {
        Vector copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    ~Vector() {
        delete [] objects;
    }

    Vector( Vector && rhs )
            : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects } {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    Vector & operator= ( Vector && rhs ) {
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( objects, rhs.objects );

        return *this;
    }

    bool empty() const {
        return size() == 0;
    }

    int size() const {
        return theSize;
    }

    int capacity() const {
        return theCapacity;
    }

    Object & operator[]( int index ) {
#ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException{ };
#endif
        return objects[ index ];
    }

    const Object & operator[]( int index ) const {
#ifndef NO_CHECK
        if( index < 0 || index >= size() )
            throw ArrayIndexOutOfBoundsException{ };
#endif
        return objects[ index ];
    }

    void resize( int newSize ) {
        if( newSize > theCapacity )
            reserve( newSize * 2 );
        theSize = newSize;
    }

    void reserve( int newCapacity ) {
        if( newCapacity < theSize )
            return;

        Object *newArray = new Object[ newCapacity ];
        for( int k = 0; k < theSize; ++k )
            newArray[ k ] = std::move( objects[ k ] );

        theCapacity = newCapacity;
        std::swap( objects, newArray );
        delete [] newArray;
    }

    void push_back( const Object & x ) {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = x;
    }

    void push_back( Object && x ) {
        if( theSize == theCapacity )
            reserve( 2 * theCapacity + 1 );
        objects[ theSize++ ] = std::move( x );
    }

    void pop_back() {
        if( empty() )
            throw UnderflowException{ };
        --theSize;
    }

    const Object & back () const {
        if( empty() )
            throw UnderflowException{ };
        return objects[ theSize - 1 ];
    }

    // Iterator stuff: not bounds checked
    typedef Object * iterator;
    //using iterator = Object*;
    typedef const Object * const_iterator;
    //using const_iterator = const Object*

    iterator begin() {
        return &objects[ 0 ];
    }

    const_iterator begin() const {
        return &objects[ 0 ];
    }

    iterator end() {
        return &objects[ size() ];
    }

    const_iterator end() const {
        return &objects[ size() ];
    }

    static const int SPARE_CAPACITY = 2;

private:
    int theSize;
    int theCapacity;
    Object * objects;
};

#endif //ALGORITHM_ANALYSIS_VECTOR_H
