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
    const int iterations_count = 1e3;
    BigInteger b0 = random(0, n - 1);
    BigInteger b1 = b0;
    int q = rand() % 5 + 1;
    b1 = (b1 * b1 + q) % n;
    BigInteger g = gcd(abs(b1 - b0), n);
    for (int i = 0; i < iterations_count && (g == 1 || g == n); ++i) {
        b0 = (b0 * b0 + q) % n;
        b1 = (b1 * b1 + q) % n;
        b1 = (b1 * b1 + q) % n;
        g = gcd(abs(b1 - b0), n);
    }
    return g;
}

vector<BigInteger> Algorithms::factorization(BigInteger n) {

    listOfPrimeDivisors.clear();

    int i = 2;

    while (n > 2 && i < 1000000) {
        while (n % i == 0) {
            n /= i;
            listOfPrimeDivisors.push_back(i);
        }
        if (i == 2) {
            i = 3;
        } else {
            i += 2;
        }
    }

    recursive_factorization(n);

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
    if (n < 10000000) {
        return isPrime_naive(n.to_int());
    }
    return isPrime_MillerRabin(n);
}

void Algorithms::recursive_factorization(BigInteger n) {
    if (isPrime(n)) {
        listOfPrimeDivisors.push_back(n);
        return;
    }
    if (n == 1) {
        return;
    }
    while (n > 2) {
        BigInteger g = pollardRho(n);
        recursive_factorization(g);
        n /= g;

        if (isPrime(n)) {
            break;
        }
    }

    if (n > 1) {
        listOfPrimeDivisors.push_back(n);
    }
}

int Algorithms::mobiusFunction(BigInteger n) {
    if (n == BigInteger(1)) {
        return 1;
    }
    auto fact = factorization(n);
    sort(fact.begin(), fact.end());
    int k = 1;
    for (int i = 1; i < fact.size(); ++i) {
        if (fact[i] != fact[i - 1]) {
            ++k;
        } else {
            return 0; // n % fact[i]^2 == 0
        }
    }
    if (k % 2) {
        return -1;
    }
    return 1;
}

BigInteger Algorithms::eulerFunction(BigInteger n) {
    auto fact = factorization(n);
    sort(fact.begin(), fact.end());
    BigInteger res = n;
    for (int i = 0; i < fact.size(); ++i) {
        if (i == 0 || (fact[i] != fact[i - 1])) {
            res -= res / fact[i];
        }
    }
    return res;
}

int Algorithms::jacobiSymbol(BigInteger a, BigInteger P) {
    if (P == BigInteger(1)) {
        return 1;
    }
    auto fact = factorization(P);
    sort(fact.begin(), fact.end());
    int ans = 1;
    for (BigInteger p: fact) {
        ans *= legendreSymbol(a, p);
        if (ans == 0) {
            return 0;
        }
    }
    return ans;
}

int Algorithms::legendreSymbol(BigInteger a, BigInteger p) {
    if (a % p == 0) {
        return 0;
    }
    if (powm(a, (p - 1) / 2, p) == 1) {
        return 1;
    }
    return -1;
}

BigInteger Algorithms::discreteLog(BigInteger a, BigInteger b, BigInteger m) {
    BigInteger n = sqrt(m) + 1;
    BigInteger A = powm(a, n, m);
    BigInteger cur_a = A;
    map<BigInteger, BigInteger> mp;
    for (int i = 1; i <= n.to_int(); ++i) {
        mp[cur_a] = i;
        cur_a = (cur_a * A) % m;
    }
    cur_a = b;
    for (int i = 0; i < n.to_int(); ++i) {
        if (mp.count(cur_a)) {
            BigInteger ans = mp[cur_a] * n - i;
            if (ans < m) {
                return ans;
            }
        }
        cur_a = (cur_a * a) % m;
    }
    return -1;
}
