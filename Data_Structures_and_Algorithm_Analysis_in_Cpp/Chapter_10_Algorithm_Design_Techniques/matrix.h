#ifndef ALGORITHM_ANALYSIS_MATRIX_H
#define ALGORITHM_ANALYSIS_MATRIX_H

//#include <vector>
#include "Vector.h"
#include <initializer_list>
using namespace std;

template <typename Object>
class matrix {
public:
    matrix( int rows, int cols ) : array( rows ) {
        for( auto & thisRow : array )
            thisRow.resize( cols );
    }

    matrix( initializer_list<Vector<Object>> lst ) : array( lst.size( ) ) {
        int i = 0;
        for( auto & v : lst )
            array[ i++ ] = std::move( v );
    }

    matrix( const Vector<Vector<Object>> & v ) : array{ v } { }

    matrix( Vector<Vector<Object>> && v ) : array{ std::move( v ) } { }

    const Vector<Object> & operator[]( int row ) const {
        return array[ row ];
    }

    Vector<Object> & operator[]( int row ) {
        return array[ row ];
    }

    int numrows() const {
        return array.size();
    }

    int numcols() const {
        return numrows() ? array[ 0 ].size() : 0;
    }

private:
    Vector<Vector<Object>> array;
};

#endif //ALGORITHM_ANALYSIS_MATRIX_H
