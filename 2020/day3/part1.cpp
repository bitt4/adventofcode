#include <iostream>
#include <vector>

int main(){

    std::string line;
    uint32_t pos = 0, trees = 0;

    for(int i = 0; i < 323; i++){
        std::cin >> line;

        pos %= line.length();

        if(line[pos] == '#')
            trees++;

        pos += 3;
    }

    std::cout << trees << '\n';

    return 0;
}
