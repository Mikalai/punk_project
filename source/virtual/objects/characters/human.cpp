#include "human_impl.h"

namespace Virtual
{
	Human::Human() 
		: impl(nullptr)
	{}

	Human::~Human()
	{
		delete impl;
	}
}