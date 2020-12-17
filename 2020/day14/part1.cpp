#include <iostream>
#include <map>

uint32_t get_address(std::string mem){
    size_t i = 4;
    while(mem[i] != ']')
        i++;
    return static_cast<uint32_t>(std::stoul(mem.substr(5 - 1, 5 + i)));
}

uint64_t apply_mask(std::string mask, uint64_t num){
    uint64_t masked = num;
    for(size_t i = 0; i < 36; i++){
        if(mask[i] != 'X'){
            if(mask[i] == '1'){
                masked |= (1UL << (35 - i));
            }
            else {
                masked &= ~(1UL << (35 - i));
            }
        }
    }

    return masked;
}

int main(){

    std::string mask;
    uint64_t sum = 0;
    std::map<uint32_t, uint64_t> memory;    /* I think memory addresses could in this case be 16-bit, but whatever */

    const size_t input_size = 585;

    std::string var, value;
    for(size_t i = 0; i < input_size; i++){
        std::cin >> var;
        std::cin.ignore(3);
        std::cin >> value;

        if(var == "mask")
            mask = value;
        else {
            uint32_t current_mem = get_address(var);
            memory[current_mem] = apply_mask(mask, std::stoull(value));
        }
    }

    for(const auto &x : memory){
        sum += x.second;
    }

    std::cout << sum << '\n';

    return 0;
}
