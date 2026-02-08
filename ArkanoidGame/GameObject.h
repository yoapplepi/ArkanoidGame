#pragma once
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	class GameObject
	{
	public:

		GameObject() = default;

		GameObject(const std::string& textureId, const sf::Vector2f& position, float width, float heigth);
		virtual ~GameObject() = default;

		virtual void Init() = 0;
		virtual void Update(float timeDelta) = 0;
		virtual void Draw(sf::RenderWindow& window);

		const sf::Vector2f& GetPosition() const { return sprite.getPosition(); }
		const sf::FloatRect& GetRect() const { return sprite.getGlobalBounds(); }

	protected:
		sf::Sprite sprite;
		sf::Texture texture;
	};
}