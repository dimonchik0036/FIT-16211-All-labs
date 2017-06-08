//	 Labs: 8-1-prim-kruskal
// Author: Dimonchik0036

#define ERROR_NUMB_VERT "bad number of vertices\n"
#define ERROR_NUMB_EDGE "bad number of edges\n"
#define ERROR_VERT "bad vertex\n"
#define ERROR_LENG "bad length\n"
#define ERROR_NUMB_LINE "bad number of lines\n"
#define ERROR_TREE "no spanning tree\n"

#define ERROR_FILE "File error!\n"
#define ERROR_MEM "Out of memory!\n"

#define MIN_NUMB_VERT 0
#define MAX_NUMB_VERT 5000
#define MIN_NUMB_EDGE 0
#define INF -1

#define IN_FILE "in.txt"
#define OUT_FILE "out.txt"


#include <stdio.h>


struct Vert
{
	unsigned int lengthPath;
	unsigned int indexFrom;
};


int read_first_values(FILE *fIn, int *N, int *M);

int** alloc_matrix(int size);

int get_edges(int **matrix, int size, const int N, FILE *fIn);

int search_tree(int **matrix, int N, FILE *fOut);

void free_matrix(int **matrix, int N);
