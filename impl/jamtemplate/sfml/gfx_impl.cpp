#include "gfx_impl.hpp"
#include "performance_measurement.hpp"
#include <math_helper.hpp>
#include <rect_lib.hpp>
#include <sprite.hpp>
#include <tracy/Tracy.hpp>
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
    GfxImpl::createZLayer(0);
    auto const scaledWidth = static_cast<unsigned int>(m_window.getSize().x / m_camera.getZoom());
    auto const scaledHeight = static_cast<unsigned int>(m_window.getSize().y / m_camera.getZoom());

    m_view = std::make_shared<sf::View>(toLib(
        jt::Rectf { 0, 0, static_cast<float>(scaledWidth), static_cast<float>(scaledHeight) }));
    m_view->setViewport(toLib(jt::Rectf { 0, 0, 1, 1 }));
    m_viewHalfSize = fromLib(m_view->getSize() * 0.5f);
}

jt::RenderWindowInterface& jt::GfxImpl::window() { return m_window; }

jt::CamInterface& jt::GfxImpl::camera() { return m_camera; }

std::shared_ptr<jt::RenderTargetInterface> jt::GfxImpl::target() { return m_target; }

jt::TextureManagerInterface& jt::GfxImpl::textureManager() { return m_textureManager.value(); }

void jt::GfxImpl::reset() { m_camera.reset(); }

void jt::GfxImpl::update(float elapsed)
{
    ZoneScopedN("jt::GfxImpl::update");
    m_camera.update(elapsed);

    m_target->forall([this](auto t) { t->setView(*m_view); });
    m_view->setCenter(
        toLib(jt::MathHelper::castToInteger(m_camera.getCamOffset() + m_viewHalfSize)));

    DrawableImpl::setCamOffset(m_viewHalfSize - fromLib(m_view->getCenter()));
}

void jt::GfxImpl::clear() { m_target->clearPixels(); }

void jt::GfxImpl::display()
{
    m_target->forall([this](auto& layer) { drawOneZLayer(layer); });
    m_window.display();
}

void jt::GfxImpl::drawOneZLayer(std::shared_ptr<jt::RenderTargetLayer> const& layer)
{
    if (layer == nullptr) [[unlikely]] {
        throw std::invalid_argument {
            "GfXImpl::display called with nullptr jt::RenderTargetLayer"
        };
    }
    // convert renderTarget to sprite and draw that
    auto spriteForDrawing = std::make_unique<jt::Sprite>();
    spriteForDrawing->fromTexture(layer->getTexture());
    auto const shakeOffset = m_camera.getShakeOffset();
    spriteForDrawing->setPosition(shakeOffset);
    // Note: RenderTexture has a bug and is displayed upside down
    horizontalFlip(spriteForDrawing, m_camera.getZoom(), m_window.getSize().y);
    m_window.draw(spriteForDrawing);
}

void jt::GfxImpl::createZLayer(int z)
{
    auto const target = m_window.createRenderTarget();

    auto const scaledWidth = static_cast<unsigned int>(m_window.getSize().x / m_camera.getZoom());
    auto const scaledHeight = static_cast<unsigned int>(m_window.getSize().y / m_camera.getZoom());

    target->create(scaledWidth, scaledHeight);
    target->setSmooth(false);

    m_target->add(z, target);
}
