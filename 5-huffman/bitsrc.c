//	 Labs: 5-huffman
// Author: Dimonchik0036

#include "huffman.h"

/*
 * For all func
 * Write/read occurs only when the full bit is typed(count == 7)
 */
void set_file_bit(BARR_ELTYPE *buf, _Bool set, size_t count, FILE *fout)
{
	count %= BARR_ELBITS;
	count = BARR_ELBITS - 1 - count;

	if (set)
	BARR_SET(buf, count);
	else
	BARR_CLEAR(buf, count);
	if (!count) // Write only if input count = 7 => filling  last bit
		fwrite(buf, BARR_ELBITS / CHAR_BIT, 1, fout);
}

_Bool get_file_bit(BARR_ELTYPE *buf, size_t count, FILE *fin)
{
	count %= BARR_ELBITS;
	count = BARR_ELBITS - 1 - count;

	_Bool retBit = BARR_TEST(buf, count);

	if (!count) fread(buf, BARR_ELBITS / CHAR_BIT, 1, fin);

	return retBit;
}

BARR_ELTYPE get_file_byte(BARR_ELTYPE *buf, size_t count, FILE *fin)
{
	count %= BARR_ELBITS;

	BARR_ELTYPE byteChar = 0;

	for (int numBit = BARR_ELBITS - 1; numBit >= 0; numBit--)
	{
		if (get_file_bit(buf, count, fin))
		BARR_SET(&byteChar, numBit);
		else
		BARR_CLEAR(&byteChar, numBit);

		count++;
	}
	return byteChar;
}
