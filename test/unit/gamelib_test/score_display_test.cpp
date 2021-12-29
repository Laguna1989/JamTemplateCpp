#include "drawable_helpers.hpp"
#include "hud/score_display.hpp"
#include "render_target.hpp"
#include <gtest/gtest.h>
#include <memory>

auto create_string(std::string const& string)
{
    std::shared_ptr<jt::RenderTarget> renderTarget = nullptr;
    return jt::dh::createText(renderTarget, string, 10, jt::colors::White, "assets/font.ttf");
}

TEST(ScoreDisplayTest, TextIsNotChangedByAddingItToDisplay)
{
    auto const expected_string = "ABCD";
    auto text = create_string(expected_string);
    ScoreDisplay sd { text, "" };
    ASSERT_EQ(text->getText(), expected_string);
}

TEST(ScoreDisplayTest, TextIsUpdatedOnNotify)
{
    auto text = create_string("");
    ScoreDisplay sd { text, "" };
    sd.notify(20);
    ASSERT_EQ(text->getText(), "20");
}
