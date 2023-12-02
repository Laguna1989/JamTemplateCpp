#include "animation.hpp"
#include <aselib/aseprite_data.hpp>
#include <math_helper.hpp>
#include <nlohmann.hpp>
#include <sprite.hpp>
#include <strutils.hpp>
#include <system_helper.hpp>
#include <texture_manager_interface.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

namespace {

std::shared_ptr<jt::Sprite>& getCurrentSprite(
    jt::Animation::AnimationMapType& frames, std::string const& animName, size_t const animIndex)
{
    auto const cit = frames.find(animName);
    if (cit == frames.cend()) {
        throw std::invalid_argument { "AnimName: '" + animName + "' not part of animation" };
    }

    return cit->second.at(animIndex);
}

} // namespace

void jt::Animation::add(std::string const& fileName, std::string const& animName,
    jt::Vector2u const& imageSize, std::vector<unsigned int> const& frameIndices,
    float frameTimeInSeconds, TextureManagerInterface& textureManager)
{
    if (frameTimeInSeconds <= 0) {
        throw std::invalid_argument { "animation frame time is negative or zero." };
    }
    std::vector<float> frameTimes;
    frameTimes.resize(frameIndices.size(), frameTimeInSeconds);
    add(fileName, animName, imageSize, frameIndices, frameTimes, textureManager);
}

void jt::Animation::add(std::string const& fileName, std::string const& animName,
    jt::Vector2u const& imageSize, std::vector<unsigned int> const& frameIndices,
    std::vector<float> const& frameTimesInSeconds, jt::TextureManagerInterface& textureManager)
{
    if (frameIndices.empty()) {
        throw std::invalid_argument { "animation frame indices are empty." };
    }
    if (animName.empty()) {
        throw std::invalid_argument { "animation name is empty." };
    }
    if (frameTimesInSeconds.empty()) {
        throw std::invalid_argument { "frametimes are empty." };
    }

    if (frameTimesInSeconds.size() != frameIndices.size()) {
        throw std::invalid_argument { "different sizes for frametimes and frame indices" };
    }

    if (m_frames.contains(animName)) {
        std::cout << "Warning: Overwriting old animation with name: " << animName << std::endl;
    }

    m_frames[animName] = std::vector<jt::Sprite::Sptr> {};

    for (auto const idx : frameIndices) {
        jt::Recti const rect { static_cast<int>(idx * imageSize.x), 0,
            static_cast<int>(imageSize.x), static_cast<int>(imageSize.y) };
        auto sptr = std::make_shared<Sprite>(fileName, rect, textureManager);
        m_frames[animName].push_back(sptr);
    }
    m_time[animName] = frameTimesInSeconds;
    m_isLooping[animName] = true;
}

