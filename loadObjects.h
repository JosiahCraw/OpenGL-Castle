#include <GL/glut.h>
#include "loadTGA.h"
#include "loadBMP.h"
#include "revolve.h"
#include <iostream>
#include <fstream>
using namespace std;

enum OBJECTS {QUADS=0, CYLINDER, CONE, SPHERE, RECTANGLE, REVOLVE};
const char* DELIM = ",";

void texture(string objInfo, GLuint texId[]) {
	int texNum, texEnvi;
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	texNum = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	glBindTexture(GL_TEXTURE_2D, texId[texNum]);
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	texEnvi = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	if (texEnvi == 1) {
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	} else if (texEnvi == 2) {
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
}


void scale(string objInfo) {
	float a, b, c;
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	a = stof(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	b = stof(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	c = stof(objInfo.substr(0, objInfo.find(DELIM)));
	
	glScalef(a, b, c);
}


void translate(string objInfo) {
	float a, b, c;
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	a = stof(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	b = stof(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	c = stof(objInfo.substr(0, objInfo.find(DELIM)));
	
	glTranslatef(a, b, c);
}

void rotate(string objInfo) {
	float angle;
	int x, y, z;
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	x = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	y = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	z = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	angle = stof(objInfo.substr(0, objInfo.find(DELIM)));
	cout << objInfo;
	cout << '\n';
	cout << angle;
	glRotatef(angle, x, y, z);
}

void colour(string objInfo) {
	float r, g, b;
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	r = stof(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	g = stof(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	b = stof(objInfo.substr(0, objInfo.find(DELIM)));
	
	glColor3f(r, g, b);
}

void quads(string objInfo, bool textured, GLuint texId[]) {
	int x, y, z;
	float s, e;
	
	x = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	y = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	z = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	
	if (textured) {
		s = stof(objInfo.substr(0, objInfo.find(DELIM)));
		objInfo.erase(0, objInfo.find(DELIM) + 1);
		e = stof(objInfo.substr(0, objInfo.find(DELIM)));
		objInfo.erase(0, objInfo.find(DELIM) + 1);
		glTexCoord2f(s, e);
	}
	
	glVertex3f(x, y, z);
}

void cylinder(string objInfo) {
	int baseRad, topRad, height, slices, stacks;
	
	baseRad = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	topRad = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	height = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	slices = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	stacks = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	
	GLUquadric *quad;
	quad = gluNewQuadric();
	
	gluCylinder(quad, baseRad, topRad, height, slices, stacks);
	gluQuadricDrawStyle(quad, GLU_FILL);
}

void cone(string objInfo) {
	int baseRad, height, slices, stacks;
	
	baseRad = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	height = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	slices = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	stacks = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	
	glutSolidCone(baseRad, height, slices, stacks);
}

void sphere(string objInfo) {
	int radius, slices, stacks;
	
	radius = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	slices = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	stacks = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	
	glutSolidSphere(radius, slices, stacks);					
}

void rectangle(string objInfo, bool textured, GLuint texId[]) {
	int width, height, depth;
	int mainFaceTiles[2] = {};
	
	width = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	height = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	depth = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	
	if (textured) {
		mainFaceTiles[0] = stoi(objInfo.substr(0, objInfo.find(DELIM)));
		objInfo.erase(0, objInfo.find(DELIM) + 1);
		mainFaceTiles[1] = stoi(objInfo.substr(0, objInfo.find(DELIM)));
		objInfo.erase(0, objInfo.find(DELIM) + 1);
	}
	
	int corners[8][3] = {
		{0,0,0},
		{width,0,0},
		{width,height,0},
		{0,height,0},
		{0,0,depth},
		{width,0,depth},
		{width,height,depth},
		{0,height,depth}
	};
	
	int faces[6][4] = {
		{0,1,2,3},
		{4,0,3,7},
		{1,5,6,2},
		{3,2,6,7},
		{4,5,1,0},
		{5,4,7,6}
	};
		
	int textures[4][2] = {
		{0,0},
		{1,0},
		{1,1},
		{0,1}
	};
	
	if (textured) {
		textures[1][0] = mainFaceTiles[0];
		textures[2][0] = mainFaceTiles[0];
		textures[2][1] = mainFaceTiles[1];
		textures[3][1] = mainFaceTiles[1];
	}
		
	for (int i=0; i<6;i++) {
		//glBindTexture(GL_TEXTURE_2D, texId[8]);
		glBegin(GL_QUADS);
		for (int j=0; j<4; j++) {
			int points[3] = {corners[faces[i][j]][0],
				corners[faces[i][j]][1], 
				corners[faces[i][j]][2]};
			if (textured) {
				glTexCoord2f(textures[j][0], textures[j][1]);
			}
			glVertex3f(points[0], points[1], points[2]);
		}
		textured = false;
		glEnd();
	}
}

void getRevolve(string objInfo, bool textured) {
	string file = objInfo.substr(0, objInfo.find(DELIM));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	int num = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	int slices = stoi(objInfo.substr(0, objInfo.find(DELIM)));
	objInfo.erase(0, objInfo.find(DELIM) + 1);
	
	revolve(file, textured, num, slices);
}


void loadObjFromFile(string file, GLuint texId[]) {
	string objInfo;
	ifstream objFile;
	objFile.open(file);
	glEnable(GL_TEXTURE_2D);
	int objectType = 0;
	while (1) {
		bool textured;
		getline(objFile, objInfo);
		cout << objInfo;
		cout << '\n';
		if (objInfo.substr(0, objInfo.find(DELIM)) == "QUADS") {
			glBegin(GL_QUADS);
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "END") {
			glEnd();
			textured = false;
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "ENDTEX") {
			textured = false;
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "FILEEND") {
			break;
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "TEXTURE") {
			textured = true;
			texture(objInfo, texId);
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "CYLINDER") {
			objectType = CYLINDER;
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "SPHERE") {
			objectType = SPHERE;
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "CONE") {
			objectType = CONE;
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "RECTANGLE") {
			objectType = RECTANGLE;
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "PUSH") {
			glPushMatrix();
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "POP") {
			glPopMatrix();
			glColor3f(0.0, 0.0, 0.0);
			textured = false;
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "SCALE") {
			scale(objInfo);			
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "TRANSLATE") {
			translate(objInfo);			
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "ROTATE") {
			rotate(objInfo);			
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "COLOUR") {
			colour(objInfo);			
		} else if (objInfo.substr(0, objInfo.find(DELIM)) == "REVOLVE") {
			objInfo.erase(0, objInfo.find(DELIM) + 1);
			getRevolve(objInfo, textured);			
		} else {
			switch (objectType) {
				case (QUADS):
					quads(objInfo, textured, texId);
					break;
				case (CYLINDER):
					cylinder(objInfo);
					break;	
				case (CONE):
					cone(objInfo);					
					break;
				case (SPHERE):
					sphere(objInfo);
					break;
				case (RECTANGLE):					
					rectangle(objInfo, textured, texId);					
					break;
			}
		}
	}
	
}
