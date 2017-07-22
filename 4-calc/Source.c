// LABA 4 - calc
// by Dimonchik0036

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Обозначает границу стека 
#define END 0

// Операции, доступные на стеке 
#define ADD '+'
#define SUB '-'
#define MUL '*'
#define DIV '/'

// Операция или число(для поля isOperation) 
#define OPERATION true
#define NUMBER false

#define OPEN_BRACKET '('
#define CLOSE_BRACKET ')'

#define INPUT_SIZE 1024
#define MAX_STACK_SIZE 1024
#define MAX_OPERATION_STACK_SIZE 1024

// Сообщения об ошибке
#define AHTUNG {printf("syntax error\n"); return NULL;}
#define ALARM {printf("division by zero\n"); return;}

// Последние считанные лексемы 
enum last_item 
{
	LAST_START_FILE,
	LAST_NUMBER,
	LAST_OPERATION,
	LAST_OPEN_BRACKET,
	LAST_CLOSE_BRACKET
};

// Элемент стека
struct Item 
{
	// Значение данного элемента стека
	int value;

	// Если true, то в поле value хранится значение соответсвующее операции, иначе там число
	bool isOperation;
};

// Проверка на оператор
bool isOperator(char c);

// Проверка на число
bool isNumber(char c);

// Возвращает приоритет
int getOperationPriority(char operation);

// Считывает со входного потока, формирует стек и возвращает его. Если при формировании происходит ошибка, кричит AHTUNG и завершает работу.
struct Item* infixToPostfix() 
{
	struct Item *stack = malloc(MAX_STACK_SIZE * sizeof(struct Item));

	// Стек операций
	char operatorsStack[MAX_OPERATION_STACK_SIZE];

	// Считываем входную строку.
	char input[INPUT_SIZE];
	gets(input);

	size_t stackPos = 0;
	size_t operatorsStackLen = 0;

	// Тип последнего обработаного элемента (определены как #define LAST_*)
	enum last_item lastItemType = LAST_START_FILE;

	size_t pos = 0;

	while (input[pos] != '\0') 
	{
		if (isNumber(input[pos])) // Считывание числа
		{ 
			if (lastItemType == LAST_NUMBER || lastItemType == LAST_CLOSE_BRACKET) // Нет оператором м-ду числами: x y .. или .. ) x ..
				AHTUNG

			int number = 0;

			while (isNumber(input[pos])) 
			{
				number = number * 10 + (input[pos] - '0');
				pos++;
			}
			pos--;

			struct Item item = { number, NUMBER };
			stack[stackPos++] = item;

			lastItemType = LAST_NUMBER;
		}
		else if (input[pos] == OPEN_BRACKET) // Начало выражения в скобках
		{ 
			if (lastItemType == LAST_NUMBER) // Нет оператора после числа: .. x ( ..
				AHTUNG
			
			operatorsStack[operatorsStackLen++] = input[pos];
			lastItemType = LAST_OPEN_BRACKET;
		}
		else if (isOperator(input[pos])) // Оператор +, -, *, /
		{ 
			if (lastItemType == LAST_START_FILE || lastItemType == LAST_OPEN_BRACKET) 
			{
				if (input[pos] == ADD || input[pos] == SUB) // Корректная обработка отрицательных чисел: - x .. и .. (- x ..
				{ 
					struct Item item = { 0, NUMBER };
					stack[stackPos++] = item;
				}
				else // Нет левого аргумента: * x .. и .. ( * x ..
					AHTUNG
			}

			if (lastItemType == LAST_OPERATION) // Два оператора подряд: .. + * ..
				AHTUNG

			// Проверяем приоритеты операций
			if (getOperationPriority(input[pos]) <= getOperationPriority(operatorsStack[operatorsStackLen - 1])) 
			{
				struct Item item = { operatorsStack[operatorsStackLen - 1], OPERATION };
				stack[stackPos++] = item;
				operatorsStackLen--;
			}

			operatorsStack[operatorsStackLen++] = input[pos];
			lastItemType = LAST_OPERATION;
		}
		else if (input[pos] == CLOSE_BRACKET) // Конец выражения в скобках
		{ 
			if (lastItemType == LAST_OPEN_BRACKET) // Пустая скобка: .. ( ) .. 
				AHTUNG
			if (lastItemType == LAST_OPERATION) // Нет правого аргумента: .. ( x + ) ..
				AHTUNG

			bool found = false;

			while (operatorsStackLen > 0) 
			{
				if (operatorsStack[operatorsStackLen - 1] == OPEN_BRACKET) 
				{
					found = true;
					break;
				}

				struct Item item = { operatorsStack[operatorsStackLen - 1], OPERATION };
				stack[stackPos++] = item;
				operatorsStackLen--;
			}
			if (!found) // До конца стека операций не было найдено открывающихся скобок, значит это ошибка
				AHTUNG

			operatorsStackLen--;
			lastItemType = LAST_CLOSE_BRACKET;
		}
		else if (input[pos] == ' ') // Пропускаем пробелы
		{ 

		}
		else // Неизвестный символ
			AHTUNG
		
		pos++;
	}

	if (lastItemType == LAST_OPERATION) // Нет правого аргумента: "... 1 * "
		AHTUNG

	// В конце считывания закидываем все операции, оставшиеся на стеке операций, в основной стек
	while (operatorsStackLen > 0) 
	{
		if (operatorsStack[operatorsStackLen - 1] == OPEN_BRACKET)
			AHTUNG

		struct Item item = { operatorsStack[operatorsStackLen - 1], OPERATION };
		stack[stackPos++] = item;
		operatorsStackLen--;
	}

	// Помечаем конец стека
	struct Item item = { END, OPERATION };
	stack[stackPos] = item;

	return stack;
}

// Определяет размер стека
size_t stackSize(struct Item *stack);

// Вычисляет результат выражения
void postfixCalc(struct Item *stack);

int main() 
{
	struct Item *stack = infixToPostfix();

	if ((stack != NULL) && !(stack[0].isOperation && stack[0].value == 0)) 
		postfixCalc(stack);

	if ((stack != NULL) && (stack[0].isOperation && stack[0].value == 0))
		printf("syntax error\n");

	free(stack);

	return 0;
}

bool isOperator(char c)
{
	return c == ADD || c == SUB || c == MUL || c == DIV;
}

bool isNumber(char c)
{
	return c - '0' >= 0 && c - '0' <= 9;
}

int getOperationPriority(char operation)
{
	switch (operation)
	{
	case MUL:
	case DIV:
		return 1;
	case ADD:
	case SUB:
		return 0;
	}

	return -1;
}

size_t stackSize(struct Item *stack)
{
	size_t i = 0;
	while (!stack[i].isOperation || stack[i].value) {
		i++;
	}

	return i;
}

void postfixCalc(struct Item *stack)
{
	size_t size = stackSize(stack);

	struct Item calculation[22];
	size_t calculationPos = 0;
	int a, b, result;

	for (size_t i = 0; i < size; i++)
	{
		if (!stack[i].isOperation)
		{
			calculation[calculationPos++].value = stack[i].value;
		}
		else
		{
			b = calculation[--calculationPos].value;
			a = calculation[--calculationPos].value;

			switch (stack[i].value)
			{
			case ADD:
				calculation[calculationPos++].value = a + b;
				break;
			case SUB:
				calculation[calculationPos++].value = a - b;
				break;
			case MUL:
				calculation[calculationPos++].value = a * b;
				break;
			case DIV:
				if (b == 0)
					ALARM
					calculation[calculationPos++].value = a / b;
				break;
			}
		}
	}

	result = calculation[0].value;

	printf("%d\n", result);
}