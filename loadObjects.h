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
		int x, y, z, texNum, baseRad, topRad, height, slices, stacks, texEnvi;
		float s, e;
		bool textured;
		getline(objFile, objInfo);
		cout << objInfo;
		cout << '\n';
		if (objInfo.substr(0, objInfo.find(delim)) == "QUADS") {
			glBegin(GL_QUADS);
		} else if (objInfo.substr(0, objInfo.find(delim)) == "END") {
			glEnd();
			textured = false;
		} else if (objInfo.substr(0, objInfo.find(delim)) == "ENDTEX") {
			textured = false;
		} else if (objInfo.substr(0, objInfo.find(delim)) == "FILEEND") {
			break;
		} else if (objInfo.substr(0, objInfo.find(delim)) == "TEXTURE") {
			textured = true;
			objInfo.erase(0, objInfo.find(delim) + 1);
			texNum = stoi(objInfo.substr(0, objInfo.find(delim)));
			glBindTexture(GL_TEXTURE_2D, texId[texNum]);
			objInfo.erase(0, objInfo.find(delim) + 1);
			texEnvi = stoi(objInfo.substr(0, objInfo.find(delim)));
			if (texEnvi == 1) {
				glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			}
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
			a = stof(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			b = stof(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			c = stof(objInfo.substr(0, objInfo.find(delim)));
			
			glScalef(a, b, c);
			
		} else if (objInfo.substr(0, objInfo.find(delim)) == "TRANSLATE") {
			float a, b, c;
			objInfo.erase(0, objInfo.find(delim) + 1);
			a = stof(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			b = stof(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			c = stof(objInfo.substr(0, objInfo.find(delim)));
			
			glTranslatef(a, b, c);
			
		} else if (objInfo.substr(0, objInfo.find(delim)) == "ROTATE") {
			float angle;
			int x, y, z;
			objInfo.erase(0, objInfo.find(delim) + 1);
			x = stoi(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			y = stoi(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			z = stoi(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			angle = stof(objInfo.substr(0, objInfo.find(delim)));
			
			glRotatef(angle, x, y, z);
			
		} else if (objInfo.substr(0, objInfo.find(delim)) == "COLOUR") {
			float r, g, b;
			objInfo.erase(0, objInfo.find(delim) + 1);
			r = stof(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			g = stof(objInfo.substr(0, objInfo.find(delim)));
			objInfo.erase(0, objInfo.find(delim) + 1);
			b = stof(objInfo.substr(0, objInfo.find(delim)));
			
			glColor3f(r, g, b);
			
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
