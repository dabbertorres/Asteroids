#ifndef SHIP_HPP
#define SHIP_HPP

#include "Object.hpp"

#include "Time.hpp"

#include "Ternary.hpp"
#include <SFML/Graphics/ConvexShape.hpp>

class Ship : public Object
{
public:
	Ship(sf::Vector2f position = {0.f, 0.f}, sf::Vector2f velocity = {0.f, 0.f});
	virtual ~Ship() = default;

	bool fire(Time newTime);

	// controls
	Ternary thrust;
	Ternary rotation;
	bool isFiring;

private:
	virtual const sf::Shape& getShape() const override;

	virtual void privateUpdate(float dt) override;

	sf::ConvexShape shape;
	Time lastFireTime;
};

#endif
