#ifndef GUARD_JAMTEMPLATE_PARTICLE_SYSTEM_HPP_GUARD
#define GUARD_JAMTEMPLATE_PARTICLE_SYSTEM_HPP_GUARD

#include "game_interface.hpp"
#include "game_object.hpp"
#include <array>
#include <functional>
#include <memory>

namespace jt {

template <class T, size_t N>
class ParticleSystem : public GameObject {
public:
    using ResetCallbackType = std::function<void(std::shared_ptr<T> particle)>;

    template <typename InitCallbackT>
    static std::shared_ptr<ParticleSystem<T, N>> createPS(
        InitCallbackT const& init, ResetCallbackType const reset)
    {
        return std::make_shared<ParticleSystem<T, N>>(init, reset);
    }

    template <typename InitCallbackT>
    ParticleSystem(InitCallbackT const& init, ResetCallbackType const reset)
        : m_resetCallback { reset }
        , m_particles {}
        , m_currentIndex { 0 }
    {
        for (auto& p : m_particles) {
            p = init();
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
    ResetCallbackType m_resetCallback {};
    std::array<std::shared_ptr<T>, N> m_particles;

    std::size_t m_currentIndex { 0U };

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
};

} // namespace jt

#endif // GUARD_JAMTEMPLATE_PARTICLE_SYSTEM_HPP_GUARD
