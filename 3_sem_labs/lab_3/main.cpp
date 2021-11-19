#include <iostream>
#include <string>
#include "graph.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "");
	graph Vertices(true, 2);
	vertex *vert;
	vert = new vertex[5];
	vert[0].name = "A";
	vert[1].name = "B";
	vert[2].name = "C";
	vert[3].name = "D";
	vert[4].name = "E";
	Vertices.addvertex(&vert[0]);
	Vertices.addvertex(&vert[1]);
	Vertices.addvertex(&vert[2]);
	Vertices.addvertex(&vert[3]);
	Vertices.printgraph();
	Vertices.addEdge(&vert[0], &vert[1]);
	Vertices.addEdge(&vert[0], &vert[2]);
	Vertices.addEdge(&vert[1], &vert[3]);
	Vertices.addEdge(&vert[2], &vert[3]);
	Vertices.printgraph();
	Vertices.shortestPath(&vert[0], &vert[1]);
	Vertices.shortestPath(&vert[0], &vert[3]);
	Vertices.addvertex(&vert[5]);
	vert[3].name = "jjhg";
	Vertices.removeVertex(&vert[2]);
	Vertices.shortestPath(&vert[0], &vert[3]);
	/*cout << "Создание графа:\n\nОриентрированность графа (1==Неориентирован 2==Ориентирован): ";
	int directed;
	cin >> directed;
	while ((directed != 1) && (directed != 2)) {
		cout << "Ошибка. Введи корректное значение 1 или 2." << endl;
		cin >> directed;
	}
	graph Mygraph(--directed, 1);
	cout << "\nВведи кол-во вершин в графе (size): "; //На слуйчай если хочется ввести количество самому
	int size;
	cin >> size;
	cout << endl;
	vertex *allvertices = new vertex[size];
	for (int i = 0; i < size; i++) {
		cout << "Введи название " << i + 1 << "-й вершины: ";
		cin >> allvertices[i].name;
		Mygraph.addvertex(&allvertices[i]);
	}
	Mygraph.printgraph();
	vertex* vertex1;
	vertex1 = Mygraph.findVertex("Kiev");
	vertex* vertex2;
	vertex2 = Mygraph.findVertex("Moscow");
	if ((vertex1 != NULL) && (vertex2 != NULL)) {
		if (Mygraph.isEdge(vertex1, vertex2))cout << "Киев связан с Москвой" << endl;
		else cout << "Киев не связан с Москвой" << endl;
		Mygraph.addEdge(vertex1, vertex2);
		if (Mygraph.isEdge(vertex1, vertex2))cout << "Киев связан с Москвой" << endl;
		else cout << "Киев не связан с Москвой" << endl;
		Mygraph.printgraph();
	}
	Mygraph.removeVertex(&allvertices[size - 1]);
	Mygraph.printgraph();
	if (vertex2 != NULL)Mygraph.removeVertex(vertex2);
	Mygraph.printgraph();
	graph Cities(false, 2); //Создаём граф из 4-х городов
	vertex* cities;
	cities = new vertex[4];
	cities[0].name = "Moscow";
	cities[1].name = "Tver";
	cities[2].name = "Ivanovo";
	cities[2].level = 1;
	cities[3].name = "Podolsk";
	for (int i = 0; i < 4; i++) {
		Cities.addvertex(&cities[i]);
	}
	Cities.addEdge(&cities[0], &cities[1]);
	Cities.addEdge(&cities[0], &cities[2]);
	Cities.addEdge(&cities[0], &cities[3]);
	Cities.addEdge(&cities[1], &cities[2]);
	Cities.printgraph();
	Cities.shortestPath(&cities[3], &cities[2]);
	Cities.removeEdge(&cities[0], &cities[2]);
	Cities.removeEdge(&cities[0], &cities[1]);
	Cities.printgraph();
	Cities.shortestPath(&cities[3], &cities[2]);
	char c;
	graph Vertices(false, 17); //Создаём граф из простых вершин
	vertex *vert;
	vert = new vertex[8];
	for (int i = 0; i < 8; i++) {
		c = 65 + i;
		vert[i].name += c;
		Vertices.addvertex(&vert[i]);
	}
	Vertices.addEdge(&vert[0], &vert[1]);
	Vertices.addEdge(&vert[0], &vert[2]);
	Vertices.addEdge(&vert[0], &vert[3]);
	Vertices.addEdge(&vert[0], &vert[4]);
	Vertices.addEdge(&vert[2], &vert[7]);
	Vertices.addEdge(&vert[3], &vert[5]);
	Vertices.addEdge(&vert[4], &vert[5]);
	Vertices.addEdge(&vert[5], &vert[6]);
	Vertices.addEdge(&vert[5], &vert[7]);
	Vertices.addEdge(&vert[6], &vert[7]);
	Vertices.printgraph();
	Vertices.shortestPath(&vert[1], &vert[7]);*/
	system("pause");
	return 0;
}