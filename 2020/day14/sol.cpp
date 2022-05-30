#include <fstream>
#include <iostream>
#include <map>
#include <vector>

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

void fill_memory(std::map<u64, u64>& memory, u64 address, u64 value, std::string mask, u32 i = 36) {
    if (i == 0) {
        memory[address] = value;
        return;
    }

    auto next_bit = mask[i - 1];

    switch (next_bit) {
    case '0':
        fill_memory(memory, address, value, mask, i - 1);
        break;
    case '1':
        fill_memory(memory, address |  (1ULL << (36 - i)), value, mask, i - 1);
        break;
    case 'X':
        fill_memory(memory, address |  (1ULL << (36 - i)), value, mask, i - 1);
        fill_memory(memory, address & ~(1ULL << (36 - i)), value, mask, i - 1);
        break;
    default: {}
    }
}

int main() {
    std::ifstream input("input");
    std::map<u64, u64> memory;
    std::vector<std::tuple<u64, u64, std::string>> program;

    std::string mask;
    std::string line;
    while (std::getline(input, line)) {
        std::string var = line.substr(0, line.find(' '));
        std::string arg = line.substr(line.rfind(' ') + 1);

        if (var == "mask") {
            mask = arg;
        } else {
            u32 current_mem = get_address(var);
            u64 value = std::stoull(arg);
            memory[current_mem] = apply_mask(mask, value);
            program.push_back({ current_mem, value, mask });
        }
    }

    u64 sum1 = 0;
    for (const auto& [_, x] : memory) {
        sum1 += x;
    }

    std::cout << "part 1: " << sum1 << '\n';

    memory.clear();

    for (auto [address, value, mask] : program) {
        fill_memory(memory, address, value, mask);
    }

    u64 sum2 = 0;
    for (const auto& [_, x] : memory) {
        sum2 += x;
    }

    std::cout << "part 2: " << sum2 << '\n';

    return 0;
}
