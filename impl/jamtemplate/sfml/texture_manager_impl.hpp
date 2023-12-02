#ifndef JAMTEMPLATE_TEXTURE_MANAGER_IMPL_HPP
#define JAMTEMPLATE_TEXTURE_MANAGER_IMPL_HPP

#include <SFML/Graphics.hpp>
#include <texture_manager_interface.hpp>
#include <map>
#include <memory>

namespace jt {
class TextureManagerImpl : public ::jt::TextureManagerInterface {
public:
    explicit TextureManagerImpl(std::shared_ptr<jt::RenderTargetLayer> renderer);
    sf::Texture& get(std::string const& str) override;
    void reset() override;
    std::string getFlashName(std::string const& str) override;
    std::size_t getNumberOfTextures() noexcept override;

private:
    std::map<std::string, sf::Texture> m_textures;
    bool containsTexture(std::string const& str) const;
};
} // namespace jt

#endif // JAMTEMPLATE_TEXTURE_MANAGER_IMPL_HPP
