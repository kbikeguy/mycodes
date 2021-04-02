#include "SharpenImage.h"

sharpenImage::sharpenImage()
{
}

sharpenImage::~sharpenImage()
{
}

vector<Points> sharpenImage::buildGraph(vector<string> & image)
{
    vector<Points> graph;
    Points point;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            if (image[i][j] == '1')
            {
                point.x = j;
                point.y = i;
                graph.push_back(point);                  
            }
    }

    return graph;
}

void sharpenImage::setHeight(int h)
{
    height = h;
}

void sharpenImage::setWidth(int w)
{
    width = w;
}

stack<Points> sharpenImage::jarvisMarch(vector<Points> V)
{
    //might be better to make copy here
    stack<Points> hull;
    pair<int, int> minMax = minMaxPoint(V);    //set lowest point in graph
    Points bottom = V[minMax.first];
    Points top = V[minMax.second];
    hull.push(bottom);
    V.erase(V.begin() + minMax.first);
    Points next = { -1, -1 };

    //build the left side
    while (top.y != hull.top().y || top.x != hull.top().x)
    {
        int index = 0;

        double min = acos(-1) * 180.0 / PI;
        //double min = getAngle(V[0], hull.top());
        next = V[0];
        for (unsigned int i = 0; i < V.size(); i++)
        {
            //if not below current point
            if (V[i].y <= hull.top().y)
            {
                double angle = getAngle(V[i], hull.top()); //what gets passed in
                bool collinear = abs(angle - min) <= 0.00001;
                bool add = false;
                if (collinear) {
                    double newOne = dist(V[i], hull.top());
                    double orig = dist(next, hull.top());
                    add = collinear && orig < newOne;
                }
                double diff = angle - min;
                if ( (!collinear && diff <= 0) || add)
                {
                    min = angle;
                    next = V[i];
                    index = i;
                }
            }
        }
        hull.push(next);
        V.erase(V.begin() + index);
    }


    //readd ending point
    V.push_back(bottom);
    //build the right side, what needs to change?
    while (bottom.y != hull.top().y || bottom.x != hull.top().x)
    {
        int index = 0;
        double min = (acos(1) * 180.0 / PI) + 360; // would this need to be 0?
        //double min = 360 - getAngle(V[0], hull.top());
        Points next = V[0];
        for (unsigned int i = 0; i < V.size(); i++) //
        {
            //if not above current point
            if (V[i].y >= hull.top().y)
            {
                double angle = 360 - getAngle(V[i], hull.top()); //what gets passed in
                bool collinear = abs(angle - min) <= 0.00001;
                bool add = false;
                if (collinear) {
                    double newOne = dist(V[i], hull.top());
                    double orig = dist(next, hull.top());
                    add = collinear && orig < newOne;
                }

                if ( (!collinear && angle - min <= 0) || add)
                {
                    min = angle;
                    next = V[i];
                    index = i;
                }
               
            }
        }
        hull.push(next);
        V.erase(V.begin() + index);
    }

    hull.pop();

    return hull;
}

pair <int, int> sharpenImage::minMaxPoint(vector<Points> &v)
{
    Points bottom = v[0];
    Points top = bottom;
    int up = 0, down = 0;

    for (unsigned int i = 1; i < v.size(); i++)
    {       
        //find bottom
        if (v[i].y > bottom.y)
        {
            bottom = v[i];
            down = i;
        }
        else if (v[i].y == bottom.y && v[i].x < bottom.x)
        {
            bottom = v[i];
            down = i;
        }

        //find top
        if (v[i].y < top.y)
        {
            top = v[i];
            up = i;
        }
        else if (top.y == v[i].y && v[i].x > top.x)
        {
            bottom = v[i];
            up = i;
        }
    }

    return make_pair(down, up);
}

