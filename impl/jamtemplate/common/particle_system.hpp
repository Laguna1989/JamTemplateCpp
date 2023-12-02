#ifndef JAMTEMPLATE_PARTICLE_SYSTEM_HPP
#define JAMTEMPLATE_PARTICLE_SYSTEM_HPP

#include <circular_buffer.hpp>
#include <game_object.hpp>
#include <cstddef>
#include <functional>
#include <memory>

namespace jt {

template <class T, std::size_t N>
class ParticleSystem : public GameObject {
public:
    using ResetCallbackType
        = std::function<void(std::shared_ptr<T>& particle, jt::Vector2f const& pos)>;

    /// Create a Particle System
    /// \tparam InitCallbackT Type of the init callback, should be of type T(void)
    /// \param init init callback
    /// \param reset reset callback
    /// \return shared pointer to the created ParticleSystem
    template <typename InitCallbackT>
    static std::shared_ptr<ParticleSystem<T, N>> createPS(
        InitCallbackT const& init, ResetCallbackType const reset)
    {
        return std::make_shared<ParticleSystem<T, N>>(init, reset);
    }

    /// Constructor
    /// \tparam InitCallbackT Type of the init callback, should be of type T(void)
    /// \param init init callback
    /// \param reset reset callback
    template <typename InitCallbackT>
    ParticleSystem(InitCallbackT const& init, ResetCallbackType const reset)
        : m_resetCallback { reset }
    {
        std::generate(m_particles.begin(), m_particles.end(), init);
    };

    /// Fire the particle system, creating num particles
    /// \param num the amount of particles to spawn
    /// \param pos the position where to spawn the particles
    void fire(unsigned int num = 1, jt::Vector2f const& pos = jt::Vector2f {})
    {
        for (auto i = 0u; i != num; ++i) {
            m_resetCallback(m_particles[m_currentIndex], pos);
            m_currentIndex++;
        }
    };

    /// Execute a function for each particle
    /// \param fun function to execute for each particle
    void forEach(std::function<void(std::shared_ptr<T>&)> const& fun)
    {
        for (auto& p : m_particles) {
            fun(p);
        }
    }

private:
    ResetCallbackType m_resetCallback {};
    mutable jt::CircularBuffer<std::shared_ptr<T>, N> m_particles {};
    std::size_t m_currentIndex { 0u };

    void doUpdate(float const elapsed) override
    {
        for (auto& p : m_particles) {
            p->update(elapsed);
        }
    }

    void doDraw() const override
    {
        for (auto const& p : m_particles) {
            p->draw(renderTarget());
        }
    }
};

} // namespace jt

#endif // JAMTEMPLATE_PARTICLE_SYSTEM_HPP
