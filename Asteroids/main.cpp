#include <chrono>
#include <random>
#include <string>
#include <vector>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "Object.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"
#include "Asteroid.hpp"

#include "Time.hpp"

constexpr auto DELTA_TIME = std::chrono::duration_cast<Clock::duration>(1.0s / 60);
constexpr auto DELTA_TIME_SEC = static_cast<float>(DELTA_TIME.count()) / Clock::duration::period::den;

const sf::VideoMode WINDOW_MODE = {800, 600};

const std::uniform_int_distribution<int> booleanDist{0, 1};
const std::uniform_real_distribution<float> velocityDist{-50.f, 50.f};
std::mt19937 randGen;

void update(Ship& ship, std::vector<Bullet>& bullets, std::vector<Asteroid>& asteroids, Time newTime);
bool collision(const Object& one, const Object& two);
void interpolate(Ship& ship, std::vector<Bullet>& bullets, std::vector<Asteroid>& asteroids, Duration lag);
void handleEvents(sf::RenderWindow& window, Ship& ship);

int main(int, char**)
{
	{
		// initalize random number generator
		std::random_device rd;
		std::seed_seq seed{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
		randGen.seed(seed);
	}

	Object::windowSize = {WINDOW_MODE.width, WINDOW_MODE.height};

	sf::RenderWindow window{WINDOW_MODE, "Asteroids", sf::Style::Titlebar | sf::Style::Close};
	window.setVerticalSyncEnabled(true);

	auto currentTime = Clock::now();

	auto lag = Clock::duration::zero();

	Ship player;
	player.setPosition(WINDOW_MODE.width / 2.f, WINDOW_MODE.height / 2.f);

	std::vector<Asteroid> asteroids;
	std::vector<Bullet> bullets;

	while(window.isOpen())
	{
		auto newTime = Clock::now();

		// calc delta time (time between this frame and last frame)
		auto dt = newTime - currentTime;
		currentTime = newTime;

		// keep track of any timing discrepancies to determine
		// when to update vs when to draw
		lag += dt;

		// must handle events as often as possible, otherwise the OS gets antsy
		handleEvents(window, player);

		// update while we're lagging behind where we should be
		while(lag >= DELTA_TIME)
		{
			// "physics"
			update(player, bullets, asteroids, newTime);

			lag -= DELTA_TIME;
		}

		// due to an amount of time (< DELTA_TIME) probably being left over after updating,
		// interpolate positions of objects to keep things smooth
//		interpolate(player, bullets, asteroids, lag);

		window.clear();

		for(auto& a : asteroids)
			window.draw(a);

		for(auto& b : bullets)
			window.draw(b);

		window.draw(player);

		window.display();
	}

	return 0;
}

void update(Ship& ship, std::vector<Bullet>& bullets, std::vector<Asteroid>& asteroids, Time newTime)
{
	if(ship.fire(newTime))
	{
		bullets.emplace_back(ship.getPosition(), ship.heading());
	}

	if(Asteroid::spawn(newTime))
	{
		// create an Asteroid at a random corner of the window
		// and give it a random velocity
		sf::Vector2f position = {static_cast<float>(booleanDist(randGen) * WINDOW_MODE.width),
			static_cast<float>(booleanDist(randGen) * WINDOW_MODE.height)};
		sf::Vector2f velocity = {velocityDist(randGen), velocityDist(randGen)};

		asteroids.emplace_back(position, velocity);
	}

	ship.update(DELTA_TIME_SEC);

	for(auto& a : asteroids)
		a.update(DELTA_TIME_SEC);

	for(auto& b : bullets)
		b.update(DELTA_TIME_SEC);

	for(auto a = asteroids.begin(); a != asteroids.end(); )
	{
		// player and asteroids can collide
		if(collision(ship, *a))
		{
			// game over!
			break;
		}

		// bullets and asteroids can collide
		bool dead = false;

		for(auto b = bullets.begin(); b != bullets.end(); )
		{
			dead = collision(*a, *b);

			if(dead)
			{
				a = asteroids.erase(a);
				b = bullets.erase(b);

				// *a is gone, so we probably shouldn't try using it anymore
				// lets get a new one
				break;
			}
			else
			{
				++b;
			}
		}

		if(!dead)
			++a;
	}
}

bool collision(const Object& one, const Object& two)
{
	// simple circle-circle collision check:
	// if the distance between the centers is less than the sum of the radii, collision

	auto distVec = one.getPosition() - two.getPosition();
	auto dist = std::sqrt(distVec.x * distVec.x + distVec.y * distVec.y);

	return dist < one.getRadius() + two.getRadius();
}

void interpolate(Ship& ship, std::vector<Bullet>& bullets, std::vector<Asteroid>& asteroids, Duration lag)
{
	static auto toSec = [](Duration d) { return std::chrono::duration_cast<std::chrono::duration<float>>(d); };
	static auto interp = [](const Object& o, auto alpha) { return o.getPosition() * alpha + o.getPreviousPosition() * (1.f - alpha); };

	const auto alpha = toSec(lag) / toSec(DELTA_TIME);

	ship.setPosition(interp(ship, alpha));

	for(auto& b : bullets)
		b.setPosition(interp(b, alpha));

	for(auto& a : asteroids)
		a.setPosition(interp(a, alpha));
}

void handleEvents(sf::RenderWindow& window, Ship& ship)
{
	sf::Event event;
	while(window.pollEvent(event))
	{
		switch(event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				switch(event.key.code)
				{
					case sf::Keyboard::Escape:
						window.close();
						break;

					case sf::Keyboard::Up:
						++ship.thrust;
						break;

					case sf::Keyboard::Down:
						--ship.thrust;
						break;

					case sf::Keyboard::Left:
						--ship.rotation;
						break;

					case sf::Keyboard::Right:
						++ship.rotation;
						break;

					case sf::Keyboard::Space:
						ship.isFiring = true;
						break;

					default:
						break;
				}
				break;

			case sf::Event::KeyReleased:
				switch(event.key.code)
				{
					case sf::Keyboard::Up:
						--ship.thrust;
						break;

					case sf::Keyboard::Down:
						++ship.thrust;
						break;

					case sf::Keyboard::Left:
						++ship.rotation;
						break;

					case sf::Keyboard::Right:
						--ship.rotation;
						break;

					case sf::Keyboard::Space:
						ship.isFiring = false;
						break;

					default:
						break;
				}
				break;

			default:
				break;
		}
	}
}
