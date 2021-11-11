#include <stdio.h>
#include <stdlib.h>

// Структура - набор полей разных типов
struct Student{
    int x; // поля внутри структуры
    int group;
    int y;
    char name[100];
    char *p;
}; // здесь, мы как бы создали новый тип под названием "struct Student"


// можно делать вложенные структуры
struct Point{
	int x;
	int y;
};
struct Rect{
	struct Point lt;
	struct Point rb;
};
// и объявим тут функцию, которая будет работать с аргументами типа struct Rect, опишем ее ниже
void change_rect(struct Rect *); // ";" - означает, что это объявление ф-ции (declaration), а описана (definition) она будет в другом месте


// функция, в качества аргумента принимающая структуру,
// и обращающаяся к ее полям
void print_struct(struct Student AAA){

    printf("%d %d %d\n", AAA.x, AAA.group, AAA.y);
	// если обращаемся к полям структуры используя ее имя, то ставим "."
	
    return;
}

// функция, в качества аргумента принимающая указатель на структуру,
// и изменяющая ее поля
// т.к., имея указатель (зная адрес), можем изменять поля внутри структуры
void null_struct(struct Student * XXX){
    
    XXX->x = 0;
    XXX->group = 0;
    XXX->y = 0;
	// если обращаемся к полям структуры используя указатель на нее, то ставим "->"
    
    return;
}

int main()
{
    struct Student new_student; // выделить память, локально в ф-ции main, под переменную типа "struct Student"
	// т.е. под саму структуру new_student
	
	// если обращаемся к полям структуры используя ее имя, то ставим "."
    new_student.x = 1;
    new_student.group = 45;
    new_student.y = 2;
	
	struct Student * p; // выделить память под указатель на структуру
	p = &new_student;	// создали указатель
	
	// если обращаемся к полям структуры используя указатель на нее, то ставим "->"
    p->x = 3;
    p->group = 33;
    p->y = 3;
	
	// т.е. new_student.x = 1; <=> (&new_student)->x = 1;


	// Позовем функции
	// передаем копию структуры в качестве аргумента
    print_struct(new_student);

	// передаем указатель на структуру в качестве аргумента
	null_struct(p); // эквивалентно null_struct(&new_student);

	

	// Создадим одну структуру типа struct Rect
	struct Rect rect_1; // выделили память как для локальной переменной ф-ции main()
	
	// обратимся к координате "x" ее верхнего левого угла 
	// (который описывается структурой с именем lt, имеющей тип struct Point)
	rect_1.lt.x = 0;
	// а координату "y" считаем из командной строки, а потом распечатаем
	scanf("%d", &rect_1.lt.y);
	printf("%d", rect_1.lt.y);
	
	// Создадим еще одну структуру типа struct Rect
	struct Rect * q_rect_2 = (struct Rect *)malloc(sizeof(struct Rect));
	// выделили память динамически
	
	// обратимся к ее полям
	q_rect_2->lt.x = 7;
	// и передадим ее в функцию, которая ее обнулит
	change_rect(q_rect_2);
	
	
	// Создадим (динамически) массив структур типа struct Point
	int n = 10;
	struct Point * q_point = (struct Point *)malloc(sizeof(struct Point) * n);
	// и обратимся к полям первой
	q_point[0].x = 1;
	q_point[0].y = 2;
		
    return 0;
}

void change_rect(struct Rect * q){
	q->lt.x = 0;
	q->lt.y = 0;
	q->rb.x = 0;
	q->rb.y = 0;
	return;
}
