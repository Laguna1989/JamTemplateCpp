#include "gfx_impl.hpp"
#include <rect_lib.hpp>
#include <sprite.hpp>
#include <vector_lib.hpp>

namespace {

void horizontalFlip(std::unique_ptr<jt::Sprite> const& spr, float zoom, float window_size_y)
{
    spr->setScale(jt::Vector2f { zoom, -zoom });
    spr->setPosition({ spr->getPosition().x, spr->getPosition().y + window_size_y });
    spr->update(0.0f);
}

} // namespace

jt::GfxImpl::GfxImpl(RenderWindowInterface& window, CamInterface& cam)
    : m_window { window }
    , m_camera { cam }
    , m_target {}
    , m_textureManager { nullptr }
{
    m_target = std::make_shared<jt::RenderTarget>();
    createZLayer(0);
    auto const scaledWidth = static_cast<unsigned int>(m_window.getSize().x / m_camera.getZoom());
    auto const scaledHeight = static_cast<unsigned int>(m_window.getSize().y / m_camera.getZoom());

    m_view = std::make_shared<sf::View>(toLib(
        jt::Rectf { 0, 0, static_cast<float>(scaledWidth), static_cast<float>(scaledHeight) }));
    m_view->setViewport(toLib(jt::Rectf { 0, 0, 1, 1 }));
}

jt::RenderWindowInterface& jt::GfxImpl::window() { return m_window; }

jt::CamInterface& jt::GfxImpl::camera() { return m_camera; }

std::shared_ptr<jt::RenderTargetInterface> jt::GfxImpl::target() { return m_target; }

jt::TextureManagerInterface& jt::GfxImpl::textureManager() { return m_textureManager.value(); }

void jt::GfxImpl::reset() { m_camera.reset(); }

void jt::GfxImpl::update(float elapsed)
{
    m_camera.update(elapsed);

    // cast to int and back to float to avoid rounding issues with subpixel positions
    int const camOffsetix { static_cast<int>(m_camera.getCamOffset().x + m_view->getSize().x / 2) };
    int const camOffsetiy { static_cast<int>(m_camera.getCamOffset().y + m_view->getSize().y / 2) };

    m_target->forall([this](auto t) { t->setView(*m_view); });
    m_view->setCenter(
        toLib(jt::Vector2f { static_cast<float>(camOffsetix), static_cast<float>(camOffsetiy) }));

    DrawableImpl::setCamOffset(-1.0f * fromLib(m_view->getCenter() - m_view->getSize() / 2.0f));
}

void jt::GfxImpl::clear() { m_target->clearPixels(); }

void jt::GfxImpl::display()
{
    m_target->forall([this](auto t) {
        if (t == nullptr) {
            throw std::invalid_argument {
                "GfXImpl::display called with nullptr jt::RenderTargetLayer"
            };
        }
        drawOneZLayer(*t);
    });
    m_window.display();
}

void jt::GfxImpl::drawOneZLayer(jt::RenderTargetLayer& rt)
{
    // convert renderTarget to sprite and draw that.
    auto spriteForDrawing = std::make_unique<Sprite>();
    spriteForDrawing->fromTexture(rt.getTexture());
    auto const shakeOffset = m_camera.getShakeOffset();
    spriteForDrawing->setPosition(shakeOffset);
    // Note: RenderTexture has a bug and is displayed upside down.
    horizontalFlip(spriteForDrawing, m_camera.getZoom(), m_window.getSize().y);
    m_window.draw(spriteForDrawing);
}

void jt::GfxImpl::createZLayer(int z)
{
    auto target = m_window.createRenderTarget();

    auto const scaledWidth = static_cast<unsigned int>(m_window.getSize().x / m_camera.getZoom());
    auto const scaledHeight = static_cast<unsigned int>(m_window.getSize().y / m_camera.getZoom());

    target->create(scaledWidth, scaledHeight);
    target->setSmooth(false);

    m_target->add(z, target);
}
