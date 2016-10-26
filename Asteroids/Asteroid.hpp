#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include "Object.hpp"

#include "Time.hpp"

#include <SFML/Graphics/CircleShape.hpp>

class Asteroid : public Object
{
public:
	static bool spawn(Time newTime);

	Asteroid(sf::Vector2f position = {0.f, 0.f}, sf::Vector2f velocity = {0.f, 0.f});
	virtual ~Asteroid() = default;

private:
	static Time lastSpawn;

	virtual const sf::Shape& getShape() const override;

	sf::CircleShape shape;
};

#endif
