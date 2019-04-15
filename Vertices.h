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

	void print(void);
	
	void printValues(int value);
};

void Vertices::setX(string xValues) {
	cout << xValues;
	cout << '\n';
	for (int i=0;i<num;i++) {
		Vertices::x[i] = stof(xValues.substr(0, xValues.find(delim)));
		xValues.erase(0, xValues.find(delim) + 1);
	}
}

void Vertices::setY(string yValues) {
	for (int i=0;i<num;i++) {
		Vertices::y[i] = stof(yValues.substr(0, yValues.find(delim)));
		yValues.erase(0, yValues.find(delim) + 1);
	}
}

void Vertices::setZ(string zValues) {
	for (int i=0;i<num;i++) {
		Vertices::z[i] = stof(zValues.substr(0, zValues.find(delim)));
		zValues.erase(0, zValues.find(delim) + 1);
	}
}

void Vertices::print(void) {
	Vertices::printValues(0);
	Vertices::printValues(1);
	Vertices::printValues(2);
}

void Vertices::printValues(int value) {
	for (int i=0;i<num;i++) {
		if (value==0) {
			cout << Vertices::x[i];
		} else if (value==1) {
			cout << Vertices::y[i];
		} else if (value==2) {
			cout << Vertices::z[i];
		}
	}
	cout << '\n';
}
