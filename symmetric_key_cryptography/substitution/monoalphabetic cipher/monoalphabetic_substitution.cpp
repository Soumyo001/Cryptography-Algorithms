//This is just a random example of mono alphabetic substitution.

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <random>
#include <ctime>

void generate_dictionary(std::unordered_map<char, char>& cipher){
    for(char i = 'a'; i<='z'; ++i){
        char cipher_char = 65+std::rand()%26;
        cipher[i] = cipher_char;
    }

    for(char i = 'A'; i<='Z'; ++i){
        char cipher_char = 97+std::rand()%16;
        cipher[i] = cipher_char;
    }
}

int main(void){
    srand(time(0));
    std::unordered_map<char, char> cipher;
    generate_dictionary(cipher);
    for(auto& i:cipher) std::cout<<i.first<<" "<<i.second<<"\n";
    std::string s;
    getline(std::cin, s);
    for (int i = 0; i < s.length(); i++)
    {
        if(s[i] == ' ') continue;
        s[i] = cipher[s[i]];
    }
    std::cout<<s<<"\n";
    
}