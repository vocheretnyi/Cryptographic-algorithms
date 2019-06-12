//
// Created by Viacheslav on 09.12.2018.
//

#ifndef CRYPTOGRAPHIC_ALGORITHMS_ELLYPTICPOINT_H
#define CRYPTOGRAPHIC_ALGORITHMS_ELLYPTICPOINT_H

#include "BigInteger.h"
#include "Algorithms.h"

using namespace BigIntegerLibrary;

class EllypticPoint {
public:
    EllypticPoint();
    EllypticPoint(BigInteger _x, BigInteger _y);

    EllypticPoint& operator=(const EllypticPoint&);

    EllypticPoint operator+(const EllypticPoint &other) const;
    EllypticPoint operator*(const BigInteger &c) const;
    EllypticPoint operator-() const;

    const BigInteger& getX() const;

    const BigInteger& getY() const;

private:
    BigInteger x, y;
    const BigInteger p = 67;
    const BigInteger a = 2;
};


#endif //CRYPTOGRAPHIC_ALGORITHMS_ELLYPTICPOINT_H
