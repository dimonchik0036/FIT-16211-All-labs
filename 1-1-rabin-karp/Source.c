// LABA 1-1-rabin-karp
// by Dimonchik0036

#define _CRT_SECURE_NO_WARNINGS

#define SHABLON_SIZE 20
#define TEXT_SIZE 20
#define CONST 3

#include <stdio.h>
#include <locale.h>
#include <math.h>

void search(unsigned char *arr, unsigned char *pattern, int index, int patternSize);

int main()
{
	setlocale(LC_ALL, "Russian");

	unsigned char pattern[SHABLON_SIZE];
	unsigned char text[TEXT_SIZE];

	int patternHashSummary = 0;
	int nextHashSummary = 0;

	int patternSize = 0;
	unsigned int c;

	while ((c = getchar()) != '\n')
		pattern[patternSize++] = c;

	fread(text, sizeof(*text), patternSize, stdin);

	for (int i = 0; i < patternSize; i++)
		patternHashSummary += (pattern[i] % CONST)*(int)pow(CONST, i);

	for (int i = 0; i < patternSize; i++)
		nextHashSummary += (text[i] % CONST)*(int)pow(CONST, i);

	printf("%d ", patternHashSummary);
	
	if (patternHashSummary == nextHashSummary)
		search(text, pattern, patternSize - 1, patternSize);

	int index = patternSize;

	int iPow3 = (int)pow(CONST, patternSize - 1);

	while ((c = getchar()) != EOF)
	{
		text[index % TEXT_SIZE] = c;

		nextHashSummary -= text[(index - patternSize) % TEXT_SIZE] % CONST;
		nextHashSummary /= CONST;
		nextHashSummary += (c % CONST)*iPow3;

		if (nextHashSummary == patternHashSummary)
			search(text, pattern, index , patternSize);

		index++;
	}

	return 0;
}

void search(unsigned char *arr, unsigned char *pattern, int index, int patternSize)
{
	int count = patternSize - 1;

	while ((count >= 0) && ((arr[(index - count) % TEXT_SIZE]) == (pattern[patternSize - 1 - count])))
	{
		printf("%d ", index - count + 1);
		count--;
	}

	if (count != -1)
	{
		printf("%d ", index - count + 1);
	}
}