void jt::Animation::loadFromJson(
    std::string const& jsonFileName, TextureManagerInterface& textureManager)
{
    m_frames.clear();
    m_time.clear();

    if (!jsonFileName.ends_with(".json")) {
        throw std::invalid_argument { "file '" + jsonFileName + "' is not a json file" };
    }
    if (!jt::SystemHelper::checkForValidFile(jsonFileName)) {
        throw std::invalid_argument { "file '" + jsonFileName + "' is not a regular file" };
    }

    auto const filePathWithoutExtension = jsonFileName.substr(0, jsonFileName.length() - 5);

    auto const imageFileName = filePathWithoutExtension + ".png";

    auto const baseAnimName = strutil::split(filePathWithoutExtension, "/").back();

    std::ifstream file { jsonFileName };
    nlohmann::json j;
    file >> j;

    if (j.count("frames") == 0) {
        throw std::invalid_argument { "json file does not have 'frames' entry" };
    }
    if (!j["frames"].is_object()) {
        throw std::invalid_argument { "json 'frames' is not an array" };
    }
    if (j.count("meta") == 0) {
        throw std::invalid_argument { "json file does not have 'meta' entry" };
    }
    if (j["meta"].count("frameTags") == 0) {
        throw std::invalid_argument { "json file does not have 'meta.frameTags' entry" };
    }
    if (!j["meta"]["frameTags"].is_array()) {
        throw std::invalid_argument { "json 'meta.frameTags' is not an array" };
    }
    for (auto const& frame : j["meta"]["frameTags"]) {
        auto const animationName = frame["name"].get<std::string>();
        auto const animationStart = frame["from"].get<unsigned int>();
        auto const animationEnd = frame["to"].get<unsigned int>();

        auto const frameIndices = jt::MathHelper::numbersBetween(animationStart, animationEnd);
        std::vector<float> frameTimes;

        auto const startFrameName = baseAnimName + " " + std::to_string(animationStart) + ".ase";
        if (!j["frames"].contains(startFrameName)) {
            throw std::invalid_argument { "'frames/" + startFrameName + "' does not exist" };
        }
        auto const width = j["frames"][startFrameName]["sourceSize"]["w"].get<unsigned int>();
        auto const height = j["frames"][startFrameName]["sourceSize"]["h"].get<unsigned int>();

        for (auto const id : frameIndices) {
            auto const frameName = baseAnimName + " " + std::to_string(id) + ".ase";
            if (j["frames"].count(frameName) == 0) {
                throw std::invalid_argument { "json file does not have 'frames." + frameName
                    + "' entry" };
            }
            if (j["frames"][frameName].count("duration") == 0) {
                throw std::invalid_argument { "json file does not have 'frames." + frameName
                    + ".duration' entry" };
            }
            auto const frameTime = j["frames"][frameName]["duration"].get<float>() / 1000.0f;
            frameTimes.push_back(frameTime);
        }

        add(imageFileName, animationName, jt::Vector2u { width, height }, frameIndices, frameTimes,
            textureManager);
    }
}

void jt::Animation::loadFromAseprite(
    std::string const& asepriteFileName, jt::TextureManagerInterface& textureManager)
{
    aselib::AsepriteData ase { asepriteFileName };

    auto const imageSize
        = jt::Vector2u { ase.m_header.m_width_in_pixel, ase.m_header.m_height_in_pixel };

    if (ase.m_frames[0].m_chunks.m_tag_chunks.empty()) {
        // no custom animation defined in aseprite, use all frames as default "idle" animation
        std::vector<unsigned int> frameIDs
            = jt::MathHelper::numbersBetween(0u, static_cast<unsigned int>(ase.m_frames.size()));

        add(asepriteFileName, "idle", imageSize, frameIDs, 0.1f, textureManager);

    } else {
        for (auto const& tagChunk : ase.m_frames[0].m_chunks.m_tag_chunks) {
            for (auto const& tag : tagChunk.m_tags) {
                auto const animName = tag.m_tag_name;
                auto const startFrame = tag.m_from_frame;
                auto const endFrame = tag.m_to_frame;
                auto const repeat = tag.m_repeat_animation == 0;

                std::vector<unsigned int> frameIDs = jt::MathHelper::numbersBetween(
                    static_cast<unsigned int>(startFrame), static_cast<unsigned int>(endFrame));

                std::vector<float> frame_times;
                frame_times.resize(frameIDs.size());
                std::transform(
                    frameIDs.cbegin(), frameIDs.cend(), frame_times.begin(), [&ase](auto const id) {
                        // aseprite stores the frametime in milliseconds, JT expects it in seconds.
                        return ase.m_frames.at(id).m_frame_header.m_frame_duration / 1000.0f;
                    });

                add(asepriteFileName, animName, imageSize, frameIDs, frame_times, textureManager);
                setLooping(animName, repeat);
            }
        }
    }
}

bool jt::Animation::hasAnimation(std::string const& animationName) const
{
    return (m_frames.contains(animationName));
}

std::vector<std::string> jt::Animation::getAllAvailableAnimationNames() const
{
    std::vector<std::string> names;
    names.resize(m_frames.size());
    std::transform(m_frames.cbegin(), m_frames.cend(), names.begin(),
        [](auto kvp) -> std::string { return kvp.first; });

    return names;
}

