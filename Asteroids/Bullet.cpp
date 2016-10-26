#include "Bullet.hpp"

constexpr float BASE_VELOCITY = 200.f;

Bullet::Bullet(sf::Vector2f position, sf::Vector2f velocity)
	: Object(position, velocity * BASE_VELOCITY),
	shape{10.f, 4}
{
	shape.setFillColor(sf::Color::White);
	shape.setOrigin(shape.getLocalBounds().width / 2.f, shape.getLocalBounds().height / 2.f);
}

const sf::Shape& Bullet::getShape() const
{
	return shape;
}

