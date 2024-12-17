#include <bits/stdc++.h>
const std::string key = "GYBNQKURP";

//backward shifting
void encrypt(std::string& s, int shift){
    for(int i=0; i<s.length();++i){
        if((s[i]>=65 && s[i]<=90) || (s[i]>=97 && s[i]<=122)){
            if(isupper(s[i])){
                if(s[i] - (shift % 26) < 65)
                    s[i] = 91 - (65 - (s[i] - (shift % 26)));
                else s[i] -= (shift % 26);
            }else{
                if(s[i] - (shift % 26) < 97)
                    s[i] = 123 - (97 - (s[i] - (shift % 26)));
                else s[i] -= (shift % 26);
            }
        }
    }
}


int main(void){
    std::cout<<"Message : ";
    std::string s;
    getline(std::cin, s);
    
    std::string test_key;
    std::cout<<"Enter Key (Key must be a single stream uppercase) :";
    std::cin>>test_key;
    std::cin.ignore();
    if(key!=test_key)  return EXIT_FAILURE;
    for(auto& c:test_key){
        if(!isalpha(c)) return EXIT_FAILURE;
    }

    std::cout<<"Shift : ";
    int shift;std::cin>>shift;

    encrypt(s, shift);
    std::cout<<s;

}