//
// Created by Viacheslav on 09.11.2018.
//

#ifndef BIGINTEGER_ALGORITHMS_H
#define BIGINTEGER_ALGORITHMS_H

#include "BigInteger.h"

using namespace BigIntegerLibrary;


class Algorithms {

private:
    //Helper for chinese, return a^(-1) mod m
    BigInteger inverse(BigInteger a, BigInteger m);

    BigInteger random(BigInteger l, BigInteger r);

    vector<BigInteger> listOfPrimeDivisors;

    // Check for primality using Miller-Rabin, where k = number of iteration
    bool isPrime_MillerRabin(const BigInteger& n, int k = 5);

    bool isPrime_naive(long long);

    // return random divisor of n using Pollard-Rho algo
    BigInteger pollardRho(BigInteger n);

    void recursive_factorization(BigInteger n);

public:

    BigInteger chineseSolver(const vector<BigInteger>& a, const vector<BigInteger>& r);


    vector<BigInteger> factorization(BigInteger n);


    bool isPrime(const BigInteger& n);


};


#endif //BIGINTEGER_ALGORITHMS_H
