#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random.hpp>

using namespace boost::multiprecision;
using namespace boost::random;

struct RSAKeys
{
    cpp_int e, d, n;
    // RSAKeys(cpp_int e, cpp_int d, cpp_int n):e(e),d(d),n(n){}
};


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

// Miller-Rabin primality test
bool isPrime(cpp_int n, int confidence_level = 10){
    if(n <= 1 || n == 4) return false;
    if(n <= 3) return true;
    if(n % 2 == 0) return false;

    // calculate n - 1 = 2^k * m
    cpp_int m = n - 1;
    while(m % 2 == 0)  m /= 2;

    std::random_device rd;
    mt19937 generator(rd());
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

cpp_int gcd(cpp_int a, cpp_int b){
    if(b == 0) return a;
    return gcd(b, a%b);
}

//  extended euclidian algorithm helps to derive the coefficient of x and y.
//  in extended eulid we need to solve 
//           a.x + b.y = g --> (i)
//  where g is the gcd(a,b)
//  after getting (x, y) = (1, 0) we can move backwards up to the recursive call
//  all we have to do is to find out how the coefficients x and y change, i.e. the changing equation
//  of x and y during the transition from (a, b) to (b, a mod b). as the transition happens in every iteration,
//  coefficients x and y also changes. 
//  let assume the coefficient x1 and y1 for (b, a mod b)
//  then a.x + b.y = g => b.x1 + (a mod b).y1 = g ---> (ii)
//  we can write a mod b = a - floor(a/b)*b --> (iii)
//  by substituting (ii) and (iii), we get
//     b.x1 + (a-floor(a/b)*b).y1 = g
//  => b.x1 + a.y1 - (a/b)*b*y1 = g
//  => a.y1 + b.(x1 - (a/b)*y1) = g --> (iv)
//  comparing (i) and (iv) we get,
//  x = y1
//  y = x1 - (a/b)*y1

cpp_int extendedEuclid(cpp_int a, cpp_int b, cpp_int& x, cpp_int& y){
    if(b == 0){
        x = 1;
        y = 0;
        return a;
    }
    cpp_int x1, y1;
    cpp_int g = extendedEuclid(b, a%b, x1, y1);
    x = y1;
    y = x1 - (a/b)*y1;
    return g;
}

// generate private key d by doing modular inverse e*d mod phi_n = 1 mod phi_n, where 0<=d<=n
// e and phi_n must be coprime i.e. gcd(e, phi_n) = 1, which is the first condition for having a unique modular inverse
// then we need to find the modular inverse d,
// from the equation, e*d + k*phi_n = gcd(e, phi_n) 
// which can solved using extended euclidian algorithm
cpp_int generatePrivateEx(const cpp_int e, const cpp_int phi_n){
    cpp_int x, y;
    cpp_int g = extendedEuclid(e, phi_n, x, y);
    // gcd(e, phi_n)!=1, i.e. e and phi_n are not coprime and the mod-inverse do not exist
    if(g!=1){
        throw std::invalid_argument("Modular Inverse of e does not exist as gcd(e, phi_n)!=1");
        exit(EXIT_FAILURE);
    }
    return (x % phi_n + phi_n) % phi_n;
}

// get random e such that 1 < e < phi_n and gcd(e, phi_n) = 1
cpp_int generatePublicEx(const cpp_int phi_n){
    std::random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<cpp_int> dis(2, phi_n - 1);
    cpp_int e;
    do{
        e = dis(generator);
    }while(gcd(e, phi_n)!=1);
    return e;
}

const RSAKeys generateRSAKey(const int bitLength) {
    cpp_int p = generateLargePrime(bitLength);
    cpp_int q = generateLargePrime(bitLength);
    cpp_int n = p*q;
    cpp_int phi_n = (p-1)*(q-1);
    cpp_int e = generatePublicEx(phi_n);
    cpp_int d = generatePrivateEx(e, phi_n);
    // std::cout<<gcd(e, phi_n)<<"\t"<<(1<e)<<"\t"<<(e>=phi_n)<<"\t"<<(d<=n)<<"\n\n";

    std::cout<<"Public Exponent (e, n) : ( "<< e <<",\t"<< n <<") \n\n"
    <<"Private Exponent (d, n) : ( "<< d << ",\t"<<n<<") \n\n";

    const RSAKeys keys = {e, d, n};
    return keys;
}

void PKCS7(std::string& s, int blockSize){
    int n = s.length();
    int padLength = (blockSize - (n%blockSize));
    for(int i=0;i<padLength;++i) s+=std::to_string(padLength)+" "; 
}

std::vector<cpp_int> encrypt(std::string& s, const cpp_int e, const cpp_int n, int block = 20){
    std::vector<cpp_int> v;
    PKCS7(s, block);
    for (int i = 0; i < s.length(); i += block)
    {
        std::string blockText = s.substr(i, block);
        cpp_int blockValue = 0;
        for(const char c : blockText) blockValue = (blockValue*256) + static_cast<cpp_int>(static_cast<unsigned char>(c));
        cpp_int encryptedBlock = fastExponentiation(blockValue, e, n);
        v.push_back(encryptedBlock);
    }
    return v;
}

std::string decrypt(std::vector<cpp_int>& v, const cpp_int d, const cpp_int n){
    std::string text = "";
    for(const cpp_int i:v)
    {
        cpp_int decryptedBlock = fastExponentiation(i, d, n); // decrypt : m = c^d mod n
        std::string block = "";
        while (decryptedBlock > 0)
        {
            char ch = static_cast<char>(static_cast<unsigned char>(decryptedBlock % 256));
            block = std::string(1, ch) + block;
            decryptedBlock /= 256;
        }
        text += block;
    }
    return text;
}

void removePadding(std::string& s){
    std::istringstream ss(s);
    std::string lastWord;
    for(;ss>>lastWord;);
    int digitCount = lastWord.length()+1;
    int c = std::stoi(lastWord);
    if(c<=s.size()){
        while(c>0){
            s.pop_back();
            if(s[s.size()-1]==' '){
                continue;
            }
            --digitCount;
            if(digitCount == 0){
                digitCount = lastWord.length();
                --c;
            }
        }
    }
    else{
        std::cout << "Error: Number to remove is greater than string length." << std::endl;
        exit(EXIT_FAILURE);
    }
}

int main(void){
    int bitLength = 512;
    const RSAKeys keys = generateRSAKey(bitLength);
    std::string s,temp;
    std::cout<<"Enter Message : ";
    getline(std::cin, s);
    temp = s;
    std::vector<cpp_int> cipher = encrypt(s, keys.e, keys.n);
    std::string text = decrypt(cipher, keys.d, keys.n);
    removePadding(text);
    std::cout<<text<<"\n\n"<<(text == temp ? "IDENTICAL!!":"NOT IDENTICAL")<<"\n"<<s.length()<<" "<<text.length();
}