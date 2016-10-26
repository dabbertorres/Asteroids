#include "Asteroid.hpp"

constexpr auto ASTEROID_SPAWN_PERIOD = 5.0s;

Time Asteroid::lastSpawn;

bool Asteroid::spawn(Time newTime)
{
	if(newTime - lastSpawn > ASTEROID_SPAWN_PERIOD)
	{
		lastSpawn = newTime;
		return true;
	}
	else
	{
		return false;
	}
}

Asteroid::Asteroid(sf::Vector2f position, sf::Vector2f velocity)
	: Object(position, velocity),
	shape{50.f, 8}
{
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(shape.getLocalBounds().width / 2.f, shape.getLocalBounds().height / 2.f);
}

const sf::Shape& Asteroid::getShape() const
{
	return shape;
}
