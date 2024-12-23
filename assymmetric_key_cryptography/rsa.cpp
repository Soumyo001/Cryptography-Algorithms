#include <bits/stdc++.h>
#include <openssl/bn.h>
#include <openssl/crypto.h>

const int N = 1e7+10;

std::vector<bool> sievePrime(){
    std::vector<bool> v(N, true);
    v[0]=v[1]=false;
    for (size_t i = 2; i*i < N; ++i) if(v[i]) for (size_t j = i*i; j < N; j+=i) v[j] = false;
    return v;
}

int main(void){
    std::cout<<(1LL<<(32-1))<<" "<<(1LL<<32)-1;
    const char*  n1 = "131465394891348917894178959058903689034560893456890456890";
    const char*  n2 = "148912378951132451351353455667845673467546767845678475777";


    BIGNUM* bn1 = NULL;
    BIGNUM* bn2 = NULL;
    BN_dec2bn(&bn1, n1);
    BN_dec2bn(&bn2, n2);
    BIGNUM* bn3 = BN_new();
    BN_add(bn3, bn1, bn2);
    const char* n3 = BN_bn2dec(bn3);
    std::cout<<n3;
}