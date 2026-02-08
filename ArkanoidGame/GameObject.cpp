#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <assert.h>
#include "Sprite.h"

namespace ArkanoidGame
{
	GameObject::GameObject(const std::string& texturePath, const sf::Vector2f& position, float width, float heigth)
	{
		assert(texture.loadFromFile(texturePath));

		InitSprite(sprite, width, heigth, texture);
		sprite.setPosition(position);
	}

	void GameObject::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}
}