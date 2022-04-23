#set( $_HAS_SPRITE = ($SpriteName != ''))
#set( $_HAS_ANIMATION = ($AnimationName != ''))
#set( $_HAS_SOUND = ($SoundName != ''))
#set( $_HAS_PHYSICS = ($Physics != ''))

#[[#include]]# "${NAME}.hpp"
#if ($_HAS_ANIMATION)
#[[#include]]# <animation.hpp>
#end
#if ($_HAS_SPRITE)
#[[#include]]# <sprite.hpp>
#end
#if ($_HAS_SOUND)
#[[#include]]# <sprite.hpp>
#end
#[[#include]]# <game_interface.hpp>



#if ($_HAS_PHYSICS)
${ClassName}::${ClassName}(std::shared_ptr<jt::Box2DWorldInterface> world, b2BodyDef const* def)
: jt::Box2DObject { world, def }
{
	
}
#end


void ${ClassName}::doCreate()
{
#if ($_HAS_ANIMATION)
	${AnimationName} = std::make_shared<jt::Animation>();
	${AnimationName}->loadFromJson(/*TODO*/ "", getGame()->gfx().textureManager());
	${AnimationName}->play(/*TODO*/"idle");
#end

#if ($_HAS_SPRITE)
	${SpriteName} = std::make_shared<jt::Sprite>(/*TODO*/ "", getGame()->gfx().textureManager());
#end

#if ($_HAS_SOUND)
	${SoundName} = getGame()->audio().addTemporarySound(/*TODO*/"");
#end
}

void ${ClassName}::doUpdate(float const elapsed)
{
#if ($_HAS_ANIMATION)
	#if ($_HAS_PHYSICS)
		${AnimationName}->setPosition(getPosition());
	#end
		${AnimationName}->update(elapsed);
#end
#if ($_HAS_SPRITE)
	#if ($_HAS_PHYSICS)
		${SpriteName}->setPosition(getPosition());
	#end
		${SpriteName}->update(elapsed);
#end
}

void ${ClassName}::doDraw() const
{
#if ($_HAS_ANIMATION)
	${AnimationName}->draw(getGame()->gfx().target());
#end
#if ($_HAS_SPRITE)
	${SpriteName}->draw(getGame()->gfx().target());
#end
}
