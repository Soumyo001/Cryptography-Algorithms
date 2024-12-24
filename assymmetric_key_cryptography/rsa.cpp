#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

using namespace boost::multiprecision;
using namespace boost::random;

cpp_int fastExponentiation(cpp_int base, cpp_int ex, cpp_int mod){
    cpp_int result = 1;
    base = base % mod;
    while (ex > 0)
    {
        if(ex & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        ex >>= 1;
    }
    return result;
}

bool isPrime(cpp_int n, int confidence_level = 10){
    if(n <= 1 || n == 4) return false;
    if(n <= 3) return true;
    if(n % 2 == 0) return false;

    // calculate n - 1 = 2^k % m
    cpp_int m = n - 1;
    while(m % 2 == 0)  m /= 2;

    std::random_device rd;
    mt11213b generator(rd());
    uniform_int_distribution<cpp_int> dis(2, n-2);

    for (int i = 0; i < confidence_level; ++i)
    {
        // choose a => 1 < a < n - 1
        cpp_int a = dis(generator);

        // calculate b0 = a^m mod n
        cpp_int x = fastExponentiation(a, m, n);
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

cpp_int generateLargePrime(int bit){
    std::random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<cpp_int> dis(cpp_int(1)<<(bit-1), (cpp_int(1)<<bit)-1);

    cpp_int choice;
    do
    {
        choice = dis(generator);
        if(!(choice&1)) ++choice;
    } while (!isPrime(choice));
    return choice;
}

int main(void){
    cpp_int p = generateLargePrime(512);
    cpp_int q = generateLargePrime(512);
    cpp_int n = p*q;
    std::cout<<p<<" "<<q<<" "<<n;
}