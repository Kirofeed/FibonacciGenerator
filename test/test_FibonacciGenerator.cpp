#define UNIT_TEST
#include <gtest/gtest.h>
#include "FibonacciGenerator.h"
#include <vector>
#include <limits>
#include <sstream>

using namespace Industrial;

class DummyLogger : public ILogger {
public:
    virtual void log(const std::string& message) {
    }
};

TEST(FibonacciGeneratorTest, GenerateZeroElements) {
    DummyLogger dummy;
    FibonacciGenerator<int> fibGen(&dummy);
    std::vector<int> result = fibGen.generate(0);
    EXPECT_EQ(0u, result.size());
}

TEST(FibonacciGeneratorTest, GenerateOneElement) {
    DummyLogger dummy;
    FibonacciGenerator<int> fibGen(&dummy);
    std::vector<int> result = fibGen.generate(1);
    ASSERT_EQ(1u, result.size());
    EXPECT_EQ(0, result[0]);
}

TEST(FibonacciGeneratorTest, GenerateMultipleElements) {
    DummyLogger dummy;
    FibonacciGenerator<int> fibGen(&dummy);
    std::vector<int> result = fibGen.generate(10);
    std::vector<int> expected;
    expected.push_back(0);
    expected.push_back(1);
    expected.push_back(1);
    expected.push_back(2);
    expected.push_back(3);
    expected.push_back(5);
    expected.push_back(8);
    expected.push_back(13);
    expected.push_back(21);
    expected.push_back(34);
    EXPECT_EQ(expected, result);
}

TEST(FibonacciGeneratorTest, TestComputeNext) {
    DummyLogger dummy;
    class TestFibonacci : public FibonacciGenerator<int> {
    public:
        TestFibonacci(ILogger* logger) : FibonacciGenerator<int>(logger) {}
        int publicComputeNext(int a, int b) {
            return computeNext(a, b);
        }
    };

    TestFibonacci testFib(&dummy);
    EXPECT_EQ(8, testFib.publicComputeNext(3, 5));
}

TEST(FibonacciGeneratorTest, OverflowDetection) {
    DummyLogger dummy;
    FibonacciGenerator<unsigned int> fibGen(&dummy);
    unsigned int a = std::numeric_limits<unsigned int>::max() - 1;
    unsigned int b = 2;
    EXPECT_THROW({
        class TestFibonacci : public FibonacciGenerator<unsigned int> {
        public:
            TestFibonacci(ILogger* logger) : FibonacciGenerator<unsigned int>(logger) {}
            unsigned int publicComputeNext(unsigned int a, unsigned int b) {
                return computeNext(a, b);
            }
        };
        TestFibonacci testFib(&dummy);
        testFib.publicComputeNext(a, b);
    }, FibonacciException);
}
