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
float look_x, look_z=-1., eye_x, eye_z; 
bool pressed=false;


void initialise(void) {
	//float black[4] = {0.0, 0.0, 0.0, 1.0};
    float white[4]  = {1.0, 1.0, 1.0, 1.0};
    float grey[4] = {0.2, 0.2, 0.2, 1.0};
    
	CompNumOfTex();
	NUMTEX = numOfTex();
	glGenTextures(NUMTEX, texId);
    loadTextures(texId);
    
    glClearColor (0., 0., 0., 0.);
    
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glEnable(GL_SMOOTH);
    
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glClearColor (1.0, 1.0, 1.0, 0.0);

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(80.0, 1.78, 100.0, 5000.0);
}


void display(void) {
	float white[4]  = {1.0, 1.0, 1.0, 1.0};
	
	//float cdr=3.14159265/180.0;
	float lgt_pos[] = {1000.0f, 1000, 1000.0f, 1000.0f};
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
	//gluPerspective(45., 1.78, 100., 5000.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//look_x = -100.0*sin(lookAngle*cdr);
    //look_z = -100.0*cos(lookAngle*cdr);
	gluLookAt(eye_x, 500, eye_z, look_x, 500, look_z,   0, 1, 0);
	
	glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	//glClearColor (0.2f, 0.2f, 0.2f, 1.0f);
	loadObjFromFile("cfg/skybox.cfg", texId, pressed);
	loadObjFromFile("cfg/ship.cfg", texId, pressed);
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
	loadObjFromFile("cfg/castle.cfg", texId, pressed);
	glFlush();
}


 void special(int key, int x, int y) {
    if(key == GLUT_KEY_LEFT) lookAngle -= 0.1;  //Change direction
        else if(key == GLUT_KEY_RIGHT) lookAngle += 0.1;
        else if(key == GLUT_KEY_DOWN)
        {  //Move backward
                eye_x -= sin(lookAngle);
                eye_z += cos(lookAngle);
        }
        else if(key == GLUT_KEY_UP)
        { //Move forward
			eye_x += sin(lookAngle);
			eye_z -= cos(lookAngle);
		}

        look_x = eye_x + 100*sin(lookAngle);
        look_z = eye_z - 100*cos(lookAngle);
        glutPostRedisplay();
}

void keyPresses(unsigned char key, int x, int y) {
	if(key == 99) {
		cout << "Pressed!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1";
		cout << '\n';
		pressed = !pressed;
	}
}

void timer(int value)
{
	cout << "test";
	cout << '\n';
	glutTimerFunc(50, timer, value);
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
	glutKeyboardFunc(keyPresses);
	glutTimerFunc(50, timer, 0);
	
	glutMainLoop();
	return 0;
}
