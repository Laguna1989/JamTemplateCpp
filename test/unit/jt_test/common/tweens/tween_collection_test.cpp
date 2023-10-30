#include <tween_collection.hpp>
#include <gtest/gtest.h>

TEST(TweenCollectionTest, UpdateWithoutTweensDoesNotThrow)
{
    jt::TweenCollection collection;
    ASSERT_NO_THROW(collection.update(0.0f));
}

class FakeTween : public jt::TweenInterface {
public:
    void update(float /*elapsed*/) override { m_hasBeenUpdated = true; }
    bool isAlive() const override { return m_alive; }

    bool m_alive { true };
    bool m_hasBeenUpdated { false };
};

TEST(TweenCollectionTest, InitialSizeIsZero)
{
    jt::TweenCollection collection;
    ASSERT_EQ(collection.size(), 0u);
}

TEST(TweenCollectionTest, AddIncreasesCount)
{
    jt::TweenCollection collection;
    collection.add(std::make_shared<FakeTween>());
    ASSERT_EQ(collection.size(), 1u);
}

TEST(TweenCollectionTest, UpdateUpdatesTween)
{
    jt::TweenCollection collection;
    auto tw = std::make_shared<FakeTween>();
    collection.add(tw);
    collection.update(0.1f);
    ASSERT_EQ(tw->m_hasBeenUpdated, true);
}

TEST(TweenCollectionTest, KillingTweenRemovesItInUpdate)
{
    jt::TweenCollection collection;
    auto tw = std::make_shared<FakeTween>();
    collection.add(tw);
    tw->m_alive = false;
    collection.update(0.1f);
    ASSERT_EQ(collection.size(), 0u);
}
