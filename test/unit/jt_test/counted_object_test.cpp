#include <counted_object.hpp>
#include <gtest/gtest.h>

class A : public jt::CountedObj<A> {
};

class CountMe : public jt::CountedObj<CountMe> {
public:
    std::size_t getNumberOfAliveObjects() const { return aliveObjects(); }
    std::size_t getNumberOfCreatedObjects() const { return createdObjects(); }
    void resetCreatedObjects() { resetCreated(); }
};

TEST(CountedObjectTest, AliveObjectCounterIsInitiallyZero)
{
    ASSERT_EQ(jt::CountedObj<CountMe>::aliveObjects(), 0);
}

TEST(CountecObjectTest, AliveObjectCounterIsOneAfterCreation)
{
    CountMe cm;
    ASSERT_EQ(cm.getNumberOfAliveObjects(), 1);
}

TEST(CountecObjectTest, AliveObjectCounterIsDecreasedAfterCreation)
{
    {
        CountMe cm;
        // sanity check
        ASSERT_EQ(jt::CountedObj<CountMe>::aliveObjects(), 1);
    }
    ASSERT_EQ(jt::CountedObj<CountMe>::aliveObjects(), 0);
}

TEST(CountecObjectTest, CreatedObjectsIsZeroAfterReset)
{
    CountMe cm;
    cm.resetCreatedObjects();
    ASSERT_EQ(cm.createdObjects(), 0);
}
