// This sample shows how to test code relying on some global flag variables.
// Combine() helps with generating all possible combinations of such flags,
// and each test is given one combination as a parameter.

// Use class definitions to test from this header.
#include "prime_tables.h"
#include "gtest/gtest.h"

namespace {
#if GTEST_HAS_COMBINE

// Suppose we want to introduce a new, improved implementation of PrimeTable
// which combines speed of PrecalcPrimeTable and versatility of
// OnTheFlyPrimeTable (see prime_tables.h). Inside it instantiates both
// PrecalcPrimeTable and OnTheFlyPrimeTable and uses the one that is more
// appropriate under the circumstances. But in low memory conditions, it can be
// told to instantiate without PrecalcPrimeTable instance at all and use only
// OnTheFlyPrimeTable.
    class HybridPrimeTable : public PrimeTable {
    public:
        HybridPrimeTable(bool force_on_the_fly, int max_precalculated)
                : on_the_fly_impl_(new OnTheFlyPrimeTable),
                  precalc_impl_(force_on_the_fly ? NULL :
                                new PreCalculatedPrimeTable(max_precalculated)),
                  max_precalculated_(max_precalculated) {}

        virtual ~HybridPrimeTable() {
            delete on_the_fly_impl_;
            delete precalc_impl_;
        }

        virtual bool IsPrime(int n) const {
            if (precalc_impl_ != NULL && n < max_precalculated_)
                return precalc_impl_->IsPrime(n);
            else
                return on_the_fly_impl_->IsPrime(n);
        }

        virtual int GetNextPrime(int p) const {
            int next_prime = -1;
            if (precalc_impl_ != NULL && p < max_precalculated_)
                next_prime = precalc_impl_->GetNextPrime(p);

            return next_prime != -1 ? next_prime : on_the_fly_impl_->GetNextPrime(p);
        }

    private:
        OnTheFlyPrimeTable *on_the_fly_impl_;
        PreCalculatedPrimeTable *precalc_impl_;
        int max_precalculated_;
    };

    using ::testing::TestWithParam;
    using ::testing::Bool;
    using ::testing::Values;
    using ::testing::Combine;

// To test all code paths for HybridPrimeTable we must test it with numbers
// both within and outside PreCalculatedPrimeTable's capacity and also with
// PreCalculatedPrimeTable disabled. We do this by defining fixture which will
// accept different combinations of parameters for instantiating a
// HybridPrimeTable instance.
    class PrimeTableTest : public TestWithParam<::testing::tuple<bool, int> > {
    protected:
        virtual void SetUp() {
            // This can be written as
            //
            // bool force_on_the_fly;
            // int max_precalculated;
            // ::std::tie(force_on_the_fly, max_precalculated) = GetParam();
            //
            // once the Google C++ Style Guide allows use of ::std::tie.
            // See C++PL page 985
            //
            bool force_on_the_fly = ::testing::get<0>(GetParam());
            int max_precalculated = ::testing::get<1>(GetParam());
            table_ = new HybridPrimeTable(force_on_the_fly, max_precalculated);
        }

        virtual void TearDown() {
            delete table_;
            table_ = NULL;
        }

        HybridPrimeTable *table_;
    };

    TEST_P(PrimeTableTest, ReturnsFalseForNonPrimes) {
        // Inside the test body, you can refer to the test parameter by GetParam().
        // In this case, the test parameter is a PrimeTable interface pointer which
        // we can use directly.
        // Please note that you can also save it in the fixture's SetUp() method
        // or constructor and use saved copy in the tests.

        EXPECT_FALSE(table_->IsPrime(-5));
        EXPECT_FALSE(table_->IsPrime(0));
        EXPECT_FALSE(table_->IsPrime(1));
        EXPECT_FALSE(table_->IsPrime(4));
        EXPECT_FALSE(table_->IsPrime(6));
        EXPECT_FALSE(table_->IsPrime(100));
    }

    TEST_P(PrimeTableTest, ReturnsTrueForPrimes) {
        EXPECT_TRUE(table_->IsPrime(2));
        EXPECT_TRUE(table_->IsPrime(3));
        EXPECT_TRUE(table_->IsPrime(5));
        EXPECT_TRUE(table_->IsPrime(7));
        EXPECT_TRUE(table_->IsPrime(11));
        EXPECT_TRUE(table_->IsPrime(131));
    }

    TEST_P(PrimeTableTest, CanGetNextPrime) {
        EXPECT_EQ(2, table_->GetNextPrime(0));
        EXPECT_EQ(3, table_->GetNextPrime(2));
        EXPECT_EQ(5, table_->GetNextPrime(3));
        EXPECT_EQ(7, table_->GetNextPrime(5));
        EXPECT_EQ(11, table_->GetNextPrime(7));
        EXPECT_EQ(131, table_->GetNextPrime(128));
    }

// In order to run value-parameterized tests, you need to instantiate them,
// or bind them to a list of values which will be used as test parameters.
// You can instantiate them in a different translation module, or even
// instantiate them several times.
//
// Here, we instantiate our tests with a list of parameters. We must combine
// all variations of the boolean flag suppressing PrecalcPrimeTable and some
// meaningful values for tests. We choose a small value (1), and a value that
// will put some of the tested numbers beyond the capability of the
// PrecalcPrimeTable instance and some inside it (10). Combine will produce all
// possible combinations.

    // In the Combine(Bool(), Values(1, 10))
    // Four cases can be created for testing
    //  1) True, 1
    //  2) False, 1
    //  3) True, 10
    //  4) False, 10
    INSTANTIATE_TEST_CASE_P(MeaningfulTestParameters,
                            PrimeTableTest,
                            Combine(Bool(), Values(1, 10)));

#else

    // Google Test may not support Combine() with some compilers. If we
    // use conditional compilation to compile out all code referring to
    // the gtest_main library, MSVC linker will not link that library at
    // all and consequently complain about missing entry point defined in
    // that library (fatal error LNK1561: entry point must be
    // defined). This dummy test keeps gtest_main linked in.
    TEST(DummyTest, CombineIsNotSupportedOnThisPlatform) {}

#endif  // GTEST_HAS_COMBINE
}  // namespace
