#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

#include <SFML/Graphics/Shape.hpp>

class Object : public sf::Drawable, public sf::Transformable
{
public:
	static sf::Vector2u windowSize;

	Object(sf::Vector2f position = {0.f, 0.f}, sf::Vector2f velocity = {0.f, 0.f});
	virtual ~Object() = default;

	float getRadius() const;
	sf::Vector2f heading() const;

	sf::Vector2f getPreviousPosition() const;
	void setPosition(sf::Vector2f pos);
	void setPosition(float x, float y);

	void update(float dt);

	sf::Vector2f velocity;

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override final;

	virtual const sf::Shape& getShape() const = 0;

	virtual void privateUpdate(float dt);

	static void boundToWindow(sf::Vector2f& vec);

	sf::Vector2f previousPosition;
};

#endif
