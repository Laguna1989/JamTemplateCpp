#include "scene_spatial_grid.hpp"
#include <drawable_helpers.hpp>
#include <game_interface.hpp>
#include <math_helper.hpp>
#include <random/random.hpp>
#include <algorithm>
#include <cmath>
#include <string>

namespace {
constexpr jt::Vector2f screenSize { 400.0f, 300.0f };
constexpr int numberOfDots { 600 };
constexpr float minQueryRadius { 8.0f };
constexpr float maxQueryRadius { 120.0f };

float wrap(float const value, float const max)
{
    if (value < 0.0f) {
        return value + max;
    }
    if (value >= max) {
        return value - max;
    }
    return value;
}
} // namespace

void SceneSpatialGrid::doCreate()
{
    m_grid = std::make_shared<jt::SpatialObjectGrid<GridDot, cellSize>>();
    m_grid->setGameInstance(getGame());
    m_grid->create();

    for (auto i = 0; i != numberOfDots; ++i) {
        auto const dot = std::make_shared<GridDot>(GridDot { jt::Random::getRandomPointIn(screenSize),
            jt::Random::getRandomPointInCircle(30.0f) });
        m_dots.push_back(dot);
        m_grid->push_back(dot);
    }

    m_dotShape = jt::dh::createShapeRect(
        jt::Vector2f { 2.0f, 2.0f }, jt::colors::White, textureManager());
    m_cellShape = jt::dh::createShapeRect(jt::Vector2f { cellSize - 1.0f, cellSize - 1.0f },
        jt::Color { 255, 255, 0, 40 }, textureManager());
    m_radiusShape = jt::dh::createShapeCircle(
        maxQueryRadius, jt::Color { 255, 60, 60, 60 }, textureManager());
    m_radiusShape->setOrigin(jt::OriginMode::CENTER);

    m_info = jt::dh::createText(renderTarget(), "", 12);
    m_info->setTextAlign(jt::Text::TextAlign::LEFT);
    m_info->setPosition(jt::Vector2f { 4.0f, 282.0f });
    m_info->setShadow(jt::colors::Black, jt::Vector2f { 1.0f, 1.0f });
}

void SceneSpatialGrid::moveDots(float const elapsed)
{
    for (auto& dot : m_dots) {
        dot->position += dot->velocity * elapsed;
        dot->position.x = wrap(dot->position.x, screenSize.x);
        dot->position.y = wrap(dot->position.y, screenSize.y);
    }
    // Moves the dots into their new cells
    m_grid->update(elapsed);
}

void SceneSpatialGrid::queryAroundMouse()
{
    auto const mousePosition = mouse()->getMousePositionWorld();

    m_candidates.clear();
    m_hits.clear();
    for (auto const& weakDot : m_grid->getObjectsAround(mousePosition, m_queryRadius)) {
        auto const dot = weakDot.lock();
        if (!dot) {
            continue;
        }
        m_candidates.push_back(dot);
        if (jt::MathHelper::lengthSquared(dot->position - mousePosition)
            <= m_queryRadius * m_queryRadius) {
            m_hits.push_back(dot);
        }
    }
}

void SceneSpatialGrid::doUpdate(float const elapsed)
{
    auto const keyboard = getGame()->input().keyboard();
    if (keyboard->pressed(jt::KeyCode::Up)) {
        m_queryRadius = std::min(m_queryRadius + 60.0f * elapsed, maxQueryRadius);
    }
    if (keyboard->pressed(jt::KeyCode::Down)) {
        m_queryRadius = std::max(m_queryRadius - 60.0f * elapsed, minQueryRadius);
    }

    moveDots(elapsed);
    queryAroundMouse();

    auto const radiusScale = m_queryRadius / maxQueryRadius;
    m_radiusShape->setScale(jt::Vector2f { radiusScale, radiusScale });
    m_radiusShape->setPosition(mouse()->getMousePositionWorld());
    m_radiusShape->update(elapsed);

    m_info->setText("Up/Down: radius. Checked " + std::to_string(m_candidates.size()) + " / "
        + std::to_string(m_dots.size()) + " dots, " + std::to_string(m_hits.size()) + " in range");
    m_info->update(elapsed);
}

void SceneSpatialGrid::drawQueriedCells() const
{
    // Same cell range as SpatialObjectGrid::getObjectsAround uses internally
    auto const mousePosition = mouse()->getMousePositionWorld();
    auto const cellX = static_cast<int>(std::floor(mousePosition.x / cellSize));
    auto const cellY = static_cast<int>(std::floor(mousePosition.y / cellSize));
    auto const distanceInCells = static_cast<int>(std::ceil(m_queryRadius / cellSize));

    for (auto x = cellX - distanceInCells; x <= cellX + distanceInCells; ++x) {
        for (auto y = cellY - distanceInCells; y <= cellY + distanceInCells; ++y) {
            m_cellShape->setPosition(jt::Vector2f { static_cast<float>(x * cellSize),
                static_cast<float>(y * cellSize) });
            m_cellShape->update(0.0f);
            m_cellShape->draw(renderTarget());
        }
    }
}

void SceneSpatialGrid::drawDots(
    std::vector<std::shared_ptr<GridDot>> const& dots, jt::Color const& color) const
{
    m_dotShape->setColor(color);
    for (auto const& dot : dots) {
        m_dotShape->setPosition(dot->position);
        m_dotShape->update(0.0f);
        m_dotShape->draw(renderTarget());
    }
}

void SceneSpatialGrid::doDraw() const
{
    drawQueriedCells();
    m_radiusShape->draw(renderTarget());

    drawDots(m_dots, jt::Color { 120, 120, 120 });
    drawDots(m_candidates, jt::colors::Yellow);
    drawDots(m_hits, jt::Color { 255, 60, 60 });

    m_info->draw(renderTarget());
}

std::string SceneSpatialGrid::getName() const { return "jt::SpatialObjectGrid"; }
