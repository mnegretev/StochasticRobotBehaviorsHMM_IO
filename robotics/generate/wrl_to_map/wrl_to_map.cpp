#include "BresenhamAlgorithm.h"
#include "parserFileWRL.h"

int print_help()
{
    std::cout << "This program have this options." << std::endl;
    std::cout << "--file: The wrl file to convert a image map" << std::endl;
    std::cout << "--res: The resolution of ocupancy grid" << std::endl;
    /*prinf("--w: The width of the ocupancy grid");
    prinf("--res: The resolution of ocupancy grid");*/
    return -1;
}

std::string getFileName(const std::string& s) {

       char sep = '/';

#ifdef _WIN32
          sep = '\\';
#endif

             size_t i = s.rfind(sep, s.length());
                if (i != std::string::npos) {
                          return(s.substr(i+1, s.length() - i));
                             }

                   return("");
}

int main(int argc, char ** argv){

    std::string fileWrl;
    // float res, w, h;
    float res;
    int paramCount = 0;
    for(int i=0; i < argc; i++) 
    {
        std::string strParam(argv[i]);
        if(strParam.compare("--file") == 0){
            fileWrl = std::string(argv[++i]);
            paramCount++;
        }
        if(strParam.compare("--res") == 0){
            res = atof(argv[++i]);
            paramCount++;
        }
        /*if(strParam.compare("--w") == 0)
            w = atof(argv[++i]);
        if(strParam.compare("--h") == 0)
            h = atof(argv[++i]);*/
    }
    if(paramCount < 2)
        return print_help();
    
    std::string fileName = getFileName(fileWrl);
    size_t lastindex = fileName.find_last_of("."); 
    std::string rawname = fileName.substr(0, lastindex); 
    std::cout << fileName << std::endl;
    std::cout << rawname << std::endl;

    std::vector<biorobotics::Polygon> polygons = biorobotics::parserFile(fileWrl);
    
    float minX, maxX, minY, maxY; 

    for(int i = 0 ; i < polygons.size(); i++){
        biorobotics::Polygon polygon = polygons[i];
        for(int j = 0; j < polygon.num_vertex; j++){
            biorobotics::Vertex2 v1 = polygon.vertex[j];
            if(i == 0 and j == 0){
                minX = v1.x;
                minX = v1.x;
                minY = v1.y;
                maxY = v1.y;
            }
            else{
                if(v1.x < minX)
                    minX = v1.x;
                if(v1.y < minY)
                    minY = v1.y;
                if(v1.x > maxX)
                    maxX = v1.x;
                if(v1.y > maxY)
                    maxY = v1.y;
            }
        }
    }

    float w = (fabs(maxX) + fabs(minX)) * 2.0f;
    float h = (fabs(maxY) + fabs(minY)) * 2.0f;


    biorobotics::Vertex2 origin(-w / 2.0f,  -h / 2.0f);
    /*float w = 40, h = 40;
    biorobotics::Vertex2 origin(-20.0,  -20.0);
    float res = 0.05;*/

    int sizeOccupancyMatrix = (int) (w / res * h / res);

    signed char * occupancyMatrix = new signed char[sizeOccupancyMatrix];
    int cols = (int) (w / res);
    int rows = (int) (h / res);
    for(int i = 0; i < cols; i++)
        for(int j = 0; j < rows; j++){
            occupancyMatrix[i + j * cols] = 0;
        }

    for(int i = 0 ; i < polygons.size(); i++){
        biorobotics::Polygon polygon = polygons[i];
        for(int j = 0; j < polygon.num_vertex; j++){
            biorobotics::Vertex2 v1 = polygon.vertex[j];
            biorobotics::Vertex2 v2;
            if(j < polygon.num_vertex - 1)
                v2 = polygon.vertex[j + 1];
            else
                v2 = polygon.vertex[0];
            int cellX1 = (int)((v1.x - origin.x) / res);
            int cellY1 = (int)((v1.y - origin.y) / res);
            int cellX2 = (int)((v2.x - origin.x) / res);
            int cellY2 = (int)((v2.y - origin.y) / res);
            bresenhamAlgorithm(cellX1, cellY1, cellX2, cellY2, occupancyMatrix, cols, rows, res);
        }
    }

    std::stringstream ss;
    ss << "world/" << rawname << ".pmg";
    std::string mapdatafile = ss.str();
    FILE* out = fopen(mapdatafile.c_str(), "w");
    if (!out)
    {
        printf("Couldn't save map file to %s", mapdatafile.c_str());
        return -1;
    }

    fprintf(out, "P5\n# CREATOR: Map_generator.cpp %.3f m/pix\n%d %d\n255\n",
            res, cols, rows);
    for(unsigned int y = 0; y < rows; y++) {
        for(unsigned int x = 0; x < cols; x++) {
            unsigned int i = x + (rows - y - 1) * cols;
            if (occupancyMatrix[i] == 0) { //occ [0,0.1)
                fputc(254, out);
            } else if (occupancyMatrix[i] == +100) { //occ (0.65,1]
                fputc(000, out);
            } else { //occ [0.1,0.65]
                fputc(205, out);
            }
        }
    }

    fclose(out);

    ss.str("");
    ss << "world/" << rawname << ".yaml";
    std::string mapmetadatafile = ss.str();
    FILE* yaml = fopen(mapmetadatafile.c_str(), "w");
    fprintf(yaml, "image: %s\nresolution: %f\norigin: [%f, %f, %f]\nnegate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\n\n",
            mapdatafile.c_str(), res, origin.x, origin.y, 0.0);

    fclose(yaml);
    return 1;
}
