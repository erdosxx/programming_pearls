#ifndef ALGORITHM_ANALYSIS_DSEXCEPTIONS_H
#define ALGORITHM_ANALYSIS_DSEXCEPTIONS_H

#include <string>
using namespace std;

class DSException {
public:
    DSException( const string & msg = "" ) : message( msg ) {
    }

    virtual ~DSException() { }

    virtual string toString() const
#ifndef NO_RTTI
    { return "Exception " + string( typeid( *this ).name() ) + ": " + what(); }
#else
    { return "Exception " + string( ": " ) + what(); }
#endif
    virtual string what() const {
        return message;
    }

private:
    string message;
};

class UnderflowException { };
class IllegalArgumentException { };
class ArrayIndexOutOfBoundsException { };
class IteratorOutOfBoundsException { };
class IteratorMismatchException { };
class IteratorUninitializedException { };
class CycleFoundException { };

class GraphException : public DSException {
public:
    GraphException( const string & msg = "" ) : DSException( msg ) {
        cout << toString();
    }
};


#endif //ALGORITHM_ANALYSIS_DSEXCEPTIONS_H
