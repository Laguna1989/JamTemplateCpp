#ifndef JAMTEMPLATE_PARTICLE_SYSTEM_HPP_GUARD
#define JAMTEMPLATE_PARTICLE_SYSTEM_HPP_GUARD

#include "Game.hpp"
#include "GameObject.hpp"
#include <array>
#include <functional>

namespace JamTemplate {

template <class T, size_t N>
class ParticleSystem : public GameObject {
public:
    using ResetCallbackType = std::function<void(std::shared_ptr<T> particle)>;
    using InitCallbackType = std::function<std::shared_ptr<T>(void)>;

    ParticleSystem(InitCallbackType const init, ResetCallbackType const reset)
        : m_resetCallback { reset }
        , m_particles {}
        , m_currentIndex { 0 }
    {
        for (auto i = 0U; i != N; ++i) {
            m_particles.at(i) = init();
        }
    };

    void Fire(unsigned int num = 1)
    {
        for (auto i = 0U; i != num; ++i) {
            m_resetCallback(m_particles.at(m_currentIndex));
            m_currentIndex++;
            if (m_currentIndex >= m_particles.size()) {
                m_currentIndex = 0;
            }
        }
    };

private:
    virtual void doUpdate(float const elapsed)
    {
        for (auto& p : m_particles) {
            p->update(elapsed);
        }
    };

    virtual void doDraw() const
    {
        for (auto& p : m_particles) {
            p->draw(getGame()->getRenderTarget());
        }
    };
    virtual void doCreate() {};

    ResetCallbackType m_resetCallback;
    std::array<std::shared_ptr<T>, N> m_particles;

    std::size_t m_currentIndex;
};

} // namespace JamTemplate

#endif // !JAMTEMPLATE_CONVERSIONS_HPP_GUARD
