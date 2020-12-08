#include <iostream>
#include <map>

int main(){

    std::map<char, int> group_answ;
    std::string line;
    uint32_t sum = 0;
    int group_size = 0;

    for(size_t i = 0; i < 2087; i++){
        std::getline(std::cin, line);

        for(size_t j = 0; j < line.length(); j++){
            group_answ[line[j]]++;
        }

        if(line == "" || i == 2086){
            for(char c = 'a'; c <= 'z'; c++){
                if(group_answ[c] == group_size){
                    sum++;
                }
            }

            group_size = 0;
            group_answ.clear();
        }
        else {
            group_size++;
        }
    }

    std::cout << sum << '\n';

    return 0;
}
