#ifndef BULLET_HPP
#define BULLET_HPP

#include "Object.hpp"

#include <SFML/Graphics/CircleShape.hpp>

class Bullet : public Object
{
public:
	Bullet(sf::Vector2f position = {0.f, 0.f}, sf::Vector2f velocity = {0.f, 0.f});
	virtual ~Bullet() = default;

private:
	virtual const sf::Shape& getShape() const override;

	sf::CircleShape shape;
};

#endif
