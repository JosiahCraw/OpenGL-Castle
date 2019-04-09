#include <GL/glut.h>
#include "loadTGA.h"
#include "loadBMP.h"
#include <iostream>
#include <fstream>
using namespace std;

#define GL_CLAMP_TO_EDGE 0x812F   //To get rid of seams between textures

int numOfTextures;

struct Texture {
	string name;
	int type;
	int param;
};


void loadTexFromFile(Texture textures[]) {
	string texInfo;
	ifstream texFile;
	const char* delim = ",";
	texFile.open("cfg/textures.cfg");
	int i = 0;
	while (1) {
		string name;
		getline(texFile, texInfo);
		name = texInfo.substr(0, texInfo.find(delim));
		if (name == "end") {
			return;
		}
		textures[i].name = name;
		texInfo.erase(0, texInfo.find(delim) + 1);
		textures[i].type = stoi(texInfo.substr(0, texInfo.find(delim)));
		texInfo.erase(0, texInfo.find(delim) + 1);
		textures[i].param = stoi(texInfo.substr(0, texInfo.find(delim)));
		i++;
	}
	
}


void CompNumOfTex(void) {
	string numTex;
	ifstream numFile;
	const char* delim = ",";
	numFile.open("cfg/numTex.cfg");
	getline(numFile, numTex);
	int num = stoi(numTex.substr(0, numTex.find(delim)));
	numOfTextures = num;
}


const int numOfTex(void) {
	return numOfTextures;
}


void loadTextures(GLuint texId[]) 
{
	Texture textures[numOfTex()];
	loadTexFromFile(textures);
	int num = numOfTex();
	for (int i=0; i<num; i++) {
		glBindTexture(GL_TEXTURE_2D, texId[i]);
		cout << textures[i].name;
		cout << '\n';
		if (textures[i].type == 0) {
			loadTGA(textures[i].name);
		} else {
			loadBMP(textures[i].name);
		}
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		if (textures[i].param == 1) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		} else if (textures[i].param == 2) {
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		} else if (textures[i].param == 3) {
			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}		
	}	
	glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
}
