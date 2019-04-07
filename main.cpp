#include <iostream>
#include <cmath> 
#include <GL/freeglut.h>
#include <bits/stdc++.h>
#include "loadTGA.h"
#include "loadTextures.h"
#include "loadObjects.h"


using namespace std;

#define GL_CLAMP_TO_EDGE 0x812F   //To get rid of seams between textures
float lookAngle = 0.0;		//Camera rotation
int NUMTEX;
GLuint texId[100];
//GLuint texId[NUMTEX];


void initialise(void) {
	float black[4] = {0.0, 0.0, 0.0, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};
    
	CompNumOfTex();
	NUMTEX = numOfTex();
	glGenTextures(NUMTEX, texId);
    loadTextures(texId);
    
    glClearColor (0.2f, 0.2f, 0.2f, 1.0f);
    
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(80.0, 1.0, 100.0, 5000.0);   //Perspective projection
}


void display(void) {
	float lgt_pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
	float xlook, zlook;
	float cdr=3.14159265/180.0;	//Conversion from degrees to radians
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	xlook = -100.0*sin(lookAngle*cdr);
	zlook = -100.0*cos(lookAngle*cdr);
	gluLookAt (0, 500, 0, xlook, 500, zlook, 0, 1, 0);  //camera rotation
	
	glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);
	
	glClearColor (0.2f, 0.2f, 0.2f, 1.0f);
	//loadObjFromFile("cfg/skybox.cfg", texId);
	
	loadObjFromFile("cfg/castle.cfg", texId);
	glFlush();
}


 void special(int key, int x, int y) {
    if(key==GLUT_KEY_LEFT) lookAngle+=5;		 //Turn left
    else if(key==GLUT_KEY_RIGHT) lookAngle-=5;   //Turn right

	glutPostRedisplay();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH );
	glutInitWindowSize (1280, 720); 
	glutInitWindowPosition (50, 50);
	
	glutCreateWindow ("Castle Battle");
	initialise();
	glutDisplayFunc(display); 
	glutSpecialFunc(special);
	
	glutMainLoop();
	return 0;
}

