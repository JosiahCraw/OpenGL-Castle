#include <iostream>
#include <fstream>

//const char* delim = ",";

class ExtrudeVerts {
	public:
	
	int num;
	
	float x[100] = {};
	float y[100] = {};
	float z[100] = {};
	
	ExtrudeVerts(int numVert) {
		num = numVert;
	}
	
	void setX(string);
	
	void setY(string);
	
	void setZ(string);

	void print(void);
	
	void printValues(int value);
};

void ExtrudeVerts::setX(string xValues) {
	cout << xValues;
	cout << '\n';
	for (int i=0;i<num;i++) {
		x[i] = stof(xValues.substr(0, xValues.find(delim)));
		//cout << x[i];
		xValues.erase(0, xValues.find(delim) + 1);
	}
	//cout << '\n';
}

void ExtrudeVerts::setY(string yValues) {
	for (int i=0;i<num;i++) {
		y[i] = stof(yValues.substr(0, yValues.find(delim)));
		yValues.erase(0, yValues.find(delim) + 1);
	}
}

void ExtrudeVerts::setZ(string zValues) {
	for (int i=0;i<num;i++) {
		z[i] = stof(zValues.substr(0, zValues.find(delim)));
		zValues.erase(0, zValues.find(delim) + 1);
	}
}

void ExtrudeVerts::print(void) {
	ExtrudeVerts::printValues(0);
	ExtrudeVerts::printValues(1);
	ExtrudeVerts::printValues(2);
}

void ExtrudeVerts::printValues(int value) {
	for (int i=0;i<num;i++) {
		if (value==0) {
			cout << x[i];
		} else if (value==1) {
			cout << y[i];
		} else if (value==2) {
			cout << z[i];
		}
	}
}

