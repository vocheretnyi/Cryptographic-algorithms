//
// Created by Viacheslav on 09.11.2018.
//

#include "Algorithms.h"

BigInteger Algorithms::inverse(BigInteger a, BigInteger m) {
    BigInteger x, y;
    BigInteger g = BigIntegerLibrary::gcdex(a, m, x, y);
    if (g != BigInteger(1)) {
        //TODO
        return BigInteger(-1);
    } else {
        x = (x % m + m) % m;
        return x;
    }
}

BigInteger Algorithms::chineseSolver(const vector<BigInteger>& a, const vector<BigInteger>& r) {
    BigInteger M(1);
    int len = a.size();
    for (const BigInteger& a_i: a) {
        M *= a_i;
    }
    vector<BigInteger> m(len), rev_m(len);
    BigInteger x(0);
    for (int i = 0; i < len; ++i) {
        m[i] = M / a[i];
        rev_m[i] = inverse(m[i], a[i]);
        if (rev_m[i] < zero) {
            return BigInteger(-1);
        }
        x = (x + r[i] * m[i] * rev_m[i]) % M;
    }
    return x;
}

BigInteger Algorithms::pollardRho(BigInteger n) {
    const int iterations_count = 1e5;
//    BigInteger x = random(1, n - 2);
//    BigInteger y = 1;
//    for (long long i = 0, stage = 2; gcd(n, abs(x - y)) == 1; ++i) {
//        if (i == stage) {
//            y = x;
//            stage *= 2;
//        }
//        x = (x * x - 1) % n;
//    }
//    return gcd(n, abs(x - y));
    BigInteger b0 = random(0, n - 1);
    BigInteger b1 = b0;
    BigInteger g;
    b1 = b1 * b1 % n;
    b1 = b1 + 1;
    if (b1 == n) {
        b1 = 0;
    }
    g = gcd(abs(b1 - b0), n);
    for (int i = 0; i < iterations_count && (g == 1 || g == n); ++i) {
        b0 = b0 * b0 % n;
        b0 = b0 + 1;
        if (b0 == n) {
            b0 = 0;
        }
        b1 = b1 * b1 % n;
        b1 = b1 + 1;
        b1 = b1 * b1 % n;
        b1 = b1 + 1;
        if (b1 == n) {
            b1 = 0;
        }
        g = gcd(abs(b1 - b0), n);
    }
    return g;
}

vector<BigInteger> Algorithms::factorization(BigInteger n) {
    if (n == 1 || isPrime(n)) {
        return vector<BigInteger> {n};
    }

    vector<BigInteger> listOfPrimeDivisors;

    int i = 2;

    while (n > 2 && i < 1000000) {
        while (n % i == 0) {
            n /= i;
            listOfPrimeDivisors.push_back(i);
        }
        ++i;
    }


    while (n > 2) {
        BigInteger g = pollardRho(n);
        vector<BigInteger> tmp = factorization(g);
        listOfPrimeDivisors.insert(listOfPrimeDivisors.end(), tmp.begin(), tmp.end());
        n /= g;

        if (isPrime(n)) {
            break;
        }
    }

    if (n > 1) {
        listOfPrimeDivisors.push_back(n);
    }
    return listOfPrimeDivisors;
}

BigInteger Algorithms::random(BigInteger l, BigInteger r) {
    BigInteger randomNumber = BigInteger(rand()) % (r - l + 1);
    return randomNumber + l;
}

bool Algorithms::isPrime_naive(long long n) {
    if (n == 1) {
        return false;
    }
    for (int i = 2; i * 1LL * i <= n; ++i) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

bool Algorithms::isPrime_MillerRabin(const BigInteger &n, int k) {
    if (n % 2 == 0) {
        return false;
    }
    BigInteger m = (n - 1);
    int s = 0;
    while (m % 2 == 0) {
        ++s;
        m /= 2;
    }
    for (int i = 0; i < k; ++i) {
        BigInteger a = random(2, n - 2);
        BigInteger x = powm(a, m, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool flag = false;
        for (int j = 0; j < s - 1; ++j) {
            x = x * x % n;
            if (x == 1) {
                return false;
            }
            if (x == n - 1) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            return false;
        }
    }
    return true;
}

bool Algorithms::isPrime(const BigInteger &n) {
    if (n < 1000000) {
        return isPrime_naive(n.to_int());
    }
    return isPrime_MillerRabin(n);
}
