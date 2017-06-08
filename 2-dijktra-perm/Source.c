#define _CRT_SECURE_NO_WARNINGS
#define SIZE_ARRAY 11
#include <stdlib.h>
#include <stdio.h>

//Смена ячеек в массиве
void swap(int *arr, int i, int j);

//Переход к следующей перестановке
int nextPermutation(int *arr, int arrSize);

//Вывод перестановки
void printArray(int *arr, int arrSize);

int main()
{
	//Массив, содержащий все цифры перестановки
	int numberArray[SIZE_ARRAY];
	int numberSize = 0;
	int i; //Переменная для циклов
	char n;

	while ((n = getchar()) != '\n')
	{
		if ((n < '0') || (n > '9'))
		{
			printf("bad input");

			return 0;
		}
		numberArray[numberSize] = n - '0';
		numberSize++;
	}
	
	//Проверка на одинаковые цифры
	int equality = 1; //Счётчик равных чисел

	for (i = 0; i < numberSize - 1; i++)
		if (numberArray[i] == numberArray[i + 1])
			equality++;

	if (equality == numberSize)
	{
		if (numberSize != 1)
		{
			printf("bad input");

			return 0;
		}
	}

	//Желаемое количество перестановок
	int repeat;
	scanf("%d", &repeat);

	//Поиск и вывод перестановок
	while ((nextPermutation(numberArray, numberSize))&&(repeat > 0))
	{
		printArray(numberArray, numberSize);
		repeat--;
	}

	return 0;
}

void swap(int *arr, int i, int j)
{
	int s = arr[i]; 
	arr[i] = arr[j];
	arr[j] = s;
}

int nextPermutation(int *arr, int arrSize)
{
	//Предпоследняя позиция
	int j = arrSize - 2;

	while (j != -1 && arr[j] >= arr[j + 1]) 
		j--;

	//Проверка на существование следующей перестановки
	if (j == -1)
		return 0; 
	
	//Последняя позиция
	int k = arrSize - 1;

	while (arr[j] >= arr[k]) 
		k--;

	swap(arr, j, k);

	//Сортировка оставшейся части
	int l = j + 1, r = arrSize - 1; 

	while (l<r)
		swap(arr, l++, r--);

	return 1;
}

void printArray(int *arr, int arrSize) 
{ 
	for (int i = 0; i < arrSize; i++)
		printf("%d", arr[i]);

	printf("\n");
}