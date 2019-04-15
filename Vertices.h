#include <iostream>
#include <fstream>
const char* delim = ",";

class Vertices {
	public:
	
	int num;
	
	float x[100] = {};
	float y[100] = {};
	float z[100] = {};
	
	Vertices(int numVert) {
		num = numVert;
	}
	
	void setX(string);
	
	void setY(string);
	
	void setZ(string);
};

void Vertices::setX(string xValues) {
	cout << xValues;
	cout << '\n';
	for (int i=0;i<num;i++) {
		x[i] = stof(xValues.substr(0, xValues.find(delim)));
		xValues.erase(0, xValues.find(delim) + 1);
	}
}

void Vertices::setY(string yValues) {
	for (int i=0;i<num;i++) {
		y[i] = stof(yValues.substr(0, yValues.find(delim)));
		yValues.erase(0, yValues.find(delim) + 1);
	}
}

void Vertices::setZ(string zValues) {
	for (int i=0;i<num;i++) {
		z[i] = stof(zValues.substr(0, zValues.find(delim)));
		zValues.erase(0, zValues.find(delim) + 1);
	}
}
