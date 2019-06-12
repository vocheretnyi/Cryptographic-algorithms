//
// Created by Viacheslav on 09.12.2018.
//

#include "ElGamalEncryption.h"

ElGamalEncryption::ElGamalEncryption() {
    a = 2;
    b = 3;
    p = 67;
    e1 = EllypticPoint(2, 22);
    d = 4;
    e2 = e1 * d;
}

pair<EllypticPoint, EllypticPoint> ElGamalEncryption::encode(EllypticPoint P) {
    BigInteger r = 2;
    C1 = e1 * r;
    C2 = P + (e2 * r);
    return make_pair(C1, C2);
}

EllypticPoint ElGamalEncryption::decode(pair<EllypticPoint, EllypticPoint> C) {
    EllypticPoint P = C.second + (-(C.first * d));
    return P;
}
