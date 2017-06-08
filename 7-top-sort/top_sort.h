//	 Labs: 7-top-sort
// Author: Dimonchik0036

#ifndef TOP_SORT_H_
#define TOP_SORT_H_

#define ERROR_NUMB_VERT "bad number of vertices\n"
#define ERROR_VERT "bad vertex\n"
#define ERROR_NUMB_EDG "bad number of edges\n"
#define ERROR_NUMB_LINE "bad number of lines\n"
#define ERROR_CYCLE "impossible to sort\n"

#define INPUT_FILE "in.txt"
#define OUTPUT_FILE "out.txt"

#define ERROR(stream, str) { fprintf(stream, str);\
									fclose(fin);\
									fclose(fout);\
									exit(0); }


#include <stdio.h>
#include <stdlib.h>


struct Node
{
	struct List *link;
	struct Node *next;
};

struct List
{
	int index;
	char color;
	struct Node *first;
};

struct List* list_create(int N);

void list_add(struct List *list, int indexFrom, int indexTo);

void remove_list(struct List *list, int N);

int top_sort(struct List *list, int N, FILE *fout);

void read_first_values(FILE *fin, FILE *fout, int *N, int *M);

void get_values(FILE *fin, FILE *fout, struct List *list, int N, int M);
#endif
