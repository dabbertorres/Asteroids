#ifndef TERNARY_HPP
#define TERNARY_HPP

#include <cstdint>

class Ternary
{
public:
	Ternary(std::int8_t = 0);

	Ternary& operator=(std::int8_t);

	// prefix
	Ternary& operator++();
	Ternary& operator--();

	// postfix
	Ternary operator++(int);
	Ternary operator--(int);

	operator std::int8_t() const;

private:
	static std::int8_t bound(std::int8_t);

	std::int8_t value;
};

#endif
