#ifndef GUARD_JAMTEMPLATE_DRAWABLES_IMPL_TEST_HPP
#define GUARD_JAMTEMPLATE_DRAWABLES_IMPL_TEST_HPP

#include "animation.hpp"
#include "bar.hpp"
#include "line.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "text.hpp"
#include "tilemap/tile_layer.hpp"

class DrawableFactoryInterface {
public:
    virtual ~DrawableFactoryInterface() = default;
    virtual std::shared_ptr<jt::DrawableInterface> createDrawable() = 0;
};

class SpriteFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable() override
    {
        auto s = std::make_shared<jt::Sprite>();
        s->loadSprite("assets/coin.png");
        return s;
    }
};

class AnimationFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable() override
    {
        auto a = std::make_shared<jt::Animation>();
        a->add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 0.1f);
        a->play("idle");
        return a;
    }
};

class ShapeFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable() override
    {
        auto s = std::make_shared<jt::Shape>();
        s->makeRect(jt::Vector2 { 16, 16 });
        return s;
    }
};

class TextFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable() override
    {
        auto t = std::make_shared<jt::Text>();
        std::shared_ptr<jt::renderTarget> rt { nullptr };
        t->loadFont("assets/font.ttf", 12, rt);
        return t;
    }
};

class BarFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable() override
    {
        auto b = std::make_shared<jt::Bar>(32.0f, 12.0f);
        return b;
    }
};

class TileMapFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable() override
    {
        auto t = std::make_shared<jt::tilemap::TileLayer>("assets/tileson_test.json", "ground");
        t->setScreenSizeHint(jt::Vector2 { 400.0f, 300.0f });
        return t;
    }
};

class LineFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable() override
    {
        auto l = std::make_shared<jt::Line>(jt::Vector2 { 1.0f, 10.0f });
        return l;
    }
};

#endif // GUARD_JAMTEMPLATE_DRAWABLES_IMPL_TEST_HPP
