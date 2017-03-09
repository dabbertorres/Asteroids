#include "Object.hpp"

#include <cmath>

sf::Vector2u Object::windowSize = {0u, 0u};

Object::Object(sf::Vector2f position, sf::Vector2f velocity)
	: velocity{velocity}
{
	setPosition(position);
}

float Object::getRadius() const
{
	auto bounds = getShape().getGlobalBounds();
	return std::max(bounds.width, bounds.height) / 2.f;
}

sf::Vector2f Object::heading() const
{
	constexpr float PI = 3.14159f;

	// degrees [0, 360] to radians [-PI, PI], then shift by 90 deg (PI / 2) so 0 deg is up (not right)
	float rot = getRotation() * PI / 180.f - PI / 2.f;
	return {std::cos(rot), std::sin(rot)};
}

sf::Vector2f Object::getPreviousPosition() const
{
	return previousPosition;
}

void Object::setPosition(sf::Vector2f pos)
{
	previousPosition = getPosition();
	boundToWindow(pos);
	sf::Transformable::setPosition(pos);
}

void Object::setPosition(float x, float y)
{
	setPosition({x, y});
}

void Object::update(float dt)
{
	privateUpdate(dt);

	sf::Vector2f newPos = getPosition() + velocity * dt;
	boundToWindow(newPos);
	setPosition(newPos);
}

void Object::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    auto& shape = getShape();

    // round position for more accurate drawing (there's nothing smaller than a pixel after all!)
    auto pos = shape.getPosition();
    sf::Vector2f rounded{std::round(pos.x), std::round(pos.y)};
    
    auto transform = getTransform();
    states.transform *= transform.translate(rounded - pos);

	target.draw(shape, states);
}

void Object::privateUpdate(float)
{
	// do nothing by default
}

void Object::boundToWindow(sf::Vector2f& vec)
{
	if(vec.x < 0)
		vec.x = static_cast<float>(windowSize.x);
	else if(vec.x > windowSize.x)
		vec.x = 0;

	if(vec.y < 0)
		vec.y = static_cast<float>(windowSize.y);
	else if(vec.y > windowSize.y)
		vec.y = 0;
}
