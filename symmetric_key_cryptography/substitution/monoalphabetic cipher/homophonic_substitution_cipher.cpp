#include <bits/stdc++.h>

// allowing symbols from length = 2 to 3
std::vector<std::string> generateSpecialSymbols()
{
    std::vector<std::string> symbols;
    for (int i = 10; i < 100; ++i){
        symbols.push_back(std::to_string(i));
    }
    for (char c = 33; c < 126; ++c)
    {
        // if(!isalpha(c)) 
        //     symbols.push_back(std::string(1, c));
        for (char x = c+1; x <= 126; ++x)
        {
            std::string s = std::string(1, c);
            std::string t = std::string(1, x);
            s += t;
            symbols.push_back(s);
            for(char z = x; z <= 126; ++z){
                std::string v = std::string(1, z);
                v+=s;
                symbols.push_back(v);
            }
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(symbols.begin(), symbols.end(), g);

    return symbols;
}

std::map<char, double> readFDT()
{
    std::map<char, double> freq;
    std::ifstream file("freq_distribution_table.txt");
    if (!file.is_open())
    {
        std::cerr << "Could not read FDT. \n";
        exit(1);
    }

    std::string line;
    while (getline(file, line))
    {
        std::istringstream stream(line);
        char letter;
        double dist;
        stream >> letter >> dist;
        freq[letter] = dist;
    }
    file.close();
    return freq;
}

void displaySymbolMap(std::map<char, std::vector<std::string>> &symbolMap)
{
    for (auto &i : symbolMap)
    {
        std::cout << i.first << ": ";
        for (auto &j : i.second)
        {
            std::cout << j << " ";
        }
        std::cout << "\n\n";
    }
}

std::map<char, std::vector<std::string>> generateSymbolMap(std::vector<std::string> &symbols, std::map<char, double> &FDT)
{
    std::map<char, std::vector<std::string>> symMap;
    int idx = 0;
    for (char c = 'A'; c <= 'Z'; ++c)
    {
        int symbolCount = std::round((symbols.size() * FDT.at(c)) / 100);
        for (int i = 0; i < symbolCount && idx < symbols.size(); ++i, ++idx)
            symMap[c].push_back(symbols[idx]);
    }

    return symMap;
}

std::map<std::string, char> reverseSymbolMap(std::map<char, std::vector<std::string>>& symMap){
    std::map<std::string, char> revSymMap;
    for(auto& i:symMap) 
        for(auto& j:i.second)
            revSymMap[j] = i.first;
            
    return revSymMap;
}

std::string encrypt(std::string &s, std::map<char, std::vector<std::string>> &symbolMap)
{
    std::default_random_engine generator(static_cast<unsigned>(time(0)));
    std::string cipherText = "";
    for (auto &c : s)
    {
        if (isalpha(c)){
            char upperChar = toupper(c);
            const std::vector<std::string> &pool = symbolMap.at(upperChar);

            std::uniform_int_distribution<int> distribution(0, pool.size() - 1);
            int randIdx = distribution(generator);
            cipherText += pool[randIdx] + " ";
        }else {
            if(c==' '){
                cipherText+="/xSP ";
            }
            else{
                // cipherText+= (c + " "); don't use this as the character is being appended to a string
                // cipherText.append("/SPC");
                // cipherText.append(std::string(1,c));
                // cipherText.append("/SPC ");
                cipherText+= "/xSPC"+std::string(1,c)+"/xSPC ";
            }
        }
    }
    return cipherText;
}

std::string decrypt(std::string& s, std::map<char, std::vector<std::string>>& symbolMap){
    std::map<std::string, char> rsm = reverseSymbolMap(symbolMap);
    std::string chunk, text="";
    std::regex pattern(".*?/xSPC(.*?)/xSPC.*");
    std::stringstream stream(s);
    while (stream>>chunk)
    {
        if(chunk == "/xSP"){
            text += " ";
        }
        else if(chunk.find("/xSPC")!=std::string::npos){
            text+= std::regex_replace(chunk, pattern, "$1");
        }
        else if(rsm.find(chunk)!=rsm.end()){
            char c = rsm.at(chunk);
            if(isalpha(c))
                text+=std::string(1,c);
        }
        else{
            text+=chunk;
        }
    }
    return text;
}

int main(void)
{
    std::vector<std::string> symbols = generateSpecialSymbols();
    for(auto& i:symbols) std::cout<<i<<" ";

    std::map<char, double> FDT = readFDT();
    std::map<char, std::vector<std::string>> symbolMap = generateSymbolMap(symbols, FDT);
    displaySymbolMap(symbolMap);
    std::string s;
    // std::cout << "Enter Plain Text : ";
    // getline(std::cin, s);

    std::ifstream file("input.txt");
    if(!file.is_open()){
        std::cerr<<"Error : can't open file. \n";
        return EXIT_FAILURE;
    }
    std::ostringstream oss;
    oss<<file.rdbuf();
    s = oss.str();
    file.close();

    std::string cipherText = encrypt(s, symbolMap);
    std::cout<<cipherText<<"\n"<<"encryption length : "<<cipherText.length()<<"\n";
    std::string decryptedText = decrypt(cipherText, symbolMap);
    std::cout<<decryptedText<<"\n\n";

    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    std::transform(decryptedText.begin(), decryptedText.end(), decryptedText.begin(), ::tolower);

    if (s == decryptedText) {
        std::cout << "The paragraphs are identical (ignoring case)." << std::endl;
    } else {
        std::cout << "The paragraphs are NOT identical." << std::endl;

        // Print mismatched portions (debugging)
        for (size_t i = 0; i < s.size() && i < decryptedText.size(); ++i) {
            if (s[i] != decryptedText[i]) {
                std::cout << "Mismatch at position " << i << ": "
                << s[i] << " != " << decryptedText[i] << std::endl;
            }
        }
    }
}