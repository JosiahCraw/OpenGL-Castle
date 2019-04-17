#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include "class/Vertices.h"
#include <cmath>

using namespace std;


void loadVertexes(string file, Vertices *vert) {
	string currVertices;
	ifstream verticesFile;
	verticesFile.open(file);
	
	getline(verticesFile, currVertices);
	vert->setX(currVertices);
	
	getline(verticesFile, currVertices);
	vert->setY(currVertices);
	
	getline(verticesFile, currVertices);
	vert->setZ(currVertices);
	
}

void normal(float x1, float y1, float z1,
            float x2, float y2, float z2,
            float x3, float y3, float z3 ) {
    float nx, ny, nz;
    nx = y1*(z2-z3)+ y2*(z3-z1)+ y3*(z1-z2);
    ny = z1*(x2-x3)+ z2*(x3-x1)+ z3*(x1-x2);
    nz = x1*(y2-y3)+ x2*(y3-y1)+ x3*(y1-y2);
    glNormal3f(nx, ny, nz);
}


void revolve(string file, bool textured, int num, int slices) {
	float wx[num]={}, wy[num]={}, wz[num]={}, theta, s, t;
	theta = (360.0/slices) * M_PI / 180;
	
	Vertices vert(num);
	
	loadVertexes(file, &vert);
	
	for (int j=0;j<slices;j++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int i=0;i<vert.num;i++) {
			wx[i] = vert.x[i] * cos(theta) + vert.z[i] * sin(theta);
			wy[i] = vert.y[i];
			wz[i] = -vert.x[i] * sin(theta) + vert.z[i] * cos(theta);
		}		
		for (int i=0;i<vert.num;i++) {
			
			if (textured) {
				s = j/(float)slices;
				t = i / (float)vert.num;

				glTexCoord2f(s, t);
			}
								
			if (i > 0) {
			normal(wx[i-1], wy[i-1], wz[i-1], 
				vert.x[i-1], vert.y[i-1], vert.z[i-1], 
				vert.x[i], vert.y[i], vert.z[i]);
			}
			
			glVertex3f(vert.x[i], vert.y[i], vert.z[i]);
			
			if (i > 0) {
			normal(wx[i-1], wy[i-1], wz[i-1],
				vert.x[i], vert.y[i], vert.z[i],
				wx[i], wy[i], wz[i]);
			}
			
			if (textured) {
				s = (j+1)/(float)slices;
				t = i / (float)vert.num;

				glTexCoord2f(s, t);
			}
			
			glVertex3f(wx[i], wy[i], wz[i]);
		}
		for (int i=0;i<vert.num;i++) {
			
			vert.x[i] = wx[i];
			vert.y[i] = wy[i];
			vert.z[i] = wz[i];	
		}
		glEnd();
	}
}
