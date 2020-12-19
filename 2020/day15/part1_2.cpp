#include <iostream>
#include <vector>
#include <map>

std::vector<std::string> split_string(std::string target, char delimeter = ' '){
    std::vector<std::string> out;
    int position = 0;
    size_t length = target.length();

    for(size_t i = 0; i < length; i++){
        if(target[i] == delimeter){
            out.push_back(std::string(target, position, i - position));
            position = i+1;
            continue;
        }
        if(i == length - 1){
            out.push_back(std::string(target, position, length - position));
        }
    }

    return out;
}

int main(){

    std::map<uint64_t, uint64_t> numbers;
    std::string input;
    std::cin >> input;

    uint64_t last;
    uint64_t turn = 1;

    for(const auto &x : split_string(input, ',')){
        last = std::stoull(x);
        numbers[last] = turn++;
    }

    last = 0;
    turn++;
    uint64_t tmp;

    while(true){
        if(numbers[last] == 0){
            numbers[last] = turn - 1;
            last = 0;
        }
        else {
            tmp = last;
            last = turn - 1 - numbers[last];
            numbers[tmp] = turn - 1;
        }

        if(turn == 2020)
            std::cout << last << '\n';
        else if(turn == 30000000){
            std::cout << last << '\n';
            break;
        }

        turn++;
    }


    return 0;
}
