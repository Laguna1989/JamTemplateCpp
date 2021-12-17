#ifndef GUARD_JAMTEMPLATE_EASE_OBJECT_HPP
#define GUARD_JAMTEMPLATE_EASE_OBJECT_HPP

#include "game_object.hpp"
#include "shape.hpp"
#include "text.hpp"
#include <functional>
#include <memory>

class EaseObject : public jt::GameObject {
public:
    EaseObject(std::string const& name, std::function<float(float, float, float, float)> func,
        jt::Vector2f offset);

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

private:
    std::shared_ptr<jt::Shape> m_backgroundShape { nullptr };
    std::shared_ptr<jt::Shape> m_objectShape { nullptr };
    std::shared_ptr<jt::Text> m_text { nullptr };

    std::string m_textString { "" };
    std::function<float(float, float, float, float)> m_func;
    jt::Vector2f m_offset;
};

#endif // MYAWESOMEGAME_EASE_OBJECT_HPP
