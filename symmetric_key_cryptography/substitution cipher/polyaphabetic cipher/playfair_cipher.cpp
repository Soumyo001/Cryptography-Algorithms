#include <bits/stdc++.h>

const std::string key = "MITNICK";

std::pair<std::vector<std::vector<char>>, std::map<char, std::pair<int,int>>> prepareKeyMatrix(std::string key){
    std::pair<std::vector<std::vector<char>>, std::map<char, std::pair<int,int>>> keyMatrixPos;
    keyMatrixPos.first.resize(5);
    for(int i=0;i<5;++i) keyMatrixPos.first[i].resize(5);
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string keyAlphabet = "";
    bool hasIJ = false;
    for(auto& c : key) 
        if(keyAlphabet.find(c)==std::string::npos){
            if((c == 'I' || c == 'J') && hasIJ == true)
                continue;
            keyAlphabet+=std::string(1, c);
            if(c == 'I' || c == 'J') 
                hasIJ = true;
        }
    for(auto& c : alphabet) if(keyAlphabet.find(c)==std::string::npos){
        if((c == 'I' || c == 'J') && hasIJ)
            continue;
        keyAlphabet += std::string(1, c);
        if(c == 'I' || c == 'J')
            hasIJ = true;
    }

    for(int i = 0, k = 0; i<5; ++i){
        for(int j = 0; j<5 && k<keyAlphabet.length(); ++j, ++k){
            keyMatrixPos.first[i][j] = keyAlphabet[k];
            keyMatrixPos.second[keyAlphabet[k]] = {i,j};
            if(keyAlphabet[k] == 'I')
                keyMatrixPos.second['J'] = {i,j};
            else if(keyAlphabet[k] == 'J')
                keyMatrixPos.second['I'] = {i,j};
        }
    }
    return keyMatrixPos;
}

void prepareText(std::string& s){
    s.erase(std::remove_if(s.begin(), s.end(), [](const char c){
        return !std::isalpha(c);
    }),s.end());
    for(auto& c : s) c = toupper(c);
    for(int i=0;i<s.length(); i+=2){
        if(i+1<s.length() && s[i] == s[i+1]){
            if(s[i] == 'X') s[i+1] = 'Q';
            else s[i+1] = 'X';
            s.insert(i+2, 1, s[i]);
        }
    }
    if(s.length()&1 ){
        if(s[s.length()-1] == 'X') s+="Q";
        else s+="X";
    }
}

std::string cleanDecryptedText(std::string s) {
    std::string realText = "";
    for (int i = 0; i < s.length(); i+=2) {
        if( (s[i] == 'X'  && s[i+1] == 'Q')
        ||  (s[i] == 'Q'  && s[i+1] == 'X')
        ||  s[i+1] == 'X' || s[i+1] == 'Q'
        ){
            realText += std::string(1, s[i]);
        }else{
            realText += std::string(1, s[i]) + std::string(1, s[i+1]) ;
        }
    }
    return realText;
}

// std::map<char, std::pair<int,int>> getPos(const std::vector<std::vector<char>>& keyMatrix, const char a, const char b){
//     std::map<char,std::pair<int,int>> pos;
//     for(int i=0;i<keyMatrix.size();++i){
//         for(int j=0;j<keyMatrix[i].size();++j){
//             if(keyMatrix[i][j]==a)
//                 pos[a]={i,j};
//             else if(keyMatrix[i][j]==b)
//                 pos[b]={i,j};
//             else if(a=='I' || a=='J')

//         }
//     }
//     return pos;
// }

std::string encrypt(std::vector<std::vector<char>>& keyMatrix, std::string& s, std::map<char, std::pair<int,int>>& keyPos){
    std::string cipher = "";
    for(int c=0;c<s.length();c+=2){
        char a = toupper(s[c]);
        char b = toupper(s[c+1]);
        if(keyPos[a].first == keyPos[b].first){

            cipher += keyMatrix[keyPos[a].first][(keyPos[a].second+1) % 5];
            cipher += keyMatrix[keyPos[b].first][(keyPos[b].second+1) % 5];

        }else if(keyPos[a].second == keyPos[b].second){

            cipher += keyMatrix[(keyPos[a].first+1) % 5][keyPos[a].second];
            cipher += keyMatrix[(keyPos[b].first+1) % 5][keyPos[b].second];

        }else{
            cipher += keyMatrix[keyPos[a].first][keyPos[b].second];
            cipher += keyMatrix[keyPos[b].first][keyPos[a].second];
        }
        cipher+=" ";
    }
    return cipher;
}

std::string decrypt(std::vector<std::vector<char>>& keyMatrix, std::string& s, std::map<char, std::pair<int,int>>& keyPos){
    s.erase(std::remove_if(s.begin(),s.end(),::isspace), s.end());
    std::string text = "";
    for(int i=0;i<s.length();i+=2){
        char a = s[i];
        char b = s[i+1];
        if(keyPos[a].first == keyPos[b].first){
            if(keyPos[a].second - 1 < 0)
                text += keyMatrix[keyPos[a].first][4];
            else
                text += keyMatrix[keyPos[a].first][keyPos[a].second - 1];
            if(keyPos[b].second - 1 < 0)
                text += keyMatrix[keyPos[b].first][4];
            else
                text += keyMatrix[keyPos[b].first][keyPos[b].second - 1];
        }
        else if(keyPos[a].second == keyPos[b].second){
            if(keyPos[a].first - 1 < 0)
                text += keyMatrix[4][keyPos[a].second];
            else
                text += keyMatrix[keyPos[a].first - 1][keyPos[a].second];
            if(keyPos[b].first - 1 < 0)
                text += keyMatrix[4][keyPos[b].second];
            else
                text += keyMatrix[keyPos[b].first - 1][keyPos[b].second];
        }else{
            text += keyMatrix[keyPos[a].first][keyPos[b].second];
            text += keyMatrix[keyPos[b].first][keyPos[a].second];
        }
    }
    return cleanDecryptedText(text);
}

int main(void){
    std::cout<<"Enter Key : ";
    std::string test_key;std::cin>>test_key;
    std::cin.ignore();
    if(key!=test_key)
        return EXIT_FAILURE;
    for(auto& c : test_key) c = toupper(c);
    std::pair<std::vector<std::vector<char>>, std::map<char,std::pair<int,int>>> keyMatrixPos= prepareKeyMatrix(test_key);
    std::vector<std::vector<char>> keyMatrix = keyMatrixPos.first;
    std::map<char,std::pair<int,int>> keyPos = keyMatrixPos.second;
    for(auto& i:keyMatrix){
        for(auto& j:i) std::cout<<j<<" ";
        std::cout<<"\n";
    }
    std::cout<<"Enter Text : ";
    std::string s;
    getline(std::cin, s);
    prepareText(s);
    std::cout<<s<<"\n";
    std::string cipher = encrypt(keyMatrix, s, keyPos);
    std::cout<<cipher<<"\n";
    std::string text = decrypt(keyMatrix, cipher, keyPos);
    std::cout<<text<<"\n\n";
}