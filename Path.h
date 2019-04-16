#include <iostream>
#include <fstream>

class Path {
	public:
	
	int num;
	
	float x[500] = {};
	float y[500] = {};
	float z[500] = {};
	
	Path(int numVert) {
		num = numVert;
	}
	
	void setX(string);
	
	void setY(string);
	
	void setZ(string);
};

void Path::setX(string xValues) {
	cout << xValues;
	cout << '\n';
	for (int i=0;i<num;i++) {
		x[i] = stof(xValues.substr(0, xValues.find(delim)));
		//cout << x[i];
		xValues.erase(0, xValues.find(delim) + 1);
	}
	//cout << '\n';
}

void Path::setY(string yValues) {
	for (int i=0;i<num;i++) {
		y[i] = stof(yValues.substr(0, yValues.find(delim)));
		yValues.erase(0, yValues.find(delim) + 1);
	}
}

void Path::setZ(string zValues) {
	for (int i=0;i<num;i++) {
		z[i] = stof(zValues.substr(0, zValues.find(delim)));
		zValues.erase(0, zValues.find(delim) + 1);
	}
}