std::string jt::Animation::getRandomAnimationName() const
{
    if (m_frames.empty()) {
        throw std::invalid_argument {
            "can not get random animation name if no animation has been added"
        };
    }
    return jt::SystemHelper::select_randomly(m_frames).first;
}

void jt::Animation::play(std::string const& animationName, size_t startFrameIndex, bool restart)
{
    m_isValid = hasAnimation(animationName);
    if (!m_isValid) {
        std::cout << "Warning: Play Animation with invalid animName: '" + m_currentAnimName + "'\n";
        return;
    }

    if (m_currentAnimName != animationName || restart) {
        m_currentIdx = startFrameIndex;
        m_currentAnimName = animationName;
        m_frameTime = 0;
    }
}

void jt::Animation::setColor(jt::Color const& col)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setColor(col);
        }
    }
}

jt::Color jt::Animation::getColor() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getColor();
}

void jt::Animation::setPosition(jt::Vector2f const& pos) { m_position = pos; }

jt::Vector2f jt::Animation::getPosition() const { return m_position; }

jt::Rectf jt::Animation::getGlobalBounds() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getGlobalBounds();
}

jt::Rectf jt::Animation::getLocalBounds() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getLocalBounds();
}

void jt::Animation::setScale(jt::Vector2f const& scale)
{
    for (auto& kvp : m_frames) {
        for (auto& spr : kvp.second) {
            spr->setScale(scale);
        }
    }
}

jt::Vector2f jt::Animation::getScale() const
{
    return getCurrentSprite(m_frames, m_currentAnimName, m_currentIdx)->getScale();
}

void jt::Animation::setOriginInternal(jt::Vector2f const& origin)
{
    for (auto const& kvp : m_frames) {
        for (auto const& sptr : kvp.second) {
            sptr->setOrigin(origin);
        }
    }
}

void jt::Animation::setOutline(jt::Color const& color, int width)
{
    DrawableImpl::setOutline(color, width);
    for (auto const& kvp : m_frames) {
        for (auto const& sprite : kvp.second) {
            sprite->setOutline(color, width);
        }
    }
}

void jt::Animation::setShadow(jt::Color const& color, jt::Vector2f const& offset)
{
    DrawableImpl::setShadow(color, offset);
    for (auto const& kvp : m_frames) {
        for (auto const& sprite : kvp.second) {
            sprite->setShadow(color, offset);
        }
    }
}

void jt::Animation::setShadowActive(bool active)
{
    DrawableImpl::setShadowActive(active);
    for (auto const& kvp : m_frames) {
        for (auto const& sprite : kvp.second) {
            sprite->setShadowActive(active);
        }
    }
}

void jt::Animation::doDrawShadow(std::shared_ptr<jt::RenderTargetLayer> const /*sptr*/) const { }

void jt::Animation::doDrawOutline(std::shared_ptr<jt::RenderTargetLayer> const /*sptr*/) const { }

void jt::Animation::doDraw(std::shared_ptr<jt::RenderTargetLayer> const sptr) const
{
    if (!m_isValid) {
        std::cerr << "Warning: Drawing Animation with invalid animName: '" + m_currentAnimName
                + "'\n";
        return;
    }
    m_frames.at(m_currentAnimName).at(m_currentIdx)->setBlendMode(getBlendMode());
    m_frames.at(m_currentAnimName).at(m_currentIdx)->draw(sptr);
}

void jt::Animation::doDrawFlash(std::shared_ptr<jt::RenderTargetLayer> const /*sptr*/) const { }

void jt::Animation::doFlashImpl(float t, jt::Color col)
{
    for (auto& kvp : m_frames) {
        for (auto& sprite : kvp.second) {
            sprite->flash(t, col);
        }
    }
}

