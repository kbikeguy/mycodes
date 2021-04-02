#include "Dynamic.h"


int main() {
    Dynamic obj;
    int i;
    int cost;
    

    //get all the data
    cout << "Enter test num: ";
    cin >> i;

    obj.fillAds(i);
    obj.costs.resize(obj.billboardLength + 1, 0);


    //dynamic call
    cost = obj.memorized_cut_rod();

    //display results
    cout << "test " << i << "\nBoard cost: " << cost << endl;
    int j = 0;
    for(auto vec : obj.splits)
    {
        cout << "(" << vec[0] << ", " << vec[1] << ") --> " << obj.result[j] << endl;
        j++;
    }
    cout << endl;

    return 0;
}