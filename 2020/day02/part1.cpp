#include <iostream>
#include <vector>
#include <string>

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

    int valid_passwords = 0;
    std::string range, rule, password;

    for(int i = 0; i < 1000; i++){
        std::cin >> range >> rule >> password;

        char character = rule[0];

        std::vector<std::string> range_split = split_string(range, '-');

        int from = std::stoi(range_split[0]);
        int to = std::stoi(range_split[1]);

        int char_occ = 0;
        for(size_t k = 0; k < password.length(); k++){
            if(password[k] == character){
                char_occ++;
            }
        }

        if(from <= char_occ && char_occ <= to){
            valid_passwords++;
        }
    }

    std::cout << valid_passwords << '\n';

    return 0;
}
