#include "Ship.hpp"

constexpr float ACCEL = 200.f;
constexpr float ROT_VELOCITY = 180.f;
constexpr auto FIRE_PERIOD = 0.75s;

Ship::Ship(sf::Vector2f position, sf::Vector2f velocity)
	: Object(position, velocity),
	shape{3},
	isFiring(false)
{
	// isosceles triangle
	// values picked because they looked good
	shape.setPoint(0, {-0.67f, 0.5f});
	shape.setPoint(1, {0.f, -1.f});
	shape.setPoint(2, {0.67f, 0.5f});

	shape.setFillColor(sf::Color::Green);
	shape.setScale({20.f, 20.f});
}

bool Ship::fire(Time newTime)
{
	if(isFiring && newTime - lastFireTime >= FIRE_PERIOD)
	{
		lastFireTime = newTime;
		return true;
	}
	else
	{
		return false;
	}
}

const sf::Shape& Ship::getShape() const
{
	return shape;
}

void Ship::privateUpdate(float dt)
{
	velocity += ACCEL * dt * thrust * heading();
	rotate(ROT_VELOCITY * dt * rotation);
}
