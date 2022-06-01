#include <iostream>
#include <fstream>
#include <set>
#include <vector>

int main() {
    std::ifstream input("input");
    if (!input.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    std::set<uint64_t> adapters;

    uint64_t tmp;
    while (input >> tmp) {
        adapters.insert(tmp);
    }

    uint32_t one_jolt_diff = 0,
             three_jolt_diffs = 1; // built-in joltage adapter

    uint64_t last_adapter = 0;
    for (const auto adapter : adapters) {
        uint64_t difference = adapter - last_adapter;

        if (difference == 1) {
            one_jolt_diff++;
        } else if (difference == 3) {
            three_jolt_diffs++;
        }
        last_adapter = adapter;
    }

    std::cout << "part 1: " << one_jolt_diff * three_jolt_diffs << '\n';

    std::vector<uint64_t> dp(*adapters.rbegin() + 1, 0);
    dp[0] = 1;

    for (const auto adapter : adapters) {
        for (size_t i = 1; i <= 3; ++i) {
            if (adapter >= i) {
                dp[adapter] += dp[adapter - i];
            }
        }
    }

    std::cout << "part 2: " << dp.back() << '\n';

    return 0;
}
