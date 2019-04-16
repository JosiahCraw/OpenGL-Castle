#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <cmath>
#include "class/ExtrudeVerts.h"

using namespace std;


void loadVertexes(string file, ExtrudeVerts *vert) {
	string currExtrudeVerts;
	ifstream ExtrudeVertsFile;
	ExtrudeVertsFile.open(file);
	
	getline(ExtrudeVertsFile, currExtrudeVerts);
	vert->setX(currExtrudeVerts);
	
	getline(ExtrudeVertsFile, currExtrudeVerts);
	vert->setY(currExtrudeVerts);
	
	getline(ExtrudeVertsFile, currExtrudeVerts);
	vert->setZ(currExtrudeVerts);
	
}

void extNormal(float x1, float y1, float z1,
            float x2, float y2, float z2,
            float x3, float y3, float z3 ) {
    float nx, ny, nz;
    nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
    ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
    nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}

void extrude(string file, float width, float height, float depth, bool textured, int num) {
	float wx[num]={}, wy[num]={}, wz[num]={};
	
	ExtrudeVerts vert(num);
	
	loadVertexes(file, &vert);
	
	glBegin(GL_TRIANGLE_STRIP);
	
	for (int i=0; i<vert.num; i++) {
		wx[i] = vert.x[i] + width;
		wy[i] = vert.y[i] + height;
		wz[i] = vert.z[i] + depth;
		
		if (i > 0) {
			extNormal(wx[i-1], wy[i-1], wz[i-1], 
				vert.x[i-1], vert.y[i-1], vert.z[i-1], 
				vert.x[i], vert.y[i], vert.z[i]);
		}
		
		if (textured) {
			glTexCoord2f(1/(float)num,0.0);
		}
		
		glVertex3f(vert.x[i], vert.y[i], vert.z[i]);
		
		if (i > 0) {
			extNormal(wx[i-1], wy[i-1], wz[i-1], 
				vert.x[i-1], vert.y[i-1], vert.z[i-1], 
				vert.x[i], vert.y[i], vert.z[i]);
		}
		
		if (textured) {
			glTexCoord2f(1/(float)num,1.0);
		}
		
		glVertex3f(wx[i], wy[i], wz[i]);
	}
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP);
	for (int i=0; i<vert.num; i++) {
		if (i > 0) {
			extNormal(wx[i-1], wy[i-1], wz[i-1], 
				vert.x[i-1], vert.y[i-1], vert.z[i-1], 
				vert.x[i], vert.y[i], vert.z[i]);
		}
		glVertex3f(vert.x[i], vert.y[i], vert.z[i]);
	}
	glEnd();
	
	glBegin(GL_TRIANGLE_STRIP);
	for (int i=0; i<vert.num; i++) {
		if (i > 0) {
			extNormal(wx[i-1], wy[i-1], wz[i-1], 
				vert.x[i-1], vert.y[i-1], vert.z[i-1], 
				vert.x[i], vert.y[i], vert.z[i]);
		}
		glVertex3f(wx[i], wy[i], wz[i]);
	}
	glEnd();
}
