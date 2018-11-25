//
//  main.cpp
//  BigInteger
//
//  Created by Viacheslav Ocheretnyi on 26.09.2018.
//  Copyright © 2018 Viacheslav Ocheretnyi. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "BigInteger.h"
#include "Algorithms.h"

using namespace std;
using namespace BigIntegerLibrary;


int main() {
    srand(time(NULL));
    Algorithms solver = Algorithms();
    cout << solver.discreteLog(3, 15, 17);
    return 0;
}
