#include "graph.h"
#include <iostream>
#include <string>
#include <queue>
using namespace std;

graph::graph(bool directed, int maxSize) { //Конструктор класса graph
	size = 0;
	this->maxsize = maxSize;
	this->directed = directed;
	//vs = (list **)malloc((sizeof(list *))*maxSize); - не работает... Почему?
	list **vs;
	vs = new list*[maxSize];
	for (int i = 0; i < maxSize; i++)vs[i] = NULL;
	this->vs = vs;
}
void graph::addvertex(vertex* v) { //Метод класса graph для добавления вершины
	/*cout << &v << endl;                         - РАЗОБРАТЬСЯ, почему адреса не совпадают???
	cout<< this->findVertex(v.name) << endl;*/
	if (findVertex(v->name) != NULL) return; //Проверка на наличие вершины в графе
	size++;
	if (size == maxsize) resize();
	int hash = hashF(v->name);
	vs[hash] = addNode(v, vs[hash]);
}
void graph::addEdge(vertex* v1, vertex* v2) { //Метод класса graph для добавления ребра
	if (isEdge(v1, v2))return;
	if ((findVertex(v1->name) == NULL) || (findVertex(v2->name) == NULL)) return;
	string key = v1->name;
	int hash = hashF(key);
	list *cur;
	cur = findNode(vs[hash], key);
	cur->nroot = addToRoot(v2, cur->nroot);
	if (!directed) {
		key = v2->name;
		hash = hashF(key);
		cur = findNode(vs[hash], key);
		cur->nroot = addToRoot(v1, cur->nroot);
	}
}
void graph::removeEdge(vertex* v1, vertex* v2) { //Метод класса graph для удаления ребра
	if ((findVertex(v1->name) == NULL) || (findVertex(v2->name) == NULL)) return;
	string key = v1->name;
	int hash = hashF(key);
	list *cur;
	cur = findNode(vs[hash], key);
	removeNeighbour(cur, v2, cur->nroot);
	if (!directed) {
		key = v2->name;
		hash = hashF(key);
		cur = findNode(vs[hash], key);
		removeNeighbour(cur, v1, cur->nroot);
	}
}
bool graph::isEdge(vertex* v1, vertex* v2) { //Метод класса graph для проверки наличия ребра
	if ((findVertex(v1->name) == NULL) || (findVertex(v2->name) == NULL)) return false;
	string key = v1->name;
	int hash = hashF(key);
	list *curl;
	curl = findNode(vs[hash], key);
	ns* cur = curl->nroot;
	while (cur != NULL) {
		if (cur->v->name == v2->name) return true;
		cur = cur->next;
	}
	return false;
}
void graph::removeVertex(vertex* v) { //Метод класса graph для УДАЛЕНИЯ ВЕРШИНЫ
	if (size == 0)return;
	string key = v->name;
	int hash = hashF(key);
	if (findNode(vs[hash], key) == NULL)return;
	for (int i = 0; i < maxsize; i++) {
		if (vs[i] != NULL)removeEdge(vs[i]->v, v);
	}
	removeNode(this, hash, vs[hash], key);
	size--;
}
int graph::hashF(string key) { //Метод класса graph (Хэш-Функция)
	int len = key.size();
	int hash = 0;
	for (int i = 0; i < len; i++) {
		hash += ((int)key[i]) * ((int)key[i]);
	}
	hash %= maxsize;
	return hash;
}
void graph::resize() { //Метод класса graph для РАСШИРЕНИЯ ХЭШ-ТАБЛИЦЫ
	maxsize *= 2;
	//list** vs2 = (list **)realloc(vs, sizeof(list *)*maxsize);
	list**vs2;
	vs2 = new list*[maxsize];
	list* cur1;
	list* cur2;
	int hash = 0;
	for (int i = 0; i < maxsize; i++) {
		vs2[i] = NULL;
	}
	for (int i = 0; i < maxsize / 2; i++) {
		cur2 = vs[i];
		while (cur2 != NULL) {
			hash = hashF(cur2->key);
			vs2[hash] = addNode(cur2->v, vs2[hash]);
			cur1 = cur2->next;
			removeNode(this, i, cur2, cur2->key);
			cur2 = cur1;
		}
	}
	delete vs;
	vs = vs2;
}
vertex* graph::findVertex(string key) { //Метод класса graph, позволяющий по ключу (key) найти вершину vertex
	vertex* vertex;
	list* list;
	int hash = hashF(key);
	list = findNode(vs[hash], key);
	if (list == NULL)return NULL;
	vertex = list->v;
	return vertex;
}
void graph::printgraph() { //Метод класса graph для ВЫВОДА ГРАФА
	cout << endl << "Вывод графа: " << endl << endl;
	list *cur;
	for (int i = 0; i < maxsize; i++) {
		cur = vs[i];
		while (cur != NULL) {
			printList(cur);
			cur = cur->next;
		}
	}
}
void graph::aroundgraph() { //Метод класса graph для ОБХОДА ГРАФА и ЗАНУЛЕНИЯ ПОЛЯ LEVEL (v.level=0)
	list *cur;
	ns* curns;
	vertex* vert;
	for (int i = 0; i < maxsize; i++) {
		cur = vs[i];
		while (cur != NULL) {
			cur->v->level = 0;
			curns = vs[i]->nroot;
			while (curns != NULL) {
				vert = curns->v;
				vert->level = 0;
				curns = curns->next;
			}
			cur = cur->next;
		}
	}
}
int graph::shortestPath(vertex* v1, vertex* v2) { //Метод класса graph для ПОИСКА КРАТЧАЙШЕГО ПУТИ и ВЫВОДА ОДНОГО ИЗ ПУТЕЙ НА ЭКРАН
	if ((findVertex(v1->name) == NULL) || (findVertex(v2->name) == NULL)) return -1;
	queue <vertex*> queue;
	int count = 0, current = 0, hash = 0;
	string key;
	list *curl;
	ns *curns;
	vertex *v;
	aroundgraph();
	v = v1; queue.push(v);
	while (v->name != v2->name) {
		key = v->name;
		queue.pop();
		hash = hashF(key);
		curl = findNode(vs[hash], key);
		curns = curl->nroot;
		while (curns != NULL) {
			if ((curns->v->level == 0) && (curns->v->name != v1->name)) {
				curns->v->level = v->level + 1;
				if (current < curns->v->level)current++;
				queue.push(curns->v);
			}
			curns = curns->next;
		}
		if (queue.empty()) {
			cout << "Кратчайший путь между " << v1->name << " и " << v2->name << " не найден. " << endl;
			return -1;
		}
		v = queue.front();
		if (v->level == count + 1)count++;
	}
	cout << "Кратчайший путь между " << v1->name << " и " << v2->name << " равен " << count << ":" << endl;
	if (count == 0) {
		cout<< v1->name << " -> " << v2->name << endl;
		return 0;
	}
	vertex *vl=NULL;
	v = v1;
	bool found = false;
	while (v1->level >= 0) {
		hash = hashF(v->name);
		curl = findNode(vs[hash], v->name);
		curns = curl->nroot;
		while (curns != NULL) {
			if (curns->v->level == v->level + 1) {
				vl = v;
				v = curns->v;
				if (found) {
					cout << " -> " << v->name;
					if (v == v2) {
						cout << endl;
						v1->level = -1;
						break;
					}
				}
				if (v == v2) {
					found = true;
					v = v1;
					cout << v1->name;
				}
				break;
			}
			curns = curns->next;
		}
		if (curns == NULL) {
			v->level = 0;
			if (v != vl)v = vl;
			else v = v1;
		}
	}
	aroundgraph();
	return count;
}
list* addNode(vertex* v, list* root) { //Ф-я для работы со списком коллизий (*list) ДОБАВЛЕНИЕ экземпляра структуры в список
	list *last;
	//last = (list *)malloc(sizeof(list)); - РАЗОБРАТЬСЯ, почему не работает!!!
	last = new list;
	last->next = root;
	last->key = v->name;
	last->v = v;
	ns *spisok;
	//spisok = (ns *)malloc(sizeof(ns));
	spisok = new ns;
	spisok = NULL;
	last->nroot = spisok;
	return last;
}
list* findNode(list* root, string key) { //Ф-я для работы со списком коллизий (*list) ПОИСК экземпляра структуры в списке по ключу(key)
	list *cur = root;
	if (cur == NULL)return NULL;
	while (cur->key != key) {
		cur = cur->next;
		if (cur == NULL)return NULL;
	}
	return cur;
}
void printList(list* root) { //Ф-я для работы с экземпляром списка коллизий (*list) ВЫВОД
	cout << "Соседи вершины " << root->key << endl;
	printNeighbours(root->nroot);
}
void removeNode(graph* graph, int hash, list* root, string key) { //Ф-я для работы со списком коллизий (*list) УДАЛЕНИЕ экземпляра структуры в списке
	list *cur1 = NULL;
	list *cur2 = root;
	while (cur2->key != key) {
		cur1 = cur2;
		cur2 = cur2->next;
		if (cur2 == NULL)return;
	}
	if (cur2 == root) {
		(*graph).vs[hash] = root->next;
		delete cur2;
		return;
	}
	cur1->next = cur2->next;
	delete cur2;
}
ns* addToRoot(vertex* v, ns* nroot) { //Ф-я для работы со списком смежных вершин (*ns) ДОБАВЛЕНИЕ экземпляра структуры в списке
	ns *cur;
	cur = new ns;
	cur->v = v;
	cur->next = nroot;
	return cur;
}
void removeNeighbour(list* root, vertex* v, ns* nroot) {//Ф-я для работы со списком смежных вершин (*ns) УДАЛЕНИЕ экземпляра структуры в списке
	ns *cur1 = NULL;
	ns* cur2 = nroot;
	if (cur2 == NULL)return;
	while (cur2->v->name != v->name) {
		cur1 = cur2;
		cur2 = cur2->next;
		if (cur2 == NULL) return;
	}
	if (cur2 == nroot) {
		root->nroot = nroot->next;
		delete cur2;
		return;
	}
	cur1->next = cur2->next;
	delete cur2;
}
void printNeighbours(ns* nroot) { //Ф-я для работы со списком смежных вершин (*ns) ВЫВОД списка экземпляров структур
	ns* cur = nroot;
	while (cur != NULL) {
		cout << "\t" << cur->v->name << endl;
		cur = cur->next;
	}
	cout << endl;
}