//
// Created by Viacheslav on 09.11.2018.
//

#ifndef BIGINTEGER_ALGORITHMS_H
#define BIGINTEGER_ALGORITHMS_H

#include "BigInteger.h"
#include <algorithm>
#include <map>

using namespace BigIntegerLibrary;


class Algorithms {

private:

    vector<BigInteger> listOfPrimeDivisors;

    // Check for primality using Miller-Rabin, where k = number of iteration
    bool isPrime_MillerRabin(const BigInteger& n, int k = 5);

    bool isPrime_naive(long long);

    // return random divisor of n using Pollard-Rho algo
    BigInteger pollardRho(BigInteger n);

    void recursive_factorization(BigInteger n);

    pair<BigInteger, BigInteger> powComplexMod(pair<BigInteger, BigInteger> a, BigInteger n, BigInteger m, BigInteger w);

    pair<BigInteger, BigInteger> mulComplex( pair<BigInteger, BigInteger> a,  pair<BigInteger, BigInteger> b, BigInteger w, BigInteger mod);

    void generateKeys();

public:
    BigInteger random(BigInteger l, BigInteger r);
    BigInteger chineseSolver(const vector<BigInteger>& a, const vector<BigInteger>& r);

    //Helper for chinese, return a^(-1) mod m
    BigInteger inverse(BigInteger a, BigInteger m);


    vector<BigInteger> factorization(BigInteger n);


    bool isPrime(const BigInteger& n);

    int mobiusFunction(BigInteger n);

    BigInteger eulerFunction(BigInteger n);

    int jacobiSymbol(BigInteger a, BigInteger p);

    int legendreSymbol(BigInteger a, BigInteger p);

    // using baby-step-giant-step algorithm
    BigInteger discreteLog(BigInteger a, BigInteger b, BigInteger m);

    // using Cipolla's algorithm
    pair<BigInteger, BigInteger> discreteSquareRoot(BigInteger p, BigInteger n);

    void ElGamalEncryption(BigInteger m);
};


#endif //BIGINTEGER_ALGORITHMS_H
