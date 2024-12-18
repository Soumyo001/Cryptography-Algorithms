#include <bits/stdc++.h>

const std::string key = "GYBNQKURP";

std::string createSubstitutionAlphabet(std::string key){
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string substitutionAlphabet = "";
    for(auto& c : key) if(substitutionAlphabet.find(c)!=std::string::npos) substitutionAlphabet+=c;
    for(auto& c:alphabet)
        if(substitutionAlphabet.find(c)==std::string::npos)
            substitutionAlphabet+=c;
    
    return substitutionAlphabet;
}

void encrypt(std::string& s, std::string subAlpha){
    for(auto& c : s){
        if(isalpha(c)){
            bool upper = isupper(c);
            c = toupper(c);
            c = subAlpha[c-'A'];
            if(!upper) c = tolower(c);
        }
    }
}

int main(void){
    std::string test_key;
    std::cout<<"Enter Key : ";
    std::cin>>test_key;
    std::cin.ignore();
    if(key!=test_key){
        std::cerr<<"Invalid Key. \n";
        return EXIT_FAILURE;
    }
    for(auto& c:test_key) if(!isupper(c)) c = toupper(c);
    std::string s;
    std::cout<<"Enter Plain Text : ";
    getline(std::cin, s);
    std::string substitutionAlphabet = createSubstitutionAlphabet(test_key);
    encrypt(s,substitutionAlphabet);
    std::cout<<s;
}