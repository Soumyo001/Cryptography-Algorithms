#include <bits/stdc++.h>

const std::string key = "KEVINMITNICKISAGENIOUS";

std::vector<std::vector<char>> prepareGrid(std::string& s, std::string& key){
    std::vector<char> v(key.length());
    std::vector<std::vector<char>> grid;
    for(int i=0;i<key.length();++i) v[i] = key[i];
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

std::string encrypt(std::string& key, std::string& s){
    s.erase(std::remove_if(s.begin(),s.end(),[](const char c){
        return !isalpha(c);
    }), s.end());
    for(auto& c:s) c = toupper(c);

    std::string cipher = "";
    std::vector<std::vector<char>> grid = prepareGrid(s, key);
    std::vector<bool> visited(key.length(), false);

    std::cout<<"Matrix : \n";
    for(auto& i:grid){
        for(auto& j:i) std::cout<<j<<" ";
        std::cout<<"\n";
    }

    std::vector<char> order_key(key.begin(), key.end());
    sort(order_key.begin(), order_key.end());

    std::cout<<"Encryption Order : \n";
    for(auto& i:order_key) std::cout<<i<<" ";
    std::cout<<"\n";

    for(auto& k:order_key){
        for (int i = 0; i < grid[0].size(); i++)
        {
            if(grid[0][i] == k && !visited[i]){
                for (size_t j = 1; j < grid.size(); j++)
                {
                    cipher+=std::string(1, grid[j][i]);
                }
                visited[i] = true;
                break;
            }
        }
        cipher+=" ";
    }

    return cipher;
}

std::pair<int, int> getDim(std::string& s){
    std::pair<int, int> dim;
    std::istringstream stream(s);
    std::string chunk;
    while (stream>>chunk)
    {
        dim.first = chunk.length()+1;
        ++dim.second;
    }
    return dim;
}

std::string decrypt(std::string& s, std::string& key){
    std::pair<int,int> gridDim = getDim(s);
    std::vector<std::vector<char>> grid(gridDim.first, std::vector<char>(gridDim.second));
    for(size_t i = 0; i < key.length(); ++i) grid[0][i] = key[i];
    std::vector<char> order_key(key.begin(), key.end());
    sort(order_key.begin(), order_key.end());
    std::vector<bool> visited(key.length(), false);
    std::istringstream stream(s);
    std::string chunk;
    for(size_t k = 0; k < order_key.size() && stream>>chunk; ++k){
        for(size_t i = 0; i < grid[0].size(); ++i)
        {
            if(grid[0][i] == order_key[k] && !visited[i]){
                for(size_t j = 1; j < grid.size(); ++j){
                    grid[j][i] = chunk[j-1];
                }
                visited[i] = true;
                break;
            }
        }
    }

    std::string text = "";

    for(size_t i = 1; i < grid.size(); ++i){
        for(size_t j = 0; j < grid[i].size(); ++j) text += grid[i][j];
    }

    long pos = text.find_last_not_of('X');
    text.resize(pos+1);
    return text;
}

int main(void){
    std::cout<<"Enter Key : ";
    std::string test_key;
    std::cin>>test_key;
    std::cin.ignore();
    if(key!=test_key){
        std::cerr<<"Invalid Key. Exiting... \n";
        return EXIT_FAILURE;
    }
    std::string s;
    std::cout<<"Enter Text : ";
    getline(std::cin, s);
    std::string cipher = encrypt(test_key, s);
    std::cout<<cipher<<"\n";
    std::string text = decrypt(cipher, test_key);
    std::cout<<text;

}