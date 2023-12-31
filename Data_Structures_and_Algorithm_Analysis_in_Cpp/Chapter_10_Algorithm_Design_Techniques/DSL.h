#ifndef ALGORITHM_ANALYSIS_DSL_H
#define ALGORITHM_ANALYSIS_DSL_H

#include "dsexceptions.h"
#include <iostream>        // For NULL
using namespace std;

// Deterministic skip list class class
//
// CONSTRUCTION: with INFINITY object that is
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printList( )      --> Print items in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class DSL {
public:
    /**
     * Construct the tree.
     * inf is the largest Comparable.
     */
    DSL( const Comparable & inf ) : INFINITY( inf ) {
        bottom = new SkipNode();
        bottom->right = bottom->down = bottom;
        tail   = new SkipNode( INFINITY );
        tail->right = tail;
        header = new SkipNode( INFINITY, tail, bottom );
    }

    /**
     * Copy constructor.
     * Left as an exercise.
     */
    DSL( const DSL & rhs ) : INFINITY( rhs.INFINITY) {
        cout << "Copy constructor is unimplemented" << endl;
    }

    ~DSL() {
        makeEmpty();
        delete header;
        delete tail;
        delete bottom;
    }

    const Comparable & findMin() const {
        if( isEmpty() )
            throw UnderflowException();

        SkipNode *current = header;
        while( current->down != bottom )
            current = current->down;

        return current->element;
    }

    const Comparable & findMax() const {
        if( isEmpty() )
            throw UnderflowException();

        SkipNode *current = header;
        for( ; ; )
            // if right is not tail: we defined tail->right = tail
            // we need to find item before infinity. So current->right != tail is wrong.
            if( current->right->right != tail )  // If right is not the infinity element
                current = current->right;
            else if( current->down != bottom )
                current = current->down;
            else
                return current->element;
    }

    bool contains( const Comparable & x ) const {
        SkipNode *current = header;

        bottom->element = x;
        for( ; ; )
            if( x < current->element )
                current = current->down;
            else if( current->element < x )
                current = current->right;
            else
                return current != bottom;
    }

    bool isEmpty() const {
        return header->right == tail && header->down == bottom;
    }

    void printList() const {
        SkipNode *current = header;

        while( current->down != bottom )
            current = current->down;

        while( current->right != tail ) {
            cout << current->element << endl;
            current = current->right;
        }
    }

    void makeEmpty() {
        reclaimMemory( header );
        header->right = tail;
        header->down = bottom;
    }

    // see Fig 12.22 and 12.25 Weiss D/S in C 2nd Edition p. 472 and 474
    void insert( const Comparable & x ) {
        SkipNode *current = header;

        bottom->element = x;
        while( current != bottom ) {
            while( current->element < x )
                current = current->right;

            // If gap size is 3 or at bottom level and
            // must insert, then promote middle element
            // current->down->right->right : if gap is 3, this is largest element < current
            if( current->down->right->right->element < current->element ) { // if gap size is 3
                current->right = new SkipNode( current->element,
                                               current->right, current->down->right->right );
                current->element = current->down->right->element;
            } else
                current = current->down;
        }

        // Raise height of DSL if necessary
        if( header->right != tail )
            header = new SkipNode( INFINITY, tail, header );
    }

    //TODO: add remove
    void remove( const Comparable & x ) {
        cout << "Sorry, remove unimplemented; " << x <<
        " still present" << endl;
    }

    //TODO: add copy operator
    const DSL & operator=( const DSL & rhs ) {
        if( this != &rhs )
            cout << "Sorry, operator= is unimplemented" << endl;

        return *this;
    }

private:
    struct SkipNode {
        Comparable element;
        SkipNode  *right;
        SkipNode  *down;

        SkipNode( const Comparable & theElement = Comparable(),
                  SkipNode *rt = nullptr, SkipNode *dt = nullptr )
                : element( theElement ), right( rt ), down( dt ) { }
    };

    const Comparable INFINITY;
    SkipNode *header;  // The list
    SkipNode *bottom;
    SkipNode *tail;

    // Usual recursive stuff
    /**
     * reclaimMemory is left as an exercise.
     * Hint: delete from top level to bottom level.
     */
    //TODO: add reclaimMemory
    void reclaimMemory( SkipNode *t ) const {
        if( t != bottom )
            cout << "reclaimMemory is unimplemented -- leaking!" << endl;
    }
};

#endif //ALGORITHM_ANALYSIS_DSL_H
