#include "utility.h"

int main(int argc, char* argv[])
{
    ifstream fin;
    FFT input;
    
    if(argc > 1)
        input = readFile(argv[1]);
        
    else
    {
        cerr << "Invalid number of command arguments\n";
        return 1;
    }
    //check if file was read
    if (!input.size())
        return 1;    
 
    //begin FFT
    input = recursiveFFT(input);  

    //set the precision to 2 decimal places and print results
    cout << fixed << setprecision(2);
    if (input.size() < 9)
        for (auto val : input)
            cout << "(" << val.real() << ", " << val.imag() << ")\n";
    else
        print_top_polynomial(input);

    return 0;
}