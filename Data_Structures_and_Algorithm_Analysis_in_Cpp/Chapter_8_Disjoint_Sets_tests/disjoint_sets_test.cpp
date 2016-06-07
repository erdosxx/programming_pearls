#include <gtest/gtest.h>
#include "DisjSets.h"

class DisjSetsFixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    DisjSetsFixture() : Test() {

    }

    virtual ~DisjSetsFixture() {
    }
};

TEST_F(DisjSetsFixture, DisjSets_Function) {
    int numElements = 128;
    int numInSameSet = 16;

    DisjSets ds{ numElements };
    int set1, set2;

    for( int k = 1; k < numInSameSet; k *= 2 ) {
        for( int j = 0; j + k < numElements; j += 2 * k ) {
            set1 = ds.find( j );
            set2 = ds.find( j + k );
            ds.unionSets( set1, set2 );
        }
    }

    for( int i = 0; i < numElements; ++i ) {
        ASSERT_EQ(16*(i/16), ds.find(i));
    }
}

