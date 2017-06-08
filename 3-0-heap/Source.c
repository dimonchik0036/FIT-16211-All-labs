//LABA 3-0-heap
//by Dimonchik0036

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>

//Меняет ячейки в массиве
void swap(int *arr, int i, int j);

//Начинка сортировки
void shiftDown(int *arr, int i, int j);

//Пирамидальная сортировка
void heapSort(int *arr, int arrSize);

int main()
{
	int n; //Количество чисел в массиве

	scanf("%d", &n);

	//Массив из n чисел
	int *numberArray;
	numberArray = (int*)malloc(n * sizeof(*numberArray));

	if (numberArray == NULL)
	{
		printf("not memory");

		return 0;
	}

	int i; //Переменная для цикла

	for (i = 0; i < n; i++)
	{
		scanf("%d", &numberArray[i]); //Ввод данных в массив
	}

	//Сортировка
	heapSort(numberArray, n);

	//Вывод массива
	for (i = 0; i < n; i++)
	{
		printf("%d ", numberArray[i]);
	}

	return 0;
}

void swap(int *arr, int i, int j)
{
	int keys = arr[i];
	arr[i] = arr[j];
	arr[j] = keys;
}

void shiftDown(int *arr, int i, int j)
{
	int left = 2 * i + 1; 
	int right = left + 1; 
	int maximum = left;

	while (maximum < j)
	{
		if (right < j)
		{
			if (arr[left] < arr[right])
			{
				maximum = right;
			}
		}

		if (arr[i] < arr[maximum])
		{
			swap(arr, i, maximum);
		}
		else
		{
			break;
		}

		i = maximum;

		left = 2 * i + 1;
		right = left + 1;
		maximum = left;
	}
}

void heapSort(int *arr, int arrSize)
{
	int i;
	int len = arrSize;
	
	for (i = len / 2 - 1; i >= 0; i--)
	{
		shiftDown(arr, i, len);
	}
	
	for (i = len - 1; i > 0; i--)
	{
		swap(arr, 0, i);
		shiftDown(arr, 0, i);
	}
}

