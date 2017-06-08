//	 Labs: 5-huffman
// Author: Dimonchik0036

#ifndef BITARRAY_H_
#define BITARRAY_H_
#include <limits.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char BARR_ELTYPE;

#define BARR_ELBITS (CHAR_BIT * sizeof(BARR_ELTYPE))
#define BARR_ARRAYSIZE(N) (((N) + BARR_ELBITS - 1) / BARR_ELBITS)
#define BARR_MALLOC(N) ((BARR_ELTYPE *)malloc(BARR_ARRAYSIZE(N) * sizeof(BARR_ELTYPE)))
#define BARR_FREE(barr) free(barr)
#define BARR_CLEARARRAY(barr, N) memset(barr, 0, BARR_ARRAYSIZE(N) * sizeof(BARR_ELTYPE))

#define BARR_ELNUM(N) ((N) / BARR_ELBITS)
#define BARR_BITNUM(N) ((N) % BARR_ELBITS)

#define BARR_SET(barr, N) ((barr)[BARR_ELNUM(N)] |= (BARR_ELTYPE) 1 << BARR_BITNUM(N))
#define BARR_CLEAR(barr, N) ((barr)[BARR_ELNUM(N)] &= ~((BARR_ELTYPE) 1 << BARR_BITNUM(N)))
#define BARR_TEST(barr, N) ((barr)[BARR_ELNUM(N)] & (BARR_ELTYPE) 1 << BARR_BITNUM(N))
#endif
