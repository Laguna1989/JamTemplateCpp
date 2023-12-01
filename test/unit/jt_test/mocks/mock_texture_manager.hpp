#ifndef JAMTEMPLATE_MOCK_TEXTURE_MANAGER_HPP
#define JAMTEMPLATE_MOCK_TEXTURE_MANAGER_HPP

#include "texture_manager_interface.hpp"

#if USE_SFML
class MockTextureManager : public jt::TextureManagerInterface {
public:
    sf::Texture& get(std::string const& /*str*/) override
    {
        throw std::logic_error { "never call this on the mock" };
    }

    void reset() override { }

    std::string getFlashName(std::string const& /*str*/) override { return ""; }

    std::size_t getNumberOfTextures() noexcept override { return 0u; }
};
#else
class MockTextureManager : public jt::TextureManagerInterface {
public:
    std::shared_ptr<SDL_Texture> get(std::string const& /*str*/) override { return nullptr; }

    void reset() override { }

    std::string getFlashName(std::string const& /*str*/) override { return ""; }

    std::size_t getNumberOfTextures() noexcept override { return 0u; }
};
#endif

#endif // JAMTEMPLATE_MOCK_TEXTURE_MANAGER_HPP
