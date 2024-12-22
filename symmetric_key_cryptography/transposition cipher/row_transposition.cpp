#include <bits/stdc++.h>

const std::string key = "KEVINMITNICK";

std::vector<std::vector<char>> prepareGrid(std::string& s, std::string& key){
    std::vector<std::vector<char>> grid;
    std::vector<char> v(key.begin(), key.end());
    sort(v.begin(), v.end());
    grid.push_back(v);
    v.clear();
    for(auto& i:s){
        v.push_back(i);
        if((int)v.size() == key.length()){
            grid.push_back(v);
            v.clear();
        }
    }
    if(!v.empty()){
        while ((int)v.size()!=key.length())
        {
            v.push_back('X');
        }
        grid.push_back(v); 
    }
    return grid;
}

std::string encrypt(std::string& s, std::string& key){
    s.erase(std::remove_if(s.begin(),s.end(),[](const char c){
        return !isalpha(c);
    }), s.end());
    for(auto& c:s) c = toupper(c);
    std::vector<std::vector<char>> grid = prepareGrid(s, key);
    std::cout<<"Matrix : \n";
    for(const auto& i:grid){
        for(const auto& j:i) std::cout<<j<<" ";
        std::cout<<"\n";
    }

    std::vector<bool> visited(key.length(), false);
    std::string cipher = "";
    for(size_t i = 1; i < grid.size(); ++i){
        for(auto& k:key){
            for (size_t j = 0; j < grid[0].size(); ++j)
            {
                if(grid[0][j] == k && !visited[j]){
                    cipher += grid[i][j];
                    visited[j] = true;
                    break;
                }
            }
        }
        std::fill(visited.begin(), visited.end(), false);
        cipher += " ";
    }
    return cipher;
}

std::pair<int, int> getDim(std::string& s){
    std::pair<int, int> dim = {0, 0};
    std::istringstream stream(s);
    std::string chunk;
    while (stream>>chunk)
    {
        ++dim.first;
        dim.second = chunk.length();
    }
    ++dim.first;
    return dim;
}

std::string decrypt(std::string& s, std::string& key){
    std::pair<int, int> gridDim = getDim(s);
    std::vector<std::vector<char>> grid(gridDim.first, std::vector<char>(gridDim.second));
    for(size_t i = 0; i < grid[0].size(); ++i) grid[0][i] = key[i];
    std::vector<char> order_key(key.begin(), key.end());
    sort(order_key.begin(), order_key.end());
    std::vector<bool> visited(gridDim.second, false);
    std::istringstream stream(s);
    std::string chunk;
    for (int i = 1; i < grid.size() && stream>>chunk; ++i)
        for (int j = 0; j < grid[i].size() && j < chunk.length(); ++j) grid[i][j] = chunk[j];
    std::string text = "";
    for (size_t i = 1; i < grid.size(); i++){
        for (auto &k : order_key){
            for (size_t j = 0; j < grid[i].size(); j++)
            {
                if (grid[0][j] == k && !visited[j])
                {
                    text += grid[i][j];
                    visited[j] = true;
                    break;
                }
            }
        }
        std::fill(visited.begin(), visited.end(), false);
    }
    long pos = text.find_last_not_of('X');
    text.resize(pos+1);
    return text;
}

int main(void){
    std::string test_key;
    std::cout<<"Enter Key : ";
    std::cin>>test_key;
    std::cin.ignore();
    if(key!=test_key){
        std::cerr<<"Error : Invalid Key. Exiting... \n";
        return EXIT_FAILURE;
    }
    std::string s;
    std::cout<<"Enter Text : ";
    getline(std::cin, s);
    std::string cipher = encrypt(s, test_key);
    std::cout<<cipher<<"\n";
    std::string text = decrypt(cipher, test_key);
    std::cout<<text;
}