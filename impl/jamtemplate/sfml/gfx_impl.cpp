#include "gfx_impl.hpp"
#include "rect_lib.hpp"
#include "sprite.hpp"
#include "vector_lib.hpp"
#include <utility>

namespace {

void horizontalFlip(std::unique_ptr<jt::Sprite> const& spr, float zoom, float window_size_y)
{
    spr->setScale(jt::Vector2f { zoom, -zoom });
    spr->setPosition({ spr->getPosition().x, spr->getPosition().y + window_size_y });
    spr->update(0.0f);
}

} // namespace

namespace jt {

GfxImpl::GfxImpl(RenderWindow&& window, Camera&& cam)
    : m_window { std::move(window) }
    , m_camera { std::move(cam) }
    , m_renderTarget { m_window.createRenderTarget() }
    , m_textureManager { m_renderTarget }
{
    auto const scaledWidth = static_cast<unsigned int>(m_window.getSize().x / m_camera.getZoom());
    auto const scaledHeight = static_cast<unsigned int>(m_window.getSize().y / m_camera.getZoom());

    m_renderTarget->create(scaledWidth, scaledHeight);
    m_renderTarget->setSmooth(false);

    m_view = std::make_shared<sf::View>(toLib(
        jt::Rectf { 0, 0, static_cast<float>(scaledWidth), static_cast<float>(scaledHeight) }));
    m_view->setViewport(toLib(jt::Rectf { 0, 0, 1, 1 }));

    m_sprite_for_drawing = std::make_unique<jt::Sprite>();
}

RenderWindowInterface& GfxImpl::window() { return m_window; }

CamInterface& GfxImpl::camera() { return m_camera; }

std::shared_ptr<RenderTarget> GfxImpl::target() { return m_renderTarget; }

TextureManagerInterface& GfxImpl::textureManager() { return m_textureManager.value(); }

void GfxImpl::reset() { m_camera.reset(); }

void GfxImpl::update(float elapsed)
{
    m_camera.update(elapsed);

    // cast to int and back to float to avoid rounding issues with subpixel positions
    int const camOffsetix { static_cast<int>(m_camera.getCamOffset().x + m_view->getSize().x / 2) };
    int const camOffsetiy { static_cast<int>(m_camera.getCamOffset().y + m_view->getSize().y / 2) };

    m_renderTarget->setView(*m_view);
    m_view->setCenter(
        toLib(jt::Vector2f { static_cast<float>(camOffsetix), static_cast<float>(camOffsetiy) }));

    DrawableImpl::setCamOffset(-1.0f * fromLib(m_view->getCenter() - m_view->getSize() / 2.0f));
}

void GfxImpl::clear() { m_renderTarget->clear(sf::Color::Black); }

void GfxImpl::display()
{
    // convert renderTexture to sprite and draw that.
    const sf::Texture& texture = m_renderTarget->getTexture();

    m_sprite_for_drawing->fromTexture(texture);
    auto const shakeOffset = m_camera.getShakeOffset();
    m_sprite_for_drawing->setPosition(shakeOffset);
    // Note: RenderTexture has a bug and is displayed upside down.
    horizontalFlip(m_sprite_for_drawing, m_camera.getZoom(), m_window.getSize().y);

    m_window.draw(m_sprite_for_drawing);

    m_window.display();
}

} // namespace jt
