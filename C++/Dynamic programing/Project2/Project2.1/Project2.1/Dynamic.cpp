#include "Dynamic.h"


Dynamic::Dynamic()
{
}

Dynamic::~Dynamic()
{
}

void Dynamic::fillAds() {

    int val;

    cin >> billboardLength >> numAds;

    cubedVals.resize(billboardLength, 0);

    for (int i = 0; i < numAds; i++)
    {
        cin >> val;
        adLengths.push_back(val);
    }

}



void Dynamic::setSplit(int start, int stop, int adTotal)
{
    vector<int> vec = {start, stop, adTotal};
    splits.push_back(vec);
}


int  Dynamic::cubed(int cube){
    //GRADING: REUSE
    if (cube && !cubedVals[cube])
        cubedVals[cube] = cube * cube * cube;

    return cubedVals[cube];
}



void Dynamic::BoardCost()
{
    if (numAds == 1)
    {
        setSplit(1, 1, adLengths[0]);
        return;
    }

    int rowStart = 0;
    int rowAdSum;
    int rowStop;
    bool over = false;

    while (rowStart < numAds)
    {
        rowStop = rowStart;
        rowAdSum = 0;
        over = false;
        while (!over)
        {
            //incriment rowsum
            rowAdSum += adLengths[rowStop];

            if (rowAdSum > billboardLength)
            {
                //GRADING: UPDATE
                rowAdSum -= adLengths[rowStop];
                costs.push_back(cubed(billboardLength - rowAdSum));
                over = true;
                //GRADING: UPDATE
                setSplit(rowStart + 1, rowStop, rowAdSum);
                rowStart = rowStop;
            }
            else if (rowAdSum == billboardLength || rowStop >= numAds - 1)
            {
                //cubed[0] already = 0
                over = true;
                //Grading: UPDATE
                setSplit(rowStart + 1, rowStop + 1, rowAdSum);
                rowStart = rowStop + 1;
            }

            //incriment index and check for going over
            if (!over && ++rowStop > numAds)
                over = true;

        }
    }
}

void Dynamic::print()
{
    cout <<"\nBoard cost: " << accumulate(costs.begin(), costs.end(), 0) << endl;
   
    for(auto vec : splits)
    {
        cout << "(" << vec[0] << ", " << vec[1] << ") --> " << vec[2] << endl;

    }
    cout << endl;
}