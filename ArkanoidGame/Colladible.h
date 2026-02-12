#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace ArkanioidGame
{
	class Colladible
	{
	protected:
		virtual void OnHit() = 0;

	public:
		virtual bool CheckCollision(std::shared_ptr<Colladible> collidable)
		{
			if (GetCollision(collidable))
			{
				OnHit();
				collidable->OnHit();
				return true;
			}

			return false;
		}

		virtual bool GetCollision(std::shared_ptr<Colladible> collidable) const = 0;
	};
}