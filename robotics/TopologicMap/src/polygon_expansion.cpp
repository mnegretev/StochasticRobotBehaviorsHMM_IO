#include "definition.h"
#include "parserFileWRL.h"
#include "utilMap.h"

using namespace biorobotics;

int main(int argc, char* argv[]) {

	if (argc < 2) {
		std::cout
			<< "Execute: ./polygon_expansion -f filesWRL/random_1.wrl -o topological_maps/random_11 -r .01"
			<< std::endl;
		return -1;
	}

	std::string fileIn = "";
	std::string fileGrownOut = "";
	std::string fileTopOut = "";
	std::string strParam(argv[1]);
	float ratio;

	for (int i = 0; i < argc; i++) {
		std::string strParam(argv[i]);
		if (strParam.compare("-f") == 0)
			fileIn = argv[++i];
		if (strParam.compare("-o") == 0)
			fileGrownOut = argv[++i];
		if (strParam.compare("-r") == 0)
			ratio = atof(argv[++i]) * 10.0;
	}

	if (fileGrownOut.compare("") == 0) {
		std::stringstream ss;
		std::string outTemp;
		outTemp = fileIn.c_str();
		std::size_t pos = outTemp.find(".wrl");
		outTemp = outTemp.substr(0, pos);
		ss << outTemp << "_exp.wrl";
		fileGrownOut = ss.str();
		ss.str("");
		ss << outTemp.c_str() << ".top";
		fileTopOut = ss.str();
	} else {
		std::string outTemp = fileGrownOut;
		std::stringstream ss;
		ss << outTemp << "_exp.wrl";
		fileGrownOut = ss.str();
		ss.str("");
		ss << outTemp << ".top";
		fileTopOut = ss.str();
	}

	std::ofstream fileSave1;
	fileSave1.open(fileGrownOut.c_str());

	float w, h;
	std::vector<Polygon> polygons = parserFile(fileIn, w, h);
	std::vector<Polygon> grownPoly = grownPolygons(polygons, ratio);

	if (fileSave1.is_open()) {
		int numObstacle = 1;
		int numWalls = 1;
		fileSave1 << ";******************************************************************************" << std::endl;
		fileSave1 << ";* File:" << fileGrownOut << "                                                         *" << std::endl;
		fileSave1 << ";*          world. These areas are derivated from the objects in the          *" << std::endl;
		fileSave1 << ";*          world.                                                            *" << std::endl;
		fileSave1 << ";******************************************************************************" << std::endl;
		fileSave1 << std::endl;
		fileSave1 << "( dimensions random " << (float) w/10.0 << " " << (float) h/10.0 << " )" << std::endl;	
		fileSave1 << std::endl;
		for (int i = 0; i < grownPoly.size(); i++) {
			if(grownPoly[i].objectType == OBSTACLE)
				fileSave1 << "( polygon obstacle obs_" << numObstacle++;
			else if(grownPoly[i].objectType == WALL)
				fileSave1 << "( polygon wall wall_" << numWalls++;
			Polygon poly = grownPoly[i];
			for (int j = 0; j < poly.num_vertex; j++) {
				fileSave1 << " " << poly.vertex[j].x / 10.0 << " "
					<< poly.vertex[j].y / 10.0;
			}
			fileSave1 << " )" << std::endl;
		}
	}
	fileSave1.close();

	bool ** adyacencies;
	int sizeAdyacencies = 0;
	adyacencies = computeMapTopologic(polygons, grownPoly, ratio, &sizeAdyacencies);

	Vertex2 * vertexMap;
	int sizeVertexMap = 0;
	vertexMap = createVertexPointerFromPolygons(&grownPoly[0],
			grownPoly.size(), &sizeVertexMap);

	std::ofstream fileSave2;
	fileSave2.open(fileTopOut.c_str());

	if (fileSave2.is_open())
		fileSave2 << "( num nodes " << sizeAdyacencies << " )" << std::endl;

	if (fileSave2.is_open()) {
		fileSave2 << "( name nodes ";
		for (int i = 0; i < sizeAdyacencies; i++) {
			fileSave2 << i << " ";
		}
		fileSave2 << ")" << std::endl;
	}

	if (fileSave2.is_open()) {
		for (int i = 0; i < sizeAdyacencies; i++) {
			Vertex2 vertex1(vertexMap[i].x / 10.0,
					vertexMap[i].y / 10.0);
			fileSave2 << "( node " << i << " " << vertex1.x << " " << vertex1.y
				<< " )" << std::endl;
		}
	}

	for (int i = 0; i < sizeAdyacencies; i++) {
		for (int j = 0; j < sizeAdyacencies; j++) {
			if (adyacencies[i][j]) {
				Vertex2 vertex1(vertexMap[i].x / 10.0,
						vertexMap[i].y / 10.0);
				Vertex2 vertex2(vertexMap[j].x / 10.0,
						vertexMap[j].y / 10.0);
				fileSave2 << "( connection " << i << " " << j << " "
					<< vertex1.sub(vertex2).norm() << " )" << std::endl;
			}
		}
	}

	fileSave2.close();

	return 1;
}
