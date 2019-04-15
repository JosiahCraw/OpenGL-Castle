#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include "Vertices.h"
#include <cmath>

using namespace std;


void loadVertexes(string file, Vertices vert) {
	string currVertices;
	ifstream verticesFile;
	verticesFile.open(file);
	
	cout << "Loading Verticies X";
	cout << '\n';
	
	getline(verticesFile, currVertices);
	
	cout << "Got line X";
	cout << '\n';
	
	vert.setX(currVertices);
	
	cout << "Loading Verticies Y";
	cout << '\n';
	
	getline(verticesFile, currVertices);
	
	cout << "Got line Y";
	cout << '\n';
	
	vert.setY(currVertices);
	
	cout << "Loading Verticies Z";
	cout << '\n';
	
	getline(verticesFile, currVertices);
	
	cout << "Got line Z";
	cout << '\n';
	
	vert.setZ(currVertices);
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


void revolve(string file, bool textured, int num) {
	float wx[num]={}, wy[num]={}, wz[num]={}, theta, s, t;
	
	theta = -1 * M_PI / 180;
	
	Vertices vert(num);
	
	loadVertexes(file, vert);
	
	vert.print();
	
	for (int j=0;j<360;j++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int i=0;i<vert.num;i++) {
			wx[i] = vert.x[i] * cos(theta) + vert.z[i] * sin(theta);
			wy[i] = vert.y[i];
			wz[i] = -vert.x[i] * sin(theta) + vert.z[i] * cos(theta);
			
			if (i > 0) {
				normal(vert.x[i-1], vert.y[j-1], vert.z[j-1],
					vert.x[i], vert.y[i], vert.z[i],
					wx[i], wy[i], wz[i]);
			}
			
			if (textured) {
				s = j/36.0;
				t = i / (float)vert.num;
				
				glTexCoord2f(s, t);
				glVertex3f(vert.x[i], vert.y[i], vert.z[j]);
				
				glVertex3f(wx[i], wy[i], wz[i]);					
			} else {
				glVertex3f(vert.x[i], vert.y[i], vert.z[j]);
				glVertex3f(wx[i], wy[i], wz[i]);
			}
			
			vert.x[i] = wx[i];
			vert.y[i] = wy[i];
			vert.z[i] = wz[i];	
		}
		glEnd();
		
	}
}