void jt::Animation::doUpdate(float elapsed)
{
    if (!m_isValid) {
        std::cout << "Warning: Update Animation with invalid animName: '" + m_currentAnimName
                + "'\n";
        return;
    }

    // proceed time
    m_frameTime += elapsed * m_animationplaybackSpeed;

    auto const frame_time = m_time[m_currentAnimName][m_currentIdx];
    // increase index
    while (m_frameTime >= frame_time) {
        m_frameTime -= frame_time;
        m_currentIdx++;
    }
    // wrap index or fix index at last frame
    if (m_currentIdx >= m_frames.at(m_currentAnimName).size()) {
        if (getCurrentAnimationIsLooping()) {
            m_currentIdx = 0;
        } else {
            m_currentIdx = m_frames.at(m_currentAnimName).size() - 1;
        }
    }

    // update values for current sprite
    auto const& currentSprite = m_frames.at(m_currentAnimName).at(m_currentIdx);
    currentSprite->setPosition(m_position + getShakeOffset() + getOffset());
    currentSprite->setIgnoreCamMovement(DrawableImpl::getIgnoreCamMovement());

    // update all sprites
    for (auto& kvp : m_frames) {
        for (auto& sprite : kvp.second) {
            sprite->update(elapsed);
        }
    }
}

void jt::Animation::doRotate(float rot)
{
    for (auto& kvp : m_frames) {
        for (auto& sprite : kvp.second) {
            sprite->setRotation(rot);
        }
    }
}

float jt::Animation::getCurrentAnimationSingleFrameTime() const
{
    return m_time.at(m_currentAnimName).at(m_currentIdx);
}

float jt::Animation::getCurrentAnimTotalTime() const
{
    float sum = 0.0f;
    for (auto frameTime : m_time.at(m_currentAnimName)) {
        sum += frameTime;
    }
    return sum;
}

float jt::Animation::getAnimTotalTimeFor(std::string const& animName)
{
    if (!hasAnimation(animName)) {
        throw std::invalid_argument { "no animation with name " + animName };
    }
    float sum = 0.0f;
    for (auto frameTime : m_time.at(animName)) {
        sum += frameTime;
    }
    return sum;
}

std::size_t jt::Animation::getNumberOfFramesInCurrentAnimation() const
{
    return m_frames.at(m_currentAnimName).size();
}

std::string jt::Animation::getCurrentAnimationName() const { return m_currentAnimName; }

bool jt::Animation::getCurrentAnimationIsLooping() const
{
    if (!hasAnimation(m_currentAnimName)) {
        return true;
    }
    return m_isLooping.at(m_currentAnimName);
}

bool jt::Animation::getIsLoopingFor(std::string const& animName) const
{
    if (!hasAnimation(animName)) {
        throw std::invalid_argument { "no animation with name " + animName };
    }
    return m_isLooping.at(animName);
}

void jt::Animation::setLooping(std::string const& animName, bool isLooping)
{
    if (!hasAnimation(animName)) {
        throw std::invalid_argument { "invalid animation name: " + animName };
    }
    m_isLooping[animName] = isLooping;
}

void jt::Animation::setLoopingAll(bool isLooping)
{
    for (auto& l : m_isLooping) {
        l.second = isLooping;
    }
}

std::size_t jt::Animation::getCurrentAnimationFrameIndex() const { return m_currentIdx; }

void jt::Animation::setFrameTimes(
    std::string const& animationName, std::vector<float> const& frameTimes)
{
    if (!m_frames.contains(animationName)) {
        throw std::invalid_argument { "cannot set frame times for invalid animation: "
            + animationName };
    }
    if (frameTimes.size() != m_frames[animationName].size()) {
        throw std::invalid_argument { "frame times size does not match frame index size" };
    }
    m_time[animationName] = frameTimes;
}

void jt::Animation::setAnimationSpeedFactor(float factor) { m_animationplaybackSpeed = factor; }

float jt::Animation::getAnimationSpeedFactor() const { return m_animationplaybackSpeed; }
