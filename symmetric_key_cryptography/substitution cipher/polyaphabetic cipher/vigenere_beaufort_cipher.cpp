#include <iostream>
#include <string>

const std::string key = "GYBNQKURP";

void encrypt(std::string& s, std::string& key, int type){
    for(int i=0, j = 0; i < s.length(); ++i){
        if((s[i] >= 65 && s[i] <= 90) || (s[i]>=97 && s[i]<=122)){
            if(type == 2){
                if(isupper(s[i])){

                    if(s[i] + (toupper(key[j % key.length()]) - 65) > 90)
                        s[i] = 64 + (s[i] + (toupper(key[j % key.length()]) - 65)) - 90;
          
                    else
                        s[i] += (toupper(key[j % key.length()]) - 65);

                }else if(islower(s[i])){

                    if(s[i] + (tolower(key[j % key.length()]) - 97) > 122)
                        s[i] = 96 + (s[i] + (tolower(key[j % key.length()]) - 97)) - 122;

                    else
                        s[i] += (tolower(key[j % key.length()]) - 97);

                }
            }else{
                if(isupper(s[i])){

                    if(s[i] - (toupper(key[j % key.length()]) - 65) < 65)
                        s[i] = 91 - (65 - (s[i] - (toupper(key[j % key.length()]) - 65)));

                    else
                        s[i] -= (toupper(key[j % key.length()]) - 65);

                }else if(islower(s[i])){

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
    int type;
    std::cout<<"Beaufort Cipher (1)\nVigenere Cipher (2)\n :";
    while (true)
    {
        std::cin>>type;
        if(type == 1 || type == 2 ) break;
        else{
            std::cout<<" :";
            continue;
        }
    }
    
    encrypt(s, test_key, type);
    std::cout<<s<<"\n";
}