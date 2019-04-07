#include <GL/glut.h>
#include "loadTGA.h"
#include "loadBMP.h"
#include <iostream>
#include <fstream>
using namespace std;

enum OBJECTS {QUADS=0, CYLINDER, CONE};

void loadObjFromFile(string file, GLuint texId[]) {
	string objInfo;
	ifstream objFile;
	const char* delim = ",";
	objFile.open(file);
	glEnable(GL_TEXTURE_2D);
	int objectType = 0;
	while (1) {
		int x, y, z, texNum, baseRad, topRad, height, slices, stacks;
		float s, e;
		bool textured;
		getline(objFile, objInfo);
		if (objInfo.substr(0, objInfo.find(delim)) == "QUADS") {
			glBegin(GL_QUADS);
		} else if (objInfo.substr(0, objInfo.find(delim)) == "END") {
			glEnd();
			textured = false;
		} else if (objInfo.substr(0, objInfo.find(delim)) == "FILEEND") {
			break;
		} else if (objInfo.substr(0, objInfo.find(delim)) == "TEXTURE") {
			textured = true;
			objInfo.erase(0, objInfo.find(delim) + 1);
			texNum = stoi(objInfo.substr(0, objInfo.find(delim)));
			glBindTexture(GL_TEXTURE_2D, texId[texNum]);
		} else if (objInfo.substr(0, objInfo.find(delim)) == "CYLINDER") {
			objectType = CYLINDER;
		} else if (objInfo.substr(0, objInfo.find(delim)) == "CONE") {
			objectType = CONE;
		} else if (objInfo.substr(0, objInfo.find(delim)) == "PUSH") {
			glPushMatrix();
		} else if (objInfo.substr(0, objInfo.find(delim)) == "POP") {
			glPopMatrix();
		} else if (objInfo.substr(0, objInfo.find(delim)) == "SCALE") {
			float a, b, c;
			objInfo.erase(0, objInfo.find(delim) + 1);
			a = stoi(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			b = stoi(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			c = stoi(objInfo.substr(0, objInfo.find(delim)));
			
			glScalef(a, b, c);
			
		} else if (objInfo.substr(0, objInfo.find(delim)) == "TRANSLATE") {
			float a, b, c;
			objInfo.erase(0, objInfo.find(delim) + 1);
			a = stoi(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			b = stoi(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			c = stoi(objInfo.substr(0, objInfo.find(delim)));
			
			glTranslatef(a, b, c);
			
		} else {
			switch (objectType) {
				case (QUADS):
					x = stoi(objInfo.substr(0, objInfo.find(delim)));
					objInfo.erase(0, objInfo.find(delim) + 1);
					y = stoi(objInfo.substr(0, objInfo.find(delim)));
					objInfo.erase(0, objInfo.find(delim) + 1);
					z = stoi(objInfo.substr(0, objInfo.find(delim)));
					objInfo.erase(0, objInfo.find(delim) + 1);
					if (textured) {
						s = stof(objInfo.substr(0, objInfo.find(delim)));
						objInfo.erase(0, objInfo.find(delim) + 1);
						e = stof(objInfo.substr(0, objInfo.find(delim)));
						objInfo.erase(0, objInfo.find(delim) + 1);
						glTexCoord2f(s, e);
					}
					glVertex3f(x,  y, z);
					break;
				case (CYLINDER):
					baseRad = stoi(objInfo.substr(0, objInfo.find(delim)));
					objInfo.erase(0, objInfo.find(delim) + 1);
					topRad = stoi(objInfo.substr(0, objInfo.find(delim)));
					objInfo.erase(0, objInfo.find(delim) + 1);
					height = stoi(objInfo.substr(0, objInfo.find(delim)));
					objInfo.erase(0, objInfo.find(delim) + 1);
					slices = stoi(objInfo.substr(0, objInfo.find(delim)));
					objInfo.erase(0, objInfo.find(delim) + 1);
					stacks = stoi(objInfo.substr(0, objInfo.find(delim)));
					objInfo.erase(0, objInfo.find(delim) + 1);
					
					GLUquadric *quad;
					quad = gluNewQuadric();
					
					gluCylinder(quad, baseRad, topRad, height, slices, stacks);
					gluQuadricDrawStyle(quad, GLU_FILL);
					break;	
				case (CONE):
					baseRad = stoi(objInfo.substr(0, objInfo.find(delim)));
					objInfo.erase(0, objInfo.find(delim) + 1);
					height = stoi(objInfo.substr(0, objInfo.find(delim)));
					objInfo.erase(0, objInfo.find(delim) + 1);
					slices = stoi(objInfo.substr(0, objInfo.find(delim)));
					objInfo.erase(0, objInfo.find(delim) + 1);
					stacks = stoi(objInfo.substr(0, objInfo.find(delim)));
					objInfo.erase(0, objInfo.find(delim) + 1);
					
					glutSolidCone(baseRad, height, slices, stacks);
					break;
			}
		}
	}
	
}
