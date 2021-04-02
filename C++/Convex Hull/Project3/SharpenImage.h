#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <windows.h>

using namespace std;

#define WHITE 0
#define BLACK 1
#define OFFSET 48
#define PI 3.14159265

struct Points {
    int x, y;
};

class sharpenImage
{
    public:        
        sharpenImage();
        ~sharpenImage();
        vector<Points> buildGraph(vector<string> &);
        string strip(string, char);
        void setHeight(int);
        void setWidth(int);
        stack<Points> jarvisMarch(vector<Points>);
        pair<int, int> minMaxPoint(vector<Points>&);
        double dist(Points, Points);
        double getAngle(Points, Points);
        vector<Points> getGraph();
        double calcArea(stack<Points>);
        bool reduceImage(vector<string> &);
        void setPercent(double);
        void setHull(stack<Points>);
        void setArea(double);
        void setGraph(vector<Points>);
        void printImage(vector<string>, stack<Points>);
        bool isHull(int, int, stack<Points>);

    private:
        stack<Points> hull;
        int width, height;
        vector<Points> origonalGraph;
        double originalArea;
        double percent;
};



