#ifndef ALGORITHM_ANALYSIS_AVLTREE_H
#define ALGORITHM_ANALYSIS_AVLTREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>

using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

// TODO: add abstract tree class and extend it to AVLTree.
//       Most of the implememtations are same as BinearySearchTree.

template <typename Comparable>
class AvlTree {
public:
    AvlTree() : root{nullptr} { }

    AvlTree( const AvlTree & rhs ) : root{nullptr} {
        root = clone( rhs.root );
    }

    AvlTree( AvlTree && rhs ) : root{rhs.root} {
        rhs.root = nullptr;
    }

    ~AvlTree() {
        makeEmpty();
    }

    AvlTree & operator=( const AvlTree & rhs ) {
        AvlTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }

    AvlTree & operator=( AvlTree && rhs ) {
        std::swap( root, rhs.root );

        return *this;
    }

    const Comparable & findMin() const {
        if( isEmpty() )
            throw UnderflowException{ };
        return findMin(root)->element;
    }

    const Comparable & findMax( ) const {
        if( isEmpty() )
            throw UnderflowException{ };
        return findMax(root)->element;
    }

    bool contains( const Comparable & x ) const {
        return contains(x, root);
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void printTree() const {
        if( isEmpty() )
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert( const Comparable & x ) {
        insert(x, root);
    }

    void insert( Comparable && x ) {
        insert(std::move( x ), root);
    }

    void remove( const Comparable & x ) {
        remove(x, root);
    }

private:
    struct AvlNode {
        Comparable element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const Comparable & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
                : element{ele}, left{lt}, right{rt}, height{h} { }

        AvlNode( Comparable && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
                : element{std::move( ele )}, left{lt}, right{rt}, height{h} { }
    };

    AvlNode *root;

    void insert( const Comparable & x, AvlNode * & t ) {
        if( t == nullptr )
            t = new AvlNode{x, nullptr, nullptr};
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );

        balance(t);
    }

    void insert( Comparable && x, AvlNode * & t ) {
        if( t == nullptr )
            t = new AvlNode{std::move(x), nullptr, nullptr};
        else if( x < t->element )
            insert( std::move(x), t->left );
        else if( t->element < x )
            insert( std::move(x), t->right );

        balance(t);
    }

    void remove( const Comparable & x, AvlNode * & t ) {
        if( t == nullptr )
            return;   // Item not found; do nothing

        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) { // Two Children
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else {
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }

        balance(t);
    }

    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance( AvlNode * & t ) {
        if( t == nullptr )
            return;

        if( height(t->left) - height(t->right) > ALLOWED_IMBALANCE ) {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        } else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }

        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    AvlNode * findMin( AvlNode *t ) const {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    AvlNode * findMax( AvlNode *t ) const {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }

    bool contains( const Comparable & x, AvlNode *t ) const {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    void makeEmpty( AvlNode * & t ) {
        if( t != nullptr ) {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    void printTree( AvlNode *t ) const {
        if( t != nullptr ) {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    AvlNode * clone( AvlNode *t ) const {
        if( t == nullptr )
            return nullptr;
        else
            return new AvlNode{ t->element, clone( t->left ), clone( t->right ), t->height };
    }

    int height( AvlNode *t ) const {
        return t == nullptr ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const {
        return lhs > rhs ? lhs : rhs;
    }

    void rotateWithLeftChild( AvlNode * & k2 ) {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    void rotateWithRightChild( AvlNode * & k1 ) {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    // See Fig 4.38 p168
    void doubleWithLeftChild( AvlNode * & k3 ) {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    // See Fig 4.39 p168
    void doubleWithRightChild( AvlNode * & k1 ) {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif //ALGORITHM_ANALYSIS_AVLTREE_H
