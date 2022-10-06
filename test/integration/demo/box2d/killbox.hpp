#ifndef JAMTEMPLATE_KILLBOX_HPP
#define JAMTEMPLATE_KILLBOX_HPP

#include "graphics/drawable_interface.hpp"
#include <game_object.hpp>
#include <rect.hpp>
#include <vector.hpp>
#include <functional>

// TODO think about interface
class Killbox : public jt::GameObject {
public:
    Killbox(jt::Rectf const& rect, std::string const& name, std::string const& type);
    void checkIfPlayerIsInKillbox(
        jt::Vector2f const& playerPosition, std::function<void(void)> callback) const;

    std::string getName() const override;

    jt::Vector2f getPosition() const;
    void setPosition(jt::Vector2f const& pos);

private:
    mutable std::shared_ptr<jt::DrawableInterface> m_drawable { nullptr };
    jt::Rectf m_rect {};

    std::string m_name { "" };
    std::string m_type { "" };

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;
};

#endif // JAMTEMPLATE_KILLBOX_HPP
