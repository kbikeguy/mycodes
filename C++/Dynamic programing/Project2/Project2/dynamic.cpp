#include "Dynamic.h"


Dynamic::Dynamic()
{
}

Dynamic::~Dynamic()
{
}

void Dynamic::fillAds(int test) {

    int val;
    ifstream file(rootPath  + testFiles[test]);

    cin >> billboardLength >> numAds;

    splits.resize(numAds);
    adLengths.push_back(0);

    for(int i = 0; i < numAds; i++)
    {
        cin >> val;
        int diff = billboardLength - val;
        adLengths.push_back(val);
        price.push_back(diff);
    }
}

int Dynamic::BoardCost(int i, int currentRow)
{
    //base case
    //if (currentRow > minNumberOfRows)
    //    return INT_MAX;

    if(i == numAds) 
    {
        return 0;
    }

    if (splits[i][currentRow] != -1) 
    {
        return splits[i][currentRow];
    }

    int sum = 0;
    int minCost = INT_MAX;

    for (int z = i; z < numAds; z++) 
    {
        sum += adLengths[z];
        if (sum > billboardLength) 
        {
            break;
        }

        int retVal = cubed(billboardLength - sum) + BoardCost(z + 1, currentRow + 1);

        if (minCost > retVal) 
        {
            minCost = retVal;
            //parentNode[i][currentRow] = make_pair(z+1, currentRow+1);
        }
    }
   // dp[i][currentRow] = minCost;
    return minCost;
        
}
/*MEMOIZED-CUT-ROD(p, n)
    let r[0...n]ç be a new array
    for i = 0 to n
        r[i] = -infinity 
    return MEMOIZED-CUT-ROD-AUX(p, n, r)

MEMOIZED-CUT-ROD-AUX(p, n, r)
    if r[n] >= 0
        return r[n]ç
    if n == 0
        q = 0
    else 
        q = -infinity
        for i = 1 to n
            q = max(q, p[i] ç+ MEMOIZED-CUT-ROD-AUX(p, n - i, r))
    r[n] = q
    return q
    */

void Dynamic::setSplit(int start, int stop, int val)
{
    vector<int> vec = {start, stop, val};
    splits.push_back(vec);
}

int  Dynamic::cubed(int cube){
    //GRADING: REUSE
    if (!cube)
        return cube;

    if (costs[cube] == 0)
        costs[cube] = cube * cube * cube;

    return costs[cube];
}


void printCutRodSolution(vector<int> p, int n)
{
    // pair<vector<int>, vector<int>> rs = extendedCutRodSolution(p, n);

    while(n > 0){
        //    cout << rs.second[n] << endl;
        //   n -= rs.second[n];
    }

}

int Dynamic::memorized_cut_rod( )
{
    //vector<int> result, split;
    result.resize(numAds + 1, -1);
    splits.resize(numAds + 1);
    splits
    return memorized_cut_rod_aux(numAds);
}


int Dynamic::memorized_cut_rod_aux(int n)
{
    //already found
    if (result[n] != -1)
        return result[n];
    
    int value;

    //at the end
    if (n == numAds)
        value = 0;

    else
    {
        int rowSum = 0;
        value = INT_MAX;
        for (int i = 1; i < n; i++)
        {
            rowSum += adLengths[i];
            //over basecase
            if (rowSum > billboardLength)
                return INT_MAX;

            int temp = min(value, memorized_cut_rod_aux(n - i));

            if (temp < value)
            {
                //GRADING: UPDATE
                value = temp;
                split[n] = i;
            }
        }
    }

    result[n] = value;

    return value;
}


void Dynamic::BoardCostGreedy()
{    
    if (numAds == 1)
    {
        setSplit(1, 1, adLengths[0]);
        return;
    }
    
    int i, j; 
    int rowStart = 0;
    int rowAdSum;
    int rowStop;
    bool over = false;

    while(rowStart < numAds)
    {
        rowStop = rowStart;
        rowAdSum = 0;
        over = false;
        while(!over)
        {
            //incriment rowsum
            rowAdSum += adLengths[rowStop];

            if (rowAdSum > billboardLength)
            {
                rowAdSum -= adLengths[rowStop];
                cubed(billboardLength - rowAdSum);
                over = true;
                setSplit(rowStart + 1, rowStop , rowAdSum);
                rowStart = rowStop;
            }
            else if (rowAdSum == billboardLength || rowStop >= numAds - 1)
            {
                //cubed[0] already = 0
                over = true;
                setSplit(rowStart + 1, rowStop + 1, rowAdSum);
                rowStart = rowStop + 1;
            }
            //rowStop++;
            //incriment index and check for going over
            if(!over && ++rowStop > numAds)
                over = true;

        }
    }

    /*
    for (i = 1; i <= numAds; i++) 
    {
    int min_val = INT_MAX; 
    for (j = 0; j < i; j++)
    //GRADING: REUSE 
    min_val = min(min_val, adLengths[j] + val[i-j-1]); 


    val[i] = min_val;

    } 

    minCost = val[numAds]; 
    */
}


/*
void outer(){
int roots[5][5];

for(int i = 0; i < 5; i++)
for(int j = 0; j < 5; j++)
roots[i][j] = 0;

roots[1][4] = 3;
roots[2][4] = 3;
roots[3][4] = 3;
roots[4][4] = 4;

roots[1][3] = 3;
roots[2][3] = 3;
roots[3][3] = 3;

roots[1][2] = 1;
roots[2][2] = 2;

roots[1][1] = 1;

int node = roots[1][4];

for(int i = 1; i < 5; i++){
for(int j = 1; j < 5; j++)
cout << roots[i][j] << " ";
cout << endl;
}

cout << "Key of " << node << " is the root\n";
inner(1, node - 1, node, " left ", roots);
inner(node + 1, 4, node, " right ", roots);
}

void inner (int start, int end, int parent, string dir, int roots[5][5]){
if (start <= end)
{
int node = roots[start][end];
cout << "Key of " << node << ", is" << dir << "child of Key of " << parent << endl;
inner(start, node - 1, node, " left ", roots);
inner(node + 1, end, node, " right ", roots);
}
}



int memoized_cut_rod(vector<int> price, int n) {

    vector<int> result;

    result.resize(n+1);

    for (int i = 0; i < result.size(); i++)
        result[i] = 0;

}

int extend_cut_rod(vector<int> price, int n, vector<int> result, vector<int> split) {
    if (result[n] > 0)
        return result[n];
    int value;

    if (n == 0)
        value = 0;
    else {
        value = -9999;
        for (int i = 1; i < min(n, (int)price.size()); i++) {
            int temp = max(value, price[i] + extend_cut_rod(price, n - i, result, split));

            if (temp > value) {
                value = temp;
                split[n] = i;
            }
        }
    }

    result[n] = value;
    return value;
}
*/