#include "../../punk_engine.h"

int main()
{
	Math::vec3 p[] = {
		Math::vec3(-1, -2, 1),
		Math::vec3(1, 0, 2),
		Math::vec3(2, -1, 3),
		Math::vec3(2, -1, 2) };

	Math::BoundingBox bbox;
	bbox.Create((float*)p, 4, sizeof(Math::vec3));

	return 0;
}