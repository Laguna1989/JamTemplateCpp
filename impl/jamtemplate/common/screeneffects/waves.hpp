#ifndef JAMTEMPLATE_WAVES_HPP
#define JAMTEMPLATE_WAVES_HPP

#include <animation.hpp>
#include <game_object.hpp>
#include <rect.hpp>

namespace jt {
// TODO add to demo
class Waves : public jt::GameObject {
public:
    Waves(std::string const& filename, jt::Rectf const& size, std::vector<jt::Rectf> const& exclude,
        int count);

    void setZ(int zLayer);

private:
    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

    std::vector<std::shared_ptr<jt::Animation>> m_animations {};

    std::string m_filename;
    jt::Rectf m_size {};
    std::vector<jt::Rectf> m_exclude {};
    int m_count { 0 };
};

} // namespace jt

#endif // JAMTEMPLATE_WAVES_HPP
