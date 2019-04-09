#include <iostream>
#include <fstream>
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
float angle=0, look_x, look_z=-1., eye_x, eye_z; 
//GLuint texId[NUMTEX];


void initialise(void) {
	//float black[4] = {0.0, 0.0, 0.0, 1.0};
    //float white[4]  = {1.0, 1.0, 1.0, 1.0};
    
	CompNumOfTex();
	NUMTEX = numOfTex();
	glGenTextures(NUMTEX, texId);
    loadTextures(texId);
    
    glClearColor (0., 0., 0., 0.);
    
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
    glEnable(GL_NORMALIZE);
    
	//glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    //glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    //glLightfv(GL_LIGHT0, GL_SPECULAR, white);
    
    //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //glEnable(GL_COLOR_MATERIAL);
	//glEnable(GL_TEXTURE_2D);
	
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(80.0, 1.0, 100.0, 5000.0);   //Perspective projection
}


void display(void) {
	float cdr=3.14159265/180.0;
	//float lgt_pos[] = {0.0f, 0.0f, 0.0f, 1.0f};
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
	//gluPerspective(45., 1., 1., 100.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	look_x = -100.0*sin(lookAngle*cdr);
    look_z = -100.0*cos(lookAngle*cdr);
	gluLookAt(eye_x, 500, eye_z, look_x, 500, look_z,   0, 1, 0);
	
	//glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);
	//glDisable(GL_LIGHTING);
	//glClearColor (0.2f, 0.2f, 0.2f, 1.0f);
	loadObjFromFile("cfg/skybox.cfg", texId);
	cout << "HERE";
	cout << '\n';
	//glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
	loadObjFromFile("cfg/castle.cfg", texId);
	glFlush();
}


 void special(int key, int x, int y) {
    if(key == GLUT_KEY_LEFT) lookAngle += 5;  //Change direction
        else if(key == GLUT_KEY_RIGHT) lookAngle -= 5;
        else if(key == GLUT_KEY_DOWN)
        {  //Move backward
                eye_x -= 0.1*sin(angle);
                eye_z += 0.1*cos(angle);
        }
        else if(key == GLUT_KEY_UP)
        { //Move forward
                eye_x += 0.1*sin(angle);
                eye_z -= 0.1*cos(angle);
        }

        look_x = eye_x + 100*sin(angle);
        look_z = eye_z - 100*cos(angle);
        glutPostRedisplay();
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH );
	glutInitWindowSize (1280, 720); 
	glutInitWindowPosition (50, 50);
	
	glutCreateWindow ("Castle Battle");
	initialise();
	glutDisplayFunc(display); 
	glutSpecialFunc(special);
	
	glutMainLoop();
	return 0;
}
