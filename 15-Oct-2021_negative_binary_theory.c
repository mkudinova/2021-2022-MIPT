/* Представление отрицательных чисел на примере типа char.
Переменная типа char - это 1 байт, т.е. 8 бит.
Например, 0 будет записан, как 0000 0000.

Если возьмем двоичное число 1111 1111 и прибавим к нему еще 1 (т.е. 0000 0001 в двоичном виде), то получится 1 0000 0000, которое в тип char уже не влезет, произойдет переполнение и, в итоге, в ячейке памяти окажется 0000 0000, то есть 0.

А если при прибавлении 1 к 1111 1111 получается 0, то можно считать 1111 1111 представлением числа -1.

"По определению, −1 — это такое число, при прибавлении к которому единицы (нейтрального элемента относительно операции умножения) получается ноль (нейтральный элемент относительно операции сложения)." (https://ru.wikipedia.org/wiki/%E2%88%921_(%D1%87%D0%B8%D1%81%D0%BB%D0%BE))

Этот принцип и взят за основу представления отрицательных чисел в современных компьютерах. Такое представление еще называется "дополнительным кодом" (https://ru.wikipedia.org/wiki/%D0%94%D0%BE%D0%BF%D0%BE%D0%BB%D0%BD%D0%B8%D1%82%D0%B5%D0%BB%D1%8C%D0%BD%D1%8B%D0%B9_%D0%BA%D0%BE%D0%B4).

Таким образом, получается:

Десятичная система		Десятичная система		Двоичная система		Шестнадцатеричная система
(char, со знаком)		(unsigned char)
0						0						0000 0000				00
1						1						0000 0001				01
2						2						0000 0010				02
3						3						0000 0011				03
4						4						0000 0100				04
5						5						0000 0101				05
6						6						0000 0110				06
7						7						0000 0111				07
8						8						0000 1000				08
9						9						0000 1001				09
10						10						0000 1010				0a
11						11						0000 1011				0b
12						12						0000 1100				0c
13						13						0000 1101				0d
14						14						0000 1110				0e
15						15						0000 1111				0f
16						16						0001 0000				10
17						17						0001 0001				11
...						...						...						...
125						125						0111 1101				7d
126						126						0111 1110				7e
127						127						0111 1111				7f
-128						128						1000 0000				80
-127						129						1000 0001				81
-126						130						1000 0010				82
...						...						...						...
-5						251						1111 1011				fb
-4						252						1111 1100				fc
-3						253						1111 1101				fd
-2						254						1111 1110				fe
-1						255						1111 1111				ff

Поэтому выходит, что
unsigned char in [0, 255] (т.е., [0; 2^8-1])
char in [-128, 127] (т.е., [-2^7; 2^7-1])

Для других типов данных конкретное представление будет отличаться, но логика остается той же.

И если первый (старший) разряд в двоичной записи числа x = 0, то сам число x >= 0
а если = 1, то число x < 0

Из-за этого бинарные операции сдвига влево для типов char и unsigned char работают по разному (для чисел, чья бинарная запись начинается с "1").
Сдвиг для знаковых типов не меняет знак числа
*/


#include <stdio.h>

int main()
{
	// Пусть было:
	char c = -1;
	unsigned char d = 255;
	// оба имеют двоичное представление 1111 1111

	c = c >> 1;
	d = d >> 1;

	// в результате будет
	printf("%d %d", c, d);

	c = -1; // было (как бы отрицательное) 1111 1111 -> 1111 1111, сдвинули на 1 влево и на освободившееся место опять поставили 1 (т.к., число должно остаться отрицательным)
	d = 127; // было (как бы положительное) 1111 1111 -> 0111 1111, сдвинули на 1 влево и на освободившееся место поставили 0

    return 0;
}

