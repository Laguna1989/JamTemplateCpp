#include <backend_setup.hpp>
#include <line.hpp>
#include <shape.hpp>
#include <text.hpp>
#include <gtest/gtest.h>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

namespace {

constexpr int targetWidth { 128 };
constexpr int targetHeight { 64 };

struct PixelBounds {
    int minX { std::numeric_limits<int>::max() };
    int minY { std::numeric_limits<int>::max() };
    int maxX { std::numeric_limits<int>::min() };
    int maxY { std::numeric_limits<int>::min() };

    bool isEmpty() const { return minX > maxX; }
};

std::uint32_t alphaOf(std::uint32_t const pixel) { return pixel & 0xFFu; }

std::uint32_t redOf(std::uint32_t const pixel) { return (pixel >> 24u) & 0xFFu; }

// Collected for every render of the current test and printed if the test fails, so failures on
// machines without a debugger (e.g. CI) can be analyzed.
std::string renderDiagnostics;

std::string describeRenderer(SDL_Renderer* const renderer)
{
    SDL_RendererInfo info {};
    SDL_GetRendererInfo(renderer, &info);
    std::string description = std::string { "video driver: " }
        + (SDL_GetCurrentVideoDriver() ? SDL_GetCurrentVideoDriver() : "none")
        + ", render driver: " + (info.name ? info.name : "none");

    if (SDL_GL_GetCurrentContext() != nullptr) {
        using GlGetString = unsigned char const* (*)(unsigned int);
        auto const glGetStringFunction
            = reinterpret_cast<GlGetString>(SDL_GL_GetProcAddress("glGetString"));
        if (glGetStringFunction != nullptr) {
            constexpr unsigned int glRenderer { 0x1F01u };
            constexpr unsigned int glVersion { 0x1F02u };
            auto const* const rendererName = glGetStringFunction(glRenderer);
            auto const* const version = glGetStringFunction(glVersion);
            description += std::string { ", GL renderer: " }
                + (rendererName ? reinterpret_cast<char const*>(rendererName) : "unknown")
                + ", GL version: "
                + (version ? reinterpret_cast<char const*>(version) : "unknown");
        }
    }
    return description;
}

// ASCII art of all touched pixels: '#' opaque, '+' partially transparent, '.' transparent.
std::string describePixels(std::vector<std::uint32_t> const& pixels)
{
    int minX { targetWidth };
    int minY { targetHeight };
    int maxX { -1 };
    int maxY { -1 };
    for (int y = 0; y != targetHeight; ++y) {
        for (int x = 0; x != targetWidth; ++x) {
            if (alphaOf(pixels.at(static_cast<std::size_t>(y * targetWidth + x))) != 0u) {
                minX = std::min(minX, x);
                minY = std::min(minY, y);
                maxX = std::max(maxX, x);
                maxY = std::max(maxY, y);
            }
        }
    }
    if (maxX < 0) {
        return "no pixels touched\n";
    }
    minX = std::max(0, minX - 1);
    minY = std::max(0, minY - 1);
    maxX = std::min(targetWidth - 1, maxX + 1);
    maxY = std::min(targetHeight - 1, maxY + 1);

    std::string description = "pixels starting at (" + std::to_string(minX) + ", "
        + std::to_string(minY) + "):\n";
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            auto const alpha = alphaOf(pixels.at(static_cast<std::size_t>(y * targetWidth + x)));
            description += alpha == 0u ? '.' : (alpha == 255u ? '#' : '+');
        }
        description += '\n';
    }
    return description;
}

