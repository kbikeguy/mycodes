#include "SharpenImage.h"

int main()
{
    ifstream fin;
    int height, width;
    string file, format, line;
    double percentage;
    vector<string> image;
    vector<Points> graph;
    sharpenImage obj;
   
    //get file, percent threshold
    cin >> file >> percentage;
    fin.open(file);
    
    //read in format, width, and height
    fin >> format >> width >> height;
    obj.setWidth(width);
    obj.setHeight(height);     

    //read in image from file
    while (getline(fin, line))    
        if (!line.empty())
            image.push_back(obj.strip(line, ' '));
        
    
    //set percentage
    obj.setPercent(percentage / 100.0);

    //build origonal graph
    graph = obj.buildGraph(image);
    obj.setGraph(graph);
   
    //build origonal hull
    stack<Points> hull = obj.jarvisMarch(graph);
    obj.setHull( obj.jarvisMarch(graph));

    //set starting area
    double area = obj.calcArea(hull);
    obj.setArea(area);   
   
    //delete unwanted points
    if (!obj.reduceImage(image))
        cout << "No pixels deleted.\n";

    
    return 0;
}