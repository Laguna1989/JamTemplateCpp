#[[#ifndef]]# ${INCLUDE_GUARD}
#[[#define]]# ${INCLUDE_GUARD}

#set( $_HAS_SPRITE = ($SpriteName != ''))
#set( $_HAS_ANIMATION = ($AnimationName != ''))
#set( $_HAS_SOUND = ($SoundName != ''))
#set( $_HAS_PHYSICS = ($Physics != ''))

#if ($_HAS_SOUND)
#[[#include]]# <audio/sound_interface.hpp>
#end
#if ($_HAS_PHYSICS)
#[[#include]]# <box2dwrapper/box2d_object.hpp>
#else
#[[#include]]# <game_object.hpp>
#end

#[[#include]]# <memory>


namespace jt{
#if ($_HAS_ANIMATION)
class Animation;
#end
#if ($_HAS_SPRITE)
class Sprite;
#end
}

class ${ClassName} : public 
#if ($_HAS_PHYSICS)
jt::Box2DObject
#else
jt::GameObject
#end
 {
#if ($_HAS_PHYSICS)
public:
 ${ClassName}(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def);
#end
private:
#if ($_HAS_SPRITE)
    std::shared_ptr<jt::Sprite> ${SpriteName};
#end
#if ($_HAS_ANIMATION)
    std::shared_ptr<jt::Animation> ${AnimationName};
#end
#if ($_HAS_SOUND)
    std::shared_ptr<jt::SoundInterface> ${SoundName};
#end

    void doCreate() override;
    void doUpdate(float const elapsed) override;
    void doDraw() const override;

};
#[[#endif]]# //${INCLUDE_GUARD}