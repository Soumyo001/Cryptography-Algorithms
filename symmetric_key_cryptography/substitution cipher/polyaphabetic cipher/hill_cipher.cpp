#include <bits/stdc++.h>

const std::string key = "GYBNQKURP";

// encryption in hill climb cypher : C = K.P mod 26
// decryption in hill climb cypher : D = K^-1.C mod 26

std::vector<std::vector<int>> getKeyMatrix(int block){
    std::cout<<"Enter Key : ";
    std::string test_key;
    std::cin>>test_key;
    std::cin.ignore();
    if(test_key.length() !=  block*block){
        std::cerr<<"Invalid Key. Must be a multiple of block size. ";
        exit(1);
    }
    std::vector<std::vector<int>> keyMatrix(block, std::vector<int>(block, 0));
    for(int i=0; i< block*block; ++i){
        keyMatrix[i/block][i%block] = toupper(test_key[i]) - 'A';
    }
    return keyMatrix;
}

std::string getPlainText(){
    std::cout<<"Enter Message : ";
    std::string s;getline(std::cin, s);
    for(int i=0; i<s.length(); ++i) if(isalpha(s[i])) s[i] = toupper(s[i]);
    return s;
}

std::vector<int> stringToNumber(std::string s){
    std::vector<int> numbers;
    for(auto& i:s) if(isalpha(i)) numbers.push_back(toupper(i) - 'A');
    return numbers;
}

std::string encrypt(std::vector<std::vector<int>>& keyMatrix, std::string& s, int block){
    std::vector<int> numbers = stringToNumber(s);
    while ((int)numbers.size() % block != 0 ) numbers.push_back('X' - 'A');
    std::string encryptedText = "";
    for (int x = 0; x < numbers.size(); x+=block)
    {
        std::vector<int> chunk(block, 0);
        for(int i=x, j=0; i < x+block; ++i,++j){
            chunk[j] = numbers[i];
        }
        for(int i=0; i<block; ++i){
            int encryptedChunk = 0;
            for(int j=0; j<block; ++j){
                encryptedChunk += keyMatrix[i][j]*chunk[j];
            }
            encryptedText += char((encryptedChunk%26) + 'A');
        }
    }
    return encryptedText;
}


int main(void){
    std::cout<<"Block size : ";
    int blk_size;std::cin>>blk_size;
    std::vector<std::vector<int>> keyMatrix = getKeyMatrix(blk_size);
    std::string s = getPlainText();
    std::string cipher = encrypt(keyMatrix, s, blk_size);
    std::cout<<cipher;
}