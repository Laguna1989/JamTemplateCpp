
#ifndef GUARD_JAMTEMPLATE_DRAWABLES_IMPL_TEST_HPP
#define GUARD_JAMTEMPLATE_DRAWABLES_IMPL_TEST_HPP

#include "animation.hpp"
#include "bar.hpp"
#include "line.hpp"
#include "shape.hpp"
#include "sprite.hpp"
#include "text.hpp"
#include "tilemap/tile_layer.hpp"
#include "tilemap/tilemap_manager_tileson_impl.hpp"
#include "tilemap/tileson_loader.hpp"

class DrawableFactoryInterface {
public:
    virtual ~DrawableFactoryInterface() = default;
    virtual std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& textureManager)
        = 0;
};

class SpriteFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable(jt::TextureManagerInterface& tm) override
    {
        return std::make_shared<jt::Sprite>("assets/coin.png", tm);
    }
};

class AnimationFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& textureManager) override
    {
        auto a = std::make_shared<jt::Animation>();
        a->add("assets/coin.png", "idle", { 16, 16 }, { 0 }, 0.1f, textureManager);
        a->play("idle");
        return a;
    }
};

class ShapeFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& textureManager) override
    {
        auto s = std::make_shared<jt::Shape>();
        s->makeRect(jt::Vector2f { 16, 16 }, textureManager);
        return s;
    }
};

class TextFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& /*textureManager*/) override
    {
        auto t = std::make_shared<jt::Text>();
        std::shared_ptr<jt::RenderTarget> renderTarget { nullptr };
        t->loadFont("assets/font.ttf", 12, renderTarget);
        return t;
    }
};

class BarFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& textureManager) override
    {
        auto b = std::make_shared<jt::Bar>(32.0f, 12.0f, true, textureManager);
        return b;
    }
};

class TileMapFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::TilemapManagerTilesonImpl> tilemapManager;
    std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& textureManager) override
    {
        jt::tilemap::TilesonLoader loader("assets/tileson_test.json");
        auto t = std::make_shared<jt::tilemap::TileLayer>(
            loader.loadTilesFromLayer("ground", textureManager));
        t->setScreenSizeHint(jt::Vector2f { 400.0f, 300.0f });
        return t;
    }
};

class TileMapFactoryWithoutScreenSizeHint : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::TilemapManagerTilesonImpl> tilemapManager;
    std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& textureManager) override
    {
        jt::tilemap::TilesonLoader loader("assets/tileson_test.json");
        auto t = std::make_shared<jt::tilemap::TileLayer>(
            loader.loadTilesFromLayer("ground", textureManager));
        return t;
    }
};

class LineFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& /*textureManager*/) override
    {
        auto l = std::make_shared<jt::Line>(jt::Vector2f { 1.0f, 10.0f });
        return l;
    }
};

#endif // GUARD_JAMTEMPLATE_DRAWABLES_IMPL_TEST_HPP
