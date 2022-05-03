#include <system_helper.hpp>
#include <gtest/gtest.h>

TEST(IsUninitializedWeakPtr, ReturnsFalseForValidWeakPtr)
{
    auto sptr = std::make_shared<int>(5);
    std::weak_ptr<int> wptr = sptr;

    auto const result = jt::SystemHelper::is_uninitialized_weak_ptr(wptr);
    EXPECT_FALSE(result);
}

TEST(IsUninitializedWeakPtr, ReturnsTrueForUninitializedWeakPtr)
{
    std::weak_ptr<int> wptr;

    auto const result = jt::SystemHelper::is_uninitialized_weak_ptr(wptr);
    EXPECT_TRUE(result);
}

TEST(IsUninitializedWeakPtr, ReturnsFalseForExpiredWeakPtr)
{
    auto sptr = std::make_shared<int>(5);
    std::weak_ptr<int> wptr = sptr;
    sptr.reset();

    ASSERT_TRUE(wptr.expired());
    auto const result = jt::SystemHelper::is_uninitialized_weak_ptr(wptr);
    EXPECT_FALSE(result);
}

TEST(EraseIf, RemoveEvenNumbersFromVector)
{
    std::vector<int> numbers { 0, 1, 2, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::vector<int> expected { 1, 3, 5, 7, 9 };

    jt::SystemHelper::erase_if(numbers, [](auto number) { return number % 2 == 0; });

    EXPECT_EQ(numbers, expected);
}

TEST(EraseIf, FromEmptyVector)
{
    std::vector<int> numbers {};
    std::vector<int> expected {};

    jt::SystemHelper::erase_if(numbers, [](auto number) { return number % 2 == 0; });

    EXPECT_EQ(numbers, expected);
}

TEST(RemoveIntersectionTest, EmptyAResultsInEmptyVector)
{
    std::vector<int> a {};
    std::vector<int> const b { 1, 2, 3 };

    jt::SystemHelper::remove_intersection(a, b);

    ASSERT_TRUE(a.empty());
}

TEST(RemoveIntersectionTest, SameVectorsResultsInEmptyVector)
{
    std::vector<int> a { 1, 2, 3 };
    std::vector<int> const b { 1, 2, 3 };

    jt::SystemHelper::remove_intersection(a, b);

    ASSERT_TRUE(a.empty());
}

TEST(RemoveIntersectionTest, CompletelyDifferentVectorsDoesNotModifyA)
{
    std::vector<int> a { 1, 2, 3 };
    std::vector<int> const expected { a.cbegin(), a.cend() };
    std::vector<int> const b { 4, 5, 6 };

    jt::SystemHelper::remove_intersection(a, b);

    ASSERT_EQ(a, expected);
}

TEST(RemoveIntersectionTest, PartialIntersectionIsRemoved)
{
    std::vector<int> a { 1, 2, 3, 4 };
    std::vector<int> const b { 1, 3, 5 };
    std::vector<int> const expected { 2, 4 };

    jt::SystemHelper::remove_intersection(a, b);

    ASSERT_EQ(a, expected);
}

TEST(RemoveIntersectionTest, DuplicateEntriesAreNotRemovedByDefault)
{
    std::vector<int> a { 1, 2, 2, 3, 4 };
    std::vector<int> const b {};
    std::vector<int> const expected { 1, 2, 2, 3, 4 };

    jt::SystemHelper::remove_intersection(a, b);

    ASSERT_EQ(a, expected);
}

TEST(RemoveIntersectionTest, AllDuplicateEntriesAreRemovedIfInB)
{
    std::vector<int> a { 1, 2, 2, 3, 4 };
    std::vector<int> const b { 2 };
    std::vector<int> const expected { 1, 3, 4 };

    jt::SystemHelper::remove_intersection(a, b);

    ASSERT_EQ(a, expected);
}
