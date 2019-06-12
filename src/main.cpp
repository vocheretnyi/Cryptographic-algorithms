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
#include "EllypticPoint.h"
#include "ElGamalEncryption.h"

using namespace std;
using namespace BigIntegerLibrary;

const string menu[] = {
        "Factorization (Pollard-Rho algorithm)",
        "Discrete log (baby-step-giant-step algorithm)",
        "Euler and Mobius functions",
        "Legendre and Jacobi symbols",
        "Discrete square root (Cipolla's algorithm)",
        "Is prime (Miller-Rabin algorithm)",
        //""
};
Algorithms solver;

void testDiscreteLog() {
    for (int i = 0; i < 5; ++i) {
        BigInteger a = solver.random(10, 10000);
        BigInteger x = solver.random(10, 10000);
        BigInteger p = solver.random(10, 10000);
        while (gcd(a, p) != 1) {
            p = solver.random(10, 10000);
        }
        a %= p;

        BigInteger b = powm(a, x, p);

        cout << a << "^x"  << "(mod " << p << ") = " << b << "\n";
        x = solver.discreteLog(a, b, p);
        cout << "x = " << x << "\n";
        cout << "Check: " << a << " ^ " << x << " (mod " << p << ") =	 " << powm(a, x, p) << "\n";
    }
}

/*
 test:
 1. what you want
 2. 3^x = 13(mod 17) (answer 4)
    3^x = 1452(mod 1999) (answer 789)
 3.
 4.
 5. n = 10, p = 13, answer = 6 and 7
    n = 331575, p = 1000003, answer = 144161 and 855842
 6. n = 252097800623 (prime), 252097800625(not prime)

 */

int main() {
    srand(time(NULL));
    solver = Algorithms();
    int menu_len = sizeof(menu) / sizeof(string);
    int t;

    while (true) {
        cout << "Choose variant:\n";
        for (int i = 1; i <= menu_len; ++i) {
            cout << i << ". " << menu[i - 1] << "\n";
        }
        cin >> t;
        if (t == 1) {
            BigInteger n;
            cin >> n;
            auto res = solver.factorization(n);
            cout << "Factorization is:\n";
            for (auto x: res) {
                cout << x << ' ';
            }
            cout << "\n";
        } else if (t == 2) {
            cout << "Enter a, b, m (a^x = b (mod m))\n";
            BigInteger a, b, m;
            cin >> a >> b >> m;
            cout << "x = " << solver.discreteLog(a, b, m) << "\n";
//            testDiscreteLog();
        } else if (t == 3) {
            BigInteger n;
            cin >> n;
            cout << "Euler and Mobius functions: " << solver.eulerFunction(n) << ' ' << solver.mobiusFunction(n) << "\n";
        } else if (t == 4) {
            cout << "Enter n and p for (n|p)\n";
            BigInteger n, p;
            cin >> n >> p;
            cout << "Legendre and Jacobi functions: " << solver.legendreSymbol(n, p) << ' ' << solver.jacobiSymbol(n, p) << "\n";
        } else if (t == 5) {
            cout << "Enter p and n, for (x^2 = n (mod p))\n";
            BigInteger n, p;
            cin >> p >> n;
            auto res = solver.discreteSquareRoot(p, n);
            cout << "solutions: " << res.first << ' ' << res.second << "\n";
        } else if (t == 6) {
            BigInteger n;
            cin >> n;
            cout << "Isprime: " << solver.isPrime(n) << "\n";
        } else if (t == 7) {
            ElGamalEncryption elGamalEncryption = ElGamalEncryption();
            auto res = elGamalEncryption.encode(EllypticPoint(24, 26));
            auto point = elGamalEncryption.decode(res);
            cout << point.getX() << ' ' << point.getY();
        }
    }
    return 0;
}
