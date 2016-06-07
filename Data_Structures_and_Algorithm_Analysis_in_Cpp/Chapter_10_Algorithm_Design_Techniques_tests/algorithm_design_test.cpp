#include <gtest/gtest.h>
#include "optMatrix.h"
#include "all_pairs_shortest_path.h"
#include "Random.h"
#include "DSL.h"
#include "primality.h"

class OptMatrixFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    OptMatrixFixture() : Test() {

    }

    virtual ~OptMatrixFixture() {
    }
};

TEST_F(OptMatrixFixture, optimal_ordering_matrix_Function) {
    // See p 504
    Vector<int> c = {50, 10, 40, 30, 5};
    matrix<int> m(5, 5);
    matrix<int> lastChange(5, 5);

    optMatrix(c, m, lastChange);

    /*
    cout << endl;
    for (int i = 1; i < m.numrows(); ++i) {
        for (int j = 1; j < m.numcols(); ++j)
            cout << m[i][j] << "    ";
        cout << endl;
    }
     */
    const int OPTIMAL_MULT= 10500;
    ASSERT_EQ(OPTIMAL_MULT, m[1][m.numcols()-1]);

    /*
    cout << endl;
    for (int i = 1; i < lastChange.numrows(); ++i) {
        for (int j = 1; j < lastChange.numcols(); ++j)
            cout << lastChange[i][j] << "    ";
        cout << endl;
    }
    */
    // Optimal Solution: A(B(CD))
    // A(BCD)
    ASSERT_EQ(1, lastChange[1][4]);
    //   B(CD)
    ASSERT_EQ(2, lastChange[2][4]);
    //     CD
    ASSERT_EQ(3, lastChange[3][4]);
}

TEST_F(OptMatrixFixture, all_pairs_shortest_path_Function) {
    matrix<int> a
            { {
                      { 0, 2, -2, 2 },
                      { 1000, 0, -3, 1000 },
                      { 4, 1000, 0, 1000 },
                      { 1000, -2, 3, 0 }
              } };

    matrix<int> d( 4, 4 );
    matrix<int> path( 4, 4 );

    allPairs( a, d, path );

    cout << endl;

    for(int i = 0; i < d.numrows( ); ++i ) {
        for( int j = 0; j < d.numcols( ); ++j )
            cout << d[ i ][ j ] << "    " ;
        cout << endl;
    }

    cout << "-------------"<< endl;

    for(int i = 0; i < path.numrows(); ++i ) {
        for( int j = 0; j < path.numcols( ); ++j )
            cout << path[ i ][ j ] << "    " ;
        cout << endl;
    }

}

TEST_F(OptMatrixFixture, random_gen_Function) {
    Random r{1};

    for( int i = 0; i < 20; ++i )
        cout << r.randomInt() << endl;
}

TEST_F(OptMatrixFixture, Skip_List_Function) {
    const int INFINITY = 99999999;
    DSL<int> t( INFINITY );

    int NUMS = 3900;
    const int GAP  =   37;

    for(int i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );

    ASSERT_EQ(1, t.findMin());
    ASSERT_EQ(NUMS-1, t.findMax());

    for(int i = 1; i < NUMS; i++ )
        ASSERT_TRUE(t.contains(i));

    ASSERT_FALSE(t.contains(0));

    //t.printList();
}

TEST_F(OptMatrixFixture, primality_Function) {
    ASSERT_TRUE(isPrime(71));
    ASSERT_TRUE(isPrime(199));
    ASSERT_FALSE(isPrime(341));
    ASSERT_FALSE(isPrime(561));
    ASSERT_FALSE(isPrime(41041));
    ASSERT_FALSE(isPrime(321197185));
}
