const char* delim = ",";

class Vertices {
	public:
	
	int num;
	
	int x[100] = {};
	int y[100] = {};
	int z[100] = {};
	
	Vertices(int numVert) {
		num = numVert;
	}
	
	void setX(string xValues) {
		for (int i=0;i<num;i++) {
			x[i] = stoi(xValues.substr(0, xValues.find(delim)));
			xValues.erase(0, xValues.find(delim) + 1);
		}
	}
	
	void setY(string yValues) {
		for (int i=0;i<num;i++) {
			y[i] = stoi(yValues.substr(0, yValues.find(delim)));
			yValues.erase(0, yValues.find(delim) + 1);
		}
	}
	
	void setZ(string zValues) {
		for (int i=0;i<num;i++) {
			z[i] = stoi(zValues.substr(0, zValues.find(delim)));
			zValues.erase(0, zValues.find(delim) + 1);
		}
	}
	
	
};
