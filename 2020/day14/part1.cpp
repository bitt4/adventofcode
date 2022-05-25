#include <fstream>
#include <iostream>
#include <map>

using u64 = uint64_t;
using u32 = uint32_t;

u32 get_address(const std::string& mem) {
    size_t i = 4;
    while (mem[i] != ']') {
        i++;
    }
    return std::stoul(mem.substr(5 - 1, 5 + i));
}

u64 apply_mask(const std::string& mask, const u64 num) {
    u64 masked = num;
    for (size_t i = 0; i < 36; ++i) {
        if (mask[i] != 'X') {
            if (mask[i] == '1') {
                masked |= (1UL << (35 - i));
            } else {
                masked &= ~(1UL << (35 - i));
            }
        }
    }

    return masked;
}

int main() {
    std::ifstream input("input");
    std::map<u32, u64> memory;    /* I think memory addresses could in this case be 16-bit, but whatever */

    std::string mask;
    std::string line;
    while (std::getline(input, line)) {
        std::string var = line.substr(0, line.find(' '));
        std::string value = line.substr(line.rfind(' ') + 1);

        if (var == "mask") {
            mask = value;
        } else {
            u32 current_mem = get_address(var);
            memory[current_mem] = apply_mask(mask, std::stoull(value));
        }
    }

    u64 sum = 0;
    for (const auto& [_, x] : memory) {
        sum += x;
    }

    std::cout << sum << '\n';

    return 0;
}
