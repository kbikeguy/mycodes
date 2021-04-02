#include "utility.h"


//comparator struct to sort using values from different, but given, vector
struct Comp {
    Comp(const vector<double> &v) : sortOn(v) {}

    bool operator()(int a, int b)
    {
        return sortOn[a] > sortOn[b];
    }

    const vector<double> &sortOn;
};

/*
*/
void print_top_polynomial(vector <complex<double>> &a)
{
    //calculate the spectral power
    vector<double> power(a.size());
    //TODO
    for (unsigned int i = 0; i < a.size(); i++)
        power[i] = a[i].real() * a[i].real() + a[i].imag() * a[i].imag();



    //make a vector of indices
    vector<int> indices;
    indices.resize(power.size());
    for (unsigned int i = 0; i < power.size(); ++i)
        indices[i] = i;

    //sort index vector, but using the power values
    sort(indices.begin(), indices.end(), Comp(power));

    //print top 7
    for (int i = 0; i < 7; i++)
    {
        string index = to_string(indices[i]);
        index.append(11 - index.size(), ' ');
        cout << index << "(" << a[indices[i]].real() << ", " << a[indices[i]].imag() << ")\n";
    }
}

FFT readFile(char file[])
{

    FFT input;
    int coefficient;

    //open and check file
    ifstream fin(file);
    if (!fin.is_open())
    {
        cerr << "File not found\n";
        return input;
    }

    //fill vector
    while (fin >> coefficient)
        input.push_back(coefficient);

    fin.close();

    //reverse the list
    reverse(input.begin(), input.end());

    //pad with 0s while length is not a power of 2
    int size = input.size();
    if (ceil(log2(size)) != floor(log2(size)))
    {
        int power[] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536};
        
        for (int i = 1; i < 16; i++)
            if (size < power[i])
            {
                input.resize(power[i], 0);
                return input;
            }
        
    }
       
    return input;
}

/******************************************************************************
This is my implimentation of the FFT using the algorythm you presented in the 
lecture. I modified it based on an algothm on
https://www.geeksforgeeks.org/fast-fourier-transformation-poynomial-multiplication/
11/10/2020 where i calculate w_n useing cos and sin for extra speed
******************************************************************************/
FFT recursiveFFT(FFT &a)
{
     int n = a.size();

    //base case
    if (n & 0b0001)
        return a;
    
   //set up vars
    int limit = n >> 1;
    FFT y(n), E(limit), D(limit);
    double constant = PI2 / n;

    //split into odd and even
    for (int i = 0; i < limit; i++)
    {
        E[i] = a[i << 1];
        D[i] = a[1 + (i << 1)];
    }

    //recursive calls
    FFT evenResult = recursiveFFT(E);
    FFT oddResult = recursiveFFT(D);
    
    //calculate results with a mirror approach for speed    
    for (int i = 0; i < limit; i++)
    {
        //the spacing between roots of unity in this set(e^(2*pi*i/n))
        double theta = constant * i;
        complex<double> w(cos(theta), sin(theta));
        y[i] = evenResult[i] + w * oddResult[i];
        y[i + limit] = evenResult[i] - w * oddResult[i];
    }

    return y;
}
