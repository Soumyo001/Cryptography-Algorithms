#include <bits/stdc++.h>

long long fastExponentiation(long long base, long long ex, long long mod){
    long long result = 1;
    base = base % mod;
    while (ex > 0)
    {
        if(ex & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        ex >>= 1;
    }
    return result;
}

bool isPrime(long long n, int confidence_level = 5){
    if(n <= 1 || n == 4) return false;
    if(n <= 3) return true;

    // calculate n - 1 = 2^k % m
    long long m = n - 1;
    while(m % 2 == 0) m /= 2;

    for (size_t i = 0; i < confidence_level; ++i)
    {
        // choose a => 1 < a < n - 1
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<long long> dis(2, n - 2);
        long long a = dis(generator);

        // calculate b0 = a^m mod n
        long long x = fastExponentiation(a, m, n);
        // check if x is +1 or -1
        if(x == 1 || x == n - 1) continue;

        while (m != n - 1)
        {
            x = (x * x) % n;
            m = m * 2;

            if(x == 1) return false;
            if(x == n - 1) break;
        }
        if(x != n - 1) return false;
    }
    
    return true;
}

long long generateLargePrime(int bit){
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<long long> dis(1LL<<(bit-1), (1LL<<bit)-1);

    long long choice;
    do
    {
        choice = dis(generator);
        if(!(choice&1)) ++choice;
    } while (!isPrime(choice));
    return choice;
}

int main(void){
    long long p = generateLargePrime(32);
    long long q = generateLargePrime(32);
    std::cout<<p<<" "<<q;
}