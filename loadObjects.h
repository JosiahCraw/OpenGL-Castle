#include <GL/glut.h>
#include "loadTGA.h"
#include "loadBMP.h"
#include <iostream>
#include <fstream>
using namespace std;


void loadObjFromFile(string file, GLuint texId[]) {
	string objInfo;
	ifstream objFile;
	const char* delim = ",";
	objFile.open(file);
	glEnable(GL_TEXTURE_2D);
	while (1) {
		int x, y, z, texNum;
		float s, e;
		getline(objFile, objInfo);
		if (objInfo.substr(0, objInfo.find(delim)) == "QUADS") {
			glBegin(GL_QUADS);
		} else if (objInfo.substr(0, objInfo.find(delim)) == "END") {
			glEnd();
		} else if (objInfo.substr(0, objInfo.find(delim)) == "FILEEND") {
			break;
		} else if (objInfo.substr(0, objInfo.find(delim)) == "TEXTURE") {
			objInfo.erase(0, objInfo.find(delim) + 1);
			texNum = stoi(objInfo.substr(0, objInfo.find(delim)));
			glBindTexture(GL_TEXTURE_2D, texId[texNum]);
		} else {
			x = stoi(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			y = stoi(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			z = stoi(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			s = stof(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			e = stof(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			
			glTexCoord2f(s, e);
			glVertex3f(x,  y, z);
			
			
		}
	}
	
}
