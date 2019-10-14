#pragma once

#include <sstream>

template<typename T>
std::string ToString(T value)
{
	std::stringstream ss;
	ss << value;
	std::string str = ss.str();
	return str;
}
