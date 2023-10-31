#ifndef JAMTEMPLATE_DRAWABLES_IMPL_TEST_HPP
#define JAMTEMPLATE_DRAWABLES_IMPL_TEST_HPP

#include <animation.hpp>
#include <bar.hpp>
#include <line.hpp>
#include <shape.hpp>
#include <sprite.hpp>
#include <text.hpp>
#include <tilemap/tile_layer.hpp>
#include <tilemap/tilemap_cache.hpp>
#include <tilemap/tileson_loader.hpp>

class DrawableFactoryInterface {
public:
    virtual ~DrawableFactoryInterface() = default;
    virtual std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& textureManager)
        = 0;
    virtual bool skipVisibilityCheck() const { return false; }
};

class SpriteFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable(jt::TextureManagerInterface& tm) override
    {
        return std::make_shared<jt::Sprite>("assets/test/unit/jt_test/coin.png", tm);
    }
};

class AnimationFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& textureManager) override
    {
        auto a = std::make_shared<jt::Animation>();
        a->add(
            "assets/test/unit/jt_test/coin.png", "idle", { 16, 16 }, { 0 }, 0.1f, textureManager);
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
        static std::shared_ptr<jt::RenderTargetLayer> renderTarget { nullptr };
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

class TileMapLoaderCache {
public:
    static std::shared_ptr<jt::tilemap::TilesonLoader> getLoader()
    {
        if (!m_initialized) {
            m_loader = std::make_shared<jt::tilemap::TilesonLoader>(
                m_cache, "assets/test/unit/jt_test/tileson_test_small.json");
            m_initialized = true;
        }
        return m_loader;
    };

private:
    static bool m_initialized;
    static std::shared_ptr<jt::tilemap::TilesonLoader> m_loader;
    static jt::TilemapCache m_cache;
};

bool TileMapLoaderCache::m_initialized { false };
std::shared_ptr<jt::tilemap::TilesonLoader> TileMapLoaderCache::m_loader { nullptr };
jt::TilemapCache TileMapLoaderCache::m_cache {};

class TileMapFactory : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::TilemapCache> tilemapManager;
    std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& textureManager) override
    {
        static auto const tiles = TileMapLoaderCache::getLoader()->loadTilesFromLayer(
            "ground", textureManager, "assets/test/unit/jt_test/");
        auto t = std::make_shared<jt::tilemap::TileLayer>(tiles);
        t->setScreenSizeHint(jt::Vector2f { 400.0f, 300.0f });
        return t;
    }

    bool skipVisibilityCheck() const override { return true; }
};

class TileMapFactoryWithoutScreenSizeHint : public DrawableFactoryInterface {
public:
    std::shared_ptr<jt::TilemapCache> tilemapManager;
    std::shared_ptr<jt::DrawableInterface> createDrawable(
        jt::TextureManagerInterface& textureManager) override
    {
        //        jt::tilemap::TilesonLoader
        //        loader("assets/test/unit/jt_test/tileson_test_small.json");
        auto t = std::make_shared<jt::tilemap::TileLayer>(
            TileMapLoaderCache::getLoader()->loadTilesFromLayer(
                "ground", textureManager, "assets/test/unit/jt_test/"));
        return t;
    }

    bool skipVisibilityCheck() const override { return true; }
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

#endif // JAMTEMPLATE_DRAWABLES_IMPL_TEST_HPP
