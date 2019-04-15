#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include "Vertices.h"
using namespace std;


void loadVertexes(string file) {
	const char* DELIM = ",";
	string currVertices;
	ifstream verticesFile;
	int numVertices;
	verticesFile.open(file);
	
	getline(verticesFile, currVertices);
	
	numVertices = stoi(currVertices.substr(0, currVertices.find(DELIM)));
	currVertices.erase(0, currVertices.find(DELIM) + 1);
	Vertices vert(numVertices);
	
	while (1) {
		
	}
	
}

void revolve(void) {
	
}
