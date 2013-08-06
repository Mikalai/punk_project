#include "generator.h"
#include <string.h>

const char* supported_type[] =
{"checker",
 "noise"};

void (*Creator[])(int, char**) =
{
	CreateChecker,
	CreateNoise
};

int get_type(const char* type)
{
	int cur_type = START;
	while (cur_type != END)
	{
		if (strcmp(supported_type[cur_type], type) == 0)
		{
			return (int)cur_type;
		}
		cur_type++;
	}
	return END;
}
