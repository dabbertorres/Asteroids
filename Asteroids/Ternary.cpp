#include "Ternary.hpp"

Ternary::Ternary(std::int8_t val)
	: value(val)
{}

Ternary& Ternary::operator=(std::int8_t val)
{
	value = bound(val);
	return *this;
}

Ternary& Ternary::operator++()
{
	value = bound(value + 1);
	return *this;
}

Ternary& Ternary::operator--()
{
	value = bound(value - 1);
	return *this;
}

Ternary Ternary::operator++(int)
{
	auto old = value;
	value = bound(value + 1);
	return Ternary{old};
}

Ternary Ternary::operator--(int)
{
	auto old = value;
	value = bound(value - 1);
	return Ternary{old};
}

Ternary::operator std::int8_t() const
{
	return value;
}

std::int8_t Ternary::bound(std::int8_t val)
{
	return	val < -1 ? -1 : 
			val > 1 ? 1 :
			val;
}