// Renders the drawable into a transparent offscreen texture and returns its RGBA8888 pixels.
std::vector<std::uint32_t> renderToPixels(jt::DrawableImpl& drawable)
{
    SDL_ClearError();
    auto const renderer = getRenderTarget();
    std::shared_ptr<SDL_Texture> const target { SDL_CreateTexture(renderer.get(),
                                                    SDL_PIXELFORMAT_RGBA8888,
                                                    SDL_TEXTUREACCESS_TARGET, targetWidth,
                                                    targetHeight),
        [](SDL_Texture* t) { SDL_DestroyTexture(t); } };

    auto* const oldTarget = SDL_GetRenderTarget(renderer.get());
    SDL_SetRenderTarget(renderer.get(), target.get());
    SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 0);
    SDL_RenderClear(renderer.get());

    drawable.update(0.0f);
    drawable.draw(renderer);

    std::vector<std::uint32_t> pixels(static_cast<std::size_t>(targetWidth * targetHeight));
    SDL_RenderReadPixels(renderer.get(), nullptr, SDL_PIXELFORMAT_RGBA8888, pixels.data(),
        targetWidth * static_cast<int>(sizeof(std::uint32_t)));

    renderDiagnostics += describeRenderer(renderer.get()) + "\nSDL error: " + SDL_GetError() + "\n"
        + describePixels(pixels);

    SDL_SetRenderTarget(renderer.get(), oldTarget);
    return pixels;
}

// Renders the drawable and returns the bounding box of all pixels that were touched.
PixelBounds renderAndGetPixelBounds(jt::DrawableImpl& drawable)
{
    auto const pixels = renderToPixels(drawable);

    PixelBounds bounds;
    for (int y = 0; y != targetHeight; ++y) {
        for (int x = 0; x != targetWidth; ++x) {
            auto const alpha = alphaOf(pixels.at(static_cast<std::size_t>(y * targetWidth + x)));
            if (alpha == 0u) {
                continue;
            }
            bounds.minX = std::min(bounds.minX, x);
            bounds.minY = std::min(bounds.minY, y);
            bounds.maxX = std::max(bounds.maxX, x);
            bounds.maxY = std::max(bounds.maxY, y);
        }
    }
    return bounds;
}

std::shared_ptr<jt::Text> createLeftAlignedText(std::string const& content)
{
    auto text = std::make_shared<jt::Text>();
    text->loadFont("assets/font.ttf", 12, getRenderTarget());
    text->setTextAlign(jt::Text::TextAlign::LEFT);
    text->setText(content);
    text->setPosition(jt::Vector2f { 4.0f, 4.0f });
    return text;
}

std::shared_ptr<jt::Shape> createCenteredRect()
{
    auto shape = std::make_shared<jt::Shape>();
    shape->makeRect(jt::Vector2f { 4.0f, 2.0f }, getTextureManager());
    shape->setOrigin(jt::Vector2f { 2.0f, 1.0f });
    shape->setPosition(jt::Vector2f { 10.0f, 10.0f });
    return shape;
}

} // namespace

class SdlRenderTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        jt::DrawableImpl::setCamOffset(jt::Vector2f { 0.0f, 0.0f });
        renderDiagnostics.clear();
    }

    void TearDown() override
    {
        if (HasFailure()) {
            std::cout << renderDiagnostics;
        }
    }
};

TEST_F(SdlRenderTest, FlippedShapeIsMirroredAroundItsOrigin)
{
    auto const shape = createCenteredRect();
    shape->setScale(jt::Vector2f { -1.0f, 1.0f });

    auto const bounds = renderAndGetPixelBounds(*shape);

    ASSERT_FALSE(bounds.isEmpty());
    EXPECT_EQ(bounds.minX, 8);
    EXPECT_EQ(bounds.maxX, 11);
    EXPECT_EQ(bounds.minY, 9);
    EXPECT_EQ(bounds.maxY, 10);
}

TEST_F(SdlRenderTest, FlippedShapeRotatesAroundItsOrigin)
{
    auto const shape = createCenteredRect();
    shape->setScale(jt::Vector2f { -1.0f, 1.0f });
    shape->setRotation(90.0f);

    auto const bounds = renderAndGetPixelBounds(*shape);

    // rotating the 4x2 rect by 90 degrees around its center gives a 2x4 rect around (10, 10)
    ASSERT_FALSE(bounds.isEmpty());
    auto const tolerance = 1;
    EXPECT_NEAR(bounds.minX, 9, tolerance);
    EXPECT_NEAR(bounds.maxX, 10, tolerance);
    EXPECT_NEAR(bounds.minY, 8, tolerance);
    EXPECT_NEAR(bounds.maxY, 11, tolerance);
}

