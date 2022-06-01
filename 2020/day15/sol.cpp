#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using u32 = uint32_t;

std::vector<std::string> split_string(std::string s, const std::string delim, std::vector<std::string> acc = {}) {
    auto pos = s.find(delim);
    if (pos != std::string::npos) {
        acc.push_back(s.substr(0, pos));
        return split_string(s.substr(pos + delim.length()), delim, acc);
    } else {
        acc.push_back(s);
        return acc;
    }
}

int main() {
    std::ifstream input_file("input");
    if (!input_file.is_open()) {
        std::cerr << "Can't read puzzle input file.\n";
        return -1;
    }

    std::map<u32, u32> numbers;
    std::string input;

    std::getline(input_file, input);
    input_file.close();

    u32 turn = 1;
    for (const auto &x : split_string(input, ",")) {
        numbers[std::stoul(x)] = turn++;
    }

    u32 last = 0;

    for (; turn < 30'000'000; ++turn) {
        if (numbers[last] == 0) {
            numbers[last] = turn;
            last = 0;
        } else {
            int tmp = last;
            last = turn - numbers[last];
            numbers[tmp] = turn;
        }

        if (turn == 2020 - 1) {
            std::cout << "part 1: " << last << '\n';
        }
    }

    std::cout << "part 2: " << last << '\n';

    return 0;
}
