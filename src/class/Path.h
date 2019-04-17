#include <iostream>
#include <fstream>

class Path {
	public:
	
	int num;
	int numAngles;
	
	float x[500] = {};
	float y[500] = {};
	float z[500] = {};
	
	int angle[20][2] = {};
	
	int angleIndex = 0;
	
	Path(int numVert) {
		num = numVert;
	}
	
	void setX(string);
	
	void setY(string);
	
	void setZ(string);
	
	void setCorners(string);
	
	int checkCornering(int index);
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

void Path::setCorners(string cornerValues) {
	numAngles = 0;
	
	if (cornerValues == "NULL,") {
		return;
	}
	
	angleIndex = 0;
	
	cout << cornerValues;
	
	while (1) {
		if (cornerValues=="END,") {
			break;
		}
		angle[angleIndex][0] = stoi(cornerValues.substr(0, cornerValues.find(delim)));
		cornerValues.erase(0, cornerValues.find(delim) + 1);
		angle[angleIndex][1] = stoi(cornerValues.substr(0, cornerValues.find(delim)));
		cornerValues.erase(0, cornerValues.find(delim) + 1);
		
		angleIndex++;
	}
	numAngles = angleIndex;
}

int Path::checkCornering(int index) {
	for (int i=0; i<num; i++) {
		if (angle[i][0] >= index) {
			return angle[i][1];
		}
	}
	return 0;
}
