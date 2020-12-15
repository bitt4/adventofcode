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

    uint32_t earliest;
    uint64_t min = 18446744073709551615U;    /* 2^64 - 1 */
    std::string line;
    std::vector<uint64_t> timings;

    std::cin >> earliest;
    std::cin >> line;

    for(std::string &x : split_string(line, ',')){
        if(x != "x")
            timings.push_back(stoull(x));
    }

    uint64_t nearest;
    uint64_t first_bus;
    for(uint64_t &i : timings){
        nearest = earliest / i * i + i;
        if(nearest < min){
            min = nearest;
            first_bus = i;
        }
    }

    std::cout << first_bus * (min - earliest);

    return 0;
}
