#include <bits/stdc++.h>

std::vector<std::string> generateSpecialSymbols()
{
    std::vector<std::string> symbols;
    for (char c = 33; c <= 126; ++c)
        symbols.push_back(std::string(1, c));
    for (int i = 0; i < 100; ++i)
        symbols.push_back(std::to_string(i));
    for (char c = 33; c < 126; ++c)
    {
        for (char x = c+1; x <= 126; ++x)
        {
            std::string s = std::string(1, c);
            std::string t = std::string(1, x);
            s += t;
            symbols.push_back(s);
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
        }
    }
    return cipherText;
}

int main(void)
{
    std::vector<std::string> symbols = generateSpecialSymbols();
    std::map<char, double> FDT = readFDT();
    std::map<char, std::vector<std::string>> symbolMap = generateSymbolMap(symbols, FDT);
    displaySymbolMap(symbolMap);
    std::string s;
    std::cout << "Enter Plain Text : ";
    getline(std::cin, s);

    std::string cipherText = encrypt(s, symbolMap);
    std::cout<<cipherText;
}