//	 Labs: 5-huffman
// Author: Dimonchik0036

#ifndef HUFFMAN_H_
#define HUFFMAN_H_
#define FILE_NAME_RD "in.txt"
#define FILE_NAME_WR "out.txt"
#define MAX_CODE_BITS 32
#define ALPH_SIZE 256
#define WIN_NEW_LINE 2
#define BUFFER_SIZE 1024

#define COMPRES_OPT  'c'
#define EXPAN_OPT  'd'
#define COMPRES 1
#define DECOMPRES 2
#define FILE_EMPTY 3
#define BAD_OPT -1
#define BAD_FILE -2

#include <stdio.h>
#include "bitarray.h"
#define RUN_ASSERT(X, ERR_STRING, RETURN_VAL)\
    if(!(X))\
    {\
        fprintf(stderr,ERR_STRING);\
        exit((RETURN_VAL));\
    }

/* Htree */
typedef struct Node
{
	unsigned char ch;
	struct Node *left;
	struct Node *right;
} Node;

/* Hcode */
typedef struct Symbol
{
	unsigned char code[MAX_CODE_BITS];
	size_t lengthCode;
} Symbol;

void* malloc_wr(size_t countByte);

size_t* get_prob_tree(Node **tree, FILE *fin); // Build array frequencies, Htree without code

void tree_remove(Node *tree); // Remove Htree

void write_file(FILE *fin, FILE *fout, Symbol *alph, Node *tree); // Write compressed file

void fill_tree_code(Node *tree, Symbol *alph, BARR_ELTYPE tmpCode[MAX_CODE_BITS], size_t deep); // Htree Hcode

unsigned int write_tree(FILE *fout, Node *tree, BARR_ELTYPE *buf); // Write Htree to the beginning

void set_file_bit(BARR_ELTYPE *buf, _Bool set, size_t count, FILE *fin); // Set bit in the file

_Bool get_file_bit(BARR_ELTYPE *buf, size_t count, FILE *fin); // Get bit in the file

BARR_ELTYPE get_file_byte(BARR_ELTYPE *buf, size_t count, FILE *fin); // Get byte in the file

void decompres(FILE *fin, FILE *fout, unsigned char sizeLostByte); // Decompress compressed file

void compres(FILE *fin, FILE *fout); // Compres raw file

void create_tree_node(BARR_ELTYPE *buf, Node *tree, size_t *fileBitPos, FILE *fin); // Create Tree node from compres for decompres

void RLE(FILE *fout, size_t smbFrequency, unsigned char RLEsmb); // Code RLE

void UNRLE(FILE *fin, FILE *fout); // Decode RLE

unsigned char is_RLE(size_t *alphVal); // RLE check
#endif
