#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include "Path.h"

using namespace std;

void loadMotion(string file, Path* path) {
	string currPath;
	ifstream pathFile;
	pathFile.open(file);
	
	getline(pathFile, currPath);
	path->setX(currPath);
	
	getline(pathFile, currPath);
	path->setY(currPath);
	
	getline(pathFile, currPath);
	path->setZ(currPath);
}

void linearMotion(string file, int index[], int num, int currIndex, int repeat, bool hold) {
	
	Path path(num);
	
	loadMotion(file, &path);
	
	if (index[currIndex] >= num) {
		if (repeat) {
			index[currIndex] = 0;
		} else {
			index[currIndex] = num-1;
		}
	}
	
	glTranslatef(path.x[index[currIndex]], path.y[index[currIndex]], path.z[index[currIndex]]);
	
	if (!hold) {
		index[currIndex] += 1;
	}
}
