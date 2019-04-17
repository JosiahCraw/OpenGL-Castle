#include <iostream>
#include <fstream>
#include <cmath> 
#include <GL/freeglut.h>
#include <bits/stdc++.h>
#include "src/loadTGA.h"
#include "src/loadTextures.h"
#include "src/loadObjects.h"

using namespace std;

#define GL_CLAMP_TO_EDGE 0x812F   //To get rid of seams between textures
float lookAngle = 0.0;		//Camera rotation
int NUMTEX;
GLuint texId[100];
GLuint texIdEmpty[2];
float look_x, look_z=-1., eye_x, eye_z; 
bool spacePressed=false;
bool cannonPressed=false;
bool pressed=false;
float cutoff=15,expo=50;


void initialise(void) {
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
	glEnable(GL_LIGHT1);
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
    gluPerspective(80.0, 1.78, 100.0, 50000.0);
}


void display(void) {
	float lgt_pos[] = {1000.0f, 1000, 1000.0f, 1000.0f};
	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	float spotdir[] = {0, 1, 0};
	
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, cutoff);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, expo);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotdir);
	
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, cutoff);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, expo);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spotdir);
	
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, cutoff);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, expo);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spotdir);
	
	glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, cutoff);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, expo);
	glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, spotdir);
		
	gluLookAt(eye_x, 150, eye_z, look_x, 150, look_z,   0, 1, 0);
	
	
	glLightfv(GL_LIGHT0, GL_POSITION, lgt_pos);
    
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
    
	loadObjFromFile("cfg/obj/ship.cfg", texId, spacePressed);
	loadObjFromFile("cfg/obj/robot1.cfg", texId, pressed);
	loadObjFromFile("cfg/obj/robot2.cfg", texId, pressed);
	loadObjFromFile("cfg/obj/cannon.cfg", texId, cannonPressed);
	//loadObjFromFile("cfg/obj/castleTest.cfg", texId, pressed);
	loadObjFromFile("cfg/obj/castle.cfg", texId, pressed);
	
	glDisable(GL_COLOR_MATERIAL);
	
	glDisable(GL_LIGHTING);
	
	loadObjFromFile("cfg/obj/skybox.cfg", texId, pressed);
	
	glEnable(GL_LIGHTING);
	
	glutSwapBuffers();
}


 void special(int key, int x, int y) {
    if(key == GLUT_KEY_LEFT) lookAngle -= 0.087;  //Change direction
        else if(key == GLUT_KEY_RIGHT) lookAngle += 0.087;
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
}

void keyPresses(unsigned char key, int x, int y) {
	if(key == 115) {
		spacePressed = !spacePressed;
	} else if (key == 99) {
		cannonPressed = true;
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
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
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
