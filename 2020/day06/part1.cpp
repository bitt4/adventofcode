#include <iostream>
#include <map>

int main(){

    std::map<char, bool> group_answ;
    std::string line;
    uint32_t sum = 0;

    for(size_t i = 0; i < 2087; i++){
        std::getline(std::cin, line);

        for(size_t j = 0; j < line.length(); j++){
            group_answ[line[j]] = true;
        }

        if(line == "" || i == 2086){
            for(char c = 'a'; c <= 'z'; c++){
                if(group_answ[c]){
                    sum++;
                }
            }

            group_answ.clear();
        }
    }

    std::cout << sum << '\n';

    return 0;
}
