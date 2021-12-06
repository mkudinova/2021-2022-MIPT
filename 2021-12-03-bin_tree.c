#include<stdio.h>
#include<stdlib.h>

struct Elem {
	int val; // значение, которое хранится в элементе ((!) может быть указателем на строку, например)
	struct Elem * lv, * pr; // указатели на левого и правого потомков
};
struct Elem * root; // глобальная переменная, хранящая указатель на начало дерева

void print_tree_dfs(struct Elem * p){ // рекурсивный обход дерева в глубину
	if (p == NULL){
		return;
	}
	
	print_tree_dfs(p->lv); // распечатать левое поддерево все целиком
	printf("%d ", p->val); // распечатать значение текущего элемента
	print_tree_dfs(p->pr); // распечатать правое поддерево все целиком
	
	return;
}
void print_tree_bfs(struct Elem * p); // обход дерева в ширину, см. ниже

void add_elem(int x){
	struct Elem * p = (struct Elem *)malloc(sizeof(struct Elem)); // выделить под элемент память
	p->val = x; // заполнить его поля
	p->lv = NULL;
	p->pr = NULL;
	
	// ищем для него подходящее место в дереве
	// если дерево пусто
	if (root == NULL){
		root = p;
		return;
	}
	
	// если дерево не пусто, ищем для него родительский элемент (вставляем только как лист)
	struct Elem * q = root;
	while(1){
		if (x < q->val){ // если x меньше, чем значение текущего элемента, то вставляем в левое поддерево
			if (q->lv != NULL){
				q = q->lv; // переходим в левого потомка текущего элемента
			}
			else{
				q->lv = p; // вставляем новый элемент, если левого потомка не было
				break;
			}
		}
		else{ // если x больше или равно, то - в правое поддерево
			if (q->pr != NULL){
				q = q->pr; // переход в правого потомка
			}
			else{
				q->pr = p; // вставка в качестве правого потомка
				break;
			}
		}
	}

	return;
}

struct Elem * find_elem(int x){ // проход по дереву в этом случае аналогичен add_elem
	if (root == NULL){
		printf("Empty tree");
		return NULL;
	}
	
	struct Elem * p = root; // p - будет указателем на текущий элемент на каждой итерации
	while(1){
		if(x == p->val) // если значение совпало - мы нашли нужный элемент
			return p;
		if(x < p->val){ // если x меньше, идем искать в левом поддереве
			if(p->lv != NULL)
				p = p->lv; // если левое поддерево есть - переходим левого потомка
			else
				return NULL; // если левого поддерева нет - значит не нашли нужный элемент
		}
		if(x > p->val){ // если x больше, идем искать в правом поддереве
			if(p->pr != NULL)
				p = p->pr;
			else
				return NULL;
		}
	}
	
	return NULL;
}

// пример
int main(){
	root = NULL;
	add_elem(7); // вставим в корневой элемент
	add_elem(5); // пойдет как левый потомок 7
	add_elem(8); // пойдет как правый потомок 7
	add_elem(6); // пойдет как правый потомок 5
	add_elem(3); // пойдет как левый потомок 5
	add_elem(1); // пойдет как левый потомок 3
	add_elem(4); // пойдет как правый потомок 3
	add_elem(9); // пойдет как правый потомок 8
	printf("Print as Depth-first search (DFS):\n"); // see https://en.wikipedia.org/wiki/Depth-first_search
	print_tree_dfs(root); // распечатать все дерево целиком
	printf("\n");
	printf("Print subtree as (DFS):\n");
	print_tree_dfs(find_elem(3)); // распечатать поддерево с корнем в элементе, имеющим значение = 3
	printf("\n");
	printf("Print as breadth-first search (BFS):"); // see https://en.wikipedia.org/wiki/Breadth-first_search
	print_tree_bfs(root);
	// дерево в таком случае выглядит так:
	// .......7.......
	// ...5.......8...
	// .3...6.......9.
	// 1.4............
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// печать через обход дерева в ширину - полезна для проверки функций вставки в(удаления из) дерево
// для его реализации понадобится очередь для хранения еще не обработанных вершин,
// которую можно реализовывать, например, через список
// для этого понадобятся функции 
void add_to_queue(struct Elem * p); // добавить элемент в очередь (напр., добавить в конец списка)
struct Elem * take_from_queue(); // вынуть элемент из очереди (напр., удалить из начала списка)
int queue_not_empty(); // проверить, что очередь не пуста (напр., указатель на голову списка != NULL)
// примеры этих функций для списков есть в https://github.com/mkudinova/2021-2022-MIPT/blob/main/2021-12-03-list.c или https://github.com/mkudinova/C/blob/main/Nov/20 

void print_tree_bfs(struct Elem * p){
	struct Elem * q; // временная переменная, на каждой итерации цикла будет хранить адрес обрабатываемого элемента

	add_to_queue(p); // создадим очередь
	while(queue_not_empty()){ // пока в ней есть элементы
		q = take_from_queue(); // вынем элемент из очереди
		printf("%d ", q->val); // обработаем его, например, распечатаем его значение
		add_to_queue(q->lv); // добавим в очередь его потомков
		add_to_queue(q->pr);
		//(или перед добавлением в очередь, или внутри add_to_queue(), надо проверить, что такой потомок вообще есть)
	}
	return;
}

// а здесь мы сделаем эту очередь через массив (для небольших деревьев)
#define max_N_elem 100
struct Elem * queue[max_N_elem]; // выделим массив, который хранит адреса вершин
int i_beg = 0, i_end = 0, i_layer = 0; // i_beg - начало очереди, i_end - конец очереди,
// i_layer - первая вершина на этом уровне (чтобы все распечаталось не одной строкой, а по уровням дерева)
void add_to_queue(struct Elem * p){ // добавить указатель на вершину дерева в массив
	if(p == NULL) // ничего не делать, если на самом деле вершины нет
		return;
	queue[i_end] = p; // положить в конец
	i_end++; // передвинуть индекс, который указывает на конец очереди (последняя заполненная ячейка массива + 1)
	return;
}
struct Elem * take_from_queue(){
	if(i_beg == i_layer){ // это только, чтобы разбить по уровням дерева
		printf("\n"); // прежде чем вынуть последний элемент уровня, поставим "\n", отметим конец следующего уровня
		i_layer = i_end;
	}
	struct Elem * q = queue[i_beg]; // запомнить значение, чтобы потом сделать return
	i_beg++; // увеличить индекс начала очереди (i_beg = индекс первого из необработанных элементов) 
	return q;
}
int queue_not_empty(){
	if(i_beg != i_end)
		return 1;
	else
		return 0;
}