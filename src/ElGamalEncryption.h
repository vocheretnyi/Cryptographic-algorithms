//
// Created by Viacheslav on 09.12.2018.
//

#ifndef CRYPTOGRAPHIC_ALGORITHMS_ELGAMALENCRYPTION_H
#define CRYPTOGRAPHIC_ALGORITHMS_ELGAMALENCRYPTION_H

#include "BigInteger.h"
#include "Algorithms.h"
#include "EllypticPoint.h"

using namespace BigIntegerLibrary;

class ElGamalEncryption {
public:
    ElGamalEncryption();
    pair<EllypticPoint, EllypticPoint> encode(EllypticPoint P);
    EllypticPoint decode(pair<EllypticPoint, EllypticPoint> C);

private:
    EllypticPoint C1, C2;
    EllypticPoint e1, e2;
    BigInteger d;
    BigInteger p;
    BigInteger a, b;
};


#endif //CRYPTOGRAPHIC_ALGORITHMS_ELGAMALENCRYPTION_H
