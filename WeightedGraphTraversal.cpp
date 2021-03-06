#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define vertices 10
#define inf 1000

int *conversion(int *graphOne, int row, int column) {
	int *p;
	p = graphOne + (row * vertices + column);
	return p;
}

void printGraph(int graph[][vertices]) {
	bool occurence[vertices][vertices];
	int i;
	int j;
	int count = 0;
	
	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			occurence[i][j] = false;
		}
	}
	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			if (graph[i][j] != inf && graph[i][j] != 0 && occurence[i][j] == false) {//edge exists
				if (i < j) {
					printf("V%d-V%d=%d\n", i + 1, j + 1, graph[i][j]);
					count++;
				}
				else {
					printf("V%d-V%d=%d\n", j + 1, i + 1, graph[i][j]);
					count++;
				}
				occurence[i][j] = true;
				occurence[j][i] = true;
			}
		}
	}
	printf("%d Edges\n", count);
}

void loopRemoval(int *graphOne, bool past[], int vertex, bool sameEdge[]) {
	int i;
	vertex--;//scale down from 1-10 to 0-9

	for (i = 0; i < vertices; i++) {
		if (*conversion(graphOne, vertex, i) != 0 && *conversion(graphOne, vertex, i) != inf && sameEdge[10*vertex+i] == false) {
			if (past[i] == true) {//loop destruction
				*conversion(graphOne, vertex, i) = inf;
				*conversion(graphOne, i, vertex) = inf;
			}
			else {
				past[vertex] = true;
				sameEdge[10 * vertex + i] = true;
				sameEdge[10 * i + vertex] = true;
				i++;//scale up
				loopRemoval(graphOne, past, i, sameEdge);
				i--;//scale back down
			}
		}
	}
}

bool allTrue(bool content[]) {
	int i = sizeof(content) / sizeof(bool);//num of elements
	i--;

	for (i; i >= 0; i--) {
		if (content[i] == false) {
			return false;
			exit(0);
		}
	}

	return true;
}

int shortestPath(int graph[][vertices], int start, int end) {
	int distances[vertices];//distance from start to each vertex, inf=no edge
	char paths[vertices][vertices + 2];//path of the shortest distance from start to each vertex
	bool inTree[vertices];
	int cVertex;
	int pVertex = inf;
	int smallestVal = inf;//initialize as biggest possible val
	int i;
	int j;

	for (i = 0; i < vertices; i++) {
		inTree[i] = false;
		distances[i] = inf;
		for (j = 0; j < vertices + 2; j++) {
			paths[i][j] = 0;
		}
	}
	start--;//scale down from 1-10 to 0-9
	end--;
	inTree[start] = true;
	distances[start] = 0;

	cVertex = start;
	while (allTrue(inTree) == false) {
		for (i = 0; i < vertices; i++) {
			if (graph[cVertex][i] != 0 && graph[cVertex][i] != inf && i != pVertex) {//vertex exists from start to i, not loop
				if ((graph[cVertex][i]+distances[cVertex]) < distances[i]) {
					distances[i] = graph[cVertex][i] + distances[cVertex];
					//implement path thingy here
					memcpy(paths[i], paths[cVertex], sizeof(paths[cVertex]) / sizeof(char));
					for (j = 0; j < vertices + 2; j++) {
						if (paths[i][j] == 0) {
							break;
						}
					}
					paths[i][j] = cVertex + '0';
				}
			}
		}
		pVertex = cVertex;
		for (i = 0; i < vertices; i++) {
			if (distances[i] < smallestVal && inTree[i] == false) {
				smallestVal = distances[i];
				cVertex = i;
			}
		}
		inTree[cVertex] = true;
		smallestVal = inf;
	}
	printf("\n");
	for (j = 0; j < vertices + 2; j++) {
		if (paths[end][j] != 0) {
			printf("V%c ", paths[end][j]+1);
		}
	}
	printf("\n");
	return distances[end];
}

int main()
{
	int graph[vertices][vertices];
	bool created[vertices];
	bool past[vertices];
	bool sameEdge[vertices*vertices];
	int edges = vertices + 2;
	int currentV;
	int prevV;
	int i;
	int j;
	
	//Initialization Stuff
	srand(time(0));
	for (i = 0; i < vertices; i++) {
		for (j = 0; j < vertices; j++) {
			graph[i][j] = inf;//no edge connection between the two vertices
			sameEdge[10 * i + j] = false;
		}
		created[i] = false;
		graph[i][i] = 0;
		past[i] = false;
	}

	//Randomly Generate Graph(Potential Loop)
	prevV = rand() % 10;
	for (i = 0; i < edges; i++) {
		currentV = rand() % 10;
		if (i < vertices) {
			while (created[currentV] == true || (graph[prevV][currentV] < inf && graph[prevV][currentV] >= 0)) {
				currentV = rand() % 10;
			}
		}
		else {
			while (graph[prevV][currentV] < inf && graph[prevV][currentV] >= 0) {
				currentV = rand() % 10;
			}
		}
		created[currentV] = true;
		graph[prevV][currentV] = rand() % 15 + 1;//assign weight
		graph[currentV][prevV] = graph[prevV][currentV];
		prevV = currentV;
	}
	//Loop Removal
	loopRemoval(&graph[0][0], past, 1, sameEdge);
	printGraph(graph);

	//Find Shortest Path
	int start = 0;
	int end = 0;
	char input;

	printf("Please Enter the Starting Vertex: ");
	while ((input = getchar()) != '\n') {
		start = start * 10 + (input - '0');
	}
	printf("Please Enter the Ending Vertex: ");
	while ((input = getchar()) != '\n') {
		end = end * 10 + (input - '0');
	}
	i = shortestPath(graph, start, end);
	printf("Shortest Path has Length %d\n", i);
}