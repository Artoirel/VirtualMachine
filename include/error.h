#ifndef __ERROR_H__
#define __ERROR_H__

#include <stdio.h>
#include <stdlib.h>

#define THROW_ERROR(y) \
	fprintf(stderr, y); \
	fflush(stderr); \
	exit(EXIT_FAILURE);
#endif
