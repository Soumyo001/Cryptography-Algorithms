#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>

const std::string key = "GYBNQKURP";

void encrypt(std::string& s, std::string& key, int type){
    for(int i = 0, j = 0; i < s.length(); ++i){
        if((s[i] >= 65 && s[i] <= 90) || ( s[i] >= 97 && s[i] <= 122)){
            if(type == 2){
                if(isupper(s[i]))  //Enter plain text : Hi I am Soumyo!! ThIs Is A SeCrEt pASSworD, Don'T gIve This tO aNyBoDy!!
                {
                    if (s[i] + ( toupper(key[j % key.length()]) - 65 ) > 90)
                        s[i] = 64 + ( s[i] + ( toupper(key[j % key.length()]) - 65 ) ) - 90;
                    
                    else
                        s[i] += (toupper(key[j % key.length()]) - 65);
                }
                else if(islower(s[i]))
                {
                    if(s[i] + ( tolower(key[j % key.length()]) - 97 ) > 122)
                        s[i] = 96 + (s[i] + (tolower(key[j % key.length()]) - 97)) - 122;
                    
                    else
                        s[i] += (tolower(key[j % key.length()]) - 97);
                }
            }else{
                if(isupper(s[i]))
                {
                    if(s[i] - (toupper(key[j % key.length()]) - 65) < 65)
                        s[i] = 91 - (65 - (s[i] - (toupper(key[j % key.length()]) - 65)));

                    else
                        s[i] -= (toupper(key[j % key.length()]) - 65);
                }
                else if(islower(s[i]))
                {
                    if(s[i] - (tolower(key[j % key.length()]) - 97) < 97)
                        s[i] = 123 - (97 - (s[i] - (tolower(key[j % key.length()]) - 97)));

                    else
                        s[i] -= (tolower(key[j % key.length()]) - 97);
                }
            }

            ++j;
        }
    }
}

int main(void){
    std::string test_key;
    std::cout<<"Enter Key (Key must be a single stream uppercase) :";
    std::cin>>test_key;
    std::cin.ignore();
    if(key!=test_key) return EXIT_FAILURE;
    for (char c : test_key) {
        if (!isupper(c)) {
            std::cerr << "Key must be uppercase alphabetic characters only.\n";
            return EXIT_FAILURE;
        }
    }
    std::string s;
    std::cout<<"Enter plain text : ";
    getline(std::cin, s);
    test_key += s;
    test_key.erase(std::remove_if(test_key.begin(), test_key.end(),[](const char c){
        return !isalpha(c);
    }), test_key.end());
    int type;
    std::cout<<"Beaufort Cipher (extended) (1)\nVigenere Cipher (extended) (2)\n:";
    while (true)
    {
        std::cin>>type;
        if(type == 1 || type == 2 ) break;
        else{
            std::cout<<":";
            continue;
        }
    }
    
    encrypt(s, test_key, type);
    std::cout<<s<<"\n";
}