#ifndef JAMTEMPLATE_ANIMATION_HPP_INCLUDEGUARD
#define JAMTEMPLATE_ANIMATION_HPP_INCLUDEGUARD

#include <map>
#include <iostream>
#include <vector>
#include <memory>

#include <SFML/Graphics.hpp>

#include "SmartSprite.hpp"

namespace JamTemplate {

	class Animation : public SmartObject
	{
	public:
		Animation()
		{

		}

		void add(std::string fileName, std::string animName, sf::Vector2u size, std::vector<unsigned int> frameIndices, float frameTime)
		{
			if (frameIndices.size() == 0) return;
			m_frames[animName] = std::vector<JamTemplate::SmartSprite::Sptr>{};
			m_time[animName] = frameTime;

			for (const auto idx : frameIndices)
			{
				sf::IntRect rect{static_cast<int>(idx*size.x), 0, static_cast<int>(size.x), static_cast<int>(size.y)};
				SmartSprite::Sptr sptr = std::make_shared<SmartSprite>();
				sptr->loadSprite(fileName, rect);
				m_frames[animName].push_back(sptr);
			}
		}

		void play(std::string animName, size_t startFrame = 0)
		{
			m_currentIdx = startFrame;
			m_currentAnimName = animName;
			m_frameTime = 0;
		}

		void setColor(sf::Color const& col)
		{
			for (auto& kvp : m_frames)
			{
				for (auto& spr : kvp.second)
				{
					spr->setColor(col);
				}
			}
		}

		const sf::Color getColor() const
		{
			for (auto const& kvp : m_frames)
			{
				for (auto const& sptr : kvp.second)
				{
					return sptr->getColor();
				}
			}
			return sf::Color{};
		}

		void setPosition(sf::Vector2f const& pos)
		{
			m_position = pos;
		}
		const sf::Vector2f getPosition() const
		{
			return m_position;
		}


		sf::Transform const getTransform() const
		{
			for (auto const& kvp : m_frames)
			{
				for (auto const& sptr : kvp.second)
				{
					return sptr->getTransform();
				}
			}
			return sf::Transform{};
		}
		sf::FloatRect getGlobalBounds() const
		{
			for (auto const& kvp : m_frames)
			{
				for (auto const& sptr : kvp.second)
				{
					return sptr->getGlobalBounds();
				}
			}
			return sf::FloatRect{};
		}

		void setFlashColor(sf::Color const& col)
		{
			for (auto& kvp : m_frames)
			{
				for (auto& spr : kvp.second)
				{
					spr->setFlashColor(col);
				}
			}
		}
		const sf::Color getFlashColor() const
		{
			for (auto const& kvp : m_frames)
			{
				for (auto const& sptr : kvp.second)
				{
					return sptr->getFlashColor();
				}
			}
			return sf::Color{};
		}

		virtual void setScale(sf::Vector2f const& scale)
		{
			for (auto& kvp : m_frames)
			{
				for (auto& spr : kvp.second)
				{
					spr->setScale(scale);
				}
			}
		}
		virtual const sf::Vector2f getScale()
		{
			for (auto& kvp : m_frames)
			{
				for (auto const& sptr : kvp.second)
				{
					return sptr->getScale();
				}
			}
			return sf::Vector2f{1,1};
		}

	private:
		std::map<std::string, std::vector<SmartSprite::Sptr>> m_frames;
		std::map<std::string, float> m_time;
		
		size_t m_currentIdx = 0;
		std::string m_currentAnimName = "";

		sf::Vector2f m_position;

		float m_frameTime = 0;

		void doDraw(std::shared_ptr<sf::RenderTarget> sptr) const
		{
			if (m_frames.count(m_currentAnimName) == 0)
				return;

			m_frames.at(m_currentAnimName).at(m_currentIdx)->draw(sptr);
		}

		void doDrawFlash(std::shared_ptr<sf::RenderTarget> sptr) const
		{}

		virtual void doUpdate(float elapsed)
		{
			if (m_frames.count(m_currentAnimName) == 0)
				return;
			
			m_frameTime += elapsed;
			if (m_frameTime >= m_time[m_currentAnimName])
			{
				m_frameTime = 0;
				m_currentIdx++;
				if (m_currentIdx >= m_frames.at(m_currentAnimName).size())
				{
					m_currentIdx = 0;
				}
			}
			m_frames.at(m_currentAnimName).at(m_currentIdx)->setPosition(m_position + getShakeOffset());
			m_frames.at(m_currentAnimName).at(m_currentIdx)->update(elapsed);
		}

		
	};

} // namespace JamTemplate

#endif
