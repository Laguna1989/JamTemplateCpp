#include <backend_setup.hpp>
#include <shape.hpp>
#include <sprite.hpp>
#include <text.hpp>
#include <gtest/gtest.h>
#include <memory>
#include <ostream>
#include <tuple>

namespace {

class BoundsDrawableFactoryInterface {
public:
    virtual ~BoundsDrawableFactoryInterface() = default;
    virtual std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& textureManager)
        = 0;
    // text positions are cast to integer after applying the alignment offset
    virtual float tolerance() const { return 0.001f; }
    virtual std::string name() const = 0;
};

class BoundsSpriteFactory : public BoundsDrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable(jt::TextureManagerInterface& tm) override
    {
        return std::make_shared<jt::Sprite>("assets/test/unit/jt_test/coin.png", tm);
    }
    std::string name() const override { return "Sprite"; }
};

class BoundsShapeFactory : public BoundsDrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable(jt::TextureManagerInterface& tm) override
    {
        auto s = std::make_shared<jt::Shape>();
        s->makeRect(jt::Vector2f { 16, 24 }, tm);
        return s;
    }
    std::string name() const override { return "Shape"; }
};

class BoundsTextFactory : public BoundsDrawableFactoryInterface {
public:
    explicit BoundsTextFactory(jt::Text::TextAlign align)
        : m_align { align }
    {
    }

    std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& /*textureManager*/) override
    {
        static auto renderTarget = getRenderTarget();
        auto t = std::make_shared<jt::Text>();
        t->loadFont("assets/font.ttf", 12, renderTarget);
        t->setTextAlign(m_align);
        t->setText("bounds");
        return t;
    }

    float tolerance() const override { return 1.0f; }

    std::string name() const override
    {
        return m_align == jt::Text::TextAlign::LEFT ? "TextLeft" : "TextCenter";
    }

private:
    jt::Text::TextAlign m_align;
};

struct BoundsCase {
    jt::Vector2f position;
    jt::Vector2f scale;
    jt::Vector2f origin;
    jt::Vector2f offset;
};

std::ostream& operator<<(std::ostream& os, BoundsCase const& c)
{
    return os << "pos(" << c.position.x << "," << c.position.y << ") scale(" << c.scale.x << ","
              << c.scale.y << ") origin(" << c.origin.x << "," << c.origin.y << ") offset("
              << c.offset.x << "," << c.offset.y << ")";
}

} // namespace

class DrawableGlobalBoundsTestFixture
    : public ::testing::TestWithParam<
          std::tuple<std::shared_ptr<BoundsDrawableFactoryInterface>, BoundsCase>> {
protected:
    jt::TextureManagerInterface& tm { getTextureManager() };

    void TearDown() override { jt::DrawableImpl::setCamOffset(jt::Vector2f { 0.0f, 0.0f }); }
};

INSTANTIATE_TEST_SUITE_P(DrawableGlobalBoundsTest, DrawableGlobalBoundsTestFixture,
    ::testing::Combine(
        ::testing::Values(std::make_shared<BoundsSpriteFactory>(),
            std::make_shared<BoundsShapeFactory>(),
            std::make_shared<BoundsTextFactory>(jt::Text::TextAlign::LEFT),
            std::make_shared<BoundsTextFactory>(jt::Text::TextAlign::CENTER)),
        ::testing::Values(
            // clang-format off
            BoundsCase { { 10.0f, 20.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
            BoundsCase { { 10.0f, 20.0f }, { 2.0f, 3.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } },
            BoundsCase { { 10.0f, 20.0f }, { 1.0f, 1.0f }, { 4.0f, 6.0f }, { 0.0f, 0.0f } },
            BoundsCase { { 10.0f, 20.0f }, { 2.0f, 3.0f }, { 4.0f, 6.0f }, { 0.0f, 0.0f } },
            BoundsCase { { 10.0f, 20.0f }, { 1.0f, 1.0f }, { 0.0f, 0.0f }, { 5.0f, -7.0f } },
            BoundsCase { { 10.0f, 20.0f }, { 2.0f, 3.0f }, { 4.0f, 6.0f }, { 5.0f, -7.0f } }
            // clang-format on
            )),
    [](auto const& info) {
        return std::get<0>(info.param)->name() + "_" + std::to_string(info.index);
    });

TEST_P(DrawableGlobalBoundsTestFixture, GlobalBoundsMatchTransform)
{
    auto const& [factory, c] = GetParam();

    auto const drawable = factory->createDrawable(tm);
    drawable->update(0.0f);
    auto const unscaled = drawable->getGlobalBounds();
    ASSERT_GT(unscaled.width, 0.0f);
    ASSERT_GT(unscaled.height, 0.0f);

    drawable->setPosition(c.position);
    drawable->setScale(c.scale);
    drawable->setOrigin(c.origin);
    drawable->setOffset(c.offset);
    drawable->update(0.0f);

    auto const bounds = drawable->getGlobalBounds();
    auto const tolerance = factory->tolerance();
    EXPECT_NEAR(bounds.left,
        c.position.x + c.offset.x + c.scale.x * (unscaled.left - c.origin.x), tolerance);
    EXPECT_NEAR(
        bounds.top, c.position.y + c.offset.y + c.scale.y * (unscaled.top - c.origin.y), tolerance);
    EXPECT_NEAR(bounds.width, unscaled.width * c.scale.x, tolerance);
    EXPECT_NEAR(bounds.height, unscaled.height * c.scale.y, tolerance);
}

TEST(DrawableGlobalBoundsTest, CenteredTextIsCenteredAroundPosition)
{
    BoundsTextFactory factory { jt::Text::TextAlign::CENTER };
    auto const drawable = factory.createDrawable(getTextureManager());
    jt::Vector2f const position { 50.0f, 20.0f };
    drawable->setPosition(position);
    drawable->update(0.0f);

    auto const bounds = drawable->getGlobalBounds();
    // sfml glyph bounds do not start exactly at the text position
    auto const glyphBearingTolerance = 1.0f;
    EXPECT_NEAR(bounds.left + bounds.width / 2.0f, position.x,
        factory.tolerance() + glyphBearingTolerance);
}
