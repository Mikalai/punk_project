#include <stdio.h>
#include <string.h>
#include "generator.h"
//
//	syntax
//	width height alpha[0|1] type
//


int main(int argc, char** argv)
{
	if (argc < 5)
		printf("Syntax: %s width height type", argv[0]);

	int type = get_type(argv[3]);

	if (type == END)
	{
		printf("Unsupported type %s\n", argv[4]);
		return 0;
	}

	(*Creator[type])(argc, argv);

	return 0;
}