#include <bits/stdc++.h>
//I was doing something else here lol. main algo is coming soon

void primeFactors(int n){
    while(n%2==0){
        std::cout<<2<<" ";
        n/=2;
    }

    for(int i= 3; i<sqrt(n);i+=2){
        while (n%i == 0)
        {
            std::cout<<i<<" ";
            n/=i;
        }
    }
    if(n>2) std::cout<<n<<"\n";
}

int main(void){
    primeFactors(28);
}