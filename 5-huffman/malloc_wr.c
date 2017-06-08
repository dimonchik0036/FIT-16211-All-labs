//	 Labs: 5-huffman
// Author: Dimonchik0036

#include <stdio.h>
#include <stdlib.h>

void* malloc_wr(size_t count_byte)
{
	void *ptmp = malloc(count_byte);

	if (!ptmp)
	{
		fprintf(stderr, " Can't alloc memory. Program exit\n");
		exit(EXIT_FAILURE);
	}
	return ptmp;
}