double sharpenImage::dist(Points p1, Points p2)
{
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double sharpenImage::getAngle(Points newPoint, Points base)
{
    //set up psudo h-line point
    Points p3 = { width, base.y };

    //build vectors
    Points vec1 = { newPoint.x - base.x, newPoint.y - base.y };
    Points vec2 = { p3.x - base.x, p3.y - base.y };

    //calc dot product
    double dotProd = (vec1.x * vec2.x) + (vec1.y * vec2.y);

    //calc magnitudes
    double vec1Mag = sqrt((vec1.x * vec1.x) + (vec1.y * vec1.y));
    double vec2Mag = sqrt((vec2.x * vec2.x) + (vec2.y * vec2.y));
    double mags = vec1Mag * vec2Mag;

    //calc angle
    double angle = acos(dotProd / mags) * 180.0 / PI;

    return angle;
}



vector<Points> sharpenImage::getGraph()
{
    return origonalGraph;
}

double sharpenImage::calcArea(stack<Points> hull)
{
    //check for line
    if (hull.size() < 3)
        return DBL_MAX;

    double area = 0.0;

    vector<Points> v;
    v.resize(hull.size());

    for (int i = hull.size() - 1; hull.size(); i--)
    {
        v[i] = hull.top();
        hull.pop();
    }

    Points start = v[0];


    for (unsigned int i = 1; i < v.size() - 1; i++)
    {
        double sideA = dist(start, v[i]);
        double sideB = dist(v[i], v[i + 1]);
        double sideC = dist(start, v[i + 1]);
        double semiper = (sideA + sideB + sideC) / 2.0;
        area += sqrt(semiper*(semiper - sideA) *(semiper - sideB) * (semiper - sideC));
    }

    return area;
}

bool sharpenImage::reduceImage(vector<string>& image)
{
    bool despecled = false;
    bool done = false;
    vector<Points> toRemove;
    vector<vector<Points>> tempNewGraph;
    vector<stack<Points>> tempNewHull;
    vector<double> tempNewArea;
    vector<Points> newGraph;
    stack<Points> newHull;
    double newArea;
    Points remove;
    int missing = std::string::npos;

  

    while (!done)
    {
        done = true;
        double currBestPercent = -1;
        for (int i = 0; hull.size() > 2 && i < height; i++)
        {
            //if no 1s in this row, dont search it
            int start = image[i].find('1');
            if (start != missing)
            {
                for (int j = start; j != missing; j = image[i].find('1', j + 1))
                {
                    if (image[i][j] == '1')
                    {
                        //delete the value
                        image[i][j] = '0';

                        //build the new hull
                        vector<Points> despeckledGraph = buildGraph(image);
                        stack<Points> despeckledHull = jarvisMarch(despeckledGraph);
                        double despeckledArea = calcArea(despeckledHull);
                        double reduced = (1 - (despeckledArea / originalArea));

                        //put the pixel back
                        image[i][j] = '1';
                        double diff = reduced - currBestPercent;

                        //test new area against old area
                        if (percent <= reduced && diff > 0.0001)
                        {
                            done = false;
                            currBestPercent = reduced;
                            newArea = despeckledArea;
                            newGraph = despeckledGraph;
                            newHull = despeckledHull;
                            remove = { j, i };                            
                        }                        
                    }
                }
            }
            
        }
        //check if something should be removed
        if (!done)
        {
            despecled = true;
            origonalGraph = newGraph;
            hull = newHull;
            originalArea = newArea;
            cout << "Delete pixel at (" << remove.y << ", " << remove.x << ")\n";
            image[remove.y][remove.x] = '0';
        }
    }

    return despecled;
}

void sharpenImage::setPercent(double p)
{
    percent = p;
}

void sharpenImage::setHull(stack<Points> h)
{
    hull = h;
}

void sharpenImage::setArea(double area)
{
    
    originalArea = area;
}

void sharpenImage::setGraph(vector<Points> graph)
{
    origonalGraph = graph;
}

string sharpenImage::strip(string word, char letter)
{
    string str = "";

    for (auto x : word)
    {
        if (x != letter)
            str += x;

    }

    return str;
}

void sharpenImage::printImage(vector<string> image, stack<Points> Hull)
{
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (unsigned int i = 0; i < image.size(); i++)
    {
        for (unsigned int j = 0; j < image[0].size(); j++)
        {
            if (image[i][j] == '1')
            {
                if (isHull(j, i, Hull))
                {
                    SetConsoleTextAttribute(hConsole, 13);
                    cout << image[i][j];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else
                    cout << image[i][j];
            }
            else
                cout << " ";
        }

        cout << endl;
    }


}

bool sharpenImage::isHull(int x, int y, stack<Points> p)
{

    while (p.size())
    {
        if (p.top().x == x && p.top().y == y)
            return true;
        p.pop();
    }

    return false;
}
