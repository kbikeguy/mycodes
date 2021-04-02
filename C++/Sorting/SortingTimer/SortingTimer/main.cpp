#include "Utility.h"

void main() {
    char choice = 'c';
    vector<int> input, save;

    while (toupper(choice) != 'Q') {
        cout << "\nEnter T to run time tests\n"
            << "Enter I to accept user input and perform an insertion sort\n"
            << "Enter M to accept user input and perform a merge sort\n"
            << "Enter Q to quit" << endl;

        cout << "Choice: ";
        cin >> choice;

        if (toupper(choice) == 'T') {
            //TODO run time tests
            ofstream csvFile;
            csvFile.open("times.csv");
            timeTests(csvFile);
            csvFile.close();
        }
        else if (toupper(choice) == 'I') {
            cout << "Input ( # # # ... -999): ";
            //TODO get user input, sort it, and display the results
            input = getInput();
            insert(input);
            print(input);
        }
        else if (toupper(choice) == 'M') {
            cout << "Input ( # # # ... -999): ";
            //TODO get user input, sort it, and display the results
            input = save = getInput();
            mergeSort(input, 0, input.size() - 1);
            print(input);
        }
    }

    return;

}