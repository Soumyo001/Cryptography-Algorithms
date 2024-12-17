#include <bits/stdc++.h>

const std::string key = "GYBNQKURP";

void encrypt(std::string& s){
    for(int i=0;i<s.length();++i){
        if(s[i]>=65 && s[i]<=90){
            s[i] = 90-(s[i]-65);
        }else if(s[i]>=97 && s[i]<=122)
        {
            s[i] = 122-(s[i]-97);
        }
    }
}

int main(void){
    std::string test_key;
    std::string s;
    std::cout<<"Enter Plain Text : ";
    getline(std::cin, s);
    std::cout<<"Enter Key : ";
    std::cin>>test_key;
    std::cin.ignore();
    if(key!=test_key) return EXIT_FAILURE;
    encrypt(s);
    std::cout<<s;  
}