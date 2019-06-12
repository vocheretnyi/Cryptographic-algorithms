//
// Created by Viacheslav on 09.12.2018.
//

#include "EllypticPoint.h"

EllypticPoint::EllypticPoint() {
    x = 0;
    y = 0;
}

EllypticPoint::EllypticPoint(BigInteger _a, BigInteger _b) {
    x = _a;
    y = _b;
}

EllypticPoint EllypticPoint::operator+(const EllypticPoint& other) const {
    BigInteger x1 = x, y1 = y;
    BigInteger x2 = other.x, y2 = other.y;
    BigInteger x3(0), y3(0);
    Algorithms algorithms = Algorithms();
    if (x1 != x2 && y1 != y2) {
        BigInteger lambda = ((y2 - y1 + p) % p * algorithms.inverse((x2 - x1 + p) % p, p)) % p;
//        lambda = a;
        x3 = (lambda * lambda - x2 - x1 + p * p) % p;
        y3 = (lambda * (x1 - x3) - y1 + p * p) % p;
    } else if (x1 == x2 && y1 == y2) {
        BigInteger lambda = (x1 * x1 * 3 + a + p * p) % p * algorithms.inverse (y1 + y1, p) % p;
//        lambda = a;
        x3 = (lambda * lambda - x2 - x1 + p * p) % p;
        y3 = (lambda * (x1 - x3) - y1 + p * p) % p;
    } else {
//        cout << "Mda";
    }
    return EllypticPoint(x3, y3);
}

EllypticPoint EllypticPoint::operator*(const BigInteger& c) const {
    EllypticPoint res(*this);
    for (int i = 1; i < c.to_int(); ++i) {
        res = res + (*this);
    }
    return res;
}

EllypticPoint EllypticPoint::operator-() const {
    return EllypticPoint(x, (-y + p) % p);
}

const BigInteger& EllypticPoint::getX() const {
    return x;
}

const BigInteger& EllypticPoint::getY() const {
    return y;
}

EllypticPoint& EllypticPoint::operator=(const EllypticPoint& other) {
    x = other.x;
    y = other.y;
    return *this;
}

//void EllypticPoint::setParams(BigInteger _a, BigInteger _b, BigInteger _p) {
//    a = _a;
//    b = _b;
//    p = _p;
//}
