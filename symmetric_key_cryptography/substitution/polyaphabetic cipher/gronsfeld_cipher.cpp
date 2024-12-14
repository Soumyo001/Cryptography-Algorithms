#include <iostream>
#include <string>

const std::string key = "5234623431";

void encrypt(std::string& s, std::string key, int type){
    for(int i=0,j=0;i<s.length();++i){
        if(isalpha(s[i])){
            if(type == 1){
                if(isupper(s[i])){
                    if(s[i] - (key[j%key.length()] - '0') < 'A')
                        s[i] = 91 - ('A' - (s[i] - (key[j%key.length()] - '0')));
                    else
                        s[i] -= (key[j%key.length()] - '0');
                }else{
                    if(s[i] - (key[j%key.length()] - '0') < 'a')
                        s[i] = 123 - ('a' - (s[i] - (key[j%key.length()] - '0')));
                    else
                        s[i] -= (key[j%key.length()] - '0');
                }
            }else{
                if(isupper(s[i])){
                    if(s[i] + (key[j%key.length()] - '0') > 'Z')
                        s[i] = 64 + ((s[i] + (key[j%key.length()] - '0')) - 'Z');
                    else
                        s[i] += (key[j%key.length()] - '0');
                }else{
                    if(s[i] + (key[j%key.length()] - '0') > 'z')
                        s[i] = 96 + ((s[i] + (key[j%key.length()] - '0')) - 'z');
                    else
                        s[i] += (key[j%key.length()] - '0');
                }
            }

            ++j;
        }
    }
}

int main(void){
    std::string test_key;
    std::cout<<"Enter Key : ";
    std::cin>>test_key;
    std::cin.ignore();
    if(key!=test_key) return EXIT_FAILURE;
    for(auto& c:test_key) if(!(c>='0' && c<='9')) return EXIT_FAILURE;
    std::string s;
    std::cout<<"Enter Plain Text : ";
    getline(std::cin, s);
    std::cout<<"Left Shift\nRight Shift (1...2): ";
    int type;
    while (true)
    {
        std::cin>>type;
        if(type == 1 || type == 2) break;
    }
    encrypt(s,test_key,type);
    std::cout<<s;
}