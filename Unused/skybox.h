#include <GL/freeglut.h>

void skybox(GLuint texId[]) {
	
	glEnable(GL_TEXTURE_2D);
	
	////////////////////// LEFT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1000,  0, 1000);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-1000, 0., -1000);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1000, 1000., -1000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1000, 1000, 1000);
	glEnd();
	
	////////////////////// FRONT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[1]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1000,  0, -1000);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1000, 0., -1000);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1000, 1000, -1000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1000,  1000, -1000);
	glEnd();
	
	////////////////////// RIGHT WALL ///////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[2]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1000,  0, -1000);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1000, 0, 1000);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1000, 1000,  1000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1000,  1000,  -1000);
	glEnd();
	
	////////////////////// REAR WALL ////////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[3]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f( 1000, 0, 1000);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-1000, 0,  1000);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1000, 1000,  1000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f( 1000, 1000, 1000);
	glEnd();
	
	/////////////////////// TOP //////////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1000, 1000, -1000);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1000, 1000,  -1000);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1000, 1000,  1000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1000, 1000, 1000);
	glEnd();
	
	/////////////////////// FLOOR //////////////////////////
	glBindTexture(GL_TEXTURE_2D, texId[5]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1000, 0., 1000);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1000, 0.,  1000);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1000, 0., -1000);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1000, 0., -1000);
	glEnd();
	
}
