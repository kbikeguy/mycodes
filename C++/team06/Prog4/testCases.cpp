#define CATCH_CONFIG_MAIN
#include "..\catch.hpp"
#include <iostream>
#include <string>
#include <sstream>

#include "utilities.h"

using namespace std;


TEST_CASE("cmln handling")
{
    char **argv = new (nothrow) char*[5];
    for (int i = 0; i < 5; i++)
        argv[i] = new (nothrow) char[30];
    strcpy_s(argv[0], 29, "prog4.exe");
    strcpy_s(argv[1], 29, "data.sim");
    strcpy_s(argv[2], 29, "40");
   
    //checks argc
    REQUIRE(check_cmln(0, argv) == false);
    REQUIRE(check_cmln(3, argv) == true);
    REQUIRE(check_cmln(4, argv) == false);

    //checks argv, belt length
    REQUIRE(check_cmln(3, argv) == true);
    strcpy_s(argv[2], 29, "a");
    REQUIRE(check_cmln(3, argv) == false);
    strcpy_s(argv[2], 29, "1a");
    REQUIRE(check_cmln(3, argv) == false);
    strcpy_s(argv[2], 29, "a1");
    REQUIRE(check_cmln(3, argv) == false);
}

TEST_CASE("sortBelt")
{
    //checks that it maintains the ordering when in correct order
    int beltWidths[4] = { 10, 15, 20 };
    char beltNames[4] = { 'A', 'B', 'C' };

    sortBelt(beltWidths, beltNames, 3);
    REQUIRE(beltWidths[0] == 10);
    REQUIRE(beltWidths[1] == 15);
    REQUIRE(beltWidths[2] == 20);
    REQUIRE(beltNames[0] == 'A');
    REQUIRE(beltNames[1] == 'B');
    REQUIRE(beltNames[2] == 'C');

    //checks that it switches the first two widths and names
    beltWidths[0] = 15;
    beltWidths[1] = 10;
    beltWidths[2] = 20;

    beltNames[0] = 'A';
    beltNames[1] = 'B';
    beltNames[2] = 'C';

    sortBelt(beltWidths, beltNames, 3);
    REQUIRE(beltWidths[0] == 10);
    REQUIRE(beltWidths[1] == 15);
    REQUIRE(beltWidths[2] == 20);
    REQUIRE(beltNames[0] == 'B');
    REQUIRE(beltNames[1] == 'A');
    REQUIRE(beltNames[2] == 'C');

    //checks that it switches the second two widths and names
    beltWidths[0] = 10;
    beltWidths[1] = 20;
    beltWidths[2] = 15;

    beltNames[0] = 'A';
    beltNames[1] = 'B';
    beltNames[2] = 'C';

    sortBelt(beltWidths, beltNames, 3);
    REQUIRE(beltWidths[0] == 10);
    REQUIRE(beltWidths[1] == 15);
    REQUIRE(beltWidths[2] == 20);
    REQUIRE(beltNames[0] == 'A');
    REQUIRE(beltNames[1] == 'C');
    REQUIRE(beltNames[2] == 'B');

    //checks that it switches the first and last width and name
    beltWidths[0] = 20;
    beltWidths[1] = 15;
    beltWidths[2] = 10;

    beltNames[0] = 'A';
    beltNames[1] = 'B';
    beltNames[2] = 'C';

    sortBelt(beltWidths, beltNames, 3);
    REQUIRE(beltWidths[0] == 10);
    REQUIRE(beltWidths[1] == 15);
    REQUIRE(beltWidths[2] == 20);
    REQUIRE(beltNames[0] == 'C');
    REQUIRE(beltNames[1] == 'B');
    REQUIRE(beltNames[2] == 'A');
}

TEST_CASE("rotateBox")
{
    box *package = new (nothrow) box;
    package->dim1 = 1;
    package->dim2 = 2;
    package->dim3 = 3;

    //conserves order of ordered package
    rotateBox(*package);
    REQUIRE(package->dim1 == 1);
    REQUIRE(package->dim2 == 2);
    REQUIRE(package->dim3 == 3);

    //switches first two dimensions
    package->dim1 = 2;
    package->dim2 = 1;
    package->dim3 = 3;
    rotateBox(*package);
    REQUIRE(package->dim1 == 1);
    REQUIRE(package->dim2 == 2);
    REQUIRE(package->dim3 == 3);

    //switches second two dimensions
    package->dim1 = 1;
    package->dim2 = 3;
    package->dim3 = 2;
    rotateBox(*package);
    REQUIRE(package->dim1 == 1);
    REQUIRE(package->dim2 == 2);
    REQUIRE(package->dim3 == 3);

    //switches first and last dimensions
    package->dim1 = 3;
    package->dim2 = 2;
    package->dim3 = 1;
    rotateBox(*package);
    REQUIRE(package->dim1 == 1);
    REQUIRE(package->dim2 == 2);
    REQUIRE(package->dim3 == 3);
}