TEST_F(SdlRenderTest, ScaledTextRotatesAroundItsOrigin)
{
    auto text = std::make_shared<jt::Text>();
    text->loadFont("assets/font.ttf", 12, getRenderTarget());
    text->setTextAlign(jt::Text::TextAlign::LEFT);
    text->setText("bounds");
    auto const unscaledSize = text->getLocalBounds();
    text->setOrigin(jt::Vector2f { unscaledSize.width / 2.0f, unscaledSize.height / 2.0f });
    text->setScale(jt::Vector2f { 2.0f, 2.0f });
    jt::Vector2f const pivot { 64.0f, 32.0f };
    text->setPosition(pivot);

    auto const unrotated = renderAndGetPixelBounds(*text);
    text->setRotation(180.0f);
    auto const rotated = renderAndGetPixelBounds(*text);

    // a rotation by 180 degrees mirrors all pixels at the pivot
    ASSERT_FALSE(unrotated.isEmpty());
    ASSERT_FALSE(rotated.isEmpty());
    auto const tolerance = 1;
    EXPECT_NEAR(rotated.minX, 2 * static_cast<int>(pivot.x) - unrotated.maxX, tolerance);
    EXPECT_NEAR(rotated.maxX, 2 * static_cast<int>(pivot.x) - unrotated.minX, tolerance);
    EXPECT_NEAR(rotated.minY, 2 * static_cast<int>(pivot.y) - unrotated.maxY, tolerance);
    EXPECT_NEAR(rotated.maxY, 2 * static_cast<int>(pivot.y) - unrotated.minY, tolerance);
}

TEST_F(SdlRenderTest, TextIsRenderedWithSmoothEdges)
{
    auto const text = createLeftAlignedText("bounds");

    auto const pixels = renderToPixels(*text);

    auto const partiallyTransparent = std::count_if(pixels.cbegin(), pixels.cend(),
        [](auto const p) { return alphaOf(p) != 0u && alphaOf(p) != 255u; });
    EXPECT_GT(partiallyTransparent, 0);
}

TEST_F(SdlRenderTest, SmoothTextEdgesAreNotDarkened)
{
    // White text drawn onto a transparent black target ends up with red == alpha. If the alpha
    // were applied twice (once when building the text texture, once when drawing it), the
    // edges would be darker: red == alpha * alpha / 255.
    auto const text = createLeftAlignedText("bounds");

    auto const pixels = renderToPixels(*text);

    auto const tolerance = 2;
    for (auto const p : pixels) {
        if (alphaOf(p) == 0u) {
            continue;
        }
        EXPECT_NEAR(static_cast<int>(redOf(p)), static_cast<int>(alphaOf(p)), tolerance);
    }
}

TEST_F(SdlRenderTest, TextIsDecodedAsUtf8)
{
    // three two-byte characters must be narrower than four one-byte characters. Decoded as
    // Latin-1, "äää" would be six glyphs.
    auto const umlauts = createLeftAlignedText("\xC3\xA4\xC3\xA4\xC3\xA4");
    auto const ascii = createLeftAlignedText("aaaa");

    EXPECT_LT(umlauts->getGlobalBounds().width, ascii->getGlobalBounds().width);
}

struct LineScaleCase {
    float scaleX;
    int expectedMinX;
    int expectedMaxX;
};

class SdlLineRenderTest : public SdlRenderTest,
                          public ::testing::WithParamInterface<LineScaleCase> { };

INSTANTIATE_TEST_SUITE_P(SdlLineRenderTest, SdlLineRenderTest,
    ::testing::Values(LineScaleCase { 1.0f, 10, 14 }, LineScaleCase { 2.0f, 10, 18 },
        LineScaleCase { -1.0f, 6, 10 }));

TEST_P(SdlLineRenderTest, LineIsScaledFromItsStartPosition)
{
    auto const& c = GetParam();
    jt::Line line { jt::Vector2f { 4.0f, 0.0f } };
    line.setPosition(jt::Vector2f { 10.0f, 10.0f });
    line.setScale(jt::Vector2f { c.scaleX, 1.0f });

    auto const bounds = renderAndGetPixelBounds(line);

    ASSERT_FALSE(bounds.isEmpty());
    EXPECT_EQ(bounds.minX, c.expectedMinX);
    EXPECT_EQ(bounds.maxX, c.expectedMaxX);
    EXPECT_EQ(bounds.minY, 10);
    EXPECT_EQ(bounds.maxY, 10);
}
