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
    BigInteger a("545344234");
//    a = 10000;
//    cin >> a;
    Algorithms solver = Algorithms();
    vector<BigInteger> res = solver.factorization(a);
    for (BigInteger x: res) {
        cout << x << " ";
    }
    return 0;
}
